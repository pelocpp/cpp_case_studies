<!-- Kettenrechnen.md -->

# Kettenrechnen

Mit dem Kettenrechnen kehren wir zu den Ursprüngen unserer Grundschulzeit zurück.
Für diejenigen unter Ihnen, die dieses Thema aus Ihrem Gedächtnis verdrängt haben:

Jede Kettenrechnung beginnt mit einer normalen Rechenaufgabe (z.B. &ldquo;1+3&rdquo;).
Das Resultat muss im Gedächtnis behalten werden,
denn es folgt eine weitere Operation (z.B. &ldquo;*5&rdquo;),
welche jeweils zum vorhergehenden Resultat gerechnet werden muss.
Das neue Zwischenresultat merkt man sich ebenfalls wieder für die nächste Operation usw. usw.
So verlängert sich die &ldquo;Rechenkette&rdquo; immer weiter.

Im Beispiel

```
1 + 3 * 5 - 2 * 2 - 8 / 2
```

sollte man 14 als Endergebnis erhalten.

Entwickeln Sie eine Funktion `compute`, die eine Kettenrechnung als Parameter übergeben bekommt
und ihr Resultat zurückliefert:

```cpp
int calc (std::string chain);
```

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

Wir klären noch einige Details zum Kettenrechnen vorab:
Ja, wir machen die Beobachtung, dass die vier Grundrechenarten ohne Operatorenvorrang
auszuwerten sind, das heißt also, dass die Regel &ldquo;Punkt vor Strich&rdquo; nicht gilt.
Auch gibt es keine Klammern. Sie würden ja die Reihenfolge der Auswertung von Rechnungen
beeinflussen.

Die Zahlen sind generell aus dem Bereich der *ganzen* Zahlen zu wählen,
es treten also positive und negative Zahlen in Erscheinung.
Die Null als Operand schließen wir aus, auch wollen wir führende Nullen wie `0100` nicht zulassen.
Als Zwischenergebnis in der Berechnung einer Rechenkette kann der Wert 0 sehr wohl auftreten. 

Divisionen finden statt, sie liefern als Ergebnis das Resultat der *ganzzahligen* Division zurück,
ein möglicher Rest geht also verloren.

Und schließlich: Eine Rechenkette kann beliebig lang sein, zumindest so lang, dass sie in
Objekten des Typs `std::string` Platz findet.

Am folgenden Beispiel können Sie erkennen, wie das Programm ablaufen sollte:

```cpp
01: void test()
02: {
03:     ChainCalculatorClassic chain{};
04:     chain.calc("1 + 3 * 5 - 2 * 2 - 8 / 2");
05:     auto result{ chain.getResult() };
06:     std::cout << "Result: " << result << std::endl;
07: }
```

*Ausgabe*:

```
Result: 14
```

Wir haben der Lösung einen gewissen objektorientierten Touch veröiehen:
Es kommt eine Klasse `ChainCalculatorClassic` zum Einsatz,
eine Methode `calc` kümmert sich um das Kettenrechnen und
das Ergebnis kann durch die *getter*-Methode `getResult` abgeholt werden.

Jetzt wird es ein wenig interessanter: Wir stellen im Lösungsteil
gleich vier unterschiedliche Lösungsansätze vor:

  * Klassisches C++ &ndash; im wesentlich unter Verwendung der Klassen `std::string` und `std::string::const_iterator`.
  * Einsatz von regulären Ausdrücken.
  * Einsatz von Hilfsmitteln aus der STL (STL-Klassen `std::vector` und `std::variant`).
  * Einsatz von generischen Methoden und Parameter Packs.

Das Ganze garnieren wir zum Abschluss mit einer Messung der Programmlaufzeiten.

Natürlich würde zur Lösung der gestellten Aufgabe auch ein Lösungsansatz genügen.
Es war aber auch meine Neugierde geweckt, einen Blick auf die Laufzeiten
der unterschiedlichen Lösungsansätze zu werfen.

Und ich konnte auf diese Weise eine Brücke von der klassischen Vorgehensweise bis hin zu Modern C++ Konzepten schlagen.
  
# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).


## Lösungsansatz mit klassischem C++

Diese Lösung kommt im wesentlichen nur mit einem Objekt der Klasse `std::string` aus.
Die Rechenkette wird als `std::string`-Objekt an eine entsprechende `calc`-Methode durchgereicht.
Mit geeigneten Iteratoren-Objekten eines `std::string`-Objekts wird die Rechenkette traversiert,
es werden Operanden und Operatoren gewissermaßen &ldquo;manuell&rdquo; aus der Rechenkette extrahiert
und zeitgleich die Kettenrechnung durchgeführt.

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

Die Realisierung der Methode `getNextToken` weist Ähnlichkeiten zu entsprechenden Methode
in der lexikalischen Analyse eines programmiersprachlichen Quelltextes auf.

Signifikante Stellen in der Analyse der Eingabe-Zeichenkette sind die Anfangszeichen von Operatoren
und Operatoren. Operatoren sind einfach zu erkennen, da sie durch ein einzelnes Zeichen `+`, `-`, `*` und `/` definiert sind.
In anderen Programmiersprachen gibt es Operatoren wie etwa `++` oder `!=`,
also Operatoren bestehend aus mehreren Zeichen. Mit dieser Problematik sind wir 
bei unseren Rechenketten nicht konfrontiert.

Operanden müssen wiederum mit einem Zeichen im Bereich von `1` bis `9` anfangen.
Danach kann eine konsekutive Folge weiterer Zeichen im Bereich von `0` bis `9` solange folgen,
bis in der Zeichenkette ein anderes Zeichen vorliegt (zum Beispiel ein Leerzeichen `_` oder ein Operator).

Weitere Details in der Realisierung der `getNextToken`-Methode 
entnehen Sie bitte LISTING XXX:

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

In manchen Abschnitten weist die letzte Lösung doch gewisse Umständlichkeiten auf, oder
um es präziser zu sagen: Da könnte man das eine oder andere besser machen.

Reguläre Ausdrücke sind das probate Mittel, um Zeichenketten zu zerlegen
und ihre Inhalte zu extrahieren. Mit &ldquo;Inhalten&rdquo; sind hier Operatoren und Operanden gemeint.

In der vorgestellten Lösung finden Sie den regulären Ausdruck

```
([1-9][0-9]*)|\\+|\\-|\\*|\\/
```

vor. Mit seiner Hilfe zerlegen wir eine Kettenrechnung in Operatoren und Operanden.

Das Zerlegen des Ergenisses in Folge der Anwendung eines regulären Ausdrucks
lässt sich ganz C++&ndsh;konform mit Iteratoren-Objekten bewerkstelligen:
Es kommen zwei `std::sregex_iterator`-Objekte zum Einsatz.


Klasse *ChainCalculatorRegex* &ndash; Schnittstelle:

```cpp
```

Klasse *ChainCalculatorRegex* &ndash; Realisierung:


```cpp
```


*Beispiel*:

```cpp
```

*Ausgabe*:




## Lösungsansatz mit STL

Mit den beiden Klassen `std::vector` und `std::variant` lassen sich interessante
Anwendungen schreiben. Zum Einen ist ein `std::vector`-Objekt ein homogener Container,
mit der Klasse `std::variant` kommt hier etwas Farbe ins Spiel.

Also wenn wir einen Container des Typs `std::vector<std::variant<T ...>>`
betrachten, dann schaffen wir es auf diese Weise, Daten unterschiedlichen Typs
in einem `std::vector`-Objekt abzulegen.

Der einzige Unterschied zu den bisherigen Lösungsansätzen besteht darin,
dass wir die Schnittstelle der `calc`-Methode anpassen müssen:

An Stelle von

```cpp
void calc(std::string expression);
```

haben wir nun folgende Signatur:


```cpp
void calc(std::integral auto ... args)
```

Hier sind gleich zwei Änderungen vorhanden: Mit `auto ... args` ist ein so genanntes
*Parameter Pack* beim Aufruf bereitzustellen, also eine beliebig lange Liste von Parametern,
die unterschiedlichen Typs sein dürfen. In einer zweiten Modifikation 
unterwerden wir uns bzgl. der Parameter dem Konzept `std::integral`.

In einer Kettenrechung schlagen wir hier zwei Fliegen mit einer Klappe:
Die Operatoren sind vom Typ `char`, zumindest in aktuellen Festlegung.
Die Operanden sind vom Typ `int`.

Im Gegensatz zu den bisherigen Lösungen sieht ein Aufruf der `calc`-Methode
nun so aus:

```cpp
chain.calc(10, '+', 20, '+', 30);
```

Sowohl die Operanden als auch die Operatoren sind nun fein säuberlich zu trennen.
Dies kann man möglicherweise als nachteilig gegenüber der Notation mit einem `std::string`-Objekt ansehen,
auf der anderen Seite eröffnen sich aber viele neue Möglichkeiten,
zum Beispiel im Einsatz von *Parameter Packs*.

Der Clou in diesem Lösungsansatz besteht nun darin,
dass eine beliebig lange Liste von Operanden und Operatoren
an der `calc`-Methodenaufrufschnittstelle eingepackt und anschießend
im Kontruktor eines `std::vector<std::variant<char, int>>`-Objekts
wieder ausgepackt wird.

Um es noch einfacher zu sagen: Ohne jeglichen Programmieraufwand von unserer Seite
wird eine Liste von Parametern, wie etwa

```
10, '+', 20, '+', 30
```

in einem `std::vector<std::variant<char, int>>`-Objekt abgelegt.

Dieses Objekt durchlaufen wir nun mit einem Aufruf von `std::accumulate`:


An Hand von Metaprogramming-Techniken im Umfeld der *Type Traits* 
extrahieren wir aus dem `std::vector<std::variant<char, int>>`-Objekt 
alternierend `char`- (Operatoren) und  `int`-Variablen (Operanden).

Die Struktur eines  `std::accumulate`-Funktionsaufrufs eignet sich in geradezu idealerweise dazu,
die einzelnen Schritte einer Kettenrechnung Schritt für Schritt auszuführen.


## Lösungsansatz mit Modern C++



Die beiden Methoden `encode` und `decode` haben eher den Charakter einer Funktion.
Wir siedeln ihre Realisierung zwar in einer Klasse `MorseCalculator` an,
definieren die Methoden aber als (statische) Klassenmethoden ([Listing 1]):

###### {#listing_1_class_morsecalculator_decl}

```cpp
```

*Listing* 1: Klasse `MorseCalculator`: Definition.

Im Quellcode von [Listing 1] sind zwei weitere Subtilitäten verborgen, auf die ich aufmerksam machen möchte:

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
