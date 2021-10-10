<!-- MorseCalculator.md -->

Im Jahr 1857 hat der Amerikaner *Samuel Morse* das Morsealphabet erfunden. Damals war es noch
nicht möglich, gesprochenen Text über Telegrafenleitungen zu übermitteln. Also verwendete
Samuel Morse für jeden Buchstaben kurze und lange Piepstöne (Punkte und Striche). Diese
Punkte und Striche kann man aber auch als Lichtblitze, Pfeiftöne etc. weitergeben. So ist es
möglich, ganze Worte mit anderen über große Distanzen zu &ldquo;sprechen&rdquo;.

Schreiben Sie zwei Funktionen `encode` und `decode`, die eine lesbare Nachricht in Morseschrift
verschlüsseln bzw. entschlüsseln.

<!--more-->

# Lernziele

  * Klasse `std::string_view`, `std::string_view`-Literale, Suffix &ldquo;sv&rdquo;
  * `constexpr`-Objekte
  * Lambda-Funktionen
  * STL-Algorithmen `std::begin`, `std::end`, `std::for_each`, `std::find_if`
  * STL-Klasse `std::array`
  * `using` Direktive
  * Zerlegung von Zeichenketten (*string splitting*)

# Einführung

Es gibt im Morsealphabet keine Unterscheidung zwischen Groß- und Kleinbuchstaben, die
Zuordnung einzelner Buchstaben zu den Punkten und Strichen ist in [Tabelle 1] abgedruckt:

###### {#tabelle_1_morsealphabet}

| Zeichen | Morsedarstellung | Zeichen | Morsedarstellung |
| :- | :- | :- | :- |
| A | .-   | N | -.   |
| B | -... | O | ---  |
| C | -.-. | P | .--. |
| D | -..  | Q | --.- |
| E | .    | R | .-.  |
| F | ..-. | S | ...  |
| G | --.  | T | -    |
| H | .... | U | ..-  |
| I | ..   | V | ...- |
| J | .--- | W | .--  |
| K | -.-  | X | -..- |
| L | .-.. | Y | -.-- |
| M | --   | Z | --.. |

*Tabelle* 1: Verschlüsselung der Buchstaben im Morsealphabet.

*Hinweis*: Beim Morsen wird zwischen zwei Buchstaben in einem Wort eine Pause eingeschoben.
In der Implementierung von `encode` verwenden Sie dazu ein Leerzeichen (Blank `' '`). Für die
Pause zwischen zwei Wörtern benötigen Sie ebenfalls ein Trennzeichen, der Schrägstrich `'/'` ist
ein geeigneter Kandidat. Das Leerzeichen können Sie offensichtlich nicht verwenden, da sich
sonst Pausen zwischen Buchstaben und Wörtern nicht unterscheiden lassen!

An dem folgenden Beispiel können Sie erkennen, wie das Programm ablaufen sollte:

```cpp
std::string text{ "C IS BEAUTIFUL" };
std::string message{ MorseCalculator::encode(text) };
std::cout << "Result: " << message << std::endl;
```

*Ausgabe*:

```
Result: -.-. /.. ... /-... . .- ..- - .. ..-. ..- .-..
```

# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

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
01: using namespace std::literals::string_view_literals;
02: 
03: using MorseAlphabet = std::array<std::pair<char, std::string_view>, 26>;
04: 
05: class MorseCalculator
06: {
07: public:
08:     static std::string encode(const std::string& message);
09:     static std::string decode(const std::string& message);
10: 
11: private:
12:     static std::string charToMorse(char ch);
13:     static char morseToChar(const std::string& morse);
14: 
15:     static constexpr MorseAlphabet m_alphabet
16:     { {
17:         { 'A', ".-"sv },   { 'B', "-..."sv },
18:         { 'C', "-.-."sv }, { 'D', "-.."sv },
19:         { 'E', "."sv },    { 'F', "..-."sv },
20:         { 'G', "--."sv },  { 'H', "...."sv },
21:         { 'I', ".."sv },   { 'J', ".---"sv },
22:         { 'K', "-.-"sv },  { 'L', ".-.."sv },
23:         { 'M', "--"sv },   { 'N', "-."sv },
24:         { 'O', "---"sv },  { 'P', ".--."sv },
25:         { 'Q', "--.-"sv }, { 'R', ".-."sv },
26:         { 'S', "..."sv },  { 'T', "-"sv },
27:         { 'U', "..-"sv },  { 'V', "...-"sv },
28:         { 'W', ".--"sv },  { 'X', "-..-"sv },
29:         { 'Y', "-.--"sv }, { 'Z', "--.."sv },
30:     } } ;
31: 
32: public:
33:     static inline constexpr size_t size ()
34:     {
35:         return m_alphabet.size();
36:     }
37: 
38:     static inline constexpr std::pair<char, std::string_view> getEntry (const int index)
39:     {
40:         return m_alphabet[index];
41:     }
42: 
43:     template <int INDEX>
44:     static inline constexpr std::pair<char, std::string_view> getEntry()
45:     {
46:         return m_alphabet[INDEX];
47:     };
48: };

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
01: std::string MorseCalculator::charToMorse(char ch)
02: {
03:     ch = std::toupper(ch);
04: 
05:     auto it = std::find_if(
06:         std::begin(m_alphabet),
07:         std::end(m_alphabet),
08:         [&](const auto& entry) {
09:             return entry.first == ch;
10:         }
11:     );
12: 
13:     return (it != std::end(m_alphabet))
14:         ? std::string{ (*it).second }
15:         : std::string{};
16: }
17: 
18: char MorseCalculator::morseToChar(const std::string& morse)
19: {
20:     auto it = std::find_if(
21:         std::begin(m_alphabet), 
22:         std::end(m_alphabet),
23:         [&](const auto& entry) {
24:             return entry.second == morse;
25:         }
26:     );
27: 
28:     return (it != std::end(m_alphabet)) ? (*it).first : '\0';
29: }
30: 
31: std::string MorseCalculator::encode(const std::string& message)
32: {
33:     std::string result;
34: 
35:     std::for_each(
36:         std::begin(message),
37:         std::end(message),
38:         [&](const char ch) {
39:             if (ch == ' ') {
40:                 result.push_back('/');
41:             }
42:             else {
43:                 std::string morse = charToMorse(ch);
44:                 result.append(morse);
45:                 result.push_back(' ');
46:             }
47:         }
48:     );
49: 
50:     return result;
51: }
52: 
53: std::string MorseCalculator::decode(const std::string& message)
54: {
55:     std::string tmp{ message };
56:     char delimiter{ '/' };
57:     std::vector<std::string> words;
58:     std::string word;
59: 
60:     std::string result{};
61: 
62:     // splitting a stream with std::getline
63:     // (delimiter does't need to be a white space)
64:     std::istringstream tokenStream(tmp);
65:     while (std::getline(tokenStream, word, delimiter)) {
66:         words.push_back(word);
67:     }
68: 
69:     std::for_each(
70:         std::begin(words), 
71:         std::end(words),
72:         [&](const std::string& word) {
73:             // splitting a stream with STL iterator interface 
74:             std::istringstream iss(word);
75:             auto begin = std::istream_iterator<std::string>{ iss };
76:             auto end = std::istream_iterator<std::string>{};
77: 
78:             // constructs the container with the contents of the range
79:             std::vector<std::string> letters{ begin, end };
80: 
81:             std::for_each(
82:                 std::begin(letters),
83:                 std::end(letters), 
84:                 [&](std::string morse) {
85:                     char ch{ morseToChar(morse) };
86:                     result.push_back(ch);
87:                 }
88:             );
89: 
90:             result.push_back(' ');
91:         }
92:     );
93: 
94:     return result;
95: }
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

Der Einsatz eines `std::array`-Objekts ist für performantes  Chiffrieren und Dechiffrieren nicht die
performanteste Lösung. Überlegen Sie, wie man eine *BiMap*-Klasse implementieren könnte,
um laufzeit-optimalere Ergebnisse zu erzielen.

<br/>

<!-- Links Definitions -->

[Tabelle 1]: #tabelle_1_morsealphabet

[Listing 1]: #listing_1_class_morsecalculator_decl
[Listing 2]: #listing_2_class_morsecalculator_impl

<!-- End-of-File -->
