<!-- Partitions.md -->

In der Zahlentheorie oder in der Kombinatorik ist eine *Partition* einer natürlichen Zahl *n* eine Möglichkeit, *n* als Summe natürlicher Zahlen zu schreiben. Zwei Summen, die sich nur in der Reihenfolge ihrer Summanden unterscheiden, werden als dieselbe Partition aufgefasst. Zum Beispiel kann die natürliche Zahl 4 auf fünf verschiedene Arten aufgeteilt werden:

```
4
3 + 1
2 + 2
2 + 1 + 1
1 + 1 + 1 + 1 
```

Wir beschäftigen uns in dieser Fallstudie mit der Fragestellung, auf wie viele Arten sich eine natürliche Zahl als Summe von natürlichen Zahlen &ndash; auch _Partition_ oder _Zerlegung_ genannt &ndash; schreiben lässt und wie sich diese mit den Hilfsmitteln von *Modern C++* berechnen lassen.

<!--more--> 

# Lernziele

* STL-Klassen `std::set<T>` und `std::multiset<T>`
* Einheitliche Initialisierung
* Initialisierungsliste (`std::initializer_list<T>`)
* Container-Methoden `cbegin()` und `cend()`
* Konstruktor-Erzeugung mit `delete` unterdrücken
* In-Place Konstruktion von Objekten mit `emplace`
* Schlüsselwort `auto`
* Datentyp `size_t`

# Einführung

Wir beschäftigen uns in dieser Fallstudie mit der Fragestellung, auf wie viele Arten sich eine natürliche Zahl als Summe von natürlichen Zahlen &ndash; auch _Partition_ oder _Zerlegung_ genannt &ndash; schreiben lässt? Wir präzisieren die Fragestellung noch mit folgender Ergänzung: Zwei Zerlegungen, die sich nur in der Reihenfolge ihrer Summanden unterscheiden, gelten als gleich. Konkret: Die Zerlegungen der ersten fünf natürlichen Zahlen sehen so aus:

```
1 = 1

2 = 2
2 = 1 + 1

3 = 3
3 = 2 + 1
3 = 1 + 1 + 1

4 = 4
4 = 3 + 1
4 = 2 + 2
4 = 2 + 1 + 1

4 = 1 + 1 + 1 + 1
5 = 5
5 = 4 + 1
5 = 3 + 2
5 = 3 + 1 + 1
5 = 2 + 2 + 1
5 = 2 + 1 + 1 + 1
5 = 1 + 1 + 1 + 1 + 1
```

# Partitionen vergleichen

Unterschiedliche Zerlegungen derselben natürlichen Zahl lassen sich vergleichen. Welche Operatoren sollten Sie zu diesem Zweck
in der Klasse `Partition` implementieren? Erkennen Sie am folgenden Beispiel aller Zerlegungen der Zahl 7, wie der Vergleich zweier Partitionen definiert sein könnte?

```
7 = 7
7 = 6 + 1
7 = 5 + 2
7 = 5 + 1 + 1
7 = 4 + 3
7 = 4 + 2 + 1
7 = 4 + 1 + 1 + 1
7 = 3 + 3 + 1
7 = 3 + 2 + 2
7 = 3 + 2 + 1 + 1
7 = 3 + 1 + 1 + 1 + 1
7 = 2 + 2 + 2 + 1
7 = 2 + 2 + 1 + 1 + 1
7 = 2 + 1 + 1 + 1 + 1 + 1
7 = 1 + 1 + 1 + 1 + 1 + 1 + 1
```

Nach diesen Vorüberlegungen wollen wir nun drei Klassen `Partition`, `PartitionSet` und `PartitionCalculator`
betrachten, um mit ihrer Hilfe die Zerlegungen einer natürlichen Zahl zu berechnen.

# Die Klasse `Partition`

Die algorithmische Bestimmung aller Partitionen einer natürlichen Zahl ist keineswegs trivial,
wie man bei anfänglicher Betrachtung vielleicht glauben mag. Mithilfe des rekursiven Methodenaufrufs
lässt sich das Problem am ehesten vergleichsweise einfach lösen. Zu diesem Zweck entwerfen wir zunächst
eine Klasse `Partition`. Objekte dieser Klasse beschreiben eine einzelne Zerlegung einer natürlichen Zahl, also zum Beispiel

```
3 + 1 + 1
```

als eine mögliche Zerlegung der Zahl 5. Implementieren Sie die Klasse `Partition` anhand der Spezifikation aus [Tabelle 1].
Überlegen Sie, welcher STL-Container sich anbietet, um die einzelnen Summanden einer Partition zu verwalten.
Bedenken Sie dabei, dass man `Partition`-Objekte miteinander vergleichen können muss und aus diesem Grund
die Summanden eines solchen Objekts stets sortiert (z.B. in absteigender Reihenfolge) vorliegen sollten, um das Vergleichen zu vereinfachen.

###### {#tabelle_1_class_partition}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `Partition() = default;`<br/>Der Standardkonstruktor initialisiert ein leeres `Partition`-Objekt. |
| Benutzerdefinierter Konstruktor | `Partition(const std::initializer_list<size_t>& list);`<br/>Erzeugt ein `Partition`-Objekt auf Basis der Summanden der Initialisierungsliste `list`. |
| Benutzerdefinierter Konstruktor | `Partition(const std::vector<size_t>& vec);`<br/>Erzeugt ein `Partition`-Objekt auf Basis der Summanden eines `std::vector<size_t>`-Objekts. Dieser Konstruktor spielt vor allem im Algorithmus zur Erzeugung von Partitionen eine Rolle. |
| _getter_ `number()` | `size_t number() const;`<br/>Liefert die zur Partition gehörende natürliche Zahl zurück. |
| _getter_ `size()` | `size_t size() const;`<br/>Liefert die Anzahl der Summanden der Partition zurück. |
| _getter_ `numbers()` | `std::vector<size_t> numbers();`<br/>Liefert die einzelnen Summanden der Partition in einem `std::vector<size_t>`-Objekt zurück. |
| Operator `==` | `friend bool operator==(const Partition&, const Partition&);`<br/>Vergleicht zwei `Partition`-Objekte auf Gleichheit. Siehe dazu die Definition der Gleichheit zweier Zerlegungen in der Einführung. |
| Operatoren `<` und `>` | `friend bool operator<(const Partition&, const Partition&);`<br/>`friend bool operator>(const Partition&, const Partition&);`<br/>Vergleicht zwei `Partition`-Objekte auf &ldquo;kleiner&rdquo; oder &ldquo;größer&rdquo;. Die Art und Weise, wie Partitionen verglichen werden, wurde eingangs erläutert. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const Partition&);`<br/>Gibt ein `Partition`-Objekt auf der Konsole aus. Die Darstellung einer Partition sollte folgendes Aussehen haben:<br/>`7 = 3 + 2 + 1 + 1` |

*Tabelle* 1: Wesentliche Elemente der Klasse `Partition`.

Zur Überprüfung Ihrer Implementierung sollten die folgenden Codefragmente wie beschrieben ausführbar sein:

```cpp
Partition p1 { 2 };
std::cout << p1 << std::endl;
Partition p2{ 1, 1 };
std::cout << p2 << std::endl;
std::cout << std::boolalpha << (p1 == p2) << std::endl;
std::cout << std::boolalpha << (p1 < p2) << std::endl;
std::cout << std::boolalpha << (p1 > p2) << std::endl;
```

_Ausgabe_:

```
2 = 2
2 = 1 + 1
false
false
true
```

Oder zum Beispiel:

```cpp
Partition p3{ 1, 2, 3 };
std::cout << p3 << std::endl;
Partition p4{ 3, 2, 1 };
std::cout << p4 << std::endl;
std::cout << std::boolalpha << (p3 == p4) << std::endl;
std::cout << std::boolalpha << (p3 < p4) << std::endl;
std::cout << std::boolalpha << (p3 > p4) << std::endl;
```

_Ausgabe_:

```
6 = 3 + 2 + 1
6 = 3 + 2 + 1
true
true
false
```

Möchte man die einzelnen Zahlen einer Partition einzeln durchlaufen, zum Beispiel mit einer bereichs-basierten `for`-Schleife, dann muss die Klasse `Partition` noch um zwei Methoden `begin()` und `end()` erweitert werden, die geeignete Iteratorobjekte zurückliefern.

*Hinweis*: In der Realisierung dieser beiden Methoden
können diese auf gleichnamige Methoden des unterlagerten STL-Containers verschaltet werden:

```cpp
Partition p{ 1, 2, 3, 4, 5 };
for (const auto elem : p) {
    std::cout << elem << ' ';
}
```

_Ausgabe_:

```
5 4 3 2 1
```

# Die Klasse `PartitionSet`

Die Menge aller Partitionen einer natürlichen Zahl wird in einem Objekt der Klasse `PartitionSet` zusammengefasst.
Es ergibt keinen Sinn, eine bestimmte Partition mehrfach in einem `PartitionSet`-Objekt abzulegen.
Mit welchem STL-Container lässt sich diese Anforderung leicht realisieren? Weitere Details zur Klasse `PartitionSet` siehe [Tabelle 2]:

###### {#tabelle_2_class_partitionset}

| Element | Beschreibung |
| :---- | :---- |
| Benutzerdefinierter Konstruktor | `PartitionSet(size_t number);`<br/>Erzeugt ein `PartitionSet`-Objekt zur natürlichen Zahl `number`. Die einzelnen `Partition`-Objekte, deren Berechnung noch aussteht, sind mit der `insert`-Methode in die Partitionenliste des aktuellen Objekts aufzunehmen, siehe dazu weiter unten. |
| _getter_ `number()` | `size_t number() const;`<br/>Liefert die natürliche Zahl zurück, deren Partitionen betrachtet werden. |
| _getter_ `size()` | `size_t size() const;`<br/>Liefert die Anzahl der `Partition`-Objekte in der Partitionenmenge zurück. |
| Methode `insert()` | `bool insert(const Partition& p);`<br/>Fügt die Partition `p` in die aktuelle Partitionenmenge ein. Zu beachten: Eine Partition darf in der Menge nicht mehrfach enthalten sein. `insert` liefert `false` zurück, wenn die Partition `p` bereits in der Partitionenliste des Objekts enthalten ist, andernfalls `true`. |
| Methode `emplace()` | `template <typename ... Args>`<br/>`bool emplace(Args&& ... args);`<br/>Fügt eine Partition in die aktuelle Partitionenmenge mit einer so genannten _In-Place_ Konstruktion ein. Die `emplace`-Methode muss auf Grund dessen mit einer variablen Anzahl von `size_t`-Werten aufrufbar sein, für die der unterlagerte STL-Container mit einem geeigneten Konstruktor der `Partition`-Klasse ein entsprechendes Objekt _in-place_ konstruiert. Dies setzt voraus, dass der gewählte STL-Container für die Partitionenmenge eine `emplace`-Methode besitzt. Der Rückgabewert spezifiziert, ob die Partition in der Partitionenmenge bereits enthalten war oder nicht.<br/><br/>_Hinweis_: Konstante Literale wie 1, 2, 3 usw. sind per Sprachdefinition C++ Literale des Datentyps `int`. Wenn die Klasse `Partition` intern mit `size_t`-Werten arbeitet, müssen derartige `int`-Literale in der Realisierung von `emplace` nach `size_t` konvertiert werden. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const PartitionSet&);`<br/>Gibt ein `PartitionSet`-Objekt auf der Konsole aus. Die Ausgabe sollte – am Beispiel der Zahl 3 gezeigt – folgendes Aussehen haben:<br/>`1: 3 = 3`<br/>`2: 3 = 2 + 1`<br/>`3: 3 = 1 + 1 + 1` |

*Tabelle* 2: Wesentliche Elemente der Klasse `PartitionSet`.

Die Klasse `PartitionSet` aus [Tabelle 2] ist noch nicht in der Lage, die Partitionen zu einer beliebigen natürlichen Zahl zu berechnen. Darauf kommen wir im folgenden Abschnitt zu sprechen. Die prinzipielle Funktionsweise der Klasse `PartitionSet` lässt sich aber schon mal &ldquo;manuell&rdquo; testen:

```cpp
PartitionSet set{ 3 };
set.insert({ 3 });
set.insert({ 1, 2 });
set.insert({ 1, 1, 1 });
std::cout << "Partitions of " << set.number() << ": " << std::endl;
std::cout << set << std::endl;
```

_Ausgabe_:

```
Partitions of 3:
1: 3 = 3
2: 3 = 2 + 1
3: 3 = 1 + 1 + 1
[3 partitions]
```

Wenn Sie in diesem Beispiel die Anzahl der Konstruktorenaufrufe der `Partition`-Objekte zählen,
werden Sie feststellen, dass pro `insert`-Methodenaufruf an einem `PartitionSet`-Objekt zwei `Partition`-Objekte erzeugt werden:

* Ein erstes als Parameter des `insert`-Methodenaufrufs.
* Ein zweites beim Einfügen in den STL-Container der `PartitionSet`-Klasse.

Unter Verwendung der `emplace`-Methode, die von den meisten STL-Containerklassen bereitgestellt wird, erreicht man, dass in so einer Situation ein `Partition`-Objekt nur ein einziges Mal angelegt wird. Das heißt zunächst einmal, dass die `insert`-Methode in ihrer betrachteten Form so nicht zum Zuge kommen kann. Genau die Erzeugung dieses `Partition`-Objekts, das als Parameter an `insert` übergeben wird, gilt es ja gerade zu vermeiden. Dies wiederum hat zur Folge, dass alle Parameter, die man zur Erzeugung eines `Partition`-Objekts benötigt, an eine entsprechende Methode an der `PartitionSet`-Klasse zu übergeben sind. Wir nennen diese Methode sinnigerweise ebenfalls `emplace`.

Damit sind wir bei variadischen Templates angekommen, um mit ihrer Hilfe beliebig viele `size_t`-Werte (die Zahlen, aus denen eine Partition besteht) 
geeignet an eine Methode der `PartitionSet`-Klasse übergeben zu können:

```cpp
PartitionSet set{ 4 };
set.emplace(4);
set.emplace(3, 1);
set.emplace(2, 2);
set.emplace(2, 1, 1);
set.emplace(1, 1, 1, 1);

std::cout << "Partitions of " << set.number() << ": " << std::endl;
std::cout << set << std::endl;
```

_Ausgabe_:

```
Partitions of 4:
1: 4 = 4
2: 4 = 3 + 1
3: 4 = 2 + 2
4: 4 = 2 + 1 + 1
5: 4 = 1 + 1 + 1 + 1
[5 partitions]
```

Erkennen Sie zwischen den Aufrufen der `emplace`- und der `insert`-Methode einen Unterschied? Richtig erkannt: Die `insert`-Aufrufe nehmen ein `std::initializer_list<size_t>`-Objekt entgegen, deshalb müssen zwischen den runden Klammern noch geschweifte Klammern stehen. Die `emplace`-Aufrufe sind mit einer variablen Anzahl von Parametern konzipiert (präziser formuliert: als _Parameter Pack_). Hier sind geschweifte Klammern nicht notwendig und als solche syntaktisch auch gar nicht zulässig. Wir testen zusätzlich noch, dass dieselbe Partition nicht mehrfach einem `PartitionSet`-Objekt hinzugefügt werden kann:

```cpp
PartitionSet set{ 4 };
bool b;

b = set.insert({ 2, 1, 1 });
std::cout << std::boolalpha << b << std::endl;
b = set.insert({ 1, 2, 1 });
std::cout << std::boolalpha << b << std::endl;
b = set.insert({ 1, 1, 2 });
std::cout << std::boolalpha << b << std::endl;

std::cout << "Partitions of " << set.number() << ": " << std::endl;
std::cout << set << std::endl;
```

_Ausgabe_:

```
true
false
false
Partitions of 4:
1: 4 = 2 + 1 + 1
[1 partitions]
```

# Rekursive Berechnung aller Partitionen einer natürlichen Zahl

Wir kommen nun auf das Kernstück der Aufgabe zu sprechen, die algorithmische Berechnung aller Partitionen zu einer vorgegebenen natürlichen Zahl. Ist _n_ die zu Grunde liegende natürliche Zahl, so gehen wir davon aus, dass mittels Rekursion die Menge aller Partitionen der Zahl _n_ - 1 bereits vorliegt. Da für _n_ = 1 diese Berechnung trivial ist, stellt diese Annahme keine Einschränkung dar!

Haben wir alle Partitionen der Zahl _n_ - 1 vorliegen, so berechnen wir wie folgt alle Partitionen der Zahl _n_: Wir nehmen eine beliebige Partition der Zahl _n_ - 1 zur Hand. Ihre Anzahl der Summanden sei _m_. Wenn wir nun der Reihe nach zu jedem einzelnen dieser _m_ Summanden den Wert 1 addieren, erhalten wir auf einen Schlag _m_ Partitionen der Zahl _n_! Um es am folgenden Beispiel zu demonstrieren: Ist

```
4 + 2 + 2
```

eine Partition der Zahl 8, so erhalten wir sofort die drei Partitionen

```
(4+1) + 2 + 2 = 5 + 2 + 2
4 + (2+1) + 2 = 4 + 3 + 2
4 + 2 + (2+1) = 4 + 2 + 3 = 4 + 3 + 2
```

der natürlichen Zahl 9. Der einzige Nachteil dieses Ansatzes ist bereits erkennbar:
Wir können auf diese Weise mehrfach dieselbe Partition erhalten, wie das Beispiel zeigt. Dies stellt aber kein echtes Problem dar. Wir müssen bei der Konstruktion der Partitionenmenge nur darauf achten, dass beim Einfügen neu berechneter Partitionen diese nicht schon in der vorhandenen Partitionenmenge enthalten sind.

Man kann sich leicht überlegen, dass bei vorliegender Partitionenmenge einer Zahl _n_ - 1 auf diese Weise alle Partitionen der Zahl _n_ berechnet werden – mit einer Ausnahme: Die Partition

```
1 + 1 + ... + 1    // n Summanden
```

wird nicht konstruiert, da bei allen berechneten Partitionen mindestens ein Summand immer den Wert 2 besitzt. In der Tat ist die fehlende Partition einer Zahl _n_, die aus _n_ 1-en besteht, noch nachträglich in die Partitionenmenge aufzunehmen. In [Listing 1] finden Sie eine Beschreibung des Algorithmus in Gestalt von Pseudocode vor:

###### {#pseudocode_listing_algorithm}

**Methode**: `Calculate`
**Input**: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Zahl *n*
**Output**: &nbsp;&nbsp;`PartitionSet`-Objekt mit allen Partitionen der Zahl *n*

**if** *n* = 1 **then**

> **return** `PartitionSet`-Objekt mit Zerlegung `{ 1 }`

**else**

> Berechne rekursiv `PartitionSet`-Objekt *P*<sub>*n* - 1</sub> zur Zahl *n* - 1:
> `PartitionSet` *P*<sub>*n* - 1</sub> = `calculate` (*n* - 1)
> *P*<sub>result</sub> = leeres `PartitionSet`-Objekt

> **for all** p &#x2208; *P*<sub>*n* - 1</sub> **do**<br/>

> > Berechne *m* Kandidaten für eine Partition von *n* (*m* Anzahl der Summanden von *p*) durch sukzessive Addition von 1 auf die einzelnen Summanden
> > Füge Kandidaten in *P*<sub>result</sub> ein, wenn dieser noch nicht in *P*<sub>result</sub> enthalten ist

> **endfor**

> Erzeuge Partition *P*<sub>1</sub> der Länge *n* (Summanden alle gleich 1)
> Füge Partition *P*<sub>1</sub> in *P*<sub>result</sub> ein
> **return** *P*<sub>result</sub>

**endif**

*Listing* 1: Pseudocode zur Berechnung aller Partitionen einer natürlichen Zahl.

Implementieren Sie in diesem Abschnitt eine Methode `calculate` zur Berechnung aller Partitionen einer natürlichen Zahl
und ordnen Sie diese einer separaten Klasse `PartitionsCalculator` zu ([Tabelle 3]):

###### {#tabelle_3_class_partitionscalculator}

| Methode | Beschreibung |
| :---- | :---- |
| `calculate()` | `static PartitionSet calculate(size_t n);`<br/>Berechnet die Menge aller Partitionen der Zahl _n_ anhand des in [Listing 1] beschriebenen Algorithmus. Das Ergebnis wird durch den Rückgabewert (Objekt vom Typ `PartitionSet`) zurückgeliefert. |

*Tabelle* 3: Elemente der Klasse `PartitionsCalculator`.

Es folgt ein Beispielfragment zum Testen Ihrer Realisierung der Klasse `PartitionsCalculator`:

```cpp
PartitionSet set = PartitionCalculator::calculate(6);
std::cout << "Partitions of " << set.number() << ": " << std::endl;
std::cout << set << std::endl;
```

_Ausgabe_:

```
Partitions of 6:
 1: 6 = 6
 2: 6 = 5 + 1
 3: 6 = 4 + 2
 4: 6 = 4 + 1 + 1
 5: 6 = 3 + 3
 6: 6 = 3 + 2 + 1
 7: 6 = 3 + 1 + 1 + 1
 8: 6 = 2 + 2 + 2
 9: 6 = 2 + 2 + 1 + 1
10: 6 = 2 + 1 + 1 + 1 + 1
11: 6 = 1 + 1 + 1 + 1 + 1 + 1
[11 partitions]
```

# Anzahl der Partitionen

Die Anzahl der Partitionen einer natürlichen Zahl haben Sie im letzten Teilschritt als Nebeneffekt berechnet. Es gibt aber auch eine alternative Möglichkeit mit Hilfe einer rekursiven Formel, also ohne die Partitionen selbst bestimmen zu müssen. Wir führen zu diesem Zweck die Bezeichnung _sum_(_n_) für die gesuchte Anzahl ein. Ferner sei _b_(_n_, _m_) die Anzahl der Zerlegungen von _n_, in denen der größte Summand gleich _m_ ist. Also an einem Beispiel erläutert: In der Menge aller Partitionen von 5

```
1: 5 = 5
2: 5 = 4 + 1
3: 5 = 3 + 2
4: 5 = 3 + 1 + 1
5: 5 = 2 + 2 + 1
6: 5 = 2 + 1 + 1 + 1
7: 5 = 1 + 1 + 1 + 1 + 1
```

finden wir insgesamt _sum_(5) = 7 Zerlegungen vor. Für die Anzahl der Zerlegungen von 5, in denen der größte Summand gleich _m_ (_m_ = 1, 2, 3, 4 und 5) ist, gilt hier

```
b(5,1) = 1
b(5,2) = 2
b(5,3) = 2
b(5,4) = 1
b(5,5) = 1
```

Offensichtlich gilt nun

_sum_(_n_) = _b_(_n_,1) + _b_(_n_,2) + _b_(_n_,3) + .... + _b_(_n_,_n_-1) + _b_(_n_,_n_)

Weiter muss man nicht gehen, denn _b_(_n_,_n_+1), _b_(_n_,_n_+2) sind ja alle 0. Bleibt noch die Frage nach der Berechnung von _b_(_n_,_m_). Hier gilt folgende rekursive Formel:

_b_(_n_,_m_) = _b_(_n_-1,_m_-1) + _b_(_n_-_m_,_m_)

Wenn Sie die folgenden Anfangsbedingungen berücksichtigen, von deren Korrektheit man sich leicht überzeugen kann, steht einer einfachen, direkten Umsetzung in eine rekursive Methode `numberOfPartitions` ([Tabelle 4]) nichts mehr im Wege:

###### {#tabelle_4_class_partitionscalculator_02}

| Methode | Beschreibung |
| :---- | :---- |
| `numberOfPartitions` | `static size_t numberOfPartitions(size_t n, size_t maxSummand);`<br/>Berechnet die Anzahl aller Partitionen zur Zahl _n_, die einen maximalen Summanden _maxSummand_ besitzen. |
| `numberOfPartitions` | `static size_t numberOfPartitions(size_t n);`<br/>Berechnet die Anzahl aller Partitionen zur Zahl _n_. |

*Tabelle* 4: Zwei Überladungen der Methode `numberOfPartitions` in der Klasse `PartitionsCalculator`.

Für die Zahlen von 1 bis 20 ergeben sich folgende Anzahlen an Partitionen:

```cpp
for (size_t i = 1; i != 21; ++i) {
    std::cout 
        << "Number partitions of " << i
        << ": " << PartitionCalculator::numberPartitions(i)
        << std::endl;
}
```

_Ausgabe_:

```
Number partitions of 1: 1
Number partitions of 2: 2
Number partitions of 3: 3
Number partitions of 4: 5
Number partitions of 5: 7
Number partitions of 6: 11
Number partitions of 7: 15
Number partitions of 8: 22
Number partitions of 9: 30
Number partitions of 10: 42
Number partitions of 11: 56
Number partitions of 12: 77
Number partitions of 13: 101
Number partitions of 14: 135
Number partitions of 15: 176
Number partitions of 16: 231
Number partitions of 17: 297
Number partitions of 18: 385
Number partitions of 19: 490
Number partitions of 20: 627
```

# Lösung

Wir gehen zunächst auf die Klasse `Partition` ein. Da die Zahlen einer Partition mehrfach auftreten dürfen,
bietet sich als Container eine Instanz der Klasse `std::multiset` an. In der Ausgabe einer Partition auf der Konsole sollten die Zahlen in absteigender Reihenfolge aufgelistet werden, für die Vergleichsfunktion greifen wir deshalb auf das Funktionsobjekt `std::greater<size_t>` zurück. Eine Definition der `Partition`-Klasse sieht so aus:

###### {#listing_class_partition_decl}

```cpp
01: class Partition
02: {
03: private:
04:     std::multiset<size_t, std::greater<size_t>> m_numbers;
05:     size_t m_number{ };
06: 
07: public:
08:     // c'tor(s)
09:     Partition() = default;
10:     Partition(const std::initializer_list<size_t>&);
11:     Partition(const std::vector<size_t>&);
12: 
13:     // getter
14:     size_t number() const { return m_number; }
15:     size_t size() const { return m_numbers.size(); }
16:     std::vector<size_t> numbers() const;
17: 
18:     // operators
19:     friend bool operator==(const Partition&, const Partition&);
20:     friend bool operator<(const Partition&, const Partition&);
21:     friend bool operator>(const Partition&, const Partition&);
22: 
23:     // iterator support
24:     std::multiset<size_t, std::greater<size_t>>::const_iterator begin() {
25:         return m_numbers.cbegin(); 
26:     }
27:     std::multiset<size_t, std::greater<size_t>>::const_iterator end() {
28:         return m_numbers.cend(); 
29:     }
30: 
31:     // output
32:     friend std::ostream& operator<< (std::ostream&, const Partition&);
33: };
```

*Listing* 2: Klasse `Partition`: Definition.

In Zeile 5 von [Listing 2] finden wir einen Initialisierer für eine Instanzvariable vor. In diesem Fall kann man dann den Default-Konstruktor mit `default` definieren.

In den Zeilen 24 und 27 werden eine `begin()` und `end()`-Methode definiert, um `Partition`-Objekte iterieren zu können. Darunter verstehen wir, dass wir in einer bereichs-basierten `for`-Schleife die einzelnen Zahlen der Partition traversieren können. Eine Iterator-Unterstützung ist einfach zu realisieren, wenn wir die Iteratorimplementierung eines unterlagerten STL-Containers zur Verfügung stehen haben. In unserem Fall ist dies das `std::multiset<size_t, std::greater<size_t>>`-Objekt, dessen `begin()` und `end()`-Methode uns die gewünschten Iteratorobjekte zurückliefern. Die Definitionen in den Zeilen 24 und 27 hätte man auch kürzer und damit einfacher lesbarer gestalten können:

```cpp
auto begin() { return m_numbers.cbegin(); }
auto end() { return m_numbers.cend(); }
```

Wenn wir den Typ einer Variable oder wie in unserem Fall, den Rückgabetyp einer Methode, mit `auto` definieren, bestimmt der Übersetzer den tatsächlichen Typ aus dem Kontext. Die beiden Methoden liefern also Objekte des Typs `std::multiset<size_t, std::greater<size_t>>::const_iterator` zurück, nur ist die Lesbarkeit mit `auto` doch um ein Vielfaches angenehmer. Damit sind wir schon bei der Implementierung der Klasse `Partition` angekommen:

###### {#listing_class_partition_impl}

```cpp
01: // c'tor(s)
02: Partition::Partition(const std::initializer_list<size_t>& list)
03:     : m_numbers{ list.begin(), list.end() }
04: {
05:     m_number = std::accumulate(m_numbers.cbegin(), m_numbers.cend(), static_cast<size_t>(0));
06: }
07: 
08: Partition::Partition(const std::vector<size_t>& numbers)
09:     : m_numbers{ numbers.cbegin(), numbers.cend() } 
10: {
11:     m_number = std::accumulate(m_numbers.cbegin(), m_numbers.cend(), static_cast<size_t>(0));
12: }
13: 
14: // getter
15: std::vector<size_t> Partition::numbers() const {
16:     std::vector<size_t> result;
17:     result.assign(m_numbers.begin(), m_numbers.end());
18:     return result;
19: }
20: 
21: // operators
22: bool operator==(const Partition& p1, const Partition& p2)
23: {
24:     // partitions of different numbers can't be compared
25:     if (p1.number() != p2.number())
26:         throw std::invalid_argument(std::string("Partitions don't belong to same number!"));
27: 
28:     // partitions with a different number of summands can't be equal
29:     if (p1.size() != p2.size())
30:         return false;
31: 
32:     // compare all summands - sets are  sorted
33:     return (p1.m_numbers == p2.m_numbers);
34: }
35: 
36: bool operator<(const Partition& p1, const Partition& p2)
37: {
38:     // partitions of different numbers can't be compared
39:     if (p1.number() != p2.number())
40:         throw std::invalid_argument(std::string("Partitions don't belong to same number!"));
41: 
42:     std::multiset<size_t>::iterator it1 = p1.m_numbers.cbegin();
43:     std::multiset<size_t>::iterator it2 = p2.m_numbers.cbegin();
44: 
45:     while (it1 != p1.m_numbers.cend() && it2 != p2.m_numbers.cend()) {
46: 
47:         if ((*it1) > (*it2))
48:             return false;
49:         if ((*it1) < (*it2))
50:             return true;
51: 
52:         ++it1;
53:         ++it2;
54:     }
55: 
56:     return true; // wird das erreicht ????????????
57: }
58: 
59: bool operator>(const Partition& p1, const Partition& p2)
60: {
61:     return !(p1 < p2);
62: }
63: 
64: // output
65: std::ostream& operator<< (std::ostream& os, const Partition& p)
66: {
67:     os << p.m_number << " = ";
68:     if (p.m_numbers.begin() != p.m_numbers.end()) {
69: 
70:         std::multiset<size_t>::const_iterator it = p.m_numbers.begin();
71:         std::multiset<size_t>::const_iterator penultimate = std::prev(p.m_numbers.end());
72:         for (it = p.m_numbers.begin(); it != penultimate; ++it) {
73:             os << (*it) << " + ";
74:         }
75:         os << (*penultimate) << ' ';
76:     }
77:     return os;
78: }
```

*Listing* 3: Klasse `Partition`: Implementierung.

Der `std::accumulate`-Algorithmus in den Zeilen 5 und 11 liefert mit den jeweiligen Parametern die Summe aller Werte des Bereichs zurück. Der Aufruf von `std::vector<size_t>::assign()` (Zeile 17) weist dem Vektor neue Elemente zu, indem die alten (sofern vorhanden) ersetzt werden. In Zeile 33 wird der Inhalt zweier `std::vector<size_t>`-Objekte auf Gleichheit überprüft, sprich sie müssen die gleiche Anzahl von Elementen haben und jedes Element des ersten Vektors wird mit dem Element des zweiten Vektors an derselben Position verglichen.

Zur Verwaltung der `Partition`-Objekte gibt es die Klasse `PartitionSet`:

###### {#listing_class_partitionset_decl}

```cpp
01: class PartitionSet {
02: 
03: private:
04:     std::set<Partition, std::greater<Partition>> m_partitions;
05:     size_t m_number{ };
06: 
07: public:
08:     // c'tors/d'tor
09:     PartitionSet() = delete;
10:     PartitionSet(size_t);
11: 
12:     // properties
13:     size_t number() const { return m_number; }
14:     size_t size() const { return m_partitions.size(); };
15: 
16:     // public interface
17:     bool insert(const Partition&);
18: 
19:     template <typename ... Args>
20:     bool emplace(Args&& ... args) {
21: 
22:         // error handling
23:         std::initializer_list<size_t> list =
24:             std::initializer_list<size_t>{ static_cast<size_t>(args)... };
25: 
26:         size_t number = std::accumulate(list.begin(), list.end(), static_cast<size_t>(0));
27:         if (number != m_number) {
28:             throw std::invalid_argument("Number of partition doesn't match set!");
29:         }
30: 
31:         auto result = m_partitions.emplace(Partition{ static_cast<size_t>(args) ... });
32: 
33:         return std::get<1>(result);
34:     }
35: 
36:     // iterator support
37:     std::set<Partition, std::greater<Partition>>::const_iterator begin() {
38:         return m_partitions.cbegin(); 
39:     }
40:     std::set<Partition, std::greater<Partition>>::const_iterator end() {
41:         return m_partitions.cend(); 
42:     }
43: 
44:     // output
45:     friend std::ostream& operator<< (std::ostream&, const PartitionSet&);
46: };
```

*Listing* 4: Klasse `PartitionSet`: Definition.

Der Default-Konstruktor ergibt bei dieser Klasse wenig Sinn. Es sollte in Minimalfall immer die natürliche Zahl, um deren Zerlegungen es geht, bekannt sein. Deshalb wird in Zeile 9 ([Listing 4]) der Default-Konstruktor mit dem Schlüsselwort `delete` markiert, die Klasse besitzt folglich *keinen* Standard-Konstruktor. Für die Realisierung der `emplace`-Methode (Zeile 20) kommt das Feature der &ldquo;*Template Member Function*&rdquo; zum Einsatz. Ferner findet die Implementierung
im Header-File statt, da dies bei Templates der einfachste Ansatz ist.

In Zeile 24 von [Listing 4] findet die so genannte _Parameter Pack Expansion_ statt (`static_cast<size_t>(args)...`). Es handelt sich um die drei nachgestellten Punkte (`...`) nach dem Parameter `args`. Wir wenden die  _Parameter Pack Expansion_ an, um alle Parameter in einem `std::initializer_list<size_t>`-Objekt zusammenzufassen. Dieses Objekt verwenden wir zur Fehlerüberprüfung (Zeile 26) und berechnen mit `std::accumulate` die Summe der Parameter. Den auf diese Weise erhaltenen Wert vergleichen wir in Zeile 27 mit `m_number` auf Übereinstimmung. Bei Nicht-Übereinstimmung werfen wir ein `std::invalid_argument`-Objekt und verlassen die `emplace`-Methode vorzeitig.

In Zeile 31 führen wir eine zweite _Parameter Pack Expansion_ aus, um damit *_*in-place* ein `Partition`-Objekt zu erzeugen, das wir an die `emplace`-Methode des `std::multiset<size_t, std::greater<size_t>>`-Objekts durchschleusen. Der Rückgabewert von `emplace` ist vom Typ `std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool>`. Hier interessiert uns nur der zweite Wert des Paares. Er gibt an, ob die Partition bereits in der Partitionenmenge vorhanden war oder nicht. Für den Zugriff auf `std::pair<>`-Objekte gibt es die `std::get<>`-Methode, der Template Parameter muss vom Typ `int` sein. Für die Realisierung der `PartitionSet`-Klasse im _.cpp_-File bleiben nur noch ein Konstruktor, die `insert`-Methode und der Ausgabeoperator übrig:

###### {#listing_class_partitionset_impl}

```cpp
01: // c'tors
02: PartitionSet::PartitionSet(size_t number) : m_number{ number } {}
03: 
04: // public interface
05: bool PartitionSet::insert(const Partition& p) {
06: 
07:     if (p.number() != m_number) {
08:         throw std::invalid_argument("Number of partition doesn't match set!");
09:     }
10: 
11:     std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result = m_partitions.insert(p);
12:     return std::get<1>(result);
13: }
14: 
15: // output
16: std::ostream& operator<< (std::ostream& os, const PartitionSet& set)
17: {
18:     std::for_each(
19:         std::begin(set.m_partitions), 
20:         std::end(set.m_partitions),
21:         [&, n = 1](const Partition& p) mutable {
22:             os << std::setw(3) << n << ": " << p << std::endl;
23:             ++n;
24:         }
25:     );
26:     os << '[' << set.size() << " partitions]" << std::endl;
27:     return os;
28: }
```

*Listing* 5: Klasse `PartitionSet`: Implementierung.

Die Implementierung der `insert`-Methode (Zeilen 5 bis 14) hätte man auch kürzer gestalten können. Es ging mir darum, zum einen diese Methode mit einem Rückgabewert (Partition schon vorhanden oder nicht) und mit einer Fehlerüberprüfung (Partition und Partitionenmenge passen zusammen oder nicht) auszustatten.

Die Methoden zum Berechnen aller Partitionen einer natürlichen Zahl sind vom Charakter her eher funktional ausgelegt, in der Klasse `PartitionCalculator` finden sich daher nur statische Klassenmethoden vor:

###### {#listing_class_partitioncalculator_decl}

```cpp
01: class PartitionCalculator
02: {
03: public:
04:     // c'tor
05:     PartitionCalculator() = delete;
06: 
07:     // public interface
08:     static PartitionSet calculate(size_t n);
09:     static size_t numberPartitions(size_t number);
10:     static size_t numberPartitions(size_t number, size_t maxSummand);
11: };
```

*Listing* 6: Klasse `PartitionCalculator`: Definition.

Mit dem `delete`-Schlüsselwort in Zeile 5 stellen wir sicher, dass die `PartitionCalculator`-Klasse keinen Standard-Konstruktor besitzt. Da sie auch keine anderen Konstruktoren hat, lassen sich also keine `PartitionCalculator`-Objekte erzeugen, was unser Entwurfsziel war.

###### {#listing_class_partitioncalculator_impl}

```cpp
01: // public interface
02: PartitionSet PartitionCalculator::calculate(size_t number)
03: {
04:     PartitionSet result{ number };
05: 
06:     if (number == 1) {
07:         Partition p{ 1 };
08:         result.insert(p);
09:     }
10:     else {
11:         PartitionSet setMinusOne = calculate(number - 1);
12: 
13:         for (const auto& p : setMinusOne) {
14: 
15:             std::vector<size_t> numbers = p.numbers();
16:             for (size_t j = 0; j != numbers.size(); j++) {
17:                 numbers[j]++;
18:                 Partition q{ numbers };
19:                 result.insert(q);
20:                 numbers[j]--;
21:             }
22:         }
23: 
24:         // create missing partition (just consisting of '1's)
25:         std::vector<size_t> ones(number, 1);
26:         Partition pOnes{ ones };
27:         result.insert(pOnes);
28:     }
29: 
30:     return result;
31: }
32: 
33: size_t PartitionCalculator::numberPartitions(size_t number)
34: {
35:     if (number < 1)
36:         return 0;
37: 
38:     size_t total = 0;
39:     for (int maxSummand = 1; maxSummand <= number; maxSummand++)
40:         total += numberPartitions(number, maxSummand);
41: 
42:     return total;
43: }
44: 
45: size_t PartitionCalculator::numberPartitions(size_t number, size_t maxSummand)
46: {
47:     if (maxSummand > number) {
48:         return 0;
49:     }
50:     else if (maxSummand == 0) {
51:         return 0;
52:     }
53:     else if (maxSummand == 1) {
54:         return 1;
55:     }
56:     else {
57:         return
58:             numberPartitions(number - 1, maxSummand - 1) +
59:             numberPartitions(number - maxSummand, maxSummand);
60:     }
61: }
```

*Listing* 7: Klasse `PartitionCalculator`: Implementierung.

Die Aufruf von Konstruktoren der Klasse `std::vector<T>` kann manchmal leicht verwirrend sein. In Zeile 25 wird ein `std::vector<size_t>`-Objekt mit `number` Elementen vom Wert `1` erzeugt.

# There&lsquo;s more

Das Thema &ldquo;Aufzählen&rdquo; &ndash; in unserem Fall &ldquo;Partitionen aufzählen&rdquo; &ndash; tritt immer bei Klassen in Erscheinung, deren Struktur gewisse Ähnlichkeiten mit einem Container hat. Ergänzen Sie Ihre Implementierung der Klasse `PartitionSet` entsprechend.

_Beispielfragment_:

```
PartitionSet set = PartitionCalculator::calculate(5);
for (const Partition& p : set) {
    std::cout << p << std::endl;
}
```

_Ausgabe_:

```
5 = 5
5 = 4 + 1
5 = 3 + 2
5 = 3 + 1 + 1
5 = 2 + 2 + 1
5 = 2 + 1 + 1 + 1
5 = 1 + 1 + 1 + 1 + 1
```

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_partition
[Tabelle 2]: #tabelle_2_class_partitionset
[Tabelle 3]: #tabelle_3_class_partitionscalculator
[Tabelle 4]: #tabelle_4_class_partitionscalculator_02

[Listing 1]: #pseudocode_listing_algorithm

[Listing 2]: #listing_class_partition_decl
[Listing 3]: #listing_class_partition_impl
[Listing 4]: #listing_class_partitionset_decl
[Listing 5]: #listing_class_partitionset_impl
[Listing 6]: #listing_class_partitioncalculator_decl
[Listing 7]: #listing_class_partitioncalculator_impl

[Abbildung 1]: #abbildung_1_imgage_pseudocode_partitions_calculator

<!-- End-of-File -->
