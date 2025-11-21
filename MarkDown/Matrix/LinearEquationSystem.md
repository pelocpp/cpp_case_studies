# Lineare Gleichungssysteme

https://share.google/aimode/aft5asTCDimwL1wgI


Der Gauß-Algorithmus &ndash; auch als Gaußsches Eliminationsverfahren bezeichnet &ndash; ist eine Methode
zur Lösung linearer Gleichungssysteme.

Der Algorithmus besteht aus zwei Hauptphasen:

  * **Vorwärtselimination**: Die erweiterte Koeffizientenmatrix wird in obere Dreiecksform gebracht. Dabei werden durch äquivalente Zeilenumformungen systematisch Variablen eliminiert, sodass unter der Hauptdiagonalen der Matrix nur noch Nullen stehen.
  * **Rückwärtssubstitution**: Die Variablen werden von unten nach oben berechnet und in die darüberliegenden Gleichungen eingesetzt.

Unter der erweiterten Koeffizientenmatrix verstehen wir eine Matrix, die neben den Elementen des Gleichungssystems
auch die Elemente des Vektors auf der rechten Seite enthält.



Bemerkung:<br />
In einer sehr einfachen Realisierung kann man hierbei auf die so genannte *Pivotisierung* verzichten.
Ohne Pivotisierung kann der Algorithmus instabil werden oder fehlschlagen, wenn ein Diagonalelement (Pivot-Element) null oder sehr nahe bei null ist.
Die Pivotisierung wird normalerweise verwendet, um dies zu vermeiden und die numerische Stabilität zu gewährleisten


## Einfache Darstellung des Algorithmus




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

---
---
---



## Test Tabellen und lineare Gleichungssystem

Wir betrachten zum Lösung eines linearen Gleichungssystems den Algorithmus von Gauß.


https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/

Was versteht man Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauß
unter der Vorwärtselimination?

Wie funktioniert die Vorwärtselimination beim
Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauß
im Detail?

Wie funktioniert die Rückwärtssubstitution beim
Lösen eines linearen Gleichungssystems nach dem Algorithmus von Gauß
im Detail?


## Lösen eines linearen Gleichungssystems

Wir betrachten zum Lösung eines linearen Gleichungssystems den Algorithmus von Gauß.
Die Vorwärtselimination ist hierbei der erste Schritt des Algorithmus,
bei dem ein lineares Gleichungssystem schrittweise in eine obere Dreiecksform umgewandelt wird.

Das Ziel ist die Umwandlung in ein System von vereinfachten Gleichungen,
das von unten nach oben leicht lösbar ist.

Wir betrachten nun im Detail die Schritte der Vorwärtselimination.

   * Aufschreiben der erweiterten Koeffizientenmatrix:<br />
Zunächst ist das lineare Gleichungssystem in eine erweiterte Matrix so umzuformulieren,
dass die Koeffizienten der Variablen in den ersten *m* Spalten einer *n*&times;*m*+1 Matrix
und die konstanten Werte auf der rechten Seite der Gleichungen in der *m*+1.-ten Spalte stehen:

   * Auswahl des Pivotelements:<br />
Wählen Sie in der ersten Spalte das erste Element als Pivotelement aus.
Im einfachsten Fall ist dies das erste Element der Spalte.
Diese Auswahl erfolgt unter der Annahme, dass der Wert von Null verschieden ist.
Andernfalls ist für diese Zeile nichts zu tun.<br />   
*Bemerkung*:<br />
Bei der Gleitkommaarithmetik sind Rundungsfehler möglich. Aus diesem Grund sind sehr kleine Zahlen im Nenner von Brüchen ungünstig,
da diese bei der Berechung des Bruchs zu Ungenauigkeiten führen können.
Bei der Auswahl des Pivotelements gibt es daher auch den Ansatz, nicht das erste (oberste) Element in der aktuellen Spalte zu wählen,
sondern das größte Element in der Spalte zu wählen. Dies kann nur funktionieren, wenn dann die entsprechenden Zeilen getauscht werden.
Wir stellen diesen Ansatz weiter unten vor.

   * Eliminieren der Elemente unter dem Pivotelement:<br />
Verwenden Sie das Pivotelement, um alle Koeffizienten in der ersten Spalte unterhalb der ersten Zeile
auf Null zu setzen.
Dazu subtrahieren wir ein geeignetes Vielfaches der ersten Zeile von den jeweiligen darunterliegenden Zeilen.

   * Fortsetzen für die nächsten Spalten:<br />
Man bewege sich zur zweiten Spalte. Die erste Zeile wird nicht mehr für die folgenden Umformungen verwendet.
Wählen Sie in der zweiten Spalte das nächste Pivotelement, das nun der erste Nicht-Null-Eintrag in der zweiten Zeile ist.
Wiederholen Sie den Eliminationsschritt, indem Sie ein Vielfaches der zweiten Zeile von den darunterliegenden Zeilen subtrahieren,
um die Einträge in der zweiten Spalte auf Null zu setzen.

   * Wiederholungen bis zur Dreiecksform:<br />

Führen Sie diesen Vorgang für alle Spalten fort, bis die Matrix in der oberen Dreiecksform vorliegt. Das bedeutet, alle Einträge unter der Hauptdiagonalen sind Null. 

### Detaillierte Beschreibung der Rückwärtssubstitution

Die Rückwärtssubstitution beim Gauß-Algorithmus ist ein Verfahren, bei dem man,
nachdem ein lineares Gleichungssystem in die obere Dreiecksform gebracht wurde,
die Lösungen schrittweise &bdquo;von unten nach oben&rdquo; ermittelt.

Man beginnt mit der letzten Gleichung, die nur eine Unbekannte enthält, um deren Wert zu bestimmen.
Diesen Wert setzt man dann in die Gleichung darüber ein, um die nächste Variable zu ermitteln,
und fährt so fort, bis alle Variablen berechnet sind. 

### Schritt-für-Schritt-Anleitung

  * Beginnen Sie mit der letzten Zeile:<br />
In der oberen Dreiecksform (auch Zeilenstufenform genannt) ist die letzte Zeile des Gleichungssystems eine einfache Gleichung,
die nur eine Unbekannte enthält. Sie können diese Gleichung nun direkt nach dieser Variable auflösen.

  * Setzen Sie den Wert in die vorletzte Zeile ein:<br />
Nehmen Sie den gerade berechneten Wert und setzen Sie ihn in die vorletzte Gleichung ein.
Diese Gleichung enthält nun nur noch zwei Unbekannte, von denen eine bekannt ist.

  * Lösen Sie nach der nächsten Variablen auf:<br />
Die Gleichung hat sich zu einer linearen Gleichung mit nur noch einer unbekannten Variablen reduziert,
die Sie nun leicht berechnen können.

  * Wiederholen Sie den Vorgang:<br />
Setzen Sie die Werte der beiden gerade berechneten Variablen in die nächsthöhere Gleichung ein.
Auch diese vereinfacht sich nun zu einer Gleichung, die nur noch eine unbekannte Variable enthält.
Fahren Sie so fort, bis Sie alle Werte ermittelt haben.

Zum Schluss setzen Sie die Werte aller bereits berechneten Variablen in die erste Gleichung ein,
um die letzte verbliebene Variable zu bestimmen und um das System vollständig zu lösen. 


### Ein ausführliches Beispiel

Wir betrachten die einzelnen Schritte während der Vorwärtselimination und Rückwärtssubstitution
nun im Detail. Es handelt sich um ein lineares Gleichungssystem
mit den vier Unbekannten *x*<sub>0</sub>, *x*<sub>1</sub>, *x*<sub>2</sub> und *x*<sub>3</sub>:

<pre>
 3<i>x</i><sub>3</sub> + 1<i>x</i><sub>2</sub> - 5<i>x</i><sub>1</sub> + 4<i>x</i><sub>0</sub> = -18
 2<i>x</i><sub>3</sub> - 3<i>x</i><sub>2</sub> + 3<i>x</i><sub>1</sub> - 2<i>x</i><sub>0</sub> =  19
 5<i>x</i><sub>3</sub> - 3<i>x</i><sub>2</sub> + 4<i>x</i><sub>1</sub> + 1<i>x</i><sub>0</sub> =  22
-2<i>x</i><sub>3</sub> + 4<i>x</i><sub>2</sub> - 3<i>x</i><sub>1</sub> - 5<i>x</i><sub>0</sub> = -14
</pre>

Wir führen die Schritte des Gauß Algorithmus jeweils in 2 Varianten durch:
Zum einen in Gleitpunktarithmetik, so wie es Maschinenprogramme (mit einer entsprechenden Genauigkeit oder eben auch Ungenauigkeit) tun würden.
Zum anderen mit Brüchen, um das Ergebnis exakt bestimmen zu können.

Wir werden sehen, dass auch bei der Durchführung mit Gleitpunktarithmetik die Ungenauigkeiten nicht so groß sind.


#### Betrachtung der Vorwärtselimination

##### Elimintation der Null in der ersten Spalte

###### Umwandlung der zweiten Gleichung

Wir wählen das Pivot-Element 2/3:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +    4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> - 14/3<i>x</i><sub>0</sub> =  31
 5<i>x</i><sub>3</sub> -    3<i>x</i><sub>2</sub> +    4<i>x</i><sub>1</sub> +    1<i>x</i><sub>0</sub> =  22
-2<i>x</i><sub>3</sub> +    4<i>x</i><sub>2</sub> -    3<i>x</i><sub>1</sub> -    3<i>x</i><sub>0</sub> = -14
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -     5<i>x</i><sub>1</sub> +      4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> + 6.333<i>x</i><sub>1</sub> -  4.666<i>x</i><sub>0</sub> =  31
 5<i>x</i><sub>3</sub> -    3<i>x</i><sub>2</sub> +     4<i>x</i><sub>1</sub> +      1<i>x</i><sub>0</sub> =  22
-2<i>x</i><sub>3</sub> +    4<i>x</i><sub>2</sub> -     3<i>x</i><sub>1</sub> -      3<i>x</i><sub>0</sub> = -14
</pre>

---

###### Umwandlung der dritten Gleichung

Wir wählen das Pivot-Element 5/3:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +    4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> - 14/3<i>x</i><sub>0</sub> =  31
      -14/3<i>x</i><sub>2</sub> + 37/3<i>x</i><sub>1</sub> - 17/3<i>x</i><sub>0</sub> =  52
-2<i>x</i><sub>3</sub> +     4<i>x</i><sub>2</sub> -   3<i>x</i><sub>1</sub> -    3<i>x</i><sub>0</sub> = -14
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -      5<i>x</i><sub>1</sub> +      4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> -  4.666<i>x</i><sub>0</sub> =  31
     -4.666<i>x</i><sub>2</sub> + 12.333<i>x</i><sub>1</sub> -  5.666<i>x</i><sub>0</sub> =  52
-2<i>x</i><sub>3</sub> +    4<i>x</i><sub>2</sub> -      3<i>x</i><sub>1</sub> -      3<i>x</i><sub>0</sub> = -14
</pre>

---

###### Umwandlung der vierten Gleichung

Wir wählen das Pivot-Element -2/3:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +    4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> - 14/3<i>x</i><sub>0</sub> =  31
      -14/3<i>x</i><sub>2</sub> + 37/3<i>x</i><sub>1</sub> - 17/3<i>x</i><sub>0</sub> =  52
       14/3<i>x</i><sub>2</sub> - 19/3<i>x</i><sub>1</sub> -  7/3<i>x</i><sub>0</sub> = -26
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub>  +   1<i>x</i><sub>2</sub> -      5<i>x</i><sub>1</sub> +      4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> -  4.666<i>x</i><sub>0</sub> =  31
     -4.666<i>x</i><sub>2</sub> + 12.333<i>x</i><sub>1</sub> -  5.666<i>x</i><sub>0</sub> =  52
      4.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> -  2.333<i>x</i><sub>0</sub> = -26
</pre>

---

##### Elimintation der Null in der zweiten Spalte

###### Umwandlung der dritten Gleichung

Wir wählen das Pivot-Element 14/11:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +    4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> - 14/3<i>x</i><sub>0</sub> =  31
              141/33<i>x</i><sub>1</sub> + 9/33<i>x</i><sub>0</sub> =  138/11
       14/3<i>x</i><sub>2</sub> - 19/3<i>x</i><sub>1</sub> -  1/3<i>x</i><sub>0</sub> = -26
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub>  +   1<i>x</i><sub>2</sub> -      5<i>x</i><sub>1</sub> +     4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> - 4.666<i>x</i><sub>0</sub> = 31
                 4.272<i>x</i><sub>1</sub> + 0.272<i>x</i><sub>0</sub> = 12,545
      4.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> - 0.333<i>x</i><sub>0</sub> = -26
</pre>


###### Umwandlung der vierten Gleichung

Wir wählen das Pivot-Element -14/11:

<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +      4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> -   14/3<i>x</i><sub>0</sub> = 31
              141/33<i>x</i><sub>1</sub> +   9/33<i>x</i><sub>0</sub> = 138/11
               57/33<i>x</i><sub>1</sub> - 273/33<i>x</i><sub>0</sub> = 148/11
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub>  +   1<i>x</i><sub>2</sub> -      5<i>x</i><sub>1</sub> +     4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> - 4.666<i>x</i><sub>0</sub> = 31
                 4.272<i>x</i><sub>1</sub> + 0.272<i>x</i><sub>0</sub> = 12,545
                 1.727<i>x</i><sub>1</sub> - 8.272<i>x</i><sub>0</sub> = 13.454
</pre>


---

##### Elimintation der Null in der dritten Spalte

###### Umwandlung der vierten Gleichung

Wir wählen das Pivot-Element 57/141:


<pre>
 3<i>x</i><sub>3</sub> +    1<i>x</i><sub>2</sub> -    5<i>x</i><sub>1</sub> +      4<i>x</i><sub>0</sub> = -18
      -11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> -   14/3<i>x</i><sub>0</sub> = 31
              141/33<i>x</i><sub>1</sub> +   9/33<i>x</i><sub>0</sub> = 138/11
                    -39006/4653<i>x</i><sub>0</sub> = 13002/1551
</pre>

oder in Gleitpunktdarstellung:

<pre>
 3<i>x</i><sub>3</sub>  +   1<i>x</i><sub>2</sub> -      5<i>x</i><sub>1</sub> +     4<i>x</i><sub>0</sub> = -18
     -3.666<i>x</i><sub>2</sub> -  6.333<i>x</i><sub>1</sub> - 4.666<i>x</i><sub>0</sub> = 31
                 4.272<i>x</i><sub>1</sub> + 0.272<i>x</i><sub>0</sub> = 12,545
                         -8.3829<i>x</i><sub>0</sub> = 8,38297
</pre>

---


### Berechnung des Ergebnisses mit der Rückwärtssubstitution

Wir wollen einmal das Verfahren der Rückwärtssubstitution ansehen.
Die letzte, umgewandelte Gleichung lautet

<pre>
-39006/4653<i>x</i><sub>0</sub> = 13002/1551
</pre>

Da können wir die Zähler mit `13002` und die Nenner mit `1551` kürzen und erhalten

<pre>
-3/3<i>x</i><sub>0</sub> = -<i>x</i><sub>0</sub> = 1/1 = 1
</pre>

Folglich berechnet sich <i>x</i><sub>0</sub> zu -1.
Dieser Wert wird nun in die vorletzte Gleichung eingesetzt:

<pre>
141/33<i>x</i><sub>1</sub> + 9/33<i>x</i><sub>0</sub> = 138/11
</pre>

also

<pre>
141/33<i>x</i><sub>1</sub> - 9/33 = 138/11
</pre>

Weiter zu

<pre>
141/33<i>x</i><sub>1</sub> = 138/11 + 9/33 = (138*3)/33 + 9/33 = 423/33
</pre>

und 

<pre>
141<i>x</i><sub>1</sub> = 423
</pre>

und damit ist <i>x</i><sub>1</sub> gleich 3.

Auf geht es zur dritten Gleichung von unten aus gesehen:

<pre>
-11/3<i>x</i><sub>2</sub> + 19/3<i>x</i><sub>1</sub> - 14/3<i>x</i><sub>0</sub> = 31
</pre>

<i>x</i><sub>0</sub> gleich -1 und <i>x</i><sub>1</sub> gleich 3 eingesetzt ergibt 

<pre>
-11/3<i>x</i><sub>2</sub> + (3*19)/3 + 14/3 = 31
</pre>

Weiter folgt

<pre>
-11/3<i>x</i><sub>2</sub> + 19 + 14/3 = 31
</pre>

und 

<pre>
-11/3<i>x</i><sub>2</sub> = 31 - 19 - 14/3 = ((3*31) - (19*3) - 14)/3 = (93-57-14)/3 = 22/3
</pre>

Damit folgt

<pre>
-11<i>x</i><sub>2</sub> = 22
</pre>

Es ist somit 1<i>x</i><sub>2</sub> gleich -2. Alle drei gefundenen Werte setzen wir in die erste Gleichung ein:

<pre>
3<i>x</i><sub>3</sub> + 1<i>x</i><sub>2</sub> - 5<i>x</i><sub>1</sub> + 4<i>x</i><sub>0</sub> = -18
</pre>

Sprich

<pre>
3<i>x</i><sub>3</sub> -2 - 5*3 - 4 = -18
</pre>

und damit

<pre>
3<i>x</i><sub>3</sub> = -18 + 2 + 5*3 + 4 = -18 + 2 + 15 + 4 = -18 + 21 = 3 
</pre>

Es ergibt sich <i>x</i><sub>3</sub> = 1.

Abschließend können wir den berechneten
Lösungsvektor `{` <i>x</i><sub>3</sub>, <i>x</i><sub>2</sub>, <i>x</i><sub>1</sub>, <i>x</i><sub>0</sub> `}` = `{ 1, -2, 3, -1 }` mit der Matrix des Gleichungssystems multiplizieren,
um uns von der Korrektheit des Ergebnisses überzeugen zu können:


<pre>
 3<i>x</i><sub>3</sub> + 1<i>x</i><sub>2</sub> - 5<i>x</i><sub>1</sub> + 4<i>x</i><sub>0</sub> =  3 * 1 + 1 * (-2) - 5 * 3 + 4 * (-1) = -18
 2<i>x</i><sub>3</sub> - 3<i>x</i><sub>2</sub> + 3<i>x</i><sub>1</sub> - 2<i>x</i><sub>0</sub> =  2 * 1 - 3 * (-2) + 3 * 3 - 2 * (-1) =  19
 5<i>x</i><sub>3</sub> - 3<i>x</i><sub>2</sub> + 4<i>x</i><sub>1</sub> + 1<i>x</i><sub>0</sub> =  5 * 1 - 3 * (-2) + 4 * 3 + 1 * (-1) =  22
-2<i>x</i><sub>3</sub> + 4<i>x</i><sub>2</sub> - 3<i>x</i><sub>1</sub> - 5<i>x</i><sub>0</sub> = -2 * 1 + 4 * (-2) - 3 * 3 - 5 * (-1) = -14
</pre>


