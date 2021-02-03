<!-- Das Springerproblem -->

Das Springerproblem (Schachspiel) ist auf den Schweizer Mathematiker *Leonhard Euler* (1707 &ndash; 1783) zurückzuführen. Dieser stellte sich vor über 200 Jahren, genauer im Jahre 1758, die folgende Frage: &ldquo;Gegeben sei ein leeres Schachbrett. Gibt es eine Zugfolge, mit der der Springer alle (schwarzen und weißen) Felder des Bretts genau einmal besucht?&rdquo;. Dabei legen wir zugrunde, dass der Springer auf dem Schachbrett in der Ecke unten links startet.

Hmmm, eine gute Frage, wird sich der geneigte Leser jetzt sagen. Möglicherweise kann man sie innerhalb von wenigen Minuten selbst lösen, schließlich ist ein Schachbrett mit seinen 8&#x00D7;8 Feldern nicht so wirklich groß.

Stellt man nach einer ersten Phase euphorischen Suchens ernüchternd fest, dass das Problem vielleicht doch nicht so einfach zu lösen ist, kommt man vielleicht auf den revolutionären Gedanken, dem Problem mit Hilfe eine Softwareprogramms auf den Leib zu rücken. Dies ist natürlich möglich, wie wir in dieser Fallstudie am Beispiel von C++ zeigen werden.

<!--more-->

Der Standardalgorithmus für die Lösung solcher Probleme ist das sogenannte *Backtracking*. Die Idee hierbei ist, die Figur solange zu setzen, bis entweder eine Lösung gefunden wurde, oder man sie nicht mehr weitersetzen kann. In diesem Fall geht man dann einen Zug zurück und versucht, eine Lösung über einen alternativen Weg zu finden. Auf diese Weise findet das Verfahren immer eine oder mehrere Lösungen &ndash; wenn es sie denn gibt.

Zu beachten ist dabei leider noch ein kleiner Schönheitsfehler: Die Laufzeiten derartiger Programme können immens sein (Tage, Wochen, Jahre, ...), je nachdem, welche Schachbretter wir betrachten, wenn wir das Springerproblem nicht nur für Schachbretter mit der Standardgröße von 8&#x00D7;8 Feldern analysieren, sondern verallgemeinern wollen. 

<!--more-->

<!--
Gegenstand dieser Fallstudie ist das klassische Springerproblem des Schachspiels. Die Springerfigur wird dazu auf ein beliebiges Feld eines *n*&#x00D7;*n* Schachbretts gestellt. Das Problem besteht nun darin, eine Zugfolge zu finden, bei der der Springer, entsprechend seiner Bewegungsmöglichkeiten im Schach, nacheinander alle Felder des Schachbrettes besetzt &ndash; jedes Feld genau einmal!
-->

Prinzipiell ist von vorneherein nicht klar, ob es überhaupt eine Lösung gibt. Wenn ja, kann es auch sein, dass mehrere Zugfolgen existieren! Eine mögliche Lösung des Springerproblems auf einem realen Schachbrett (also mit 64 Feldern) finden Sie in [Abbildung 1] vor:

###### {#abbildung_1_springer_problem_single_solution}

{{< figure src="/img/springer_problem/Knight_Problem_Single_Solution.png" width="80%" >}}

*Abbildung* 1: Eine Lösung des Springerproblems.

Mit den Rechnern der aktuellen Generation wird es sehr schwer sein, für ein 8×8 Schachbrett alle Lösungen zu bestimmen.
Wir konzentrieren uns deshalb in der Aufgabe auf kleinere Bretter. Die Anzahl realistisch ermittelbarer Lösungen für kleinere Schachbretter können Sie [Abbildung 2] entnehmen:

###### {#abbildung_2_springer_problem_number_of_solutions}

{{< figure src="/img/springer_problem/Knight_Moves_Solutions.png" width="80%" >}}

*Abbildung* 2: Einige Resultate des Springerproblems.

Die Zugregel für einen Springer kann man so beschreiben: Von seinem Ausgangsfeld kann er zuerst zwei Felder in eine beliebige Richtung gehen (keine Diagonale) und dann noch ein Feld zur Seite treten. Befindet er sich in einem der mittleren Felder des Spielfeldes, so gibt es 8 Zielfelder, die er betreten kann (siehe dazu auch [Abbildung 3]). Steht er hingegen mehr in der Nähe des Schachbrettrands, so verringert sich die Anzahl der Sprungmöglichkeiten entsprechend.

###### {#abbildung_3_springer_problem_possible_moves_of_knight}

{{< figure src="/img/springer_problem/knight_moves_possible_moves.svg" width="50%" >}}

*Abbildung* 3: Zugmöglichkeiten des Springers auf einem Schachbrett.

# Lösungsstrategie &ldquo;Trial and Error&rdquo;

Wir erläutern eine Lösungsstrategie für das Springerproblem am Beispiel eines 3&#x00D7;4-Schachbretts und erklären in einzelnen Schritten den Ablauf. Exemplarisch legen wir für den Springer die Startposition in der linken unteren Ecke fest, also das Feld mit den Koordinaten (2,0), wobei wir den Ursprung des Bretts in der linken, oberen Ecke zu Grunde legen. Es wäre aber auch jedes andere Feld zur Erörterung der Lösungsstrategie geeignet [Abbildung 4]. Die &ldquo;1&rdquo; symbolisiert, dass es sich um den ersten Zug des Springers handelt:


###### {#abbildung_4_springer_problem_knight_moves_01}
{{< figure src="/img/springer_problem/knight_moves_start.svg" width="25%" >}}
*Abbildung* 4: Ausgangssituation &ldquo;1&rdquo;: Springer wird im linken unteren Feld platziert.

Anhand der Ausgangsposition des Springers bestimmen wir nun eine Liste seiner möglichen Züge, die er von der aktuellen Position aus bestreiten kann. Sitzt der Springer auf dem Feld (2,0), so hat er in diesem Fall die Wahl zwischen zwei Zielfeldern (0,1) und (1,2), um weiter voran zu schreiten. Sie finden diese Felder in [Abbildung 5] grau hinterlegt vor. Wir entscheiden uns für das erste Feld aus der Liste, auf dem Schachbrett nehmen wir durch die &ldquo;2&rdquo; eine entsprechende Nummerierung vor:

###### {#abbildung_5_springer_problem_knight_moves_01}
{{< figure src="/img/springer_problem/knight_moves_01.svg" width="60%" >}}
*Abbildung* 5: Spielsituation &ldquo;2&rdquo;: Springer zieht von Feld (2,0) nach Feld (0,1).

Von der aktuellen Springerposition ausgehend bestimmen wir wieder alle möglichen Felder, auf die der Springer nun springen kann. Es ist wieder eine Liste mit zufälligerweise zwei Positionen, dieses Mal sind es die Felder (1,3) und (2,2), siehe [Abbildung 6]. Wir wählen wieder das erste Element aus der Liste aus und setzen die Figur auf das Feld (1,3):

###### {#abbildung_6_springer_problem_knight_moves_02}
{{< figure src="/img/springer_problem/knight_moves_02.svg" width="60%" >}}
*Abbildung* 6: Spielsituation &ldquo;3&rdquo;: Springer zieht von Feld (0,1) nach Feld (1,3).

Es wurden bei weitem noch nicht alle Felder des Schachbretts besucht. Von der Springerposition (1,3) ausgehend bietet sich dieses Mal aber nur ein einziges Feld (2,1) für den Folgezug an, siehe [Abbildung 7]:

###### {#abbildung_7_springer_problem_knight_moves_03}
{{< figure src="/img/springer_problem/knight_moves_03.svg" width="60%" >}}
*Abbildung* 7: Spielsituation &ldquo;4&rdquo;: Springer zieht von Feld (1,3) nach Feld (2,1).

Und noch einmal gilt es diese Runde zu drehen. Dieses Mal können wir zwei Felder (0,0) und (0,2) als mögliche nächste Kandidaten ausmachen. Wir entscheiden uns in [Abbildung 8] für das Feld (0,0):

###### {#abbildung_8_springer_problem_knight_moves_04}
{{< figure src="/img/springer_problem/knight_moves_04.svg" width="60%" >}}
*Abbildung* 8: Spielsituation &ldquo;5&rdquo;: Springer zieht von Feld (2,1) nach Feld (0,0).

Ich verspreche es, diese Runde drehen wir jetzt zum letzen Mal. Es gibt wieder nur ein einziges Feld zum Weiterspielen, in [Abbildung 9] erkennen Sie das weitere Vorgehen:

###### {#abbildung_9_springer_problem_knight_moves_05}
{{< figure src="/img/springer_problem/knight_moves_05.svg" width="60%" >}}
*Abbildung* 9: Spielsituation &ldquo;6&rdquo;: Springer zieht von Feld (0,0) nach Feld (1,2).

Wir sind an einer entscheidenden Stelle in der Betrachtung der Lösungsstrategie angekommen. Wenn Sie [Abbildung 9] betrachten, werden Sie erkennen, dass es von der aktuellen Springerposition aus betrachtet keine weitere Möglichkeit gibt, zu springen und damit zu einer Lösung des Springerproblems zu gelangen. Jetzt kommen die Listen mit den möglichen Folgezügen aus den vorherigen Schritten zum Zuge. Offensichtlich war die Auswahl eines Folgezugs in den Schritten zuvor nicht Erfolg versprechend. Wir müssen die Figur also auf die vorherige Ausgangssituation zurücksetzen. Da wir in diesem Schritt (im konkret vorliegenden Beispiel) aber nur einen einzigen Folgezug hatten, müssen wir gleich noch eine weitere Ausgangssituation zurücksetzen und kommen damit in [Abbildung 7] an. Dort hatten wir, vom Spielfeld mit der Nummer 4 ausgehend, die zwei möglichen Folgezüge (0,0) und (0,2) zur Auswahl. Die Entscheidung für (0,0) hat nicht zum Ziel geführt, also versuchen wir es jetzt mit der zweiten Alternative (0,2), siehe [Abbildung 10]. Wir verstehen jetzt, zu welchem Zweck die Listen mit den möglichen Folgezügen aufzubewahren sind. Gelangt man in einem bestimmten Schritt in die missliche Situation, dass es keine Folgezüge mehr gibt, muss man einen oder mehrere Schritte rückgängig machen und mit einem alternativen Folgezug sein Glück von Neuem versuchen.

###### {#abbildung_10_springer_problem_knight_moves_06}
{{< figure src="/img/springer_problem/knight_moves_06.svg" width="60%" >}}
*Abbildung* 10: Springer geht zur Spielsituation &ldquo;4&rdquo; zurück und springt jetzt von (2,1) nach Feld (0,2).

Dieses Verfahren läuft solange weiter, bis alle Felder des Schachbrettes besucht worden sind (und man damit eine Lösung gefunden hat), oder man feststellt, dass es keine Lösung gibt. Möchte man alle Lösungen zu einer bestimmten Schachbrettgröße finden, bricht man das Verfahren nach dem Entdecken einer Lösung nicht ab, sondern hinterlegt die gefundene Lösung in einer geeigneten Datenstruktur und setzt das Verfahren mit den noch vorhandenen Alternativzügen fort. Wenn Sie alles richtig gemacht haben, werden Sie bei dem betrachteten Beispiel eines 3&#x00D7;4-Schachbretts zwei Lösungen aufspüren, die Sie in [Abbildung 11] betrachten können:

###### {#abbildung_11_springer_problem_knight_moves_07}
{{< figure src="/img/springer_problem/knight_moves_07.svg" width="60%" >}}
*Abbildung* 11: Zwei Lösungen des Springerproblems auf einem 3&#x00D7;4-Schachbrett.

Die dargelegte Lösungsstrategie ist in der Informatik unter dem Begriff &ldquo;Trial and Error&rdquo; geläufig. Sie findet immer dann Anwendung, wenn zur Lösung eines Problems kein systematisches Verfahren zur Verfügung steht. Bei der &ldquo;Trial and Error&rdquo;-Methode werden nacheinander alle in Frage kommenden Lösungskandidaten durchprobiert, bis eine oder mehrere Lösungen gefunden wurden.

Im Falle des Springerproblems bedeutet dies, dass nach dem Setzen des Springers auf ein Ausgangsfeld maximal 8 Möglichkeiten zu betrachten sind, um auf das nächste Feld zu springen. Auf diesem Feld gibt es wiederum maximal 8 Möglichkeiten, um zum nächsten Feld weiterzuziehen usw. Geht es auf einem bestimmten Spielfeld überhaupt nicht mehr weiter, wird der letzte Schritt (beziehungsweise die letzten Schritte) zurückgenommen, und es werden stattdessen alternative Zugmöglichkeiten ausprobiert. Hieraus erklärt sich auch der Begriff &ldquo;Backtracking&rdquo;, der häufig bei &ldquo;Trial and Error&rdquo;-Problemen anzutreffen ist.

Durch das systematische Vorwärts- und Rückwärtsziehen des Springers auf dem Schachbrett ist sichergestellt, dass alle in Frage kommenden Lösungswege betrachtet werden. Bildlich gesprochen kann man die Bewegungen des Springers als &ldquo;Aufspannen eines Lösungsbaums&rdquo; ansehen [Abbildung 12]. In diesem Baum gilt es, Ast für Ast zu traversieren, um die Lösungen zu finden. Führt ein Ast nicht zu einer Lösung, so muss man auf diesem Ast ganz zurückgehen und einen anderen Ast überprüfen.

###### {#abbildung_12_springer_problem_solution_tree}
{{< figure src="/img/springer_problem/knight_moves_solution_tree.png" width="90%" >}}
*Abbildung* 12: Lösungsbaum eines Backtracking-Verfahrens.

In der programmiersprachlichen Umsetzung müssen wir den Lösungsbaum nicht explizit erzeugen. Backtracking-Verfahren lassen sich typischerweise am einfachsten rekursiv beschreiben, die Möglichkeit eines rekursiven Methodenaufrufs nimmt einem diese Arbeit quasi ab, oder noch verwirrender: Der Lösungsbaum wird auf dem Methodenaufrufstapel implizit, quasi versteckt aufgespannt.

In unserem konkreten Beispiel lässt sich nun zusammenfassend das Lösungsverfahren durch die in [Abbildung 13] skizzierte, rekursive Methode `FindMoves` darstellen:

TO BE DONE

###### {#abbildung_13_springer_problem_pseudo_code}
{{< figure src="/img/springer_problem/KnightsProblem_PseudoCode_01.png" width="90%" >}}
*Abbildung* 13: Grobskizze einer rekursiven Methode FindMoves zur Bestimmung aller Zugfolgen.

Wir schließen die theoretischen Vorarbeiten hiermit ab, es folgen Hinweise für eine Umsetzung des Lösungsverfahrens in einer *Modern C++*-Anwendung.

# Klasse `Coordinate`

Für die Koordinaten des Schachbretts verwenden wir eine Klasse `Coordinate`, um zwei ganzzahlige Werte *x* und *y*, die eine Position auf dem Schachbrett beschreiben, zu kapseln. Dafür gäbe es natürlich in C++ mehrere Möglichkeiten, eine von ihnen wäre der Einsatz der STL-Klasse `std::pair<T>`.
Ich habe mich für eine rudimentäre C++-Klasse `Coordinate` entschieden, deren Definition Sie [Tabelle 1] entnehmen können:

###### {#tabelle_1_class_coordinate}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `Coordinate();`<br/>Es wird die Koordinate `{0, 0}` erzeugt. |
| Benutzerdefinierter Konstruktor | `Coordinate(int row, int col);`<br/>Es wird die Koordinate mit Reihe `row` und Spalte `col` erzeugt. |
| *getter* `getRow()` | `int getRow();`<br/>Liefert die Reihe der Koordinate zurück. |
| *getter* `getCol()` | `int getCol();`<br/>Liefert die Spalte der Koordinate zurück. |
| Methode `fromOffset()` | `Coordinate<T> fromOffset(int rowOfs, int colOfs);`<br/>Liefert eine neue Koordinate zurück, die sich aus der aktuellen Koordinate modifiziert um die beiden Offsets `rowOfs` und `colOfs` ergibt. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const Coordinate&);`<br/>Gibt ein `Coordinate`-Objekt auf der Konsole aus. |

*Tabelle* 1: Wesentliche Elemente der Klasse `Coordinate`.

# Klasse `KnightProblemBoard`

Für das Schachbrett selbst definieren wir eine Klasse `KnightProblemBoard`. Im Großen und Ganzen kann man sagen, dass diese Klasse eine zwei-dimensionale
Ausprägung eines Objekts des Typs `std::array<>` kapselt. Mit seiner Hilfe lässt sich die Implementierung der noch ausstehenden Klasse `KnightProblemSolver` vereinfachen.

Ein Wert 0 im `std::array<>`-Objekt besagt, dass das korrespondierende Feld noch nicht vom Springer besucht wurde. Ganzzahlige Werte größer Null besagen, dass der Springer schon auf dem Feld war. Der Wert selbst gibt an, beim wievielten Zug das Feld betreten wurde:

###### {#abbildung_14_springer_problem_example_board}
{{< figure src="/img/springer_problem/knight_moves_board_example.svg" width="25%" >}}
*Abbildung* 12: Zweidimensionale Matrix zur Verwaltung eines 3&#x00D7;4 Schachbretts inklusive Springerzug.

Die Momentaufnahme des Beispiels aus [Abbildung 14] besagt, dass auf dem Schachbrett bereits ein Springerzug der Länge vier statt gefunden hat. Der Algorithmus ist offenbar noch damit beschäftigt, den vorliegenden Springerzug zu einem Zug mit 12 Sprüngen zu vervollständigen. Eine gefundene Lösung spiegelt sich in dem `std::array<>`-Objekt also dadurch wieder, dass keine Nullen mehr vorhanden sind und jeder Wert zwischen 1 und dem Produkt der Reihen- und Spaltenanzahl genau einmal auftritt. Zwei Beispiele solcher `std::array<>`-Objekte hatten wir in [Abbildung 11] schon gesehen.

 Mit [Tabelle 2] schließen wir die Betrachtung der Klasse `KnightProblemBoard` ab:

###### {#tabelle_2_class_knightproblemboard}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `KnightProblemBoard();`<br/>Es wird ein leeres Schachbrett angelegt, alle Felder sind mit 0 vorbelegt. |
| *getter* `at()` | `int& at(const Coordinate<T>& coord);`<br/>Liefert eine Referenz des Schachbretts an der Stelle `coord` zurück. |
| Methode `clearBoard()` | `void clearBoard();`<br/>Alle Felder des Schachbretts werden mit dem Wert 0 belegt. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const KnightProblemBoard&);`<br/>Gibt ein `KnightProblemBoard`-Objekt auf der Konsole aus. |

*Tabelle* 2: Wesentliche Elemente der Klasse `KnightProblemBoard`.

<!-- ########################################################################################### -->

# Klasse `KnightProblemSolver`

Wir kommen auf das Kernstück der Aufgabe zu sprechen. In der Klasse `KnightProblemSolver` wird auf Basis der Backtracking-Lösungsstrategie die Menge aller Springerproblemlösungen zu einer bestimmten Schachbrettgröße berechnet. Zunächst stellen wir in [Tabelle 3] den Konstruktor und die Eigenschaften der `KnightProblemSolver`-Klasse vor:

###### {#tabelle_3_class_knightproblemsolver_getters}

| Element | Beschreibung |
| :---- | :---- |
| *getter* `getRows()` | `int getRows();`<br/>Liefert die Anzahl der Reihen des Schachbretts zurück. |
| *getter* `getCols()` | `int getCols();`<br/>Liefert die Anzahl der Spalten des Schachbretts zurück. |
| *getter* `getSolutions()` | `std::list<std::vector<Coordinate<int>>> getSolutions();`<br/>Liefert die Liste aller ermittelten Lösungen des Springerzug-Problems zurück. Im Falle des Beispiels aus [Abbildung 11] sieht die Liste am Ende des Programms so aus:<br/>`{`<br/>&nbsp;&nbsp;`{`<br/>&nbsp;&nbsp;&nbsp;&nbsp;`{2,0}, {1,2}, {0,0}, {2,1}, {1,3}, {0,1},`<br/>&nbsp;&nbsp;&nbsp;&nbsp;`{2,2}, {0,3}, {1,1}, {2,3}, {0,2}, {1,0}`<br/>&nbsp;&nbsp;`},`<br/>&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;&nbsp;`{2,0}, {1,2}, {0,0}, {2,1}, {1,3}, {0,1},`<br/>&nbsp;&nbsp;&nbsp;&nbsp;`{2,2}, {1,0}, {0,2}, {2,3}, {1,1}, {0,3}`<br/>&nbsp;&nbsp;`}`<br/>`}`<br/> |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const KnightProblemSolver&);`<br/>Gibt ein `KnightProblemSolver`-Objekt auf der Konsole aus ???. |

*Tabelle* 3: *getter*-Methoden der Klasse `KnightProblemSolver`.

Weiter geht es mit den Instanzvariablen eines `KnightProblemSolver`-Objekts.
Im Mittelpunkt steht hier offensichtlich ein Objekt des Typs `KnightProblemBoard`, siehe [Tabelle 2].
Weitere, wichtige Instanzvariablen der `KnightProblemSolver`-Klasse, sofern sie durch die *getter*-Methoden aus [Tabelle 3] nicht schon abgehandelt wurden, entnehmen Sie bitte [Tabelle 4]:

<!-- ??????????????????????????????????????????????????????????????????????  -->

###### {#tabelle_4_class_knightproblemsolver_members}

| Instanzvariable | Beschreibung |
| :---- | :---- |
| `m_board` | `KnightProblemBoard m_board;`<br/>Repräsentiert das Schachbrett, das durch ein `KnightProblemSolver`-Objekt verwaltet wird. |
| `m_current` | `std::vector<Coordinate<int>> m_current;`<br/>Liste von `Coordinate`-Objekten zur Ablage eines Springerzugs. Zu Beginn der Suche ist das `m_current`-Objekt logischerweise leer. Dem Springerzug aus [Abbildung 14] entspricht das Listenobjekt<br/>`{ {2,0}, {1,2}, {0,0}, {2,1} }`. |
| `m_solutions` | `std::list<std::vector<Coordinate<int>>> m_solutions;`<br/>Liste der zu einem bestimmten Zeitpunkt während der Ausführung des  *Backtracking*-Algorithmus gefundenen Lösungen. |
| `m_moveNumber` | `int m_moveNumber;`<br/>Zähler für den Sprung im aktuellen Springerzug. Die Variable nimmt Werte zwischen 1 (Ausgangsposition) und Zeilenanzahl &#x00D7; Spaltenanzahl (letzter Zug eines Lösungszugs) an. |

*Tabelle* 4: Zentrale Instanzvariablen der Klasse `KnightProblemSolver`.

Wie findet man nun eine Folge von Springerzügen auf dem Schachbrett? Die Grobskizze der Methode `findMoves` aus [Abbildung 13] gilt es nun zu verfeinern. Hierzu betrachten wir in [Tabelle 4] zuerst alle Hilfsmethoden der Klasse `KnightProblemSolver`, die zur Realisierung der `findMoves`-Methode beitragen:

<!-- OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  -->

###### {#tabelle_5_class_knightproblemsolver_helpers}

| Methode | Beschreibung |
| :---- | :---- |
| `setKnightMoveAt` | `void setKnightMoveAt(const Coordinate& coord);`<br/>Setzt den Springer auf dem Schachbrett auf die Position `coord`. Im korrespondierenden `std::array<>`-Objekt sollte die Nummer des Zugs eingetragen werden. |
| `unsetKnightMoveAt` | `void unsetKnightMoveAt(const Coordinate& coord);`<br/>Macht einen Springerzug auf dem Schachbrett an der Position `coord` rückgängig. Im korrespondierenden `std::array<>`-Objekt sollte der Wert 0 eingetragen werden. |
| `inRange` | `bool inRange(const Coordinate& coord);`<br/>Liefert `true` oder `false` in Abhängigkeit davon zurück, ob die Werte des `Coordinate`-Objekts ein gültiges Feld auf dem Schachbrett spezifizieren oder nicht. |
| `canMoveTo` | `bool canMoveTo(const Coordinate& coord);`<br/>Liefert `true` zurück, wenn der Springer von der aktuellen Position auf das Feld mit der Position `coord` springen kann. Die Koordinaten müssen gültig sein und das Feld darf von dem Springer noch nicht durch einen vorangegangenen Zug betreten worden sein. |
| `nextKnightMoves` | `std::vector<Coordinate> nextKnightMoves(const Coordinate& coord);`<br/>Erstellt eine Liste mit allen möglichen Folgezügen, ausgehend von der Position `coord`. Ein Springer, der auf einem Schachbrett auf dem Feld mit den Koordinaten (x,y) steht, kann im nächsten Zug die Felder mit folgenden Koordinaten erreichen (siehe auch [Abbildung 3]):<br/>(*x*-1, *y*+2) und (*x*-1, *y*-2),<br/>(*x*-2 , *y*+1) und (*x*-2, *y*-1),<br/>(*x*+1, *y*-2) und (*x*+1, *y*+2),<br/>(*x*+2, *y*+1) und (*x*+2, *y*-1)<br/>Hierbei ist natürlich jeweils zu überprüfen, ob der Zielzug überhaupt auf dem Schachbrett liegt, siehe dazu die Methoden `inRange` bzw. `canMoveTo`. Folglich kann die Resultatliste bis zu acht `Coordinate`-Elemente enthalten. |
| `isSolution` | `bool isSolution();`<br/>Liefert `true` zurück, wenn aktuell auf dem Schachbrett eine Lösung des Springerproblems vorliegt, andernfalls `false`. |

*Tabelle* 5: Hilfsmethoden der Klasse `KnightProblemSolver`.

Wir sind so gut wie am Ziel angekommen. Die einzige noch fehlende Methode FindMoves ist gemäß [Tabelle 6] zu definieren:

###### {#tabelle_6_class_knightproblemsolver_findmoves}

| Methode | Beschreibung |
| :---- | :---- |
| `findMoves` | `int findMoves(const Coordinate& coord);`<br/>Bestimmt alle Lösungen des Springerproblems, falls vorhanden. Zum Beginn der Suche ist der Springer auf die Position `coord` gesetzt, typischerweise die linke untere Ecke des Schachbretts. Die Lösungen sind über die *getter*-Methode `getSolutions()` verfügbar. |

*Tabelle* 6: Methode `findMoves` der Klasse `KnightProblemSolver`.

****

<!-- Links Definitions -->

[Tabelle 1]:    #tabelle_1_class_coordinate
[Tabelle 2]:    #tabelle_2_class_knightproblemboard
[Tabelle 3]:    #tabelle_3_class_knightproblemsolver_getters
[Tabelle 4]:    #tabelle_4_class_knightproblemsolver_members
[Tabelle 5]:    #tabelle_5_class_knightproblemsolver_helpers
[Tabelle 6]:    #tabelle_6_class_knightproblemsolver_findmoves

[Abbildung 1]:  #abbildung_1_springer_problem_single_solution
[Abbildung 2]:  #abbildung_2_springer_problem_number_of_solutions
[Abbildung 3]:  #abbildung_3_springer_problem_possible_moves_of_knight

[Abbildung 4]:  #abbildung_4_springer_problem_knight_moves_start
[Abbildung 5]:  #abbildung_5_springer_problem_knight_moves_01
[Abbildung 6]:  #abbildung_6_springer_problem_knight_moves_02
[Abbildung 7]:  #abbildung_7_springer_problem_knight_moves_03
[Abbildung 8]:  #abbildung_8_springer_problem_knight_moves_04
[Abbildung 9]:  #abbildung_9_springer_problem_knight_moves_05
[Abbildung 10]: #abbildung_10_springer_problem_knight_moves_06
[Abbildung 11]: #abbildung_11_springer_problem_knight_moves_07

[Abbildung 12]: #abbildung_12_springer_problem_solution_tree
[Abbildung 13]: #abbildung_13_springer_problem_pseudo_code

[Abbildung 14]: #abbildung_14_springer_problem_example_board

<!-- End-of-File -->





