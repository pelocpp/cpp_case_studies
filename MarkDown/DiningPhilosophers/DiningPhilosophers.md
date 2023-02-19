<!-- Dinierende Philosophen -->

Das Beispiel der dinierenden Philosophen ist eines der populärsten Standardprobleme
aus dem Bereich der Parallelprogrammierung.
Es erlaubt, die Kooperation der beteiligten Threads
in einer lebendigen Simulation darzustellen.

<!--more-->

# Lernziele

  * `std::mutex`
  * `std::scoped_lock` und RAII-Idiom
  * `std::this_thread::get_id` und `std::this_thread::sleep_for`
  * `std::future` und `std::async`
  * `std::atomic`, `fetch_add` und `fetch_sub`
  * STL-Containerklasse `std::array`
  * Berechnung von Zufallszahlen (`std::random_device`, `std::mt19937` und `std::uniform_int_distribution`)
  * Multithreading-sicheres Logging (Klasse `Logger`)

# Einführung

Das Problem ist das Folgende: In einem Kloster gibt es fünf Mönche, die sich der Philosophie widmen.
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

<img src="DiningPhilosophers.png" width="320">

*Abbildung* 1: Die dinierenden Philosophen.

Eine Lösung dieses Problems gestattet es, dass jederzeit so viele Philosophen wie möglich essen können
und dass keiner der Philosophen verhungert. Man kann sich leicht überlegen, 
dass stets maximal zwei Philosophen gleichzeitig essen können und dass eine Gabel immer ungenutzt bleibt.

---

In dieser Fallstudie wollen wir das Problem der dinierenden Philosophen in einer C++&ndash;Konsolen-Anwendung umsetzen.
Im Mittelpunkt steht die Auseinandersetzung mit den Hilfsmittels des Multithreadings.
Wie schon erwähnt geht es darum, dass der Zugriff auf eine Gabel durch die beiden benachbarten Philosophen
korrekt erfolgt. Zwei Philosophen dürfen diesselbe Gabel nicht zu einem Zeitpunkt gleichzeitig aufnehmen, und:
Ist ein Philosoph im Besitz einer Gabel, so legt er diese nach einer bestimmten Essenzeit wieder auf den Tisch zurück,
so kann folglich vom benachbarten Philosophen aufgenommen werden.


In einer semi-grafischen Ausgabe können wir das Problem zum Beispiel auf diese Weise visualisieren:

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

Die Nummer in den eckigen Klammern zu Beginn einer jeden Zeile stehen für eine Thread-Id. 












# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wir beginnen mit einigen Vorüberlegungen, wie sich der konkurrierende Zugriff
zweier Philosophen auf ein Gabel-Objekt korrekt gestalten lässt.


Der konfliktfreie Zugriff auf eine Gabel kann software-technisch mit einem `std::mutex`-Objekt gelöst werden.
Jede Gabel besitzt aus diesem Grund ein solches `std::mutex`-Objekt.

Eine Klasse `Fork` besitzt aus diesem Grund ein `std::mutex`-Objekt.
Weitere Funktionalitäten sind für ein Gabelobjekt nicht notwendig ([Listing 1]):


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

Gemäß der Problemstellung liegen fünf Gabelobjekte auf einem Tisch.
Wir modellieren deshalb eine Klasse `Table` mit fünf `Fork`-Objekten,
die wir in einem `std::array`-Objekt ablegen.

Da zu bestimmten Zeitpunkten auf ein Gabelobjekt zugegriffen wird, kapseln wir den ZUgriff
mit einer Überladung des `operator[]`-Operators.

Die Sicherstellung, dass zu einem bestimmten Zeitpunkt nur eine Gabel aufgegriffen werden kann,
wird durch Philosophen ausgeführt. Direkter formuliert: Der Tisch stellt Gabeln mit ` std::mutex`-Objekten zur Verfügung,
der Aufruf der Methoden `lock` und `unlock` erfolgt durch die Initiative eines Philosophen. 

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

*Listing* 2: Klasse `Table` &ndash; Deklaration.

Das Salz in der Suppe dieser Fallstudie ist natürlich die Beobachtung des Umstands, dass zu jedem Zeitpunkt
niemals 5 fünf Gabeln zum Essen verwendet werden. Da ein essender Philosoph immer 2 Gabeln zum Essen benötigt,
müssen immer 5, 3 oder zumindest eine freie Gabel auf dem Tisch liegen. Sollten alle 5 Gabeln in Gebrauch sein,
haben wir einen Fehler in der Simulation.

Um die Anzahl der in Gebrauch befindlichen Gabeln besser &ndash; und vor allem auch korrekt &ndash; beobachten zu können,
haben wir das Tischobjekt um eine `int`-Variable `m_numForksInUse` ergänzt.

Da &ndash; wir kommen darauf noch zu sprechen &ndash; die Aktivitäten eines Philosophen im Kontext eines Threads
stattfinden, muss der schreibende und lesende Zugriff auf diese `m_numForksInUse`-Variable *thread-sicher* sein.
Damit sind wir beim Klassen-Template `std::atomic<T>` angekommen, siehe Zeile 5 von [Listing 2].

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
Aus diesem Grund ist `m_numForksInUse` immer um den Wert 2 zu inkrementieren oder dekrementieren.

Damit sind wir beim zentralen Punkt in der Anwendung angekommen, der Realisierung eines Philosophen:


WEITER WEITER WEITER WEITER 
WEITER WEITER 
WEITER WEITER 
WEITER WEITER 
WEITER WEITER 



## Klasse `XXX`


# There&lsquo;s more

Gray-Codes lassen sich sowohl mit einem rekursiven als auch mit einem iterativen Algorithmus berechnen.
Versuchen Sie, an Hand der Beschreibung des Algorithmus in [Abbildung 2] eine iterative Realisierung in C++ umzusetzen.
Die folgende [Anregung](https://www.geeksforgeeks.org/generate-n-bit-gray-codes/) könnte hierbei behilflich sein.


<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_graycodescalculator

[Listing 1]: #listing_01_class_fork
[Listing 2]: #listing_02_class_table_decl
[Listing 3]: #listing_03_class_table_impl



[Abbildung 1]:  #abbildung_1_gray_codes_four_bits
[Abbildung 2]:  #abbildung_2_gray_codes_construction

<!-- End-of-File -->

