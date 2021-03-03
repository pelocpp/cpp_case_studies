<!-- Polynoms.md -->

# Einführung

Gegenstand dieser Aufgabe sind Polynomfunktionen, kurz auch Polynome genannt.
Formal ist ein Polynom als Summe von Vielfachen von Potenzen einer Variablen *x* definiert:

P<sub>n</sub>(*x*) = a<sub>n</sub>*x*<sup>n</sup> + a<sub>n-1</sub>*x*<sup>n-1</sup> + ... + a<sub>2</sub>*x*<sup>2</sup> + a<sub>1</sub>*x* + a<sub>0</sub>.

Die Variable *x* wie auch die Koeffizienten a<sub>i</sub> können beliebige reelle Werte annehmen,
wir sprechen von einem reellen Polynom. Als *Grad* des Polynoms wird der höchste Exponent *n* bezeichnet,
für den der Koeffizient an des Ausdrucks a<sub>n</sub>*x*<sup>n</sup> nicht null ist.
Dieser Koeffizient wird auch *Leitkoeffizient* genannt.

Entwickeln Sie eine Klasse `Polynom`, die &ndash; möglichst einfallsreich &ndash; die unterschiedlichen Konstrukte
(Instanzvariablen, Konstruktoren, Methoden, inklusive *getter*- und *setter*-Methoden, Operatoren usw.)
zur Definition einer Klasse in Modern C++ in Anspruch nimmt.

<!--more--> 

# Lernziele

  * Einheitliche Initialisierung
  * Initialisierungsliste (`std::initializer_list<T>`)
  * STL-Klasse `std::vector<T>`
  * C++ Iteratorenkonzept

# Konstruktoren und *getter*-/*setter*-Methoden

Die Konstruktoren und *getter*-/*setter*-Methoden der Klasse `Polynom` finden Sie in [Tabelle 1] genauer spezifiziert vor

###### {#tabelle_1_class_polynom_ctors}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `Polynom() = default;`<br/>Der Standardkonstruktor erzeugt ein Null-Polynom. Dieses besitzt den Rang 0, der Leitkoeffizient hat ebenfalls den Wert 0: P<sub>0</sub>(*x*) = 0. |
| Benutzerdefinierter Konstruktor | `Polynom(const std::initializer_list<double>&);`<br/>Der benutzerdefinierte Konstruktor legt ein Polynom mit den Koeffizienten einer variabel lange Liste von Koeffizienten an. Das erste Element des Arrays ist dem niederwertigsten Koeffizienten zuzuordnen, das letzte dem höchstwertigen. |
| *getter* `rank()` | `size_t rank() const;`<br/>Liefert den Grad des Polynoms zurück. |
| *getter* `zero()` | `bool zero() const;`<br/>Liefert den Wert `true` zurück, wenn das aktuelle Polynom das Null-Polynom ist, andernfalls `false`. |

*Tabelle* 1: Konstruktoren und *getter*-/*setter*-Methoden der Klasse `Polynom`.

Es folgen einige Beispiele:

```cpp
Polynom p1{ };
Polynom p2{ -5.0, +6.0, -7.0 };

std::cout << p1 << std::endl;
std::cout << p1.rank() << std::endl;
std::cout << std::boolalpha << p1.zero() << std::endl;

std::cout << p2 << std::endl;
std::cout << p2.rank() << std::endl;
std::cout << std::boolalpha << p2.zero() << std::endl;
```

*Ausgabe*:

```
0
0
true
-7x^2+6x^1-5
2
false
```

Für die Ausgabe eines Polynoms auf der Konsole implementieren Sie den Ausgabeoperator `<<` geeignet ([Tabelle 2]):

###### {#tabelle_2_class_polynom_output}

| Element | Beschreibung |
| :---- | :---- |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const Polynom&);`<br/>Gibt das Polynom p auf der Konsole aus. |

*Tabelle* 2: Ausgabeoperator `<<` der Klasse `Polynom`.

*Beispiel*:

```cpp
Polynom p{ 2.0, -4.0, 0.0, 3.0 };
std::cout << p << std::endl;
```

*Ausgabe*:

```
3x^3+0x^2-4x^1+2x^0
```

oder etwas eleganter

```
3x^3-4x^1+2
```

# Operatoren

Polynome besitzen eine Reihe zentraler Operatoren und Methoden, um sie beispielsweise zu addieren oder zu multiplizieren
oder aber um ihren Wert für ein bestimmtes Argument zu berechnen.
Im Folgenden finden Sie einige Wiederholungen der Grundlagen von Polynomen vor.

Die Addition eines Polynoms des Grades *n* mit einem Polynom des Grades kleiner-gleich *m* ergibt ein Polynom des Grades *max*(*n*, *m*).
Die Koeffizienten des Ergebnispolynoms werden jeweils durch Addition des Koeffizienten *a*<sub>i</sub> des einen Polynoms
mit dem passenden Koeffizienten *b*<sub>i</sub> des anderen Polynoms gebildet. Für die beiden Polynome

P(*x*) = 3*x*<sup>3</sup> - 4*x* + 2

und

Q(*x*) = 5*x*<sup>2</sup> + 3*x* + 3

lautet die Summe

P(*x*) + Q(*x*) = 3*x*<sup>3</sup> + 5*x*<sup>2</sup> - *x* + 5.

Analog zur Addition von Polynomen ist ihre Subtraktion definiert,
es werden einfach nur die entsprechenden Koeffizienten voneinander subtrahiert.

Die Polynommultiplikation eines Polynoms des Grades *n* mit einem Polynom des Grades *m* ergibt ein Polynom
des Grades *n*+*m*. Bei der Polynommultiplikation multiplizieren Sie jedes a<sub>i</sub>x<sup>i</sup> des einen Polynoms
mit allen b<sub>j</sub>x<sup>j</sup> des anderen Polynoms und summieren die Koeffizienten der jeweilig passenden Grade.
Das Produkt der Polynome des letzten Beispiels lautet:

P(*x*) * Q(*x*) = 15*x*<sup>5</sup> + 9*x*<sup>4</sup> - 11*x*<sup>3</sup> - 2*x*<sup>2</sup> - 6*x* + 6.

Im Prinzip können Sie das Multiplizieren zweier Polynome auch als Ausmultiplizieren von Klammern ansehen:

(3*x*<sup>3</sup> - 4*x* + 2) * (5*x*<sup>2</sup> + 3*x* + 3)

= 15*x*<sup>5</sup> + 9*x*<sup>4</sup> + 9*x*<sup>3</sup> - 20*x*<sup>3</sup> - 12*x*<sup>2</sup> - 12*x* + 10*x*<sup>2</sup> + 6*x* + 6

= 15*x*<sup>5</sup> + 9*x*<sup>4</sup> - 11*x*<sup>3</sup> - 2*x*<sup>2</sup> - 6*x* + 6.

Auf die Division gehen wir etwas ausführlicher ein.
Wir teilen das Polynom *x*<sup>3</sup> + 6*x*<sup>2</sup> + 3*x* - 10 durch das Polynom *x* + 5. Zuerst müssen wir bestimmen,
wie oft *x* + 5 in das erste Polynom hineinpasst.
Man betrachtet dabei stets die höchste Potenz aus beiden Polynomen (also *x*<sup>3</sup> aus dem ersten und *x* aus dem zweiten Polynom) und berechnet,
wie oft *x* in *x*<sup>3</sup> hineinpasst. Anders herum formuliert: Mit was muss man *x* malnehmen, so dass *x*<sup>3</sup> herauskommt?
Natürlich mit *x*<sup>2</sup>, das erste Teilresultat der Division ergibt sich nun zu

(*x*<sup>3</sup> + 6*x*<sup>2</sup> + 3*x* - 10) : (*x* + 5) = *x*<sup>2</sup>

Wie bei der Division von ganzen Zahlen multipliziert man jetzt den neuen Bestandteil des Ergebnisses mit dem Divisor
und schreibt ihn &ldquo;passend&rdquo; unter den Dividenden,
also gleiche Potenzen von *x* sind jeweils untereinander zu schreiben:

(*x*<sup>3</sup> + 6*x*<sup>2</sup> + 3*x* - 10) : (*x* + 5) = *x*<sup>2</sup>

 *x*<sup>3</sup> + 5*x*<sup>2</sup>

Nun wird die Subtraktion durchgeführt und werden anschließend alle restlichen Glieder des Polynoms &ldquo;heruntergeholt&rdquo;:

{{< figure src="/img/Polynoms/PolynomDivision01.png" width="25%" >}}

Der Rest hat nur noch den Polynomgrad 2, wir haben also das Problem schon um einen Grad verringert.
Nun stehen wir wieder vor der Ausgangsfrage: Wie oft passt das *x* aus dem Divisor in das *x*2,
die höchste Potenz des Restes. Offensichtlich *x*-Mal, damit ist der nächste Summand
des Quotienten (des Ergebnisses) +*x*:

{{< figure src="/img/Polynoms/PolynomDivision02.png" width="25%" >}}

Die jetzt noch zu beantwortende Frage lautet &ldquo;Wie oft passt x in -2x?&rdquo;.
Offensichtlich -2-Mal, und die (letzte) Subtraktion sieht nun so aus:

{{< figure src="/img/Polynoms/PolynomDivision03.png" width="25%" >}}

Dass diese Polynomdivision keinen Rest besitzt, ist in der Tat Zufall – oder um es doch ehrlich zu sagen:
Ich habe es mit Absicht so hingedeichselt :-). Es kann allerdings auch der Fall vorliegen, dass das Restpolynom
nicht mehr durch das Divisorpolynom teilbar ist. In diesem Fall weist die Polynomdivision einen &ldquo;Rest&rdquo; auf.
Neben der Division gibt es daher auch die Modulo-Operation für Polynome,
also die Bestimmung des Restpolynoms bei Polynomdivision, siehe dazu folgendes Beispiel:

{{< figure src="/img/Polynoms/PolynomDivision04.png" width="25%" >}}

Damit kommen wir zur Auswertung des Polynoms an einer bestimmten Stelle *x*.
Um uns unnötige Berechnungen von Potenzen zu ersparen, berechnen wir den Wert mit dem sogenannten *Horner*-Schema.
Die Arbeitsweise des Horner-Schemas kann man leicht erkennen, wenn wir es konkret für Polynome bis zum dritten Grad einmal exemplarisch betrachten:

P<sub>0</sub>(x) = a<sub>0</sub>,

P<sub>1</sub>(x) = a<sub>1</sub>x + a<sub>0</sub>,

P<sub>2</sub>(x) = a<sub>2</sub>x<sup>2</sup> + a<sub>1</sub>x + a<sub>0</sub> = (a<sub>2</sub>x + a<sub>1</sub>)x + a<sub>0</sub>,

P<sub>3</sub>(x) = a<sub>3</sub>x<sup>3</sup> + a<sub>2</sub>x<sup>2</sup> + a<sub>1</sub>x + a<sub>0</sub> = ((a<sub>3</sub>x + a<sub>2</sub>)x + a<sub>1</sub>)x + a<sub>0</sub>.

Jetzt wird die Wiederholstruktur des *Horner*-Schemas deutlich erkennbar:

*y*<sub>3</sub> = a<sub>3</sub>.

*y*<sub>2</sub> = a<sub>2</sub> + *x* * *y*<sub>3</sub>.

*y*<sub>1</sub> = a<sub>1</sub> + *x* * *y*<sub>2</sub>.

*y*<sub>0</sub> = a<sub>0</sub> + *x* * *y*<sub>1</sub>.

Der gesuchte Polynomwert entspricht nun dem Wert *y*<sub>0</sub>. An Hand dieses recht einfachen Beispiels sollte die Arbeitsweise
des *Horner*-Schemas erkennbar geworden sein, weitere Erläuterungen finden Sie in der einschlägigen Literatur vor.

Abschließend treffen wir eine Aussage zum Vergleich zweier Polynome: Ein Polynom ist größer als ein anderes, wenn sein Grad größer ist.
Ist der Grad gleich, sind der Reihe nach alle Koeffizienten, beginnend bei a<sub>n</sub>, zu vergleichen.
Sind alle Koeffizienten gleich, sind die Polynome gleich.

Informationen bezüglich der einzelnen C++-Operatorensignaturen der soeben betrachteten Polynomfunktionen finden Sie nun in [Tabelle 3] vor:

###### {#tabelle_3_class_polynom_arithmetic_operators}

| Element | Beschreibung |
| :---- | :---- |
| Operator `+` | `friend Polynom operator+ (const Polynom&, const Polynom&);`<br/>Addition zweier Polynome. |
| Operator `-` | `friend Polynom operator+ (const Polynom&, const Polynom&);`<br/>Subtraktion zweier Polynome. |
| Operator `*` | `friend Polynom operator+ (const Polynom&, const Polynom&);`<br/>Multiplikation zweier Polynome. |
| Operator `/` | `friend Polynom operator+ (const Polynom&, const Polynom&);`<br/>Division zweier Polynome. |
| Operator `%` | `friend Polynom operator+ (const Polynom&, const Polynom&);`<br/>Rest bei Division zweier Polynome. |

*Tabelle* 3: Arithmetische Operatoren der Klasse `Polynom`.

Zum Testen Ihrer Realisierung fügen wir einige Testbeispiele auf:

*Beispiel*:

```cpp
Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
Polynom p2{ 3.0, 3.0, 5.0 };
Polynom p3 = p1 + p2;
std::cout << p1 << std::endl;
std::cout << p2 << std::endl;
std::cout << p3 << std::endl;
```

*Ausgabe*:

```
3x^3-4x^1+2
5x^2+3x^1+3
3x^3+5x^2-x^1+5
```

*Beispiel*:

```cpp
Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
Polynom p2{ 3.0, 3.0, 5.0 };
Polynom p3 = p1 - p2;
std::cout << p3 << std::endl;
```

*Ausgabe*:

```
3x^3-5x^2-7x^1-1
```

*Beispiel*:

```cpp
Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
Polynom p2{ 3.0, 3.0, 5.0 };
std::cout << "p1*p2: " << p1*p2 << std::endl;
```

*Ausgabe*:

```
p1*p2: 15x^5+9x^4-11x^3-2x^2-6x^1+6
```

*Beispiel*:

```cpp
Polynom p1{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
Polynom p2{ 4.0, 2.0, 0.0, 1.0 };
std::cout << p1 << std::endl;
std::cout << p2 << std::endl;
std::cout << "p1/p2: " << p1/p2 << std::endl;
```

*Ausgabe*:

```
2x^5-x^4+5x^3+6x^2-2x^1+4
x^3+2x^1+4
p1/p2: 2x^2-x^1+1
```

*Beispiel*:

```cpp
Polynom p1{ 0, -4, 8, 10, 3 };
Polynom p2{ 0, 4, 3 };
std::cout << "p1%p2: " << p1 % p2 << std::endl;
```

*Ausgabe*:

```
p1%p2: -4x^1
```

*Hinweis*: Die Division zweier Polynome kann in der Realisierung dadurch vereinfacht werden,
wenn Sie die Klasse `Polynom` um zwei Hilfsmethoden sowie zwei Hilfsoperatoren ergänzen ([Tabelle 4]):

###### {#tabelle_4_class_polynom_helper_methods}

| Element | Beschreibung |
| :---- | :---- |
| Operator `*` | `friend Polynom operator* (const Polynom& p, double scalar);`<br/>`friend Polynom operator* (double scalar, const Polynom& p);`<br/>Multiplikation eines Polynoms `p` mit der Konstanten `scalar`. |
| Methode `multiplyX` | `void multiplyX(size_t k);`<br/>Multiplikation eines Polynoms mit `x` oder einer Potenz von `x`. Der Parameter `k` spezifiziert den Exponenten von `x`, beschreibt also den Term *x*<sup>k</sup>. |

*Tabelle* 4: Hilfsmethoden der Klasse `Polynom`.

Die arithmetischen Operatoren sollten in der Klasse `Polynom` auch in der Wertzuweisungsform vorhanden sein, siehe [Tabelle 5]:

###### {#tabelle_5_class_polynom_arithmetic_assignment_operators}

| Element | Beschreibung |
| :---- | :---- |
| Operator `+=` | `friend Polynom& operator+= (Polynom&, const Polynom&);`<br/>Additionswertzuweisung. |
| Operator `-=` | `friend Polynom& operator-= (Polynom&, const Polynom&);`<br/>Subtraktionswertzuweisung. |
| Operator `*=` | `friend Polynom& operator*= (Polynom&, const Polynom&);`<br/>Multiplikationswertzuweisung. |
| Operator `/=` | `friend Polynom& operator/= (Polynom&, const Polynom&);`<br/>Divisionswertzuweisung. |
| Operator `%=` | `friend Polynom& operator%= (Polynom&, const Polynom&);`<br/>Modulo Wertzuweisung. |

*Tabelle* 5: Arithmetische Operatoren der Klasse `Polynom` in der Wertzuweisungsform.

Auch zu den Operatoren von [Tabelle 5] führen wir ein Beispiel auf:

*Beispiel*:

```cpp
Polynom p1{ 1.0, 2.0, 3.0 };
Polynom p2{ 3.0, 2.0, 1.0 };
std::cout << p1 << std::endl;
std::cout << p2 << std::endl;

p1 += p2;
std::cout << p1 << std::endl;
p1 -= p2;
std::cout << p1 << std::endl;
p1 *= p2;
std::cout << p1 << std::endl;
p1 /= p2;
std::cout << p1 << std::endl;
p1 %= p2;
std::cout << p1 << std::endl;
```

*Ausgabe*:

```
3x^2+2x^1+1
x^2+2x^1+3
4x^2+4x^1+4
3x^2+2x^1+1
3x^4+8x^3+14x^2+8x^1+3
3x^2+2x^1+1
-4x^1-8
```

Bislang haben uns wir ausschließlich dem &ldquo;Ring der Polynome&rdquo; zugewendet, wie ein Mathematiker sagen würde.
Um die mathematische Schreibweise für die Auswertung eines Polynoms *p* an der Stelle *y* nachzuahmen,
bieten sich in C++ gleich zwei Operatoren an: Der Index-Operator `[]` sowie der Funktionsaufruf-Operator `()`, auch *Funktor* genannt.
Der Index-Operator bietet sich eigentlich immer dann an, wenn die zugrunde liegende Klasse den Charakter von etwas &ldquo;indizierbarem&rdquo; hat.
Dies trifft auf die Klasse `Polynom` eigentlich nicht zu, daher ist meine Wahl auf den Funktionsaufruf-Operator `()` gefallen:

###### {#tabelle_6_class_polynom_functor}

| Element | Beschreibung |
| :---- | :---- |
| Operator `()` | `double operator() (double x);`<br/>Auswertung des Polynoms an der Stelle `x`. |

*Tabelle* 6: Funktionsaufruf-Operator `()` zum Auswerten eines Polynoms.

*Beispiel*:

```cpp
Polynom p1{ 1.0 };
std::cout << "p1: " << p1 << std::endl;

std::cout << "p1(0.0) = " << p1(0.0) << std::endl;
std::cout << "p1(1.0) = " << p1(1.0) << std::endl;
std::cout << "p1(2.0) = " << p1(2.0) << std::endl;

Polynom p2{ 1.0, 3.0 };
std::cout << "p2: " << p2 << std::endl;

std::cout << "p2(0.0) = " << p2(0.0) << std::endl;
std::cout << "p2(1.0) = " << p2(1.0) << std::endl;
std::cout << "p2(2.0) = " << p2(2.0) << std::endl;

Polynom p3{ 2.0, -4.0, 0.0, 3.0 };
std::cout << "p3: " << p3 << std::endl;

std::cout << "p3(0.0) = " << p3(0.0) << std::endl;
std::cout << "p3(1.0) = " << p3(1.0) << std::endl;
std::cout << "p3(2.0) = " << p3(2.0) << std::endl;
```

*Ausgabe*:

```
p1: 1
p1(0.0) = 1
p1(1.0) = 1
p1(2.0) = 1
p2: 3x^1+1
p2(0.0) = 1
p2(1.0) = 4
p2(2.0) = 7
p3: 3x^3-4x^1+2
p3(0.0) = 2
p3(1.0) = 1
p3(2.0) = 18
```

Natürlich lassen sich Polynome auch vergleichen. In [Tabelle 7] finden Sie die üblichen Vergleichsoperatoren vor:

###### {#tabelle_7_class_comparison_operators}

| Element | Beschreibung |
| :---- | :---- |
| Operator `==` | `friend Polynom& operator== (const Polynom&, const Polynom&);`<br/>Test auf Gleichheit zweier Polynome. |
| Operator `!=` | `friend Polynom& operator!= (const Polynom&, const Polynom&);`<br/>Test auf Ungleichheit zweier Polynome. |
| Operator `<` | `friend Polynom& operator< (const Polynom&, const Polynom&);`<br/>Test auf &ldquo;Kleiner&rdquo; zweier Polynome. |
| Operator `<=` | `friend Polynom& operator<= (const Polynom&, const Polynom&);`<br/>Test auf &ldquo;Kleiner-Gleich&rdquo; zweier Polynome. |
| Operator `>` | `friend Polynom& operator> (const Polynom&, const Polynom&);`<br/>Test auf &ldquo;Größer&rdquo; zweier Polynome. |
| Operator `>=` | `friend Polynom& operator>= (const Polynom&, const Polynom&);`<br/>Test auf &ldquo;Größer-Gleich&rdquo; zweier Polynome. |

*Tabelle* 7: Vergleichsoperatoren für Objekte der Klasse `Polynom`.

WEITER: Testbeispioel und die Implementierung testen !!!!!!!!!!

// =================================================================================================

# There&lsquo;s more

Unsere bisherigen Betrachtungen einer Potenzmenge haben sich ausschließlich auf Grundmengen mit ganzen Zahlen beschränkt.
Für die Grundmenge kann man aber auch die Annahme treffen, dass deren integraler Datentyp (`int`, `short`, `long`, `size_t`, etc.) variabel sein sollte.
Auch kann man sich eine Grundmenge aus Zeichen (`char`) vorstellen.
Welche Änderungen sind an den beiden Klassen `PartialSet` und `PowerSet` vorzunehmen,
um die Grundmenge mit unterschiedlichen integralen Datentypen definieren zu können?

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_polynom_ctors
[Tabelle 2]: #tabelle_2_class_polynom_output
[Tabelle 3]: #tabelle_3_class_polynom_arithmetic_operators
[Tabelle 4]: #tabelle_4_class_polynom_helper_methods
[Tabelle 5]: #tabelle_5_class_polynom_arithmetic_assignment_operators
[Tabelle 6]: #tabelle_6_class_polynom_functor
[Tabelle 7]: #tabelle_7_class_comparison_operators

// [Listing 1]: #tabelle_1_class_polynom_ctors
// [Listing 2]: #listing_class_partialset_impl
// [Listing 3]: #listing_class_powerset_decl
// [Listing 4]: #listing_class_powerset_impl

<!-- End-of-File -->
