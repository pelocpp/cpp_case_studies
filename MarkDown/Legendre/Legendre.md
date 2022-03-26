<!-- Legendre.md -->

# Fakultäten, Binomialkoeffizienten und Herr Legendre

Die Fakultät ist in der Mathematik eine Funktion, die einer natürlichen Zahl *n* das Produkt
aller natürlichen Zahlen kleiner und gleich dieser Zahl zuordnet: *n*! = 1 * 2 * 3 * … * *n*.
In der Kombinatorik spielt die Fakultät ebenfalls eine große Rolle, weil *n*! die Anzahl der
Möglichkeiten ist, unterschiedliche Gegenstände der Reihe nach anzuordnen. 
Bei diesen Überlegungen kommen Binomialkoeffizienten ins Spiel.

Sowohl Fakultäten als auch Binomialkoeffizienten weisen eine unangenehme Eigenschaft auf:
Ihre Werte können sehr schnell sehr groß werden &ndash; und sind damit in Variablen des Typs `long` oder `size_t`
nicht mehr darstellbar. Ein Satz von Legendre verschafft hier Abhilfe:
Er befasst sich mit der Frage, wie oft ein Primfaktor in der Primfaktorzerlegung von *n*! für ein *n* &isinv; N vorkommt &ndash;
um damit eine alternative Darstellung für Fakultäten und Binomialkoeffizienten zu ermöglichen, die das Problem das Überlaufs umgehen kann.

Wir betrachten in dieser Fallstudie die Berechnung von Fakultäten und Binomialkoeffizienten sowohl in der 
klassischen Definition als auch als Produkt von Primfaktorzerlegungen mit Hilfe des Satzes von Legendre.

<!--more-->

# Lernziele

  * Klasse `std::unordered_map`
  * Structured Binding
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Notiert wird die Fakultätsfunktion durch ein dem Argument nachgestelltes Ausrufezeichen,
einer Schreibweise, die dem elsässischen Mathematiker Christian Kramp (1760 – 1826)
zugeordnet wird. Betrachten wir zur Veranschaulichung dieser Funktion
beispielsweise die drei Farben Rot, Grün und Blau. Wie viele Möglichkeiten gibt es, sie
anzuordnen? Für die erste Position kommen alle drei Farben in Betracht. Ist die erste Farbe
gesetzt, können nur noch zwei Farben um die zweite Position konkurrieren. Für die Belegung
der Positionen 1 und 2 ergeben sich bei drei Farben also 3 * 2 Möglichkeiten. Für die letzte
Position bleibt nur noch eine Farbe übrig, letztlich gilt für die Anzahl der
Anordnungsmöglichkeiten somit 3 * 2 * 1 = 3! = 6.

## Teilaufgabe 1: Klasse `Factorial`

Die Fakultätsfunktion lässt sich sehr einfach iterativ wie auch rekursiv programmieren.
Erstellen Sie eine Klasse `Factorial` mit zwei Methoden
`factorialRecursive` und `factorialIterative`. Die folgenden Code-Fragmente
sollten mit Hilfe Ihrer Klassenimplementierung ausführbar sein:

```cpp
Factorial f(5);
f.factorialIterative();
std::cout << f.get() << "! = " << f.value() << std::endl;

f.set(10);
f.factorialRecursive();
std::cout << f.get() << "! = " << f.value() << std::endl;
```

*Ausgabe*:

```
5! = 120
10! = 3628800
```

*Kontrollfrage*:
Ab welchem größerem *n* erhalten Sie mit Ihrem Testprogramm &ndash; offensichtlich &ndash; falsche
Resultate? Welche Erklärung haben Sie dafür?

## Teilaufgabe 2: Ein Nachschlagewerk

Zur Vorbereitung der nachfolgenden Teilaufgaben betrachten wir nun Nachschlagewerke in
der Programmierung. Darunter verstehen wir eine Datenstruktur, die zu einer bestimmten
Information (auch *Schlüssel* genannt) einen *Wert* verwaltet. Ein Telefonbuch ist ein solches
Beispiel: Als Schlüssel fungiert ein Name, die Telefonnummer ist ihm als Wert zugeordnet.
Fremdsprachenlexika sind ein weiteres Beispiel.

Wozu benötigen wir in dieser Fallstudie Nachschlagewerke?
Im Folgenden zerlegen wir bestimmte Zahlen in ihre Primfaktoren. Als Schlüssel fungiert die
Primzahl, der zugeordnete Wert ist der Exponent, der angibt, wie oft die Primzahl in der zu
zerlegenden Zahl vorkommt. Auf die Primfaktorenzerlegung gehen wir später ein, zunächst
halten wir fest, dass wir eine Klasse `PrimeDictionary` entwickeln, deren Schlüssel und
Werte jeweils vom Typ `size_t` sind. Weitere Hinweise entnehmen Sie bitte [Tabelle 1]:


###### {#tabelle_1_class_primedictionary}

| Element | Beschreibung |
| :---- | :---- |
| Konstruktor | `PrimeDictionary();`<br/>Standardkonstruktor für ein `PrimeDictionary`-Objekt. |
| Methode `get` | `size_t get(size_t key) const;`<br/>Liefert Wert zum Schlüssel `key` zurück. |
| Methode `set` | `void set(size_t key, size_t value);`<br/> Fügt einen neuen Eintrag (Schlüssel `key` mit Wert `value`) in das `PrimeDictionary`-Objekt ein. |
| Ausgabe | `std::ostream& operator<< (std::ostream&, const PrimeDictionary&);`<br/>Erzeugt ein `BigInteger`-Objekt anhand eines `long`-Werts. |
| Konvertierungs-Konstruktor | `explicit BigInteger(long long);`<br/>Es ist der Standardausgabeoperator zu implementieren. Eine Ausgabe könnte so aussehen:<br/>`(2,4)(3,2)(5,1)(7,1)` |

*Tabelle* 1: Element der Klasse `PrimeDictionary`.

*Hinweis*:
Zur Realisierung der Klasse `PrimeDictionary` sollten Sie einen geeigneten Container aus der STL einsetzen.
Welche Klasse bietet sich hier an?

Folgendes Code-Fragment sollte mit Hilfe Ihrer Realisierung ausführbar sein:

```cpp
PrimeDictionary dict{};
dict.set(2, 4);  // 2 hoch 4
dict.set(3, 2);  // 3 hoch 2
dict.set(5, 0);  // 5 hoch 0
dict.set(7, 1);  // 7 hoch 1
std::cout << dict << std::endl;

size_t key = 3;
size_t value = dict.get(key);
std::cout << "Value at " << key << ": " << value << std::endl;
dict.set(key, 22);
value = dict.get(key);
std::cout << "Value at " << key << ": " << value << std::endl;
```

*Ausgabe*:

```
(2,4)(3,2)(5,0)(7,1)
Value at 3: 2
Value at 3: 22
```

## Teilaufgabe 3: Der Satz von Legendre 

Die bislang vorgestellten Möglichkeiten zur Berechung der Fakultätsfunktion lösen nicht das
Problem, dass die Werte sehr schnell wachsen und in Variablen des Typs `size_t` ab einer
bestimmten Größe nicht mehr darstellbar sind. Am Beispiel von

```
100! =
93.326.215.443.944.152.681.699.238.856.266.700.490.715.968.264.381.621.
468.592.963.895.217.599.993.229.915.608.941.463.976.156.518.286.253.697.
920.827.223.758.251.185.210.916.864.000.000.000.000.000.000.000.000
```

können Sie das Problem eindrucksvoll erkennen.

Wir kommen nun zu einer anderen Alternative, große Zahlen darzustellen. Speziell für
Fakultäten ist dies auf eine Entdeckung des franz. Mathematikers *Adrien-Marie Legendre*
(1752 bis 1833) zurückzuführen. An Statt die Zahl im Zehnersystem hinzuschreiben, stellen
wir sie in ihrer Primfaktorzerlegung dar. Um die Primfaktoren einer Zahl zu berechnen,
müssten wir die Zahl aber selbst kennen, werden Sie nun vermutlich argumentieren &ndash; wir
können sie auf Grund ihrer Größe aber gar nicht softwaretechnisch darstellen. An dieser Stelle
kommt nun der Satz von Legendre ins Spiel, er lautet:

*Satz von Legendre*:
In der Primfaktorzerlegung von *n*! gilt für den Exponenten einer jeder
Primzahl, die *n*! teilt:

###### {#abbildung_1_satz_von_legendre}

{{< figure src="/img/legendre/SatzVonLegendre.png" width="50%" >}}

*Abbildung* 1: Der Satz von Legendre und Gaußklammern.

Hierbei repräsentieren in [Abbildung 1] die senkrechten Klammern so genannte Gaußklammern; sie stehen für
&ldquo;die größte ganze Zahl kleiner gleich *n*/*p*&rdquo;. Ferner beachte man: Von den Summanden |*n*/*p*<sup>i</sup>|
sind nur endlich viele ungleich 0, nämlich die für alle *i* mit *p*<sup>i</sup> &leq; *n*.

*Beispiel*:
Wir probieren die Formel am Beispiel von 10! aus. Die 2 hat in der Primfaktorzerlegung von 10! den Exponenten

e(2) = |10/2| + |10/4| + |10/8| = 5 + 2 + 1 = 8.

Für die 3 ergibt sich folgender Exponent:

e(3) = |10/3| + |10/9| = 3 + 1 = 4.

Für 5 gilt:

e(5) = |10/5| = 2.

Damit bleibt nur noch die Primzahl 7 übrig, alle weiteren Primzahlen sind größer als 10:

e(7) = |10/7| = 1.

Wir können uns nun von der Korrektheit des Satzes von Legendre überzeugen. Für die Zahl
10! schreiben wir in der dezimalen Darstellung 3.628.800. Unter Verwendung der
Primfaktoren 2, 3, 5, und 7 gilt

2<sup>8</sup> * 3<sup>4</sup> * 5<sup>2</sup> * 7<sup>1</sup> = 256 * 81 * 25 * 7 = 3.628.800.

Wir sehen, dass bei dieser Darstellung der Wert von *n*! nicht benötigt wird, die einzelnen
Primfaktoren lassen sich nur unter Zuhilfenahme von *n* berechnen! Da die Hochstellung von
Zahlen in einer Konsolenanwendung nicht ganz so einfach ist, modifizieren wir diese
Darstellung softwaregerechter ab in

10! = (2,8) (3,4) (5,2) (7,1)

Erweitern Sie nun die Klasse Factorial um eine Methode `factorialLegendre`, um die
Berechnung der Fakultät einer natürlichen Zahl in Partialbruchzerlegung durchzuführen:

```
PrimeDictionary factorialLegendre ();
```

Einen Pseudo-Code für den Satz von Legendre finden Sie in [Abbildung 2] vor:

###### {#abbildung_2_satz_von_legendre_pseudo_code}

{{< figure src="/img/legendre/SatzVonLegendre.png" width="50%" >}}

*Abbildung* 2: Satz von Legendre in Pseudo-Code-Darstellung.

Folgendes Code-Fragment sollte ausführbar sein:

```cpp
Factorial f(10);
PrimeDictionary primes = f.factorialLegendre();
std::cout << primes << std::endl;
```

*Ausgabe*:

```
(2,8)(3,4)(5,2)(7,1)
```

Mit Hilfe des Satzes von Legendre lassen sich weitere Fragen aus der Zahlentheorie beantworten.
Ein Beispiel gefällig?

Auf wie viele Nullen endet die Zahl 2012! ?

*Hinweis*:
Eine Null am Ende bedeutet, dass die Zahl durch 10 teilbar ist. Wie oft ist 2012! durch 10
teilbar? Sie ist so oft durch 10 teilbar, wie in der Primfaktorzerlegung genügend Zweien und
Fünfen vorkommen, um den Faktor 10 zu bilden.

Da der Faktor 2 alle geraden Zahlen teilt und somit häufiger vorhanden ist, lässt sich festhalten,
dass die Antwort allein durch die Anzahl der Fünfen bestimmt ist.

## Teilaufgabe 4: Der Binomialkoeffizient

Eine weitere Funktion aus dem Themenkreis der Kombinatorik ist der Binomialkoeffizient. Er
gibt an, auf wie viele verschiedene Arten man *k* Objekte aus einer Menge von *n*
verschiedenen Objekten auswählen kann – ohne Zurücklegen und ohne Beachtung der
Reihenfolge. Die mathematische Formel zur Berechnung des Binomialkoeffizienten für 0 &leq; *n* und 0 <= *k* &leq; *n* lautet wie folgt ([Abbildung 3]):

###### {#abbildung_3_binomial_coefficient_definition}

{{< figure src="/img/legendre/BinomialCoefficient.png" width="50%" >}}

*Abbildung* 3: Definition eines Binomialkoeffizienten.

Auf der linken Seite steht die Kurzschreibweise des Binomialkoeffizienten, gesprochen
&ldquo;n über k&rdquo;. Auf der rechten Seite steht die Berechnung des Koeffizienten als Bruch mit drei
Fakultäten. Wir verdeutlichen dies an zwei Beispielen in [Abbildung 4]:

###### {#abbildung_4_binomial_coefficient_definition_examples}

{{< figure src="/img/legendre/BinomialCoefficient_TwoSamples.png" width="50%" >}}

*Abbildung* 4: Zwei Beispiele für Binomialkoeffizienten.

Der Binomialkoeffizient &ldquo;49 über 6&rdquo; entspricht damit beispielsweise der Anzahl der
möglichen Ziehungen beim Lotto &ndash; nicht zu verwechseln mit der Treffer-Wahrscheinlichkeit
&ldquo;6 Richtige&rdquo; beim Lotto, die durch eine hypergeometrische Verteilung ermittelbar ist.

Erstellen Sie eine Klasse `BinomialCoefficient` mit einer Methode `calculate` zur
Berechnung des Binomialkoeffizienten. Die folgenden Code-Fragmente sollten mit Hilfe
Ihrer Klassenimplementierung ausführbar sein:

```cpp
BinomialCoefficient coeff;

for (size_t i{ 1 }; i != 10; ++i)
{
    coeff.setUpper(2 * i);
    coeff.setLower(i);
    coeff.calculate();

    std::cout
        << "Binomial "
        << coeff
        << " = "
        << coeff.value() << std::endl;
}
```

*Ausgabe*:

```
Binomial (2, 1) = 2
Binomial (4, 2) = 6
Binomial (6, 3) = 20
Binomial (8, 4) = 70
Binomial (10, 5) = 252
Binomial (12, 6) = 924
Binomial (14, 7) = 3432
Binomial (16, 8) = 12870
Binomial (18, 9) = 48620
```

Berechnen Sie der Reihe nach die Binomialkoeffizienten &ldquo;2 über 1&rdquo;, &ldquo;4 über 2&rdquo;, &ldquo;8 über 4&rdquo;, usw.
Ab welchem Koeffizienten machen Sie auch hier die Beobachtung, dass die sehr schnell wachsenden Werte zu falschen Resultaten führen.

## Teilaufgabe 5: Methode `reduce`

Um dieses Problem zu lösen, kommen wir wieder auf den Trick mit der Partialbruchzerlegung zurück.
Um den Koeffizienten &ldquo;*n* über *k*&rdquo; auszurechnen, berechnen wir die drei Werte *n*!, *k*! und (*n* – *k*)! als `PrimeDictionary`-Objekte
und vereinfachen diese anschließend.
Dazu werden wir eine Methode `reduce` einführen, die zwei `PrimeDictionary`-Objekte als
Parameter hat und die Vereinfachung des ersten `PrimeDictionary`-Objekts um das zweite
`PrimeDictionary`-Objekt durchführt. Dazu betrachten wir am besten ein Beispiel in [Abbildung 5]:

###### {#abbildung_5_binomial_coefficient_reduce_method}

{{< figure src="/img/legendre/ReduceSample.png" width="100%" >}}

*Abbildung* 5: Vereinfachung zweier `PrimeDictionary`-Objekte.

Ergänzen Sie nun Klasse `PrimeDictionary` um eine Methode `reduce`:

```cpp
void reduce (const PrimeDictionary&);
```

Die Reduktion eines `PrimeDictionary`-Objekts durch ein zweites erfolgt dadurch, indem
man das zweite `PrimeDictionary`-Objekt Eintrag für Eintrag traversiert und die Potenzen
der Primzahlen von denen des ersten `PrimeDictionary`-Objekts subtrahiert. Verwenden Sie
zum Testen Ihrer Implementierung das Beispiel aus [Abbildung 3].

## Teilaufgabe 6: Darstellung von Binomialkoeffizienten in Partialbruchdarstellung

Mit Hilfe der `reduce`-Methode können wir nun sehr schnell der Klasse
`BinomialCoefficient` eine Methode `calculateLegendre` hinzufügen:

```cpp
PrimeDictionary calculateLegendre () const;
```

Zur Berechnung eines Binomialkoeffizienten zu *n* und *k* sind gemäß [Abbildung 3] die drei
Fakultäten *n*!, *k*! und (*n* – *k*)! zu berechnen. Wenn Sie zuerst das `PrimeDictionary`-Objekt
zu *n*! um das `PrimeDictionary`-Objekt bzgl. *k*! reduzieren und das resultierende
`PrimeDictionary`-Objekt noch einmal um das `PrimeDictionary`-Objekt bzgl. (*n* – *k*)!
reduzieren, erhalten Sie den Binomialkoeffizienten &ndash; auch für sehr große Werte &ndash; in Partialbruchdarstellung.

Überprüfen Sie Ihre Implementierung an folgendem Codefragment:

```cpp
BinomialCoefficient bin;

for (size_t i{ 1 }; i != 25; i++)
{
    bin.setUpper(2 * i);
    bin.setLower(i);
    PrimeDictionary result = bin.calculateLegendre();

    std::cout
        << "Binomial ("
        << std::setw(2) << bin.getUpper()
        << ", "
        << std::setw(2) << bin.getLower()
        << ") = "
        << result << std::endl;
}
```

*Ausgabe*:

```
Binomial ( 2,  1) = (2,1)
Binomial ( 4,  2) = (2,1)(3,1)
Binomial ( 6,  3) = (2,2)(3,0)(5,1)
Binomial ( 8,  4) = (2,1)(3,0)(5,1)(7,1)
Binomial (10,  5) = (2,2)(3,2)(5,0)(7,1)
Binomial (12,  6) = (2,2)(11,1)(3,1)(5,0)(7,1)
Binomial (14,  7) = (2,3)(11,1)(3,1)(13,1)(5,0)(7,0)
Binomial (16,  8) = (2,1)(11,1)(3,2)(13,1)(5,1)(7,0)
Binomial (18,  9) = (2,2)(11,1)(3,0)(13,1)(5,1)(7,0)(17,1)
Binomial (20, 10) = (2,2)(19,1)(11,1)(3,0)(13,1)(5,0)(7,0)(17,1)
Binomial (22, 11) = (2,3)(19,1)(11,0)(3,1)(13,1)(5,0)(7,1)(17,1)
Binomial (24, 12) = (2,2)(19,1)(11,0)(3,0)(13,1)(5,0)(7,1)(17,1)(23,1)
Binomial (26, 13) = (2,3)(19,1)(11,0)(3,0)(13,0)(5,2)(7,1)(17,1)(23,1)
Binomial (28, 14) = (2,3)(19,1)(11,0)(3,3)(13,0)(5,2)(7,0)(17,1)(23,1)
Binomial (30, 15) = (2,4)(19,1)(11,0)(3,2)(13,0)(5,1)(7,0)(17,1)(23,1)(29,1)
Binomial (32, 16) = (2,1)(19,1)(11,0)(3,2)(13,0)(5,1)(7,0)(17,1)(23,1)(29,1)(31,1)
Binomial (34, 17) = (2,2)(19,1)(11,1)(3,3)(13,0)(5,1)(7,0)(17,0)(23,1)(29,1)(31,1)
Binomial (36, 18) = (2,2)(19,1)(11,1)(3,1)(13,0)(5,2)(7,1)(17,0)(23,1)(29,1)(31,1)
Binomial (38, 19) = (2,3)(19,0)(11,1)(3,1)(13,0)(5,2)(7,1)(17,0)(23,1)(29,1)(31,1)(37,1)
Binomial (40, 20) = (2,2)(19,0)(11,1)(3,2)(13,1)(5,1)(7,1)(17,0)(23,1)(29,1)(31,1)(37,1)
Binomial (42, 21) = (2,3)(19,0)(11,1)(3,1)(13,1)(5,1)(7,0)(17,0)(23,1)(29,1)(31,1)(37,1)(41,1)
Binomial (44, 22) = (2,3)(19,0)(11,0)(3,1)(13,1)(5,1)(7,0)(17,0)(23,1)(29,1)(31,1)(37,1)(41,1)(43,1)
Binomial (46, 23) = (2,4)(19,0)(11,0)(3,3)(13,1)(5,2)(7,0)(17,0)(23,0)(29,1)(31,1)(37,1)(41,1)(43,1)
Binomial (48, 24) = (2,2)(19,0)(11,0)(3,2)(13,1)(5,2)(7,0)(17,0)(23,0)(29,1)(31,1)(37,1)(41,1)(43,1)(47,1)
```

# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

TO BE DONE ????????????????

Wir versuchen, in der Realisierung der Fallstudie einige Aspekte von *Modern C++* zu integrieren.
Da wäre zum Beispiel das Morsealphabet. Es bietet sich an, diese Datenstruktur so zu konzipieren,
dass ihr Inhalt bereits vom Übersetzer gebildet werden kann. Das Schlüsselwort `constexpr` kommt daher zum Einsatz &ndash;
und ein Objekt der Klasse `std::array`, da dieses etliche `constexpr`-definierte Konstruktoren und Methoden besitzt:


# There&lsquo;s more

TO BE DONE ????????????????

Der Einsatz eines `std::array`-Objekts ist für performantes  Chiffrieren und Dechiffrieren nicht die
performanteste Lösung. Überlegen Sie, wie man eine *BiMap*-Klasse implementieren könnte,
um laufzeit-optimalere Ergebnisse zu erzielen.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_primedictionary

[Abbildung 1]: #abbildung_1_satz_von_legendre
[Abbildung 2]: #abbildung_2_satz_von_legendre_pseudo_code
[Abbildung 3]: #abbildung_3_binomial_coefficient_definition
[Abbildung 4]: #abbildung_4_binomial_coefficient_definition_examples
[Abbildung 5]: #abbildung_5_binomial_coefficient_reduce_method

[Listing 1]: #listing_1_class_morsecalculator_decl
[Listing 2]: #listing_2_class_morsecalculator_impl

<!-- End-of-File -->
