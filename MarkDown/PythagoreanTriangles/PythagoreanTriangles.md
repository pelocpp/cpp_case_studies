<!-- Pythagorean Triangles -->

// TODO: Geht das was mit genrate .... oder siehe auch das Collatz - Pronlem ....

// TODO: Das Triple machen wir doch mit einem std::tuple

// TODO : Ab 23 gibt es eine thread sichere Ausgabe !!!

Und wieder steht etwas Schulmathematik auf dem Programm, dieses Mal geht es um &bdquo;rechtwinklige Dreiecke&rdquo;
Für derartige Rechtecke gibt es den Satz von Pythagoras, er trifft eine Aussage für die drei Seitenlängen eines solchen Dreiecks.

Wir wollen im Folgenden nur solche Rechtecke betrachten, deren Seitenlängen ganzzahlig sind.

Schreiben Sie ein C++&ndash;Programm, das für folgende Fragestellung eine Antwort findet:

Für welchen Umfang *p* mit *p* <= 2000 ist die Anzahl der verschiedenen rechwinkligen Dreiecke
mit ganzzahligen Seitenlängen *a*, *b* und *c* am größten?


Hinweis: Die Aufgabenstellung stammt aus dem Repository &bdquo;Project Euler&rdquo;:
*Project Euler* ist eine englischsprachige Website. Sie enthält eine Reihe von Problemstellungen,
die mithilfe von Mathematik und Programmierung gelöst werden können. Die Aufgabenstellung dieser Fallstudie
finden Sie unter &bdquo;Problem 39&rdquo;.

e sich sicherlich auch kürzer und direkter erzielen, nur würden wir dabei keinen Lerneffekt erreichen.

<!--more-->

# Lernziele

  * Klasse `std::function<T>`
  * Container `std::vector<T>`
  * `if`-Anweisung mit *Initializer*
  * Algorithmen `std::for_each`, `std::begin`, `std::end`


  * Lambda-Funktionen mit Zugriffsklausel
  * Initialisierungsliste
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Für rechtwinklige Dreiecke gibt es den Satz des Pythagoras. Dieser besagt, dass
für die drei Seiten a, b und c die Beziehung *a*<sup>2</sup> + *b*<sup>2</sup> = *c*<sup>2</sup> gilt.
Dabei steht *c* für die Hypotenuse, sie ist die längste Seite eines rechtwinkligen Dreiecks und liegt dem rechten Winkel gegenüber.
Als Kathete werden die beiden kürzeren Seiten in einem rechtwinkligen Dreieck bezeichnet.



###### {#abbildung_1_gray_codes_four_bits}

{{< figure src="/img/graycodes/GrayCodes01.png" width="50%" >}}

RightTriangle.png

*Abbildung* 1: Rechtwinkliges Dreick mit Hypotenuse und Kateten.


Der Umfang *p* (engl: *perimeter*) eines rechwinkligen Dreieckes berechnet sich zu *p* = *a* + *b* + *c*. 

Das  Problem 39 aus dem *Project Euler* lautet nun:
Für welchen Umfang *p* mit *p* <= 2000 ist die Anzahl der verschiedenen rechwinkligen Dreiecke
mit ganzzahligen Seitenlängen *a*, *b* und *c* am größten?

*Beispiel*:
Betrachten wir den Umfang *p* = 120:
Die drei Tripel { 20, 48, 52 }, { 24, 45, 51 } und { 30, 40, 50 } sind die einzigen drei Tripel, die mit ganzzahligen Werten ein rechtwinkliges Dreieck des Umfangs *p* = 120 beschreiben.

*Hinweise*:
Mit Hilfe der beiden Gleichungen *a*<sup>2</sup> + *b*<sup>2</sup> = *c*<sup>2</sup> und *p* = *a* + *b* + *c* lässt
sich auf recht einfache Weise eine Methode mit einigen wenigen geschachtelten Kontrollstrukturen entwerfen,
die alle in Frage kommenden Tripel (*a*, *b*, *c*) berechnet.






// ALT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Die Besonderheit des Gray-Codes liegt darin,
dass sich benachbarte Zahlenketten nur in genau einem Bit unterscheiden.
Dies gilt auch für den Übergang vom 2<sup>*n*</sup>-1.-ten Code zum 0.-ten Code:

*Definition*: Eine Folge aller 2<sup>*n*</sup> Bitketten der Länge n (n &geq; 1) heißt ein *Gray-Code* der Länge *n*,
falls sich jeweils 2 benachbarte Bitketten in nur einer Bitposition unterscheiden.

Diese Eigenschaft kommt vielen Anwendungen zu Gute, wie wir beispielsweise an einem Inkrementalgeber erörtern können.
Würde ein Inkrementalgeber eine herkömmliche Binärzahl (im Zweier-Komplement) als Position liefern,
also etwa `0101` für 5 und `0110` für 6, dann gäbe es ein Problem,
wenn nicht alle Bits absolut gleichzeitig ihre Wertigkeit ändern.
In diesem Fall könnten &bdquo;Phantomwerte&rdquo; wie `0100` (4) oder `0111` (7) auftreten.
Der Gray-Code hat dieses Problem nicht, da sich benachbarte Werte nur in einem Bit unterscheiden.
In [Abbildung 1] wird diese Eigenschaft am Beispiel des 4-Bit-Gray-Codes demonstriert:

###### {#abbildung_1_gray_codes_four_bits}

{{< figure src="/img/graycodes/GrayCodes01.png" width="50%" >}}

*Abbildung* 1: 4-Bit-Gray-Code.

# Erzeugung von Gray-Codes

Um Gray-Codes einer bestimmten Länge zu erzeugen, ist eine Darstellung wie in [Abbildung 2] gezeigt intuitiver.
Ausgehend von einer Kombination der beiden Bits 0 und 1 wird durch wiederholtes Spiegeln der Ausgangsinformation
und Hinzufügen von 0- und 1-Werten an der höchstwertigen Stelle der vollständige Gray-Code aufgebaut.
In [Abbildung 2] finden Sie die sukzessive Erzeugung des 1-, 2- und 3-Bit-Gray-Codes bis hin zum 4-Bit-Gray-Code vor:

###### {#abbildung_2_gray_codes_construction}

{{< figure src="/img/graycodes/GrayCodes02_Construction.png" width="80%" >}}

*Abbildung* 2: Bildung des Gray-Codes durch Spiegelung und Bitergänzung.

Erstellen Sie eine &bdquo;Modern C++&rdquo;&ndash;Anwendung, die möglichst einfallsreich alle Gray-Codes
für ein beliebiges *n* berechnet. Orientieren Sie sich in Ihrer Realisierung an den Details von [Tabelle 1]:

###### {#tabelle_1_class_graycodescalculator}

| Element | Beschreibung |
| :---- | :---- |
| Methode `calculate` | `static std::list<std::list<bool>> calculate(size_t len);`<br/>.Berechnet alle Gray-Codes einer bestimmten Länge `len`. Das Ergebnis wird in einem `std::list<std::list<bool>>`-Objekt zusammengestellt. |

*Tabelle* 1: Wesentliche Elemente der Klasse `GrayCodeCalculator`.


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wir beginnen mit einigen Vorüberlegungen zur Repräsentation von Gray-Codes in einem C++&ndash;Programm.
Für die Darstellung eines einzelnen Gray-Codes (einer bestimmten Länge) setzen wir die Klasse `std::list<bool>` ein.
Mehrere Gray-Codes, also `std::list<bool>`-Objekte, legen wir in einem `std::list<std::list<bool>>`-Objekt ab.
<!---
Da die Anzahl der Gray-Codes einer bestimmten Länge von vorne herein bekannt ist
(bei einer Länge *n* gibt es 2<sup>*n*</sup> Gray-Codes), kann für das `std::list<std::list<bool>>`-Objekt
bereits bei seiner Initialisierung seine Kapazität festgelegt werden!
-->

Damit sind wir schon bei der Klasse `GrayCodeCalculator` angekommen: Mit Hilfe der `calculate`-Methode 
berechnen wir die Gray-Codes einer bestimmten Länge.
Das Resultat wird in Gestalt eines `std::list<std::list<bool>>`-Objekts zurückgegeben.

Die `calculate`-Methode des Kalkulators arbeitet auf einem rekursiven Prinzip.
Liegen für eine bestimmte Länge *n* alle Gray-Codes vor, so erhält man die Gray-Codes der Länge *n*+1 wie in [Abbildung 2] skizziert wird.
Es werden alle vorliegenden Gray-Codes der Länge *n* an einer fiktiven Spiegelachse gespiegelt.
Um Gray-Codes der Länge *n*+1 zu erhalten, werden diese zunächst um ein Bit vorne verlängert (Wert 0 bzw. `false`).
In einem zweiten Schritt wird dann bei den gespiegelten Gray-Codes an der höchstwertigen Stelle
das Bit auf den Wert 1 (bzw. `true`) gesetzt. Auf diese Weise lassen sich rekursiv alle Gray-Codes einer bestimmten Länge berechnen.

Damit sind wir schon bei der Implementierung angelangt ([Listing 1] und [Listing 2]):

###### {#listing_01_graycodecalculator_decl}

```cpp
01: class GrayCodeCalculator
02: {
03: public:
04:     // c'tors
05:     GrayCodeCalculator() = delete;
06: 
07:     // public interface
08:     static std::list<std::list<bool>> calculate(size_t);
09:     static void print(std::list<std::list<bool>>);
10: 
11: private:
12:     static std::list<std::list<bool>> calculateRankOne();
13: };
```

*Listing* 1: Klasse `GrayCodeCalculator`: Definition.

###### {#listing_02_graycodecalculator_impl}

```cpp
01: std::list<std::list<bool>> GrayCodeCalculator::calculate(size_t length)
02: {
03:     if (length == 0) {
04:         throw std::invalid_argument("illegal length argument");
05:     }
06:     else if (length == 1) {
07:         return calculateRankOne();
08:     }
09:     else {
10:         std::list<std::list<bool>> tmp{ calculate(length - 1) };
11: 
12:         // need a new Gray Code list
13:         std::list<std::list<bool>> result;
14: 
15:         // copy old entries and extend them with 'false'
16:         std::for_each(
17:             std::begin(tmp),
18:             std::end(tmp),
19:             [&](const std::list<bool>& v) {
20:                 std::list<bool> ex{ v };
21:                 ex.push_front(false);
22:                 result.push_back(ex);
23:             }
24:         );
25: 
26:         // mirror old entries and extend them with 'true'
27:         std::for_each(
28:             std::rbegin(tmp),
29:             std::rend(tmp),
30:             [&](const std::list<bool>& v) {
31:                 std::list<bool> ex{ v };
32:                 ex.push_front(true);
33:                 result.push_back(ex);
34:             }
35:         );
36: 
37:         return result;
38:     }
39: }
40: 
41: std::list<std::list<bool>> GrayCodeCalculator::calculateRankOne()
42: {
43:     return { { false } , { true } };
44: }
45: 
46: void GrayCodeCalculator::print(std::list<std::list<bool>> result)
47: {
48:     for (std::list<bool> code : result) {
49:         for (bool bit : code) {
50:             std::cout << bit;
51:         }
52:         std::cout << std::endl;
53:     }
54: }
```

*Listing* 2: Klasse `GrayCodeCalculator`: Implementierung.

Das Traversieren von C++&ndash;Containern wird in [Listing 2] auf vielfältige Weise demonstriert.
Da wäre zum einen der `std::for_each`-Algorithmus (Zeilen 16 und 27). Seine Stärke liegt in der Spezifikation des 
zu Grunde liegenden Bereichs. Mit `std::begin` und `std::end` wird ein Bereich ganz klassisch vom ersten bis zum letzten Element durchlaufen.
Man kann einen Bereich aber auch in der umgekehrten Reihenfolge durchlaufen, indem man diesen mit `std::rbegin` und `std::rend` spezifiziert.

Ein zweite Variation in der Traversierung eines Containers ist die bereichsbasierte `for`-Wiederholungsschleife.
Sie kommt in den Zeilen 48 und 49 gleich zwei Mal zur Ausgabe des Ergebnisses zum Einsatz.

Interessant in  [Listing 2] ist auch Zeile 43: Hier finden Sie die Vorbelegung eines `std::list<std::list<bool>>`-Objekts
mit einer Initialisierungs-Liste vor.

Nun können wir ein `GrayCodeCalculator`-Objekt bei der Arbeit betrachten.
Wir berechnen zu diesem Zweck alle Gray-Codes bis zur Länge 5:

```cpp
// testing 1-Bit-Gray-Codes
std::list<std::list<bool>> codes = GrayCodeCalculator::calculate(1);
std::cout << codes.size() << " 1-Bit-Gray-Codes found:" << std::endl;
GrayCodeCalculator::print(codes);
std::cout << std::endl;

// testing 2-Bit-Gray-Codes
codes = GrayCodeCalculator::calculate(2);
std::cout << codes.size() << " 2-Bit-Gray-Codes found:" << std::endl;
GrayCodeCalculator::print(codes);
std::cout << std::endl;

// testing 3-Bit-Gray-Codes
codes = GrayCodeCalculator::calculate(3);
std::cout << codes.size() << " 3-Bit-Gray-Codes found:" << std::endl;
GrayCodeCalculator::print(codes);
std::cout << std::endl;

// testing 4-Bit-Gray-Codes
codes = GrayCodeCalculator::calculate(4);
std::cout << codes.size() << " 4-Bit-Gray-Codes found:" << std::endl;
GrayCodeCalculator::print(codes);
std::cout << std::endl;

// testing 5-Bit-Gray-Codes
codes = GrayCodeCalculator::calculate(5);
std::cout << codes.size() << " 5-Bit-Gray-Codes found:" << std::endl;
GrayCodeCalculator::print(codes);
```

*Ausgabe*:

```
2 1-Bit-Gray-Codes found:
0
1

4 2-Bit-Gray-Codes found:
00
01
11
10

8 3-Bit-Gray-Codes found:
000
001
011
010
110
111
101
100

16 4-Bit-Gray-Codes found:
0000
0001
0011
0010
0110
0111
0101
0100
1100
1101
1111
1110
1010
1011
1001
1000

32 5-Bit-Gray-Codes found:
00000
00001
00011
00010
00110
00111
00101
00100
01100
01101
01111
01110
01010
01011
01001
01000
11000
11001
11011
11010
11110
11111
11101
11100
10100
10101
10111
10110
10010
10011
10001
10000
```

# There&lsquo;s more

Gray-Codes lassen sich sowohl mit einem rekursiven als auch mit einem iterativen Algorithmus berechnen.
Versuchen Sie, an Hand der Beschreibung des Algorithmus in [Abbildung 2] eine iterative Realisierung in C++ umzusetzen.
Die folgende [Anregung](https://www.geeksforgeeks.org/generate-n-bit-gray-codes/) könnte hierbei behilflich sein.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_graycodescalculator

[Listing 1]: #listing_01_graycodecalculator_decl
[Listing 2]: #listing_02_graycodecalculator_impl

[Abbildung 1]:  #abbildung_1_gray_codes_four_bits
[Abbildung 2]:  #abbildung_2_gray_codes_construction

<!-- End-of-File -->