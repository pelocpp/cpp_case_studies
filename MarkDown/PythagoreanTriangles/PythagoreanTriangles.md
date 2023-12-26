<!-- Pythagorean Triangles -->

# Rechtwinklige Dreiecke und `parallel_for`

// TODO: Geht das was mit genrate .... oder siehe auch das Collatz - Pronlem ....

// TODO: Das Triple machen wir doch mit einem std::tuple

// TODO : Ab 23 gibt es eine thread sichere Ausgabe !!!

Und wieder steht etwas Schulmathematik auf dem Programm, dieses Mal geht es um &bdquo;rechtwinklige Dreiecke&rdquo;.
Für derartige Rechtecke gibt es den Satz des Pythagoras,
er fällt eine Aussage für die Seitenlängen eines solchen Dreiecks.
Wir wollen im Folgenden nur solche Rechtecke betrachten, deren Seitenlängen ganzzahlig sind.

Schreiben Sie ein C++&ndash;Programm, das für folgende Fragestellung eine Antwort findet:
Für welchen Umfang *p* mit *p* <= 2000 ist die Anzahl der verschiedenen rechwinkligen Dreiecke
mit ganzzahligen Seitenlängen *a*, *b* und *c* am größten?

Hinweis: Die Aufgabenstellung stammt aus dem Repository &bdquo;Project Euler&rdquo;:
[*Project Euler*](https://projecteuler.net/) ist eine englischsprachige Website. Sie enthält eine Reihe von Problemstellungen,
die mithilfe von Mathematik und Programmierung gelöst werden können. Die Aufgabenstellung dieser Fallstudie
finden Sie unter &bdquo;Problem 39&rdquo;.

Der Schwerpunkt der Aufgabe liegt in der Betrachtung eines parallelen Lösungsansatzes. Mit Hilfe der Klassen
`std::thread`, `std::function`, `std::mutex` und `std::lock_guard` gehen
wir auf eine Realisierung einer Funktion `parallel_for` ein.

<!--more-->

# Lernziele

  * Klassen `std::thread`, `std::function`, `std::mutex` und `std::lock_guard`
  * Container `std::vector`
  * `if`- und `for`-Anweisung mit *Initializer*
  * Algorithmen `std::for_each`, `std::begin`, `std::end`
  * Lambda-Funktionen mit Zugriffsklausel
  * Utility `std::mem_fn`

# Einführung

Für rechtwinklige Dreiecke gibt es den *Satz des Pythagoras*. Dieser besagt, dass
für die drei Seiten *a*, *b* und *c* die Beziehung *a*<sup>2</sup> + *b*<sup>2</sup> = *c*<sup>2</sup> gilt.
Dabei steht *c* für die Hypotenuse, sie ist die längste Seite eines rechtwinkligen Dreiecks und liegt dem rechten Winkel gegenüber.
Als Kathete werden die beiden kürzeren Seiten in einem rechtwinkligen Dreieck bezeichnet.



###### {#abbildung_1_gray_codes_four_bits}

<img src="RightTriangle.png" width="400">

{{< figure src="/img/graycodes/GrayCodes01.png" width="50%" >}}

RightTriangle.png

*Abbildung* 1: Rechtwinkliges Dreick mit Hypotenuse und Katheten.


Der Umfang *p* (engl: *perimeter* oder *circumference*) eines rechwinkligen Dreieckes
berechnet sich zu *p* = *a* + *b* + *c*. 

Das &bdquo;Problem 39&rdquo; aus dem *Project Euler* lautet nun:
Für welchen Umfang *p* mit *p* <= 2000 ist die Anzahl der verschiedenen rechwinkligen Dreiecke
mit ganzzahligen Seitenlängen *a*, *b* und *c* am größten?

*Beispiel*:
Betrachten wir den Umfang *p* = 120:
Die drei Tripel { 20, 48, 52 }, { 24, 45, 51 } und { 30, 40, 50 } sind die einzigen drei Tripel,
die mit ganzzahligen Werten ein rechtwinkliges Dreieck des Umfangs *p* = 120 beschreiben.

## Hinweise

Mit Hilfe der beiden Gleichungen *a*<sup>2</sup> + *b*<sup>2</sup> = *c*<sup>2</sup> und *p* = *a* + *b* + *c* lässt
sich auf recht einfache Weise eine Methode mit einigen wenigen geschachtelten Kontrollstrukturen entwerfen,
die alle in Frage kommenden Tripel (*a*, *b*, *c*) berechnet.


## Parallelisierung der Lösung

Welche Parallelisierungsansätze sind für diese Aufgabenstellung denkbar?
Implementieren Sie einen parallelen Algorithmus und vergleichen Sie die Laufzeiten der beiden Varianten.

Die im letzen Abschnitt erwähnten Kontrollstrukturen &ndash; wir reden da offensichtlich von `for`-Wiederholungsschleifen &ndash; 
kann man auf Basis einer `parallel_for`-Kontrollstrukturen parallelisieren.
Einziger Wehrmutstropfen dieser Idee: In der STL gibt es eine derartige Funktion nicht, 
aber es bereitet keine große Mühe, eine solche Funktion selber zu schreiben.





# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wir beginnen mit den Dreiecken. Da wir bei Bedarf die berechneten Dreiecke auch ausgeben wollen,
müssen wir diese in einer geeigneten Datenstruktur festhalten. Es kommen hier im Prinzip die beiden Möglichkeiten
eines `std::tuple`-Objekts oder einen Strukur in Betracht. Ich habe mich für die klassische Vorgehensweise
mit einer Struktur entschieden ([Listing 1]): 

###### {#listing_1_class_pythagorean_triple_decl}

```cpp
01: class PythagoreanTriple
02: {
03: private:
04:    std::array<size_t, 3> m_numbers;
05: 
06: public:
07:     PythagoreanTriple();
08:     PythagoreanTriple(size_t x, size_t y, size_t z);
09: 
10:     size_t circumference();
11:     std::string toString();
12: };
```

*Listing* 1: Klasse `PythagoreanTriple`: Schnittstelle.

Die Realisierung der Konstuktoren und der beiden Methoden `circumference` und `toString` ist trivial:


###### {#listing_2_class_pythagorean_triple_impl}

```cpp
01: PythagoreanTriple::PythagoreanTriple()
02:     : PythagoreanTriple{ 0, 0, 0 }
03: {}
04: 
05: PythagoreanTriple::PythagoreanTriple(size_t x, size_t y, size_t z)
06:     : m_numbers{ x, y, z }
07: {}
08: 
09: size_t PythagoreanTriple::circumference() {
10: 
11:     return m_numbers[0] + m_numbers[1] + m_numbers[2];
12: }
13: 
14: std::string PythagoreanTriple::toString() {
15: 
16:     return std::format("[{:02},{:02},{:02}]",
17:         m_numbers[0], m_numbers[1], m_numbers[2]);
18: }
```

*Listing* 2: Klasse `PythagoreanTriple`: Realisierung.


Damit sind wir schon bei der Berechnung der Dreiecke angekommen.
In einem sehr einfachen Ansatz ziehen wir drei geeignete `for`-Wiederholungsanweisungen auf,
um am Ende mit den beiden Bedingungen, die sich durch den &bdquo;Satz das Pythagoras&rdquo; und den &bdquo;Umfang des Dreiecks&rdquo; ergeben,
Treffer zu suchen. Eine grobe Skizze eine Klasse `PythagoreanTripleCalculator`
zeigt [Listing 3] auf:


###### {#listing_3_class_pythagorean_triple_calculator}


```cpp
01: template <typename TStore>
02: class PythagoreanTripleCalculator
03: {
04: private:
05:     TStore m_store;
06: 
07: public:
08:     // c'tor
09:     PythagoreanTripleCalculator() = default;
10: 
11:     // getter
12:     size_t triplesCount() { return m_store.size(); }
13: 
14:     // public sequential interface
15:     void calculateSeq(size_t max)
16:     {
17:         for (size_t circ{ 3 }; circ < max; ++circ) {
18:             calculate(circ);
19:         }
20:     }
21: 
22: private:
23:     void calculate(size_t circ)
24:     {
25:         for (size_t count{}, a{ 1 }; a <= circ; ++ a) {
26: 
27:             for (size_t b{ a }; b <= circ; ++ b) {
28: 
29:                 if (size_t c{ circ - a - b }; a * a + b * b == c * c) {
30: 
31:                     // found a pythagorean triple
32:                     count++;
33:                     m_store.add (count, circ, a, b, c);
34:                 }
35:             }
36:         }
37:     }
38: };
```

*Listing* 3: Klasse `PythagoreanTripleCalculator`: Grobe Skizzierung.

In den Zeilen 25 bis 36 von [Listing 3] erkennen wir den *Brute-Force*&ndash;Ansatz in der Berechnung
der geeigneten Dreiecke. Wenngleich diese Vorhegehensweise nicht recht elegant aussehen man,
bietet sie jedoch eine Option für den Einstieg in eine parallele Berechnung.

Die äußerste `for`-Wiederholungsanweisung nimmt sich mit dem Wert einer Dreiecksseite *a* an.
Diese Wiederholungen für alle möglichen Wert von *a* könnte man auch gleichzeitig (also *quasi*- oder *echt*-parallel) abarbeiten.
Damit sind wir bei der Realisierung einer `parallel_for`-Funktion angekommen.

Wenn wir im C++&ndash;Baukasten die Klasse `std::thread` als auch `std::function` herausgreifen,
lässt sich damit ein `parallel_for` vergleichweise realisieren ([Listing 4]):

###### {#listing_4_function_parallel_for}

```cpp
01: constexpr bool Verbose{ true };
02: 
03: void callableWrapper(Callable callable, size_t start, size_t end) {
04: 
05:     if (Verbose) {
06:         std::stringstream ss{};
07:         ss << "TID:  " << std::this_thread::get_id() << "\t[" << start << " - " << end << "]\n";
08:         std::cout << ss.str();
09:     }
10: 
11:     callable(start, end);
12: }
13: 
14: void parallel_for(
15:     size_t from,
16:     size_t to,
17:     Callable callable,
18:     bool useThreads)
19: {
20:     // calculate number of threads to use
21:     size_t numThreadsHint{ std::thread::hardware_concurrency() };
22:     size_t numThreads{ (numThreadsHint == 0) ? 8 : numThreadsHint };
23:     size_t numElements = to - from + 1;
24:     size_t batchSize{ numElements / numThreads };
25: 
26:     // allocate vector of uninitialized thread objects
27:     std::vector<std::thread> threads;
28:     threads.reserve(numThreads - 1);
29: 
30:     for (size_t i{}; i != numThreads - 1; ++i) {
31: 
32:         size_t start{ from + i * batchSize };
33: 
34:         if (useThreads) {
35: 
36:             // multi-threaded execution
37:             threads.push_back(
38:                 std::move(std::thread{
39:                     callableWrapper, callable, start, start + batchSize
40:                     }
41:                 )
42:             );
43:         }
44:         else {
45: 
46:             // single-threaded execution (for debugging purposes)
47:             callableWrapper(callable, start, start + batchSize);
48:         }
49:     }
50: 
51:     // take care of last element - calling 'callable' synchronously 
52:     size_t start{ from + (numThreads - 1) * batchSize };
53:     callableWrapper(callable, start, to);
54: 
55:     // wait for the other thread to finish their task
56:     if (useThreads)
57:     {
58:         std::for_each(
59:             threads.begin(),
60:             threads.end(),
61:             std::mem_fn(&std::thread::join)
62:         );
63:     }
64: }
```

*Listing* 4: Funktion `parallel_for`.

Aauf einige markante Stellen von [Listing 4] sollten wir näher eingehen.

WEITER: Thread erzeugen ....


# There&lsquo;s more

Gray-Codes lassen sich sowohl mit einem rekursiven als auch mit einem iterativen Algorithmus berechnen.
Versuchen Sie, an Hand der Beschreibung des Algorithmus in [Abbildung 2] eine iterative Realisierung in C++ umzusetzen.
Die folgende [Anregung](https://www.geeksforgeeks.org/generate-n-bit-gray-codes/) könnte hierbei behilflich sein.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_graycodescalculator

[Listing 1]: #listing_1_class_pythagorean_triple_decl
[Listing 2]: #listing_2_class_pythagorean_triple_impl
[Listing 3]: #listing_3_class_pythagorean_triple_calculator
[Listing 4]: #listing_4_function_parallel_for


[Abbildung 1]:  #abbildung_1_gray_codes_four_bits
[Abbildung 2]:  #abbildung_2_gray_codes_construction

<!-- End-of-File -->

