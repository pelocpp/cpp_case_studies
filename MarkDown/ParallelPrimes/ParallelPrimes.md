<!-- ParallelPrimes.md -->

<!-- Parallele Berechnung von Primzahlen mit Hindernissen -->

Die Suche nach Primzahlen &ndash; also Zahlen, die nur durch sich selbst und durch 1 teilbar sind &ndash;  war lange Zeit
eine der zentralsten Bestandteile der Zahlentheorie. Primzahlenjäger können neben den zahlreichen Erkenntnissen
der Zahlentheoretiker heutzutage auf eine zusätzliche Hilfestellung zurückgreifen, den Computer.
Wir wollen im Folgenden ein Programm entwickeln, das mit Hilfe mehrerer Threads zu zwei fest gegebenen
natürlichen Zahlen *n* und *m* die Anzahl aller Primzahlen *p* mit *n* &leq; *p* &leq; *m* bestimmt.

<!--more-->

# Lernziele

  * `std::async` und `std::future<T>` in der Anwendung
  * Klasse `std::latch`
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

{{< figure src="/img/parallelprimes/MultiThreadingPrimeCalculatorArchitecture.png" width="60%" >}}

*Abbildung* 1: Architektur einer parallelen Primzahlen-Anwendung.

Die Ausgabe der Anwendung könnte wie in [Abbildung 2] gezeigt aussehen.
Es sollten die IDs aller Threads ausgegeben werden, die sich an der Suche nach Primzahlen beteiligen &ndash;
und auch die Anzahl der gefundenen Primzahlen, die jeder Thread separat berechnet hat.
Die Summe aller Werte müsste dann die korrekte Anzahl aller Primzahlen in einem bestimmten Zahlenbereich widerspiegeln:

###### {#abbildung_2_parallelprimes_output_01}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="60%" >}}

*Abbildung* 2: Ausgabe der Ergebnisse in der Konsole.

Nach dem Start der Anwendung werden die Sekundärthreads erzeugt und gestartet.
Ist ein Sekundärthread mit der Berechnung der Primzahlen fertig, beendet er sich und zeigt die Anzahl der von ihm ermittelten Primzahlen
in der Konsole an. Sind alle Threads mit ihren Berechnungen fertig, wird in der letzten Zeile das Endergebnis,
also die Summe aller gefundenen Primzahlen, dargestellt.

In einer zweiten Variation der Anwendung werden die Primzahlen auch selbst ausgegeben, also nicht nur deren Anzahl.
Dies ist bei recht großen Zahlenbereichen etwas kritisch, da es dann sehr viele Primzahlen gibt.
In [Abbildung 3] finden Sie das Resultat aller Primzahlen im Bereich von 2 bis 1000 vor:

###### {#abbildung_3_parallelprimes_output_02}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="60%" >}}

*Abbildung* 3: Ausgabe der Ergebnisse mit allen berechneten Primzahlen.


// =====================================================================================


TODO: Beschreiben warum die Futures notwending sind !!!!!!!!!

// =====================================================================================


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

Die Instanzvariable `m_next` verwaltet eine natürliche Zahl im Bereich von `minimum()` bis `maximum()`.
Sie beschreibt die Zahl, die als nächstes zur Analyse durch einen Sekundärthread ansteht.
Alle Zahlen von `minimum()`, `minimum()`+1, `minimum()`+2, ..., bis `m_next`-1
sind bereits auf ihre Primzahleigenschaft hin untersucht worden.
Die `m_next`-Variable ist privat definiert und kann nur durch die `calcPrimes`-Methode verändert (inkrementiert) werden.

Die `calcPrimes`-Methode ist die zentrale Methode der Klasse `PrimeNumberCalculator`.
Sie ist von allen Sekundärthreads als Threadprozedur zu benutzen, die sich auf die Suche nach Primzahlen machen.

Es werden prinzipiell alle Zahlen im Bereich von `minimum()` bis `maximum()` untersucht.
Der Übergang von einer Zahl zur nächsten erfolgt (thread-sicher!) an Hand der privaten Instanzvariablen `m_next`.
Beachten Sie hierzu die Definition von `m_next`: Um ein thread-sicheres Inkrmentieren zu garantieren,
wird diese Variable vom Typ `std::atomic<size_t>` definiert! Im Gegensatz zum `++`-Operator für Variablen des Typs `size_t`
erfolgen `++`-Aufrufe an `std::atomic<T>`-Objekten thread-sicher.

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
10:     std::ptrdiff_t m_threadCount { ThreadCount };
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
073: // =====================================================================================
074: // helpers
075: 
076: void PrimeNumberCalculator::calcPrimesHelper()
077: {
078:     printHeader();
079: 
080:     size_t max{ m_maximum };  // upper prime number limit
081:     size_t next{ m_next++ };  // next prime number candidate
082:     size_t count{};           // thread-local counter - just for statistics
083: 
084:     while (next < max) {
085: 
086:         // test if candidate being prime 
087:         if (isPrime(next)) {
088:             ++m_count;  // atomic increment
089:             ++count;
090:         }
091: 
092:         // retrieve next prime number candidate
093:         next = m_next++;
094:     }
095: 
096:     printFooter(count);
097: }
098: 
099: void PrimeNumberCalculator::calcPrimesHelperEx()
100: {
101:     printHeader();
102: 
103:     size_t max{ m_maximum };  // upper prime number limit
104:     size_t next{ m_next++ };  // next prime number candidate
105:     std::vector<size_t> primes;  // thread-local prime numbers container
106: 
107:     while (next < max) {
108: 
109:         // test if candidate being prime 
110:         if (isPrime(next)) {
111:             primes.push_back(next);
112:         }
113: 
114:         // retrieve next prime number candidate
115:         next = m_next++;
116:     }
117: 
118:     if (primes.size() != 0) 
119:     {
120:         std::scoped_lock<std::mutex> lock{ m_mutex };
121: 
122:         std::vector<size_t> copy;
123: 
124:         std::swap(copy, m_primes);
125: 
126:         // no inplace algorithm
127:         std::merge(
128:             copy.begin(), 
129:             copy.end(),
130:             primes.begin(), 
131:             primes.end(), 
132:             std::back_inserter(m_primes)
133:         );
134:     }
135: 
136:     printFooter(primes.size());
137: }
138: 
139: bool PrimeNumberCalculator::isPrime(size_t number)
140: {
141:     // the smallest prime number is 2
142:     if (number <= 2) {
143:         return number == 2;
144:     }
145: 
146:     // even numbers other than 2 are not prime
147:     if (number % 2 == 0) {
148:         return false;
149:     }
150: 
151:     // check odd divisors from 3 to the square root of the number
152:     size_t end{ static_cast<size_t>(ceil(std::sqrt(number))) };
153:     for (size_t i{ 3 }; i <= end; i += 2) {
154:         if (number % i == 0) {
155:             return false;
156:         }
157:     }
158: 
159:     // found prime number
160:     return true;
161: }
162: 
163: void PrimeNumberCalculator::printResult(size_t count)
164: {
165:     std::cout 
166:         << "From " << m_minimum << " to " << m_maximum << ": found " 
167:         << count << " prime numbers." << std::endl;
168: 
169:     if (!m_primes.empty()) {
170:         for (int columns{}; size_t prime : m_primes) {
171:             std::cout << std::setw(5) << std::right << prime << " ";
172:             if (++columns % 16 == 0) {
173:                 std::cout << std::endl;
174:             }
175:         };
176:     }
177:     std::cout << std::endl;
178: }
179: 
180: void PrimeNumberCalculator::printHeader()
181: {
182:     std::stringstream ss;
183:     std::thread::id currentTID{ std::this_thread::get_id() };
184:     ss << "[" << std::setw(5) << std::right << currentTID << "]: starting ..." << std::endl;
185:     std::cout << ss.str();
186:     ss.str("");
187: }
188: 
189: void PrimeNumberCalculator::printFooter(size_t count)
190: {
191:     std::stringstream ss;
192:     std::thread::id currentTID{ std::this_thread::get_id() };
193:     ss << "[" << std::setw(5) << std::right << currentTID << "]: found " << count << '.' << std::endl;
194:     std::cout << ss.str();
195: }
```

*Listing* 2: Klasse `PrimeNumberCalculator`: Implementierung.

> Einige Anmerkungen:

In der `calcPrimes`-Methode ab Zeile 1 sind nun alle Tätigkeiten für das parallele Suchen nach Primzahlen zusammengefasst.

In den Zeilen 13 bis 20 werden mit std::async eine Reihe von Threads gestartet,
die sich auf die Suche nach Primzahlen begeben.

Wichtig ist Zeile 3: Hier kommt ein C++&ndash;20 Objekt des Typs std::latch zum Einsatz.

Frei übersetzt könnte man std::latch als Hindernis bezeichnen:
Mit dem Aufruf der wait-Methode an diesem Objekt stößt man auf ein Hindernis, man muss also warten.
Wie kann diese Blockade aufgelöst werden? Mit count_down-Aufrufen, die Sie in Zeile 10 vorfinden,
also am Ende eines calcPrimesHelper-Methodenaufrufs und damit nach einer abgeschlossenen Primzahlensuche &ndash; im Kontext eines Threads.
Damit sind wir schon bei den Details angelangt: Wie oft muss  count_down aufgerufen werden, um eine wait-Blockade aufzulösen.
Vermutlich genauso oft, wie eine entsprechende Zählervariable bei der Initialisierung des std::latch-Objekts vorbelegt wird:

```cpp
std::latch done{ m_threadCount };
```







<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_partialset

[Listing 1]: #listing_01_primenumbercalculator_decl
[Listing 2]: #listing_02_primenumbercalculator_impl

[Abbildung 1]:  #abbildung_1_application_overview
[Abbildung 2]:  #abbildung_2_parallelprimes_output_01
[Abbildung 3]:  #abbildung_3_parallelprimes_output_02

<!-- End-of-File -->
