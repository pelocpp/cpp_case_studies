<!-- UPN.md -->

Die Notation eines mathematischen Ausdrucks, wie wir ihn aus der Mathematik kennen, zum
Beispiel 2 * (7 + 5), bezeichnet man als *Infix*-Notation. Das Gegenstück dazu heißt *Postfix*-Notation
oder *UPN* (*umgekehrte polnische Notation*, engl. *reverse polish notation* oder abgekürzt *RPN*). Die
umgekehrte polnische Notation wurde 1920 von dem Polen *Jan Lukasiewicz* erfunden, um
mathematische Ausdrücke ohne Vorrangregeln (Klammern) schreiben zu können.

In dieser Fallstudie behandeln wir einen Taschenrechner für arithmetische Ausdrücke in UPN-Darstellung.
Reguläre Ausdrücke (`std::sregex_iterator`, `smatch`) und *Type Traits* (`std::is_integral`, `std::is_floating_point`)
fließen neben anderen Modern C++&ndash;Sprachmitteln in der Implementierung mit ein.

<!--more-->

# Lernziele

  * Container `std::stack<>`, `std::list<>`, `std::vector<>`
  * Verkettung von Konstruktoren
  * Datentyp `class enum`
  * &bdquo;Range-Based&bdquo; `for`-Wiederholungsschleife
  * Reguläre Ausdrücke (`std::sregex_iterator`, `smatch`)
  * Iteratoren Konzept
  * Type Traits (`std::is_integral<T>`, `std::is_floating_point<T>`)
  * STL-Algorithmen bzw. -Funktionen `std::for_each`, `std::reverse`, `std::begin`, `std::end`, `std::prev`, `std::rbegin`, `std::rend`, `std::isdigit`

# Einleitung

Wie sieht diese Notation aus? Der zu berechnende Ausdruck wird so umgestellt, daß jeweils jeder
Operator seinem bzw. seinen Operanden folgt. Statt `1 + 2` (gewöhnliche Notation) heißt es in UPN:
`1 2 +`. Auf diese Art werden auch komplexere Ausdrücke geschrieben: `(1 + 2) * 3` wird zu `1 2 + 3 *`, und
`1 + 2 * 3` wird zu `1 2 3 * +`. Man sieht, daß keine Klammern mehr benötigt werden. Die UPN-Notation
wird sogar von einigen Programmiersprachen wie Forth oder Postscript verwendet.

Die Berechnung von *Postfix*-Ausdrücken ist prinzipiell viel leichter zu programmieren, als dies für
*Infix*-Terme der Fall ist. Außerdem benötigt die *Postfix*-Notation keine Klammern oder Prioritäten der
Operatoren, da die Reihenfolge der Abarbeitung schon implizit durch den Ausdruck bestimmt wird.
Ein weiterer Vorteil ist die schnellere Abarbeitung im Vergleich zur *Infix*-Darstellung.

Der einzige Wehrmutstropfen im Gebrauch der *Postfix*-Notation liegt darin, dass diese Schreibweise
recht unüblich ist. Man kann sicherlich keinem Anwender zumuten, dass er alle Eingaben in *Postfix*-Notation tätigt.
Wir lösen dieses Problem in zwei Schritten:
Zunächst betrachten wir die Berechnung eines arithmetischen Ausdrucks in *Postfix*-Notation.
Im Anschluss daran gehen wir auf die Umwandlung eines arithmetischen Ausdrucks
von der *Infix*-Notation in die *Postfix*-Notation ein.
Auf die Weise kann ein Anwender arithmetische Ausdrücke in der für ihn leichter verständlichen *Infix*-Schreibweise eingeben,
das Programm legt für die Berechnung die *Postfix*-Notation zu Grunde.

# Klasse `Token`

Arithmetische Ausdrücke in der Postfix-Schreibweise bestehen nur aus Operatoren und Operanden.
Derartige Bestandteile eines arithmetischen Ausdrucks werden in der Informatik auch als *Token*
bezeichnet. Definieren Sie zunächst in Ihrem Programm zur Unterscheidung der unterschiedlichen
Tokenarten wie &bdquo;Operator&rdquo; oder &bdquo;Operand&rdquo; den folgenden Aufzählungstyp `TokenType`:

```cpp
enum class TokenType { Null, Operator, Operand, LBracket, RBracket };
```

Die symbolischen Konstanten `Operator` und `Operand` sind selbsterklärend.
Die zwei Konstanten `LBracket` und `RBracket` benötigen wir bei der Umwandlung von der *Infix*- in die *Postfix*-Darstellung.
Die Konstante `Null` eignet sich zum Initialisieren von Variablen des `TokenType`-Typs.

Als Operatoren sehen wir in dieser Betrachtung die fünf üblichen binären Operatoren `+`, `-`, `*`, `/` und `%` vor.
Definieren Sie hierzu den Aufzählungstyp `OperatorType`:

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
| Benutzerdefinierter Konstruktor | `Token(TokenType type);`<br/>Der benutzerdefinierte Konstruktor legt ein `Token`-Objekt vom Typ `type` an. |
| Benutzerdefinierter Konstruktor | `Token(OperatorType op);`<br/>Der benutzerdefinierte Konstruktor legt ein `Token`-Objekt vom Typ `TokenType::Operator` an, `op` spezifiziert den Operator. |
| Benutzerdefinierter Konstruktor | `Token(int value);`<br/>Der benutzerdefinierte Konstruktor legt ein `Token`-Objekt vom Typ `TokenType::Operand` an, `value` beschreibt den Wert. |
| *getter* `getTokenType()` | `TokenType getTokenType() const;`<br/>Liefert die Art des Tokens zurück &ndash; siehe dazu den Aufzählungstyp `TokenType`. |
| *getter* `getOperatorType()` | `OperatorType getOperatorType() const;`<br/>Liefert für Token von der Art `Operator` den konkreten Operator zurück. Dieser wird durch den Aufzählungstyp `OperatorType` beschrieben. |
| *getter* `getValue()` | `int getValue() const;`<br/>Liefert den numerischen Wert eines Tokens zurück.<br/>*Hinweis*: Diese Eigenschaft besitzt offensichtlich nur dann einen sinnvollen Wert, wenn die Art des Tokens den Wert `Operand` hat. |
| *getter* `getPrecedence()` | `size_t getPrecedence() const;`<br/>Liefert den Vorrang eines Operators zurück.<br/>*Hinweis*: Diese Eigenschaft besitzt nur bei der Umwandlung eines arithmetischen Ausdrucks von der *Infix*- in die *Postfix*-Notation eine Rolle. |
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

<pre>
(
)
+
12345
</pre>

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
| Methode `set` | `void set(const std::string&);`<br/>Mit `set` wird ein korrekter arithmetischer Ausdruck in *Postfix*-Notation an das `TokenScanner`-Objekt übergeben. |
| Methode `get` | `const std::string& get() const;`<br/>`get` liefert die im `TokenScanner`-Objekt abgelegte Zeichenkette zurück. |
| Methode `scan` | `void scan();`<br/>Eine im Objekt hinterlegte Zeichenkette wird mit der `scan`-Methode von links nach rechts durchlaufen und dabei in ihre `Token`-Bestandteile zerlegt. |
| Methode `begin` | `iterator begin();`<br/>Das Resultat eines `scan`-Aufrufs kann durch eine Iteration über `Token`-Objekte abgerufen werden. `begin()` beschreibt den Anfang der Iteration. |
| Methode `end` | `end begin();`<br/>Das Resultat eines `scan`-Aufrufs kann durch eine Iteration über `Token`-Objekte abgerufen werden. `end()` beschreibt das Ende der Iteration. |

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

<pre>
Input: 1 2 *
</pre>

Das zweite Beispiel demonstriert die Zerlegung eines arithmetischen Ausdrucks in seine einzelnen
Bestandteile. Die Zerlegung erfolgt in der `scan`-Methode, das Resultat wird
durch eine &bdquo;Range-Based&bdquo; `for`-Wiederholungsschleife ausgegeben:

```cpp
Scanner<int> scanner;
scanner.set("1 2 - 3 -");
scanner.scan();
for (const auto& token : scanner) {
    std::cout << "Token: " << token << std::endl;
}
```

*Ausgabe*:

<pre>
Input: 1 2 - 3 -

Token: 1
Token: 2
Token: -
Token: 3
Token: -
</pre>

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

###### {#abbildung_1_upn_postfix_calculator}

{{< figure src="/img/upn_calculator/upn_postfix_calculator_01.svg" width="90%" >}}

*Abbildung* 1: Arbeitsweise des Postfix-Kalkulators an einem Beispiel betrachtet.

Implementieren Sie eine Klasse `PostfixCalculator`, die im Wesentlichen nur eine zentrale
Methode `calc` besitzt ([Tabelle 3]):

###### {#tabelle_3_class_token_calculator}

| Element | Beschreibung |
| :---- | :---- |
| Methode `calc` | `int calc(std::list<Token>::iterator begin, std::list<Token>::iterator end);`<br/>Berechnet den Wert eines arithmetischen Ausdrucks in *Postfix*-Notation. Das Ergebnis ist vom Typ `int`, der Ausdruck wird durch zwei `std::list<Token>::iterator`-Iteratorenobjekte beschrieben. Der Ausdruck muss korrekt vorliegen. |

*Tabelle* 3: Öffentliches Element der Klasse `PostfixCalculator`.

Unser erstes Beispiel testet ein `PostfixCalculator`-Objekt &ndash; und dies, nebenbei bemerkt &ndash; ohne Gebrauch
eines `Scanner`-Objekts. Man sieht an dem Beispiel, dass man das `std::list<Token>`-Objekt
gewissermaßen auch &bdquo;händisch&rdquo; erstellen kann &ndash; wenn man es richtig konstruiert:

*Beispiel*:

```cpp
// postfix: 1 2 - 3 - (infix: 1 - 2 - 3)
Token<long long> t1{ 1 };
Token<long long> t2{ 2 };
Token<long long> t3{ OperatorType::SubOp };
Token<long long> t4{ 3 };
Token<long long> t5{ OperatorType::SubOp };

std::list<Token<long long>> tokens;
tokens.push_back(t1);
tokens.push_back(t2);
tokens.push_back(t3);
tokens.push_back(t4);
tokens.push_back(t5);

// print postfix notation to stdout
std::cout << "Postfix Expression: " << std::endl;
for (const auto& token : tokens) {
    std::cout << token << ' ';
}
std::cout << std::endl;

// calculate result of postfix expression
PostfixCalculator<long long> calculator;
auto result = calculator.calc(std::begin(tokens), std::end(tokens));
std::cout << "Result: " << result << std::endl;
```

*Ausgabe*:

<pre>
Postfix Expression:
1 2 - 3 -
Result: -4
</pre>

Noch ein zweites Beispiel &ndash; dieses Mal unter Verwendung eines `Scanner`-Objekts:

```cpp
// sum of first ten numbers
Scanner<int> scanner;
scanner.set("0 1 2 3 4 5 6 7 8 9 + + + + + + + + +");
scanner.scan_classic();

PostfixCalculator<int> calculator;
int result = calculator.calc(scanner.begin(), scanner.end());
std::cout << "Result: " << result << std::endl;
```

*Ausgabe*:

<pre>
Result: 45
</pre>

# Ein systematischer Test

In der letzten Teilaufgabe haben Sie Ihre Implementierung hoffentlich mit einigen manuell erstellten
Beispielen getestet. Ohne großen Aufwand ist es aber auch möglich, für bestimmte Testszenarien
einen Test zu automatisieren. Ergänzen Sie zu diesem Zweck Ihr Programm
um eine Testmethode `createPowerOf2PostfixExpression`:

```cpp
constexpr size_t MaxPower = 16;

for (size_t n{1}; n != MaxPower; ++n) {

    // construct scan string for powers of '2'
    std::string s{};
    for (size_t i{}; i != n; ++i) {
        s.append("2 ");
    }
    for (size_t i{}; i != n - 1; ++i) {
        s.append("* ");
    }

    // compute value
    Scanner<int> scanner;
    scanner.set(s);
    scanner.scan();

    PostfixCalculator<int> calculator;
    int result = calculator.calc(scanner.begin(), scanner.end());
    std::cout << scanner.get() << " ==> " << result << std::endl;
}
```

Je nach Potenz wird eine Zeichenkette mit vielen Operanden (`2`) und Operatoren (`*`) gebildet,
zum Beispiel

<pre>
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * * *
</pre>

bei 16 Operanden. Die Ausgabe
des Testprogramms sieht dann für die ersten fünfzehn Zweierpotenzen so aus:

<pre>
2  ==> 2
2 2 *  ==> 4
2 2 2 * *  ==> 8
2 2 2 2 * * *  ==> 16
2 2 2 2 2 * * * *  ==> 32
2 2 2 2 2 2 * * * * *  ==> 64
2 2 2 2 2 2 2 * * * * * *  ==> 128
2 2 2 2 2 2 2 2 * * * * * * *  ==> 256
2 2 2 2 2 2 2 2 2 * * * * * * * *  ==> 512
2 2 2 2 2 2 2 2 2 2 * * * * * * * * *  ==> 1024
2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * *  ==> 2048
2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * *  ==> 4096
2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * *  ==> 8192
2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * *  ==> 16384
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 * * * * * * * * * * * * * *  ==> 32768
</pre>

Mit dem vorliegenden Kalkulator haben Sie einen Rechenautomaten implementiert,
der beliebige arithmetische Ausdrücke auf der Basis der vier Grundrechenarten beherrscht.
Der einzige Nachteil besteht darin, dass die Formulierung des arithmetischen Ausdrucks in der umgekehrt polnischen Notation
für den menschlichen Betrachter doch irgendwie ungewohnt ist. Damit sind wir bei der letzten Teilaufgabe angekommen:

# Klasse `InfixToPostfixConverter` &ndash; *Infix*- nach *Postfix*-Konvertierung

Wir gehen zum Abschluss auf einen Konverter für arithmetische Ausdrücke ein,
der diese von der *Infix*- in die *Postfix*-Notation umwandelt. Damit kommen wir aus dem Dilemma heraus,
dass die Betrachtung eines arithmetischen Ausdrucks in der *Postfix*-Notation doch etwas ungewohnt ist.
Arithmetische Ausdrücke in der *Infix*-Notation können neben den Operatoren
und ihren Operanden auch noch runde Klammern besitzen:

<pre>
7 + 7 * 7
3 * (5 + ((2 * 3) - 4))
((28 + 2) * (2 / 4))
</pre>

Mit den runden Klammern lassen sich die standardmäßig vorherrschenden Vorrangregeln (&bdquo;Punkt-vor-Strich&bdquo;) abändern.
Ein Operator mit einem höheren Vorrang wird einem Operator mit einem niedrigeren Vorrang in der Ausführung vorgezogen,
siehe [Abbildung 2]. Da wir in dieser Studie nur die fünf Operatoren `+`, `-`, `*`, `/` und `%`
zulassen, können wir den Aspekt des *Operatorenvorrangs* simpel auch als &bdquo;Punkt-vor-Strich&bdquo;-Regel titulieren.

###### {#abbildung_2_upn_operator_precedence}

{{< figure src="/img/upn_calculator/upn_postfix_calculator_02.svg" width="45%" >}}

*Abbildung* 2: Rangfolge von arithmetischen Operatoren.

Wir kommen nun auf den Algorithmus für die Konvertierung des arithmetischen Ausdruck
von der *Infix*- in die *Postfix*-Notation zu sprechen.
Für die Konvertierung kommen drei Datencontainer zum Einsatz:

  * Klasse `std::list<Token>` &ndash; Eingabeliste, die alle Operatoren, Operanden und runden Klammern eines arithmetischen Ausdrucks in *Infix*-Notation enthält.
  * Klasse `std::list<Token>` &ndash; Ausgabeliste, die das Ergebnis der Umwandlung (Ausdruck in *Postfix*-Notation) aufnimmt.
  * Klasse `std::stack<Token>` &ndash; Während der Konvertierung benötigen wir für die temporäre Ablage von Eingabe-Elementen einen Stapel.
    Dieser nimmt temporär während des Konvertierens Operatoren und Klammern auf.

Wir sind bei der Beschreibung des Algorithmus angekommen.
Die Liste der einzelnen `Token`-Objekte (Parameter `infix`) ist Objekt für Objekt
zu traversieren, es lassen sich dabei fünf Fälle unterscheiden:

  * Nächstes Element ist ein Operand (Zahl) &rarr; Zahl in *Postfix*-Liste einfügen.
  * Nächstes Element ist eine öffnende Klammer `(` &rarr; Klammer auf den temporären Stapel schieben.
  * Nächstes Element ist ein Operator &rarr; Zuerst sind vom Stapel alle Operatoren mit gleicher oder höherer Priorität in die *Postfix*-Liste zu schieben,
    bis eine öffnende Klammer `(` erreicht wird oder der Stapel leer ist
    oder eben ein Operator niedriger Priorität erreicht wurde.
    Abschließend wird der gefundene Operator auf den temporären Stapel geschoben.
  * Nächstes Element ist eine schließende Klammer `)` &rarr; Alle Operatoren vom Stapel sind bis zur ersten öffnenden Klammer <quote>(</quote> vom Stapel
    zu entfernen und in die *Postfix*-Liste zu schieben.
    Die öffnende Klammer auf dem Stapel sowie die schließende Klammer
    von der Eingabe sind zu verwerfen (sie werden nicht in die *Postfix*-Liste kopiert).
  * Die Eingabe ist leer &rarr; Es werden alle Operatoren, die sich noch auf dem temporären Stapel befinden,
    in die *Postfix*-Liste geschoben.

Sollten Sie Probleme haben, den Algorithmus genau zu erfassen, gehen Sie am besten das folgende Beispiel
Zeile für Zeile in der Testausgabe durch. Es wird der arithmetische Ausdruck `(3 + 7) / (4 - 2)` konvertiert:

<pre>
(    [(]                 []
3    [(]                 [3]
+    [(, +]              [3]
7    [(, +]              [3, 7]
)    []                  [3, 7, +]
/    [/]                 [3, 7, +]
(    [/, (]              [3, 7, +]
4    [/, (]              [3, 7, +, 4]
-    [/, (, -]           [3, 7, +, 4]
2    [/, (, -]           [3, 7, +, 4, 2]
)    [/]                 [3, 7, +, 4, 2, -]
     []                  [3, 7, +, 4, 2, -, /]
</pre>

Implementieren Sie eine Klasse `InfixToPostfixConverter` mit der in
[Tabelle 4] spezifizierten Methode `convert`:

###### {#tabelle_4_class_infix_to_postfix}

| Element | Beschreibung |
| :---- | :---- |
| Methode `convert` | `std::list<Token> convert(`<br/>`std::list<Token>::iterator begin, `<br/>`std::list<Token>::iterator end`<br/>`);`<br/>Konvertiert einen arithmetischen Ausdruck von der *Infix*-Notation (zwei Iteratoren `begin` und `end` zu einem `std::list<Token>`-Objekt) in die *Postfix*-Notation (Rückgabewert). |

*Tabelle* 4: Öffentliches Element der Klasse `InfixToPostfixConverter`.

*Hinweis*: Die Eingabeliste für Methode  `convert` (arithmetischer Ausdruck in *Infix*-Notation) wird
durch zwei Iteratoren-Objekte (Typ `std::list<Token>::iterator`) beschrieben.
Zum Testen Ihrer Realisierung betrachten wir jetzt ein Beispiel eines komplexeren `Infix`-Ausdrucks:

<pre>
2 * 3 / (2 - 1) + 5 * (4 - 1)
</pre>

Das erfolgreiche Zusammenspiel aller Klassen können Sie am folgenden Codefragment überprüfen:

```cpp
Scanner<int> scanner;
scanner.set("2 * 3 / (2 - 1) + 5 * (4 - 1)");
scanner.scan();

// print postfix notation to stdout
std::cout << "Infix Expression:   ";
for (const Token<int>& token : scanner) {
    std::cout << token << ' ';
}
std::cout << std::endl << std::endl;

InfixToPostfixConverter<int> conv;
std::list<Token<int>> postfix = conv.convert(std::begin(scanner), std::end(scanner));

// print postfix notation to stdout
std::cout << "Postfix Expression: ";
for (const Token<int>& token : postfix) {
    std::cout << token << ' ';
}
std::cout << std::endl;

PostfixCalculator<int> calculator;
int result = calculator.calc(std::begin(postfix), std::end(postfix));
std::cout << "Result: " << result << std::endl;
```

*Ausgabe*:

<pre>
Infix Expression:  2 * 3 / ( 2 - 1 ) + 5 * ( 4 - 1 )
Postfix Expression: 2 3 * 2 1 - / 5 4 1 - * +
Result: 21
</pre>

Die Zwischenschritte auf den beteiligten Container-Objekte sehen dieses Mal so aus:

<pre>
2    []                  [2]
*    [*]                 [2]
3    [*]                 [2, 3]
/    [/]                 [2, 3, *]
(    [/, (]              [2, 3, *]
2    [/, (]              [2, 3, *, 2]
-    [/, (, -]           [2, 3, *, 2]
1    [/, (, -]           [2, 3, *, 2, 1]
)    [/]                 [2, 3, *, 2, 1, -]
+    [+]                 [2, 3, *, 2, 1, -, /]
5    [+]                 [2, 3, *, 2, 1, -, /, 5]
*    [+, *]              [2, 3, *, 2, 1, -, /, 5]
(    [+, *, (]           [2, 3, *, 2, 1, -, /, 5]
4    [+, *, (]           [2, 3, *, 2, 1, -, /, 5, 4]
-    [+, *, (, -]        [2, 3, *, 2, 1, -, /, 5, 4]
1    [+, *, (, -]        [2, 3, *, 2, 1, -, /, 5, 4, 1]
)    [+, *]              [2, 3, *, 2, 1, -, /, 5, 4, 1, -]
     []                  [2, 3, *, 2, 1, -, /, 5, 4, 1, -, *, +]
</pre>


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Da mit Ausnahme des Hauptprogramms alle Klassen in der Lösung als Klassentemplates realisiert wurden,
fällt die Unterscheidung in Header- und Realisierungsdatei weg &ndash; zumindest in dem von mir gewählten Ansatz.

Es folgen in unmittelbarer Reihenfolge die Implementierungen
der Klassen `Token`,  `Scanner`,  `PostfixCalculator` und  `InfixToPostfixConverter`,
in [Listing 1] wenden wir uns Klasse `Token` zu:

###### {#listing_1_class_token}

```cpp
001: enum class TokenType { Null, Operator, Operand, LBracket, RBracket };
002: 
003: enum class OperatorType { NullOp, AddOp, SubOp, MulOp, DivOp, ModOp };
004: 
005: template <typename T>
006: class Token;
007: 
008: template <typename T>
009: std::ostream& operator<< (std::ostream&, const Token<T>&);
010: 
011: template <typename T>
012: class Token
013: {
014:     friend std::ostream& operator<< <> (std::ostream&, const Token<T>&);
015: 
016: private:
017:     // member data
018:     TokenType m_type;      // classification of token
019:     OperatorType m_op;     // classification of operator (TokenType == Operator)
020:     T m_value;             // value of constant (TokenType == Constant)
021:     size_t m_precedence;   // precedence of this operator, if any 
022: 
023: public:
024:     // c'tor(s)
025:     Token() : Token(TokenType::Null, OperatorType::NullOp, T{}) {}
026:     Token(TokenType type) : Token(type, OperatorType::NullOp, T{}) {}
027:     Token(OperatorType op) : Token(TokenType::Operator, op, T{}) {}
028:     Token(T value) : Token(TokenType::Operand, OperatorType::NullOp, value) {}
029: 
030:     // getter
031:     TokenType getTokenType() const { return m_type; }
032:     OperatorType getOperatorType() const { return m_op; }
033:     T getValue() const { return m_value; }
034:     size_t getPrecedence() const { return m_precedence; }
035: 
036: private:
037:     // general purpose c'tor
038:     Token(TokenType type, OperatorType op, T value) 
039:         : m_type{ type }, m_op{ op }, m_value{ value } 
040:     {
041:         switch (op)
042:         {
043:         case OperatorType::AddOp:
044:         case OperatorType::SubOp:
045:             m_precedence = 1;
046:             break;
047:         case OperatorType::MulOp:
048:         case OperatorType::DivOp:
049:         case OperatorType::ModOp:
050:             m_precedence = 2;
051:             break;
052:         default:
053:             m_precedence = 0;
054:         }
055:     }
056: };
057: 
058: template <typename T>
059: std::ostream& operator<< (std::ostream& os, const Token<T>& tok)
060: {
061:     switch (tok.m_type)
062:     {
063:     case TokenType::Operand:
064:         os << tok.m_value;
065:         break;
066: 
067:     case TokenType::Operator:
068:         switch (tok.m_op)
069:         {
070:         case OperatorType::AddOp:
071:             os << '+';
072:             break;
073:         case OperatorType::SubOp:
074:             os << '-';
075:             break;
076:         case OperatorType::MulOp:
077:             os << '*';
078:             break;
079:         case OperatorType::DivOp:
080:             os << '/';
081:             break;
082:         case OperatorType::ModOp:
083:             os << '%';
084:             break;
085:         case OperatorType::NullOp:
086:             break;
087:         }
088:         break;
089: 
090:     case TokenType::LBracket:
091:         os << '(';
092:         break;
093: 
094:     case TokenType::RBracket:
095:         os << ')';
096:         break;
097: 
098:     default:
099:         os << ' ';  // suited for debugging output
100:         break;
101:     }
102: 
103:     return os;
104: }
```

*Listing* 1: Klassentemplate `Token<T>`

Ein Hinweis zu [Listing 1] und hier zu den Zeilen 5, 6, 8, 9 sowie 14 und 58 bis 104:
Es ist nicht ganz trival, den `operator<<` in einem Klassentemplate zu implementieren.
Der `<<`-Operator kann auf Grund seines ersten Parameters vom Typ `ostream&` nicht in der Klasse definiert werden.
Aus diesem Grund sind einige Tricks anzuwenden, die es dennoch ermöglichen, für alle Templateinstanziierungen von `Token<T>`
auch eine Überladung des dazugehörigen Operators `<<` zu haben.

Damit sind wir auch schon bei der nächsten Klasse `Scanner` in [Listing 2] angekommen:

###### {#listing_2_class_scanner}

```cpp
001: template <typename T>
002: class Scanner
003: {
004: private:
005:     const std::string token_regex = "([0]|[1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/|\\%";
006: 
007: public:
008:     using iterator = std::list<Token<T>>::iterator;
009:     using const_iterator = std::list<Token<T>>::const_iterator;
010: 
011: private:
012:     std::string         m_line;
013:     std::list<Token<T>> m_tokens;
014:     std::regex          m_token_regex;
015: 
016: public:
017:     // c'tor
018:     Scanner() : m_line{}, m_token_regex{ token_regex } {}
019:      
020:     // getter/setter
021:     void set(const std::string& line) { m_line = line; }
022:     const std::string& get() const { return m_line; }
023: 
024:     // iterator support
025:     iterator begin() { return m_tokens.begin(); }
026:     iterator end() { return m_tokens.end(); }
027:     const_iterator begin() const { return m_tokens.cbegin(); }
028:     const_iterator end() const { return m_tokens.cend(); }
029: 
030:     // public interface
031:     void scan()
032:     {
033:         m_tokens.clear();
034: 
035:         auto rbegin = std::sregex_iterator(
036:             std::begin(m_line),
037:             std::end(m_line),
038:             m_token_regex
039:         );
040: 
041:         auto rend = std::sregex_iterator();
042: 
043:         while (rbegin != rend)
044:         {
045:             std::smatch m = *rbegin;
046:             std::string token = m.str();
047: 
048:             Token<T> tok{};
049:             switch (token[0])
050:             {
051:             case '(':
052:                 tok = Token<T>{ TokenType::LBracket };
053:                 m_tokens.push_back(tok);
054:                 break;
055: 
056:             case ')':
057:                 tok = Token<T>{ TokenType::RBracket };
058:                 m_tokens.push_back(tok);
059:                 break;
060: 
061:             case '+':
062:                 tok = Token<T>{ OperatorType::AddOp };
063:                 m_tokens.push_back(tok);
064:                 break;
065: 
066:             case '-':
067:                 tok = Token<T>{ OperatorType::SubOp };
068:                 m_tokens.push_back(tok);
069:                 break;
070: 
071:             case '*':
072:                 tok = Token<T>{ OperatorType::MulOp };
073:                 m_tokens.push_back(tok);
074:                 break;
075: 
076:             case '/':
077:                 tok = Token<T>{ OperatorType::DivOp };
078:                 m_tokens.push_back(tok);
079:                 break;
080: 
081:             case '%':
082:                 tok = Token<T>{ OperatorType::ModOp };
083:                 m_tokens.push_back(tok);
084:                 break;
085: 
086:             case '0':
087:             case '1':
088:             case '2':
089:             case '3':
090:             case '4':
091:             case '5':
092:             case '6':
093:             case '7':
094:             case '8':
095:             case '9':
096:             {
097:                 long long tmp{ stoll(token) };
098:                 T value{ static_cast<T>(tmp) };
099:                 tok = Token<T>{ value };
100:                 m_tokens.push_back(tok);
101:                 break;
102:             }
103:             default:
104:                 m_tokens.push_back(tok);
105:                 break;
106:             }
107: 
108:             ++rbegin;
109:         }
110:     }
111: 
112:     void scan_classic() 
113:     {
114:         m_tokens.clear();
115: 
116:         for (size_t i{}; i != m_line.size(); ++i)
117:         {
118:             char ch{ m_line[i] };
119:             Token<T> tok{};
120: 
121:             switch (ch)
122:             {
123:             case ' ':
124:                 continue;
125: 
126:             case '(':
127:                 tok = Token<T>{ TokenType::LBracket };
128:                 m_tokens.push_back(tok);
129:                 break;
130: 
131:             case ')':
132:                 tok = Token<T>{ TokenType::RBracket };
133:                 m_tokens.push_back(tok);
134:                 break;
135: 
136:             case '+':
137:                 tok = Token<T>{ OperatorType::AddOp };
138:                 m_tokens.push_back(tok);
139:                 break;
140: 
141:             case '-':
142:                 tok = Token<T>{ OperatorType::SubOp };
143:                 m_tokens.push_back(tok);
144:                 break;
145: 
146:             case '*':
147:                 tok = Token<T>{ OperatorType::MulOp };
148:                 m_tokens.push_back(tok);
149:                 break;
150: 
151:             case '/':
152:                 tok = Token<T>{ OperatorType::DivOp };
153:                 m_tokens.push_back(tok);
154:                 break;
155: 
156:             case '%':
157:                 tok = Token<T>{ OperatorType::ModOp };
158:                 m_tokens.push_back(tok);
159:                 break;
160: 
161:             case '0':
162:             case '1':
163:             case '2':
164:             case '3':
165:             case '4':
166:             case '5':
167:             case '6':
168:             case '7':
169:             case '8':
170:             case '9':
171:             { 
172:                 T value{};
173:                 while (i != m_line.size() && std::isdigit(m_line[i]))
174:                 {
175:                     value = 10 * value + (m_line[i] - '0');
176:                     ++i;
177:                 }
178: 
179:                 // adjust index
180:                 i--;
181: 
182:                 tok = Token<T>{ value };
183:                 m_tokens.push_back(tok);
184:                 break;
185:             }
186: 
187:             default:
188:                 m_tokens.push_back(tok);
189:             }
190:         }
191:     }
192: };
```

*Listing* 2: Klassentemplate `Scanner<T>`

Zum Parsen einer Zeichenkette mit einem arithmetischen Ausdruck in *Postfix*-Notation 
finden Sie in [Listing 2] gleich zwei Lösungsansätze vor:

  * Klassisches Zerlegen einer Zeichenkette in Manier eines Scanners für höhere Programmiersprachen.
  * Zerlegen der Zeichenkette durch einen regulären Ausdruck.

Auf den regulären Ausdruck gehen wir kurz ein:

<pre>
([0]|[1-9][0-9]*)|[(]|[)]|\\+|\\-|\\*|\\/|\\%
</pre>

Die zahlreichen Alternativen für die Token werden durch `|` voneinander getrennt.
Token, die aus einem einzigen Zeichen bestehen &ndash; zum Beispiel der `+`-Operator oder eine runde Klammer `(` oder `)` &ndash; 
sind direkt im Ausdruck platziert &ndash; allerdings mit einem führenden Backslash `\`,
da einige dieser Zeichen (zum Beispiel das `+`) in einem regulären Ausdruck eine spezielle Bedeutung haben.
Da wir uns wiederum im Kontext einer C-Zeichenkette befinden, wo das Backslash `\` eine besondere Bedeutung hat,
müssen die UPN-Token folglich mit *zwei* Backslash-Zeichen eingeleitet werden, also zum Beispiel `\\+`.

Das Scannen ganzer Zahlen ist mit einem regulären Ausdruck trivial:
Wollen wir führende Nullen ausschließen, dann lautet der entsprechende Ausdruck

<pre>
[1-9][0-9]*
</pre>

Jetzt ist noch die Frage zu klären, ob die Zahl `0` ebenfalls zulässig sein soll. 
Der soeben vorgestellte reguläre Ausdruck schließt die `0` ja gerade aus.
Wir könnten das Zeichen `0` separat ergänzen, dann lautet der reguläre Ausdruck

<pre>
([0]|[1-9][0-9]*)
</pre>

Die einzelnen Bestandteile in der Analyse eines Ausdrucks in *Postfix*-Notation
können elegant mit einem Iterator für reguläre Ausdrücke (`std::sregex_iterator`)
erfasst werden, siehe hierzu die Details in [Listing 2].

Damit sind wir bei der Klasse `PostfixCalculator` angekommen ([Listing 3]):

###### {#listing_3_class_postfix_calculator}

```cpp
01: template <typename T>
02: class PostfixCalculator
03: {
04: private:
05:     std::stack<Token<T>> m_stack;  // temporary stack of operands
06: 
07: public:
08:     // public interface
09:     template <typename Iter>
10:     T calc(Iter begin, Iter end)
11:     {
12:         std::stack<Token<T>> m_stack;  // temporary stack of operands
13: 
14:         for (Iter it{ begin }; it != end; ++it)
15:         {
16:             Token<T> tok{ *it };
17: 
18:             if (tok.getTokenType() == TokenType::Operand)
19:             {
20:                 // push operand on temporary operand stack
21:                 m_stack.push(tok);
22:             }
23:             else if (tok.getTokenType() == TokenType::Operator)
24:             {
25:                 // binary operator, retrieve operands from operand stack
26:                 Token<T> right{ m_stack.top() };
27:                 m_stack.pop();
28: 
29:                 Token<T> left{ m_stack.top() };
30:                 m_stack.pop();
31: 
32:                 T rightValue{ right.getValue() };
33:                 T leftValue{ left.getValue() };
34:                 T result{};
35: 
36:                 OperatorType op{ tok.getOperatorType() };
37:                 switch (op)
38:                 {
39:                 case OperatorType::AddOp:
40:                     result = leftValue + rightValue;
41:                     break;
42:                 case OperatorType::SubOp:
43:                     result = leftValue - rightValue;
44:                     break;
45:                 case OperatorType::MulOp:
46:                     result = leftValue * rightValue;
47:                     break;
48:                 case OperatorType::DivOp:
49:                     result = leftValue / rightValue;
50:                     break;
51:                 case OperatorType::ModOp:
52:                     static_assert (
53:                         std::is_integral<T>::value or std::is_floating_point<T>::value,
54:                         "Expected integral or floating-point type."
55:                     );
56:                     if constexpr (std::is_integral<T>::value) {
57:                         result = leftValue % rightValue;
58:                     }
59:                     else if constexpr (std::is_floating_point<T>::value) {
60:                         result = std::fmod(leftValue, rightValue);
61:                     }
62:                     break;
63:                 default:
64:                     break;
65:                 }
66: 
67:                 // push result to operand stack
68:                 Token<T> val{ result };
69:                 m_stack.push(val);
70:             }
71:         }
72: 
73:         // retrieve result from stack
74:         Token<T> result{ m_stack.top() };
75:         m_stack.pop();
76:         return result.getValue();
77:     }
78: };
```

*Listing* 3: Klassentemplate `PostfixCalculator<T>`

Einen Hinweis zur Realisierung von [Listing 3] wollen wir nicht außer Acht lassen:
Werfen Sie doch bitte einen Blick auf die Zeilen 56 bis 61.
Der Modulo-Operator `%` ist in C++ nur für ganzzahlige
Datentypen definiert. Würden Sie das Klassentemplate `PostfixCalculator<T>` mit `T` gleich `double`
instanziieren, erhalten Sie einen Übersetzungsfehler!

Modernes C++ mit *Type Traits* und den beiden Funktionstemplates `std::is_integral` 
und `std::is_floating_point` bietet zusammen mit `if constexpr` die Lösung:
Je nachdem welchen Datentyp Sie für `T` wählen, entscheidet sich der Übersetzer dann,
nur einen der beiden Zweige des `if constexpr`-Konstrukts zu übersetzen.
Auf diese Weise erhalten Sie funktionsfähige UPN-Recher
des Typs `PostfixCalculator<int>` als auch `PostfixCalculator<double>`!

Wenn Sie ganz auf Nummer sicher gehen wollen,
können Sie mit einer `static_assert`-Anweisung (Zeilen 52 bis 55 in [Listing 3]) sicherstellen,
dass das Klassentemplate `PostfixCalculator<T>` ausschließlich mit
arithmetischen Datentypen (ganze Zahlen oder Gleitkommazahlen) instanziiert wird!

###### {#listing_4_class_infix_postfix_converter}

```cpp
001: template <typename T>
002: class InfixToPostfixConverter
003: {
004: private:
005:     std::list<Token<T>> m_postfix;     // postfix expression (output)
006:     std::stack<Token<T>> m_stack;      // temporary stack of operators and brackets
007: 
008: public:
009:     // public interface
010:     template <typename Iter>
011:     std::list<Token<T>> convert(Iter begin, Iter end) {
012:         clear();
013: 
014:         Token<T> next{};
015:         if (begin != end) {
016:             next = *begin;
017:             ++begin;
018:         }
019: 
020:         while (next.getTokenType() != TokenType::Null)
021:         {
022:             if (next.getTokenType() == TokenType::Operand)
023:                 processOperand(next);
024:             else if (next.getTokenType() == TokenType::Operator)
025:                 processOperator(next);
026:             else if (next.getTokenType() == TokenType::LBracket)
027:                 processLeftParenthesis(next);
028:             else if (next.getTokenType() == TokenType::RBracket)
029:                 processRightParenthesis();
030: 
031:             dumpStacks(next);
032: 
033:             if (begin != end) {
034:                 next = *begin;
035:                 ++begin;
036:             }
037:             else {
038:                 next = {};
039:             }
040:         }
041: 
042:         processEndOfInput();
043:         dumpStacks(next);
044: 
045:         return m_postfix;
046:     }
047: 
048: private:
049:     // helper methods
050:     void clear() {
051:         m_postfix.clear();
052:     }
053: 
054:     void processOperand(Token<T> next) {
055:         // append operand to the postfix buffer
056:         m_postfix.push_back(next);
057:     }
058: 
059:     void processOperator(Token<T> next) {
060:         /**
061:          * Move operators from the stack to the output buffer, as long as
062:          * - the incoming operator precedence is lower or equal to a stacked operator,
063:          * - no left parenthesis appears on the stack
064:          * - and the stack is not empty.
065:          * The incoming operator is stacked.
066:          */
067:         do
068:         {
069:             if (m_stack.empty())
070:                 break;
071: 
072:             // left parenthesis on stack encountered
073:             Token<T> top = m_stack.top();
074:             if (top.getTokenType() == TokenType::LBracket)
075:                 break;
076: 
077:             if (next.getPrecedence() <= top.getPrecedence())
078:             {
079:                 m_stack.pop();
080:                 m_postfix.push_back(top);
081:             }
082:             else {
083:                 break;
084:             }
085:         } while (true);
086: 
087:         // stack incoming operator
088:         m_stack.push(next);
089:     }
090: 
091:     void processLeftParenthesis(Token<T> next) {
092:         // push a left parenthesis onto the operator stack
093:         m_stack.push(next);
094:     }
095: 
096:     void processRightParenthesis()
097:     {
098:         // move operators from the stack to the output buffer, until a left 
099:         // parenthesis appears on the stack (the left parenthesis is discarded)
100:         do
101:         {
102:             Token<T> top = m_stack.top();
103: 
104:             if (top.getTokenType() == TokenType::LBracket)
105:                 break;
106: 
107:             m_stack.pop();
108:             m_postfix.push_back(top);
109:         } while (true);
110: 
111:         // discard left parenthesis
112:         m_stack.pop();
113:     }
114: 
115:     void processEndOfInput() {
116:         // copy remaining elements from operator stack to postfix buffer
117:         while (!m_stack.empty())
118:         {
119:             Token<T> top = m_stack.top();
120:             m_stack.pop();
121:             m_postfix.push_back(top);
122:         }
123:     }
124: 
125:     void dumpStacks(Token<T> next) {
126:         // dump latest token
127:         std::cout << next << "  ";
128: 
129:         // output stack (not trivial, because stack has limited iterator support)
130:         std::cout << "[";
131:         if (m_stack.size() != 0) {
132:             // need a copy of the stack
133:             std::stack<Token<T>> stack{ m_stack };
134:             std::vector<Token<T>> tmp{};
135:             while (!stack.empty()) {
136:                 Token<T> top = stack.top();
137:                 stack.pop();
138:                 tmp.push_back(top);
139:             }
140: 
141:             std::reverse(
142:                 std::begin(tmp),
143:                 std::end(tmp)
144:             );
145: 
146:             std::for_each(
147:                 std::begin(tmp),
148:                 std::prev(std::end(tmp)),
149:                 [](const Token<T>& token) {
150:                     std::cout << token << ", ";
151:                 }
152:             );
153: 
154:             const Token<T>& latest = tmp.back();
155:             std::cout << latest;
156:         }
157:         std::cout << "]";
158: 
159:         // fill gap equally spaced
160:         const size_t MaxDistance = 20;
161:         size_t size = m_stack.size();
162:         size_t count{};
163: 
164:         if (size == 0) {
165:             count = MaxDistance - 2;
166:         }
167:         else if (size == 1) {
168:             count = MaxDistance - 3;
169:         }
170:         else {
171:             count = MaxDistance - (3 * size);
172:         }
173: 
174:         for (size_t n{}; n != count; ++n) {
175:             std::cout << " ";
176:         }
177: 
178:         // output so far calculated tokens in postfix order
179:         std::cout << '[';
180:         if (m_postfix.size() != 0) {
181: 
182:             std::for_each(
183:                 std::begin(m_postfix),
184:                 std::prev(std::end(m_postfix)),
185:                 [](const Token<T>& token) {
186:                     std::cout << token << ", ";
187:                 }
188:             );
189: 
190:             const Token<T>& latest = m_postfix.back();
191:             std::cout << latest;
192:         }
193: 
194:         std::cout << ']';
195:         std::cout << std::endl;
196:     }
197: };
```

*Listing* 4: Klassentemplate `InfixToPostfixConverter<T>`

<br/>

# There&lsquo;s more

Eine große Schwachstelle im Entwurf der Klasse `Token` aus [Tabelle 1] wird Ihnen sicherlich aufgefallen sein:
Die Methode `getValue()`, die ein `Token`-Objekt der Ausprägung `TokenType::Operator` beschreibt,
besitzt `int` als Ergebnisdatentyp:

```cpp
int getValue() const;
```

Dies sieht nun gar nicht nach wirklichem C++ aus, viel hübscher wäre es an dieser Stelle,
den Rückgabetyp und überhaupt die gesamte Konzeption des UPN-Rechners datentyp-flexibel zu gestalten.
Natürlich sind wir bei Templates angekommen:
Realisieren Sie alle beteiligten Klassen in dieser Fallstudie als Klassentemplates.

Neben integralen Datentypen wie `int`, `long` oder `long long` könnte der UPN-Kalkulator dann auch mit `double`-Werten rechnen.
In diesem Fall müssten Sie aber den Scanner erweitern für den Fall, dass er richtige `double`-Konstanten einlesen kann.
Das ist eine nicht ganz triviale Programmieraufgabe :)

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_class_token_ctors
[Tabelle 2]: #tabelle_2_class_token_scanner
[Tabelle 3]: #tabelle_3_class_token_calculator
[Tabelle 4]: #tabelle_4_class_infix_to_postfix

[Listing 1]: #listing_1_class_token
[Listing 2]: #listing_2_class_scanner
[Listing 3]: #listing_3_class_postfix_calculator
[Listing 4]: #listing_4_class_infix_postfix_converter

[Abbildung 1]:  #abbildung_1_upn_postfix_calculator
[Abbildung 2]:  #abbildung_2_upn_operator_precedence

<!-- End-of-File -->
