<!-- HouseOfSantaClaus.md -->

Das Haus des Nikolaus ist ein altes Zeichenspiel und vermutlich jedem Leser unter Ihnen bekannt,
der Kinder sein eigen nennen darf. Ziel des Spiels ist es, ein Haus (wie in [Abbildung 1] dargestellt)
&ldquo;ohne Absetzen des Stiftes&ldquo; zu zeichnen, also in einem Zug mit acht Strecken.
Sie werden die Beobachtung machen, dass dies nicht immer zum Ziel führt,
da man öfters in die Situation gelangt, eine Strecke mehrmals zeichnen zu müssen,
was nicht erlaubt ist. Kinder erfreuen sich an diesem Spiel zusätzlich daran,
ihre Eltern lautstark am Spielen zu beteiligen, indem sie an jeder Ecke, die sie erreichen,
ein Wort des Satzes &ldquo;Das ist das Haus vom Ni&ndash;ko&ndash;laus&rdquo; aussprechen &ndash; zu
jeder Strecke gehört ein Wort bzw. eine Silbe.
Wie viele verschiedene Möglichkeiten gibt es, das Haus zu zeichnen?

###### {#abbildung_1_house_of_santa_claus}

{{< figure src="/img/houseofsantaclaus/HouseSantaClaus_01.png" width="50%" >}}

*Abbildung* 1: Das Haus des Nikolaus &ndash; als Spiel betrachtet.

<img src="./HouseSantaClaus_01.png" alt="alt text" width="100"/>

Entwerfen Sie geeignet ein oder mehrere C++&ndash;Klassen,
um alles Lösungen des &ldquo;Haus des Nikolaus&rdquo;-Problems zu ermitteln.

Im Lösungsvorschlag finden Sie zwei Realisierungsansätze vor:

  * eine klassisch Realisierung
  * eine C++20&ndash;Realisierung mit &ldquo;Ranges&rdquo;

Schreiben Sie ein Programm, das alle Möglichkeiten berechnet und in ansprechender Form auf der Konsole ausgibt.


<!--more-->

# Lernziele

  * To Be Done
  * Einheitliche Initialisierung
  * Initialisierungsliste (`std::initializer_list<T>`)
  * STL-Klasse `std::vector<T>`
  * C++ Iteratorenkonzept
  * Container-Methoden `rbegin()` und `rend()`
  * `std::move`  aus dem *Standard Library Header* `<algorithm>`
  * STL-Algorithmen `std::begin`, `std::end`, `std::for_each`, `std::next`, `std::transform`, `std::find_if`

# Einführung

Die Umsetzung der Fragestellung erfordert zunächst eine Analyse des geschilderten Problems mit der Zielsetzung,
ein mathematisches Modell zu finden, auf das das Haus des Nikolaus abbildbar ist.
Einfache Überlegungen zeigen, dass das Haus des Nikolaus als ein ungerichteter Graph angesehen werden kann
mit fünf Knoten (die Ecken des Hauses) und acht Kanten (die Verbindungen zwischen den Knoten),
siehe die linke Seite in [Abbildung 2]. Unter einem *ungerichteten* Graphen versteht man einen Graphen,
für dessen Kanten keine Regelung besteht, in welcher Richtung sie durchlaufen werden müssen.

###### {#abbildung_2_house_of_santa_claus}

{{< figure src="/img/houseofsantaclaus/HouseSantaClaus_02.png" width="50%" >}}

*Abbildung* 2: Das Haus des Nikolaus &ndash; von einem Mathematiker betrachtet.

<img src="./HouseSantaClaus_02.png" alt="alt text" width="100"/>

Damit haben wir die Aufgabenstellung auf die Frage reduziert,
wieviele Wege es in einem bestimmten ungerichteten Graphen gibt, der jede Kante genau einmal traversiert.
Eine Lösung des Problems finden Sie in [Abbildung 2] auf der rechten Seite vor:
Eine zu zeichnende Kante wird als Paar der zugehörigen Knoten repräsentiert:
(1,2) für die erste gezeichnete Kante, (2,4) für die zweite usw.
Wir erkennen am Beispiel von (1,5) auch, dass nicht jedes Knotenpaar eine gültige Kante beschreibt!

# Ein iterativer Lösungsansatz

Wir betrachten in dieser Fallstudie einen iterativen Ansatz zur programmiersprachlichen Lösung der Aufgabe
in zwei Implementierungsvarianten. Es gibt auch einen rekursiven Lösungsansatz,
der geringe Kenntnisse aus der Graphentheorie voraussetzt, den wir hier aber nicht weiter verfolgen wollen.

Der iterative Ansatz assoziiert eine Lösung mit einer Folge von Ziffern, also mit einer natürlichen Zahl.
Dazu nummerieren wir die Ecken des Hauses durch, unten links liegt die Ecke 1, die Ziffern 2, 3 und 4 folgen
entgegen dem Uhrzeigersinn für die weiteren Ecken des Rechtecks. Fehlt noch die Spitze, sie erhält die Ziffer 5.
Dem in [Abbildung 2] gezeichneten Haus ordnen wir folglich beim Malen die Ziffernfolge 1, 2, 4, 1, 3, 4, 5, 3, 2 zu,
oder etwas kompakter die neunstellige Zahl 124134532.

Nicht alle neunstelligen Zahlen eignen sich zur Darstellung einer korrekten Zeichnung.
Zahlen, die die Ziffern 6 bis 9 oder die Null enthalten, scheiden von vorne herein aus.
Also kommen nur Zahlen zwischen 111111111 und 155555552 in Betracht.
Von diesen Zahlen sind solche, die zweimal dieselbe Ziffer unmittelbar aufeinanderfolgend enthalten,
wiederum nicht geeignet, da eine Kante prinzipiell
nur zwischen zwei Knoten (mit unterschiedlicher Knotennummer) verlaufen kann.
In dem zuvor beschriebenen Wertebereich scheiden also weitere Zahlen aus.

Nun sind wir fast schon am Ziel angekommen. Die Kanten des vorliegenden Graphen lauten gemäß der Knotennummerierung
aus [Abbildung 2] (1, 2), (1, 3), (1, 4), (2, 3), (2, 4), (3, 4), (3, 5) und (4, 5).
Eine neunstellige Zahl mit den Ziffern z<sub>1</sub>, z<sub>2</sub>, ... , z<sub>9</sub>
beschreibt ebenfalls 8 Kanten (z<sub>1</sub>, z<sub>2</sub>), (z<sub>2</sub>, z<sub>3</sub>) bis (z<sub>8</sub>, z<sub>9</sub>).
Finden wir jede Kante des Nikolaushauses genau einmal in der Menge der
Kanten (z<sub>i</sub>, z<sub>i+1</sub>), *i* = 1,2,...,8 vor,
so haben wir mit der neunstelligen Zahl einen zulässigen Weg zum Zeichnen gefunden.

Ein Mathematiker wiederum würde zu der Formulierung neigen, dass zwischen den beiden zuvor beschriebenen Kantenmengen
genau dann eine bijektive Abbildung existiert, wenn ein zulässiger Pfad zum Zeichnen vorliegt.
Da Sie aber definitiv kein Mathematikbuch erworben haben, vermutlich auch keines erwerben wollten,
habe ich es bei der etwas anschaulicheren Darstellung belassen &ndash; Ihr ausdrückliches Einverständnis
natürlich vorausgesetzt :-).

# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Im Folgenden stellen wir zwei Implementierungen für einen iterativen Lösungsansatz vor. 
Beide Lösungen besitzen natürlich gemeinsame Codeanteile. Diese lassen sich, ganz im Sinne des objektorientierten Paradigmas,
elegant in einer (abstrakten) Basisklasse `HouseOfSantaClaus` zusammenfassen ([Listing 1]):

Diese abstrakte Basisklasse führen wir aus mehreren Gründen ein. Zum einen, um festzulegen,
dass es eine abstrakte Methode `solve` (pure virtuell) gibt, die dazu da ist,
die Menge aller Lösungen des Problems zu berechnen. Damit ist klar, welche Erwartungen an eine Spezialisierung
der Klasse `HouseOfSantaClaus` gestellt werden. Zum anderen, um Methoden zu implementieren,
die von allen abgeleiteten Klassen einfach übernommen werden können (im Sinne der Vererbung)
und damit deren Realisierung vereinfachen.
Dazu zählt eine getter-Methode wie NumberOfSolutions, um die Anzahl der Lösungen zu ermitteln
wie auch eine Überladung des `<<`-Operators, um die berechneten Lösungen komfortabel auf der Konsole auszugeben.
Schnittstelle und Implementierung der abstrakten Basisklasse `HouseOfSantaClaus` finden Sie
in [Listing 1] und [Listing 2] vor:

###### {#listing_1_class_houseofsantaclaus_decl}

```cpp
```

*Listing* 1: Abstrakte Basisklasse `HouseOfSantaClaus`: Definition.

Wir fahren gleich mit der Implementierung der `HouseOfSantaClaus`-Klasse in [Listing 2] fort:

###### {#listing_2_class_houseofsantaclaus_impl}

```cpp
```

*Listing* 2: Abstrakte Basisklasse `HouseOfSantaClaus`: Realisierung.

*Hinweis*: Wenn Sie [Listing 1] und [Listing 2] genau betrachtet haben, dürfte Ihnen nicht entgangen sein,
dass ein klassischen Entwurfsmuster umgesetzt wurde: Das &ldquo;Template Method Pattern&ldquo;.
Methode `isSolution` besitzt in der Klasse `HouseOfSantaClaus` eine Realisierung,
die aus einer Reihe von auszuführenden Teilschritten (Teilmethoden) besteht,
die allesamt in Klasse  `HouseOfSantaClaus` nur abstrakt definiert sind.
In einer niedrigeren Abstraktionsebene (Detailebene) ist für diese Teilmethoden eine Implementierung bereitzustellen,
wir werden die Methoden `numberToDigits`, `checkValidRangeOfDigits`, `checkSelfLoops`, `checkValidEdges` und `checkForDuplicateEdges`
einmal &ldquo;klassisch&ldquo; und ein weiteres Mal mit der C++20 &ldquo;Ranges&ldquo;-Bibliothek implementieren-
Hierfür betrachten wir nachfolgend die beiden von `HouseOfSantaClaus` abgeleiteten Klassen
`HouseOfSantaClausIterative` und `HouseOfSantaClausRanges`.

Die Implementierung des `<<`-Operators in den Zeilen XX bis XX (inklusive der Hilfsmethode `printSolution`)
von [Listing 2] führt zu folgender Darstellungsform berechneter Lösungen:

```
1->2->3->1->4->3->5->4->2
...
```

Der Entwurf der Klasse `HouseOfSantaClaus` lässt es bereits erkennen:
Abgeleitete Klassen müssen sich nur noch um die Berechnung der Lösungen kümmern,
die Infrastruktur zur komfortablen Ablage der Lösungen wird ihnen von der Basisklasse bereit gestellt.
In [Listing 3] und [Listing 4] finden Sie die Klasse `HouseOfSantaClausIterative` mit einer Implementierung vor,
die klassische Sprachmittel von C++ verwendet. 

###### {#listing_3_class_houseofsantaclausiterative_decl}

```cpp
```

*Listing* 3: Konkrete Klasse `HouseOfSantaClausIterative`: Definition.

Wir fahren gleich mit der Implementierung der `HouseOfSantaClausIterative`-Klasse in [Listing 4] fort:

###### {#listing_4_class_houseofsantaclausiterative_impl}

```cpp
```

*Listing* 3: Konkrete Klasse `HouseOfSantaClausIterative`: Realisierung.

Die Klasse `HouseOfSantaClausIterative` besteht aus zahlreichen Methoden,
die sich mit der Analyse von Zahlen beschäftigen, um einen zulässigen Pfad im Nikolaushaus zu beschreiben.
Im iterativen Ansatz spielen Zahlen eine Rolle, die ausschließlich aus den Ziffern 1 bis 5 bestehen,
diese Überprüfung führt die Methode `checkValidRangeOfDigits` durch (Zeilen XX bis YY).
Aufeinanderfolgende identische Ziffern in einer Zahl stellen keinen Pfad dar,
hierzu gibt es eine Methode `checkSelfLoops` (Zeilen XX bis YY), die derlei Zahlen ausschließt.
Da nicht alle Knoten des Nikolaushauses miteinander verbunden sind, wenden wir uns als Nächstes den unzulässigen Kanten zu.
Durch die Methode `checkValidEdges` (Zeilen XX bis YY) wird sicher gestellt, dass Kanten zwischen
den Knoten 1 und 5 bzw. 2 und 5 ausgeschlossen werden.
Damit kommen wir zur letzten Hilfsmethode `CheckForDuplicateEdges`, deren Implementierung nicht übermäßig schwer ist,
dafür aber etwas trickreich erscheinen mag (Zeilen XX bis YY). Alle zulässigen Kanten dürfen in einem korrekten Pfad
durch das Nikolaushaus nur genau einmal vorkommen.
Durch zwei geschickt aufeinander abgestimmte `for`-Wiederholungsanweisungen wird dies durch
die `checkForDuplicateEdges`-Methode überprüft.

All die zuvor geschilderten Hilfsmethoden `CheckValidRangeOfDigits`, `CheckValidSequenceOfDigits`, `CheckValidEdges`
und `CheckForDuplicateEdges` benötigen die einzelnen Ziffern einer Zahl der Einfachheit halber in einem Array angeordnet.
Diesem Zweck dient die Hilfsmethode `NumberToDigits` in den Zeilen 100 bis 107. Damit besitzt die `IsSolution`-Methode
in den Zeilen 27 bis 48 alle Zutaten, um iterativ alle möglichen (Zahlen-)Kandidaten des Nikolaushauses zu überprüfen.
Der Vorteil dieser Lösung ist, dass sie mit vergleichsweise einfachen programmiersprachlichen Hilfsmitteln implementierbar ist.

In einer zweiten Realisierung wollen wir die Ranges-Bibliothek aus C++20 einsetzen. 
Natürlich wollen wir damit einen Benefit erzielen, es soll die Bequemlichkeit und Mächtigkeit dieser Bibliothek
an einem vergleichweise einfachen Beispiel veranschaulicht werden ([Listing 5] und [Listing 5]):

###### {#listing_5_class_houseofsantaclausranges_decl}

```cpp
```

*Listing* 5: Abstrakte Basisklasse `HouseOfSantaClausRanges`: Definition.


###### {#listing_6_class_houseofsantaclausranges_impl}

```cpp
```

*Listing* 6: Abstrakte Basisklasse `HouseOfSantaClausRanges`: Realisierung.

TODO: BESCHREIBUNG EINIGER ASPEKTE IN DER REALISIERNIUNG

Vom Erfolg des Algorithmus können Sie sich an Hand der Ausgabe erzeugen,
sie ist in beiden Fällen (klassisch / Ranges-Bibliothek) identisch:

```
Iterative:   611 msecs.
1->2->3->1->4->3->5->4->2   1->2->3->1->4->5->3->4->2
1->2->3->4->1->3->5->4->2   1->2->3->4->5->3->1->4->2
1->2->3->5->4->1->3->4->2   1->2->3->5->4->3->1->4->2
1->2->4->1->3->4->5->3->2   1->2->4->1->3->5->4->3->2
1->2->4->3->1->4->5->3->2   1->2->4->3->5->4->1->3->2
1->2->4->5->3->1->4->3->2   1->2->4->5->3->4->1->3->2
1->3->2->1->4->3->5->4->2   1->3->2->1->4->5->3->4->2
1->3->2->4->3->5->4->1->2   1->3->2->4->5->3->4->1->2
1->3->4->1->2->3->5->4->2   1->3->4->1->2->4->5->3->2
1->3->4->2->1->4->5->3->2   1->3->4->2->3->5->4->1->2
1->3->4->5->3->2->1->4->2   1->3->4->5->3->2->4->1->2
1->3->5->4->1->2->3->4->2   1->3->5->4->1->2->4->3->2
1->3->5->4->2->1->4->3->2   1->3->5->4->2->3->4->1->2
1->3->5->4->3->2->1->4->2   1->3->5->4->3->2->4->1->2
1->4->2->1->3->4->5->3->2   1->4->2->1->3->5->4->3->2
1->4->2->3->4->5->3->1->2   1->4->2->3->5->4->3->1->2
1->4->3->1->2->3->5->4->2   1->4->3->1->2->4->5->3->2
1->4->3->2->1->3->5->4->2   1->4->3->2->4->5->3->1->2
1->4->3->5->4->2->1->3->2   1->4->3->5->4->2->3->1->2
1->4->5->3->1->2->3->4->2   1->4->5->3->1->2->4->3->2
1->4->5->3->2->1->3->4->2   1->4->5->3->2->4->3->1->2
1->4->5->3->4->2->1->3->2   1->4->5->3->4->2->3->1->2
Solutions:   44
Range based: 696 msecs.
1->2->3->1->4->3->5->4->2   1->2->3->1->4->5->3->4->2
1->2->3->4->1->3->5->4->2   1->2->3->4->5->3->1->4->2
1->2->3->5->4->1->3->4->2   1->2->3->5->4->3->1->4->2
1->2->4->1->3->4->5->3->2   1->2->4->1->3->5->4->3->2
1->2->4->3->1->4->5->3->2   1->2->4->3->5->4->1->3->2
1->2->4->5->3->1->4->3->2   1->2->4->5->3->4->1->3->2
1->3->2->1->4->3->5->4->2   1->3->2->1->4->5->3->4->2
1->3->2->4->3->5->4->1->2   1->3->2->4->5->3->4->1->2
1->3->4->1->2->3->5->4->2   1->3->4->1->2->4->5->3->2
1->3->4->2->1->4->5->3->2   1->3->4->2->3->5->4->1->2
1->3->4->5->3->2->1->4->2   1->3->4->5->3->2->4->1->2
1->3->5->4->1->2->3->4->2   1->3->5->4->1->2->4->3->2
1->3->5->4->2->1->4->3->2   1->3->5->4->2->3->4->1->2
1->3->5->4->3->2->1->4->2   1->3->5->4->3->2->4->1->2
1->4->2->1->3->4->5->3->2   1->4->2->1->3->5->4->3->2
1->4->2->3->4->5->3->1->2   1->4->2->3->5->4->3->1->2
1->4->3->1->2->3->5->4->2   1->4->3->1->2->4->5->3->2
1->4->3->2->1->3->5->4->2   1->4->3->2->4->5->3->1->2
1->4->3->5->4->2->1->3->2   1->4->3->5->4->2->3->1->2
1->4->5->3->1->2->3->4->2   1->4->5->3->1->2->4->3->2
1->4->5->3->2->1->3->4->2   1->4->5->3->2->4->3->1->2
1->4->5->3->4->2->1->3->2   1->4->5->3->4->2->3->1->2
Solutions:   44
```


// ==================

WEITER !!!

// ==================


# There&lsquo;s more

Unsere bisherigen Betrachtungen haben sich ausschließlich auf Polynome mit Koeffizienten des Typs `double` beschränkt.
Mittlerweile unterstützt C++ drei Gleitkommadatentypen:

  * `float` &ndash; Gleitkommatyp mit einfacher Genauigkeit.
  * `double` &ndash; Gleitkommatyp mit doppelter Genauigkeit.
  * `long double` &ndash; Gleitkommatyp mit erweiterter doppelter Genauigkeit.

Welche Änderungen sind an der Klasse `Polynom` vorzunehmen,
um Polynome mit unterschiedlichen Gleitkommadatentypen definieren zu können?

# There&lsquo;s much more

In C++ 20 wird ein neues Sprachkonzept &ndash; genannt *Concepts* &ndash; eingeführt.
Mit *Concepts* kann man Restriktionen für Datentypen festzulegen, die eine Template-Funktion oder -klasse annehmen kann.

Definieren Sie Ihre Klasse `Polynom<T>` mit Hilfe von *Concepts* so, dass ausschließlich die drei Datentypen
`float`, `double` und `long double` als Template-Argument in Betracht kommen!

<br/>

<!-- Links Definitions -->

[Abbildung 1]:  #abbildung_1_house_of_santa_claus
[Abbildung 2]:  #abbildung_2_house_of_santa_claus

[Listing 1]: #listing_1_class_houseofsantaclaus_decl
[Listing 2]: #listing_2_class_houseofsantaclaus_impl
[Listing 3]: #listing_3_class_houseofsantaclausiterative_decl
[Listing 4]: #listing_4_class_houseofsantaclausiterative_impl
[Listing 5]: #listing_5_class_houseofsantaclausranges_decl
[Listing 6]: #listing_6_class_houseofsantaclausranges_impl

<!-- End-of-File -->
