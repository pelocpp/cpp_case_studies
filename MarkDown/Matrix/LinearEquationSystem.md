# Lineare Gleichungssysteme

https://share.google/aimode/aft5asTCDimwL1wgI


Der Gauß-Algorithmus &ndash; auch als Gaußsches Eliminationsverfahren bezeichnete &ndash; ist eine Methode
zur Lösung linearer Gleichungssysteme, bei der die Matrix in eine obere Dreiecksform (Zeilenstufenform) überführt wird.

Dies geschieht durch elementare Zeilenoperationen (Multiplizieren einer Zeile mit einer Zahl ungleich Null,
Addieren des Vielfachen einer Zeile zu einer anderen Zeile), ohne die Reihenfolge der Zeilen zu tauschen.

Bemerkung:<br />
In einer sehr einfachen Realisierung kann man hierbei auf die so genannte *Pivotisierung* verzichten.
Ohne Pivotisierung kann der Algorithmus instabil werden oder fehlschlagen, wenn ein Diagonalelement (Pivot-Element) null oder sehr nahe bei null ist.
Die Pivotisierung wird normalerweise verwendet, um dies zu vermeiden und die numerische Stabilität zu gewährleisten


## Einfache Darstellung des Algorithmus

Der Algorithmus besteht aus zwei Hauptphasen:

  * **Vorwärtselimination**: Die erweiterte Koeffizientenmatrix wird in obere Dreiecksform gebracht.
  * **Rückwärtssubstitution**: Die Variablen werden von unten nach oben berechnet und in die darüberliegenden Gleichungen eingesetzt.


Unter der erweiterten Koeffizientenmatrix verstehen wir eine Matrix, die neben den Elementen des Gleichungssystems
auch die Elemente des Vektors auf der rechten Seite enthält.

## Schritt-für-Schritt-Erklärung der Vorwärtselimination

Angenommen, wir haben ein lineares Gleichungssystem mit *n* Gleichungen und *n* Unbekannten,
dargestellt durch die erweiterte Matrix [A|b].

Für jede Spalte *k* von 0 bis *n*-*2* (Indexierung beginnt bei 0):

  * Prüfung des Pivot-Elements: Stelle sicher, dass das Diagonalelement *A[k][k]* ungleich Null ist.
    Ohne Pivotisierung wird hier kein Zeilentausch vorgenommen; falls *A[k][k]==0*, bricht der Algorithmus ab oder liefert falsche Ergebnisse).
 
  * Elimination: Für jede Zeile *i* unterhalb der aktuellen Zeile *k* (von *k+1* bis *n-1*):
    * Berechne den Multiplikator *F=A[i][k]/A[k][k]*.
    * Subtrahiere das *F*-fache der Zeile *k* von der Zeile *i*, um *A[i][k]* zu Null zu machen. Wende dies auf alle Elemente in Zeile *i* an, einschließlich der rechten Seite *b*. 

## Schritt-für-Schritt-Erklärung der Rückwärtssubstitution

Nach der Elimination liegt eine obere Dreiecksmatrix vor. Wir können nun die Variablen von der letzten bis zur ersten berechnen:

Für jede Zeile *i* von *n-1* bis 0 (absteigend):
Löse die Gleichung für die Variable *x*<sub>i</sub> mit den bereits berechneten Werten
für *x*<sub>i+1</sub>, ... ,x*<sub>*n*-1</sub>*.

Die Formel lautet: *x*<sub>i</sub>=(b[i]-\sum *<sub>j=i+1</sub>^{n-1</sub>A[i][j]\cdot x*<sub>j</sub>)/A[i][i]*. 


<img src="Backward.png" width="500">

*Abbildung* 1: Berechnung eines Elements des Lösungsvektors.

