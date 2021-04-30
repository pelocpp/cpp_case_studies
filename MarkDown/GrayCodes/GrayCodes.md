<!-- Gray-Codes -->

Unter dem *Gray-Code* versteht man eine Folge binärer Zahlenketten, die nach dem Ingenieur *Frank Gray*,
einem Forscher in den *Bell Laboratories*, benannt wurde. Er erhielt im Jahre 1953 für die Nutzung
des nach ihm benannten Codes das U.S. Patent No. 2 632 058 &ldquo;Pulse Code Communication&rdquo;.
Durch die Anzahl der Bits wird die Länge *n* eines Gray-Codes festgelegt. Man kann sich leicht überlegen,
dass es zu einem bestimmten *n* 2<sup>*n*</sup> unterschiedliche Gray-Codes gibt.

Wir benutzen die Gray-Code-Darstellung, um an Hand einer Reihe von C++&ndash;Klassen
das Zusammenspiel unterschiedlicher C++&ndash;Sprachkonstrukte zu üben und zu vertiefen.
Das Endergebnis dieser Aufgabe, die Berechnung von Gray-Codes zu einem beliebigen *n*,
ließe sich sicherlich auch kürzer und direkter erzielen, nur würden wir dabei keinen Lerneffekt erreichen.

<!--more-->

# Lernziele

  * Container `std::list<T>`
  * Algorithmen std::for_each, std::begin, std::end, std::rbegin und std::rend
  * Lambda-Funktionen mit Zugriffsklausel
  * Initialisierungsliste
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Die Besonderheit des Gray-Codes liegt darin,
dass sich benachbarte Zahlenketten nur in genau einem Bit unterscheiden.
Dies gilt auch für den Übergang vom 2<sup>*n*</sup>-1.-ten Code zum 0.-ten Code:

*Definition*: Eine Folge aller 2<sup>*n*</sup> Bitketten der Länge n (n &geq; 1) heißt ein *Gray-Code* der Länge *n*,
falls sich jeweils 2 benachbarte Bitketten in nur einer Bitposition unterscheiden.

Diese Eigenschaft kommt vielen Anwendungen zu Gute, wie wir beispielsweise an einem Inkrementalgeber erörtern können.
Würde ein Inkrementalgeber eine herkömmliche Binärzahl (im Zweier-Komplement) als Position liefern,
also etwa `0101` für 5 und `0110` für 6, dann gäbe es ein Problem,
wenn nicht alle Bits absolut gleichzeitig ihre Wertigkeit ändern.
In diesem Fall könnten &ldquo;Phantomwerte&rdquo; wie `0100` (4) oder `0111` (7) auftreten.
Der Gray-Code hat dieses Problem nicht, da sich benachbarte Werte nur in einem Bit unterscheiden.
In [Abbildung 1] wird diese Eigenschaft am Beispiel des 4-Bit-Gray-Codes demonstriert:

###### {#abbildung_1_gray_codes_four_bits}

{{< figure src="/img/graycodes/GrayCodes01.png" width="80%" >}}

*Abbildung* 1: 4-Bit-Gray-Code.

# Erzeugung von Gray-Codes

Um Gray-Codes einer bestimmten Länge zu erzeugen, ist eine Darstellung wie in [Abbildung 2] gezeigt intuitiver.
Ausgehend von einer Kombination der beiden Bits 0 und 1 wird durch wiederholtes Spiegeln der Ausgangsinformation
und Hinzufügen von 0- und 1-Werten an der höchstwertigen Stelle der vollständige Gray-Code aufgebaut.
In [Abbildung 2] finden Sie die sukzessive Erzeugung des 1-, 2- und 3-Bit-Gray-Codes bis hin zum 4-Bit-Gray-Code vor:

###### {#abbildung_2_gray_codes_construction}

{{< figure src="/img/graycodes/GrayCodes02_Construction.png" width="80%" >}}

*Abbildung* 2: Bildung des Gray-Codes durch Spiegelung und Bitergänzung.

Erstellen Sie eine &ldquo;Modern C++&rdquo;&ndash;Anwendung, die möglichst einfallsreich alles Gray-Codes
für ein beliebiges *n* berechnet. Orientieren Sie sich in Ihrer Realisierung an den Details von [Tabelle 1]:

###### {#tabelle_1_class_graycodescalculator}

| Element | Beschreibung |
| :---- | :---- |
| Methode `calculate` | `static std::vector<std::vector<bool>> calculate(size_t len);`<br/>.Berechnet alle Gray-Codes einer bestimmten Länge `len`. Das Ergebnis wird in einem `std::vector<std::vector<bool>>`-Objekt zusammengestellt. |

*Tabelle* 1: Wesentliche Elemente der Klasse `GrayCodeCalculator`.


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Wir beginnen mit einigen Vorüberlegungen zur Repräsentation von Gray-Codes in einem C++&ndash;Programm.
Für die Darstellung eines einzelnen Gray-Codes (einer bestimmten Länge) setzen wir die Klasse `std::vector<bool>` ein.
Mehrere Gray-Codes, also `std::vector<bool>`-Objekte, legen wir in einem `std::vector<std::vector<bool>>`-Objekt ab.
Da die Anzahl der Gray-Codes einer bestimmten Länge von vorne herein bekannt ist
(bei einer Länge *n* gibt es 2<sup>*n*</sup> Gray-Codes), kann für das `std::vector<std::vector<bool>>`-Objekt
bereits bei seiner Initialisierung seine Kapazität festgelegt werden!

Damit sind wir schon bei der Klasse `GrayCodeCalculator` angekommen: Mit Hilfe der `calculate`-Methode 
berechnen wir die Gray-Codes einer bestimmten Länge.
Das Resultat wird in Gestalt eines `std::vector<std::vector<bool>>`-Objekts zurückgegeben.

Die `calculate`-Methode des Kalkulators arbeitet auf einem rekursiven Prinzip.
Liegen für eine bestimmte Länge *n* alle Gray-Codes vor, so erhält man die Gray-Codes der Länge *n*+1 wie in [Abbildung 2] skizziert wird.
Es werden alle vorliegenden Gray-Codes der Länge *n* an einer fiktiven Spiegelachse gespiegelt.
Um Gray-Codes der Länge *n*+1 zu erhalten, werden diese zunächst um ein Bit vorne verlängert (Wert 0 bzw. `false`).
In einem zweiten Schritt wird dann bei den gespiegelten Gray-Codes an der höchstwertigen Stelle
das Bit auf den Wert 1 gesetzt.
Auf diese Weise lassen sich rekursiv alle Gray-Codes einer bestimmten Länge berechnen.

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
03:     if (length == 1) {
04:         return calculateRankOne();
05:     }
06:     else {
07:         std::list<std::list<bool>> tmp{ calculate(length - 1) };
08: 
09:         // need a new Gray Code list
10:         std::list<std::list<bool>> result;
11: 
12:         // copy old entries and extend them with 'false'
13:         std::for_each(
14:             std::begin(tmp),
15:             std::end(tmp),
16:             [&](const std::list<bool>& v) {
17:                 std::list<bool> ex{ v };
18:                 ex.push_front(false);
19:                 result.push_back(ex);
20:             }
21:         );
22: 
23:         // mirror old entries and extend them with 'true'
24:         std::for_each(
25:             std::rbegin(tmp),
26:             std::rend(tmp),
27:             [&](const std::list<bool>& v) {
28:                 std::list<bool> ex{ v };
29:                 ex.push_front(true);
30:                 result.push_back(ex);
31:             }
32:         );
33: 
34:         return result;
35:     }
36: }
37: 
38: std::list<std::list<bool>> GrayCodeCalculator::calculateRankOne()
39: {
40:     return { { false } , { true } };
41: }
42: 
43: void GrayCodeCalculator::print(std::list<std::list<bool>> result)
44: {
45:     for (std::list<bool> code : result) {
46:         for (bool bit : code) {
47:             std::cout << bit;
48:         }
49:         std::cout << std::endl;
50:     }
51: }
```

*Listing* 2: Klasse `GrayCodeCalculator`: Implementierung.

Das Traversieren von C++&ndash;Containern wird in [Listing 2] auf vielfältige Weise demonstriert.
Da wäre zum Einen der `std::for_each`-Algorithmus (Zeilen 13 und 24). Seine Stärke liegt in der Spezifikation des 
zu Grunde liegenden Bereichs. Mit `std::begin` und `std::end` wird ein Bereich ganz klassisch vom ersten bis zum letzten Element durchlaufen.
Man kann einen Bereich aber auch in der umgekehrten Reihenfolge durchlaufen, in dem man diesen mit `std::rbegin` und `std::rend` spzifiziert.

Ein zweite Variation in der Traversierung eines Containers ist die bereichsbasierte `for`-Wiederholungsschleife.
Sie kommt in den Zeile 45 bis 50 gleich zwei Mal zur Ausgabe des Ergebnisses zum Einsatz.

Interessant in  [Listing 2] ist auch Zeile 40: Hier finden Sie die Vorbelegung eines `std::list<std::list<bool>>`-Objekts
mit einer Initialisierungs-Liste vor.


// ==============================================

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

[Tabelle 1]: #tabelle_1_class_graycodescalculator

[Listing 1]: #listing_01_graycodecalculator_decl
[Listing 2]: #listing_02_graycodecalculator_impl

[Abbildung 1]:  #abbildung_1_gray_codes_four_bits
[Abbildung 2]:  #abbildung_2_gray_codes_construction

<!-- End-of-File -->
