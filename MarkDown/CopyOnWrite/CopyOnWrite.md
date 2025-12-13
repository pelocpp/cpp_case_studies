<!-- CopyOnWrite.md -->


# &bdquo;Faules&bdquo; Kopieren: Copy on Write 

## Literatur

https://www.informatik-aktuell.de/entwicklung/programmiersprachen/cow-ptr-der-smartpointer-fuer-copy-on-write.html

https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-on-write

https://github.com/ralphtandetzky/cpp_utils

Noch eine String Implementierung:

https://github.com/allenvox/string-cow



Hmm, für den Text ?!?!?

https://stackoverflow.com/questions/1649028/how-to-implement-copy-on-write



<img src="Schablone.svg" width="500">

*Abbildung* 1: XXX.



## Kopieren auf eine andere Weise // ALTER TEXT

Viele Objekte im täglichen &bdquo;C++&bdquo;-Alltag zeichnen sich dadurch aus,
die ihre Daten über die beiden Speicherbereiche Stack und Heap verteilt sind.
Für das Kopieren derartiger Objekte bedeutet dies, dass es nicht genügt,
die auf dem Stack liegenden Verwaltungsdaten zu kopieren. Auch die Daten auf dem Heap müssen kopiert werden,
zumindest wenn man von einer echten Kopie reden möchte.

Thematisch sind wir sehr nah am Kopierkonstruktor als auch dem Wertzuweisungsoperator dran: 
Sind in den Instanzvariablen eines Objekte Verweise vorhanden, die  auf Datenstrukturen auf dem Heap verweisen,
muss der Kopierkonstruktor explizit vom Anwender bereitgestellt werden.

Im Sprachjargon eines Informatikes könnte man Implementierungen des Kopierkonstruktors (und des Wertzuweisungsoperators) 
bezeichnet man derartige Realisierungen als eifrig oder sogar als gierig.
Etwas weniger emotional betrachtet tun die Realisierungen, das, was man von ihnen erwartet:
Eine Kopie eines vorhandenen Objekts erstellen.

In der Tat könnte man "unter der Haube" etwas anderes vorgehen: Weniger eifrig, dafür mehr faul.
Der Begriff "Lazy Copy" hat sich nicht wirklich durchgesetzt, wir sprechen hier meistens vom so genannten Copy-On-Write.

Diese Kopier-Strategie bedeutet, dass beim Kopieren einer Datenstruktur X "unter der Haube" nur ein Pointer (oder eine Referenz)
auf die internen Daten weitergereicht wird.
Eine echte und tiefe Kopie der eigentlichen Daten wird dabei erst dann durchgeführt,
wenn eine Instanz von X ihre internen Daten verändert.

Auf diese Weise entsteht für den Benutzer der Datenstruktur X die Illusion,
dass es sich um zwei unabhängige Instanzen der Datenstruktur handelt (s.Abb.1).




Dabei wird die Anzahl der Referenzen auf die interne Datenstruktur mitgezählt,
damit der letzte Besitzer die Struktur löscht.

Das hat den Vorteil, dass beim Verändern von Daten, die nur einmal referenziert werden,
keine gesonderte Kopie notwendig ist und so das Kopieren erspart werden kann.

Wenn man also mehrmals hintereinander eine Instanz von X verändert,
so wird nicht jedes Mal eine neue Kopie der internen Daten erstellt,
sondern nur dann, wenn zwischendurch eine Kopie des Objektes erstellt wird.


## Unterschiedliche Möglichkeiten des Kopierens von Objekten

Eine häufige Operation in einem Programm ist das Kopieren von Objekten.
Ein Objekt steht in objektorientierten Programmiersprachen für einen zusammengesetzter Datentyp.
Das Kopieren eines Objekts beschreibt den Vorgang, bei dem alle Attribute (Instanzvariablen) eines Objekts
in den Speicherbereich eines anderen Objekts desselben Datentyps umkopiert werden.


#### Flache Kopie 

Eine flache Kopie eines Objekts kopiert alle Instanzvariablen bitweise. Dies funktioniert in C++ problemlos,
solange die Variablen Werte elementaren Datentyps sind.
In *Abbildung* 1 finden Sie ein Objekt einer Klasse `Data` dargestellt vor:

```cpp
class Data
{
private:
    int m_value_1;
    int m_value_2;
    int m_value_3;
};
```

Um ein Objekt eines solchen Typs zu kopieren, genügt es, von allen Instanzvariablen eine bitweise
Kopie zu erstellen.

<img src="copy_on_write_01.svg" width="300">

*Abbildung* 1: Zwei Objekte des Typs `Data`: Ein Original und eine Kopie.


#### Tiefe Kopie

Wir betrachten nun Objekte, die in den Instanzvariablen neben elementaren Variablen
auch Zeigervariablen enthalten, die auf dynamisch allokierten Speicher auf der Halde zeigen.

Das Prinzip einer flachen Kopie funktioniert nun nicht mehr.
Die Zeigervariablen würden zwar korrekt kopiert werden, aber der Speicher, auf den sie verweisen,
wäre derselbe, auf den der Zeiger im Ursprungsobjekt zeigt.
Die Zeigervariable im Originalobjekt und in der Kopie verweisen auf denselben
dynamisch allokierten Speicherbereich.
Dies ist in den allermeisten Fällen so nicht gewünscht, siehe auch *Abbildung* 2:

<img src="copy_on_write_02.svg" width="600">

*Abbildung* 2: Zwei Objekte des Typs `Data`: Ein Original und eine Kopie &ndash; mit Schwachstellen.

Um zu einer korrekten Kopie zu gelangen, benötigen wir die Vorgehensweise der &bdquo;tiefen Kopie&rdquo;.
Diese kopiert alle Instanzvariablen und erstellt zusätzlich Kopien des dynamisch allokierten Speichers, auf den diese Instanzvariablen verweisen
(*Abbildung* 3). Das bedeutet insbesonder, dass Instanzvariablen, die Zeiger enthalten, mit neuen Werten versorgt werden.

<img src="copy_on_write_03.svg" width="600">

*Abbildung* 3: Zwei Objekte des Typs `Data`: Ein Original und eine korrekte Kopie.

Um eine tiefe Kopie zu erstellen, müssen Sie einen Kopierkonstruktor schreiben und den Zuweisungsoperator überladen
und wie beschrieben implementieren.
Der automtisch erzeugten Standard-Kopierkonstruktor und der Zuweisungsoperator erzeugen flache Kopien.



#### Lazy Copy

Interessanterweise gibt es neben diesen beiden Kopierstrategien auch noch eine dritte Strategie,
die so genannte &bdquo;*Lazy Copy*&rdquo;-Strategie, oder auch also &bdquo;*Copy-on-Write*&rdquo; (*COW*) bezeichnet.
Die &bdquo;*Lazy Copy*&rdquo;-Strategie kombiniert die beiden oben zuvor beschriebenen Strategien.

Bei dieser Vorgehensweise benötigen wir zusätzlich zum eigentlichen Objekt ein Hüllenobjekt,
häufig als `COW_Ptr` bezeichnet. Dieses verwaltet neben den Daten des eigentlichen Objekts
eine (atomare) Zählervariable (so genannter *Referenzcounter*).

Wird ein Objekt auf Basis der &bdquo;*Lazy Copy*&rdquo;-Strategie zum ersten Mal kopiert, wird nur die erwähnte Zählervariable inkrementiert.
Das kopierte Objekt greift auf dieselben Daten wie das Originalobjekt zu.
Solange an keinem der beteiligten Objekte eine Änderung erfolgt, funktioniert dieser Ansatz.
Eine Zählervariable verfolgt, wie viele Objekte die Daten gemeinsam nutzen.

Wenn das Programm ein Objekt ändern möchte, kann es anhand des Zählers feststellen, ob die Daten gemeinsam genutzt werden.
Wenn ja, dann ist &ndash; zu diesem Zeitpunkt, also *on demand* &ndash; eine tiefe Kopie zu erstellen.

*Bemerkung*:<br />
Die Klasse `std::shared_ptr` und eine &bdquo;*Copy-on-Write*&rdquo;-Klasse weisen gewisse Ähnlichkeiten auf.
Beide Klassen verwenden Referenzzähler, die den geteilten Besitz zählen.

Man kann sagen, dass die *Lazy Copy*-Strategie von außen betrachtet sich wie eine tiefe Kopie verhält.
Intern wird aber, soweit möglich, das Prinzip einer flachen Kopie anstrebt.
Erst wenn es zu Änderungen (schreibender Zugriff) an einem der beteiligten Objekte kommt,
ist eine echte (tiefe) Kopie zu erstellen.


## Erster Entwurf einer einfachen &bdquo;*Copy-on-Write*&rdquo;-Klasse für Zeichenketten


```cpp
01: class CowString
02: {
03: private:
04:     struct Controlblock
05:     {
06:         std::atomic<std::size_t> m_refCount;
07:         std::size_t              m_length;
08: 
09:         static Controlblock*     create      (const char* src);
10:         static Controlblock*     createEmpty ();
11:     };
12: 
13:     Controlblock* m_ptr;
14:     char*         m_str;
15: 
16:     // ensure we have a private (unshared) copy before writing
17:     void detach();
18: 
19: public:
20:     // c'tor(s), d'tor
21:     CowString();
22:     CowString(const char* s);
23:     CowString(const CowString& other);
24:     ~CowString();
25: 
26:     // assignment operator
27:     CowString& operator=(const CowString& other);
28: 
29:     // getter
30:     std::size_t size() const;
31:     const char* c_str() const;
32: 
33:     // read- and write-access
34:     char operator[](std::size_t idx) const;
35:     char& operator[](std::size_t idx);
36: };
```

In den Zeilen 4 bis 11 finden wir eine geschachtelte Klasse `Controlblock` vor.
Diese hat Ähnlichkeiten mit einer *Controlblock*-Klasse, wie in Implementierungen der Smartpointer-Klasse `std::shared_ptr<T>` verwenden.
Der beschriebene Referenzzähler `m_refCount` wird in Zeile 6 definiert, es kommt die Klasse `std::atomic<std::size_t>` zum Zuge.
Die Längenvariable `m_length` beschreibt die Länge der gekapselten Zeichenkette.

Betrachten wir die Realisierung der Methoden:

```cpp
01: CowString::Controlblock* CowString::Controlblock::create(const char* src)
02: {
03:     std::size_t len{ std::strlen(src) };
04:     void* mem{ ::operator new(sizeof(Controlblock) + len + 1) };
05:     Controlblock* sd{ new (mem) Controlblock{ 1, len } };
06:     char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
07:     std::memcpy(cp, src, len + 1);
08:     return sd;
09: }
10: 
11: CowString::Controlblock* CowString::Controlblock::createEmpty()
12: {
13:     void* mem{ ::operator new(sizeof(Controlblock) + 1) };
14:     Controlblock* sd{ new (mem) Controlblock{ 1, 0 } };
15:     char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
16:     cp[0] = '\0';
17:     return sd;
18: }
19: 
20: CowString::CowString()
21: {
22:     m_ptr = Controlblock::createEmpty();
23:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
24: }
25: 
26: CowString::CowString(const char* s = "")
27: {
28:     m_ptr = Controlblock::create(s);
29:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
30: }
31: 
32: CowString::CowString(const CowString& other)
33: {
34:     m_ptr = other.m_ptr;
35:     m_str = other.m_str;
36:     m_ptr->m_refCount++;
37: }
38: 
39: CowString& CowString::operator=(const CowString& other)
40: {
41:     if (this != &other) {
42: 
43:         m_ptr->m_refCount--;
44:         if (m_ptr->m_refCount == 0) {
45:             ::operator delete(m_ptr);
46:         }
47: 
48:         m_ptr = other.m_ptr;
49:         m_str = other.m_str;
50:         m_ptr->m_refCount++;
51:     }
52: 
53:     return *this;
54: }
55: 
56: CowString::~CowString()
57: {
58:     m_ptr->m_refCount--;
59:     if (m_ptr->m_refCount == 0) {
60:         ::operator delete(m_ptr);
61:     }
62: }
63: 
64: std::size_t CowString::size() const { return m_ptr->m_length; }
65: 
66: const char* CowString::c_str() const { return m_str; }
67: 
68: // read-only access
69: char CowString::operator[](std::size_t idx) const {
70:     return m_str[idx];
71: }
72: 
73: // write access - triggers COW
74: char& CowString::operator[](std::size_t idx) {
75: 
76:     detach();
77:     return m_str[idx];
78: }
79: 
80: // ensure we have a private (unshared) copy before writing
81: void CowString::detach()
82: {
83:     if (m_ptr->m_refCount.load() > 1) {
84: 
85:         Controlblock* old{ m_ptr };
86:         m_ptr = Controlblock::create(m_str);
87:         m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
88:         old->m_refCount--;
89:     }
90: }
```

Wir gehen auf die zentralen Methoden von Listing 2 ein.
Eine der möglicherweise unangenehmen Aufgaben der Klasse `CowString` ist es,
zu einer Zeichenkette, deren Anfangsadresse bekannt ist, Speicher zu reservieren, diesen mit der Zeichenkette zu belegen
und weitere Verwaltungsinformationen (`m_length`) zu berechnen.

Für all diese Verwaltungsinformationen gibt es in der Klasse `CowString` die innere Klasse `Controlblock`.
Bei der Festlegung der Instanzvariablen dieser Klasse stoßen wir auf ein kleines Problem:
Wie bringen wir die Daten (Zeichen) der Zeichenkette in diesem Objekt unter?
Wir könnten neben der `Controlblock`-Objekt auch die Zeichen in einem separaten Speicherbereich auf dem Heap ablegen.
Das würde bedeuten, dass für eine Zeichenkette zwei Anforderungen an die Freispeicherverwaltung gestellt werden.
Dies ist nicht sehr performant, wir beschreiten einen andere Weg.

## Entwurf der Controlblock-Klasse der `CowString`-Klasse

Wir suchen die Definition einer Klasse (Struktur), die am Ende noch einen &bdquo;nachgelagertem Speicherbereich&rdquo; besitzt,
der groß genug ist, um die Zeichenkette aufzunehmen.

Nicht übersetzungsfähig sind Strukturen der Art

```cpp
struct Controlblock
{
    size_t m;
    size_t m1;
    char trailing[];
}
```

*Bemerkung*:<br />
Der GCC-Compiler übersetzt eine derartige Struktor problemlos, der MSVC-Compiler hingegen nicht.
Wir kommen nicht umhin, festzustellen, dass diese Struktur nicht dem C++-Standard entspricht.
GCC akzeptiert sie nur als Compiler-Erweiterung (GNU Flexible Array Extension).
MSVC lehnt sie gemäß dem C++-Standard korrekt ab.

Man geht tyischerweise wie folgt vor:


```cpp
struct Controlblock
{
    size_t m1;
    size_t m2;
    // no flexible sized array
}
```

Instanzen einer `Controlblock`-Struktur werden so angelegt:

```
Controlblock* makeData(std::size_t payloadSize)
{
    void* mem = ::operator new (sizeof(Controlblock) + payloadSize);
    return new (mem) Controlblock{};
}
```

Mit dem Operator `::operator new` wird Speicher reserviert und sonst nichts weiter.
Es erfolgt keine Iniialisierung bzw. Vorbelegung des reservierten Speichers.

Diese erfolgt &ndash; im skizzierten Beispiel  &ndash; mit dem so genannten Placement new:
Der Aufruf des Standardkonstruktors (`Controlblock{}`) wird auf dem reservierten Speicher angewendet.

Offen ist, wie auf den zusätzlich vorhandenen Speicher im Anschluss an das `struct Controlblock`-Objekts zugegriffen
werden kann. Dies erfolgt mit klassischen C/C++-Sprachmitteln wie `reinterpret_cast` und Zeigerarithmetik:

```cpp
Controlblock* d = makeControlblock(10);
char* payload = reinterpret_cast<char*>(data) + sizeof(Controlblock);
// 10 bytes past 'payload' pointer available
```



## &bdquo;*Copy-on-Write*&rdquo;-Klassen und die STL-Klasse `std::string`

Häufig wird die Frage gestellt, warum die Klasse `std::string` aus der STL nicht das &bdquo;*Copy-on-Write*&rdquo;-Idiom
umsetzt. Die Antwort ist vergleichsweise einfach: 
Die `std::string`-Klasse besitzt ein historisch gewachsenenes API, für das das &bdquo;*Copy-on-Write*&rdquo;-Idiom 
ungeeignet ist. Was ist damit konkret gemeint?

Viele der `std::string`-Methoden oder Operator hantieren mit Referenzen auf Daten (Zeichen)
innerhalb eines `std::string`-Objekts, zum Beispiel

```cpp
char& at(std::size_t_ pos);
```

oder auch 

```cpp
char& operator[](std::size_t_ pos);
```

oder auch

```cpp
char& front();
```

oder auch

```cpp
char& back(); 
```

Diese Konzeption war ein toller Schachzug beim Design der `std::string`-Klasse.
Es lassen sich sehr intuitive Anweisungen &ndash; mit Referenzen im Hintergrund &ndash; schreiben,
so dass lesende und schreibende Zugriffe über dieselben Methoden der `std::string`-Klasse angebildet werden können.

Nur sind wir bei diesem Ansatz mit dem Problem konfrontiert, dass wir innerhalb der `std::string`-Klasse
nicht erkennen können, ob diese Referenz außerhalb der Klasse nur lesend oder auch schreibend verwendet wird.

Man könnte natürlich &ndash; aus Sicht des &bdquo;*Copy-on-Write*&rdquo;-Idioms den Worst-Case
eines Schreibens zugrunde legen, nur wäre dies ein pessimistischer Ansatz,
der nicht zu einer praktikablen Realisierung führt.

Wenn wir eine Klasse für Zeichenketten inklusive des &bdquo;*Copy-on-Write*&rdquo;-Idioms realisieren wollen,
dann müsste man die öffentliche Schnittstelle auch anpassen.
Zum Beispiel, dass die Mehrzahl der Methoden einen lesenden Zugriff umsetzt.
Und die wenigen schreibenden Zugriffe auch klar dokumentieren, dass es hier hinter den Kuluissen
zu einer tiefen Objektkopie kommt.


