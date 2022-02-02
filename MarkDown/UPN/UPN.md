<!-- UPN.md -->

Die Notation eines mathematischen Ausdrucks, wie wir ihn aus der Mathematik kennen, zum
Beispiel 2 * (7 + 5), bezeichnet man als *Infix*-Notation. Das Gegenstück dazu heißt *Postfix*-Notation
oder *UPN* (*umgekehrte polnische Notation*, engl. *reverse polish notation* oder abgekürzt *RPN*). Die
umgekehrte polnische Notation wurde 1920 von dem Polen *Jan Lukasiewicz* erfunden, um
mathematische Ausdrücke ohne Vorrangregeln (Klammern) schreiben zu können.

In dieser Fallstudie behandeln wir einen Taschenrechner für arithmetische Ausdrücke in UPN-Darstellung.

TO BE DONE, Reg Expr.

// TODO:
// Geht das Scanning mit einem Reg Expr ?!?!?!


<!--more-->

# Lernziele - TO BE DONE

  * Container `std::vector<int>`
  * Klasse `std::string_view`
  * Utility-Klassen `std::tuple` und `std::optional`
  * Konstrukt `if constexpr`
  * Einsatz von `std::reverse_iterator`
  * Verschiebesemantik mit `std::move`
  * STL-Algorithmen bzw. -Funktionen `std::for_each`, `std::find_if`, `std::begin`, `std::end`, `std::rbegin`, `std::rend`, `std::isdigit` und `std::remove`

# Einleitung

Wie sieht diese Notation aus? Der zu berechnende Ausdruck wird so umgestellt, daß jeweils jeder
Operator seinem bzw. seinen Operanden folgt. Statt `1 + 2` (gewöhnliche Notation) heißt es in UPN:
`1 2 +`. Auf diese Art werden auch komplexere Ausdrücke geschrieben: `(1 + 2) * 3` wird zu `1 2 + 3 *`, und
`1 + 2 * 3` wird zu `1 2 3 * +`. Man sieht, daß keine Klammern mehr benötigt werden. Die UPN-Notation
wird sogar von einigen Programmiersprachen wie Forth oder Postscript verwendet.

Die Berechnung von Postfix-Ausdrücken ist prinzipiell viel leichter zu programmieren, als dies für
Infix-Terme der Fall ist. Außerdem benötigt die *Postfix*-Notation keine Klammern oder Prioritäten der
Operatoren, da die Reihenfolge der Abarbeitung schon implizit durch den Ausdruck bestimmt wird.
Ein weiterer Vorteil ist die schnellere Abarbeitung im Vergleich zur Infix-Darstellung.

Der einzige Wehrmutstropfen im Gebrauch der *Postfix*-Notation liegt darin, dass diese Schreibweise
recht unüblich ist. Man kann sicherlich keinem Anwender zumuten, dass er alle Eingaben in *Postfix*-Notation macht.
Wir lösen dieses Problem in zwei Schritten:
Zunächst betrachten wir die Berechnung eines arithmetischen Ausdrucks in *Postfix*-Notation.
Im Anschluss daran gehen wir auf die Umwandlung eines arithmetischen Ausdrucks
von der *Infix*-Notation in die *Postfix*-Notation ein.
Auf die Weise kann ein Anwender arithmetische Ausdrücke in der für ihn leichter verständlichen Infix-Schreibweise eingeben,
das Programm legt für die Berechnung die *Postfix*-Notation zu Grunde.

# Klasse `Token`

Arithmetische Ausdrücke in der Postfix-Schreibweise bestehen nur aus Operatoren und Operanden.
Derartige Bestandteile eines arithmetischen Ausdrucks werden in der Informatik auch als `Token`
bezeichnet. Definieren Sie zunächst in Ihrem Programm zur Unterscheidung der unterschiedlichen
Tokenarten wie &ldquo;Operator&rdquo; oder &ldquo;Operand&rdquo; den folgenden Aufzählungstyp `TokenType`:

```cpp
enum class TokenType { Null, Operator, Operand, LBracket, RBracket };
```

Die symbolischen Konstanten `Operator` und `Operand` sind selbsterklärend. Die Konstante
`Null` eignet sich zum Initialisieren von Variablen des `TokenType`-Typs.

TO BE DONE: LBracket, RBracket

Als Operatoren sehen
wir in dieser Betrachtung die vier üblichen binären Operatoren `+`, `-`, `*` und `/` vor. Definieren Sie hierzu
den Aufzählungstyp `OperatorType`:

```cpp
enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp, ModOp };
```

Der `NullOp`-Operator dient wiederum zum Vorbelegen von `OperatorType`-Variablen. Mit diesen
Vorbereitungen definieren wir nun die Klasse `Token` zur Beschreibung eines einzelnen Tokens
innerhalb eines arithmetischen Ausdrucks in der *Postfix*-Notation ([Tabelle 1]):

###### {#tabelle_1_class_token_ctors}

| Element | Beschreibung |
| :---- | :---- |
| Standard-Konstruktor | `Token();`<br/>Der Standardkonstruktor erzeugt ein `Token`-Objekt mit entsprechenden *Null*-Werten. |
| Benutzerdefinierter Konstruktor | `Token(TokenType type);`<br/>Der benutzerdefinierte Konstruktor legt ein Polynom mit den Koeffizienten einer variabel lange Liste von Koeffizienten an. Das erste Element des Arrays ist dem niederwertigsten Koeffizienten zuzuordnen, das letzte dem höchstwertigen. |
| Benutzerdefinierter Konstruktor | `Token(TokenType type, OperatorType op);`<br/>Der benutzerdefinierte Konstruktor legt ein Polynom mit den Koeffizienten einer variabel lange Liste von Koeffizienten an. Das erste Element des Arrays ist dem niederwertigsten Koeffizienten zuzuordnen, das letzte dem höchstwertigen. |
| Benutzerdefinierter Konstruktor | `Token(TokenType type, int value);`<br/>Der benutzerdefinierte Konstruktor legt ein Polynom mit den Koeffizienten einer variabel lange Liste von Koeffizienten an. Das erste Element des Arrays ist dem niederwertigsten Koeffizienten zuzuordnen, das letzte dem höchstwertigen. |
| *getter* `getTokenType()` | `TokenType getTokenType() const;`<br/>Liefert die Art des Tokens zurück &ndash; siehe dazu den Aufzählungstyp `TokenType`. |
| *getter* `getOperatorType()` | `OperatorType getOperatorType() const;`<br/>Liefert für Token von der Art `Operator` den konkreten Operator zurück. Dieser wird durch den Aufzählungstyp `OperatorType` beschrieben. |
| *getter* `getValue()` | `int getValue() const;`<br/>Liefert den numerischen Wert eines Tokens zurück.<br/>*Hinweis*: Diese Eigenschaft besitzt offensichtlich nur dann einen sinnvollen Wert, wenn die Art des Tokens den Wert `Operand` hat. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const Token&);`<br/>Gibt ein `Token`-Objekt auf der Konsole aus. |

*Tabelle* 1: Öffentliche Elemente der Klasse `Token`.

Objekte der Klasse `Token` bestehen im Wesentlichen nur aus einigen wenigen Instanzvariablen, um
die Eigenschaften eines Tokens gemäß [Tabelle 1] zu beschreiben. Das nachfolgende Codefragment
verdeutlicht die Arbeitsweise der `Token`-Klasse:

```cpp
Token tok1{ TokenType::LBracket };
Token tok2{ TokenType::RBracket };
Token tok3{ TokenType::Operator, OperatorType::AddOp };
Token tok4{ TokenType::Operand, 12345 };

std::cout << tok1 << std::endl;
std::cout << tok2 << std::endl;
std::cout << tok3 << std::endl;
std::cout << tok4 << std::endl;
```

*Ausgabe*:

```
(
)
+
12345
```

# Klasse `TokenScanner` &ndash; Zerlegung eines arithmetischen *Postfix*-Ausdrucks

Wir gehen im Folgenden davon aus, dass entweder im Quelltext oder auf der Konsole ein korrekter
arithmetischer Ausdruck in der *Postfix*-Notation eingegeben wird. Die Eingabe besteht also aus einer
Folge von Token, ganz im Sinne der lexikalischen Analyse eines programmiersprachlichen Quelltextes.
Um den Wert des Ausdrucks berechnen zu können, ist die Eingabe in ihre Bestandteile
(*Token*-Objekte) zu zerlegen. Dabei unterstützt uns die nachfolgende Klasse `TokenScanner` wie
folgt ([Tabelle 2]):

###### {#tabelle_2_class_token_scanner}

| Element | Beschreibung |
| :---- | :---- |
| Methode `setLine` | `void setLine(const std::string&);`<br/>Mit `setLine` wird ein korrekter arithmetischer Ausdruck in *Postfix*-Notation an das `TokenScanner`-Objekt übergeben. |
| Methode `scan` | `std::list<Token> scan();`<br/>Eine im Objekt hinterlegte Zeichenkette wird mit der `scan`-Methode von links nach rechts durchlaufen und dabei in ihre `Token`-Bestandteile zerlegt. |
| Operator `<<` | `friend std::ostream& operator<< (std::ostream&, const TokenScanner&);`<br/>Gibt die im *Scanner* hinterlegte Zeichenkette auf der Konsole aus. |

*Tabelle* 2: Öffentliche Elemente der Klasse `TokenScanner`.

Zum Testen Ihrer Realisierung der Klassen `TokenScanner` und `Token` finden Sie in
den nachfolgenden Codefragmenten zwei Anregungen vor. Im ersten Beispiel wird nur ein Postfix-
Ausdruck im Quelltext eingebettet und mit der Line-Eigenschaft an das Scanner-Objekt übertragen.
Eine Zerlegung findet noch nicht statt:

```cpp
Scanner scanner;
scanner.set("1 2 *");
std::cout << scanner << std::endl;
```

*Ausgabe*:

```
Input: 1 2 *
```

Das zweite Beispiel demonstriert die Zerlegung eines arithmetischen Ausdrucks in seine einzelnen
Bestandteile. Die Zerlegung erfolgt in der `scan`-Methode, das Resultat wird in einem
`std::list<Token>`-Objekt zurückgegeben und `Token`- für `Token`-Objekt auf der Konsole ausgegeben:

```cpp
Scanner scanner;
scanner.set("1 2 - 3 -");
std::cout << scanner << std::endl << std::endl;

std::list<Token> tokens = scanner.scan();
for (Token token : tokens)
    std::cout << "Token: " << token << std::endl;
```

*Ausgabe*:

```
Input: 1 2 - 3 -

Token: 1
Token: 2
Token: -
Token: 3
Token: -
```

# Klasse `PostfixCalculator` &ndash; Ein Taschenrechner für *Postfix*-Ausdrücke

Die Realisierung eines Rechners für arithmetische Ausdrücke in *Postfix*-Notation ist sehr einfach,
wenn wir zum Abspeichern von Zwischenergebnissen ein geeignetes Stapelobjekt verwenden. Wir
legen im Folgenden zu Grunde, dass der arithmetische Ausdruck korrekt vorliegt, also nur aus
Operatoren und Operanden besteht. Der Algorithmus zur Berechnung eines *Postfix*-Ausdrucks lautet
nun wie folgt:

  * Wird ein Operand gelesen, so wird er auf den Stapel gelegt.
  * Wird ein Operator gelesen, so holt er sich die Anzahl von Operanden, die er benötigt, vom
    Stapel und führt die Berechnung durch. Das Ergebnis dieser Berechnung wird dann
    seinerseits wieder auf den Stapel gelegt.

Bei Unklarheiten können Sie die Arbeitsweise des *Postfix*-Kalkulators in [Abbildung 1]
nachvollziehen. Ausgangsbasis ist der arithmetische Ausdruck `2 * (4 + 5) / 3`,
seine Postfix-Notation lautet `2 4 5 + * 3 /`:

TODO: Abbildung

Implementieren Sie eine Klasse `PostfixCalculator`, die im Wesentlichen nur eine zentrale
Methode `calc` besitzt:

###### {#tabelle_3_class_token_calculator}

| Element | Beschreibung |
| :---- | :---- |
| Methode `calc` | `int calc(const std::list<Token>&);`<br/>Berechnet den Wert eines arithmetischen Ausdrucks in *Postfix*-Notation. Das Ergebnis ist vom Typ `int`, der Ausdruck wird durch eine Liste von `Token`-Objekten beschrieben. Der Ausdruck muss korrekt vorliegen. <br/>*Hinweis*: Bei der Division dürfen Sie die ganzzahlige Division zu Grunde legen. Auf diese Weise können Sie im Taschenrechner mit Zwischenergebnissen des Typs `int` arbeiten. |

*Tabelle* 3: Öffentliche Elemente der Klasse `PostfixCalculator`.

Unser erstes Beispiel testet ein `PostfixCalculator`-Objekt &ndash; und dies ohne Gebrauch
eines `Scanner`-Objekts. Man sieht an dem Beispiel, dass man das `std::list<Token>`-Objekt
gewissermaßen auch &ldquo;händisch&rdquo; erstellen kann &ndash; wenn man es richtig konstruiert:

*Beispiel*:

```cpp
// postfix: 1 2 - 3 - (infix: 1 - 2 - 3)
Token t1{ TokenType::Operand, 1 };
Token t2{ TokenType::Operand, 2 };
Token t3{ TokenType::Operator, OperatorType::SubOp };
Token t4{ TokenType::Operand, 3 };
Token t5{ TokenType::Operator, OperatorType::SubOp };

std::list<Token> tokens;
tokens.push_back(t1);
tokens.push_back(t2);
tokens.push_back(t3);
tokens.push_back(t4);
tokens.push_back(t5);

// print postfix notation to stdout
std::cout << "Postfix Expression: " << std::endl;
for (Token token : tokens) {
    std::cout << token << ' ';
}
std::cout << std::endl;

// calculate result of postfix expression
PostfixCalculator calculator;
int result = calculator.calc(tokens);
std::cout << "Result: " << result << std::endl;
```

*Ausgabe*:

```
Postfix Expression:
1 2 - 3 -
Result: -4
```

Noch ein zweites Beispiel &ndash; dieses Mal unter Verwendung eines `Scanner`-Objekts:

```cpp
// sum of first ten numbers
Scanner scanner;
scanner.set("0 1 2 3 4 5 6 7 8 9 + + + + + + + + +");

std::list<Token> postfix = scanner.scan();

PostfixCalculator calc;
int result = calc.calc(postfix);
std::cout << "Result: " << result << std::endl;
```

*Ausgabe*:

```
Result: 45
```

Noch ein drittes Beispiel:

```cpp
Token t1 { TokenType::Operand, 2 };
Token t2 { TokenType::Operand, 4 };
Token t3 { TokenType::Operand, 5 };
Token t4 { TokenType::Operator, OperatorType::AddOp };
Token t5 { TokenType::Operator, OperatorType::MulOp };
Token t6 { TokenType::Operand, 3 };
Token t7 { TokenType::Operator, OperatorType::DivOp };

std::list<Token> tokens;
tokens.push_back(t1);
tokens.push_back(t2);
tokens.push_back(t3);
tokens.push_back(t4);
tokens.push_back(t5);
tokens.push_back(t6);
tokens.push_back(t7);

// print postfix notation to stdout
std::cout << "Postfix Expression: " << std::endl;
for (Token token : tokens) {
    std::cout << token << ' ';
}
std::cout << std::endl;

// calculate result of postfix expression
PostfixCalculator calculator;
int result = calculator.calc(tokens);
std::cout << "Result: " << result << std::endl;
```

Ausgabe:

```
Postfix Expression:
2 4 5 + * 3 /
Result: 6
```


# Ein systematischer Test

In der letzten Teilaufgabe haben Sie Ihre Implementierung hoffentlich mit einigen manuell erstellten
Beispielen getestet. Ohne großen Aufwand ist es aber auch möglich, für bestimmte Testszenarien
einen automatisierten Test zu erstellen. Ergänzen Sie zu diesem Zweck die Klasse Program (bzw. die
Klasse, in der Sie Ihre Main-Methode abgelegt haben), um eine Methode CreatePowerOf2PostfixExpression:

```cpp
private static String CreatePowerOf2PostfixExpression (int power);
```

Ein Aufruf von CreatePowerOf2PostfixExpression mit dem Wert 3 liefert die Zeichenkette

```
2 2 2 * *
```

zurück, ein Aufruf mit dem Wert 16 die Zeichenkette

```
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * *
```

Erstellen Sie nun eine Testmethode mit Hilfe der CreatePowerOf2PostfixExpression-Methode,
um die ersten 50 Potenzen zur Basis 2 mit Ihrem Postfix-Taschenrechner zu berechnen. Die Ausgabe
des Testprogramms sieht auf meinem Rechner für die ersten zwanzig Zweierpotenzen so aus:

```
2 ==> 2
2 2 * ==> 4
2 2 2 * * ==> 8
2 2 2 2 * * * ==> 16
2 2 2 2 2 * * * * ==> 32
2 2 2 2 2 2 * * * * * ==> 64
2 2 2 2 2 2 2 * * * * * * ==> 128
2 2 2 2 2 2 2 2 * * * * * * * ==> 256
2 2 2 2 2 2 2 2 2 * * * * * * * * ==> 512
2 2 2 2 2 2 2 2 2 2 * * * * * * * * * ==> 1024
2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * ==> 2048
2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * ==> 4096
2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * ==> 8192
2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * ==> 16384
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * ==> 32768
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * * ==> 65536
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * * * ==> 131072
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * * * * ==> 262144
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * * * * * ==> 524288
```

Mit dem vorliegenden Kalkulator haben Sie einen Rechenautomaten implementiert,
der beliebige arithmetische Ausdrücke auf der Basis der vier Grundrechenarten beherrscht.
Der einzige Nachteil besteht darin, dass die Formulierung des arithmetischen Ausdrucks in der umgekehrt polnischen Notation
für den menschlichen Betrachter doch irgendwie ungewohnt ist. Damit sind wir bei der letzten Teilaufgabe angekommen:

# Klasse `InfixToPostfixConverter` &ndash; *Infix*- nach *Postfix*-Konvertierung

Siehe upn.pdf




// ===========================================================================

TODO: Hmmm, die Methode calc könnte man auch mit einem Template umsetzen.

// ===========================================================================
// ===========================================================================


<br/>

# There&lsquo;s more

Der Einsatz eines `std::array`-Objekts ist für performantes  Chiffrieren und Dechiffrieren nicht die
performanteste Lösung. Überlegen Sie, wie man eine *BiMap*-Klasse implementieren könnte,
um laufzeit-optimalere Ergebnisse zu erzielen.

<br/>


<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_token_ctors
[Tabelle 2]: #tabelle_2_class_token_scanner
[Tabelle 3]: #tabelle_3_class_token_calculator





[Listing 1]: #listing_01_number_interface
[Listing 2]: #listing_02_number_implementation
[Listing 3]: #listing_03_palindromcalculator_interface
[Listing 4]: #listing_04_palindromcalculator_implementation

[Abbildung 1]:  #abbildung_1_schriftlichen_addition_01

<!-- End-of-File -->
