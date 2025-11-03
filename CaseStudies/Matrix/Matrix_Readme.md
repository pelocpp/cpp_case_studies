# Matrizen

https://studyflix.de/mathematik/was-ist-eine-matrix-8111

https://home.mathematik.uni-freiburg.de/knies/lehre/bkla/Skript-Brueckenkurs.pdf

https://www.matheretter.de/wiki/matrizen

https://www.heise.de/tipps-tricks/LaTeX-Matrix-erstellen-so-geht-s-4352833.html



Mit Google:

https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/

KI:  markdown math matrices examples

## Einleitung

Eine Matrix ist eine rechteckige Anordnung von Werten (mathematischen Objekten),
die in Zeilen und Spalten organisiert sind.

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


## Darstellung // TEST

Eine allgemeine *m*&times;*n*  Matrix sieht dabei so aus:

$ A = \begin{pmatrix} a & b \\ c & d \end{pmatrix} $

$$
B = \begin{bmatrix} 1 & 2 & 3 \\
4 & 5 & 6 \end{bmatrix}
$$


$$
\begin{pmatrix}
1 & 2 & 3 \\
a & b & c
\end{pmatrix}
$$

$$
\begin{bmatrix}
x_{11} & x_{12} \\
x_{21} & x_{22}
\end{bmatrix}
$$


% Using the 'matrix' environment for a plain matrix
$$
\begin{matrix}
1 & 2 & 3 \\
a & b & c
\end{matrix}
$$

Using the 'pmatrix' environment for a matrix with parentheses

$$
\begin{pmatrix}
1 & 2 & 3 \\
a & b & c
\end{pmatrix}
$$


Using the 'bmatrix' environment for a matrix with square brackets

$$
\begin{bmatrix}
1 & 2 & 3 \\
a & b & c
\end{bmatrix}
$$

Using the 'Bmatrix' environment for a matrix with curly braces

$$
\begin{Bmatrix}
1 & 2 & 3 \\
a & b & c
\end{Bmatrix}
$$


## Darstellung // TEST

Eine allgemeine *m*&times;*n*  Matrix sieht dabei so aus:

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

$$
\begin{pmatrix}
x_{11} & x_{12} & &mldr; & x_{1n}\\
x_{21} & x_{22} & &mldr; & x_{2n}\\
&mldr; &  & &mldr; & &mldr;\\
&mldr; & &mldr; & & &mldr;\\
&mldr; & &mldr; & &mldr; \\
x_{m1} & x_{m2} & &mldr; & x_{mn}\\
\end{pmatrix}
+
\begin{pmatrix}
x_{11} & x_{12} & &mldr; & x_{1n}\\
x_{21} & x_{22} & &mldr; & x_{2n}\\
&mldr; &  & &mldr; & &mldr;\\
&mldr; & &mldr; & & &mldr;\\
&mldr; & &mldr; & &mldr; \\
x_{m1} & x_{m2} & &mldr; & x_{mn}\\
\end{pmatrix}
$$

## Darstellung // TEST

## Darstellung einer Matrix in C++

Für tabellenartige Strukturen von Werten gibt es in höheren Programmiersprachen zunächst keine direkte Umsetzung.

Alle Daten, die zu einem Programm gehören, sind in (möglicherweise unterschiedlichen) Speicherbereichen
eines Programms immer sequentiell angeordnet,
rechteckige Strukturen gibt es hier nicht.

Denkt man sich alle Zeilen einer Matrix der Reihe nach hintereinander angeordnet vor,
kommen wir einer datentechnischen Umsetzung schon näher.

Datenstrukturen wie ein C-Style Array oder Objekte der Klassen `std::array` und `std::vector`
sind für solche Datensequenzen geeignet.

In einer nächsten Verfeinerung einer Realisierung einer Klasse `Matrix` müssen wir die Frage beantworten,
ob wir die Elemente einer Matrix auf dem Stack (Stapel) oder dem Heap (Halde) sehen.
Der Stack ist per se für Zwischenergebnisse und Daten kleineren Umfangs konzipiert.

Würden wir die Elemente einer Matrix in einer `Matrix`-Klasse direkt in den Instanzvariablen aufbewahren,
so würden alle Daten auf dem Stack liegen. Umgekehrt könnte man fordern, dass Instanzen einer solchen
Klasse  `Matrix` nur dynamisch, also auf dem Heap angelegt werden dürften.
Das ist aber eine sehr ungewöhnliche Einschränkung und wird so in der Praxis nicht praktiziert.

Ich habe (spaßeshalber) für eine solche Klasse `Matrix` einen ersten Entwurf gemacht:

>>> BadApproachMatrix Source-Code

Auf den ersten Blick schaut die Implementierung nicht so schlecht aus.
Bei genauerem Hinsehen können Sie jedoch erkennen, dass alle Werte des geschachteten std::array-Objekts 
*im* Instanzvariablenbereich des Objekts liegen. Bei großen Werten von `Rows` oder `Cols` kommen hier schnell
viele Werte zusammen.

Damit können wir folgern, dass für die Elemente einer Matrix grundsätzlich dynamischer Speicherplatz
in Frage kommt.

Hier geht es nun mit den Operatoren `new` und `delete` oder Smart-Pointer Klassen weiter.



Eine Matrix kann durch die Anordnung ihrer Elemente in einem einzigen, eindimensionalen Feld
(auch Vektor oder Array genannt) dargestellt werden,
wobei die Zeilen- und Spalteninformationen durch die Reihenfolge der Elemente oder eine Formel komprimiert werden.

Üblicherweise werden die Elemente in der Reihenfolge der Zeilen (Zeilen-Major-Ordnung) abgelegt,
die alternative Anordnung wäre die Spalten-Major-Ordnung, also gemäß der Reihenfolge der Spalten.

Zum Beispiel kann eine *m*&times;*n*-Matrix (*m* Reihen, *n* Spalten) in einem eindimensionalen Feld der Größe *m* * *n* gespeichert werden,
wobei sich der Index für das Element in Zeile *i* und Spalte *j* zu *i* * *n* + *j* berechnet.

*Beispiel*:<br />
Eine Matrix 2&times;3-Matrix

$$
\begin{pmatrix}
1 & 2  & 3 \\
4 & 5  & 6 \\
\end{pmatrix}
$$

wird in einem eindimensionalen Array mit den Werten `{ 1, 2, 3, 4, 5, 6 }` abgelegt.
