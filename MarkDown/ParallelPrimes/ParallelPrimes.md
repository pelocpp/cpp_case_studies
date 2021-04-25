<!-- Parallele Berechnung von Primzahlen mit “Hindernissen” -->

Die Suche nach Primzahlen &ndash; also Zahlen, die nur durch sich selbst und durch 1 teilbar sind &ndash;  war lange Zeit
eine der zentralsten Bestandteile der Zahlentheorie. Primzahlenjäger können neben den zahlreichen Erkenntnissen
der Zahlentheoretiker heutzutage auf eine zusätzliche Hilfestellung zurückgreifen, den Computer.
Wir wollen im Folgenden ein Programm entwickeln, das mit Hilfe mehrerer Threads zu zwei fest gegebenen
natürlichen Zahlen *n* und *m* die Anzahl aller Primzahlen *p* mit *n* &leq; *p* &leq; *m* bestimmt.

Für die Koordination der Threads setzen wir &ldquo;Hindernisse&rdquo; ein, also C++&ndash;20 `std::latch`-Objekte.
Studieren Sie in dieser Anwendung, wie die Primzahlensuche mit mehreren Threads auf diese Weise koordinierbar ist.

<!--more-->

# Lernziele

  * `std::async` und `std::future<T>` in der Anwendung
  * Klasse `std::latch`
  * RAII Entwurfsmuster
  * Atomare Operationen (`std::atomic<T>`)
  * Gegenseitiger Ausschluss (`std::mutex`)
  * STL-Algorithmen `std::swap` und `std::merge`
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Für die Identifizierung einer natürlichen Zahl als Primzahl benutzen wir das einfachste (und zugegeben auch langweiligste) Verfahren,
die Zahl &ndash; nennen wir sie *n* &ndash; der Reihe nach solange durch alle natürlichen Zahlen 2, 3, ... zu dividieren,
bis entweder eine Division den Rest 0 zurückliefert (und damit ein Primfaktor gefunden wurde)
oder aber der Dividend den Wert *n* annimmt. In diesem Fall besitzt die Zahl keine Primfaktoren, wir haben eine Primzahl gefunden.
Natürlich genügt es, *n* nur durch all diejenigen Zahlen zu dividieren, die kleiner oder gleich als die Quadratwurzel von *n* sind.

Zur Bestimmung der Primzahleigenschaft implementieren Sie eine statische Methode `isPrime`:

```cpp
static bool isPrime(size_t number);
```

`isPrime` liefert `true` zurück, wenn der aktuelle Parameter `number` prim ist, andernfalls `false`:
Das zentrale Anliegen der Anwendung besteht in der Verteilung der Primzahlenberechnungen auf mehrere Threads (Sekundärthreads).
Jeder dieser Sekundärthreads entnimmt aus einem zentralen Datenobjekt den nächsten Kandidaten,
der auf seine Primzahleigenschaft hin zu untersuchen ist.
Das zentrale Datenobjekt stellt sicher, dass unter keinen Umständen zwei Sekundärthreads dieselbe Zahl auf ihre Primzahleigenschaft untersuchen!

Im primären Thread der Anwendung finden nur verwaltungstechnische Tätigkeiten statt. Es werden also keine Primzahlen berechnet. Zu den Aufgaben des Primärthreads zählen:

  * Verwaltung einer unteren und oberen Grenze *n* bzw. *m* aller zu untersuchenden Zahlen mit *n* &leq; *m*.
  * Verwaltung der Anzahl der Sekundärthreads, die Primzahlen suchen.
  * Anzeige der Anzahl der durch einen Sekundärthread gefundenen Primzahlen.
  * Anzeige der Anzahl aller gefundenen Primzahlen eines bestimmten Bereichs (Zusammenfassung).

Ein Architekturbild zur Realisierung mit den zuvor skizzierten Realisierungsgedanken finden Sie in [Abbildung 1] vor.
Auf der rechten Seite ist das zentrale Datenobjekt dargestellt (Klasse `PrimeNumberCalculator`).
Mittels öffentlicher Eigenschaften lassen sich die obere und untere Grenze zum Suchen nach Primzahlen setzen.
Die private Instanzvariable `m_next` kann nur intern im Objekt benutzt werden.

Auf der linken Seite erkennt man eine beliebige Anzahl von *n* Threads T<sub>1</sub>, ... T<sub>n</sub>, die jeder für sich mit Hilfe
der `calcPrimes`-Methode auf der Suche nach Primzahlen sind. In der Realisierung von `calcPrimes` muss sichergestellt sein,
dass zwei (quasi-)parallele Aufrufe von `calcPrimes` niemals dieselbe Zahl analysieren:

###### {#abbildung_1_application_overview}

{{< figure src="/img/parallelprimes/parallel_primes_architecture.svg" width="60%" >}}

*Abbildung* 1: Architektur einer parallelen Primzahlen-Anwendung.

Die Ausgabe der Anwendung könnte wie in [Abbildung 2] gezeigt aussehen.
Es sollten die IDs aller Threads ausgegeben werden, die sich an der Suche nach Primzahlen beteiligen &ndash;
und auch die Anzahl der gefundenen Primzahlen, die jeder Thread separat berechnet hat.
Die Summe aller Werte müsste dann die korrekte Anzahl aller Primzahlen in einem bestimmten Zahlenbereich widerspiegeln:

###### {#abbildung_2_parallelprimes_output_01}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="80%" >}}

*Abbildung* 2: Ausgabe der Ergebnisse in der Konsole.

Nach dem Start der Anwendung werden die Sekundärthreads erzeugt und gestartet.
Ist ein Sekundärthread mit der Berechnung der Primzahlen fertig, beendet er sich und zeigt die Anzahl der von ihm ermittelten Primzahlen
in der Konsole an. Sind alle Threads mit ihren Berechnungen fertig, wird in der letzten Zeile das Endergebnis,
also die Summe aller gefundenen Primzahlen, dargestellt.

In einer zweiten Variation der Anwendung werden die Primzahlen auch selbst ausgegeben, also nicht nur deren Anzahl.
Dies ist bei recht großen Zahlenbereichen etwas kritisch, da es dann sehr viele Primzahlen gibt.
In [Abbildung 3] finden Sie das Resultat aller Primzahlen im Bereich von 2 bis 1000 vor:

###### {#abbildung_3_parallelprimes_output_02}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="80%" >}}

*Abbildung* 3: Ausgabe der Ergebnisse mit allen berechneten Primzahlen.

# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wie in der Aufgabenstellung gefordert, soll es in der Anwendung ein zentrales Datenobjekt geben,
dessen Hauptaufgabe darin besteht, für rechenwillige Sekundärthreads den nächsten Kandidaten
zur Überprüfung der Primzahleigenschaft bereitzustellen. Am einfachsten ist es, diese Variable in einer Klasse,
nennen wir sie `PrimeNumberCalculator`, zu kapseln.
Mit einer Methode `calcPrimes` können wir den jeweils aktuellen Kandidaten überprüfen.
Gestalten wir die Methode `calcPrimes` zusätzlich thread-sicher, so lassen sich beliebig viele
Threads mit der `calcPrimes`-Methode als Threadprozedur starten.
Eine mögliche Spezifikation der `PrimeNumberCalculator`-Klasse entnehmen Sie [Tabelle 1]:

###### {#tabelle_1_class_primenumbercalculator}

| Element | Beschreibung |
| :---- | :---- |
| *getter* `minimum()` | `size_t minimum() const;`<br/>Liefert das Minimum des zu untersuchenden Zahlenbereichs zurück. |
| *getter* `maximum()` | `size_t maximum() const;`<br/>Liefert das Maximum des zu untersuchenden Zahlenbereichs zurück. |
| *getter* `threadCount()` | `size_t threadCount() const;`<br/>Liefert die Anzahl der Threads zurück, die den Zahlenbereich analysieren. |
| *setter* `minimum()` | `void minimum(size_t minimum);`<br/>Setzt das Minimum des zu untersuchenden Zahlenbereichs. |
| *setter* `maximum()` | `void maximum(size_t minimum);`<br/>Setzt das Maximum des zu untersuchenden Zahlenbereichs. |
| *setter* `threadCount()` | `void threadCount(size_t minimum);`<br/>Setzt die Anzahl der Threads, die den Zahlenbereich analysieren. || Methode `add()` | `void add(size_t elem);`<br/>Fügt ein Element in die Teilmenge ein. Diese Methode wird zum algorithmischen Erzeugen einer Teilmenge benötigt. |
| Methode `calcPrimes` | `void calcPrimes();`<br/>Berechnet die Anzahl der Primzahlen in dem durch `minimum()` und `maximum()` definierten Zahlenbereich mit `threadCount()` Threads. |

*Tabelle* 1: Wesentliche Elemente der Klasse `PrimeNumberCalculator`.

Neben den in [Tabelle 1] beschriebenen öffentlichen Elementen der Klasse `PrimeNumberCalculator` besitzt diese
eine private Instanzvariable `m_next`:

```cpp
constexpr size_t Minimum{ 2 };
...
std::atomic<size_t> m_next{ Minimum };
```

Die Instanzvariable `m_next` verwaltet eine natürliche Zahl im Bereich von `minimum()` bis einschließlich `maximum()`.
Sie beschreibt die Zahl, die als nächstes zur Analyse durch einen Sekundärthread ansteht.
Alle Zahlen von `minimum()`, `minimum()`+1, `minimum()`+2, ..., bis `m_next`-1
sind bereits auf ihre Primzahleigenschaft hin untersucht worden.
Die `m_next`-Variable ist privat definiert und kann nur durch die `calcPrimes`-Methode verändert (inkrementiert) werden.

Die `calcPrimes`-Methode ist die zentrale Methode der Klasse `PrimeNumberCalculator`.
Sie ist von allen Sekundärthreads als Threadprozedur zu benutzen, die sich auf die Suche nach Primzahlen machen.
Beachten Sie hierzu die Definition von `m_next`: Um ein thread-sicheres Inkrementieren zu garantieren,
wird diese Variable vom Typ `std::atomic<size_t>` definiert! Im Gegensatz zum `++`-Operator für Variablen des Typs `size_t`
erfolgen `++`-Aufrufe an `std::atomic<T>`-Objekten thread-sicher!

Wird die `calcPrimes`-Methode (quasi-)parallel von mehreren Threads ausgeführt,
kann es also sein, dass &ndash; im Kontext eines Threads &ndash; gleich mehrere Zahlen übersprungen werden,
wenn ein Wechsel zum nächsten Kandidaten ansteht. Die Zahlen dazwischen wurden in der Zwischenzeit
bereits von den parallel agierenden Sekundärthreads angefordert und untersucht.

In [Listing 1] (Schnittstelle) und [Listing 2] (Realisierung) finden Sie die Schnittstelle und Realisierung
der Klasse `PrimeNumberCalculator` vor:

###### {#listing_01_primenumbercalculator_decl}

```cpp
01: constexpr size_t Minimum{ 2 };
02: constexpr size_t Maximum{ 100 };
03: constexpr std::ptrdiff_t ThreadCount{ 2 };
04: 
05: class PrimeNumberCalculator
06: {
07: private:
08:     size_t m_minimum{ Minimum };
09:     size_t m_maximum{ Maximum };
10:     ptrdiff_t m_threadCount { ThreadCount };
11: 
12:     std::atomic<size_t> m_next{ Minimum };
13:     std::atomic<size_t> m_count{};
14: 
15:     std::vector<size_t> m_primes;
16:     std::mutex          m_mutex;
17: 
18: public:
19:     // c'tors
20:     PrimeNumberCalculator() = default;
21: 
22:     // getter / setter
23:     size_t minimum() const { return m_minimum; }
24:     size_t maximum() const { return m_maximum; }
25:     size_t threadCount() const { return m_threadCount; }
26:     void minimum(size_t minimum) { m_minimum = minimum; }
27:     void maximum(size_t maximum) { m_maximum = maximum; }
28:     void threadCount(size_t threadCount) { m_threadCount = threadCount; }
29: 
30:     // public interface
31:     void calcPrimes();
32:     void calcPrimesUsingThread();
33:     void calcPrimesEx();
34: 
35: private:
36:     void calcPrimesHelper();
37:     void calcPrimesHelperEx();
38:     void printResult(size_t);
39: 
40:     static bool isPrime(size_t number);
41:     static void printHeader();
42:     static void printFooter(size_t);
43: };
```

Nicht alle Instanzvariablen der Klasse `PrimeNumberCalculator` aus [Listing 1] wurden bislang angesprochen:
`m_count` (Zeile 13) und `m_primes` (Zeile 15) dienen dem Zweck, Resultate während der (quasi-)parallelen Berechnung
aufzunehmen. Deshalb ist `m_count` mit einem Hüllenobjekt `std::atomic<size_t>` definiert,
der Zugriff auf ein `std::vector<size_t>`-Objekt hingehen ist mit einem Mutex-Objekt zu schützen (`m_mutex`, Zeile 16).

Die Anzahl der Threads wird durch `m_threadCount` festgelegt. Der Typ dieser Variablen muss laut Definition des Konstruktors
der Klasse `std::latch` vorzeichenbehaftet sein, damit sind wir bei `ptrdiff_t` angekommen.

`std::latch`-Objekte treten nicht in den Instanzvariablen der Klasse `PrimeNumberCalculator` in Erscheinung.
Sie lassen sich nur einmal initialisieren und damit auch nicht wiederverwenden,
aus diesen Gründen sind sie als lokale Variablen in Methoden einfacher hantierbar,
siehe hierzu gleich Zeile 3 in [Listing 2]:

*Listing* 1: Klasse `PrimeNumberCalculator`: Definition.

###### {#listing_02_primenumbercalculator_impl}

```cpp
001: void PrimeNumberCalculator::calcPrimes()
002: {
003:     std::latch done{ m_threadCount };
004:     std::vector<std::future<void>> tasks(m_threadCount);
005:     m_next = m_minimum;
006:     m_count = 0;
007: 
008:     auto worker = [&]() {
009:         calcPrimesHelper();
010:         done.count_down();
011:     };
012: 
013:     for (size_t i{}; i != m_threadCount; ++i) {
014: 
015:         std::future<void> future{
016:             std::async(std::launch::async, worker)
017:         };
018: 
019:         tasks.push_back(std::move(future));
020:     }
021: 
022:     done.wait();
023:     printResult(m_count);
024: }
025: 
026: void PrimeNumberCalculator::calcPrimesUsingThread()
027: {
028:     std::latch done{ m_threadCount };
029:     m_next = m_minimum;
030:     m_count = 0;
031: 
032:     for (size_t i{}; i != m_threadCount; ++i) {
033: 
034:         std::thread t{
035:             [&]() {
036:                 calcPrimesHelper();
037:                 done.count_down();
038:             }
039:         };
040:         t.detach();
041:     }
042: 
043:     done.wait();
044:     printResult(m_count);
045: }
046: 
047: void PrimeNumberCalculator::calcPrimesEx()
048: {
049:     std::latch done{ m_threadCount };
050:     std::vector<std::future<void>> tasks(m_threadCount);
051:     m_next = m_minimum;
052:     m_count = 0;
053:     m_primes.clear();
054: 
055:     auto worker = [&]() {
056:         calcPrimesHelperEx();
057:         done.count_down();
058:     };
059: 
060:     for (size_t i{}; i != m_threadCount; ++i) {
061: 
062:         std::future<void> future{
063:             std::async(std::launch::async, worker)
064:         };
065: 
066:         tasks.push_back(std::move(future));
067:     }
068: 
069:     done.wait();
070:     printResult(m_primes.size());
071: }
072: 
073: void PrimeNumberCalculator::calcPrimesHelper()
074: {
075:     printHeader();
076: 
077:     size_t max{ m_maximum };  // upper prime number limit
078:     size_t next{ m_next++ };  // next prime number candidate
079:     size_t count{};           // thread-local counter - just for statistics
080: 
081:     while (next < max) {
082: 
083:         // test if candidate being prime 
084:         if (isPrime(next)) {
085:             ++m_count;  // atomic increment
086:             ++count;
087:         }
088: 
089:         // retrieve next prime number candidate
090:         next = m_next++;
091:     }
092: 
093:     printFooter(count);
094: }
095: 
096: void PrimeNumberCalculator::calcPrimesHelperEx()
097: {
098:     printHeader();
099: 
100:     size_t max{ m_maximum };  // upper prime number limit
101:     size_t next{ m_next++ };  // next prime number candidate
102:     std::vector<size_t> primes;  // thread-local prime numbers container
103: 
104:     while (next < max) {
105: 
106:         // test if candidate being prime 
107:         if (isPrime(next)) {
108:             primes.push_back(next);
109:         }
110: 
111:         // retrieve next prime number candidate
112:         next = m_next++;
113:     }
114: 
115:     if (primes.size() != 0) 
116:     {
117:         std::scoped_lock<std::mutex> lock{ m_mutex };
118: 
119:         std::vector<size_t> copy;
120: 
121:         std::swap(copy, m_primes);
122: 
123:         // no inplace algorithm
124:         std::merge(
125:             copy.begin(), 
126:             copy.end(),
127:             primes.begin(), 
128:             primes.end(), 
129:             std::back_inserter(m_primes)
130:         );
131:     }
132: 
133:     printFooter(primes.size());
134: }
135: 
136: bool PrimeNumberCalculator::isPrime(size_t number)
137: {
138:     // the smallest prime number is 2
139:     if (number <= 2) {
140:         return number == 2;
141:     }
142: 
143:     // even numbers other than 2 are not prime
144:     if (number % 2 == 0) {
145:         return false;
146:     }
147: 
148:     // check odd divisors from 3 to the square root of the number
149:     size_t end{ static_cast<size_t>(ceil(std::sqrt(number))) };
150:     for (size_t i{ 3 }; i <= end; i += 2) {
151:         if (number % i == 0) {
152:             return false;
153:         }
154:     }
155: 
156:     // found prime number
157:     return true;
158: }
159: 
160: void PrimeNumberCalculator::printResult(size_t count)
161: {
162:     std::cout 
163:         << "From " << m_minimum << " to " << m_maximum << ": found " 
164:         << count << " prime numbers." << std::endl;
165: 
166:     if (!m_primes.empty()) {
167:         for (int columns{}; size_t prime : m_primes) {
168:             std::cout << std::setw(5) << std::right << prime << " ";
169:             if (++columns % 16 == 0) {
170:                 std::cout << std::endl;
171:             }
172:         };
173:     }
174:     std::cout << std::endl;
175: }
176: 
177: void PrimeNumberCalculator::printHeader()
178: {
179:     std::stringstream ss;
180:     std::thread::id currentTID{ std::this_thread::get_id() };
181:     ss << "[" << std::setw(5) << std::right << currentTID << "]: starting ..." << std::endl;
182:     std::cout << ss.str();
183:     ss.str("");
184: }
185: 
186: void PrimeNumberCalculator::printFooter(size_t count)
187: {
188:     std::stringstream ss;
189:     std::thread::id currentTID{ std::this_thread::get_id() };
190:     ss << "[" << std::setw(5) << std::right << currentTID << "]: found " << count << '.' << std::endl;
191:     std::cout << ss.str();
192: }
```

*Listing* 2: Klasse `PrimeNumberCalculator`: Implementierung.

Einige Anmerkungen:

  * In der `calcPrimes`-Methode ab Zeile 1 ([Listing 2]) sind nun alle Tätigkeiten für das parallele Suchen nach Primzahlen zusammengefasst.
    In den Zeilen 13 bis 20 werden mit `std::async` eine Reihe von Threads gestartet, die sich auf die Suche nach Primzahlen begeben.
    Wichtig ist Zeile 3: Hier kommt ein C++&ndash;20 Objekt des Typs `std::latch` zum Einsatz.
    Frei übersetzt könnte man `std::latch` als *Hindernis* bezeichnen:
    Mit dem Aufruf der `wait`-Methode an diesem Objekt stößt man auf ein Hindernis, man muss also warten.
    Wie kann diese Blockade aufgelöst werden? Mit `count_down`-Aufrufen, die Sie in Zeile 10 vorfinden,
    also am Ende eines `calcPrimesHelper`-Methodenaufrufs und damit nach einer abgeschlossenen Primzahlensuche &ndash; im Kontext eines Threads.
    Damit sind wir schon bei den Details angelangt: Wie oft muss die Methode `count_down` aufgerufen werden,
    um eine `wait`-Blockade aufzulösen. Vermutlich genauso oft, wie eine entsprechende Zählervariable
    bei der Initialisierung des korrespondierenden `std::latch`-Objekts vorbelegt wird:

```cpp
    std::latch done{ m_threadCount };
```

  * In Zeile 19 wird der Rückgabewert von `std::async`, ein `std::future<void>`-Objekt, in einem `std::vector<std::future<void>>`-Objekt 
    abgelegt. Man könnte dieses `std::future<void>`-Objekt verwenden, um mit seiner Hilfe (Methode `get`) Resultate vom Thread aus dem Thread
    zum Erzeuger des Threads zu transportieren. In dieser Fallstudie habe ich aber einen anderen Weg gewählt,
    die Threads legen ihre Resultate in thread-globalen Variablen ab, die via `std::atomic<T>`&ndash;Hüllen thread-sicher arbeiten.
    Wozu ist es dann überhaupt erforderlich, den Rückgabewert von `std::async` wegzuspeichern?
    Man könnte den Rückgabewert doch einfach ignorieren? Weit gefehlt, dem ist nicht so!
    Jedes `std::future<void>`-Objekt besitzt einen Destruktor, der auf das Ende des beteiligten Threads wartet!
    Ignoriert man dieses Objekt im Programm, so ist es zur Laufzeit dennoch präsent &ndash; in diesem Fall als
    anonymes temporäres Objekt. Dies wiederum bedeutet, dass am Ende des Blocks (Zeile 20) der Destruktor dieses Objekts aufgerufen wird.
    Die mittels `std::async` erzeugten Threads würden auf diese Weise alle sequentiell ausgeführt werden!
    
    Natürlich kann man trotzdem einen Ansatz wählen, der ohne `std::future<void>`-Objekte auskommt.
    In diesem Fall muss man aber auch die `std::async`-Funktion umgehen,
    eine Vorgehensweise mit `std::thread`-Objekten wäre dann das Mittel der Wahl. 
    Siehe hierzu die Methode `calcPrimesUsingThread` in den Zeilen 26 bis 45 von [Listing 2].

  * Nun gehen wir näher auf Methode `calcPrimesHelperEx` (Zeilen 96 bis 134) ein.
    Sie wird im Kontext eines Threads ausgeführt und sucht Primzahlen. Gefundene Primzahlen legt sie in einem 
    `std::vector<size_t>`-Objekt ab, dass lokal in der `calcPrimesHelperEx`-Methode definiert ist, damit auf dem Laufzeitstack
    eines Threads liegt und *nicht* vor dem konkurrierenden Zugriff anderer Threads zu schützen ist.
    
    Bleibt noch die Frage zu beantworten, wie nach dem Ende der Berechnungen etwaige Ergebnisse vom Sekundärthread
    zum Erzeugerthread gelangen? Jetzt wird es geringfügig komplizierter:
    Im Instanzvariablenbereich der Klasse `PrimeNumberCalculator` liegt ein weiteres `std::vector<size_t>`-Objekt,
    dass alle Ergebnisse nach dem Rechnen enthalten soll. Dieses Objekt ist natürlich dem konkurrierenden Zugriff anderer Threads ausgesetzt,
    deshalb kommt vor dem Zugriff ein `std::mutex`-Objekt ins Spiel.
    
    Ganz RAII-*like* legen wir ein `std::scoped_lock<std::mutex>`-Objekt in einem Block an,
    damit kümmert sich der Destruktor dieses Objekts um die Freigabe des `std::mutex`-Objekts nach erfolgtem Zugriff auf 
    das globale Resultatobjekt.
    
    Das Umkopieren der thread-lokalen Ergebnisse in das globale Objekt ist trickreich:
    Ich möchte den `std::merge`-Algorithmus einsetzen.
    Dieser arbeitet aber leider nicht *in-place*, das bedeutet, vor dem Zusammenführen der schon vorhandenen Ergebnisse
    (globales `std::vector<size_t>`-Objekt) mit den neuen Ergebnissen (lokales `std::vector<size_t>`-Objekt) benötige ich eine Kopie der schon vorhandenen Ergebnisse (globales `std::vector<size_t>`-Objekt):
    Das Kopieren eines `std::vector<size_t>`-Objekts ist eine zeitintensive Operation, die ich auf jeden Fall vermeiden möchte.
    Studieren Sie deshalb das folgende Code-Fragment:

```cpp
std::vector<size_t> copy;

std::swap(copy, m_primes);

std::merge(
    copy.begin(), 
    copy.end(),
    primes.begin(), 
    primes.end(), 
    std::back_inserter(m_primes)
);
```

Mit der `std::swap`-Funktion vertausche ich den Inhalt zweier Objekt auf Basis der *Verschiebesemantik*.
Ich vermeide es folglich, auf diese Weise das schon vorhandene Resultatobjekt (`m_primes`) zu kopieren!
Nun kann der `std::merge`-Algorithmus auf den schon vorhandenen Ergebnissen (`copy`) und den neuen Ergebnissen (`primes`)
eine neues, vermengtes Resultatobjekt (`m_primes`) erstellen &ndash; und dies alles ohne unnötige Kopieraktivitäten!

Und noch ein Hinweis: Wenn Sie die Beschreibung des `std::merge`-Algorithmus genau gelesen haben, werden Sie festgestellt haben,
dass die zu vermengenden Vektoren aufsteigend sortiert sein müssen. Vom schon vorhandene Resultatobjekt kann man
dies vielleicht voraussetzen, aber wie sieht es mit dem lokalen `std::vector<size_t>`-Objekt `primes` aus?
Dieses wird sukzessive mit `push_back`-Methodenaufrufen konstruiert,
die sich aus der Traversierung eines Zahlenbereichs in aufsteigender Sortierung ergeben:
Der lokale Resultatvektor liegt also auf Grund seiner Konstruktion automatisch sortiert vor.

Nun können wir ein `PrimeNumberCalculator`-Objekt bei der Arbeit betrachten:

```cpp
PrimeNumberCalculator calculator;
calculator.minimum(2);
calculator.maximum(100);
calculator.threadCount(2);
calculator.calcPrimes();

calculator.minimum(2);
calculator.maximum(1'000);
calculator.threadCount(4);
calculator.calcPrimes();

calculator.minimum(2);
calculator.maximum(1'000'000);
calculator.threadCount(12);
calculator.calcPrimes();
```

*Ausgabe*:

```
[ 2696]: starting ...
[16832]: starting ...
[ 2696]: found 25.
[16832]: found 0.
From 2 to 100: found 25 prime numbers.

[16832]: starting ...
[ 2696]: starting ...
[ 2696]: found 61.
[16832]: found 107.
[ 2696]: starting ...
[10464]: starting ...
[ 2696]: found 0.
[10464]: found 0.
From 2 to 1000: found 168 prime numbers.

[10464]: starting ...
[ 2696]: starting ...
[19792]: starting ...
[16832]: starting ...
[ 6152]: starting ...
[16536]: starting ...
[ 7268]: starting ...
[11896]: starting ...
[19636]: starting ...
[16632]: starting ...
[16060]: starting ...
[16424]: starting ...
[16632]: found 6261.
[ 2696]: found 6490.
[16832]: found 7168.
[16060]: found 6125.
[11896]: found 6655.
[10464]: found 6539.
[ 6152]: found 6303.
[19636]: found 6127.
[16424]: found 6097.
[19792]: found 7302.
[16536]: found 7173.
[ 7268]: found 6258.
From 2 to 1000000: found 78498 prime numbers.
```

Die Zahlen in den eckigen Klammern sind Thread-IDs der jeweiligen Threads, die für die Ausgabe verantwortlich sind.
Wenn wir die Primzahlen selbst berechnen wollen, sollten wir die Wertebereiche etwas kleiner wählen:

```cpp
PrimeNumberCalculator calculator;
calculator.minimum(2);
calculator.maximum(100);
calculator.threadCount(4);
calculator.calcPrimesEx();

calculator.minimum(2);
calculator.maximum(1'000);
calculator.threadCount(4);
calculator.calcPrimesEx();
```

*Ausgabe*:

```
[16108]: starting ...
[17440]: starting ...
[16108]: found 25.
[17440]: found 0.
[16108]: starting ...
[20044]: starting ...
[16108]: found 0.
[20044]: found 0.
From 2 to 100: found 25 prime numbers.
    2     3     5     7    11    13    17    19    23    29    31    37    41    43    47    53
   59    61    67    71    73    79    83    89    97

[20044]: starting ...
[16108]: starting ...
[ 6388]: starting ...
[17440]: starting ...
[16108]: found 58.
[17440]: found 0.
[20044]: found 85.
[ 6388]: found 25.

From 2 to 1000: found 168 prime numbers.
    2     3     5     7    11    13    17    19    23    29    31    37    41    43    47    53
   59    61    67    71    73    79    83    89    97   101   103   107   109   113   127   131
  137   139   149   151   157   163   167   173   179   181   191   193   197   199   211   223
  227   229   233   239   241   251   257   263   269   271   277   281   283   293   307   311
  313   317   331   337   347   349   353   359   367   373   379   383   389   397   401   409
  419   421   431   433   439   443   449   457   461   463   467   479   487   491   499   503
  509   521   523   541   547   557   563   569   571   577   587   593   599   601   607   613
  617   619   631   641   643   647   653   659   661   673   677   683   691   701   709   719
  727   733   739   743   751   757   761   769   773   787   797   809   811   821   823   827
  829   839   853   857   859   863   877   881   883   887   907   911   919   929   937   941
  947   953   967   971   977   983   991   997
```

# There&lsquo;s much more

Ich habe es dieses Mal unterlassen, die Zeiten zu messen, die mein Programm bei der Primzahlensuche benötigt.
Dies hatte auch einen guten Grund, den der von mir verwendete klassische Primzahlentest kommt bei größeren Zahlen
doch ganz gehörig ins Schleudern.
Abhilfe kann hier ein Verfahren schaffen, das von drei indischen Wissenschaftlern
*Manindra Agrawal*, *Neeraj Kayal* und *Nitin Saxena* vom *Indian Institute of Technology* in Kanpur entdeckt wurde:

> Der **AKS**-Primzahltest (auch bekannt unter dem Namen **Agrawal-Kayal-Saxena-Primzahltest**) ist ein deterministischer Algorithmus,
> der für eine natürliche Zahl in polynomieller Laufzeit feststellt, ob sie prim ist oder nicht.

In &ldquo;[AKS-Primzahltest](https://www.biancahoegel.de/mathe/verfahr/aks-primzahltest.html)&rdquo;
finden Sie für diesen Algorithmus eine Notation in Pseudo-Code vor.
Wer jetzt seitenweise komplizierte Ausdrücke oder mathematische Formeln vermutet,
wird überrascht sein, wie einfach der Algorithmus aufgebaut ist.
In gerade mal 13 Zeilen präsentiert sich das Werk der Informatiker.

Zwar basiert der Algorithmus, wie andere moderne Suchalgorithmen für Primzahlen auch, auf einer Variation eines *Fermat*-Tests,
doch reduziert er zunächst einmal durch eine trickreiche Kombination vorangehender Proben
die Zahl der Test-Durchläufe auf ein erträgliches Maß.

Wenn Sie eine C++-Implementierung erstellt haben, lassen Sie mich es doch wissen:
Ich freue mich über jede Zusendung. Und gleich noch eine Starthilfe vorweg:
Möglicherweise, oder eigentlich ganz sicher, werden die zu untersuchenden Primzahlen
nicht mehr durch `size_t`-Variablen darstellbar sein.
Sehr große natürliche Zahlen, so wie sie durch `BigInteger`-Objekte aus der Fallstudie
[Exakte Arithmetik ganzer Zahlen]({{< ref "/post/2021-04-10-biginteger" >}})
dargestellt werden, könnten Unterstützung leisten :)

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_partialset

[Listing 1]: #listing_01_primenumbercalculator_decl
[Listing 2]: #listing_02_primenumbercalculator_impl

[Abbildung 1]:  #abbildung_1_application_overview
[Abbildung 2]:  #abbildung_2_parallelprimes_output_01
[Abbildung 3]:  #abbildung_3_parallelprimes_output_02

<!-- End-of-File -->
