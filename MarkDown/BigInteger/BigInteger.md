<!-- BigInteger.md -->

Die ganzzahligen Standarddatentypen in C++ wie `short`, `int` usw. besitzen allesamt die Eigenschaft,
dass ihr Wertebereich limitiert ist. Für viele Anwendungen ist dies nicht nachteilig,
da sich speziell mit den Datentypen `int` und `long` oder auch `size_t` ziemlich große Zahlen darstellen lassen.
Für manche Anwendungen ist die Verarbeitung von ganzen Zahlen beliebiger Größe jedoch unabdingbar.
Wir stellen im Folgenden eine Klasse `BigInteger` vor,
die eine exakte Arithmetik vorzeichenbehafteter ganzer Zahlen beliebiger Größe zur Verfügung stellt.

Um potentiell beliebig viele Ziffern einer sehr großen Zahl in einem `BigInteger`-Objekt abzulegen,
gibt es mehrere Möglichkeiten wie etwa die Verwendung (generischer) Standardcontainer
aus der STL (C++ Standard Template Library) oder auch einfach nur die Ablage der Ziffern in einer Zeichenkette.
In der vorgestellten Lösung legen wir auf ein `std::vector<T>`-Objekt zugrunde.

<!--more-->

# Lernziele


  * Container `string_view` und `std::vector<T>`
  * `std::reverse_iterator`
  * Lambda-Funktionen (mit `mutable`)
  * Datentyp `uint8_t`
  * Verschiebesemantik mit `std::move`
  * Werfen von Ausnahmen mit `throw` und `std::invalid_argument`

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
| Konstruktor | `BigInteger();`<br/>Erzeugt ein `BigInteger`-Objekt zur Zahl 0. |
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
| *getter* `zero()` | `bool zero() const;`<br/>Liefert den Wert `true` zurück, wenn die Zahl 0 ist, andernfalls `false`. |
| *getter* `sign()` | `bool sign() const;`<br/>Liefert das Vorzeichen der Zahl zurück, `true` entspricht einer positiven Zahl, `false` einer negativen. |

*Tabelle* 2: *getter*-/*setter*-Methoden der Klasse `BigInteger`.

# Ausgabe

Zur Ausgabe eines `BigInteger`-Objekts auf der Konsole mit dem Standardobjekt `std::cout` ist
der `<<`-Operator geeignet zu überladen. Um die Lesbarkeit der Zeichenfolge zu steigern,
ist nach jeder dritten Stelle ein Punkt einzufügen, also zum Beispiel `"99.999"`.

# Arithmetische Operatoren der Klasse `BigInteger`

Wir geben nun einige Hinweise zu den Grundrechenarten, wie sie in der Schulmathematik gelehrt werden.
Bei der so genannten *schriftlichen Addition* werden die zu addierenden Zahlen rechtsbündig so angeordnet,
dass jeweils gleichwertige Ziffern untereinander stehen (Einer unter Einer, Zehner unter Zehner usw.).
Man addiert dann die jeweils untereinander stehenden Ziffern, beginnend mit den Einern.
Ergeben die addierten Ziffern eine Zahl größer oder gleich 10, berücksichtigt man den Übertrag
bei der Addition der nächsten zwei Ziffern, siehe [Abbildung 1]:

###### {#abbildung_1_schriftlichen_addition_01}

{{< figure src="/img/biginteger/Schulmathematik_Addition_01.png" width="30%" >}}

*Abbildung* 1: Schriftliche Addition der Schulmathematik.

Bei der Umsetzung der schriftlichen Addition in einem C++-Programm stellt sich die Frage,
in welcher Reihenfolge die einzelnen Ziffern im korrespondierenden `std::vector`-Objekt abgelegt werden.
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
dass wir in den einzelnen Zeilen keinen Überlauf berücksichtigen. Dies tun wir erst,
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
| Operator `+` | `friend BigInteger& operator+= (BigInteger& a, const BigInteger& b);`<br/>Addition von `a` und `b` mit Zuweisung an `a`. |
| Operator `-` | `friend BigInteger& operator-= (BigInteger& a, const BigInteger& b);`<br/>Subtraktion von `a` und `b` mit Zuweisung an `a`. |
| Operator `*` | `friend BigInteger& operator*= (BigInteger& a, const BigInteger& b);`<br/>Multiplikation von `a` und `b` mit Zuweisung an `a`. |
| Operator `/` | `friend BigInteger& operator/= (BigInteger& a, const BigInteger& b);`<br/>Division von `a` und `b` mit Zuweisung an `a`. |
| Operator `%` | `friend BigInteger& operator%= (BigInteger& a, const BigInteger& b);`<br/>Rest bei Division von `a` und `b` mit Zuweisung an `a`. |

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
| Operator `==` | `friend bool operator== (const BigInteger& a, const BigInteger& b);`<br/>Vergleicht den Wert zweier `BigInteger`-Objekte `a` und `b` auf Gleichheit. |
| Operator `!=` | `friend bool operator!= (const BigInteger& a, const BigInteger& b);`<br/>Vergleicht den Wert zweier `BigInteger`-Objekte `a` und `b` auf Ungleichheit. |
| Operator `<`  | `friend bool operator<  (const BigInteger& a, const BigInteger& b);`<br/>Umsetzung der mathematischen Relationen kleiner. |
| Operator `<=` | `friend bool operator<= (const BigInteger& a, const BigInteger& b);`<br/>Umsetzung der mathematischen Relationen kleiner-gleich. |
| Operator `>`  | `friend bool operator>  (const BigInteger& a, const BigInteger& b);`<br/>Umsetzung der mathematischen Relationen größer. |
| Operator `>=` | `friend bool operator>= (const BigInteger& a, const BigInteger& b);`<br/>Umsetzung der mathematischen Relationen größer-gleich. |

*Tabelle* 6: Vergleichsoperatoren der Klasse `BigInteger`.

# Hilfsmethoden der Klasse `BigInteger`

Möglicherweise benötigen Sie zur Implementierung der vorangestellten Abschnitte noch die eine oder andere Hilfsmethode.
Bei den arithmetischen Operationen können beispielsweise in manchen Situationen im internen `std::vector<T>`-Objekt
führende Nullen entstehen. Im Extremfall kann man dies bei der Subtraktion einer Zahl mit sich selbst beobachten, also etwa 100 - 100.
Das Ergebnis sollte dann nicht 000, sondern eben 0 lauten.
Zur Behebung dieser Unschönheit finden Sie in Tabelle 7 die Methode `removeLeadingZeros` nebst einigen weiteren Methoden vor:

###### {#tabelle_7_class_biginteger_helper_methods}  

| Element | Beschreibung |
| :---- | :---- |
| Methode `removeLeadingZeros` | `void removeLeadingZeros();`<br/>Entfernt führende Nullen im internen `std::vector<T>`-Objekt eines `BigInteger`-Objekts. |
| Methode `abs` | `BigInteger abs() const;`<br/>Liefert ein `BigInteger`-Objekt mit dem Absolutbetrag des aktuellen Objekts zurück. |
| Methode `pow` | `BigInteger pow(int n);`<br/>Liefert ein `BigInteger`-Objekt zurück, das die Basis (`*this`) potenziert mit dem Exponenten `n` repräsentiert &ndash; also `*this`<sup>n</sup>. |

*Tabelle* 7: Hilfsmethoden der Klasse `BigInteger`.

# Einige Beispiele

*Beispiel*:

```cpp
// testing c'tors
BigInteger n1{ "1234567" };
std::cout << n1 << std::endl;

BigInteger n2{ "-1234567" };
std::cout << n2 << std::endl;

BigInteger n3{ "123.456.789.012.345.678" };
std::cout << n3 << std::endl;
```

*Ausgabe*:

```
1.234.567
-1.234.567
123.456.789.012.345.678
```

*Beispiel*:

```cpp
// testing addition
BigInteger n1{ "11111111" };
BigInteger n2{ "22222222" };
std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

n1 = BigInteger{ "99999999999999" };
n2 = BigInteger{ "1" };
std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;
```

*Ausgabe*:

```
11.111.111 + 22.222.222 = 33.333.333
99.999.999.999.999 + 1 = 100.000.000.000.000
```

*Beispiel*:

```cpp
// testing subtraction
BigInteger n1{ "999" };
BigInteger n2{ "900" };
std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

n1 = BigInteger{ "999" };
n2 = BigInteger{ "998" };
std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

n1 = BigInteger{ "999" };
n2 = BigInteger{ "999" };
std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

n1 = BigInteger{ "11111" };
n2 = BigInteger{ "222" };
std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

n1 = BigInteger{ "1000000" };
n2 = BigInteger{ "1" };
std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
```

*Ausgabe*:

```
999 - 900 = 99
999 - 998 = 1
999 - 999 = 0
11.111 - 222 = 10.889
1.000.000 - 1 = 999.999
```

# Lösung

Die Realisierung der Klasse `BigInteger` ist nicht in allen Teilen trivial.
Wir gehen die einzelnen Abschnitte detailliert durch.
Die notwendigen Instanzvariablen der Klasse `BigInteger` wurden durch die Aufgabenstellung mehr oder minder nahe gelegt:

```cpp
std::vector<DigitType> m_digits;
bool m_sign;
```

Die einzelnen Ziffern der großen Zahl werden in einem Array des Typs `std::vector<DigitType>` abgelegt.
Hier hätte man vielleicht der Einfachheit halber einen Typ `std::vector<int>` erwartet. 
Da wir es möglicherweise mit vielen Ziffern zu tun haben, die im Speicher dicht gepackt und konsekutiv abgelegt werden sollten,
wollen wir hier platzsparend vorgehen. Mit einer Typdefinition

```cpp
using digit_t = uint8_t;  
```

können wir diese Anforderung erzielen und die Festlegung auch variabel (bzgl. der Übersetzungszeit) gestalten.
Für das Vorzeichen der Zahl benötigen wir eine zusätzliche Instanzvariable `m_sign`,
der Datentyp `bool` gestattet es, positive Zahlen mit dem Wert `true` und negative Zahlen mit `false` zu assoziieren. 

In [Listing 1] beginnen wir unseren Parcours durch den Lösungsteil mit der Schnittstelle der Klasse `BigInteger`:

###### {#listing_1_class_biginteger_decl}

```cpp
01: class BigInteger
02: {
03: private:
04:     std::vector<digit_t> m_digits;
05:     bool m_sign;
06: 
07: public:
08:     // c'tors / d'tor
09:     BigInteger();
10:     explicit BigInteger(std::string_view);
11: 
12:     // type conversion c'tors
13:     explicit BigInteger(int);
14:     explicit BigInteger(long);
15:     explicit BigInteger(long long);
16: 
17: public:
18:     // getter
19:     size_t size() const;
20:     bool zero() const;
21:     bool sign() const;
22: 
23:     // comparison operators
24:     friend bool operator== (const BigInteger&, const BigInteger&);
25:     friend bool operator!= (const BigInteger&, const BigInteger&);
26:     friend bool operator<  (const BigInteger&, const BigInteger&);
27:     friend bool operator<= (const BigInteger&, const BigInteger&);
28:     friend bool operator>  (const BigInteger&, const BigInteger&);
29:     friend bool operator>= (const BigInteger&, const BigInteger&);
30: 
31:     // unary arithmetic operators
32:     friend BigInteger operator+ (const BigInteger&);
33:     friend BigInteger operator- (const BigInteger&);
34: 
35:     // binary arithmetic operators
36:     friend BigInteger operator+ (const BigInteger&, const BigInteger&);
37:     friend BigInteger operator- (const BigInteger&, const BigInteger&);
38:     friend BigInteger operator* (const BigInteger&, const BigInteger&);
39:     friend BigInteger operator/ (const BigInteger&, const BigInteger&);
40:     friend BigInteger operator% (const BigInteger&, const BigInteger&);
41: 
42:     // arithmetic-assignment operators
43:     friend BigInteger& operator+= (BigInteger&, const BigInteger&);
44:     friend BigInteger& operator-= (BigInteger&, const BigInteger&);
45:     friend BigInteger& operator*= (BigInteger&, const BigInteger&);
46:     friend BigInteger& operator/= (BigInteger&, const BigInteger&);
47:     friend BigInteger& operator%= (BigInteger&, const BigInteger&);
48: 
49:     // increment/decrement operators (prefix/postfix version)
50:     friend BigInteger& operator++ (BigInteger&);       // prefix increment
51:     friend BigInteger  operator++ (BigInteger&, int);  // postfix increment
52:     friend BigInteger& operator-- (BigInteger&);       // prefix decrement
53:     friend BigInteger  operator-- (BigInteger&, int);  // postfix decrement
54: 
55:     // functor (supporting formatted output)
56:     std::string operator()(int);
57: 
58:     // public helper methods
59:     BigInteger abs() const;
60:     BigInteger pow(int);
61: 
62: private:
63:     // private helper operator
64:     digit_t& operator[] (size_t);  // subscript operator
65:     const digit_t& operator[] (size_t) const; // const subscript operator
66: 
67:     // private helper methods
68:     void removeLeadingZeros();
69:     int compareTo(const BigInteger&) const;
70:     void toBigInteger(long long);
71: 
72:     // output
73:     friend std::ostream& operator<< (std::ostream&, const BigInteger&);
74: };
```

*Listing* 1: Klasse `BigInteger`: Definition.

Der Standardkonstruktor soll die Zahl 0 repräsentieren, dazu benötigen wir immerhin ein Ziffernfeld der Länge 1:

```cpp
// default c'tor
BigInteger::BigInteger() : m_digits{ 1 }, m_sign{ true } {
    m_digits[0] = 0; 
} 
```

Der wichtigste Konstruktor der `BigInteger`-Klasse erwartet eine (beliebig lange) Zeichenkette und kopiert ihren Inhalt,
abgesehen von den Punkten `.` für die verbesserte Lesbarkeit der Eingabe, in das `m_digits`-Vektorobjekt um.
Da wir im Prinzip nur konstante Zeichenketten erwarten (oder unterstützen), ist der Parameter vom Typ `std::string_view`.
`std::string_view`-Objekte sind eine optimierte Version der Klasse `std::string`,
sie bestehen ausschließlich aus einem *raw*-Zeiger einer konstanten Zeichenkette und einer Längenangabe.
Prinzipiell wird von der Zeichenkette erwartet, dass diese korrekt aufgebaut ist.
Im Fehlerfall wird eine Ausnahme geworfen (siehe die Zeilen 10 und 23 von [Listing 2]):

###### {#listing_2_user_def_ctor}

```cpp
01: BigInteger::BigInteger(std::string_view sv) : m_sign{ true }
02: {
03:     std::reverse_iterator<std::string_view::iterator> r = sv.rbegin();
04: 
05:     std::for_each(std::rbegin(sv), std::prev(std::rend(sv)), [this](char ch) {
06:         if (ch == '.') {
07:             return;
08:         }
09:         else if (! std::isdigit(ch)) {
10:             throw std::invalid_argument("illegal digit in big number");
11:         }
12:         else {
13:             m_digits.push_back(ch - '0');
14:         }
15:     });
16: 
17:     char ch = *std::prev(std::rend(sv));
18:     if (ch == '+' or ch == '-') {
19:         m_sign = (ch == '-') ? false : true;
20:     }
21:     else {
22:         if (!std::isdigit(ch)) {
23:             throw std::invalid_argument("illegal digit in big number");
24:         }
25:         m_digits.push_back(ch - '0');
26:     }
27: 
28:     removeLeadingZeros();
29: }
```

*Listing* 2: Benutzerdefinierter Konstruktor der Klasse `BigInteger`.

Da wir die Ziffern eines `BigInteger`-Objekts intern in der umgekehrten Reihenfolge ablegen wollen,
kommt ein `std::reverse_iterator` zum Einsatz.

Nach der Erzeugung eines `BigInteger`-Objekts an Hand einer Zeichenkette kommen wir gleich auf die entgegengesetzte Operation zu sprechen:
Umwandlung eines BigInteger-Objekts in eine Zeichenkette. Diese Operationn haben wir im Funktor der Klasse untergebracht.
Dieser ist flexiblel in der Aufnahme von Parameterwerten.
Wir definieren ihn mit einem Parameter vom Typ `int`, um die Anzahl der Dreiziffernblöcke pro Zeile festzulegen.
Die Zeilen 10 bis 48 ([Listing 3]) widmen sich dem Umstand, mit wie vielen Leerzeichen der erste Dreiziffernblock aufzufüllen ist,
wenn die Anzahl der Ziffern kein Vielfaches von Drei ist. Da auch noch ein mögliches Vorzeichen zu berücksichtigen ist,
gewinnt der Sourcecode leider nicht gerade an Übersichtlichkeit.

###### {#listing_3_to_string_conversion}

```cpp
01: // functor (supporting formatted output)
02: std::string BigInteger::operator()(int n)
03: {
04:     std::string firstSuffix{};
05:     std::string subsequentSuffix{ std::string {" "} };
06: 
07:     std::string result{};
08:     int skippedDigits{};
09: 
10:     if (! m_sign) {
11:         firstSuffix = std::string{ "-" };
12:         subsequentSuffix = std::string{ "  " };
13:     }
14: 
15:     std::reverse_iterator<std::vector<digit_t>::iterator> rev_it = std::rbegin(m_digits);
16: 
17:     // calculate suffix of output
18:     if (size() % 3 == 0) {
19:         char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element
20:         char digit2 = m_digits.rbegin()[1] + '0'; // penultimate element
21:         char digit3 = m_digits.rbegin()[2] + '0'; // pen-penultimate element
22:         firstSuffix.push_back(digit1);
23:         firstSuffix.push_back(digit2);
24:         firstSuffix.push_back(digit3);
25:         subsequentSuffix.append("   ");
26:         rev_it += 3;
27:         skippedDigits = 3;
28:     }
29:     else if (size() % 3 == 1) {
30:         char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element
31: 
32:         firstSuffix.push_back(digit1);
33: 
34:         subsequentSuffix.append(" ");
35:         rev_it += 1;
36:         skippedDigits = 1;
37:     }
38:     else if (size() % 3 == 2) {
39:         char digit1 = m_digits.rbegin()[0] + '0'; // ultimate element
40:         char digit2 = m_digits.rbegin()[1] + '0'; // penultimate element
41: 
42:         firstSuffix.push_back(digit1);
43:         firstSuffix.push_back(digit2);
44: 
45:         subsequentSuffix.append("  ");
46:         rev_it += 2;
47:         skippedDigits = 2;
48:     }
49: 
50:     result = firstSuffix;
51:     result.push_back('.');
52: 
53:     int blocks{ 0 };
54: 
55:     std::for_each(
56:         rev_it,
57:         std::rend(m_digits),
58:         [&, i = m_digits.size() - skippedDigits - 1](int digit) mutable {
59:         result.push_back ((char)(digit + '0'));
60:         if (i > 0 && i % 3 == 0) {
61:             result.push_back('.');
62:             ++blocks;
63:         }
64:         --i;
65: 
66:         if (blocks == n) {
67:             result.push_back('\n');
68:             blocks = 0;
69:             result.append(subsequentSuffix);
70:         }
71:     });
72: 
73:     return result;
74: }
```

*Listing* 3: Wandlung Klasse `BigInteger` nach `std::string`.

Laut Spezifikation besitzt die `BigInteger`-Klasse drei *getter*-Methoden
`size`, `zero` und `sign`, mehr hierzu in [Listing 4]:


###### {#listing_4_getter}

```cpp
01: bool BigInteger::sign() const { return m_sign; }
02: size_t BigInteger::size() const { return m_digits.size(); }
03: bool BigInteger::zero() const { return m_digits.size() == 1 and m_digits[0] == 0; }
```

*Listing* 4: *getter*-Methoden `size`, `zero` und `sign` der Klasse `BigInteger`.

Die unären Operatoren `+` und `-`, also positives oder negatives Vorzeichen eines `BigInteger`-Objekts,
dürfen in einer korrekten Implementierung nicht fehlen ([Listing 5]):

###### {#listing_5_unary_operators}

```cpp
01: BigInteger operator+ (const BigInteger& a)
02: {
03:     return { a };
04: }
05: 
06: BigInteger operator- (const BigInteger& a)
07: {
08:     BigInteger tmp{ a };
09: 
10:     if (! a.zero()) {
11:         tmp.m_sign = !tmp.m_sign;
12:     }
13: 
14:     return tmp;
15: }
```

*Listing* 5: Unäre Operatoren `+` und `-` der Klasse `BigInteger`.

Beide Operatoren `+` und `-` delegieren ihre Arbeit im wesentlichen an den Kopier-Konstruktur der `BigInteger`-Klasse.
Dieser ist nicht explizit implementiert, da die `BigInteger`-Klasse entweder aus elementaren Instanzvariablen (hier genügt eine flache Kopie)
oder einem `std::vector<>`-Objekt besteht. Letzteres besitzt seinen eigenen Kopier-Konstruktur,
dieser wird beim Kopieren eines `BigInteger`-Objekts in Anspruch genommen.

Damit sind wir beim Kernstück der `BigInteger`-Klasse angekommen, ihren arithmetischen Operatoren.
Die Addition großer Zahlen entnehmen Sie bitte [Listing 6]:

###### {#listing_6_addition}

```cpp
WEITER WEITER ...
```




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

[Listing 1]: #listing_1_class_biginteger_decl
[Listing 2]: #listing_2_user_def_ctor
[Listing 3]: #listing_3_to_string_conversion
[Listing 4]: #listing_4_getter
[Listing 5]: #listing_5_unary_operators
[Listing 6]: #listing_6_addition
[Listing 7]: #listing_7_subtraction
[Listing 8]: #listing_8_multiplication
[Listing 9]: #listing_9_division



<!-- End-of-File -->


###### {#listing_2_user_def_ctor}

```cpp

```

*Listing* 2: Benutzerdefinierter Konstruktor der Klasse `BigInteger`.