# Variadisch + Folding = Generisch + Rekursiv: Wie bitte?

// Projektname:  VariadicGenericFoldingAndMore

## TO BE DONE

// WEITER: Concepts... Beispiel 

// Logisches AND und OR

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

Sicherlich muss man all diese Konzepte erst einmal alleinstehend für sich betrachten,
um sie zu erfassen und zu verstehen.

Interessanter wird es, wenn man diese Techniken miteinander verknüpft!

Genau dies wollen wir an einer Reihe von Beispielen näher betrachten.
Erst auf diese Weise kann man erkennen, in welche Richtung sich die Stilistik entwickelt.

Im Mittelpunkt der folgenden Beispiele soll der Ansatz stehen, mehrere dieser Techniken miteinander zu verknüpfen.
Erst auf diese Weise kann man erkennen, welche Pfade die Stilistik eines "Modern C++" Programms einschlägt.

## Variadische Funktionen und Parameter Packs

Variadische Templates gehören zu den mächtigsten Erweiterungen von C++.
Diese Art in der Schreibweise von Klassen und Funktionen
kann statt einer vorgegebenen &ndash; und damit festen &ndash; Anzahl 
von Argumenten eine beliebige Menge an Argumenten annehmen.
Darüberhinaus kann der Datentyp dieser Argumente unterschiedlich sein.
Abgelegt werden die Argumente in einem so genannten *Parameter Pack*.

Eine einfache *variadische Funktion* kann wie folgt definiert werden:

```cpp
auto f(auto ... args) {
    // some code to use args  
}
```

Die Ellipsis (...) nach dem Schlüsselwort `auto` bedeuten, dass `args` ein *Parameter Pack* ist.


Diese Funktion ist korrektes C++ &ndash; wir können sie so aufrufen:

```cpp
f(1, 2, 3);
```

oder

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
auto tf(TArgs ... args) { 
};
```

## Zugriff auf die Elemente eines Parameter Packs: Folding

Leider gibt es kein sprachliches Mittel &ndash; etwa eine Art `for`&ndash;Wiederholungsschleife &ndash;,
um die Elemente eines Parameter Packs zu durchlaufen.

Dennoch lassen sich die Elemente eines Parameter Packs *verarbeiten*:
Hierzu gibt es das so genannte *Folding* &ndash; syntaktisch in Gestalt von
*Folding* Ausdrückern. Versuchen wir es mal an einem Beispiel:

```cpp
auto sum(auto ... args) {
    return (... + args);     // (((arg1+ arg2) + arg3) + ...)
}
```

*Beispiel*:

```cpp
auto result{ sum(1, 2, 3, 4, 5) };
std::cout << "Summe: " << result << std::endl;  // "Summe: 15"
```

Interessanterweise lässt sich die variadische Funktion `sum` auch mit Werten
untschiedlichen Typs als auch mit nicht-arithmetischen Werten aufrufen, zum Beispiel
mit `std::string`&ndash;Objekten. Im Falle von nicht-arithmetischen Datentypen ist es aber
erforderlich, dass die jeweilige Klasse den `+`&ndash;Operator unterstützt:

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
ist definiert als
der Wurzel aus der Summe der Betragsquadrate der Komponenten des Vektors.

Stellen wir die Elemente eines  *n*-dimensionalen Vektors in einem Parameter Pack
zusammen, kann man eine Funktion `norm` so definieren:

```cpp
auto norm(auto ... args) {
    return std::sqrt(((args * args) + ...));    // sqrt(arg1*arg1 + arg2*arg2 + ...)
}
```

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
Argument eines anderen Funktionsaufrufs sind. Auch hierzu ein Beispiel:


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

## Parameter Packs an andere Funktionen weiterreichen

Eine Funktion kann ihr Parameter Pack an eine andere Funktion weiterreichen:

```cpp
auto sum(auto ... args) {
    return (args + ...);
}

auto average(auto ... args) {
    auto result{ sum(args...) };
    return result / sizeof... (args);
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
ob es nicht doch die Möglichkeit einer Art `for`&ndash;Wiederholungsschleife zum Traversieren 
des Parameter Packs gibt. 

Sagen wir es so: Der Ansatz mit `for` führt nach wie vor nicht zum Ziel,
aber es gibt eine spezielle Art des Foldings, die uns in die Nähe des Ziels bringt:
Das &ldquo;*Folding over a Comma*&rdquo;.

Ja, Sie haben es richtig gelesen: Wir wenden das Folding für den Komma-Operator `,` an.
Um es wahrheitsgemäßer zu sagen: Am Komma-Operator sind wir aber nicht so sehr interessiert,
aber mit seiner Hilfe schaffen wir es aber, ein Parameter Pack Element für Element auszupacken!

Es ist Zeit für ein Beispiel! Ich stelle im Folgenden
eine Funktion `doSomethingWithParameterPack` in mehreren Schreibweisen vor.
Die erste Variation sollte von der Lesbarkeit die beste sein:


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
Ja, es mutet ein wenig merkwürdig an, den Komme-Operator hier vorzufinden.
Aber wenn Sie Zeile 11 genau betrahten, werden Sie erkennen, dass es eigentlich um den Aufruf
der Hilfsfunktion `printElem` geht. Und diese Funktion wird eben auf Grund des
&ldquo;*Abrollens*&rdquo; (so könnten man *Foldung* ins Deutsche übersetzen)
der Reihe nach für jedes Element des Parameter Packs aufgerufen!

Wie versprochen, nun einige Alternativen zur Gestaltung des Quellcodes von Funktion `doSomethingWithParameterPack`:
Sollten Sie sich an der lokalen Variablen `i` in Zeile 3 stören, so könnte man
diese auch als &ldquo;*Instanzvariable*&rdquo; der inneren Lambda-Funktion `printElem` hinzufügen:


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

Die Zählvariablen `i` tritt nun in Zeile 3 von *Listing* 2 in Erscheinung.
Die Lambda-Funktion muss nun um das Schlüsselwort `mutable` ergänzt werden,
da nur dann die Zählvariable `i` modifiziert werden darf (Entfernen der `constness` des Aufrufoperators `()`).

Schon mal etwas von einem *IIFE* gehört. Okay, die Abkürzung verraten wir:

Immediately Invoked Functional Expression.

Hierunter versteht man eine  Inline-definition einer Lambda-Funktion mit unmittelbarem Aufruf!

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

In *Listing* 3 werfen wir unseren Augenmerk auf Zeile 10: Das entscheidende Symbol sind hier die
runden Klammern `()` nach der Inline-Definition einer Lambda-Funktion

```cpp
[&] { ++i; printElemToConsole(i, args); }
```

Durch die runden Klammern kommt es zum Aufruf der Lambda-Funktion!

Alle bislang drei vorgestellten Variationen der `doSomethingWithParameterPack`&ndash;Funktion
zeichnen sich dadurch aus, dass sie intern eine Hilfsfunktion verwenden.
Für alle Anhänger des Minimalismus gerne auch eine abschließende Variante,
die ohne Hilfsfunktion auskommt: Ich nehme es aber gleich vorweg:
Diese Realisierung ist am schwersten lesbar. Meiner Vorstellung von guter Software entspricht sie nicht!

```cpp
01: auto doSomethingWithParameterPack4(auto ... args) {
02: 
03:     int i{};
04: 
05:     ([&] { ++i; std::cout << "Element " << i << ": " << args << std::endl; } (), ... );
06: }
```

*Listing* 4: &ldquo;*Folding over a Comma*&rdquo; in minimalistischer Schreibweise.


## Rekursive Parameter Pack Expansion

Das folgende Beispiel ließe sich mit der Technik des Foldings lösen:
Eine Addition beliebig vieler Werte. Zum Beispiel so:

```cpp
auto sum(auto ... args) {
    return (... + args);
}
```

Es schadet aber auch nichts, wenn man C++ Quellcode lesen kann, der sich auf ältere C++ Versionen bezieht.
Damit sind wir bei rekursiven, variadischen Funktionen angekommen:

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

*Listing* XXX: Beispiel einer rekursiven Parameter Pack Expansion.

Beachten Sie in *Listing* XXX zunächst Zeile 7: Der Trick in der Rekursion liegt darin, dass
man das Parameter Pack in einen ersten und alle anderen Parameter zerlegt.
Also hier `first` für den ersten und `args ...` für die restlichen Parameter.
Wir in der gewöhnlichen rekursiven Programmierung müssen wir das Ende der Rekursion separat behandeln.
Dazu muss die Funktion `sum` überladen werden, dies geschieht in den Zeilen 1 bis 4.
Die eigentliche Rekursion findet in Zeile 8 statt: Es wird in Funkion `sum` wiederum `sum` aufgerufen,
allerdings mit einem Parameter weniger.

Das Beispiel aus *Listing* XXX demonstriert generische Funktionen.
Wir hätten es auch mit Funktionstemplates implementieren können:


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

*Listing* XXX: Dasselbe Beispiel in Template Syntax Schreibweise.

Fehlt noch die Schreibweise mit Lambda-Funktionen:

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

*Listing* XXX: Dasselbe Beispiel in Lambda-Funktionsschreibweise.

Vorsicht: Der Quellcode aus *Listing* XXX ist **nicht** übersetzungsfähug.
Es wird suggiert, dass wir es wie in *Listing* XXX mit einer Überladung von zwei Funktionen zu tun haben.

Lambdas sind anonyme Funktoren (d.h. unbenannte Funktionsobjekte bzw. unbenannte aufrufbare Objekte)
und keine einfachen Funktionen.
Daher ist ein Überladen dieser Objekte nicht möglich.

Wenn wir wieder zum C++ 17 Sprachumfang wechseln, können wir den Fehler beseitigen.
Offensichtlich geht eine Reaisierung nur mit einem Funktionsobjekt,
im Rumpf der Aufrufoperators können wir mit `if constexpr` und `sizeof...` eine Fallunterscheidung einbauen:

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

*Listing* XXX: Dasselbe Beispiel in Lambda-Funktionsschreibweise &ndash; dieses Mal korrekt.

---
---

WEITER: Hier kommt das Thema "Lambda-Funktionen und Rekursion"


## Lambda-Funktionen als Parameter für andere Funkionen

## Functional Programming with Nested Lambdas 


Anonyme Funktionen oder Lambdas wurden in C++ 11 als
praktische, leichtgewichtige Syntax zum Erstellen kurzlebiger Funktionen eingeführt.

Was nicht unmittelbar ist: Mit Hilfe von Lambda Funktionen lassen sich nun auch
Konzepte der funktionalen Programmierung in C++ formulieren.

Das bedeutet nicht, dass C++ auf einer Ebene wir Haskell oder F# steht.
Ich stelle zwei Konzepte der funktionalen Programmierung &ndash; das so genannte *Currying* und die
Modellierung von Funktionen höherer Ordnung &ndash; vor.

  
  * *Currying* &ndash; Currying is the transformation of a function with multiple arguments into a sequence of single-argument functions.
    That means converting a function like this f(a, b, c, ...) into a function like this f(a)(b)(c)... .


Currying ist die Transformation einer Funktion mit mehreren Argumenten in eine Folge von Funktionen mit einem Argument.
     Das bedeutet, eine Funktion wie diese f(a, b, c, ...) in eine Funktion wie diese f(a)(b)(c)... umzuwandeln.


  * *Funktionen höherer Ordnung* &ndash; Funktionen höherer Ordnung dienen zur Schachtelung von Funktionen. Als Input (Parameter) von Funktionen werden wiederum Funktionen verwendet

---

### *Currying*  

Wir starten gleich mit einem Beispiel:

```cpp
auto genericIncrementer = [](auto x) {
    return [x](auto y) {
        return x + y;
    };
};
```

Triviel zu erkennen ist, dass `genericIncrementer` ein Lambda Objekt ist.
Nur welchen Rückgabetyp hat `genericIncrementer`?

Hierzu müssen wir schon etwas genauer hinsehen:
Nach der `return`&ndash;Anweisung im Rumpf steht der Ausdruck

```cpp
[x] (auto y) { return x + y; }
```

Das ist wieder ein Lambda Objekt! Dieses ist allerdings nur im Kontext des umgebenden Lambda-Objekts lebensfähig
da es in seiner *Capture Clause* auf den Parameter `x` des umgebenden Aufrufoperators zugreift!
Softwaretechnisch gesehen sind Lambda Objekte vom Typ `std::function<T>`, wobei der Template Parameter `T`
die Schnittstelle des Aufrufoperators beschreibt. Wir gehen gleich hierauf noch näher ein.
Zunächst betrachten wir jetzt die Anweisung

```cpp
auto incrementByTen{ genericIncrementer(10) };
```

`incrementByTen` ist folglich ein Lambda Objekt, das für das innere Lambda Objekt den Wert
in der Capture Clause  bereitstellt (hier: Wert `10`).
Natürlich können wir das Lambda Objekt `incrementByTen` aufrufen:

```cpp
auto result{ incrementByTen(5) };
std::cout << "Result: " << result << std::endl;
```

In der Konsole erhlten wir den Wert `15` als Ergebnis.
Damit sollte das Prinzip des Currings verständlich geworden sein:

&ldquo;Mit dem Prinzip des Currying können wir eine Funktion,
die mehrere Argumente verwendet, in eine Reihe von Funktionen zerlegen,
die jeweils nur ein Argument verwenden.&rdquo;

Moment mal! Wo hatten wir in unseren bisherigen Beispiel den Aufruf mit den &ldquo;vielen&rdquo; Argumenten?
Den reiche ich jetzt nach:

```cpp
auto result{ genericIncrementer(10)(5) };  // ==> result = 15
```

Wir sprachen schon über den Rückgabetyp von `genericIncrementer`.
Der Gebrauch des `auto`&ndash;Schlüsselworts verleitet zu leicht lesbarem Quellcode &ndash;
und sollte von einem versierten C++ Entwickler auch bevorzugt werden!

Ist &ndash; wiederum vor dem Hintergrund einer leicht verständlichen Lesbarkeit des Quellcodes betrachtet &ndash;
der tatsächlich vorliegende Datentyp nicht einfach eruierbar, sollte man auf `auto` verzichten.
Aber entscheiden Sie doch selbst:

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

*Listing* XXX: Lambda-Objekte, durch `std::function<int(int)>`  definiert.



## Functional Programming with Nested Lambdas 

https://stackoverflow.com/questions/36314/what-is-currying

https://sebastianviereck.de/funktionale-programmierung-mit-javascript/


