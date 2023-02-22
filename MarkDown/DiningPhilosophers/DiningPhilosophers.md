<!-- Das Problem der dinierenden Philosophen -->

Das Beispiel der dinierenden Philosophen ist eines der populärsten Standardprobleme
aus dem Bereich der Parallelprogrammierung.
Es erlaubt, die Kooperation der beteiligten Threads
in einer lebendigen Simulation darzustellen.

Wir stellen eine Standard-Lösung für dieses Problem vor und gehen dabei
vor allem auf die Klasse `std::mutex` und das RAII-Idiom näher ein.
Basiswerkzeuge zur nebenläufigen Programmierung in C++ wie `std::async`, `std::future`
oder auch `std::scoped_lock` werden eingesetzt.


<!--more-->

# Lernziele

  * `std::mutex`
  * `std::scoped_lock` und RAII-Idiom
  * `std::this_thread::get_id` und `std::this_thread::sleep_for`
  * `std::future` und `std::async`
  * `std::atomic`, `fetch_add` und `fetch_sub`
  * STL-Containerklasse `std::array`
  * Berechnung von Zufallszahlen (`std::random_device`, `std::mt19937` und `std::uniform_int_distribution`)
  * Multithreadingsicheres Logging (Benutzerdefinierte Klasse `Logger`)
  * Variadische Templates, *Folding* und *Perfect Forwarding* 

# Einführung

Das Problem in dieser Fallstudie ist das Folgende: In einem Kloster gibt es fünf Mönche, die sich der Philosophie widmen.
Jeder Philosoph wäre glücklich, wenn er nur denken könnte, aber gelegentlich ist auch der menschliche Trieb des Essens zu beachten.
Somit kennt jeder Philosoph drei Beschäftigungen:

  * denken
  * hungrig sein
  * essen

Die gemeinschaftliche Nahrungsaufnahme findet an einem großen Tisch statt, an dem die Philosophen im Kreis sitzen.
In der Mitte des Tisches steht eine Schüssel mit Reis, die immer wieder gefüllt wird.
Auf dem Tisch gibt es ferner fünf Teller und fünf Gabeln. Solange ein Philosoph denkt, geschieht nichts.
Bekommt er Hunger, versucht er zwei Gabeln, und zwar die zu seiner linken und rechten Seite, aufzunehmen.
Ist einer seiner benachbarten Glaubensbrüder gerade beim Essen, muss er warten.
Sind beide Gabeln frei, kann er mit dem Essen beginnen. Nachdem er satt ist, legt er beide Gabeln zurück und denkt wieder.
Die drei Zustände *denken*, *hungrig sein* und *essen* werden folglich ständig in dieser Reihenfolge durchlaufen.


###### {#abbildung_1_dining_philosophers}

{{< figure src="/img/permutations/Dining_Philosophers.png" width="25%" >}}

<sup>Credits: gefunden in einem Artikel [&ldquo;Elixir, Erlang, and the Dining Philosophers&rdquo; von Tony Baker](https://spin.atomicobject.com/2012/10/31/elixir-erlang-and-the-dining-philosophers)</sup>.

*Abbildung* 1: Die dinierenden Philosophen.


Eine Lösung dieses Problems gestattet es, dass jederzeit so viele Philosophen wie möglich essen können
und dass keiner der Philosophen verhungert. Man kann sich leicht überlegen, 
dass stets maximal zwei Philosophen gleichzeitig essen können und dass eine Gabel immer ungenutzt bleibt.

In dieser Fallstudie wollen wir das Problem der dinierenden Philosophen in einer C++&ndash;Konsolen-Anwendung umsetzen.
Im Mittelpunkt steht die Auseinandersetzung mit den Hilfsmittels des Multithreadings.
Wie schon erwähnt geht es darum, dass der Zugriff auf eine Gabel durch die beiden benachbarten Philosophen
korrekt zu erfolgen hat. Zwei Philosophen dürfen dieselbe Gabel nicht zu einem Zeitpunkt gleichzeitig aufnehmen, und:
Ist ein Philosoph im Besitz zweier Gabeln, so legt er diese nach einer bestimmten Essenzeit wieder auf den Tisch zurück,
so dass diese von den benachbarten Philosophen aufgenommen werden können.


In einer semi-grafischen Ausgabe könnten wir das Problem beispielsweise auf diese Weise visualisieren:

```
[1]: Dining Philosophers Simulation [TID=1]
[2]: Philosopher 1 enters room [11272]
[3]: Philosopher 2 enters room [17056]
[2]: Philosopher 1 is thinking (at seat 0)
[4]: Philosopher 3 enters room [7336]
[5]: Philosopher 4 enters room [16980]
[3]: Philosopher 2 is thinking (at seat 1)
[4]: Philosopher 3 is thinking (at seat 2)
[5]: Philosopher 4 is thinking (at seat 3)
[6]: Philosopher 5 enters room [13908]
[6]: Philosopher 5 is thinking (at seat 4)
[3]: Philosopher 2 is hungry (at seat 1)
[2]: Philosopher 1 is hungry (at seat 0)
[3]: Philosopher 2 started eating (at seat 1) [2] uses forks 1 - 2
[5]: Philosopher 4 is hungry (at seat 3)
[5]: Philosopher 4 started eating (at seat 3) [4] uses forks 3 - 4
[4]: Philosopher 3 is hungry (at seat 2)
[6]: Philosopher 5 is hungry (at seat 4)
[3]: Philosopher 2 finished eating (at seat 1)    released forks 1 - 2
[2]: Philosopher 1 started eating (at seat 0) [4] uses forks 0 - 1
[3]: Philosopher 2 is thinking (at seat 1)
[3]: Philosopher 2 is hungry (at seat 1)
[5]: Philosopher 4 finished eating (at seat 3)    released forks 3 - 4
[4]: Philosopher 3 started eating (at seat 2) [4] uses forks 2 - 3
[5]: Philosopher 4 is thinking (at seat 3)
[5]: Philosopher 4 is hungry (at seat 3)

...

[6]: Philosopher 5 is thinking (at seat 4)
[6]: Philosopher 5 is hungry (at seat 4)
[2]: Philosopher 1 finished eating (at seat 0)    released forks 0 - 1
[6]: Philosopher 5 started eating (at seat 4) [4] uses forks 4 - 0
[2]: Philosopher 1 leaves room
[4]: Philosopher 3 finished eating (at seat 2)    released forks 2 - 3
[3]: Philosopher 2 started eating (at seat 1) [4] uses forks 1 - 2
[4]: Philosopher 3 is thinking (at seat 2)
[6]: Philosopher 5 finished eating (at seat 4)    released forks 4 - 0
[5]: Philosopher 4 started eating (at seat 3) [4] uses forks 3 - 4
[6]: Philosopher 5 is thinking (at seat 4)
[6]: Philosopher 5 is hungry (at seat 4)
[4]: Philosopher 3 is hungry (at seat 2)
[5]: Philosopher 4 finished eating (at seat 3)    released forks 3 - 4
[6]: Philosopher 5 started eating (at seat 4) [4] uses forks 4 - 0
[5]: Philosopher 4 is thinking (at seat 3)
[5]: Philosopher 4 is hungry (at seat 3)
[3]: Philosopher 2 finished eating (at seat 1)    released forks 1 - 2
[4]: Philosopher 3 started eating (at seat 2) [4] uses forks 2 - 3
[3]: Philosopher 2 leaves room
[6]: Philosopher 5 finished eating (at seat 4)    released forks 4 - 0
[6]: Philosopher 5 is thinking (at seat 4)
[6]: Philosopher 5 is hungry (at seat 4)
[6]: Philosopher 5 started eating (at seat 4) [4] uses forks 4 - 0
[6]: Philosopher 5 finished eating (at seat 4)    released forks 4 - 0
[6]: Philosopher 5 is thinking (at seat 4)
[4]: Philosopher 3 finished eating (at seat 2)    released forks 2 - 3
[5]: Philosopher 4 started eating (at seat 3) [2] uses forks 3 - 4
[4]: Philosopher 3 leaves room
[6]: Philosopher 5 is hungry (at seat 4)
[5]: Philosopher 4 finished eating (at seat 3)    released forks 3 - 4
[6]: Philosopher 5 started eating (at seat 4) [2] uses forks 4 - 0
[5]: Philosopher 4 leaves room
[6]: Philosopher 5 finished eating (at seat 4)    released forks 4 - 0
[6]: Philosopher 5 leaves room
[1]: Simulation Done.
```

Derartige Ausgaben sind zwar nicht ganz so schön wie eine grafische Oberfläche,
aber man kann &ndash; wenn man die einzelnen Zeile genau betrachtet &ndash; doch die relevanten Details
im Ablauf der Verköstigung von fünf Mönchen gut erkennen.

Wir stellen nun im Lösungsabschnitt der Reihe nach die relevanten C++&ndash;Klassen vor,
die dieser Realisierung zu Grunde liegen.


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

## Klasse `Fork`

Wir beginnen unsere Betrachtungen in der Umsetzung des Philosophenproblems mit dem schwierigsten Abschnitt,
nämlich wie sich der konkurrierende Zugriff zweier Philosophen auf eine Gabel in C++ gestalten lässt.
Softwaretechnisch ist für den konfliktfreien Zugriff auf ein kritisches Objekt bzw.
auf eine kritische Folge von Anweisungen die Klasse `std::mutex` das Mittel der Wahl.
Mit den beiden Methoden `lock` und `unlock` dieser Klasse kann man erreichen, dass kritische Code-Passagen
zu einem bestimmten Zeitpunkt immer nur von einem Thread betreten (und verlassen) werden können.

Jede Gabel (Klasse `Fork`) besitzt aus diesem Grund ein solches `std::mutex`-Objekt,
weitere Funktionalitäten sind für ein Gabelobjekt nicht notwendig ([Listing 1]):


###### {#listing_01_class_fork}

```cpp
01: class Fork
02: {
03: private:
04:     std::mutex m_mutex;
05: 
06: public:
07:     std::mutex& getMutex() { return m_mutex; }
08: };
```

*Listing* 1: Klasse `Fork`.

## Klasse `Table`

Gemäß der Problemstellung liegen fünf Gabelobjekte auf dem Essenstisch.
Wir modellieren deshalb eine Klasse `Table` mit fünf `Fork`-Objekten,
die wir in einem `std::array`-Objekt ablegen.
Da zu bestimmten Zeitpunkten auf ein Gabelobjekt zugegriffen wird, kapseln wir den Zugriff auf dieses Feld
mit einer Überladung des Index-Operators `[]`.

Die Sicherstellung, dass zu einem bestimmten Zeitpunkt nur eine Gabel von einem Philosophen aufgegriffen werden kann,
erfolgt durch die Philosophen-Objekte. Anders formuliert: Der Tisch stellt Gabeln mit ` std::mutex`-Objekten zur Verfügung,
der Aufruf der Methoden `lock` und `unlock` erfolgt indirekt durch die Initiative der Philosophen. 

###### {#listing_02_class_table_decl}

```cpp
01: class Table
02: {
03: private:
04:     std::array<Fork, NumPhilosophers> m_forks;
05:     std::atomic<int> m_numForksInUse;
06: 
07: public:
08:     Table();
09: 
10:     // index operator
11:     Fork& operator[] (size_t index);
12: 
13:     // public interface
14:     void incrementNumForks();
15:     void decrementNumForks();
16:     int numForks() const;
17: };
```

*Listing* 2: Klasse `Table` &ndash; Spezifikation.

Das Salz in der Suppe dieser Fallstudie ist natürlich die Beobachtung des Umstands,
dass zu keinem Zeitpunkt der Simulation
fünf Gabeln gleichzeitig zum Essen verwendet werden. Da ein Philosoph immer zwei Gabeln zum Essen benötigt,
müssen folglich stets eine, drei, oder fünf freie Gabeln auf dem Tisch liegen. Sollten alle fünf Gabeln in Gebrauch sein,
haben wir einen Fehler in der Simulation vorliegen.

Um die Anzahl der in Gebrauch befindlichen Gabeln besser beobachten zu können,
haben wir das Tischobjekt noch um eine `int`-Variable `m_numForksInUse` ergänzt.
Da die Aktivitäten eines Philosophen im Kontext eines Threads
stattfinden (wir kommen darauf noch zu sprechen), muss der schreibende und lesende Zugriff auf diese `m_numForksInUse`-Variable *threadsicher* sein.
Damit sind wir beim Klassen-Template `std::atomic<T>` angekommen, siehe Zeile 5 von [Listing 2].
Mit Hilfe dieser Klasse ist es möglich, den Wert von `m_numForksInUse` threadsicher &ndash; sprich *atomar* &ndash; zu verändern.

Weiter geht es mit der Realisierung der Methoden aus [Listing 2]:

###### {#listing_03_class_table_impl}

```cpp
Table::Table() : m_numForksInUse{} {}

Fork& Table::operator[] (size_t index)
{
    size_t seat{ index % 5 };
    return m_forks[seat];
}

void Table::incrementNumForks() {
    m_numForksInUse.fetch_add(2);
}

void Table::decrementNumForks() {
    m_numForksInUse.fetch_sub(2);
}

int Table::numForks() const {
    return m_numForksInUse.load();
}
```

*Listing* 3: Klasse `Table` &ndash; Realisierung.


Man beachte in [Listing 3], dass stets zwei Gabeln von einem Philosophen aufgenommen bzw. abgelegt werden.
Aus diesem Grund ist die Variable `m_numForksInUse` immer um den Wert 2 zu inkrementieren oder zu dekrementieren.

Damit sind wir beim zentralen Punkt in der Anwendung angekommen, der Realisierung eines Philosophen:

## Klasse `Philosopher`

In unserer Realisierung hat ein Philosoph einen Namen und
sitzt an einem Tisch. Die Position am Tisch beschreiben wir mit einem
Index, der Werte von 0 bis 4 annehmen kann. Die Position des Philosophen
am Tisch spielt insofern eine Rolle, da auf diese Weise die beiden 
Gabeln zu seiner linken und rechten Seite bestimmt sind.
Also dem dritten Philosoph ist die dritte und vierte Gabel
aus dem Feld `m_forks` (siehe Zeile 4 von [Listing 3]) zugeordnet, etc.

Des Weiteren kann ein Philosoph &ldquo;denken&rdquo;, &ldquo;hungrig sein&rdquo; und &ldquo;essen&rdquo;,
was wir mit entsprechenden Methoden `thinking`, `hungry` und `eating` simulieren.
Die Methode `dine` wiederum bildet den gesamten Lebenszyklus
eines Philosoph ab, den wir zur Laufzeit in einem Thread ausführen.
Um einen Thread erzeugen zu können, bieten sich in C++ prinzipiell die Klasse `std::thread`
oder das Funktionstemplate `std::async<T>` an. 
Ich habe mich für die Variante mit `std::async` entschieden,
es kommt infolgedessen auch noch das Klassen-Template
`std::future<T>` mit ins Spiel.

Den Lebenszyklus eines Philosophen wollen wir explizit starten und beenden können,
diesem Zweck dienen die beiden Methoden `start` und `stop`. 
Weitere Details in der Konzeption und Realisierung eines Philosophen stellen wir nun
in [Listing 4] und [Listing 5] vor:


###### {#listing_04_class_philosopher_decl}

```cpp
01: class Philosopher
02: {
03: private:
04:     std::string m_name;
05:     Table&      m_table;
06:     size_t      m_seat;
07: 
08:     // threading utils
09:     std::future<void> m_lifeThread;
10:     bool              m_running;
11: 
12: public:
13:     // user-defined c'tor
14:     Philosopher(std::string_view name, Table& table, size_t seat);
15: 
16:     // public interface
17:     void start();
18:     void stop();
19:     void dine() const;
20:     void eating() const;
21:     void eatingDone() const;
22:     void thinking() const;
23:     void hungry() const;
24: };
```

*Listing* 4: Klasse `Philosopher` &ndash; Spezifikation.

Wir fahren gleich mit der Realisierung der Methoden der `Philosopher`-Klasse aus [Listing 4] fort:

###### {#listing_05_class_philosopher_impl}

```cpp
01: Philosopher::Philosopher(std::string_view name, Table& table, size_t seat) :
02:     m_name{ name },
03:     m_table{ table },
04:     m_seat{ seat },
05:     m_running{ false }
06: {}
07: 
08: void Philosopher::start()
09: {
10:     m_running = true;
11:     m_lifeThread = std::async(
12:         std::launch::async, [this]() { dine(); }
13:     );
14: }
15: 
16: void Philosopher::stop()
17: {
18:     m_running = false;
19:     m_lifeThread.get();
20: }
21: 
22: void Philosopher::dine() const
23: {
24:     std::thread::id philosopherThreadId{ std::this_thread::get_id() };
25:     Logger::logAbs(std::cout, m_name, " enters room [", philosopherThreadId, ']');
26: 
27:     while (m_running) {
28:         thinking();
29:         hungry();
30:         eating();
31:         eatingDone();
32:     }
33: 
34:     Logger::logAbs(std::cout, m_name, " leaves room");
35: }
36: 
37: void Philosopher::eating() const
38: {
39:     Fork& leftFork{ m_table[m_seat] };
40:     Fork& rightFork{ m_table[m_seat + 1] };
41: 
42:     {
43:         std::scoped_lock raii_lock{ leftFork.getMutex(), rightFork.getMutex() };
44: 
45:         // just for testing purposes
46:         m_table.incrementNumForks();
47: 
48:         Logger::log(
49:             std::cout, m_name, " started eating (at seat ", m_seat,
50:             ") [", m_table.numForks(), ']', " uses forks ", m_seat, " - ", (m_seat + 1) % 5
51:         );
52: 
53:         std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * 300));
54: 
55:         // just for testing purposes
56:         m_table.decrementNumForks();
57:     }
58: }
59: 
60: void Philosopher::eatingDone() const
61: {
62:     Logger::log(
63:         std::cout, m_name, " finished eating (at seat ", m_seat,
64:         ") ", "   released forks ", m_seat, " - ", (m_seat + 1) % 5
65:     );
66: }
67: 
68: void Philosopher::thinking() const
69: {
70:     Logger::log(std::cout, m_name, " is thinking (at seat ", m_seat, ')');
71:     std::this_thread::sleep_for(std::chrono::milliseconds(Random::getNext() * 100));
72: }
73: 
74: void Philosopher::hungry() const
75: {
76:     Logger::log(std::cout, m_name, " is hungry (at seat ", m_seat, ')');
77: }
```

*Listing* 5: Klasse `Philosopher` &ndash; Realisierung.

In Methode `start` ([Listing 5], Zeile 8) wird mit `std::async` der Lebenszyklus-Thread 
eines Philosophen erzeugt. Beendet wird der Thread durch Methode `stop`.
Diese Methode verändert eine `bool`-Variable `m_running`,
die den Philosophen veranlasst, den Speisetisch zu verlassen.
Softwaretechnisch gesehen ist ein Thread dann beendet, wenn seine Threadprozedur verlassen wurde.
Die Methoden `thinking` und `hungry` sind trivial in ihrer Realisierung,
einzig und allein das Aufnehmen der beiden Gabeln zur linken und rechten 
Seite eines Philosophen sollten wir näher betrachten, sprich die Methode `eating`:

Um sinnbildlich betrachtet zwei Gabeln aufnehmen zu können,
ordnen wir jeder Gabel ein `std::mutex`-Objekt zu (siehe [Listing 1]).
Das Aufnehmen einer Gabel bzw. das Warten auf die Verfügbarkeit der Gabel,
wenn diese gerade noch vom benachbarten Philosophen verwendet wird,
entspricht somit einem Aufruf der `lock`-Methode dieses `std::mutex`-Objekts.
Liegt die Gabel auf dem Tisch (ist also verfügbar), kehrt ein Aufruf der `lock`-Methode sofort zurück &ndash;
und versetzt folglich andere `lock`-Methodenaufrufe
benachbarter Philosophen in einen Wartezustand. Ist die Gabel nicht verfügbar, blockiert
der `lock`-Methodenaufruf solange, bis die Gabel von einem anderen Philosophen abgelegt wird.

Da wir zwei Gabeln zum Essen benötigen, müssten wir geschickt zwei `lock`-Methodenaufrufe am linken und rechten
`Fork`-Objekt kaskadieren. Es geht aber auch anders &ndash; mit einer Kombination des RAII-Idioms
und der Klasse `std::scoped_lock`.
Das RAII-Idiom bedeutet zunächst einmal (um es kurz zu formulieren),
dass die Verantwortung für die paarweisen Aufrufe
von `lock` und `unlock` in die Obhut einer Hüllenklasse übergeben wird.
Da der Einsatz eines Hüllenobjekts den Übergang von Funktionsaufrufen zu objektorientierter Programmierung bedeutet,
und damit insbesondere Konstruktoren und Destruktoren ins Spiel kommen,
lassen sich auf diese Weise `lock`- und `unlock`-Funktionsaufrufe deterministisch ausführen
(im Konstrukor bzw. Destruktor einer RAII-Hüllenklasse).
Da ein Destruktoraufruf unabhängig von unerwartet eintretenden
Ausnahmen oder anderen vorzeitigen Beendigungen von Kontrollstrukturen immer ausgeführt wird,
lässt sich auf diese Weise 
ein fehlerfreies Handling von `lock`- und korrespondierendem `unlock`-Funktionsaufruf erzielen.

Bleibt noch die Wahl der RAII-Hüllenklasse zu betrachten: Hierfür bietet sich die C++&ndash;Standardklasse `std::scoped_lock` an.
Sie besitzt inbesondere einen Konstruktor, der mehrere `std::mutex`-Objekte aufnehmen kann &ndash; 
und damit den `lock`-Aufruf an zwei (sogar mehreren) `std::mutex`-Objekten im Konstruktor durchführen kann:

```cpp
std::scoped_lock raii_lock{ leftFork.getMutex(), rightFork.getMutex() };
```

Wird diese Anweisung zur Laufzeit passiert, kann man sagen, dass der dazugehötige Philosoph im Besitz der linken und rechten Gabel ist.
Wird in Zeile 57 von [Listing 5] der geschachtelte Block verlassen, kommt es zum Destruktor-Aufruf des `std::scoped_lock`-Objekts.
Es werden entsprechende `unlock`-Funktionsaufrufe an den beteiligten `std::mutex`-Objekten abgesetzt.
In der Anschauung gesprochen kann man dann sagen,
dass der Philosoph gerade beide Gabeln wieder auf den Tisch zurückgelegt hat.

Der gesamte Lebenszyklus eines Philosophen (sprich die Threadprozedur) sieht damit so aus:

```cpp
while (m_running) {
    thinking();
    hungry();
    eating();
    eatingDone();
}
```

Damit haben wir die interessanten Quellcode-Abschnitte von [Listing 5] studiert.


## Multithreading-sicheres Logging (Klasse `Logger`)

In einer Multithreading-Anwendung kann für textuelle Ausgaben das `std::cout`-Objekt nicht ohne Weiteres verwendet werden.
`std::cout` ist ein globales Objekt, Methodenaufrufe an diesem Objekt im Kontext unterschiedlicher Threads führen
zwar nicht zu einem Absturz, die Ausgaben können aber &ldquo;zerstückelt&rdquo;
auf der Konsole auftreten, zum Beispiel dann, wenn der `<<`-Operator kaskadiert verwendet wird.

Möchte man auf den Gebrauch des `<<`-Operators am `std::cout`-Objekt nicht verzichten,
muss man die Argumente zunächst in einem einzigen, separaten Objekt (vorzugsweise vom Typ `std::string`) zusammenfassen
und dieses dann mit nur einem einzigen Aufruf des `<<`-Operators auf die Konsole schieben.
Das Zusammenfassen einer beliebigen Anzahl von Parametern (unterschiedlichen Typs) in ein einzelnes `std::string`-Objekt
findet in der `logInternal`-Methode der `Logger`-Klasse statt:

###### {#listing_06_class_logger_log_method}

```cpp
01: template<typename ...Args>
02: static void logInternal(std::ostream& os, Args&& ...args)
03: {
04:     std::stringstream ss;
05:     std::thread::id currentThreadId{ std::this_thread::get_id() };
06:     size_t tid{ readableTID(currentThreadId) };
07:     std::string prefix{ "[" + std::to_string(tid) + "]: " };
08:     ss << prefix;
09: 
10:     (ss << ... << std::forward<Args>(args)) << std::endl;
11:     os << ss.str();
12: }
```

*Listing* 6: Methode `logInternal` &ndash; Klasse `Logger`.


In [Listing 6] kommen zur Verarbeitung einer beliebigen Anzahl von Parametern unterschiedlichen Datentyps
*variadische Templates*, *Folding* und *Perfect Forwarding* zum Einsatz.
Diese C++&ndash;Instrumente sind in ihrem Verständnis nicht ganz einfach, wir stellen sie deshalb 
nur exemplarisch am Beispiel der `logInternal`-Methode aus [Listing 6] vor.

Sollten Sie beim konsekutiven Einsatz des Streaming-Operators `<<` in Zeile 10 von [Listing 6] überrascht sein,
dann beachten Sie bitte Folgendes: In Zeile 4 wird eine *lokale* Variable des Typs `std::stringstream` angelegt.
Lokale Variablen werden auf dem *Stack* abgelegt, sie sind damit *nicht* dem konkurrierenden Zugriff mehrerer Threads ausgesetzt,
da jedem Thread ein exklusives Stück des Stacks zugewiesen wird. 

Die Anweisungen in den Zeilen 4 bis 10 von [Listing 6] operieren folglich ausschließlich auf Daten,
die auf dem Stack abgelegt sind! Einzig und allein in Zeile 11 wird der `<<`-Operator auf ein
`std::ostream` angewendet, hinter dem sich ein globales Objekt, wie zum Beispiel `std::cout`, verbergen kann.
Ein einmaliger `<<`-Aufruf an einem `std::ostream`-Objekt aber ist multithreading-sicher!

In der `Logger`-Klasse finden sich noch einige andere Funktionalitäten vor &ndash;
zum Beispiel zwei Funktionen `startWatch` und `stopWatch` zum Messen der Ausführungszeit eines Programms. 
Ferner wird jedem Thread, der sich in C++ mit der Funktion `std::this_thread::get_id` identifizieren lässt,
eine leichter lesbare ganze Zahl (1, 2, ...) zugeordnet. So sind die Ausgaben der 
&ldquo;*Dining Philosophers*&rdquo;-Simulation besser lesbar.

Den gesamten Quellcode der Klasse `Logger` finden Sie in zum Abschluss dieser Betrachtungen in [Listing 7] vor:

###### {#listing_07_class_logger}

```cpp
01: class Logger {
02: public:
03:     static void enableLogging(bool enable)
04:     {
05:         s_loggingEnabled = enable;
06:     }
07: 
08:     static bool isLoggingEnabled()
09:     {
10:         return s_loggingEnabled;
11:     }
12: 
13:     template<typename ...Args>
14:     static void logInternal(std::ostream& os, Args&& ...args)
15:     {
16:         std::stringstream ss;
17:         std::thread::id currentThreadId{ std::this_thread::get_id() };
18:         size_t tid{ readableTID(currentThreadId) };
19:         std::string prefix{ "[" + std::to_string(tid) + "]: " };
20:         ss << prefix;
21: 
22:         (ss << ... << std::forward<Args>(args)) << std::endl;
23:         os << ss.str();
24:     }
25: 
26:     // log conditionally
27:     template<typename ...Args>
28:     static void log(std::ostream& os, Args&& ...args)
29:     {
30:         if (!s_loggingEnabled)
31:             return;
32: 
33:         logInternal(os, std::forward<Args>(args)...);
34:     }
35: 
36:     // log unconditionally
37:     template<typename ...Args>
38:     static void logAbs(std::ostream& os, Args&& ...args)
39:     {
40:         logInternal(os, std::forward<Args>(args)...);
41:     }
42: 
43:     static size_t readableTID(const std::thread::id id)
44:     {
45:         std::scoped_lock<std::mutex> raii{ s_mutexIds };
46:         if (s_mapIds.find(id) == s_mapIds.end()) {
47:             s_nextIndex++;
48:             s_mapIds[id] = s_nextIndex;
49:         }
50: 
51:         return s_mapIds[id];
52:     }
53: 
54:     static void startWatch() {
55:         s_begin = std::chrono::steady_clock::now();
56:     }
57: 
58:     static void stopWatchMilli() {
59:         std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
60:         auto duration{ std::chrono::duration_cast<std::chrono::milliseconds>(end - s_begin).count() };
61:         std::cout << "Elapsed time in milliseconds = " << duration << " [milliseconds]" << std::endl;
62:     }
63: 
64:     static void stopWatchMicro() {
65:         std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
66:         auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - s_begin).count() };
67:         std::cout << "Elapsed time in milliseconds = " << duration << " [microseconds]" << std::endl;
68:     }
69: 
70: private:
71:     static std::chrono::steady_clock::time_point s_begin;
72:     static bool s_loggingEnabled;
73:     static std::mutex s_mutexIds;
74:     static std::map<std::thread::id, std::size_t> s_mapIds;
75:     static std::size_t s_nextIndex;
76: };
```

*Listing* 7: Klasse `Logger`.


# There&lsquo;s more

Die vorgestellte Implementierung für das &rdquo;*Dining Philosophers*&rdquo;&ndash;Problem
wurde mit modernen C++&ndash;Features wie Threads und Mutex-Objekten durchgeführt.
Allerdings ist es bei dieser Realisierung dennoch möglich, dass die Philosophen verhungern,
wenn man die Wartezeiten in den einzelnen Lebenszyklus-Methoden entfernt.

Ein Algorithmus, der verhindert, dass die Philosophen verhungern, wurde von *K Mani Chandy* und *Jayadev Misra* vorgeschlagen.
Eine Beschreibung des Algorithmus als auch eine Umsetzung in Java finden sich
[hier](https://www.codeplanet.eu/tutorials/java/69-speisende-philosophen.html).
Erstellen Sie eine alternative Realisierung des &rdquo;*Dining Philosophers*&rdquo;&ndash;Problems 
nach den Ideen von *K Mani Chandy* und *Jayadev Misra*.
Benötigen Sie noch weitere Anregungen, finden Sie bei
[Marius Bancila](https://mariusbancila.ro/blog/2017/01/20/dining-philosophers-in-c11-chandy-misra-algorithm)
eine Hilfestellung!

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_graycodescalculator

[Listing 1]:    #listing_01_class_fork
[Listing 2]:    #listing_02_class_table_decl
[Listing 3]:    #listing_03_class_table_impl
[Listing 4]:    #listing_04_class_philosopher_decl
[Listing 5]:    #listing_05_class_philosopher_impl
[Listing 6]:    #listing_06_class_logger_log_method
[Listing 7]:    #listing_07_class_logger

[Abbildung 1]:  #abbildung_1_dining_philosophers

<!-- End-of-File -->
