<!-- VariadicGenericFoldingAndMore.md -->

// Variadisch + Folding = Generisch + Rekursiv: Wie bitte?

// Projektname:  VariadicGenericFoldingAndMore


## Einleitung

Beginnend mit C++ 11 haben eine Reihe von neuen Sprachfeatures Einzug in die
Programmiersprache C++ gefunden:

 * Lambda-Funktionen
 * Generische Funktionen
 * Folding
 * Variadische Templates
 * Parameter Packs
 * Rekursive Parameter Pack Expansion
 * *IIFE* 

###### {#abbildung_1_but_why}

{{< figure src="/img/legendre/SatzVonLegendre.png" width="50%" >}}

*Abbildung* 1: Der Satz von Legendre mit Gaußklammern.


Sicherlich muss man all diese Konzepte erst einmal alleinstehend für sich betrachten,
um sie zu erfassen und zu verstehen.

In einem zweiten Schritt kommt es dann darauf an, diese Techniken miteinander zu verknüpfen!
Genau dies wollen wir an einer Reihe von Beispielen in dieser Fallstudie näher betrachten.

## Variadische Funktionen und Parameter Packs

Variadische Templates gehören zu den mächtigsten Erweiterungen von C++ ab der Version 11.
Diese Art der Schreibweise von Klassen und Funktionen
kann statt einer vorgegebenen &ndash; und damit festen &ndash; Anzahl 
von Argumenten (Datentypen, Parameter) eine beliebige Menge annehmen.
Darüber hinaus kann der Datentyp dieser Argumente in einem konkreten Anwendungsfall
dann unterschiedlich sein.
Abgelegt werden die Argumente in einem so genannten *Parameter Pack*.

Eine einfache *variadische Funktion* kann wie folgt definiert werden:

```cpp
auto f(auto ... args) {
    // some code to use args  
}
```

Die Ellipsis (...) nach dem Schlüsselwort `auto` bedeuten, dass `args` ein *Parameter Pack* ist.
Diese Funktion ist korrektes C++ &ndash; das Code-Fragment ist übersetzungsfähig &ndash;
und wir könnten sie so aufrufen:

```cpp
f(1, 2, 3);
```

oder auch so:

```cpp
f('1', 123, 987.654, std::string{"xyz"}, 10.0F);
```

Okay, zugegeben, der Rumpf der Funktion ist knapp geraten. Wir können beispielsweise die Anzahl der Parameter
mit dem `sizeof ...`&ndash;Operator bestimmen:


```cpp
auto f(auto ... args) {
    std::cout << sizeof...(args) << std::endl;
}
```

Damit erhalten wir bei der Ausführung von


```cpp
f(1, 2, 3);
f('1', 123, 987.654, std::string{ "xyz" }, 10.0F);
```

die Ausgaben

```
3
5
```

*Bemerkung*:

Variadische Funktionen ließen sich syntaktisch auch anders schreiben:
Als Lambda-Funktionen oder als Funktionstemplates:

```cpp
auto lambda = [](auto ... args) {
};
```

oder

```cpp
template<typename ... TArgs>
auto func (TArgs ... args) { 
};
```

## Zugriff auf die Elemente eines Parameter Packs: Folding

Leider gibt es kein sprachliches Mittel &ndash; etwa in der Art einer `for`&ndash;Wiederholungsschleife &ndash;,
um die Elemente eines Parameter Packs zu durchlaufen.

Dennoch lassen sich die Elemente eines Parameter Packs *verarbeiten*:
Hierzu gibt es (ab C++ 17) das so genannte *Folding* &ndash; syntaktisch in Gestalt von
*Folding Ausdrücken*. Versuchen wir es mal mit einem Beispiel:

```cpp
auto sum(auto ... args) {
    return (... + args);
}
```

Der Folding Ausdruck folgt dem `return`-Schlüsselwort, er muss in runden Klammern stehen.
Die Syntax ist mit Sicherheit gewöhnungsbedürftig, im vorliegenden Beispiel werden
alle Parameter des `sum`-Funktionsaufrufs in einen arithmetischen Ausdruck der Gestalt

```cpp
(((arg1+ arg2) + arg3) + ...)
```

umgewandelt. Man unterscheidet mehrere Varianten des Foldings, im Beispiel wird ein so genannter
*Unary Left Fold* demonstriert. Das *Left* bedeutet hier, dass Klammern (also der Vorrang) von links nach rechts
gesetzt werden.

*Beispiel*:

```cpp
auto result{ sum(1, 2, 3, 4, 5) };
std::cout << "Summe: " << result << std::endl;  // "Summe: 15"
```

Interessanterweise lässt sich die variadische Funktion `sum` auch mit Werten
unterschiedlichen Typs und auch mit nicht-arithmetischen Werten aufrufen, also zum Beispiel
mit `std::string`&ndash;Objekten. Im Falle von nicht-arithmetischen Datentypen ist es aber
erforderlich, dass die jeweilige Klasse den `+`&ndash;Operator unterstützt.
Bei Variablen unterschiedlichen Datentyps wird das Ergebnis nach den üblichen C/C++
Konvertierungsregeln bzgl. des &ldquo;*größten gemeinsamen*&rdquo; Datentyps berechnet.

*Beispiel*:

```cpp
auto result{ sum(100, 200l, 300ll, 400.0F, 500.0) };
std::cout << "Summe: " << result << std::endl;

auto concat{ sum(std::string{"ABC"}, std::string{ "DEF" }, std::string{ "GHI" }) };
std::cout << "Concatenation: " << concat << std::endl;
```

*Ausgabe*:

```
Summe: 1500
Concatenation: ABCDEFGHI
```

Noch ein etwas anwendungsbezogeneres Beispiel:
Die euklidische *Norm* eines *n*-dimensionalen Vektors
ist definiert als die Wurzel aus der Summe der Betragsquadrate
aller Komponenten des Vektors.
Stellen wir die Elemente eines *n*-dimensionalen Vektors in einem Parameter Pack
zusammen, kann man eine Funktion `norm` so definieren:

```cpp
auto norm(auto ... args) {
    return std::sqrt(((args * args) + ...));    // sqrt(arg1*arg1 + arg2*arg2 + ...)
}
```

Das Folding findet hier über dem Produkt der jeweiligen Parameter statt!

*Beispiel*:

```cpp
auto n{ norm(1.0, 2.0, 3.0, 4.0) };
std::cout << "Norm: " << n << std::endl;
```

*Ausgabe*:

```
Norm: 5.47723
```


Folding-Ausdrücke lassen es auch zu, dass die einzelnen Elemente eines Parameter Packs
Argument eines weiteren Funktionsaufrufs sind. Auch hierzu ein Beispiel:


```cpp
auto root (const auto& x) {
    return std::sqrt(x);
}

auto sumOfRoots(auto ... args) {
    return (root(args) + ...);
}
```

*Beispiel*:

```cpp
auto sum{ sumOfRoots(4.0F, 9.0F) };
std::cout << "SumOfRoots: " << sum << std::endl;
```

*Ausgabe*:

```
SumOfRoots: 5
```

## Parameter Pack an andere Funktionen weiterreichen

Eine Funktion kann ihr Parameter Pack an eine andere Funktion weiterreichen:

```cpp
auto sum(auto ... args) {
    return (args + ...);
}

auto average(auto ... args) {
    auto result{ sum(args ...) };
    return result / sizeof ... (args);
}
```

*Beispiel*:

```cpp
auto avg{ average(3.0F, 5.0F, 7.0) };
std::cout << "Average: " << avg << std::endl;
```

*Ausgabe*:

```
Average: 5
```

## Zugriff auf die Elemente eines Parameter Packs: Folding zum Zweiten

Mit Hilfe von Folding Ausdrücken kann man die Elemente eines Parameter Packs verarbeiten.
Manchmal möchte man aber pro Element eine Verarbeitung anstoßen, die sich nicht nur
auf die Anwendung eines einzelnen Operators beschränkt.
Wir sind noch einmal bei der Fragestellung angekommen,
ob es nicht doch irgendwie die Möglichkeit einer Art `for`&ndash;Wiederholungsschleife zum Traversieren 
des Parameter Packs gibt. 

Sagen wir es so: Der Ansatz mit `for` führt nach wie vor nicht zum Ziel,
aber es gibt eine spezielle Art des Foldings, die uns in die Nähe des Ziels bringt:
Das &ldquo;*Folding over a Comma*&rdquo;.

Ja, Sie haben es richtig gelesen: Wir wenden das Folding für den Komma-Operator `,` an.
Um es wahrheitsgemäßer zu sagen: Am Komma-Operator sind wir eigentlich überhaupt nicht interessiert,
aber mit seiner Hilfe schaffen wir es, ein Parameter Pack Element für Element auszupacken!

Es ist Zeit für ein Beispiel! Ich stelle im Folgenden
eine Funktion `doSomethingWithParameterPack` in mehreren Schreibweisen vor.
Die erste Variation sollte in puncto Lesbarkeit die beste sein:

###### {#listing_1_folding_over_a_comma}

```cpp
01: auto doSomethingWithParameterPack(auto ... args) {
02: 
03:     int i{};
04: 
05:     auto printElem = [&](auto arg)
06:     {
07:         ++i;
08:         std::cout << "Element " << i << ": " << arg << std::endl;
09:     };
10: 
11:     ( printElem(args) , ... );
12: }
```
*Listing* 1: &ldquo;*Folding over a Comma*&rdquo;.

Betrachten Sie in diesem Code-Fragment Zeile 11: Hier finden wir den diskutierten Folding-Ausdruck vor:
Ja, es mutet ein wenig merkwürdig an, den Komma-Operator hier vorzufinden.
Aber wenn Sie Zeile 11 genau betrachten, werden Sie erkennen, dass es eigentlich um den Aufruf
der Hilfsfunktion `printElem` geht. Und diese Funktion wird eben auf Grund des
&ldquo;*Abrollens*&rdquo; (so könnte man *Folding* ins Deutsche übersetzen)
der Reihe nach für jedes Element des Parameter Packs aufgerufen!

Nebenbei bemerkt: In *Listing* 1 finden wir eine Kombination der C++ Sprachkonstrukte
*Folding*, *Parameter Pack* und generische Lambda-Funktionen vor.

Wie versprochen, nun einige Alternativen zur Gestaltung des Quellcodes von Funktion `doSomethingWithParameterPack`:
Sollten Sie sich in Zeile 3 an der lokalen Variablen `i` stören, so könnte man
diese auch als &ldquo;*Instanzvariable*&rdquo; der inneren Lambda-Funktion `printElem` definieren:

###### {#listing_2_lambda_with_instance_variable}

```cpp
01: auto doSomethingWithParameterPack(auto ... args) {
02: 
03:     auto printElem = [&, i = 0]  (auto arg) mutable
04:     {
05:         ++i;
06:         std::cout << "Element " << i << ": " << arg << std::endl;
07:     };
08: 
09:     ( printElem(args) , ... );
10: }
```
*Listing* 2: Lambda-Funktion mit Instanzvariable.

Die Zählvariable `i` tritt nun in Zeile 3 von *Listing* 2 in Erscheinung.
Die Lambda-Funktion muss nun um das Schlüsselwort `mutable` ergänzt werden,
da nur dann die Zählvariable `i` modifiziert werden darf (Entfernen der `constness` des Aufrufoperators `()`).

Schon mal etwas von *IIFE* gehört? Okay, die Abkürzung verrate ich Ihnen:
*Immediately Invoked Functional Expression*.
Man versteht hierunter die Inline-Definition einer Lambda-Funktion mit unmittelbarem Aufruf!

###### {#listing_3_lambda_and_iife}

```cpp
01: auto doSomethingWithParameterPack(auto ... args) {
02: 
03:     auto printElemToConsole = [] (auto index, auto arg) 
04:     {
05:         std::cout << "Element " << index << ": " << arg << std::endl;
06:     };
07: 
08:     int i{};
09: 
10:     ( [&] { ++i; printElemToConsole(i, args); } () , ... );
11: }
```
*Listing* 3: *IIFE* an einem Beispiel gezeigt.

In *Listing* 3 werfen wir unser Augenmerk auf Zeile 10: Das entscheidende Symbol sind hier die
runden Klammern `()` nach der Inline-Definition der Lambda-Funktion

```cpp
[&] { ++i; printElemToConsole(i, args); } ()
```

Durch eben diese runden Klammern kommt es zum Aufruf der Lambda-Funktion!

Alle drei bislang vorgestellten Variationen der `doSomethingWithParameterPack`&ndash;Funktion
zeichnen sich dadurch aus, dass sie intern eine Hilfsfunktion verwenden.
Für alle Anhänger des Minimalismus gerne auch eine abschließende Variante ohne
Hilfsfunktion. Ich nehme es aber gleich vorweg:
Diese Realisierung ist am schwersten lesbar. Meiner Vorstellung von gutem Software-Quellcode entspricht sie nicht!

###### {#listing_4_folding_over_a_comma_minimalistic}

```cpp
01: auto doSomethingWithParameterPack(auto ... args) {
02: 
03:     int i{};
04: 
05:     ([&] { ++i; std::cout << "Element " << i << ": " << args << std::endl; } () , ... );
06: }
```
*Listing* 4: &ldquo;*Folding over a Comma*&rdquo; in minimalistischer Schreibweise.

In *Listing* 4 finden wir die innere Lambda-Funktion als Argument des Folding Ausdrucks vor &ndash; garniert mit
einem unmittelbaren Aufruf (*IIFE*).


## Rekursive Parameter Pack Expansion

Wir kommen wieder auf das Beispiel der Addition beliebig vieler Werte zurück.
Mit der Technik des *Foldings* haben wir hierfür bereits einen Lösungsansatz betrachtet:


```cpp
auto sum(auto ... args) {
    return (... + args);
}
```

Es schadet aber auch nichts, wenn man C++ Quellcode älterer C++ Versionen lesen kann.
Damit sind wir bei C++ 11 und rekursiven, variadischen Funktionen angekommen:

###### {#listing_5_recursive_parameter_pack_expansion}

```cpp
01: // end of recursion: one parameter left
02: auto sum(auto elem) {
03:     return elem;
04: }
05: 
06: // recursive case: 2 or more parameters
07: auto sum(auto first, auto ... args) {
08:     return first + sum (args ...);
09: }
```
*Listing* 5: Beispiel einer rekursiven Parameter Pack Expansion.

Beachten Sie in *Listing* 5 zunächst Zeile 7: Der Trick in der Rekursion liegt darin, dass
man das Parameter Pack in einen ersten und alle anderen Parameter zerlegt.
Also hier `first` für den ersten und `args ...` für die restlichen Parameter.
Wie in der gewöhnlichen rekursiven Programmierung müssen wir das Ende der Rekursion separat behandeln.
Dazu muss die Funktion `sum` überladen werden, dies geschieht in den Zeilen 2 bis 4.
Die eigentliche Rekursion findet in Zeile 8 statt: Es wird in Funktion `sum` wiederum `sum` aufgerufen,
allerdings mit einem Parameter weniger. 

Für diejenigen Leser, die eine exakte Formulierung bevorzugen: Eigentlich haben wir es in Zeile 8
nicht mit einem rekursiven Funktionsaufruf zu tun, sondern mit dem Aufruf einer Überladung der `sum`-Funktion.
Der Aufruf von `sum` in Zeile 8 erfolgt mit einem Parameter weniger, es handelt sich also streng genommen nicht
um einen rekursiven Aufruf. Ich überlasse es Ihnen, welche Formulierung Sie bevorzugen wollen.

Das Beispiel aus *Listing* 5 demonstriert ein Beispiel für generische Funktionen.
Wir hätten es auch mit Funktionstemplates realisieren können:

###### {#listing_6_templates_syntax_notation}


```cpp
01: // end of recursion: one parameter left
02: template <typename T>
03: auto sum(T elem) {
04:     return elem;
05: }
06: 
07: // recursive case: 2 or more parameters
08: template <typename T, typename ... TArgs>
09: auto sum(T first, TArgs ... args) {
10:     return first + sum(args ...);
11: }
```
*Listing* 6: Dasselbe Beispiel in Template Syntax Schreibweise.

Der Vollständigkeit halber noch die Schreibweise mit Lambda-Funktionen:

###### {#listing_7_lambda_syntax_notation_wrong}

```cpp
01: // end of recursion: one parameter left
02: auto sum = [](auto elem) {
03:     return elem;
04: };
05: 
06: // recursive case: 2 or more parameters
07: auto sum = [](auto first, auto ... args) {
08:     return first + sum(args ...);
09: };
```
*Listing* 7: Dasselbe Beispiel in der Lambda-Funktionsschreibweise.

*Vorsicht*: Der Quellcode aus *Listing* 7 ist **nicht** übersetzungsfähig.
Es wird suggeriert, dass wir es wie in *Listing* 5 oder *Listing* 6
mit einer Überladung von zwei Funktionen zu tun haben.

Lambdas sind anonyme Funktoren (d.h. unbenannte Funktionsobjekte bzw. unbenannte aufrufbare Objekte)
und keine einfachen Funktionen &ndash; wenngleich man häufig von Lambda *Funktionen* spricht,
aber auch diese Formulierung ist streng genommen falsch: Lambdas sind Objekte und keine Funktionen.
Daher ist ein Überladen dieser Objekte nicht möglich.

Wenn wir wieder zum C++ 17 Sprachumfang wechseln, können wir den Fehler beseitigen.
Offensichtlich geht eine Realisierung nur mit einem Aufrufoperator,
in dessen Rumpf wird mit `if constexpr` und `sizeof...` eine Fallunterscheidung eingebaut:

###### {#listing_8_lambda_syntax_notation_correct}

```cpp
01: auto sum = [](auto first, auto ... args) {
02: 
03:     if constexpr (sizeof... (args) == 0) {
04:         return first;
05:     }
06:     else {
07:         return first + sum(args ...);
08:     }
09: };
```
*Listing* 8: Dasselbe Beispiel in Lambda-Funktionsschreibweise &ndash; dieses Mal korrekt (C++ 17).

*Bemerkung*: Der Quellcode aus *Listing* 8 ist mit GCC nicht übersetzungsfähig.
Die Fehlermeldung lautet in Zeile 7: &ldquo;*Error: use of 'sum' before deduction of 'auto'*&ldquo;.
Wenn Sie eine Idee haben, wie man diesen Fehler beseitigen kann, würde ich mich über eine Nachricht sehr freuen.

## Funktionale Programmierung mit C++

Anonyme Funktionen &ndash; auch als Lambdas bezeichnet &ndash; wurden in C++ 11 als
praktische, leichtgewichtige Syntax zum Erstellen kurzlebiger Funktionen eingeführt.
Was nicht unmittelbar zu erkennen war:
Mit Hilfe derartiger Lambda Funktionen lassen sich nun auch
Konzepte der *funktionalen Programmierung* in C++ formulieren.

Ich will damit nicht zum Ausdruck bringen, dass &ldquo;Modern C++&ldquo; auf einer Ebene
wie zum Beispiel *Haskell* oder *F#* steht.
Aber das eine oder andere zentrale Konzepte der funktionalen Programmierung &ndash; wie zum Beispiel
*Currying* und *Funktionen höherer Ordnung* &ndash; können wir nun auch mit C++ Hilfsmitteln schreiben.

Was verstehen wir hierunter eigentlich:

  * *Currying* &ndash; Beschreibt die Transformation einer Funktion mit mehreren Argumenten in eine Folge von Funktionen mit einem Argument.
     Es wird ein Aufruf einer Funktion *f(a, b, c, ...)* in einen Aufruf *f(a)(b)(c)...* umgewandelt.

  * *Funktionen höherer Ordnung* &ndash; Darunter versteht man das Übergeben von Funktionen als Parameter an andere Funktionen
  und das Zurückgeben neuer Funktionen als Ergebnis!
  Eine Funktion höherer Ordnung besitzt eine oder mehrere Funktionen als Argument und gibt möglicherweise auch eine Funktion als Ergebnis zurück.

*Bemerkung*: Das viel zitierte *Currying* hat nichts mit Gerichten der asiatischen oder japanischen Küche zu tun.
Vielmehr ist der Name auf einen US-amerikanischen Logiker und Mathematiker namens *Haskell Brooks Curry* zurückzuführen.

### *Currying*

Wir starten gleich mit einem Beispiel einer generischen Funktion:

###### {#listing_9_currying}

```cpp
01: auto genericIncrementer = [] (auto x) {
02:     return [x] (auto y) {
03:         return x + y;
04:     };
05: };
```
*Listing* 9: Ein Beispiel für das *Currying*.

Trivial zu erkennen ist in *Listing* 9, dass `genericIncrementer` ein Lambda Objekt ist.
Nur welchen Rückgabetyp hat `genericIncrementer`?
Hierzu müssen wir schon etwas genauer hinschauen:
Nach der `return`&ndash;Anweisung im Rumpf steht der Ausdruck

```cpp
[x] (auto y) { return x + y; }
```

Das ist wieder ein Lambda Objekt!
Dieses ist allerdings nur im Kontext des umgebenden Lambda-Objekts lebensfähig,
da es in seiner *Capture Clause* auf den Parameter `x` des umgebenden Aufrufoperators zugreift!
Softwaretechnisch gesehen sind Lambdas Objekte vom Typ `std::function<T>`,
wobei der Template Parameter `T`
die Schnittstelle des Aufrufoperators beschreibt. Wir gehen hierauf gleich noch näher ein.
Zunächst betrachten wir jetzt die Anweisung

```cpp
auto incrementByTen{ genericIncrementer(10) };
```

`incrementByTen` ist folglich ein Lambda Objekt, das für das innere Lambda Objekt
einen Wert in der Capture Clause (hier: `10`) bereitstellt.
Natürlich können wir das Lambda Objekt `incrementByTen` aufrufen:

```cpp
auto result{ incrementByTen(5) };
std::cout << "Result: " << result << std::endl;     // "Result: 15"
```
Ein Merkmal des *Currying* ist es, dass wir auf diese Weise eine Vielzahl solcher Lambda Funktionen
erzeugen können. Zum Beispiel ein `incrementByTen`, ein `incrementByOne`, etc.,
nur um ihre Phantasie etwas anzuregen. 

In der Konsole erhalten wir den Wert `15` als Ergebnis.
Damit sollte das Prinzip des Curryings verständlich geworden sein:
&ldquo;Wir zerlegen eine Funktion,
die mehrere Argumente verwendet, in eine Reihe mehrerer Funktionen,
die jeweils nur ein Argument verwenden.&rdquo;

Moment mal! Wo hatten wir in unseren bisherigen Beispielen den Aufruf mit den &ldquo;vielen&rdquo; Argumenten?
Diesen Aufruf sollten wir nachreichen:

```cpp
auto result{ genericIncrementer(10)(5) };  // ==> "Result: 15"
```

Wir sprachen schon über den Rückgabetyp von `genericIncrementer`.
Der Gebrauch des `auto`&ndash;Schlüsselworts verleitet zu leichter lesbarem Quellcode &ndash;
und sollte von einem versierten C++ Entwickler auch bevorzugt werden!

Ist &ndash; wiederum vor dem Hintergrund der leichter Lesbarkeit des Quellcodes diskutiert &ndash;
der tatsächlich vorliegende Datentyp jedoch nicht einfach eruierbar,
sollte oder könnte man auf `auto` auch verzichten und den tatsächlich vorliegenden Datentyp verwenden.
Ein Leser Ihres Quellcodes wird Ihnen sicherlich dafür dankbar sein. Aber entscheiden Sie doch selbst:

###### {#listing_10_std_function_explained}

```cpp
01: std::function<int(int)> incrementByTen{ genericIncrementer(10) };
02: 
03: auto result{ incrementByTen(5) };
04: std::cout << "Result: " << result << std::endl;
05: 
06: std::function<int(int)> incrementByFive{ genericIncrementer(5) };
07: result = incrementByFive(10);
08: std::cout << "Result: " << result << std::endl;
```
*Listing* 10: Lambda-Objekte, durch `std::function<int(int)>` definiert.

In *Listing* 10 erkennt man durch schnelles Lesen nun, dass in den Zeilen 1 und 6
aufrufbare Objekte (*Callables*) definiert werden &ndash;
und damit keine elementaren Variablen.

### Funktionen höherer Ordnung

Eine Funktion höherer Ordnung ist eine Funktion,
die mindestens eine der folgenden Anforderungen erfüllt:

  * Sie akzeptiert eine Funktion als Argument.
  * Sie gibt eine neue Funktion zurück.
  
Auch hier starten wir gleich mit einem Beispiel:

###### {#listing_11_high_order_function}

```cpp
01: auto timesTwo = [](auto x) {
02:     return 2 * x;
03: };
04: 
05: auto repeat = [](auto func, size_t n) {
06:     auto result{ 1 };
07: 
08:     for (size_t i{ 1 }; i <= n; ++i) {
09:         result = func(result);
10:     }
11: 
12:     return result;
13: };
14: 
15: void test()
16: {
17:     auto result = repeat(timesTwo, 5);
18:     std::cout << "repeat: " << result << std::endl;
19: }
```
*Listing* 11: Beispiel einer Funktion höherer Ordnung.

Funktion `repeat` besitzt als ersten Parameter (Zeile 5) einen Formalparameter namens `func`
vom Typ `auto`.
Wir sollten uns bewusst sein, dass wir aus Zeile 5 nicht schlau werden können,
worum es sich bei `func` eigentlich handelt.
In Zeile 9 wird es nun konkreter: Auf Grund der Quellcode-Fragments

```cpp
func(result);
```
muss es sich bei `func` um etwas &ldquo;*Aufrufbares*&rdquo; handeln, also ein *Callable* im C++&ndash;Jargon.
Es sind die runden Klammern nach `func`, die den Compiler auf diese Fährte führen.
Es wurde schon mehrere Male angesprochen:
Auch wenn man landläufig von Lambda Funktionen spricht, haben wir es mit *Objekten* zu tun.
Oder noch etwas krasser: Lambda Funktionen sind keine Funktionen.

Objekte hingegen lassen sich als Parameter an andere Funktionen übergeben,
damit betrachten wir Zeile 17 in *Listing* 11:

```cpp
auto result = repeat(timesTwo, 5);
```
Es wird die Funktion `repeat` mit dem Lambda Objekt `timesTwo` aufgerufen,
das Lambda Objekt gelangt im Rumpf von `repeat` zur Ausführung.
Folglich ist `repeat` eine Funktion höherer Ordnung.

Die Flexibilität einer Funktion höherer Ordnung verstehen wir vielleicht erst wirklich dann,
wenn wir `repeat` mit unterschiedlichen Funktionen aufrufen.
Spendieren wir neben `timesTwo` doch noch eine weitere Funktion `timesThree`:

```cpp
auto timesThree = [](auto x) {
    return 3 * x;
};
```
Jetzt betrachten wir das folgende Anwendungsbeispiel:

###### {#listing_12_high_order_function_with_different_functions}

```cpp
01: void test_variadic_generic_folding_01()
02: {
03:     auto result = repeat(timesTwo, 5);
04:     std::cout << "repeat: " << result << std::endl;
05: 
06:     result = repeat(timesThree, 5);
07:     std::cout << "repeat: " << result << std::endl;
08: }
```
*Listing* 12: Aufruf einer Funktion höherer Ordnung mit unterschiedlichen Funktionen.

*Ausgabe*:

```
repeat: 32
repeat: 243
```

### Verschachtelte Funktionsaufrufe generischer Funktionen

Das Beispiel aus *Listing* 12 hätten wir auch ohne Funktion `repeat` und damit ohne
eine Funktion höherer Ordnung realisieren können, zum Beispiel so:

###### {#listing_13_nested_generic_functions}

```cpp
01: void test_variadic_generic_folding_01()
02: {
03:     auto result = timesTwo(timesTwo(timesTwo(timesTwo(1))));   // 2*2*2*2 ==> "Result: 16"
04:     std::cout << "Result: " << result << std::endl;
05: }
```
*Listing* 13: Verschachtelte Funktionsaufrufe generischer Funktionen.

In Zeile 3 von *Listing* 13 finden wir &ndash; einen nahezu klassischen &ndash; geschachtelten Funktionsaufruf vor.
Dieses Mal liegen bei den Parametern `int`-Werte vor, also haben wir es nicht
mit einer Funktion höherer Ordnung zu tun.

Okay, ich vermute mal, Sie werden sagen:
Das ginge vielleicht auch etwas &ldquo;eleganter&rdquo;,
wobei ich es Ihnen überlasse, ein geeignetes Wort für den von mir angestrebten Sachverhalt zu finden.
Die Formulierung eines geschachtelten Funktionsaufrufs ist bisweilen immer etwas mühsam,
man muss die schließenden runden Klammern am Ende des Ausdrucks genau zählen.

&ldquo;We can do better&rdquo;: Wie wäre es mit einer separaten Funktion `combine` 
&ndash; und wie sollte es anders sein: einer Funktion höherer Ordnung,
deren Argumente (Lambda Objekte) über das Parameter Pack übergeben werden
und von `combine` verschachtelt aufgerufen werden.

Das war jetzt vielleicht etwas viel auf einmal,
fangen wir in es *Listing* 14 etwas langsamer an:
Hier wollen wir meine Idee einer Funktion `combine` zunächst einmal von der Konzeption 
her gesehen betrachten:

###### {#listing_14_combine_simple_explained}

```cpp
01: auto timesTwo = [](auto x) {
02:     return 2 * x;
03: };
04: 
05: auto combine(auto func) {
06:     return func;
07: }
08: 
09: auto combine(auto func1, auto func2)
10: {
11:     return [&](auto ... parameters) {
12:         return func1(func2(parameters...));
13:     };
14: }
15: 
16: auto combine(auto func1, auto func2, auto func3)
17: {
18:     return [&](auto ... parameters) {
19:         return func1(func2(func3(parameters ...)));
20:     };
21: }
22: 
23: auto combine(auto func1, auto func2, auto func3, auto func4)
24: {
25:     return [&](auto ... parameters) {
26:         return func1(func2(func3(func4(parameters ...))));
27:     };
28: }
29: 
30: void test_variadic_generic_folding_01()
31: {
32:     auto result{ combine(timesTwo, timesTwo, timesTwo, timesTwo)(1) };  // 2*2*2*2
33:     std::cout << "combine: " << result << std::endl;
34: }
```
*Listing* 14: Diverse Überladungen einer Hilfsfunktion `combine` für einen verschachtelten Funktionsaufruf.

Lassen Sie mich aus *Listing* 14 die Überladung von `combine` aus den Zeilen 9 bis 14 herauspicken:

```cpp
auto combine(auto func1, auto func2)
{
    return [&](auto ... parameters) {
        auto result = func1(func2(parameters...));
        return result;
    };
}
```
Funktion `combine` besitzt zwei Funktionsobjekte `func1` und `func2` als Parameter:

Der verschachtelte Aufruf wird in einem inneren Lambda Objekt durchgeführt,
der Ergebniswert wird mit `return` zurückgegeben.
In Listing 14 habe ich den verschachtelten Aufruf als Argument in der `return`&ndash;Anweisung platziert,
damit wird das Ganze noch ein wenig kompakter.

Aber Vorsicht: Die tatsächliche Ausführung des verschachtelten Funktionsaufrufs
findet nicht im Kontext von `combine` statt: `combine` liefert als Ergebnis ein Lambda Objekt zurück!

Viel interessanter ist die Frage, wie eigentlich die Parameter `parameters` in die
Hilfsfunktion `combine` gelangen?
Einfache Antwort: Überhaupt nicht! Die Parameter sind beim Aufruf des zurückgegebenen
Lambda Objekts bereitzustellen,
und das ist in unserem Beispiel am Ende von Zeile 32 der Fall &ndash; hier mit dem Wert `1`.
Da es sich um ein Parameter Pack handelt, könnten dies auch mehrere Parameter sein.
Die Thematik &ldquo;*Parameter Pack an andere Funktionen weiterreichen*&rdquo;
hatten wir bereits betrachtet.

Zugegeben, nach dem Studium des Quellcodes aus *Listing* 14 werden Sie sich sicherlich fragen,
wo bei den vielen Überladungen der `combine` Hilfsfunktion noch ein Vorteil liegt?
Vielleicht erahnen Sie es schon: &ldquo;Again we can do better&rdquo;!

## Betrachtung einer generischen Funktionen höherer Ordnung mit rekursiver Parameter Pack Expansion

Ich weiß, diese Überschrift sollte man nicht ernst nehmen, aber es war ja das Ziel dieser Fallstudie,
möglichst viele Konzepte von &ldquo;Modern C++&ldquo; in möglichst geschickten Kombinationen darzulegen.

Die vielen Überladungen der `combine` Hilfsfunktion lassen sich auf eine reduzieren,
wenn man das Parameter Pack rekursiv auspackt &ndash; siehe *Listing* 15:

###### {#listing_15_generic_combine_high_order_function}

```cpp
01: auto combine(auto func)
02: {
03:     return func;
04: }
05: 
06: auto combine(auto func, auto ... funcs)
07: {
08:     return [&](auto ... parameters) {
09:         return func(combine(funcs ...) (parameters ...));
10:     };
11: }
```
*Listing* 15: Beispiel einer generischen Funktion höherer Ordnung für den verschachtelten Funktionsaufruf.

Mit den geleisteten Vorarbeiten sollte es nicht so schwer sein,
den Quellcode aus *Listing* 15 zu verstehen.
In Zeile 9 finden wir einen rekursiven Aufruf der Funktion `combine` vor.
Diese nimmt ein Parameter Pack entgegen, aber Achtung: Das Pack `funcs` ist quasi schon um ein Funktionsobjekt reduziert.
Das erste Funktionsobjekt `func` wird aufgerufen, um das Ergebnis des rekursiven Aufrufs entgegenzunehmen.

Da wir ein Beispiel mit rekursiver Parameter Pack Expansion betrachten,
benötigen wir noch eine Überladung der `combine`-Funktion,
die die Rekursion abbricht: Siehe hierzu die Zeilen 1 bis 4 von *Listing* 15.

Wir präsentieren ein Anwendungsbeispiel, um einen Aufruf der Funktion `combine` zu demonstrieren:

```cpp
auto timesTwo = [](auto x) {
    return 2 * x;
};

void test()
{
    auto result = combine(
        timesTwo, 
        timesTwo,
        timesTwo,
        timesTwo, 
        timesTwo,
        timesTwo,
        timesTwo, 
        timesTwo,
        timesTwo,
        timesTwo
    )(1);
    
    std::cout << "result: " << result << std::endl;
}
```

*Ausgabe*:

```
result: 1024
```

## Kombination von Prädikatsfunktionen mit logischer Konjunktion und Disjunktion

Möglicherweise ist mir der letzte Abschnitt doch etwas zu theoretisch geraten.
Wir wollen das Ganze um ein weiteres Beispiel ergänzen &ndash; es geht um den STL
Algorithmus `std::copy_if`.
Im letzten Parameter erwartet `std::copy_if` eine unäre Prädikatsfunktion, die
auf jedes Element des zu Grunde liegenden Containers angewendet wird und je nach Betrachtung
`true` oder `false` zurückgibt. 

Wenn wir einen Container mit Zeichenketten (`std::string`) nehmen,
könnten unäre Prädikatsfunktionen so aussehen:

```cpp
auto beginsWith = [](const std::string& s) {
    return s.find(std::string{ "a" }) == 0;
};

auto endsWith = [](const std::string& s) {
    return s.rfind(std::string{ "b" }) == s.length() - 1;
};
```

Der Parameter der beiden Prädikatsfunktionen muss vom Typ `std::string` sein,
weitere Qualifizierungen mit `const` oder `&` spielen in diesem Zusammenhang keine Rolle.
Der Rückgabetyp muss `bool` sein, was von den beiden Funktionen `beginsWith` und `endsWith` erfüllt wird.

Die beiden Lambda Objekte `beginsWith` und `endsWith` sind
einfache &ldquo;filtrierende&rdquo; Prädikatsfunktionen, um
Zeichenketten zu finden, die entweder mit `a` beginnen bzw. mit `b` enden.

Wir könnten diese beiden Funktionen in der Tat direkt als Argument für `std::copy_if` verwenden.
Aber dann suchen wir halt nur nach Zeichenketten, die entweder mit `a` beginnen oder mit `b` enden.
Wie gehen wir vor, wenn wir beide  &ndash; oder sogar noch weitere &ndash; Prädikatsfunktionen verwenden wollen,
deren jeweilige Ergebnisse dann mit entsprechenden logischen Operationen zu verknüpfen sind?

Wenn wir diesen Ideenansatz weiter verfolgen, sind wir wieder bei einer Funktion in der Art `combine`
angekommen, die sowohl die einzelnen unären Prädikatsfunktionen als auch eine weitere Funktion 
&ndash; nennen wir sie zum Beispiel `boolAnd` &ndash; entgegennimmt,
die sich um die logische Verknüpfung der Teilergebnisse der Prädikatsfunktionen abschließend kümmert.
Und wenn das alles noch nicht ausreichend ist: Das Ergebnis dieser Funktion soll als Argument für `std::copy_if`
herhalten können:

###### {#listing_16_second_generic_combine_high_order_function}

```cpp
01: auto combine(const auto& binaryFunc, auto pred1, auto pred2)
02: {
03:     return [=] (auto param) {
04:         return binaryFunc(pred1(param), pred2(param));
05:     };
06: };
07: 
08: auto boolAnd = [](auto left, auto right) {
09:     return left && right;
10: };
11: 
12: void test_variadic_generic_folding_01()
13: {
14:     std::vector <std::string> strings {
15:         "axyzb", "bxyza", "C++", "is", "wonderful", "ab"
16:     };
17: 
18:     std::vector <std::string> result;
19: 
20:     std::copy_if (
21:         strings.begin(),
22:         strings.end(),
23:         std::back_inserter(result),
24:         combine(boolAnd, beginsWith, endsWith)
25:     );
26: 
27:     for (const auto& s : result) {
28:         std::cout << s << " ";
29:     }
30: 
31:     std::cout << std::endl;
32: }
```
*Listing* 16: Anwendungsbeispiel für Kombination von Prädikatsfunktionen.

*Ausgabe*:

```
axyzb ab
```

In den Zeilen 1 bis 6 von *Listing* 16 finden Sie ein Lambda Objekt namens `combine` vor.
Dieses Funktionsobjekt gibt wiederum ein Lambda Objekt zurück,
dessen Verwendung für den `std::copy_if`-Algorithmus gedacht ist.

Die `combine`-Funktion benötigt folglich drei Funktionsparameter: eine binäre Konjunktion
und zwei Prädikatsfunktionen. Zurückgegeben wird ein Lambda Objekt,
in dessen Rumpf die Konjunktion mit den zwei Prädikatsfunktionen gebildet wird.

Wir wäre es mit einer kleinen Übungsaufgabe?
Im Quellcode von *Listing* 16 wurde das `auto`-Schlüsselwort sicherlich recht intensiv eingesetzt.
Ist Ihnen wirklich an jeder Stelle des Quellcodes klar, welcher Datentyp
vom Compiler tatsächlich abgeleitet wird?
Versuchen Sie doch einmal, das Beispiel aus *Listing* 16 ohne `auto` zu programmieren.
Ich will die Spannung nicht weiter aufrecht halten,
in *Listing* 17 finden Sie eine äquivalente Implementierung des Beispiels aus *Listing* 16 vor &ndash;
nur ohne Verwendung von `auto`:

###### {#listing_17_second_generic_combine_high_order_function_without_auto}

```cpp
01: template <typename T>
02: std::function<bool(T)> combine(
03:     std::function<bool(bool, bool)> binaryFunc,
04:     std::function<bool(T)> pred1,
05:     std::function<bool(T)> pred2)
06: {
07:     return [=](T arg) {
08:         return binaryFunc(pred1(arg), pred2(arg));
09:     };
10: };
11: 
12: std::function<bool(std::string)> beginsWith = [](const std::string& s) {
13:     return s.find(std::string{ "a" }) == 0;
14: };
15: 
16: std::function<bool(std::string)> endsWith = [](const std::string& s) {
17:     return s.rfind(std::string{ "b" }) == s.length() - 1;
18: };
19: 
20: std::function<bool(bool, bool)> boolAnd = [](bool left, bool right) {
21:     return left && right;
22: };
23: 
24: std::function<bool(bool, bool)> boolOr = [](bool left, bool right) {
25:     return left || right;
26: };
27: 
28: void test_variadic_generic_folding_01()
29: {
30:     std::vector <std::string> strings { 
31:         "axyzb", "bxyza", "aaa", "bbb", "C++", "is", "wonderful", "ab"
32:     };
33: 
34:     std::vector <std::string> result;
35: 
36:     std::copy_if(
37:         strings.begin(),
38:         strings.end(),
39:         std::back_inserter(result),
40:         combine(boolOr, beginsWith, endsWith)
41:     );
42: 
43:     for (const std::string& s : result) {
44:         std::cout << s << " ";
45:     }
46: 
47:     std::cout << std::endl;
48: 
49:     result.clear();
50: 
51:     std::copy_if(
52:         strings.begin(),
53:         strings.end(),
54:         std::back_inserter(result),
55:         combine(boolAnd, beginsWith, endsWith)
56:     );
57: 
58:     for (const std::string& s : result) {
59:         std::cout << s << " ";
60:     }
61: 
62:     std::cout << std::endl;
63: }
```

*Listing* 17: Das Anwendungsbeispiel aus *Listing* 16, implementiert ohne Gebrauch von `auto`.

*Ausgabe*:

```
axyzb aaa bbb ab
axyzb ab
```

Sie können nun selbst vergleichen, wie sich die Stilistik von C++&ndash;Programmen im Erscheinungsbild der Jahre gewandelt hat.
Und es sollte nach wie vor Ihre Entscheidung sein, welche der modernen C++ Bausteine Sie in Ihren eigenen Quellcode integrieren.

## Ausblick


Ich bin am Ende meiner Ausführungen angekommen! Ich hoffe, es hat Ihnen etwas Spaß bereitet,
zu verfolgen, welche neuen Möglichkeiten bzgl. Programmierstil und -paradigmen in &ldquo;Modern C++&ldquo;
zur Verfügung stehen.


<br/>

## Literatur

Einige Beispiele und Anregungen zu dieser Fallstudie stammen aus dem Aufsatz
&ldquo;[What are C++ variadic templates and fold expressions?](https://iamsorush.com/posts/cpp-variadic-template/)&rdquo;
(abgerufen am 8. Mai 2023).

Auch wurden Anregungen durch das Buch 

  * Bill Weinmann, &ldquo;*C++ Cookbook (1th Edition)*&rdquo;.</br>
    Verlag Packt (27. Mai 2022), 450 Seiten. Sprache: Englisch. ISBN-13: 978-1-80324-871-4, ISBN-10: 1803248718.

gegeben.

<br/>


<!-- Links Definitions -->

[Abbildung 1]: #abbildung_1_but_why


[Listing 1]: #listing_01_primedictionary_decl
[Listing 2]: #listing_01_primedictionary_impl
[Listing 3]: #listing_03_factorial_decl
[Listing 4]: #listing_03_factorial_impl
[Listing 5]: #listing_05_binomialcoefficient_decl
[Listing 6]: #listing_06_binomialcoefficient_impl

<!-- End-of-File -->
