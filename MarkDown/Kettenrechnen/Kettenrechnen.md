<!-- Kettenrechnen.md -->

# Kettenrechnen

Mit dem Kettenrechnen kehren wir zu den Ursprüngen unserer Grundschulzeit zurück.
Für diejenigen unter Ihnen, die dieses Thema aus Ihrem Gedächtnis verdrängt haben:

Jede Kettenrechnung beginnt mit einer normalen Rechenaufgabe (z.B. &ldquo;1 + 3&rdquo;).
Das Resultat muss im Gedächtnis behalten werden,
denn es folgt eine weitere Operation (z.B. &ldquo;* 5&rdquo;),
welche jeweils zum vorhergehenden Resultat gerechnet werden muss.
Das neue Zwischenresultat merkt man sich ebenfalls wieder für die nächste Operation usw. usw.
So verlängert sich die &ldquo;Rechenkette&rdquo; immer weiter.

Im Beispiel `1 + 3 * 5 - 2 * 2 - 8 / 2` sollte man 14 als Endergebnis erhalten.

Entwickeln Sie eine Funktion `calc`, die eine Kettenrechnung als Parameter übergeben bekommt
und ihr Resultat zurückliefert:

```cpp
int calc (std::string chain);
```

Offensichtlich führen viele Wege zum Ziel einer ansprechenden Realisierung. Im Lösungsteil finden Sie
Lösungsansätze vor, die generische Funktionen, heterogene STL-Container, reguläre Ausdrücke und vieles mehr anwenden.

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

###### {#listing_1_class_chaincalculatorclassic_decl}

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

*Listing* 1: Klasse `ChainCalculatorClassic`: Schnittstelle.


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
entnehen Sie bitte [Listing 2]:

###### {#listing_2_class_chaincalculatorclassic_impl}

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

*Listing* 2: Klasse `ChainCalculatorClassic`: Realisierung.



*Beispiel*:

```cpp
```

*Ausgabe*:


```
```


## Lösungsansatz mit regulären Ausdrücken

In manchen Abschnitten weist die letzte Lösung doch gewisse Umständlichkeiten auf, oder,
um es präziser zu sagen: Da könnte man das eine oder andere auch besser machen.

Reguläre Ausdrücke sind das probate Mittel, um Zeichenketten zu zerlegen
und ihre Inhalte zu extrahieren. Mit &ldquo;Inhalten&rdquo; sind hier Operatoren und Operanden gemeint.
In der vorgestellten Lösung finden Sie den regulären Ausdruck

```
([1-9][0-9]*)|\\+|\\-|\\*|\\/
```

vor. Mit seiner Hilfe zerlegen wir eine Kettenrechnung in Operatoren und Operanden.

Das Zerlegen des Ergebnisses in Folge der Anwendung eines regulären Ausdrucks
lässt sich ganz C++&ndash;konform mit Iteratoren-Objekten bewerkstelligen:
Es kommen zwei `std::sregex_iterator`-Objekte zum Einsatz.


###### {#listing_3_class_chaincalculatorregex_decl}

```cpp
```

*Listing* 3: Klasse `ChainCalculatorRegex`: Schnittstelle.


Wir fahren gleich mit der Realisierung fort:

###### {#listing_4_class_chaincalculatorregex_impl}

```cpp
```

*Listing* 4: Klasse `ChainCalculatorRegex`: Realisierung.



*Beispiel*:

```cpp
```

*Ausgabe*:




## Lösungsansatz mit STL

Mit den beiden Klassen `std::vector` und `std::variant` lassen sich interessante
Anwendungen schreiben. Zum Einen ist ein `std::vector`-Objekt ein homogener Container,
mit der Klasse `std::variant` kommt hier etwas Farbe ins Spiel.

Also wenn wir einen Container des Typs `std::vector<std::variant<TArgs ...>>`
betrachten (`TArgs ...` steht für eine Liste von Datentypen),
dann schaffen wir es auf diese Weise, Daten unterschiedlichen Typs
in einem `std::vector`-Objekt abzulegen.
Der einzige Unterschied zu den bisherigen Lösungsansätzen besteht darin,
dass wir die Schnittstelle der `calc`-Methode anpassen müssen:

An Stelle von

```cpp
void calc(std::string expression);
```

benötigen wir nun folgende Signatur:


```cpp
void calc(std::integral auto ... args)
```

Hier sind gleich zwei Beobachtungen interessant: Mit `auto ... args` ist ein so genanntes
*Parameter Pack* beim Aufruf bereitzustellen, also eine beliebig lange Liste von Parametern,
die sogar unterschiedlichen Typs sein dürfen.
In einer zusätzlichen Annotation &ndash; genauer gesagt: Einschränkung auf Basis eines C++ *Concepts* &ndash;
unterwerfen wir die möglichen Aktualparameter dem Konzept `std::integral`.

In einer Kettenrechnung schlagen wir hier zwei Fliegen mit einer Klappe:
Die Operatoren sind vom Typ `char`, zumindest in der aktuellen Festlegung.
Die Operanden wiederum sind vom Typ `int`, also sowohl Operatoren und Operanden lassen sich durch
das `std::integral`&ndash;Requirement gut erfassen.

Im Gegensatz zu den bisherigen Lösungen sieht ein Aufruf der `calc`-Methode
nun so aus:

```cpp
chain.calc(10, '+', 20, '+', 30);
```

Sowohl die Operanden als auch die Operatoren sind nun fein säuberlich zu trennen.
Dies kann man möglicherweise als nachteilig gegenüber der Notation mit einem `std::string`-Objekt ansehen.
Auf der anderen Seite eröffnen sich jetzt aber viele neue Möglichkeiten, um auf moderen C++&ndash;Sprachmittel
zurückgreifen zu können, wie zum Beispiel den Einsatz von *Parameter Packs* oder *generischen Funktionen*.

Der Clou in diesem Lösungsansatz besteht nun darin,
dass eine beliebig lange Liste von Operanden und Operatoren
an der `calc`-Methodenaufrufschnittstelle eingepackt und anschließend
im Konstruktor eines `std::vector<std::variant<char, int>>`-Objekts
wieder ausgepackt wird.

Um es noch einfacher zu sagen: Ohne jeglichen Programmieraufwand von unserer Seite
wird eine Liste von Parametern, wie etwa

```
10, '+', 20, '+', 30
```

in einem `std::vector<std::variant<char, int>>`-Objekt abgelegt:


```cpp
01: void calc(std::integral auto ... args) // pack parameters
02: {
03:     static_assert(sizeof ... (args) > 0);
04:     ...
05: 
06:     // unpack parameters
07:     std::vector<std::variant<char, OperandType>> expression{ args ... };
```

Dieses Objekt durchlaufen wir nun mit einem Aufruf des STL-Algorithmus `std::accumulate`:


An Hand von Metaprogramming-Techniken aus dem Baukasten der *Type Traits* 
extrahieren wir (mit Hilfe von `std::is_same`)aus dem `std::vector<std::variant<char, int>>`-Objekt 
alternierend `char`&ndash; und `int`&ndash;Variablen (Operatoren bzw. Operanden).

Die Struktur eines `std::accumulate`-Funktionsaufrufs eignet sich in geradezu idealerweise dazu,
die einzelnen Etappen einer Kettenrechnung Schritt für Schritt durchzuführen.

Da wir in der Realisierung dieses Mal generische Methoden verwenden (man könnte auch *Member Function Templates* sagen),
sind Klassenschnittstelle und -realisierung in einer Datei zusammengefasst:


###### {#listing_5_class_chaincalculatorstl_impl}

```cpp
001: class ChainCalculatorSTL
002: {
003: private:
004:     OperandType  m_result;
005:     OperatorType m_nextOperator;
006: 
007: public:
008:     // c'tors
009:     ChainCalculatorSTL() :
010:         m_result{},
011:         m_nextOperator{ OperatorType::NullOp }
012:     {}
013: 
014:     // getter
015:     auto getResult() const { return m_result; }
016: 
017:     // public interface
018:     void calc(std::integral auto ... args)
019:     {
020:         static_assert(sizeof ... (args) > 0);
021: 
022:         // reset calculator
023:         m_result = 0;
024:         m_nextOperator = OperatorType::NullOp;
025: 
026:         // unpack parameters
027:         std::vector<std::variant<char, OperandType>> expression{ args ... };
028: 
029:         // need state variable to control correct syntax of chain expression
030:         bool expectedOperator{ false };
031: 
032:         OperatorType nextOperator{};
033: 
034:         m_result = std::accumulate(
035:             std::begin(expression),
036:             std::end(expression),
037:             static_cast<OperandType>(0), // first element
038:             [&](OperandType element, const auto& next) mutable
039:             {
040:                 OperandType result{ element };
041: 
042:                 std::visit(
043: 
044:                     [&](const auto& value) {
045: 
046:                         using ElemType = decltype (value);
047: 
048:                         using ElemTypeWithoutReference =
049:                             typename std::remove_reference<ElemType>::type;
050: 
051:                         using ElemTypeWithoutReferenceAndConst =
052:                             typename std::remove_const<ElemTypeWithoutReference>::type;
053: 
054:                         if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, char>::value == true)
055:                         {
056:                             // store next operator
057:                             switch (value)
058:                             {
059:                             case '+':
060:                                 nextOperator = OperatorType::AddOp;
061:                                 break;
062: 
063:                             case '-':
064:                                 nextOperator = OperatorType::SubOp;
065:                                 break;
066: 
067:                             case '*':
068:                                 nextOperator = OperatorType::MulOp;
069:                                 break;
070: 
071:                             case '/':
072:                                 nextOperator = OperatorType::DivOp;
073:                                 break;
074:                             }
075: 
076:                             // toggle parsing state
077:                             expectedOperator = !expectedOperator;
078:                         }
079: 
080:                         if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, OperandType>::value == true)
081:                         {
082:                             // check parsing state
083:                             if (expectedOperator == true) {
084:                                 throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
085:                             }
086: 
087:                             switch (nextOperator)
088:                             {
089:                             case OperatorType::NullOp:
090:                                 result = value;
091:                                 break;
092:                             case OperatorType::AddOp:
093:                                 result = element + value;
094:                                 break;
095:                             case OperatorType::SubOp:
096:                                 result = element - value;
097:                                 break;
098:                             case OperatorType::MulOp:
099:                                 result = element * value;
100:                                 break;
101:                             case OperatorType::DivOp:
102:                                 result = element / value;
103:                                 break;
104:                             }
105: 
106:                             // toggle parsing state
107:                             expectedOperator = !expectedOperator;
108:                         }
109:                     },
110:                     next
111:                 );
112: 
113:                 return result;
114:             }
115:         );
116: 
117:         // last argument should be a operand
118:         if (expectedOperator == false) {
119:             throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
120:         }
121:     }
122: };
```

*Listing* 5: Klasse `ChainCalculatorSTL`: Schnittstelle und Realisierung.


*Beispiel*:

```cpp
```

*Ausgabe*:



## Lösungsansatz mit Modern C++

Im letzten Lösungsansatz haben wir ein `std::vector<std::variant<char, int>>`-Objekt
mit `std::accumulate` traviersiert. Das Stichwort `std::accumulate` sollte uns an die Technologie 
der zu Grunde liegenden Technik erinnern: Das so genannte *Folding*.

Die Kettenrechnung ist zunächst an die `calc`-Methode (wie im letzten Schritt gezeigt)
in einem *Parameter Pack* zu übergeben. Dieses muss nun natürlich irgendwann entpackt werden,
dieses Mal im Kontext eines Folding-Ausdrucks
(es kommt also *kein* `std::vector<std::variant<char, int>>`-Objekt zum Einsatz):

```cpp
01: void calc(std::integral auto ... args)
02: {
03:     ...
04: 
05:     // folding expression
06:     ( eval(args) , ... );
```

Die `eval`-Methode implementieren wir als generische Methode:

```cpp
void eval (std::integral auto arg);
```

Da sie im zuvor gezeigten *Folding Expression* sowohl für Operatoren als auch Operanden aufgerufen wird,
muss diese eine Fallunterscheidung durchführen. Es kommen wieder die Techniken des Metaprogramming zum Einsatz:

```cpp
01: // private helper method
02: void eval (std::integral auto arg)
03: {
04:     using Type = decltype(arg);
05: 
06:     if constexpr (std::is_same<Type, char>::value == true)
07:     { ...
08:     }
09: 
10:     if constexpr (std::is_integral<Type>::value == true && !std::same_as<Type, char>)
11:     { ...
12:     }
13: }
```

Damit sollte die Implementierung in ihren Grundzügen ausreichend vorbereitet sein:


###### {#listing_6_class_chaincalculatorstl_impl}

```cpp
01: class ChainCalculatorModern
02: {
03: private:
04:     OperandType m_result;
05:     char m_nextOperator;
06:     bool m_expectedOperator;
07: 
08: public:
09:     // c'tors
10:     ChainCalculatorModern () :
11:         m_result{},
12:         m_nextOperator{ '?' },
13:         m_expectedOperator{ false }
14:     {}
15: 
16:     // getter
17:     auto getResult() const { return m_result; }
18: 
19: public:
20:     void calc(std::integral auto ... args)
21:     {
22:         static_assert(sizeof ... (args) > 0);
23: 
24:         // reset calculator
25:         m_result = 0;
26:         m_nextOperator = '?';
27: 
28:         // initialize parsing state
29:         m_expectedOperator = false;
30: 
31:         ( eval(args) , ... );
32: 
33:         // last argument should be a operand
34:         if (m_expectedOperator == false) {
35:             throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
36:         }
37:     }
38: 
39: private:
40:     // private helper method
41:     void eval (std::integral auto arg)
42:     {
43:         using Type = decltype(arg);
44: 
45:         if constexpr (std::is_same<Type, char>::value == true)
46:         {
47:             // check parsing state
48:             if (m_expectedOperator == false) {
49:                 throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operator");
50:             }
51: 
52:             // store next operator
53:             m_nextOperator = arg;
54: 
55:             // toggle parsing state
56:             m_expectedOperator = !m_expectedOperator;
57:         }
58: 
59:         if constexpr (std::is_integral<Type>::value == true && !std::same_as<Type, char>)
60:         {
61:             // check parsing state
62:             if (m_expectedOperator == true) {
63:                 throw std::runtime_error("Wrong Syntax in expression: Expected Arithmetic Operand");
64:             }
65: 
66:             switch (m_nextOperator)
67:             {
68:             case '?':
69:                 m_result = arg;
70:                 break;
71:             case '+':
72:                 m_result = m_result + arg;
73:                 break;
74:             case '-':
75:                 m_result = m_result - arg;
76:                 break;
77:             case '*':
78:                 m_result = m_result * arg;
79:                 break;
80:             case '/':
81:                 m_result = m_result / arg;
82:                 break;
83:             }
84: 
85:             // toggle parsing state
86:             m_expectedOperator = !m_expectedOperator;
87:         }
88:     }
89: };
```

*Listing* 6: Klasse `ChainCalculatorModern`: Schnittstelle und Realisierung.


*Beispiel*:

```cpp
```

*Ausgabe*:




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
