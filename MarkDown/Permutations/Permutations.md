<!-- Permutationen -->

Ist eine Menge von _n_ Elementen gegeben, so bezeichnet man die möglichen Anordnungen
aller dieser _n_ Elemente als Permutationen (lat. _permutare_: vertauschen).
Die Berechnung der Permutationen einer beliebigen Menge von Elementen
steht im Mittelpunkt dieser Fallstudie.
Als Elemente verwenden wir zunächst Zeichen, also `char`-Variablen.
Dies sollte aber verallgemeinerbar sein, also auch für Variablen eines beliebigen Datentyps.

Für zwei Zeichen `A` und `B` gibt es nur die zwei Permutationen `AB` und `BA`.
Drei Zeichen, angenommen `A`, `B` und `C`, können hingegen
in sechs verschiedenen Permutationen dargestellt werden:
`ABC`, `ACB`, `BAC`, `BCA`, `CAB` und `CBA`.
Sind alle _n_ Elemente voneinander verschieden, was wir in dieser Aufgabe zu Grunde legen,
so gibt es dafür _n_! Anordnungen (_n_-Fakultät).

<!--more-->

# Lernziele

  * Template-Technik
  * STL-Container `std::list<T>` und `std::list<T>`
  * STL-Algorithmen `std::for_each`, `std::begin`, `std::end`, `std::rbegin` und `std::rend`
  * STL-Iteratoren
  * Lambda-Funktionen mit Zugriffsklausel
  * Initialisierungsliste (`std::initializer_list<T>`)
  * Anwendungsbeispiel für `std::move`
  * Anwendungsbeispiel für `std::next_permutation`
  * Benutzerdefinierter Literaloperator (`operator""`)
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Bevor wir auf den Algorithmus zur Berechnung von Permutationen eingehen,
entwickeln wir zwei Hilfsklassen `Permutation` und `PermutationContainer`.
Da wir für die Permutationen unterschiedliche Datentypen der einzelnen Elemente zu Grunde legen wollen,
kommen bei der Realisierung Klassen-Templates ins Spiel.


# Klasse `Permutation<T>`

Die Klasse `Permutation` &ndash; genauer: `Permutation<T>` &ndash; benötigen wir,
um eine einzelne Permutation darzustellen.
Überlegen Sie, welcher Container der STL als Hilfestellung dafür geeignet sein könnte?
Die Details zur Schnittstelle der Klasse `Permutation` sind in [Tabelle 1] zusammengestellt:

###### {#tabelle_1_class_permutation}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `Permutation();`<br/>Standardkonstruktor für ein `Permutation`-Objekt. |
| Konstruktor | `Permutation(std::initializer_list<T> list);`<br/>Initialisiert ein `Permutation`-Objekt mit eine Reihe von Elementen des Typs `T`, die in einem `std::initializer_list<T>`-Objekt abgelegt sind. Sinnvollerweise sollten die Elemente alle voneinander verschieden sein. Sie brauchen das in Ihrer Implementierung aber nicht zu überprüfen. |
| Methode `grade` | `size_t grade() const;`<br/>Liefert Wert zum Schlüssel `key` zurück. |
| Methode `insertAtFront` | `void insertAtFront(T elem);`<br/>Das übergebene Element `elem` wird in der vorliegenden Permutation am *Anfang* eingefügt. Insbesondere wird der *Grad* der Permutation um Eins größer. |
| Methode `removeAt` | `Permutation<T> removeAt(size_t i) const;`<br/>Die Methode entfernt ein Element an der Stelle `i` aus der vorliegenden Permutation. Das Ergebnis wird in einem neuen `Permutation<T>`-Objekt als Resultat der Methode zurüclgeliefert. Die Methode selbst ist mit `const` markiert, also das aktuelle Objekt bleibt unverändert. |
| Methode `getValues` | `std::vector<T> getValues() const;`<br/>.Die Methode liefert die aktuellen Elemente der Permutation in einem `std::vector<T>`-Objekt zurück. |
| Operator `[]` | `const T& operator[](size_t n) const;`<br/>Zugriffsoperator für das *i*.-te Element der Permutation. |

*Tabelle* 1: Element der Klasse `Permutation<T>`.

Natürlich wäre es auch wünschenswert, wenn man ein `Permutation<T>`-Objekt
mit dem `operator<<` auf der Konsole ausgeben kann:

```cpp
std::ostream& operator<< (std::ostream&, const Permutation<T>&);
```

Es folgen einige Beispiele, um die Arbeitsweise der Klasse `Permutation<T>` zu verdeutlichen.
Eine Permutation mit den drei Zeichen `'A'`, `'B'` und `'C'` wird so angelegt:

```cpp
Permutation<char> p{ 'A', 'B', 'C' };
std::cout << p << std::endl;
```

*Ausgabe*:

```
[A,B,C]
```

Noch ein ähnliches Beispiel mit den fünf Zahlen 1, 2, 3, 4 und 5:

```cpp
Permutation p({ 1, 2, 3, 4, 5 });
std::cout << p << " (Anzahl der Elemente: " << p.grade() << ')' << std::endl;
```

*Ausgabe*:

```
[1,2,3,4,5] (Anzahl der Elemente: 5)
```

Man beachte in dem letzten Beispiel, dass der Template Parametertyp `T` &ndash; in diesem Beispiel `int` &ndash; 
vom Übersetzer aus dem Datentyp der Parameter abgeleitet werden kann.

Es folgt noch ein Beispiel zu den Methoden `insertAtFront`, `removeAt`
und dem Index-Operator `oeprator[]`:

```cpp
Permutation p({ 1, 2, 3, 4, 5 });

std::cout << "Testing insertAtFront: " << std::endl;
p.insertAtFront(0);
std::cout << p << std::endl;

std::cout << "Testing []-Operator: " << std::endl;
for (size_t i{}; i != p.grade(); ++i)
{
    int n = p[i];
    std::cout << i << ": " << n << std::endl;
}

std::cout << "Testing removeAt: " << std::endl;
while (true) {
    p = p.removeAt(0);
    std::cout << p << std::endl;
    if (p.grade() == 0) {
        break;
    }
}
```

*Ausgabe*:

```
Testing insertAtFront:
[0,1,2,3,4,5]
Testing []-Operator:
0: 0
1: 1
2: 2
3: 3
4: 4
5: 5
Testing removeAt:
[1,2,3,4,5]
[2,3,4,5]
[3,4,5]
[4,5]
[5]
[]
```

# Klasse `PermutationContainer<T>`

Zum Abspeichern mehrerer `Permutation<T>`-Objekte konzipieren wir eine Klasse `PermutationContainer<T>`.
Im Prinzip handelt es sich bei dieser Klasse um eine Hüllenklasse,
die einen geeignet auszuwählendes STL-Container für eine beliebige Anzahl von `Permutation<T>`-Objekte kapselt.
Eine derartige Hüllenklasse ergibt Sinn,
da wir neben den Standard-Methoden der STL-Container noch einige zusätzliche Hilfsmethoden benötigen,
die speziell auf den Algorithmus zur Berechnung von Permutationen ausgelegt sind.

Damit werfen wir einen Blick auf [Tabelle 2]:

###### {#tabelle_1_class_permutation_container}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `PermutationContainer();`<br/>Standardkonstruktor für ein `PermutationContainer`-Objekt. |
| Methode `count` | `size_t count() const;`<br/>Liefert die Anzahl der `Permutation`-Elemente zurück, die im Objekt abgelegt sind. |
| Methode `insert` | `void insert(const Permutation<T>& p);`<br/>Fügt ein `Permutation`-Objekt in das `PermutationContainer`-Objekt ein. |
| Methode `insertAll` | `void insertAll(T elem);`<br/>. Ruft die Methode `insertAtFront` an allen `Permutation`-Objekten im vorliegenden `PermutationContainer`-Objekt mit dem Parameter `elem` auf.|

*Tabelle* 2: Element der Klasse `PermutationContainer<T>`.


Auch sollte der  `operator<<` für `PermutationContainer<T>`-Objekte realisiert sein,
um ein derartiges Container-Objekt auf der Konsole ausgeben zu können:

```cpp
std::ostream& operator<< (std::ostream&, const PermutationContainer<T>&);
```

Ein Beispiel zur `PermutationContainer<T>`-Klasse könnte so aussehen:

```cpp
Permutation<int> p({ 1, 2, 3, 4 });
Permutation<int> q({ 4, 3, 2, 1 });
std::cout << p << std::endl;
std::cout << q << std::endl;

PermutationContainer<int> container{};
container.insert(p);
container.insert(q);
std::cout << container << std::endl;
```

*Ausgabe*:

```
[1,2,3,4]
[4,3,2,1]
[1,2,3,4]
[4,3,2,1]
[2 permutations]
```

# Algorithmus zur Berechnung von Permutationen

Nun fehlt nur noch ein Algorithmus, um zu einer gegebenen Menge von Elementen alle Permutationen zu berechnen.
Ein sehr einfacher &ndash; rekursiver &ndash; Algorithmus lässt sich in Worten so beschreiben,
wenn _n_ die Anzahl der Elemente ist:

  * Erster Fall: _n_ = 1<br/>
    Die Menge hat nur ein Element, nennen wir es a<sub>1</sub>. Es existiert in diesem Fall nur eine einzige Permutation, bestehend aus dem Element a<sub>1</sub> selbst.

  * Zweiter Fall: _n_ > 1<br/>
    Wir bezeichnen die Elemente mit a<sub>1</sub>, a<sub>2</sub>, a<sub>3</sub>, ... , a<sub>_n_-1</sub>, a<sub>_n_</sub>: Nun ist der Reihe nach jedes einzelne Element a<sub>_i_</sub> (i = 1,2, ..., n)
    vorübergehend aus der vorliegenden Menge von _n_ Zeichen zu entfernen. Die zurückbleibenden _n_-1 Elemente werden nun mit diesem Algorithmus (rekursiv) permutiert.
    Der rekursive Methodenaufruf liefert als Ergebnis eine Menge von Permutationen zurück, die alle den Grad _n_-1 besitzen.
    Das entfernte Zeichen ist nun in diese Permutationen wieder einzufügen. Die Einfügeposition spielt dabei keine Rolle, wir entscheiden uns für den Anfang, siehe dazu auch die `insert`-Methode aus Tabelle 1.


Mit Hilfe der Vorarbeiten der zwei Klassen `Permutation<T>` und `PermutationContainer<T>` ([Tabelle 1] und [Tabelle 2]) 
können wir den vorgestellten Algorithmus etwas präziser formulieren: In Abbildung 3 finden Sie Pseudo-Code für eine Methode `calculate` vor:

[caption="Abbildung {counter:figure}: ", title="Pseudo-Code der Methode `calculate`."]
image::PermutationPseudeCode.png[width=450]

# Klasse `PermutationCalculator<T>`

Wir sind fast am Ziel angekommen: Die im letzen Abschnitt beschriebene Methode `calculate` ordnen
wir der Klasse `PermutationCalculator<T>` zu.
Die Definition in [Tabelle 3] stellt im Prinzip nur eine Wiederholung dar:




# There&lsquo;s more

Gray-Codes lassen sich sowohl mit einem rekursiven als auch mit einem iterativen Algorithmus berechnen.
Versuchen Sie, an Hand der Beschreibung des Algorithmus in [Abbildung 2] eine iterative Realisierung in C++ umzusetzen.
Die folgende [Anregung](https://www.geeksforgeeks.org/generate-n-bit-gray-codes/) könnte hierbei behilflich sein.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_permutation
[Tabelle 2]: #tabelle_1_class_permutation_container

[Listing 1]: #listing_01_graycodecalculator_decl
[Listing 2]: #listing_02_graycodecalculator_impl

[Abbildung 1]:  #abbildung_1_gray_codes_four_bits
[Abbildung 2]:  #abbildung_2_gray_codes_construction

<!-- End-of-File -->


