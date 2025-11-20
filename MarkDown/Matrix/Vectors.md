# Vektoren

## Links

https://studyflix.de/mathematik/was-ist-eine-matrix-8111

https://home.mathematik.uni-freiburg.de/knies/lehre/bkla/Skript-Brueckenkurs.pdf

https://www.matheretter.de/wiki/matrizen

https://www.heise.de/tipps-tricks/LaTeX-Matrix-erstellen-so-geht-s-4352833.html


Youtube:
https://www.youtube.com/watch?v=9Ule9qQaBB0

Mit Google:

https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/

KI:  markdown math matrices examples


// BEISPIELE FÜR MAthematik in Markdown

https://damienbod.com/2022/06/06/using-math-expressions-in-github-markdown/

oder

https://www.upyesp.org/posts/makrdown-vscode-math-notation/


## Einleitung zu Vektoren

// https://www.grund-wissen.de/mathematik/lineare-algebra-und-analytische-geometrie/vektoren.html


Vektoren sind gerichtete Größen, die in Betrag und Richtung (vorzeichenbehaftet) bestimmt sind.

Bei Vektoren handelt es sich aus geometrischer Sicht um Strecken, die eine bestimmten Länge und Richtung haben.

Betrachten wir Vektoren im zwei- oder dreidimensionalen Raum, reicht ein geordnetes Paar aus zwei oder ein Tupel aus drei Koordinatenwerten aus,
um den Vektor zu beschreiben &ndash; also etwa 
$\vec{x}$ = (<i>x</i><sub>1</sub>, <i>x</i><sub>2</sub>)
oder
$\vec{x}$ = (<i>x</i><sub>1</sub>, <i>x</i><sub>2</sub>, <i>x</i><sub>3</sub>).

Die einzelnen Koordinatenwerte (&bdquo;Komponenten&rdquo;) geben dabei an,
um wie viele Längeneinheiten die Spitze des Vektors entlang der jeweiligen Raumrichtung vom Anfangspunkt des Vektors entfernt liegt.

ABbildung 1

### Betrag eines Vektors

Die Länge der Verbindungsstrecke vom Anfangspunkt eines Vektors zu seinem Endpunkt wird Betrag des Vektors genannt.

Im zwei- oder dreidimensionalen Vektorraum kann der Betrag eines Vektors 
mit Hilfe des Satzes von Pythagoras anhand seiner Komponenten berechnet werden:

$$
|\vec{x}| = \sqrt{x_{1}^2+x_{2}^2+x_{3}^2}
$$

oder


$$
|\vec{x}| = \sqrt{x_{1}^2+x_{2}^2}
$$

*Beispiel*:<br />
Der dreidimensionale Vektor

$$
x=\begin{pmatrix}
4 \cr
5 \cr
2 \cr
\end{pmatrix}
$$

hat den Betrag

$$
|x| = \sqrt{4^2+5^2+2^2} = \sqrt{16+25+4} = \sqrt{45} = 999
$$


### Gleichheit (Identität) von Vektoren

Zwei Vektoren $\vec{x}$ und $\vec{y}$ sind gleich,
wenn sie in allen Koordinaten übereinstimmen.
Beide Vektoren haben dann den gleichen Betrag und die gleiche Richtung.


### Ein normierter Vektor

Ein Vektor, dessen Länge genau einer Längeneinheit entspricht, wird &bdquo;normierter&rdquo; Vektor $\vec{a}_0$ genannt.


### Addition und Subtraktion von Vektoren

Man erhält rechnerisch einen Summenvektor,
indem man die einzelnen Komponenten beider Vektoren addiert:


$$
\vec{a} + \vec{b} =
\begin{pmatrix}
a_{1} \\
a_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
a_{n} \\
\end{pmatrix}
\+
\begin{pmatrix}
b_{1} \\
b_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
b_{n} \\
\end{pmatrix}
\=
\begin{pmatrix}
a_{1}+b_{1} \\
a_{2}+b_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
a_{n}+b_{n} \\
\end{pmatrix}
$$


Eine Addition von Vektoren mit unterschiedlicher Dimension ist nicht definiert.


### Der Differenzvektor

Rechnerisch erhält man den Differenzvektor, indem man die einzelnen Komponenten beider Vektoren subtrahiert:

$$
\vec{a} - \vec{b} =
\begin{pmatrix}
a_{1} \\
a_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
a_{n} \\
\end{pmatrix}
\-
\begin{pmatrix}
b_{1} \\
b_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
b_{n} \\
\end{pmatrix}
\=
\begin{pmatrix}
a_{1}-b_{1} \\
a_{2}-b_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
a_{n}-b_{n} \\
\end{pmatrix}
$$


### Multiplikation von Vektoren

Vektoren können entweder mit einer reellen Zahl (einem so genannten &bdquo;Skalar&rdquo;)
als auch mit anderen Vektoren multipliziert werden.

Man spricht dann von einer skalaren Multiplikation oder im anderen Fall von einer Multiplikation von Vektoren. 

#### Multiplikation eines Vektors mit einer reellen Zahl (skalare Multiplikation)

Multipliziert man einen Vektor $\vec{a}$ mit einer reellen Zahl *c*,
so ergibt sich ein Vektor, der die gleiche Richtung und den gleichen Richtungssinn hat,
dessen Betrag jedoch um den Faktor c verändert ist.

  * Ist *c* > 1, so wird der Vektor gestreckt.
  * Ist 0 < *c* < 1, so wird der Vektor gestaucht.
  * Ist *c* < 0, so wird zusätzlich zur Streckung beziehungsweise Stauchung des Vektors der Richtungssinn umgedreht.

Rechnerisch lässt sich ein Vektor $\vec{a}$ mit einer reellen Zahl *c* multiplizieren,
indem jede Komponente des Vektors mit dieser Zahl multipliziert wird:

$$
c \cdot \vec{a} = c \cdot
\begin{pmatrix}
a_{1} \\
a_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
a_{n} \\
\end{pmatrix}
\=
\begin{pmatrix}
c \cdot a_{1} \\
c \cdot a_{2} \\
&mldr; \\
&mldr; \\
&mldr; \\
c \cdot a_{n} \\
\end{pmatrix}
$$

#### Das Skalarprodukt

Zunächst einmal weisen wir darauf hin, dass es hier möglicherweise etwas verwirrenden Namensgebungen für 
unterschiedliche Rechenoperationen mit Vektoren gibt.

Der Begriff "Skalarprodukt" kann zwei verschiedene Operationen bezeichnen: die Multiplikation von zwei Vektoren, was einen Skalar ergibt, und die Multiplikation eines Skalars mit einem Vektor, was das Ergebnis ein Vektor ist. Zur besseren Unterscheidung werden oft folgende Begriffe verwendet: 

Skalarprodukt (Vektor x Vektor): Das Ergebnis ist ein Skalar (eine Zahl). Alternativ kann man auch Punktprodukt sagen, um den Unterschied zu verdeutlichen.

Skalare Multiplikation (Skalar x Vektor): Das Ergebnis ist ein Vektor.

| Operation | Begriff | Ergebnis |
| :---- | :---- | :---- |
| Vektor &times; Vektor | Skalarprodukt oder Punktprodukt | Skalar (Wert) |
| Skalar &times; Vektor | Skalare Multiplikation | Vektor |

*Tabelle* 1: Unterscheidung Skalarprodukt versus skalare Multiplikation.





## Vektoren

In der Mathematik und Physik spielen Skalare und Vektoren eine große Rolle.
Während man unter einem Skalar eine Größe versteht, deren Wert sich eindeutig durch die Angabe einer Maßzahl beschreiben lässt,
benötigt man zur vollständigen Charakterisierung eines Vektors noch die Angabe einer Richtung im Raum.
So lassen sich beispielsweise Windgeschwindigkeiten, Beschleunigungen, elektrische oder magnetische Feldstärken durch Vektoren beschreiben.


## Darstellung eines Vektors in C++
