<!-- PowerSet.md -->

Unter der Potenzmenge *P*(*S*) versteht man die Menge aller möglichen Teilmengen von *S*. 
Mit Hilfe zweier Klassen  `PowerSet` und `PartialSet` sowie einem recht einfachen
Algorithmus zur Bestimmung der Potenzmenge betrachten wir diese in *Modern C++*.

<!--more--> 

# Lernziele

  * Einheitliche Initialisierung
  * Initialisierungsliste (`std::initializer_list<T>`)
  * STL-Klasse `std::set<T>`
  * Container-Methoden `cbegin()` und `cend()`
  * C++ Iteratorenkonzept

# Einführung

Als Potenzmenge bezeichnet man in der Mengenlehre die Menge aller Teilmengen zu einer
gegebenen Grundmenge. Besitzt die Grundmenge den Namen *S*, notiert man die Potenzmenge meist
als *P*(*S*) von *S*. Für die 3-elementige Menge *S* = { 1, 2, 3 } ergibt sich die Potenzmenge *P*({ 1, 2, 3 }) zu

```
P({1,2,3}) =
{
  {},
  {1},   {2},   {3},
  {1,2}, {1,3}, {2,3},
  {1,2,3}
}
```

Die Größe einer Potenzmenge (also die Anzahl aller Teilmengen) ist immer 2<sup>n</sup>,
wenn *n* die Anzahl der Elemente der Grundmenge ist.
Erstellen Sie eine Implementierung für zwei Klassen `PowerSet` (Potenzmenge) und `PartialSet`
(Teilmenge, also ein Element einer Potenzmenge). Integrieren Sie dabei, soweit sinnvoll machbar, möglichst
viele programmiersprachliche Konstrukte bzw. Sprachmittel von *Modern C++*!

# Die Klasse `PartialSet`

Bevor wir uns dem Algorithmus zur Konstruktion einer Potenzmenge (und damit der Klasse `PowerSet`) zuwenden,
benötigen Sie als Fundament die Klasse `PartialSet`. Implementieren Sie ein Grundgerüst dieser Klasse
an Hand der Vorgaben aus [Tabelle 1].

Eine Instanz der Klasse `PartialSet` sollte ihre Elemente immer in aufsteigend sortierter Form ablegen.
Auf diese Weise lassen sich Operationen wie zum Beispiel das Vergleichen von `PartialSet`-Objekten leichter implementieren.

###### {#tabelle_1_class_partialset}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `PartialSet() = default;`<br/>Der Standardkonstruktor dient zum Erzeugen einer leeren Teilmenge. |
| Benutzerdefinierter Konstruktor | `PartialSet(const std::initializer_list<size_t>& list);`<br/>Der Konstruktor erzeugt eine Teilmenge. Mit `list` wird eine variabel lange Liste von Elementen übergeben, die in der Teilmenge enthalten sind. |
| *getter* `size()` | `size_t size() const;`<br/>Liefert die Anzahl der Elemente der Teilmenge zurück. |
| Methode `add()` | `void add(size_t elem);`<br/>Fügt ein Element in die Teilmenge ein. Diese Methode wird zum algorithmischen Erzeugen einer Teilmenge benötigt. |
| Operator `==` | `friend bool operator==(const PartialSet&, const PartialSet&);`<br/>Vergleicht zwei `PartialSet`-Objekte auf Gleichheit. Zwei Teilmengen sind genau dann gleich, wenn sie die gleichen Elemente enthalten. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const Permutation&);`<br/>Gibt ein `PartialSet`-Objekt auf der Konsole aus. Die Darstellung einer Teilmenge sollte folgendes Aussehen haben:<br/>`{ 1, 2, 3 }` |

*Tabelle* 1: Wesentliche Elemente der Klasse `PartialSet`.

Wir betrachten einige Testbeispiele:

```cpp
PartialSet set1{ };
std::cout << set1 << std::endl;

PartialSet set2{ 1, 2, 3 };
std::cout << set2 << std::endl;

PartialSet set3{ 3, 2, 1 };
std::cout << set3 << std::endl;
```

*Ausgabe*:

```
{ }
{ 1, 2, 3 }
{ 1, 2, 3 }
```

Man erkennt an der Ausgabe, dass die Mengen in aufsteigend sortierter Form vorliegen bzw. ausgegeben werden.

Test der `add`-Methode:

```cpp
PartialSet set{ };
set.add(3);
set.add(2);
set.add(1);
std::cout << set << std::endl;
```

*Ausgabe*:

```
{ 1, 2, 3 }
```

Test der Vergleichsoperatoren:

```cpp
PartialSet set1{ };
std::cout << set1 << std::endl;

PartialSet set2{ 1 };
std::cout << set2 << std::endl;

PartialSet set3{ 1, 2 };
std::cout << set3 << std::endl;

PartialSet set4{ 1, 2, 3 };
std::cout << set4 << std::endl;

std::cout << std::boolalpha << (set1 == set1) << std::endl;
std::cout << std::boolalpha << (set1 == set2) << std::endl;
std::cout << std::boolalpha << (set1 < set2) << std::endl;
std::cout << std::boolalpha << (set2 < set1) << std::endl;

std::cout << std::boolalpha << (set3 == set3) << std::endl;
std::cout << std::boolalpha << (set3 == set4) << std::endl;
std::cout << std::boolalpha << (set3 < set4) << std::endl;
std::cout << std::boolalpha << (set4 < set3) << std::endl;
```

*Ausgabe*:

```
{ }
{ 1 }
{ 1, 2 }
{ 1, 2, 3 }
true
false
true
false
true
false
true
false
```

# Eine intuitive Konstruktionsvorschrift für Potenzmengen

Für die algorithmische Berechnung einer Potenzmenge gibt es eine vergleichsweise einfache intuitive
Konstruktionsvorschrift. Um beim Beispiel einer Grundmenge mit den drei Elementen 1, 2, und 3 zu
bleiben: Wenn Sie im binären Zahlensystem alle Zahlen betrachten, die aus drei binären Ziffern
bestehen, also die binären Zahlen 000, 001, 010, 011, 100, 101, 110 und 111, zu welcher Beobachtung
gelangen Sie? Der Zusammenhang zwischen dem binären Zahlensystem und einer
korrespondierenden Potenzmenge sollte mit diesem Vergleich deutlich geworden sein: Identifizieren
wir jede dieser Zahlen mit einer Teilmenge der gegebenen Grundmenge und legen wir ferner fest,
dass eine binäre Ziffer *b* spezifiziert, ob ein korrespondierendes Element in der Teilmenge enthalten
ist (*b* = 1) oder nicht (*b* = 0), so erhalten wir eine direkte Konstruktionsvorschrift für die Potenzmenge.
Am Beispiel einer Grundmenge mit den Elementen 1, 2 und 3 stellen wir diese Zuordnung zur
jeweiligen Teilmenge noch einmal exemplarisch gegenüber:

```
000 <-> { }
001 <-> { 1 }
010 <-> { 2 }
011 <-> { 1, 2 }
100 <-> { 3 }
101 <-> { 1, 3 }
110 <-> { 2, 3 }
111 <-> { 1, 2, 3 }
```

Wir legen also die Menge aller Kombinationen der Ziffern 0 und 1 zu Grunde, deren Anzahl sich – in
diesem Beispiel – zu 2<sup>3</sup> berechnet.

# Die Klasse `PowerSet`

Wir fahren mit einigen Hilfestellungen zur Implementierung der Klasse `PowerSet` in [Tabelle 2] fort:

###### {#tabelle_2_class_powerset}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `PowerSet();`<br/>Es wird die einelementige Potenzmenge erzeugt (bestehend aus der leeren Menge `{ }`). |
| Benutzerdefinierter Konstruktor | `PowerSet(size_t n);`<br/>Es wird die Potenzmenge zur Grundmenge { 1, 2, ..., *n* } erzeugt. |
| *getter* `size()` | `size_t size() const;`<br/>Liefert die Anzahl der Elemente aus der Basismenge zurück. |
| *getter* `cardinality()` | `size_t cardinality() const;`<br/>Liefert die Anzahl der Elemente der Potenzmenge zurück. *Hinweis*: Besteht die Basismenge aus *n* Elementen, so besitzt die Potenzmenge 2<sup>*n*</sup> Teilmengen. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const PowerSet&);`<br/>Gibt ein `PowerSet`-Objekt auf der Konsole aus. |

*Tabelle* 2: Wesentliche Elemente der Klasse `PowerSet`.

Es folgen einige Beispiele zur Klasse `PowerSet`. Studieren Sie diese sorgfältig und stimmen Sie Ihre Realisierung darauf ab:

*Beispiel* 1:

```cpp
PowerSet set{ };
std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
std::cout << set << std::endl;
```

*Ausgabe*:

```
Size: 0, Cardinality: 1
{ }
```

*Beispiel* 2:

```cpp
PowerSet set{ 1 };
std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
std::cout << set << std::endl;
```

*Ausgabe*:

```
Size: 1, Cardinality: 2
{ }
{ 1 }
```

*Beispiel* 3:

```cpp
PowerSet set{ 2 };
std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
std::cout << set << std::endl;
```

*Ausgabe*:

```
Size: 2, Cardinality: 4
{ }
{ 1 }
{ 1, 2 }
{ 2 }
```

*Beispiel* 4:

```cpp
PowerSet set{ 3 };
std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
std::cout << set << std::endl;
```

*Ausgabe*:

```
Size: 3, Cardinality: 8
{ }
{ 1 }
{ 1, 2 }
{ 1, 2, 3 }
{ 1, 3 }
{ 2 }
{ 2, 3 }
{ 3 }
```

# Sortierung einer Potenzmenge

In dieser Teilaufgabe betrachten wir die sortierte Ausgabe aller Teilmengen einer Potenzmenge.
Im Prinzip geht es darum, ein Kriterium für den Vergleich zweier Teilmengen festzulegen.
Wenn Sie Ihre bisherige Implementierung betrachten, sollten Sie bei der Berechnung der Potenzmenge zur Basismenge `{ 1, 2, 3, 4 }`
die folgende Ausgabe erhalten:

```
Size: 4, Cardinality: 16
{ }
{ 1 }
{ 1, 2 }
{ 1, 2, 3 }
{ 1, 2, 3, 4 }
{ 1, 2, 4 }
{ 1, 3 }
{ 1, 3, 4 }
{ 1, 4 }
{ 2 }
{ 2, 3 }
{ 2, 3, 4 }
{ 2, 4 }
{ 3 }
{ 3, 4 }
{ 4 }
```

Wie müssten Sie einen Operator `<` in der Klasse `PartialSet` definieren, um die folgende Ausgabe zu erhalten:

```
{ }
{ 1 }
{ 2 }
{ 3 }
{ 4 }
{ 1, 2 }
{ 1, 3 }
{ 1, 4 }
{ 2, 3 }
{ 2, 4 }
{ 3, 4 }
{ 1, 2, 3 }
{ 1, 2, 4 }
{ 1, 3, 4 }
{ 2, 3, 4 }
{ 1, 2, 3, 4 }
```

###### {#tabelle_3_class_partialset_operators}

| Operator | Beschreibung |
| :---- | :---- |
| Operator `<` | `friend bool operator<(const PartialSet&, const PartialSet&);`<br/>Vergleicht zwei `PartialSet`-Objekte auf &bdquo;kleiner&rdquo;. Wir bezeichnen eine Teilmenge *S*1 &bdquo;kleiner&rdquo; als eine Teilmenge *S*2, wenn *S*1 entweder weniger Elemente als *S*2 enthält oder, falls *S*2 gleich viele Elemente enthält, das erste Element von *S*1 kleiner ist als das erste Element von *S*2. Stimmen beide Teilmengen im ersten Element überein, setzen wir den Vergleich mit dem zweiten, dritten, usw. Element fort, bis ein Unterschied auftritt. Dabei wird vorausgesetzt, dass die Elemente beider Teilmengen in aufsteigender Reihenfolge vorliegen. |

*Tabelle* 3: Definition des Operators `operator<` in der Klasse `PartialSet`.

# Aufzählung einer Potenzmenge

Bei Objekten, die den Charakter eines Containers besitzen (Menge aller Schriftarten auf einem Rechner, Menge aller laufenden Prozesse, etc.)
gibt es die Möglichkeit, die einzelnen Elemente eines solchen Objekts der Reihe nach aufzuzählen (so genannte &bdquo;Traversierung der Menge&rdquo;).
Auf das Beispiel der Potenzmenge angewendet ergänzen wir die Klasse `PowerSet` um die beiden Methoden `begin()` und `end()`, die die zum Iterieren
notwendigen Objekte für den Start und das Ende einer Aufzählung bereitstellen ([Tabelle 4]):

###### {#tabelle_4_class_partialset_begin_end}

| Methode | Beschreibung |
| :---- | :---- |
| `begin()` | `std::set<PartialSet>::const_iterator begin();`<br/>Liefert ein Iterator-Objekt zurück, das auf das erste `PartialSet`-Objekt verweist. |
| `end()` | `std::set<PartialSet>::const_iterator end();`<br/>Liefert ein Iterator-Objekt zurück, das hinter das letzte Element zeigt. |

*Tabelle* 4: Aufzählung einer Potenzmenge.

Studieren und testen Sie Ihre Funktionsweise der Iterator-Realisierung an einer bereichsbasierten Wiederholungsschleife:

*Beispiel* 4:

```cpp
PowerSet powerSet{ 3 };
for (const PartialSet& set : powerSet) {
    std::cout << "Next Set: " << set << std::endl;
}
```

*Ausgabe*:

```
Next Set: { }
Next Set: { 1 }
Next Set: { 2 }
Next Set: { 3 }
Next Set: { 1, 2 }
Next Set: { 1, 3 }
Next Set: { 2, 3 }
Next Set: { 1, 2, 3 }
```

# Teilmengen einer Potenzmenge

Von einer Potenzmenge lassen sich Teilmengen bilden. Zum Beispiel kann man alle Elemente einer
Potenzmenge betrachten, die dieselbe Anzahl *k* von Elementen besitzen. Dazu betrachten wir am
besten ein Beispiel: Alle zweielementigen Teilmengen der Potenzmenge, deren Grundmenge aus
den Elementen 0, 1, und 2 besteht, lauten `{0, 1}`, `{0, 2}` und `{1, 2}`.
Ergänzen Sie Ihre Realisierung der Klasse `PowerSet` um eine Methode `partialSetsBySize`:

###### {#tabelle_5_class_powerset_begin_partialsetsbysize}

| Methode | Beschreibung |
| :---- | :---- |
| `partialSetsBySize()` | `PowerSet partialSetsBySize(size_t size);`<br/>Berechnet alle Teilmengen einer Potenzmenge mit der Größe `size`. |

*Tabelle* 5: Teilmengen einer Potenzmenge.

Ein Beispiel:

```cpp
PowerSet powerSet{ 5 };
size_t size = 3;
PowerSet someSets = powerSet.partialSetsBySize(size);
std::cout << "Partial set of size " << size << ':' << std::endl;
for (const PartialSet& set : someSets) {
    std::cout << set << std::endl;
}
```

*Ausgabe*:

```
Partial set of size 3:
{ 1, 2, 3 }
{ 1, 2, 4 }
{ 1, 2, 5 }
{ 1, 3, 4 }
{ 1, 3, 5 }
{ 1, 4, 5 }
{ 2, 3, 4 }
{ 2, 3, 5 }
{ 2, 4, 5 }
{ 3, 4, 5 }
```

# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wir stellen nachfolgend den Quellcode der beteiligten Klassen vor. Am Anfang stehen Teilmengen einer Potenzmenge und damit 
die Klasse `PartialSet` ([Listing 1] und [Listing 2]):

###### {#listing_class_partialset_decl}

```cpp
01: class PartialSet
02: {
03: private:
04:     std::set<size_t> m_numbers;
05: 
06: public:
07:     // c'tors
08:     PartialSet() = default;
09:     PartialSet(const std::initializer_list<size_t>&);
10: 
11:     // getter
12:     size_t size() const { return m_numbers.size(); }
13: 
14:     // public interface
15:     void add(size_t elem) { m_numbers.insert(elem); }
16: 
17:     // public operators
18:     friend bool operator== (const PartialSet&, const PartialSet&);
19:     friend bool operator<  (const PartialSet&, const PartialSet&);
20: 
21:     // input/output
22:     friend std::ostream& operator<< (std::ostream&, const PartialSet&);
23: };
```

*Listing* 1: Klasse `PartialSet`: Definition.

###### {#listing_class_partialset_impl}

```cpp
01: // c'tors / d'tor
02: PartialSet::PartialSet(const std::initializer_list<size_t>& list)
03:     : m_numbers{ list.begin(), list.end() } {}
04: 
05: // public operators
06: bool operator== (const PartialSet& set1, const PartialSet& set2)
07: {
08:     // delegating comparison to standard comparison of two std::set objects
09:     return (set1.m_numbers == set2.m_numbers);
10: }
11: 
12: bool operator< (const PartialSet& set1, const PartialSet& set2)
13: {
14:     if (set1.m_numbers.size() < set2.m_numbers.size()) {
15:         return true;
16:     }
17:     else if (set1.m_numbers.size() > set2.m_numbers.size()) {
18:         return false;
19:     }
20:     else {
21:         // use default function object std::less<int>
22:         return set1.m_numbers < set2.m_numbers;
23:     }
24: }
25: 
26: // output
27: std::ostream& operator<< (std::ostream& os, const PartialSet& set)
28: {
29:     os << "{ ";
30:     if (set.m_numbers.begin() != set.m_numbers.end()) {
31: 
32:         std::set<size_t>::const_iterator it = set.m_numbers.begin();
33:         std::set<size_t>::const_iterator penultimate = std::prev(set.m_numbers.end());
34:         for (it = set.m_numbers.begin(); it != penultimate; ++it) {
35:             os << (*it) << ", ";
36:         }
37:         os << (*penultimate) << ' ';
38:     }
39:     os << "}";
40:     return os;
41: }
```

*Listing* 2: Klasse `PartialSet`: Implementierung.

In der Implementierung der Klasse `PartialSet` ([Listing 2]) ist die Realisierung des Operators `<<`
möglicherweise etwas auffällig: Es geht schlicht und ergreifend darum, eine Teilmenge auf der Konsole im Format `{ 1, 2, 3 }` auszugeben,
um es an einem Beispiel festzumachen.
Dies sieht beim ersten Betrachten recht trivial aus &ndash; mit einer Ausnahme: Nach der Zahl 3, also dem letzten Element der Teilmenge, wird kein Komma mehr ausgegeben.
Natürlich ist dieses Problem nicht unlösbar, aber eben nicht mit ein paar C++-Anweisungen im Programmierstil einer ungebremsten Eleganz, wie wir den Zeilen 30 bis 38 entnehmen können.

Das Problem einer leeren Teilmenge ist in Zeile 30 abgehandelt: Nur wenn die beiden Iterator-Objekte `set.m_numbers.begin()` und `set.m_numbers.end()` gleich sind,
kommt es nicht zur Ausführung des Rumpfes der Bedingungsanweisung. Jetzt können wir bei einer nicht-leeren Teilmenge das Problem des letzten Kommas angehen,
die `std::prev`-Methode liefert immer ein gültiges Iterator-Objekt zurück (eben da die Teilmenge nicht leer ist).
Die `for`-Wiederholungsschleife gibt alle Elemente der Teilmenge bist auf das letzte aus,
diesem widmen wir uns in Zeile 37 separat.
Elegante *Modern C++*-Anweisungen wie die bereichsbasierte Wiederholungsschleife können wir leider in diesem Beispiel
nicht einsetzen, da der Bereich nicht vollständig durchlaufen wird.

Damit sind wir bei der Klasse `PowerSet` angekommen
([Listing 3] und [Listing 4]):

###### {#listing_class_powerset_decl}

```cpp
01: class PowerSet
02: {
03: private:
04:     // member data
05:     size_t m_size;                // number of elements in base set
06:     size_t m_cardinality;         // number of subsets
07:     std::set<PartialSet> m_sets;  // subsets
08: 
09: public:
10:     // c'tors
11:     PowerSet();
12:     PowerSet(size_t size);
13: 
14:     // getter
15:     size_t cardinality() const { return m_cardinality; }
16:     size_t size() const { return m_size; }
17: 
18:     // public interface
19:     PowerSet partialSetsBySize(size_t size);
20: 
21:     // iterator support
22:     std::set<PartialSet>::const_iterator begin();
23:     std::set<PartialSet>::const_iterator end();
24: 
25:     // output
26:     friend std::ostream& operator<< (std::ostream&, const PowerSet&);
27: 
28: private:
29:     void computePartialSets();
30:     static size_t powerByTwo(size_t num);
31: };
```

*Listing* 3: Klasse `PowerSet`: Definition.

###### {#listing_class_powerset_impl}

```cpp
01: // c'tors
02: PowerSet::PowerSet() : m_size{ 0 }, m_cardinality{ 1 }, m_sets{ PartialSet {} } {}
03: 
04: PowerSet::PowerSet(size_t size) : m_size{ size }, m_cardinality{ powerByTwo(size) }
05: {
06:     computePartialSets();
07: }
08: 
09: // public interface
10: PowerSet PowerSet::partialSetsBySize(size_t size) {
11: 
12:     PowerSet result{ };
13:     result.m_sets.clear();
14:     for (const PartialSet& set : m_sets) {
15:         if (set.size() == size) {
16:             result.m_sets.insert(set);
17:         }
18:     }
19:     
20:     return result;
21: }
22: 
23: // iterator support
24: std::set<PartialSet>::const_iterator PowerSet::begin() { 
25:     return m_sets.cbegin();
26: }
27: 
28: std::set<PartialSet>::const_iterator PowerSet::end() {
29:     return m_sets.cend(); 
30: }
31: 
32: // output
33: std::ostream& operator<< (std::ostream& os, const PowerSet& ps)
34: {
35:     for (const auto& set : ps.m_sets) {
36:         os << set << std::endl;
37:     }
38: 
39:     return os;
40: }
41: 
42: // private helper methods
43: void PowerSet::computePartialSets() {
44: 
45:     for (size_t i = 0; i != m_cardinality; i++) {
46: 
47:         PartialSet set{ };
48:         for (size_t j = 0; j != m_size; j++) {
49: 
50:             int mask = 1 << j;
51:             if ((mask & i) != 0) {
52:                 set.add(j + 1);
53:             }
54:         }
55: 
56:         m_sets.insert(set);
57:     }
58: }
59: 
60: size_t PowerSet::powerByTwo(size_t num)
61: {
62:     size_t base_2;
63:     for (base_2 = 1; base_2 < (static_cast<size_t>(1) << num); base_2 <<= 1)
64:         ;
65: 
66:     return base_2;
67: }
```

*Listing* 4: Klasse `PowerSet`: Implementierung.

Einige Anmerkungen zu [Listing 4]: In Zeile 13 darf der Aufruf von `clear()` nicht fehlen, da im Standard-Konstruktor der Klasse `PowerSet` das Mengenobjekt `m_sets` *nicht* initialisiert wird,
sondern mit der leeren Menge vorbelegt wird. Die einheitliche Initialisierung veranlasst in Zeile 47 in diesem Fall den Aufruf des Standard-Konstruktors der Klasse `PartialSet`.
Schließlich kann der Gebrauch des Links-Shift Operators (Zeile 63) zu besseren Laufzeiten führen als der Einsatz der `pow`-Funktion aus der `math`-Bibliothek.
Die Zeilen 45 bis 57 ([Listing 4]) sind möglicherweise etwas kurz geraten, in jedem Fall implementieren sie die
intuitive Konstruktionsvorschrift für Potenzmengen.

# There&lsquo;s more

Unsere bisherigen Betrachtungen einer Potenzmenge haben sich ausschließlich auf Grundmengen mit ganzen Zahlen beschränkt.
Für die Grundmenge kann man aber auch die Annahme treffen, dass deren integraler Datentyp (`int`, `short`, `long`, `size_t`, etc.) variabel sein sollte.
Auch kann man sich eine Grundmenge aus Zeichen (`char`) vorstellen.
Welche Änderungen sind an den beiden Klassen `PartialSet` und `PowerSet` vorzunehmen,
um die Grundmenge mit unterschiedlichen integralen Datentypen definieren zu können?

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_partialset
[Tabelle 2]: #tabelle_2_class_powerset
[Tabelle 3]: #tabelle_3_class_partialset_operators
[Tabelle 4]: #tabelle_4_class_partialset_begin_end
[Tabelle 5]: #tabelle_5_class_powerset_begin_partialsetsbysize

[Listing 1]: #listing_class_partialset_decl
[Listing 2]: #listing_class_partialset_impl
[Listing 3]: #listing_class_powerset_decl
[Listing 4]: #listing_class_powerset_impl

<!-- End-of-File -->
