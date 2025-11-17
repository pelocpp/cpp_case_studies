# Matrizen

https://studyflix.de/mathematik/was-ist-eine-matrix-8111

https://home.mathematik.uni-freiburg.de/knies/lehre/bkla/Skript-Brueckenkurs.pdf

https://www.matheretter.de/wiki/matrizen

https://www.heise.de/tipps-tricks/LaTeX-Matrix-erstellen-so-geht-s-4352833.html


Youtube:
https://www.youtube.com/watch?v=9Ule9qQaBB0

Mit Google:

https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/

KI:  markdown math matrices examples



Linear Equation Solver : r/java

Reddit · r/java
8 Kommentare · vor 11 Jahren
Get the values of the parameters for your equation (by parsing a string or having the user input them). Plug the parameters into the formula.







## Einleitung

Eine Matrix ist eine rechteckige Anordnung von Werten (mathematischen Objekten),
die in Zeilen und Spalten organisiert sind.
Eine allgemeine *m*&times;*n* Matrix mit *m* Zeilen und *n* Spalten sieht dabei so aus:

$$
\begin{pmatrix}
x_{11} & x_{12} & &mldr; & x_{1n} \\
x_{21} & x_{22} & &mldr; & x_{2n} \\
&mldr; &        &        & \\
       & &mldr; &        & \\
       &        & &mldr; & \\
       &        &        & &mldr; \\
x_{m1} & x_{m2} & &mldr; & x_{mn} \\
\end{pmatrix}
$$


Die Anzahl der Zeilen wird durch *m* und die Anzahl der Spalten durch *n* angegeben.
Eine Matrix mit *m* Zeilen und *n* Spalten nennt man *m*&times;*n* Matrix.

Matrizen stammen aus einem Teilgebiert der höheren Mathematik, der linearen Algebra,
die sich mit Vektorräumen beschäftigt.

Anwendungsfälle für das Arbeiten mit Matrizen
sind zum Beipiel lineare Gleichungssysteme,
das Lösen von linearen Gleichungssystemen,
die Computergrafik mit Transformationen wie Rotation und Skalierung,
die Kryptografie und natürlich nicht zu vergessen die KI mit dem maschinellen Lernen zur Verarbeitung großer Datenmengen.

Elementare Rechenoperationen für Matrizen sind die Addition, Subtraktion und Multiplikation.

## Vektoren

In der Mathematik und Physik spielen Skalare und Vektoren eine große Rolle.
Während man unter einem Skalar eine Größe versteht, deren Wert sich eindeutig durch die Angabe einer Maßzahl beschreiben lässt,
benötigt man zur vollständigen Charakterisierung eines Vektors noch die Angabe einer Richtung im Raum.
So lassen sich beispielsweise Windgeschwindigkeiten, Beschleunigungen, elektrische oder magnetische Feldstärken durch Vektoren beschreiben.


## Darstellung eines Vektors in C++


## Darstellung einer Matrix in C++

Für tabellenartige Strukturen von Werten gibt es in höheren Programmiersprachen keine unmittelbare Umsetzung.

Alle Daten, die zu einem Programm gehören, sind in &ndash; möglicherweise unterschiedlichen &ndash; Speicherbereichen
eines Programms immer sequentiell angeordnet, rechteckige Datenbereiche gibt es hier nicht.

Denkt man sich alle Zeilen einer Matrix der Reihe nach hintereinander angeordnet vor,
kommen wir einer datentechnischen Umsetzung schon recht nahe.

Datenstrukturen wie ein C-Style Array oder Objekte der Klassen `std::array` oder `std::vector`
sind für solche Datensequenzen geeignet.

In einer nächsten Stufe einer Verfeinerung der Realisierung einer Klasse `Matrix` müssten wir die Frage beantworten,
ob wir die Elemente einer Matrix auf dem *Stack* (Stapel) oder dem *Heap* (Halde) sehen.
Der Stack ist per se für Zwischenergebnisse und Daten kleineren Umfangs konzipiert.

Würden wir die Elemente einer Matrix in einem `Matrix`-Objekt direkt in den Instanzvariablen aufbewahren,
so würden alle Daten dieses Objekts auf dem Stack liegen, sofern es sich beispielsweise im lokale Objekte einer freien Funktion oder eines Objekts handelt.
Damit könnte man keine `Matrix`-Objekte mit großer Spalten- oder Zeilenanzahl anlegen, da so der begrenzte Speicherumfang des Stack
schnell überschritten werden dürfte.

Man könnte fordern, dass Instanzen einer solchen
Klasse  `Matrix` nur dynamisch, also auf dem Heap angelegt werden dürften.
Das ist aber eine sehr ungewöhnliche Einschränkung und wird so in der Praxis nicht praktiziert.
Abgesehen davon, dass ein Compiler derartige Einschränkungen gar nicht überprüfen kann.

Ich habe (spaßeshalber) für eine solche Klasse `Matrix` einen ersten Entwurf gemacht:


```cpp
01: template <typename T, std::size_t Rows, std::size_t Cols>
02: class BadApproachMatrix
03: {
04: protected:
05:     std::array<std::array<T, Cols>, Rows> m_values{};
06: 
07: public:
08:     // c'tors
09:     BadApproachMatrix() = default;
10: 
11:     BadApproachMatrix(std::initializer_list<double> values)
12:     {
13:         std::copy(
14:             values.begin(),
15:             values.end(),
16:             &m_values[0][0]
17:         );
18:     }
19:     ...    
20: };
```


Auf den ersten Blick schaut die Implementierung nicht so schlecht aus.
Bei genauerem Hinsehen können Sie jedoch erkennen, dass alle Werte des geschachteten `std::array`-Objekts 
*im* Instanzvariablenbereich des Objekts liegen. Bei großen Werten von `Rows` oder `Cols` kommen hier schnell
viele Werte zusammen. Siehe das folgende Beispiel mit 100 Zeilen und Spalten:

```cpp
BadApproachMatrix<double, 100, 100> largeMatrix{ };
```

Ein Blick hinter die Kulissen des Objekts zeigt uns, dass hier 8.000.000 Bytes auf dem Stack verbraucht werden.


<img src="HugeMatrixMemoryLayout.png" width="500">

*Abbildung* 1: Zu viele Daten auf dem Stack.

oder auch so:

<img src="StackExhaustion.png" width="500">

*Abbildung* 2: Zu viele Daten auf dem Stack.


Das ist in dieser Weise nicht akzeptabel, wir müssen einen anderen Weg beschreiten.
Wir können jetzt folgern, dass für die Elemente einer Matrix grundsätzlich nur dynamischer Speicherplatz
in Frage kommt.

Hier geht es nun mit den Operatoren `new` und `delete` oder Smart-Pointer Klassen weiter.

Eine Matrix kann durch die Anordnung ihrer Elemente in einem einzigen, eindimensionalen Feld dargestellt werden.
Um so auf die Elemente der Matrix zugreifen zu können, werden die Zeilen- und Spalteninformationen
eines jeden Elements durch eine Formel komprimiert ausgedrückt.

Üblicherweise werden die Elemente eines solchen rechteckigen Datenstruktur
in der Reihenfolge der Zeilen abgelegt (so genannte *Zeilen*-*Major*-Anordnung),
die alternative Anordnung wäre eine *Spalten*-*Major*-Anordnung, also gemäß der Reihenfolge der Spalten.

Speichern wir zum Beispiel eine *rows*&times;*cols*-Matrix (*rows* Zeilen, *cols* Spalten) in einem eindimensionalen Feld der Größe *rows* * *cols* ab,
lautet die Formel für den Zugriff auf das Element in Zeile *row* und Spalte *col*

*row* * *n* + *col*.

*Beispiel*:<br />
Eine 2&times;3-Matrix des Aussehens

$$
\begin{pmatrix}
1 & 2  & 3 \\
4 & 5  & 6 \\
\end{pmatrix}
$$

legen in einem eindimensionalen `int`-Array mit den Werten `{ 1, 2, 3, 4, 5, 6 }` ab.

Damit sind wir in C++ angekommen, unser Entwurf eine Klasse `Matrix` sieht so aus:

```cpp
01: class Matrix
02: {
03: protected:
04:     std::size_t m_rows;
05:     std::size_t m_cols;
06:     std::shared_ptr<double[]> m_values;
07:     ...
08: };
```


## Konstruktoren der Klasse `Matrix`

Wir wollen `Matrix`-Objekte in unterschiedlicher Weise anlegen können.
Eine Zusammenfassung der überladenen Konstruktoren folgt:
Der Standard-Konstruktor ist mehr der Vollständigkeit halber vorhanden.
Matrizen mit 0 Zeilen und 0 Spalten spielen in der Praxis keine Rolle:

```cpp
Matrix::Matrix() : m_rows{}, m_cols{}, m_values{} {}
```

Der nächste Konstruktor mit der Schnittstelle

```cpp
Matrix::Matrix(std::size_t rows, std::size_t cols)
```

legt Matrizenobjekte mit einer vorgegebenen Anzahl von Zeilen und Spalten an. Er besitzt folgende Realisierung:

```cpp
01: Matrix::Matrix(std::size_t rows, std::size_t cols)
02:     : m_rows{ rows }, m_cols{ cols } 
03: {
04:     m_values = std::make_shared<double[]>(m_rows * m_cols);
05: }
```

Man beachte hierbei, dass das Funktionstemplate `std::make_shared` den reservierten Speicher mit `0.0` vorbelegt.
Als ob wir `new double[m_rows * m_cols] {}` aufgerufen hätten.
Damit können wir Matrizen mit Null-Werten anlegen:

```cpp
Matrix matrix{ 3, 3 };
```

Hübsch wären aber andere Schreibweisen, wie wäre es beispielsweise mit

```cpp
Matrix matrix{ 3, 3, { 1, 2, 3 ,4 , 5, 6, 7, 8, 9 } };
```


Hier kommt uns die C++-Klasse `std::initializer_list` zu Hilfe.
In einer ersten Umsetzung können wir mit ihrer Hilfe eine beliebig lange Liste von Werten
an einen Konstruktorenaufruf übergeben. Diese Liste mit Werten muss dann Zeile für Zeile an das `Matrix`-Objekt übertragen werden,
so dass am Ende alle Elemente der Matrix mit den Werten aus der Liste vorbelegt sind.

Man könnte &ndash; wie in C/C++ bei unvollständigen Initialisierungen von Arrays oder Strukturen &ndash; diskutieren,
ob man für Matrizen auch diese Option einräumt, also Listen mit weniger Werten, als es die Matrix benötigt, zulässt.
Ich habe den Weg eingeschlagen, dass die Liste vollständig sein muss:


```cpp
01: Matrix::Matrix(std::size_t rows, std::size_t cols, std::initializer_list<double> values)
02:     : m_rows{ rows }, m_cols{ cols }
03: {
04:     if (m_rows * m_cols != values.size()) {
05:         throw std::invalid_argument("Wrong number of values!");
06:     }
07: 
08:     m_values = std::make_shared<double[]>(m_rows * m_cols);
09: 
10:     std::copy(
11:         values.begin(),
12:         values.end(),
13:         m_values.get()
14:     );
15: }
```

Dieser Konstruktor profitiert in seiner Realisierung davon, dass die Elemente der Matrix in einem ein-dimensionalen Feld vorliegen.
Auf diese Weise kann der STL-Algorithmus `std::copy` angeworfen werden.
Ein `std::initializer_list`-Objekt kann als Beriech (*Range*) aufgefasst werden, er unterstützt die beiden Methoden
`begin()` und `end()`. Das dritte Argument kann ein *Raw*-Zeiger sein, die STL wurde so konzipiert, 
dass Zeiger die Rolle von *random-access* Iteratoren spielen.

Noch prägnanter wäre natürlich eine Schreibweis in der Art

```cpp
Matrix matrix{ 3, 3, { { 1, 2, 3 } , { 4, 5, 6 }, { 7, 8, 9 } } };
```

Auch dies können wir realisieren, eine geschachtelte `std::initializer_list` obliegt dem Lösungsansatz:


```cpp
Matrix(
    std::size_t rows, 
    std::size_t cols,
    std::initializer_list<std::initializer_list<double>> values
);
```

In der Realisierung dieses Konstruktors achten wir wiederum darauf, dass alle `std::initializer_list`-Listen
die Länge der Zeilen und Spalten respektieren.


## Konzepte und Anforderungen für Matrizen

Die einzelnen Elemente unserer Matrix sollen Gleitpunktwerte aufnehmen.
Dabei wollen wir aber den Freiheitsgrad aufrecht erhalten, ob die Werte vom Typ `float`, `double` oder `long double` sind.
In C++ sind Klassentemplates die Antwort auf einen solchen Wunsch.

Eine Verfeinerung unserer `Matrix`-Klassendefinition sieht damit so aus:

```cpp
01: template <typename T>
02: concept FloatNumber = std::floating_point<T>;
03: 
04: template <typename T>
05:     requires FloatNumber<T>
06: class Matrix
07: {
08: protected:
09:     std::size_t m_rows;
10:     std::size_t m_cols;
11:     std::shared_ptr<T[]> m_values;
12: 
13: public:
14:     // c'tors
15:     Matrix();
16:     Matrix(std::size_t rows, std::size_t cols);
17:     Matrix(std::size_t rows, std::size_t cols, std::initializer_list<T> values);
18:     Matrix(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<T>> values);
19: 
20:     // getter   
21:     std::size_t rows() const { return m_rows; }
22:     std::size_t cols() const { return m_cols; }
23: 
24:     // public interface
25:     void print() const;
26:     T& at(std::size_t row, std::size_t col);
27:     const T& at(std::size_t row, std::size_t col) const;
28: 
29:     Matrix transpose() const;
30:     Matrix add(const Matrix& other) const;
31:     Matrix sub(const Matrix& other) const;
32:     Matrix mul(const Matrix& other) const;
33: };
```


Die Klasse `Matrix` formulieren wir nun in Gestalt einer Klassenschablone.
Für die zulässigen Datentypen, die für `T` in Betracht kommen, greifen wir auf die beiden Sprachmittel
`concept` und `requires` zurück.

Wenn wir nun versuchen, eine Templateinstantiierung für T = int vornehmen zu wollen, 
reagiert der C++&ndash;Compiler mit der Fehlermeldung

```
'Matrix': the associated constraints are not satisfied
```

## Kopieren und Verschieben von Matrix-Objekten

Im Objektmodell von C++ nehmen einige Methoden (dazu zählen wir auch Konstruktoren und Operatoren)
eine besondere Stellung ein. Es ist die Rede vom Kopierkonstruktor, dem Wertzuweisungs-Operator und dem Destruktor.
An C++ 11 gesellen hier noch der verschiebende Konstrtuktor und die verschiebende Wertzuweisung (Operator) hinzu.

Die Experten erahnen es schon: Wir kommen auf die Regeln &bdquo;*Rule-of-Three*&rdquo;, &bdquo;*Rule-of-Five*&rdquo;
und &bdquo;*Rule-of-Zero*&rdquo; zu sprechen.

Diese lauten im einzelnen

*Rule of Three*:

  * Copy constructor: `X(const X&)`
  * Copy assignment: `X& operator=(const X&)`
  * Destructor: `~X()`

*Rule of Five*:

  * Copy constructor: `X(const X&)`
  * Copy assignment: `X& operator=(const X&)`
  * Move constructor: `X(X&&) noexcept`
  * Move assignment: `X& operator=(X&&) noexcept`
  * Destructor: `~X()`

*Rule of Zero*:

  * Es dürfen keine Zeiger vorhanden sein, die mit `new` allokiert wurden.
  * Verwenden Sie Container der STL.
  * Verwenden Sie *Smart Pointer*.



Besitzen Objekte dynamisch mit `new` angelegte Daten, ist die Realisierung der  &bdquo;*Rule-of-Three*&rdquo; unumgänglich.
In unserem Fall der Klasse `Matrix` haben wir dynamsische Daten, deren Verwaltung wir aber in die Obhut einer Smart-Pointer Klasse `std::shared_ptr<T>`
gelegt haben.

Damit dürfen wir die &bdquo;*Rule-of-Zero*&rdquo; in Anspruch nehmen, und dies bedeutet: Wir müssen keine der speziellen Lebenszyklusmethoden
eines C++&ndash;Objekts implementieren.






## Rechenmethoden für Matrizen: Addition, Subtraktion und Multipliaktion

Wir starten in diesen Kapitel mit der Betrachtung der Matrizen-Addition.
Diese ist so definiert, dass in der Ergebnis-Matrix jedes Element die Summe der beiden Elemente aus erstem und zweiten Operanden ist:

$$
\begin{pmatrix}
a_{11} & a_{12} & &mldr; & a_{1n}\\
a_{21} & a_{22} & &mldr; & a_{2n}\\
&mldr; &        &        & \\
       & &mldr; &        & \\
       &        & &mldr; & \\
       &        &        & &mldr; \\
a_{m1} & a_{m2} & &mldr; & a_{mn}\\
\end{pmatrix}
\+
\begin{pmatrix}
b_{11} & b_{12} & &mldr; & b_{1n}\\
b_{21} & b_{22} & &mldr; & b_{2n}\\
&mldr; &        &        & \\
       & &mldr; &        & \\
       &        & &mldr; & \\
       &        &        & &mldr; \\
b_{m1} & b_{m2} & &mldr; & b_{mn}\\
\end{pmatrix}
\=
\begin{pmatrix}
a_{11}+b_{11} & a_{12}+b_{12} & &mldr; & a_{1n}+b_{1n}\\
a_{21}+b_{21} & a_{22}+b_{22} & &mldr; & a_{2n}+b_{2n}\\
&mldr; &        &        & \\
       & &mldr; &        & \\
       &        & &mldr; & \\
       &        &        & &mldr; \\
a_{m1}+b_{m1} & a_{m2}+b_{m2} & &mldr; & a_{mn}+b_{mn}\\
\end{pmatrix}
$$

Ein Umsatzung in C++&ndash;Quellcode ist nicht sonderlich schwer:


```cpp
01: template <typename T>
02: Matrix<T> Matrix<T>::add(const Matrix& other) const
03: {
04:     Matrix<T> result{ m_rows, m_cols };
05:     for (std::size_t i{}; i != m_rows * m_cols; ++i) {
06: 
07:         result.m_values[i] = m_values[i] + other.m_values[i];
08:     }
09:     return result;
10: }
```



## Test Tabellen und lineare Gleichungssystem

Wir betrachten zum Lösung eines linearen Gleichungssystems den Algorithmus von Gauss.


https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/

Was versteht man Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauss
unter der Vorwärtselimination?

Wie funktioniert die Vorwärtselimination beim
Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauss
im Detail?

Wie funktioniert die Rückwärtssubstitution beim
Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauss
im Detail?


## Lineare Gleichungssysteme

Wir betrachten zum Lösung eines linearen Gleichungssystems den Algorithmus von Gauss.

Die Vorwärtselimination ist der erste Schritt des Gauß-Algorithmus,
bei dem ein lineares Gleichungssystem schrittweise in eine obere Dreiecksform umgewandelt wird.
Dabei werden durch äquivalente Zeilenumformungen systematisch Variablen eliminiert,
sodass unter der Hauptdiagonalen der Matrix nur noch Nullen stehen.

Das Ziel ist die Umwandlung in ein System von vereinfachten Gleichungen,
das von unten nach oben leicht lösbar ist.

Wir betrachten das Ganze an folgendem Beispiel. Zu Lösen ist das lineare Gleichungssystem

<pre>
2x<sub>2</sub> + 3x<sub>1</sub> -  x<sub>0</sub> = -9
 x<sub>2</sub> - 2x<sub>1</sub> +  x<sub>0</sub> = 9
-x<sub>2</sub> +  x<sub>1</sub> + 2x<sub>0</sub> = 0
</pre>

### Detaillierte Schritte der Vorwärtselimination


#### 1. Aufschreiben der erweiterten Koeffizientenmatrix

Zunächst ist das lineare Gleichungssystem in eine erweiterte Matrix so umzuformulieren,
dass die Koeffizienten der Variablen in den ersten *n* Spalten einer *n*+1 &times; *m* Matrix
und die konstanten Werte auf der rechten Seite der Gleichungen in der *n*+1.-ten Spalte stehen:

<pre>
 2.0    3.0   -1.0   -9.0
 1.0   -2.0    1.0    9.0
-1.0    1.0    2.0    0.0
</pre>

#### 2. Auswahl des Pivotelements

Wählen Sie in der ersten Spalte die erste Zeile als Pivotelement aus,
in der Regel ein von Null verschiedener Wert.
Ist der Wert 0, so ist für diese Zeile nichts zu tun.

#### 3. Eliminieren der Elemente unter dem Pivotelement

Verwenden Sie das Pivotelement, um alle Koeffizienten in der ersten Spalte unterhalb der ersten Zeile
auf Null zu setzen.

Dazu subtrahieren wir ein geeignetes Vielfaches der ersten Zeile von den jeweiligen darunterliegenden Zeilen.

*Beispiel*: Um die erste Spalte einer *zeile*<sub>1</sub> in der zweiten Zeile einer *zeile*<sub>2</sub> auf Null zu setzen,
können Sie die neue Zeile als *zeile*<sub>2</sub> – k * *zeile*<sub>1</sub> definieren,
wobei *k* so gewählt wird, dass der neue Eintrag in der ersten Spalte Null wird.

Wir betrachten dies am Beispiel des obigen Gleichungssystems.
Zunächst betrachten wir das erste Element in der zweiten Gleichung, wir wollen
dieses mit dem Pivot-Element 1/2 auf Null setzen:

<pre>
 2.0     3.0   -1.0   -9.0
 0.0    -3.5    1.5   13.5
-1.0     1.0    2.0    0.0
</pre>

Es folgt die Umwandlung der dritten Gleichung  hier wählen wir das Pivot-Element -1/2:

<pre>
 2.0     3.0   -1.0   -9.0
 0.0    -3.5    1.5   13.5
 0.0     2.5    1.5,  -4.5
</pre>




#### 4. Fortsetzen für die nächste Spalten

Man bewege sich zur zweiten Spalte. Die erste Zeile wird nicht mehr für die folgenden Umformungen verwendet.

Wählen Sie in der zweiten Spalte das nächste Pivotelement, das nun der erste Nicht-Null-Eintrag in der zweiten Zeile ist.

Wiederholen Sie den Eliminationsschritt, indem Sie ein Vielfaches der zweiten Zeile von den darunterliegenden Zeilen subtrahieren,
um die Einträge in der zweiten Spalte auf Null zu setzen.

In unserem Beispiel hat das Pivot-Element nun den Wert -2.5/3.5 oder einfacher -5/7:

<pre>
 2.0     3.0   -1.0     -9.0
 0.0    -3.5    1.5     13.5
 0.0     0.0    2.571    5.143
</pre>


#### 5. Wiederholung bis zur Dreiecksform

Führen Sie diesen Vorgang für alle Spalten fort, bis die Matrix in der oberen Dreiecksform vorliegt. Das bedeutet, alle Einträge unter der Hauptdiagonalen sind Null. 

### Detaillierte Schritte der Rückwärtssubstitution

Die Rückwärtssubstitution beim Gauß-Algorithmus ist ein Prozess, bei dem man,
nachdem ein lineares Gleichungssystem in die obere Dreiecksform gebracht wurde,
die Lösungen schrittweise &bdquo;von unten nach oben&rdquo; ermittelt.

Man beginnt mit der letzten Gleichung, die nur eine Unbekannte enthält, um deren Wert zu bestimmen.
Diesen Wert setzt man dann in die Gleichung darüber ein, um die nächste Variable zu ermitteln,
und fährt so fort, bis alle Variablen berechnet sind. 

Schritt-für-Schritt-Anleitung

  * Beginnen Sie mit der letzten Zeile:<br />
In der oberen Dreiecksform (auch Zeilenstufenform genannt) ist die letzte Zeile des Gleichungssystems eine einfache Gleichung,
die nur eine Unbekannte enthält. Sie können diese Gleichung nun direkt nach dieser Variable auflösen.

  * Setzen Sie den Wert in die vorletzte Zeile ein:<br />
Nehmen Sie den gerade berechneten Wert und setzen Sie ihn in die vorletzte Gleichung ein.
Diese Gleichung enthält nun nur noch zwei Unbekannte, von denen eine jetzt bekannt ist.

  * Lösen Sie nach der nächsten Variablen auf:<br />
Die Gleichung hat sich zu einer linearen Gleichung mit nur noch einer unbekannten Variable reduziert, die Sie nun leicht berechnen können.

  * Wiederholen Sie den Vorgang:<br />
Setzen Sie die Werte der beiden gerade berechneten Variablen in die nächsthöhere Gleichung ein.
Auch diese vereinfacht sich nun zu einer Gleichung, die nur noch eine unbekannte Variable enthält.

  * Setzen Sie die ersten Werte in die erste Zeile ein:<br />
Fahren Sie so fort, bis Sie alle Werte ermittelt haben. Zum Schluss setzen Sie die Werte aller bereits berechneten Variablen in die erste Gleichung ein, um die letzte verbliebene Variable zu bestimmen und das System vollständig zu lösen. 




