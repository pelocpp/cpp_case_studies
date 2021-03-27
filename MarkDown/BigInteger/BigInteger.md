<!-- BigInteger.md -->

Die ganzzahligen Standarddatentypen in C++ wie `short`, `int` usw. besitzen allesamt die Eigenschaft,
dass ihr Wertebereich limitiert ist. Für viele Anwendungen ist dies nicht nachteilig,
da sich speziell mit den Datentypen `int` und `long` oder auch mit `size_t` ziemlich große Zahlen darstellen lassen.
Für manche Anwendungen ist die Verarbeitung von ganzen Zahlen beliebiger Größe jedoch unabdingbar.
Wir stellen im Folgenden eine Klasse `BigInteger` vor,
die eine exakte Arithmetik vorzeichenbehafteter ganzer Zahlen beliebiger Größe zur Verfügung stellt.

Um potentiell beliebig viele Ziffern einer sehr großen Zahl in einem `BigInteger`-Objekt abzulegen,
gibt es mehrere Möglichkeiten wie etwa die Verwendung (generischer) Standardcontainer
aus der STL (C++ Standard Template Library) oder auch einfach die Ablage der Ziffern in einer Zeichenkette.
In der vorgestellten Lösung zu dieser Aufgabe greifen wir auf ein `std::vector<XXX>`-Objekt zurück.

<!--more-->

# Lernziele


  * Container `string_view` und `std::vector<XXX>`
  * `std::reverse_iterator`
  * Lambda-Funktionen (mit `mutable`)

---

  * Default-Initialisierung für Member-Variablen
  * Delegation von Konstruktoren (nun auch in C++ enthalten)
  * Bereichs-basierte `for`-Wiederholungsschleife (Range-Based For Loop) *mit* Variablendeklaration
  * Container `std::forward_list<T>`
  * Neue Schlüsselwörter `override` und `final` ergänzend zu `virtual`
  * STL-Algorithmus `std::find_if`


# Grundgerüst der Klasse `BigInteger`

Unsere Kenntnisse aus der Schulmathematik zur schriftlichen Addition, Multiplikation usw. stellen
die Grundlage für die Implementierung der arithmetischen Operatoren in der `BigInteger`-Klasse dar.
Vermutlich sind Ihre Erinnerungen hierzu, wie meine auch, zwischenzeitlich recht verschwommen.
In den nachfolgenden Hinweisen finden Sie einen kurzen Auffrischungskurs dieser schulmathematischen Grundlagen vor.

Um etwaige Missverständnisse rechtzeitig auszuräumen: In der Implementierung Ihrer Klasse `BigInteger`
dürfen Sie zum Rechnen mit einzelnen Ziffern &ndash; aus denen die &ldquo;sehr großen Zahlen&rdquo; gebildet werden &ndash; selbstverständlich
die Standardoperatoren von C++ wie `+` oder `*` verwenden.
Ziel dieser Fallstudie ist es, einen Klassentyp zu entwickeln, der die Wertebereichslimitierungen
dieser elementaren ganzzahligen Datentypen überwindet.

Erste Hinweise zur `BigInteger`-Klasse finden Sie in [Tabelle 1] vor:


###### {#tabelle_1_class_biginteger_ctors}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `BigInteger() = default;`<br/>Erzeugt ein `BigInteger`-Objekt mit dem Wert Null. |
| Benutzerdefinierter Konstruktor | `explicit BigInteger(std::string_view);`<br/>Erzeugt ein `BigInteger`-Objekt mit Hilfe der Beschreibung einer Zahl in Form einer Zeichenkette. |
| Konvertierungs-Konstruktor | `explicit BigInteger(int);`<br/>Erzeugt ein `BigInteger`-Objekt anhand eines `int`-Werts. |
| Konvertierungs-Konstruktor | `explicit BigInteger(long);`<br/>Erzeugt ein `BigInteger`-Objekt anhand eines `long`-Werts. |
| Konvertierungs-Konstruktor | `explicit BigInteger(long long);`<br/>Erzeugt ein `BigInteger`-Objekt anhand eines `long long`-Werts. |

*Tabelle* 1: Konstruktoren der Klasse `BigInteger`.

Eine Zeichenkette zur Beschreibung eines `BigInteger`-Objekts darf optional mit einem Plus- oder Minuszeichen beginnen,
um das Vorzeichen der Zahl festzulegen. Danach folgen beliebig viele dezimale Ziffern:

```
BigInteger a { "+11111111111111111111111111111111111111" };
```

Mit Ausnahme von Punkten dürfen in der Zeichenkette keine anderen Zeichen enthalten sein. Punkte sind der besseren Lesbarkeit
halber in der Zeichenkette zulässig, wie etwa `"123.456.789"`.

Die *getter*- und *setter*-Methoden der Klasse `BigInteger` sind in [Tabelle 2] beschrieben:


###### {#tabelle_2_class_biginteger_getter_setter}

| Element | Beschreibung |
| :---- | :---- |
| *getter* `size()` | `size_t size() const;`<br/>Liefert die Anzahl der Ziffern der Zahl, auch *Stelligkeit* der ganzen Zahl genannt, zurück. |
| *getter* `zero()` | `bool zero() const;`<br/>Liefert den Wert `true` zurück, wenn das aktuelle Polynom das Null-Polynom ist, andernfalls `false`. |
| *getter* `sign()` | `bool sign() const;`<br/>Liefert das Vorzeichen der Zahl zurück, `true` entspricht einer positiven Zahl, `false` einer negativen. |

*Tabelle* 2: *getter*-/*setter*-Methoden der Klasse `BigInteger`.

# Ausgabe

Zur Ausgabe eines `BigInteger`-Objekts auf der Konsole mit dem Standardobjekt `std::cout` ist
der `<<`-Operator geeignet zu überladen. Um die Lesbarkeit der Zeichenfolge zu steigern,
ist nach jeder dritten Stelle ein Punkt einzufügen, also zum Beispiel `"99.999"`.

# Arithmetische Operatoren der Klasse `BigInteger`

Wir geben nun einige Hinweise zu den Grundrechenarten, wie sie in der Schulmathematik gelehrt werden.
Bei der so genannten *schriftlichen Addition* werden die zu addierenden Zahlen rechtsbündig so angeordnet,
dass jeweils gleichwertige Ziffern (Einer unter Einer, Zehner unter Zehner usw.) untereinander stehen.
Man addiert dann die jeweils untereinander stehenden Ziffern, beginnend mit den Einern.
Ergeben die addierten Ziffern eine Zahl größer oder gleich 10, berücksichtigt man den Übertrag
bei der Addition der nächsten zwei Ziffern, siehe [Abbildung 1]:

###### {#abbildung_1_schriftlichen_addition_01}

{{< figure src="/img/biginteger/Schulmathematik_Addition_01.png" width="30%" >}}

*Abbildung* 1: Schriftliche Addition der Schulmathematik.

Bei der Umsetzung der schriftlichen Addition in einem C++-Programm stellt sich die Frage,
in welcher Reihenfolge die einzelnen Ziffern im korrespondierenden `std::vector<XXX>` des `BigInteger`-Objekts abgelegt werden.
Da die einzelnen Ziffern stellenweise, beginnend mit der niedrigstwertigen Stelle, zu addieren sind, bietet es sich an,
die einzelnen Ziffern in umgekehrter Reihenfolge im Container abzuspeichern.
Wenn wir das Beispiel aus [Abbildung 1] noch einmal betrachten,
so würde die Ablage und Verarbeitung der beiden Zahlen 28345 und 7567 in einem `BigInteger`-Objekt
wie in [Abbildung 2] aussehen:

###### {#abbildung_2_schriftlichen_addition_02}

{{< figure src="/img/biginteger/Schulmathematik_Addition_02.png" width="30%" >}}

*Abbildung* 2: Ablage der Ziffern in umgekehrter Reihenfolge.

Die schriftliche Subtraktion funktioniert prinzipiell zunächst einmal so wie die schriftliche Addition.
Beginnend mit der niedrigstwertigen Stelle wird Stelle für Stelle die Ziffer des Subtrahenden (untere Ziffer)
von der Ziffer des Minuenden (obere Ziffer) abgezogen. Ein Problem entsteht,
wenn die obere Ziffer kleiner ist als die dazugehörige untere des Subtrahenden,
so dass die Subtraktion der zwei Ziffern nicht durchgeführt werden kann.
Hier gibt es mehrere Verfahren zur Lösung des Problems.
Wir skizzieren im Folgenden das so genannte *Entbündelungsverfahren*. Subtrahieren mit *Entbündeln* bedeutet,
dass der zu kleine Minuend bei seinem linken Nachbarn eine &ldquo;Anleihe&rdquo; macht.
Durch Borgen von der nächsthöheren Stelle wird die Ziffer des Minuenden um 10 erhöht,
und zum Zwecke des Ausgleichs die nächsthöherwertige Ziffer des Minuenden um 1 erniedrigt.
Auf diese Weise kann man stets erreichen, dass die untenliegende Ziffer von der obenliegenden abgezogen werden kann,
wie wir im Beispiel aus [Abbildung 3] vorführen:

###### {#abbildung_3_schulmathematik_subtraktion_01}

{{< figure src="/img/biginteger/Schulmathematik_Subtraktion_01.png" width="30%" >}}

*Abbildung* 3: Entbündelungsverfahren für Subtraktion.

Die Subtraktion der Einerstelle in [Abbildung 3] bereitet keine Probleme, 4 minus 2 ist gleich 2.
Die Zehnerstellen lassen sich zunächst nicht abziehen, der Minuend (6) ist zu klein.
Er wird darum um 10 erhöht, also gleich 16 gesetzt.
Diese 10 wird von der links daneben stehenden Ziffer (8) geliehen und deshalb wird diese
um 1 erniedrigt (neuer Wert 7). Nun können die nächsten zwei Subtraktionen (16 minus 9 und 7 minus 5)
problemlos durchgeführt werden und man erhält 272 als korrektes Gesamtergebnis der Subtraktion.

*Hinweis*: Einen Sonderfall müssen Sie in Ihrer Implementierung noch beachten,
nämlich wenn beim Leihen die korrespondierende Ziffer des Minuenden gleich 0 ist.
Von 0 lässt sich bekanntermaßen nichts borgen (ein Wert -1 stellt hier keine Lösung des Problems dar),
es muss folglich Stelle für Stelle in Richtung der höherwertigen Stellen solange weitergesucht werden,
bis eine erste Ziffer ungleich 0 vorliegt. Nun kann hier der Leihvorgang stattfinden
und der geliehene Wert über alle Zwischenstellen nach unten durchgereicht werden.
In [Abbildung 4] finden Sie ein Beispiel für diese Situation vor. Um 1 von 1000 abziehen zu können,
muss zum Leihen drei Stellen nach links gegangen werden:

###### {#abbildung_4_schulmathematik_subtraktion_02}

{{< figure src="/img/biginteger/Schulmathematik_Subtraktion_02.png" width="30%" >}}

*Abbildung* 4: Entbündelungsverfahren mit Null als linkem Nachbarn.

Damit sind wir bei der Multiplikation angekommen. Das Standardverfahren beruht darin,
die erste Zahl mit den einzelnen Ziffern der zweiten Zahl nacheinander,
beginnend bei der letzten Stelle, zu multiplizieren. Für jede neue Ziffer wird eine neue Zeile benötigt.
Man schreibt jede Multiplikation untereinander und addiert die einzelnen Werte.
Wie bei der Addition ist auch bei der Multiplikation ein Überlauf auf die jeweils nächsthöhere Stelle zu übertragen.

Im Gegensatz zum Standardverfahren der Schulmathematik vereinfachen wir das Verfahren dahingehend,
dass wir in den einzelnen Zeilen keinerlei Überlauf berücksichtigen. Dies tun wir erst,
wenn wir die Zwischenresultate der einzelnen Zeilen Spalte für Spalte, von rechts beginnend, zusammenzählen.
Am Beispiel von 98 * 12345 können Sie den Algorithmus in [Abbildung 5] nachverfolgen:

###### {#abbildung_5_schulmathematik_multiplikation}

{{< figure src="/img/biginteger/Schulmathematik_Multiplikation.png" width="30%" >}}

*Abbildung* 5: Standardverfahren für schriftliche Multiplikation.


Wir schließen diese Betrachtungen mit der schriftlichen Division ab. Bezüglich der Namensgebung
rekapitulieren wir zunächst einmal, dass ein *Dividend* durch einen *Divisor* geteilt wird,
das Ergebnis heißt *Quotient*, der in unserem Fall stets ganzzahlig ist und aus diesem Grund
in den meisten Fällen noch um einen *Rest* zu ergänzen ist. Wir beginnen mit der ersten (führenden) Zahl des Dividenden.
Ist diese Zahl nicht größer als der Divisor, nehmen wir die nächste Zahl des Dividenden mit hinzu
und wiederholen diesen Vorgang solange, bis die auf diese Weise gebildete Zahl größer ist als der Dividend.
Nun teilen wir diese Zahl durch den Divisor, das Ergebnis bildet die erste Ziffer des gesuchten Quotienten.
Um die Division fortsetzen zu können, multiplizieren wir das Ergebnis mit dem Divisor,
und subtrahieren das Produkt von der alten Zahl. Das so erhaltene Ergebnis wird durch &ldquo;Herunterziehen&rdquo;
der nächsten Ziffer von oben ergänzt. Dieses Procedere beginnen wir nun wieder von vorne.
Der neue Dividend ist das Ergebnis der letzten Subtraktion, ergänzt um die heruntergezogene Ziffer usw.

Das ganze Verfahren wird solange wiederholt, bis alle Stellen des Dividenden nach unten gezogen wurden.
Die unterste Zahl stellt den Rest der Division dar, der gesuchte Quotient wurde Ziffer für Ziffer zusammengesetzt.
Möglicherweise ist diese textuelle Beschreibung des Divisionsalgorithmus etwas schwer verdaulich,
zur Illustration betrachten wir in [Abbildung 6] das folgende Beispiel:

###### {#abbildung_6_schulmathematik_division}

{{< figure src="/img/biginteger/Schulmathematik_Division.png" width="30%" >}}

*Abbildung* 5: Standardverfahren der schriftlichen Division.

Nach diesen Hilfestellungen fassen wir die soeben besprochenen arithmetischen Operatoren
für eine Ergänzung der `BigInteger`-Klasse in [Tabelle 3] zusammen:

###### {#tabelle_3_class_biginteger_arithmetic_operators}

| Element | Beschreibung |
| :---- | :---- |
| Operator `+` | `friend BigInteger operator+ (const BigInteger& a, const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert sich aus der Addition von `a` und `b` ergibt. |
| Operator `-` | `friend BigInteger operator- (const BigInteger& a, const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert sich aus der Subtraktion von `a` und `b` ergibt. |
| Operator `*` | `friend BigInteger operator* (const BigInteger& a, const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert sich aus der Multiplikation von `a` und `b` ergibt. |
| Operator `/` | `friend BigInteger operator/ (const BigInteger& a, const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert sich aus der Division von `a` und `b` ergibt. |
| Operator `%` | `friend BigInteger operator% (const BigInteger& a, const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert sich aus dem Rest bei Division von `a` und `b` ergibt. |

*Tabelle* 3: Arithmetische Operatoren der Klasse `BigInteger`.

Neben den arithmetischen Operatoren der Klasse `BigInteger` gibt es natürlich auch noch die entsprechenden
arithmetischen Wertzuweisungsoperatoren wie zum Beispiel `+=`, siehe hierzu [Tabelle 4]:

###### {#tabelle_4_class_biginteger_arithmetic_assignment_operators}  

| Element | Beschreibung |
| :---- | :---- |
| Operator `+` | `friend BigInteger& operator+= (BigInteger&, const BigInteger&);`<br/>Addition von `a` und `b` mit Zuweisung an `a`. |
| Operator `-` | `friend BigInteger& operator-= (BigInteger&, const BigInteger&);`<br/>Subtraktion von `a` und `b` mit Zuweisung an `a`. |
| Operator `*` | `friend BigInteger& operator*= (BigInteger&, const BigInteger&);`<br/>Multiplikation von `a` und `b` mit Zuweisung an `a`. |
| Operator `/` | `friend BigInteger& operator/= (BigInteger&, const BigInteger&);`<br/>Division von `a` und `b` mit Zuweisung an `a`. |
| Operator `%` | `friend BigInteger& operator%= (BigInteger&, const BigInteger&);`<br/>Rest bei Division von `a` und `b` mit Zuweisung an `a`. |

*Tabelle* 4: Arithmetische Wertzuweisungsoperatoren der Klasse `BigInteger`.

In den meisten Situationen denken wir bei arithmetische Operatoren an ihre binäre Variante.
Ganze &ndash; und damit auch sehr große ganze &ndash; Zahlen können auch ein Vorzeichen haben: `+` oder `-`.
Für diese beiden Fälle benötigen wir jeweils den `+`&ndash; oder `-`&ndash;Operator in seiner unären Ausprägung ([Tabelle 5]):

###### {#tabelle_5_class_biginteger_unary_arithmetic_operators}

| Element | Beschreibung |
| :---- | :---- |
| Operator `+` | `friend BigInteger operator+ (const BigInteger& a);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert eine Kopie von `a` ist. |
| Operator `-` | `friend BigInteger operator- (const BigInteger& b);`<br/>Liefert ein neues `BigInteger`-Objekt zurück, dessen Wert eine negative Kopie von `a` ist. |

*Tabelle* 5: Unäre arithmetische Operatoren der Klasse `BigInteger`.

*Bemerkung*: Der unäre `+`-Operator ist eigentlich unnötig; ich habe ihn jedoch aus Symmetriegründen in der Klasse `BigInteger` mit eingeführt.
Auch ließe sich darüber diskutieren, ob das unäre Plus eine Referenz des aktuellen Objekts oder eine Kopie dessen zurückliefert.
Wiederum aus Symmetriegründen zum  `-`-Operator wollte ich beide Realisierungen identisch halten.

# Vergleichsoperatoren der Klasse `BigInteger`

Große Zahlen kann man vergleichen, etwa auf Gleichheit oder auf kleiner(-gleich) und größer(-gleich).
Entsprechende Operatoren hierzu sind in [Tabelle 6] festgelegt:

###### {#tabelle_6_class_biginteger_comparison_operators}  

| Element | Beschreibung |
| :---- | :---- |
| Operator `==` | `friend bool operator== (const BigInteger&, const BigInteger&);`<br/>Vergleicht den Wert zweier `BigInteger`-Objekte auf Gleichheit. |
| Operator `!=` | `friend bool operator!= (const BigInteger&, const BigInteger&);`<br/>Vergleicht den Wert zweier `BigInteger`-Objekte auf Ungleichheit. |
| Operator `<`  | `friend bool operator<  (const BigInteger&, const BigInteger&);`<br/>Umsetzung der mathematischen Relationen kleiner. |
| Operator `<=` | `friend bool operator<= (const BigInteger&, const BigInteger&);`<br/>Umsetzung der mathematischen Relationen kleiner-gleich. |
| Operator `>`  | `friend bool operator>  (const BigInteger&, const BigInteger&);`<br/>Umsetzung der mathematischen Relationen größer. |
| Operator `>=` | `friend bool operator>= (const BigInteger&, const BigInteger&);`<br/>Umsetzung der mathematischen Relationen größer-gleich. |

*Tabelle* 6: Vergleichsoperatoren der Klasse `BigInteger`.

# Hilfsmethoden der Klasse `BigInteger`

Möglicherweise benötigen Sie zur Implementierung der vorangestellten Abschnitte noch die eine oder andere Hilfsmethode.
Bei den arithmetischen Operationen können beispielsweise in manchen Situationen im internen `std::vector<XXX>`_Objekt
führende Nullen entstehen. Im Extremfall kann man dies bei der Subtraktion einer Zahl mit sich selbst beobachten, also etwa 100 - 100.
Das Ergebnis sollte dann nicht 000, sondern 0 lauten.
Zur Behebung dieser Unschönheit finden Sie in Tabelle 7 die Methode RemoveLeadingZeros nebst einigen weiteren Methoden vor:


WEITER: Hilfsmethoden ...................

###### {#tabelle_7_class_biginteger_helper_methods}  

| Element | Beschreibung |
| :---- | :---- |
| Operator `==` | `friend bool operator== (const BigInteger&, const BigInteger&);`<br/>Vergleicht den Wert zweier `BigInteger`-Objekte auf Gleichheit. |

*Tabelle* 7: Hilfsmethoden der Klasse `BigInteger`.


<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_biginteger_ctors
[Tabelle 2]: #tabelle_2_class_biginteger_getter_setter
[Tabelle 3]: #tabelle_3_class_biginteger_arithmetic_operators
[Tabelle 4]: #tabelle_4_class_biginteger_arithmetic_assignment_operators
[Tabelle 5]: #tabelle_5_class_biginteger_unary_arithmetic_operators
[Tabelle 6]: #tabelle_6_class_biginteger_comparison_operators
[Tabelle 7]: #tabelle_7_class_biginteger_helper_methods






[Abbildung 1]:  #abbildung_1_schriftlichen_addition_01
[Abbildung 2]:  #abbildung_2_schriftlichen_addition_02
[Abbildung 3]:  #abbildung_3_schulmathematik_subtraktion_01
[Abbildung 4]:  #abbildung_4_schulmathematik_subtraktion_02
[Abbildung 5]:  #abbildung_5_schulmathematik_multiplikation
[Abbildung 6]:  #abbildung_5_schulmathematik_division




[Listing 1]: #listing_01_ijosephus_interface
[Listing 2]: #listing_02_josephus_interface
[Listing 3]: #listing_03_josephus_implementation
[Listing 4]: #listing_04_josephusarrayimpl_interface
[Listing 5]: #listing_05_josephusarrayimpl_implementation
[Listing 6]: #listing_06_class_soldier
[Listing 7]: #listing_07_josephusforwardlistimpl_interface
[Listing 8]: #listing_08_josephusforwardlistimpl_implementation


<!-- End-of-File -->
