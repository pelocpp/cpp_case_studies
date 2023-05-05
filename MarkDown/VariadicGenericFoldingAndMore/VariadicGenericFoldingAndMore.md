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

Sicherlich muss man all diese Konzepte erst einmal alleinstehend f�r sich betrachten,
um sie zu erfassen und zu verstehen.

Interessanter wird es, wenn man diese Techniken miteinander verkn�pft!

Genau dies wollen wir an einer Reihe von Beispielen n�her betrachten.
Erst auf diese Weise kann man erkennen, in welche Richtung sich die Stilistik entwickelt.

Im Mittelpunkt der folgenden Beispiele soll der Ansatz stehen, mehrere dieser Techniken miteinander zu verkn�pfen.
Erst auf diese Weise kann man erkennen, welche Pfade die Stilistik eines "Modern C++" Programms einschl�gt.

## Variadische Funktionen und Parameter Packs

Variadische Templates geh�ren zu den m�chtigsten Erweiterungen von C++ ab der Version 11.
Diese Art der Schreibweise von Klassen und Funktionen
kann statt einer vorgegebenen &ndash; und damit festen &ndash; Anzahl 
von Argumenten (Datentypen, Parameter) eine beliebige Menge annehmen.
Dar�berhinaus kann der Datentyp dieser Argumente in einem konkreten Anwendungsfall
dann unterschiedlich sein.
Abgelegt werden die Argumente in einem so genannten *Parameter Pack*.

Eine einfache *variadische Funktion* kann wie folgt definiert werden:

```cpp
auto f(auto ... args) {
    // some code to use args  
}
```

Die Ellipsis (...) nach dem Schl�sselwort `auto` bedeuten, dass `args` ein *Parameter Pack* ist.
Diese Funktion ist korrektes C++ &ndash; das Code-Fragment ist �bersetzungsf�hig &ndash;
und wir k�nnten sie so aufrufen:

```cpp
f(1, 2, 3);
```

oder auch so:

```cpp
f('1', 123, 987.654, std::string{"xyz"}, 10.0F);
```

Okay, zugegeben, der Rumpf der Funktion ist knapp geraten. Wir k�nnen beispielsweise die Anzahl der Parameter
mit dem `sizeof ...`&ndash;Operator bestimmen:


```cpp
auto f(auto ... args) {
    std::cout << sizeof...(args) << std::endl;
}
```

Damit erhalten wir bei der Ausf�hrung von


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

Variadische Funktionen lie�en sich syntaktisch auch anders schreiben:
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
*Folding Ausdr�cken*. Versuchen wir es mal mit einem Beispiel:

```cpp
auto sum(auto ... args) {
    return (... + args);
}
```

Der Folding Ausdruck folgt dem `return`-Schl�sselwort, er muss in runden Klammern stehen.
Die Syntax ist mit Sicherheit gew�hnungsbed�rftig, im vorliegenden Beispiel werden
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

Interessanterweise l�sst sich die variadische Funktion `sum` auch mit Werten
untschiedlichen Typs und auch mit nicht-arithmetischen Werten aufrufen, also zum Beispiel
mit `std::string`&ndash;Objekten. Im Falle von nicht-arithmetischen Datentypen ist es aber
erforderlich, dass die jeweilige Klasse den `+`&ndash;Operator unterst�tzt.
Bei Variablen unterschiedlichen Datentyps wird das Ergebnis nach den �blichen C/C++
Konvertierungsregeln bzgl. des &ldquo;*gr��ten gemeinsamen*&rdquo; Datentyps berechnet.

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
der Wurzel aus der Summe der Betragsquadrate aller Komponenten des Vektors.
Stellen wir die Elemente eines  *n*-dimensionalen Vektors in einem Parameter Pack
zusammen, kann man eine Funktion `norm` so definieren:

```cpp
auto norm(auto ... args) {
    return std::sqrt(((args * args) + ...));    // sqrt(arg1*arg1 + arg2*arg2 + ...)
}
```

Das Folding findet hier �ber dem Produkt der jeweiligen Parameter statt!

*Beispiel*:

```cpp
auto n{ norm(1.0, 2.0, 3.0, 4.0) };
std::cout << "Norm: " << n << std::endl;
```

*Ausgabe*:

```
Norm: 5.47723
```


Folding-Ausdr�cke lassen es auch zu, dass die einzelnen Elemente eines Parameter Packs
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

Mit Hilfe von Folding Ausdr�cken kann man die Elemente eines Parameter Packs verarbeiten.

Manchmal m�chte man aber pro Element eine Verarbeitung ansto�en, die sich nicht nur
auf die Anwendung eines einzelnen Operators beschr�nkt.
Wir sind noch einmal bei der Fragestellung angekommen,
ob es nicht doch irgendwie die M�glichkeit einer Art `for`&ndash;Wiederholungsschleife zum Traversieren 
des Parameter Packs gibt. 

Sagen wir es so: Der Ansatz mit `for` f�hrt nach wie vor nicht zum Ziel,
aber es gibt eine spezielle Art des Foldings, die uns in die N�he des Ziels bringt:
Das &ldquo;*Folding over a Comma*&rdquo;.

Ja, Sie haben es richtig gelesen: Wir wenden das Folding f�r den Komma-Operator `,` an.
Um es wahrheitsgem��er zu sagen: Am Komma-Operator sind wir eigentlich �berhaupt nicht interessiert,
aber mit seiner Hilfe schaffen wir es aber, ein Parameter Pack Element f�r Element auszupacken!

Es ist Zeit f�r ein Beispiel! Ich stelle im Folgenden
eine Funktion `doSomethingWithParameterPack` in mehreren Schreibweisen vor.
Die erste Variation sollte in puncto Lesbarkeit die beste sein:


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
Ja, es mutet ein wenig merkw�rdig an, den Komma-Operator hier vorzufinden.
Aber wenn Sie Zeile 11 genau betrachten, werden Sie erkennen, dass es eigentlich um den Aufruf
der Hilfsfunktion `printElem` geht. Und diese Funktion wird eben auf Grund des
&ldquo;*Abrollens*&rdquo; (so k�nnte man *Folding* ins Deutsche �bersetzen)
der Reihe nach f�r jedes Element des Parameter Packs aufgerufen!

Nebenbei bemerkt: In *Listing* 1 finden wir eine Kombination der C++ Sprachkonstrukte
*Folding*, *Parameter Pack* und generische Lambda-Funktionen vor.

Wie versprochen, nun einige Alternativen zur Gestaltung des Quellcodes von Funktion `doSomethingWithParameterPack`:
Sollten Sie sich in Zeile 3 an der lokalen Variablen `i` st�ren, so k�nnte man
diese auch als &ldquo;*Instanzvariable*&rdquo; der inneren Lambda-Funktion `printElem` definieren:


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

Die Z�hlvariable `i` tritt nun in Zeile 3 von *Listing* 2 in Erscheinung.
Die Lambda-Funktion muss nun um das Schl�sselwort `mutable` erg�nzt werden,
da nur dann die Z�hlvariable `i` modifiziert werden darf (Entfernen der `constness` des Aufrufoperators `()`).

Schon mal etwas von einem *IIFE* geh�rt. Okay, die Abk�rzung verrate �ch Ihnen:
*Immediately Invoked Functional Expression*.
Man versteht hierunter die Inline-Definition einer Lambda-Funktion mit unmittelbarem Aufruf!

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
[&] { ++i; printElemToConsole(i, args); }
```

Durch eben diese runden Klammern kommt es zum Aufruf der Lambda-Funktion!

Alle drei bislang vorgestellten Variationen der `doSomethingWithParameterPack`&ndash;Funktion
zeichnen sich dadurch aus, dass sie intern eine Hilfsfunktion verwenden.
F�r alle Anh�nger des Minimalismus gerne auch eine abschlie�ende Variante ohne
Hilfsfunktion. Ich nehme es aber gleich vorweg:
Diese Realisierung ist am schwersten lesbar. Meiner Vorstellung von gutem Software-Quellcode entspricht sie nicht!

```cpp
01: auto doSomethingWithParameterPack(auto ... args) {
02: 
03:     int i{};
04: 
05:     ([&] { ++i; std::cout << "Element " << i << ": " << args << std::endl; } () , ... );
06: }
```

*Listing* 4: &ldquo;*Folding over a Comma*&rdquo; in minimalistischer Schreibweise.

In *Listing* 4 finden wie die innere Lambda-Funktion als Argument des Folding Ausdrucks vor &ndash; garniert mit
einem unmittelbaren Aufruf (*IIFE*).


## Rekursive Parameter Pack Expansion

Wir kommen wieder auf das Beispiel der Addition beliebig vieler Werte zur�ck.
Mit der Technik des *Foldings* haben wir hierf�r bereits einen L�sungsansatz betrachtet:


```cpp
auto sum(auto ... args) {
    return (... + args);
}
```

Es schadet aber auch nichts, wenn man C++ Quellcode �lterer C++ Versionen lesen kann.
Damit sind wir bei C++ 11 und rekursiven, variadischen Funktionen angekommen:

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

Beachten Sie in *Listing* 5 zun�chst Zeile 7: Der Trick in der Rekursion liegt darin, dass
man das Parameter Pack in einen ersten und alle anderen Parameter zerlegt.
Also hier `first` f�r den ersten und `args ...` f�r die restlichen Parameter.
Wie in der gew�hnlichen rekursiven Programmierung m�ssen wir das Ende der Rekursion separat behandeln.
Dazu muss die Funktion `sum` �berladen werden, dies geschieht in den Zeilen 2 bis 4.
Die eigentliche Rekursion findet in Zeile 8 statt: Es wird in Funktion `sum` wiederum `sum` aufgerufen,
allerdings mit einem Parameter weniger. 

F�r diejenigen Leser, die eine exakte Formulierung bevorzugen: Eigentlich haben wir es in Zeile 8
nicht mit einem rekursiven Funktionsaufruf zu tun, sondern mit dem Aufruf einer �berladung der `sum`-Funktion.
Der Aufruf von `sum` in Zeile 8 erfolgt mit einem Parameter weniger, es handelt sich also streng genommen nicht
um einen rekursiven Aufruf. Ich �berlassen es Ihnen, welche Formulierung Sie bevorzugen wollen.

Das Beispiel aus *Listing* 5 demonstriert ein Beispiel f�r generische Funktionen.
Wir h�tten es auch mit Funktionstemplates realisieren k�nnen:


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

Der Vollst�ndigkeit halber noch die Schreibweise mit Lambda-Funktionen:

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

*Listing* 7: Dasselbe Beispiel in Lambda-Funktionsschreibweise.

Vorsicht: Der Quellcode aus *Listing* 7 ist **nicht** �bersetzungsf�hig.
Es wird suggiert, dass wir es wie in *Listing* 5 oder *Listing* 6
mit einer �berladung von zwei Funktionen zu tun haben.

Lambdas sind anonyme Funktoren (d.h. unbenannte Funktionsobjekte bzw. unbenannte aufrufbare Objekte)
und keine einfachen Funktionen &ndash; wenngleich man h�ufig von Lambda *Funktionen* spricht,
aber auch diese Formulierung ist streng genommen falsch: Lambdas sind Objekte und keine Funktionen.
Daher ist ein �berladen dieser Objekte nicht m�glich.

Wenn wir wieder zum C++ 17 Sprachumfang wechseln, k�nnen wir den Fehler beseitigen.
Offensichtlich geht eine Realisierung nur mit einem Aufrufoperator,
in dessen Rumpf wir mit `if constexpr` und `sizeof...` eine Fallunterscheidung einbauen:

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


// NOCH NICHT SO GUT AB HIER

## Lambda-Funktionen als Parameter f�r andere Funkionen

## Functional Programming with Nested Lambdas 


Anonyme Funktionen oder Lambdas wurden in C++ 11 als
praktische, leichtgewichtige Syntax zum Erstellen kurzlebiger Funktionen eingef�hrt.

Was nicht unmittelbar einleuchtend ist: Mit Hilfe derartiger Lambda Funktionen lassen sich nun auch
Konzepte der *funktionalen Programmierung* in C++ formulieren.

Das bedeutet nicht, dass C++ auf einer Ebene wir zum Beispiel Haskell oder F# steht.
Aber zwei zentrale Konzepte der funktionalen Programmierung &ndash;
das so genannte *Currying* und Funktionen h�herer Ordnung &ndash; k�nnen wir nun auch mit C++ Hilfsmitteln schreiben.
Was verstehen wir hierunter eigentlich:

  * *Currying* &ndash; Beschreibt die Transformation einer Funktion mit mehreren Argumenten in eine Folge von Funktionen mit einem Argument.
     Das bedeutet, dass man den Aufruf einer Funktion *f(a, b, c, ...)* in einen �aufruf *f(a)(b)(c)...* umwandelt.

  * *Funktionen h�herer Ordnung* &ndash; Funktionen h�herer Ordnung dienen zur Schachtelung von Funktionen.
     Als Eingabe-Parameter von Funktionen werden wiederum Funktionen verwendet.

*Bemerkung*: Das viel zitierte *Currying* hat nichts mit Gerichten der asiatischen und japanischen K�che zu tun.
Vielmehr ist der Name auf einen US-amerikanischen Logiker und Mathematiker namens Haskell Brooks Curry zur�ckzuf�hren.

## *Currying*  

Wir starten gleich mit einem Beispiel:

```cpp
01: auto genericIncrementer = [](auto x) {
02:     return [x](auto y) {
03:         return x + y;
04:     };
05: };
```

*Listing* 9: Beispiel f�r *Currying*.


Triviel zu erkennen ist in *Listing* 9, dass `genericIncrementer` ein Lambda Objekt ist.
Nur welchen R�ckgabetyp hat `genericIncrementer`?
Hierzu m�ssen wir schon etwas genauer hinsehen:
Nach der `return`&ndash;Anweisung im Rumpf steht der Ausdruck

```cpp
[x] (auto y) { return x + y; }
```

Das ist wieder ein Lambda Objekt! Dieses ist allerdings nur im Kontext des umgebenden Lambda-Objekts lebensf�hig,
da es in seiner *Capture Clause* auf den Parameter `x` des umgebenden Aufrufoperators zugreift!
Softwaretechnisch gesehen sind Lambdas Objekte vom Typ `std::function<T>`, wobei der Template Parameter `T`
die Schnittstelle des Aufrufoperators beschreibt. Wir gehen hierauf gleich noch n�her ein.
Zun�chst betrachten wir jetzt die Anweisung

```cpp
auto incrementByTen{ genericIncrementer(10) };
```

`incrementByTen` ist folglich ein Lambda Objekt, das f�r das innere Lambda Objekt
in der Capture Clause einen Wert (hier`10`) bereitstellt.

Nat�rlich k�nnen wir das Lambda Objekt `incrementByTen` aufrufen:

```cpp
auto result{ incrementByTen(5) };
std::cout << "Result: " << result << std::endl;
```

In der Konsole erhlten wir den Wert `15` als Ergebnis.
Damit sollte das Prinzip des Currings verst�ndlich geworden sein:
&ldquo;Mit dem Prinzip des Currying k�nnen wir eine Funktion,
die mehrere Argumente verwendet, in eine Reihe von Funktionen zerlegen,
die jeweils nur ein Argument verwenden.&rdquo;

Moment mal! Wo hatten wir in unseren bisherigen Beispiel den Aufruf mit den &ldquo;vielen&rdquo; Argumenten?
Diesen Aufruf sollten wir nachreichen:

```cpp
auto result{ genericIncrementer(10)(5) };  // ==> result = 15
```

Wir sprachen schon �ber den R�ckgabetyp von `genericIncrementer`.
Der Gebrauch des `auto`&ndash;Schl�sselworts verleitet zu leicht lesbarem Quellcode &ndash;
und sollte von einem versierten C++ Entwickler auch bevorzugt werden!

Ist &ndash; wiederum vor dem Hintergrund der leichten Lesbarkeit des Quellcodes betrachtet &ndash;
der tats�chlich vorliegende Datentyp jedoch nicht einfach eruierbar, sollte oder k�nnte man auf `auto` auch verzichten.
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

*Listing* 10: Lambda-Objekte, durch `std::function<int(int)>` definiert.

In *Listing* 10 erkennt man durch schnelles Lesen nun, dass in den Zeilen aufrufbare Objekte (*Callables*) definiert werden
(und damit keine elementaren Variablen).


## Functional Programming with Nested Lambdas 

https://stackoverflow.com/questions/36314/what-is-currying

https://sebastianviereck.de/funktionale-programmierung-mit-javascript/


