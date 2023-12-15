<!-- Kettenrechnen.md -->

Mit dem Kettenrechnen kehren wir zu den Ursprüngen unserer Grundschulzeit zurück.
Für diejenigen unter Ihnen, die dieses Thema aus Ihrem Gedächtnis verdrängt haben:

Jede Kettenrechnung beginnt mit einer normalen Rechenaufgabe (z.B. &ldquo;1+3&rdquo;).
Das Resultat muss im Gedächtnis behalten werden,
denn es folgt eine weitere Operation (z.B. &ldquo;+3&rdquo;),
welche jeweils zum vorhergehenden Resultat gerechnet werden muss.
Das neue Zwischenresultat merkt man sich ebenfalls wieder für die nächste Operation usw.
So verlängert sich die &ldquo;Rechen-Kette&rdquo; immer weiter.

*Beispiel*: 

1+3 (= 4), + 3 (= 7), -2 (=5), * 2 (=10), -8 (=2), /2 (=1).

Dieses Beispiel würde man als richtige Kettenrechnung so formulieren:

1 + 3 + 3 - 2 * 2 - 8 / 2


// =====================================


<!--more-->

# Lernziele

  * STL-Klassen `std::vector`, `std::variant`
  * Lambda-Ausdrücke
  * Reguläre Ausdrücke (`std::std::regex`, `std::sregex_iterator`)
  * STL-Algorithmus `std::accumulate`
  * Schlüsselwort `auto`
  * Generische Funktionen
  * Zerlegung von Zeichenketten (*string splitting*)

# Einführung

Wir machen ferner die Beobachtung, dass die vier Grundrechenarten ohne Operatorenvorrang
auszuwerten sind, das heißt also, dass die Regel &ldquo;Punkt vor Strich&rdquo; nicht gilt.

Auch gibt es keine Klammern. Sie würden ja die Reihenfolge der Auswertung von Rechnungen
beeinflussen.

Die Zahlen sind generell aus dem Bereich der positiven und negativen natürlichen Zahlen und der Null zu wählen.
Division finden statt, sie liefern als Ergebnis das Resultat der ganzzahligen Division,
ein möglicher Rest geht also verloren.

Eine Rechenkette kann beliebig lang sein.

An dem folgenden Beispiel können Sie erkennen, wie das Programm ablaufen sollte:

```cpp
01: void test_chain_arithmetic()
02: {
03:     ChainCalculatorClassic chain{};
04:     chain.calc("10 + 20 + 30");
05:     auto result{ chain.getResult() };
06:     std::cout << "Result: " << result << std::endl;
07: }
```

*Ausgabe*:

```
Result: 60
```

Im Lösungsteil stellen wir vier unterschiedliche Lösungsansätze vor:

  * Klassisches C++ (im wesentlich unter Verwendung der Klassen `std::string` und `std::string::const_iterator`)
  * Einsatz von regulären Ausdrücken
  * Einsatz von Hilfsmitteln aus der STL (STL-Klassen `std::vector` und `std::variant`)
  * Mit generischen Funktionen und Parameter Packs


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

Natürlich würde zur Lösung der gestellten Aufgabe auch ein Lösungsansatz genügen.
Es war aber auch meine Neugierde, einen Blick auf die Laufzeit der Lösung zu werden.
Und damit wollte ich eine Brücke von der klassischen Vorgehensweise bis hin zu Modern C++ schlagen.


## Lösungsansatz mit klassischem C++

Diese Lösung kommt im wesentlichen nur mit einem Objekt der Klasse `std::string` aus.
Die Rechenkette wird als `std::string`-Objekt an eine entsprechende Methode durchgereicht.
Mit geeigneten Iteratoren-Objekten eines `std::string`-Objekts wird die Rechenkette traversiert,
es werden Operanden und Operatoren nahezu &ldquo;manuell&rdquo; aus der Rechenkette extrahiert.

Mit einer recht simplen Fehlerüberprüfung wird darauf geachtet, dass Operanden und Operatoren
abwechselnd auftreten, am Anfang und Ende sollte ebenfalls ein Operand vorhanden sein.

Der klassische Lösungsansatz zeichnet sich vielleicht nicht gerade durch Einfallsreichtum aus,
ich wollte ihn jedoch wegen des Zeitvergleichs mit an Bord haben:

Klasse *ChainCalculatorClassic* &ndash; Schnittstelle:

```cpp
01: class ChainCalculatorClassic
02: {
03: private:
04:     OperandType  m_result;
05:     OperatorType m_nextOperator;
06:     std::string::const_iterator m_begin;
07:     std::string::const_iterator m_end;
08: 
09: public:
10:     // c'tors
11:     ChainCalculatorClassic();
12: 
13:     // getter
14:     auto getResult() const { return m_result; }
15: 
16:     // public interface
17:     void calc(std::string expression);
18: 
19: private:
20:     // private helper method
21:     Token<OperandType> getNextToken();
22: };
```

Klasse *ChainCalculatorClassic* &ndash; Realisierung:


```cpp
001: // c'tors
002: ChainCalculatorClassic::ChainCalculatorClassic() :
003:     m_result{},
004:     m_nextOperator{ OperatorType::NullOp },
005:     m_begin{},
006:     m_end{}
007: {}
008: 
009: // public interface
010: void ChainCalculatorClassic::calc(std::string expression)
011: {
012:     // reset calculator
013:     m_result = 0;
014:     m_nextOperator = OperatorType::NullOp;
015: 
016:     // setup scanner
017:     m_begin = expression.begin();
018:     m_end = expression.end();
019: 
020:     // need state variable to control correct syntax of chain expression
021:     auto m_expectedOperator{ false };
022: 
023:     while (m_begin != m_end) {
024: 
025:         Token<OperandType> tok{ getNextToken() };
026: 
027:         if (tok.getTokenType() == TokenType::Operator)
028:         {
029:             if (m_expectedOperator == false) {
030:                 throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
031:             }
032: 
033:             // store next operator
034:             m_nextOperator = tok.getOperatorType();
035: 
036:             // toggle parsing state
037:             m_expectedOperator = !m_expectedOperator;
038:         }
039:         else if (tok.getTokenType() == TokenType::Operand)
040:         {
041:             if (m_expectedOperator == true) {
042:                 throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
043:             }
044: 
045:             OperandType value{ tok.getValue() };
046: 
047:             switch (m_nextOperator)
048:             {
049:             case OperatorType::NullOp:
050:                 m_result = value;
051:                 break;
052:             case OperatorType::AddOp:
053:                 m_result = m_result + value;
054:                 break;
055:             case OperatorType::SubOp:
056:                 m_result = m_result - value;
057:                 break;
058:             case OperatorType::MulOp:
059:                 m_result = m_result * value;
060:                 break;
061:             case OperatorType::DivOp:
062:                 m_result = m_result / value;
063:                 break;
064:             }
065: 
066:             // toggle parsing state
067:             m_expectedOperator = !m_expectedOperator;
068:         }
069:     }
070: 
071:     // last argument should be a operand
072:     if (m_expectedOperator == false) {
073:         throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
074:     }
075: }
076: 
077: Token<OperandType> ChainCalculatorClassic::getNextToken()
078: {
079:     Token<OperandType> tok{};
080: 
081:     // skip blanks, if any ...
082:     char ch{ *m_begin };
083:     if (ch == ' ') {
084: 
085:         ++m_begin;
086:         while (m_begin != m_end && *m_begin == ' ') {
087:             ++m_begin;
088:         }
089: 
090:         if (m_begin == m_end) {
091:             return tok;
092:         }
093:     }
094: 
095:     switch (ch)
096:     {
097:     case '+':
098:         tok = Token<OperandType>{ OperatorType::AddOp };
099:         ++m_begin;
100:         break;
101: 
102:     case '-':
103:         tok = Token<OperandType>{ OperatorType::SubOp };
104:         ++m_begin;
105:         break;
106: 
107:     case '*':
108:         tok = Token<OperandType>{ OperatorType::MulOp };
109:         ++m_begin;
110:         break;
111: 
112:     case '/':
113:         tok = Token<OperandType>{ OperatorType::DivOp };
114:         ++m_begin;
115:         break;
116: 
117:     case '0':
118:     case '1':
119:     case '2':
120:     case '3':
121:     case '4':
122:     case '5':
123:     case '6':
124:     case '7':
125:     case '8':
126:     case '9':
127:     {
128:         OperandType value{};
129:         while (m_begin != m_end && std::isdigit(*m_begin))
130:         {
131:             value = 10 * value + (*m_begin - '0');
132:             ++m_begin;
133:         }
134: 
135:         tok = Token<OperandType>{ value };
136:         break;
137:     }
138: 
139:     default:
140:         break;
141:     }
142: 
143:     return tok;
144: }
```

*Beispiel*:

```cpp
```

*Ausgabe*:




## Lösungsansatz mit regulären Ausdrücken

In manchen Abschnitten weist die letzte Lösung doch gewisse Umsändlichkeiten auf, oder
um es anders zu sagen: Da könnte man das eine oder andere besser machen.

Reguläre Ausdrücke sind das probate Mittel, um Zeichenkette zu zerlegen. 
Das wollen wir auch machen .


## Lösungsansatz mit STL

Mit den beiden Klassen `std::vector` und `std::variant` lassen sich interessante
Anwendungen schreiben. Zum Einen ist ein `std::vector`-Objekt ein homogener Container,

mit der Klasse `std::variant` kommt hier etwas Farbe ins Spiel.

WEITER ..................

            // unpack paramerters

             std::vector<std::variant<char, O


## Lösungsansatz mit Modern C++




Wir versuchen, in der Realisierung der Fallstudie einige Aspekte von *Modern C++* zu integrieren.
Da wäre zum Beispiel das Morsealphabet. Es bietet sich an, diese Datenstruktur so zu konzipieren,
dass ihr Inhalt bereits vom Übersetzer gebildet werden kann. Das Schlüsselwort `constexpr` kommt daher zum Einsatz &ndash;
und ein Objekt der Klasse `std::array`, da dieses etliche `constexpr`-definierte Konstruktoren und Methoden besitzt:

```cpp
using MorseAlphabet = std::array<std::pair<char, std::string_view>, 26>;
```

Die vielen Zeichenketten des Morsealphabets könnte man herkömmlich betrachtet in `std::string`-Objekten ablegen.
Da es sich aber ausschließlich um konstante Zeichenketten handelt, auf die wir nur lesend zugreifen,
können wir die C++17&ndash;Klasse `std::string_view` einsetzen. 

Die beiden Methoden `encode` und `decode` haben eher den Charakter einer Funktion.
Wir siedeln ihre Realisierung zwar in einer Klasse `MorseCalculator` an,
definieren die Methoden aber als (statische) Klassenmethoden ([Listing 1]):

###### {#listing_1_class_morsecalculator_decl}

```cpp
```

*Listing* 1: Klasse `MorseCalculator`: Definition.

Im Quellcode von [Listing 1] sind zwei weitere Subtilitäten verborgen, auf die ich aufmerksam machen möchte:

  * In Zeile 16 und 30 sind jeweils zwei geschweifte Klammern notwendig, um das `std::array`-Objekt statisch initialisieren
    zu können. Ich versuche, den Sachverhalt möglichst einfach zu erklären:
    Bei einem  `std::array`-Objekt kommt die so genannte *Aggregat*-*Initialisierung* zum Einsatz.
    Die Klasse `std::array` besitzt konzeptionell wiederum ein &ldquo;Built-in&rdquo; Array, das mit einer
    Initialisierungliste (`std::initializer_list`) vorbelegt wird. 
    Damit sind die inneren geschweiften Klammern für das `std::initializer_list`-Objekt,
    die äußeren für die Aggregat-Initialisierung notwendig.

  * Die Einträge des `std::array`-Objekts sind vom Typ `std::pair<char, std::string_view>`.
    Variablen des Typs  `std::string_view` lassen sich passgenau vorbelegen, wenn man an die Zeichenkettenkonstanten
    noch das Suffix `sv` anhängt (siehe die Zeilen 17 bis 29 von [Listing 1]).

Um überprüfen zu können, dass der Inhalt des Morsealphabets tatsächlich zur Übersetzungszeit generiert wird,
gibt es eine Methode `getEntry` (in zwei Überladungen).
Beide Überladungen müssen `inline` in der Klasse `MorseCalculator` vorhanden sein,
dies ist dem statischen Charakter der Methoden geschuldet.
Die Realisierung der `getEntry`-Methode ist mit und ohne `template`-Technik möglich.
Greift man auf die `template`-Technik zurück, ist der Alphabet-Index gleich dem Template-Parameter.
Logischerweise muss dieser zur Übersetzungszeit bekannt sein.
Die `getEntry`-Methoden ist in diesem Fall eine so genannte &ldquo;*Template Member Function*&rdquo;.
Eine Non-Template Klasse kann also Template Member Funktionen haben, wenn dies erwünscht ist.

Die zweite Überladung der `getEntry`-Methode kommt ohne Template-Technik aus,
mit dem Schlüsselwort `constexpr` alleine erreicht man auch das Ziel.
Wir demonstrieren beide Überladungen der `getEntry`-Methode an einem Beispiel:

```cpp
// accessing a single entry of the morse alphabet table
constexpr auto entry{ MorseCalculator::getEntry(3) };
std::cout << entry.first << ", " << entry.second << std::endl;

// accessing a single entry of the morse alphabet table
constexpr std::pair<char, std::string_view> entry2{ MorseCalculator::getEntry<5>() };
std::cout << entry2.first << ", " << entry2.second << std::endl;
```

*Ausgabe*:

```
D, -..
F, ..-.
```

Damit stellen wir in [Listing 2] die Implementierung der Klasse `MorseCalculator` vor:

###### {#listing_2_class_morsecalculator_impl}

```cpp
```

*Listing* 2: Klasse `MorseCalculator`: Implementierung.

Die beiden Methoden `charToMorse` (Zeilen 1 bis 16) und `morseToChar` (Zeilen 18 bis 29) von [Listing 2]
wandeln ein Zeichen des Alphabets in 
die entsprechende Morsezeichenkette um oder umgekehrt. Ein `std::array`-Objekt als Datenstruktur ist für 
eine lineare Suche hier sicherlich nicht der ideale Kandidat, ein `std::map`-Objekt wäre besser geeignet.
Ich habe mich letzten Endes dennoch für die `std::array`-Klasse aus zwei Gründen entschieden:
Zum einen wollte ich die Morsealphabet&ndash;Datenstruktur zur Übersetzungszeit erzeugen.
Hierzu bieten `std::map`-Objekte wenig oder eigentlich gar keine Unterstützung an.
Zum zweiten ist auch die `std::map`-Klasse nicht ganz die ideale Datenstruktur zum Suchen,
da man auf Grund der Suche in beiden Richtungen (Buchstabe nach Morsezeichenkette und umgekehrt)
eigentlich eine &ldquo;*Bi*&rdquo;Map Datenstruktur benötigen würde.

Die Realisierung der `encode`-Methode verbirgt keine Stolpersteine.
In der `decode`-Methode wird zweimal &ndash; auf unterschiedliche Weise &ndash; eine Zeichenkette in Teilzeichenketten zerlegt.
In den Zeilen 64 bis 67 vollziehen wir dies mit einer speziellen Überladung der `std::getline`-Methode.
Der Vorteil dieses Ansatzes ist, dass das Trennzeichen kein Blank sein muss (hier: Schrägstrich `'/'`).
Es wird eine Nachricht mit mehreren Wörtern in ihre einzelnen Worte zerlegt.
Die zweite Zeichenkettenzerlegung zerlegt ein Wort in Morsedarstellung in die einzelnen Buchstaben.
Hier tritt als Trennzeichen ein Blank in Erscheinung, wir können ein `std::istringstream`-Objekt
mit zwei `std::istream_iterator<std::string>`-Objekten einsetzen.
Eine spezielle Überladung der Konstruktoren der `std::vector`-Klasse besitzt
zwei `std::istream_iterator<std::string>`-Objekte
als Parameter und traversiert auf diese Weise das `std::istringstream`-Objekt, das dabei in seine einzelnen
Bestandteile zerlegt wird. Dieser Ansatz setzt ein Blank als Trennzeichen voraus (Zeilen 74 bis 79).

In den Zeilen 72 bis 91 können Sie eine Lambda-Funktion wahrnehmen, die in der Implementierung
wiederum eine Lambda-Funktion enthält (Zeilen 84 bis 87). Also einfacher formuliert: Wir haben eine geschachtelte Lambda-Funktion vorliegen.
Subtil hierbei ist, dass die innere Lambda-Funktion auf eine Variable `result` im *Closure*
der äußeren, umgebenden `decode`-Methode zugreift. Es muss folglich in beiden *Capture*-*Clauses*
der Lambda-Funktionen via Referenz-Operator `&` der Zugriff ermöglicht werden.

## Ein Beispiel

Wir schließen die Erläuterungen zur Realisierung mit einem Beispiel ab:

```cpp
// testing 'back and forth'
std::string text{ "The quick brown fox jumps over the lazy dog" };
std::cout << "Input: " << text << std::endl;
std::string message{ MorseCalculator::encode(text) };
std::cout << "Morse message: " << std::endl << message << std::endl;

std::string original{ MorseCalculator::decode(message) };
std::cout << "Result: " << original << std::endl;
```

*Ausgabe*:

```
Input: The quick brown fox jumps over the lazy dog
Morse message:
- .... . /--.- ..- .. -.-. -.- /-... .-. --- .-- -. /
..-. --- -..- /.--- ..- -- .--. ... /--- ...- . .-. /
- .... . /.-.. .- --.. -.-- /-.. --- --.
Result: THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG
```

## Literatur

Die Anregungen zum Zerlegen von Zeichenketten stammen aus

[Jonathan Boccara, &ldquo;How to split a string in C++&rdquo;](https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c//).

Die Hinweise zum Initialisieren eines `std::array`-Objekts sind

[Stackoverflow, &ldquo;C++11: Correct std::array initialization?&rdquo;](https://stackoverflow.com/questions/14178264/c11-correct-stdarray-initialization/)

entnommen.  

# There&lsquo;s more


constexpr ....

Spielverderber 


Der Einsatz eines `std::array`-Objekts ist für performantes  Chiffrieren und Dechiffrieren nicht die
performanteste Lösung. Überlegen Sie, wie man eine *BiMap*-Klasse implementieren könnte,
um laufzeit-optimalere Ergebnisse zu erzielen.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_morsealphabet

[Listing 1]: #listing_1_class_morsecalculator_decl
[Listing 2]: #listing_2_class_morsecalculator_impl

<!-- End-of-File -->
