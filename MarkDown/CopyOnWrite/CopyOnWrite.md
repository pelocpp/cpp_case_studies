<!-- CopyOnWrite.md -->

<!-- 

https://stackoverflow.com/questions/1649028/how-to-implement-copy-on-write

-->

## &bdquo;Faules&rdquo; Kopieren: Eine Alternative?

Viele Objekte im täglichen &bdquo;C++&rdquo;&ndash;Alltag zeichnen sich dadurch aus,
dass ihre Daten über die beiden Speicherbereiche Stack und Heap verteilt sind.
Für das Kopieren derartiger Objekte bedeutet dies, dass es nicht genügt,
die auf dem Stack liegenden Verwaltungsdaten &bdquo;flach&rdquo; zu kopieren. Auch die Daten auf dem Heap wollen kopiert werden,
zumindest wenn man von einer echten (&bdquo;tiefen&rdquo;) Kopie sprechen möchte.

Interessanter Weise kann man sich eine dritte Art des Kopierens vorstellen,
einen Mittelweg zwischen flacher und tiefer Kopie:
Wie wäre es, bei einer Kopieranforderung dem Benutzer von Objekt und Objektkopie
(hinter den Kulissen) zunächst einmal datentechnisch *dasselbe* Objekt in die Finger zu geben.
Solange keines dieser beiden Objekte verändert wird, besteht ja kein zwingender Handlungsbedarf, eine neue, unabhängige Kopie zu erstellen.
Problematisch wird der &bdquo;faule&rdquo; Ansatz erst dann, wenn es an einem der beteiligten Objekte zu Änderungen kommt.
Jetzt laufen Objekt und Objektkopie inhaltlich auseinander. Es wäre aber immer noch Zeit vorhanden,
verspätet &ndash; aber eben nicht zu spät &ndash; eine echte Kopie des Objekts zu erzeugen, das soeben Änderungen erfährt.

Diesen Ansatz des Kopierens könnte man als &bdquo;*Lazy Copy*&rdquo; bezeichnen, nur hat sich dieser Begriff nicht so wirklich durchgesetzt.
Wir sprechen hier meistens von der so genannten &bdquo;*Copy-On-Write*&rdquo;-Strategie.
Sprich das Erstellen einer Kopie wird erst dann angegangen, wenn es zu schreibenden Zugriffen auf das Objekt kommt.

Wir betrachten eine &bdquo;Copy-On-Write&rdquo;-Realisierung für Zeichenketten in dieser Fallstudie.
Neben einem Vergleich der Performanz zwischen der `std::string`-Klasse aus der STL und unserer selbstgeschriebenen `CowString`-Klasse
kommt auch ein Anwendungsbeispiel zum Zuge.


## Einführung

Eine häufige Operation in einem Programm ist das Kopieren von Objekten.
Ein Objekt steht in objektorientierten Programmiersprachen für einen zusammengesetzten Datentyp.
Das Kopieren eines Objekts beschreibt den Vorgang, bei dem alle Attribute (Instanzvariablen) eines Objekts
in den Speicherbereich eines anderen Objekts desselben Datentyps umkopiert werden.

Thematisch sind wir sehr nah am Kopierkonstruktor als auch dem Zuweisungsoperator von C++&ndash;Klassen dran.
Wir wiederholen zunächst die Prinzipien der flachen und tiefen Kopie von C++&ndash;Objekten,
bevor wir die dritte Alternative thematisieren.

## Unterschiedliche Möglichkeiten des Kopierens von Objekten


### Flache Kopie 

Eine flache Kopie eines Objekts kopiert alle Instanzvariablen bitweise. Dies funktioniert in C++ problemlos,
solange die Variablen Werte elementaren Datentyps sind. Werfen Sie einen Blick auf die folgende Klasse `Data`:

```cpp
class Data
{
private:
    int m_value_1;
    int m_value_2;
    int m_value_3;
};
```

In *Abbildung* 1 finden Sie ein Objekt einer Klasse `Data` dargestellt vor, das nur aus Werten elementaren Datentyps besteht.
Um ein Objekt eines solchen Typs zu kopieren, genügt es, von allen Instanzvariablen eine bitweise
Kopie zu erstellen.

<img src="copy_on_write_01.svg" width="300">

*Abbildung* 1: Zwei Objekte des Typs `Data`: Ein Original und seine Kopie.

### Tiefe Kopie

Wir betrachten nun Objekte, die in den Instanzvariablen neben Variablen elementaren Datentyps
auch Zeigervariablen enthalten, die auf dynamisch allokierten Speicher auf der Halde zeigen.
Das Prinzip einer flachen Kopie funktioniert nun nicht mehr.
Die Zeigervariablen würden zwar korrekt kopiert werden, aber der Speicher, auf den die Zeigervariablen verweisen,
wäre derselbe.
Also die Zeigervariable im Originalobjekt und die in der Kopie verweisen auf *denselben*
dynamisch allokierten Speicherbereich.

Dies ist in den allermeisten Fällen so nicht gewünscht, siehe auch *Abbildung* 2:

<img src="copy_on_write_02.svg" width="650">

*Abbildung* 2: Zwei Objekte des Typs `Data`: Ein Original und eine Kopie &ndash; mit Schwachstellen.

Um zu einer korrekten Kopie zu gelangen, benötigen wir die Vorgehensweise der &bdquo;tiefen Kopie&rdquo;.
Diese kopiert alle Instanzvariablen und erstellt zusätzlich Kopien des dynamisch allokierten Speichers, auf den diese Instanzvariablen verweisen
(*Abbildung* 3). Das bedeutet insbesondere, dass Instanzvariablen, die Zeiger enthalten, mit neuen Werten versorgt werden.

<img src="copy_on_write_03.svg" width="650">

*Abbildung* 3: Zwei Objekte des Typs `Data`: Ein Original und eine korrekte Kopie.

Um eine tiefe Kopie zu erstellen, müssen Sie einen Kopierkonstruktor schreiben und den Zuweisungsoperator überladen
und wie beschrieben implementieren.
Der automatisch erzeugte Kopierkonstruktor und der Zuweisungsoperator erzeugen flache Kopien.

### Lazy Copy

Interessanterweise gibt es neben diesen beiden Kopierstrategien auch noch eine dritte Strategie,
die so genannte &bdquo;*Lazy Copy*&rdquo;-Strategie, auch als &bdquo;*Copy-on-Write*&rdquo; (*COW*) bezeichnet.
Die &bdquo;*Lazy Copy*&rdquo;-Strategie kombiniert auf eine gewisse Weite
die beiden zuvor beschriebenen Kopierstrategien miteinander.

Sind in den Instanzvariablen eines Objekts Adressen vorhanden, die auf Datenstrukturen auf dem Heap zeigen,
müssen der Kopierkonstruktor und der Zuweisungsoperator explizit vom Anwender bereitgestellt werden,
so wie wir das soeben studiert haben.
Im Sprachjargon eines Informatikers werden derartige Realisierungen des Kopierkonstruktors und des Zuweisungsoperators 
als &bdquo;eifrig&rdquo; oder sogar als &bdquo;gierig&rdquo; tituliert.
Etwas weniger emotional formuliert tun die Realisierungen aber nur das, was man von ihnen erwartet:
Eine Kopie eines vorhandenen Objekts erstellen.

Man könnte aber &bdquo;unter der Haube&rdquo; etwas anders vorgehen:
Weniger eifrig, dafür mehr &bdquo;faul&rdquo;, auch wenn das zunächst etwas überraschend klingen mag.
Bei dieser Vorgehensweise benötigen wir zusätzlich zum eigentlichen Objekt ein Hüllenobjekt,
dass neben den Daten des Objekts zusätzliche Verwaltungsinformationen aufnimmt.

In unserer Fallstudie betrachten wir Zeichenketten, unsere Klasse heißt damit `CowString`,
wir wollen sie nun näher studieren (*Abbildung* 4).
Ein `CowString`-Objekt enthält neben den eigentlichen Daten der Zeichenkette noch weitere Daten,
die wir in Gestalt eines so genannten &bdquo;*Kontrollblocks*&rdquo; (*Controlblock*) zusammenfassen:

<img src="copy_on_write_04.svg" width="650">

*Abbildung* 4: Ein `CowString`-Objekt mit einem *Kontrollblock*.

Wir erkennen in *Abbildung* 4, dass neben den eigentlichen Daten zur Verwaltung einer Zeichenkette
ein so genannter &bdquo;*Kontrollblock*&rdquo; ins Spiel gekommen ist.
Dieser enthält im Minimalausbau eine Zählervariable, auch als *Referenz Counter* bezeichnet.
Wird ein `CowString`-Objekt zum ersten Mal angelegt, hat dieser Referenzzähler den Wert 1.
Anders herum formuliert: Es gibt keine weiteren `CowString`-Objekte, die sich die Daten des aktuellen
`CowString`-Objekts teilen.

In *Abbildung* 4 finden wir in der Klasse `CowString` weitere Instanzvariablen wir `m_str` und `m_len` vor.
`m_str` zeigt auf den Anfang der Zeichenkette, und `m_len` enthält die Länge der Zeichenkette (ohne terminierendes Null-Zeichen).
Dies sind aber schon eher ein Detail in der Realisierung der `CowString`-Klasse.
Wesentlich für unsere weiteren Betrachtungen ist der Referenzzähler,
der Bestandteil aller unterschiedlichen COW-Realisierungen ist.

*Bemerkung*:<br />
Wir legen die Realisierung unserer `CowString`-Klasse ausschließlich für eine Single-Threaded Umgebung aus.
Damit muss sich der Referenzzähler nicht mit den Problemen des atomaren Zugriffs auseinandersetzen.
In einer Multi-Threaded Umgebung muss der Referenzzähler vom Typ `std::atomic<std::size_t>` sein.


Wird ein Objekt auf Basis der &bdquo;*Lazy Copy*&rdquo;-Strategie zum ersten Mal kopiert,
ist auf dem Stack eine Adresse zu kopieren, die auf den Kontrollblock am Heap zeigt.
Im Kontrollblock wird nur die erwähnte Zählervariable inkrementiert (*Abbildung* 5).
Im `CowString`-Objekt sind alle Instanzvariablen flach zu kopieren. Dies ist nicht nur eine performante Operation,
bei der &bdquo;*Lazy Copy*&rdquo;-Vorgehensweise ist nicht mehr zu tun!

<img src="copy_on_write_05.svg" width="650">

*Abbildung* 5: Ein `CowString`-Objekt &ndash; mit einer &ndash; abhängigen &ndash; Kopie.

Wir erkennen in *Abbildung* 5, dass eine Kopie äußerst einfach und vor allem sehr schnell erstellt werden kann.
Es wird auf dem Stack ein minimales Stellvertreter-Objekt kopiert,
und im Kontrollblock auf dem Heap wird der Referenzzähler inkrementiert.

Und ja, das kopierte Objekt greift auf dieselben Daten wie das Originalobjekt zu.
Solange an keinem der beteiligten Objekte eine Änderung erfolgt, funktioniert dieser Ansatz.
Offensichtlich bedeutet diese Strategie, dass das Kopieren eines Objekts,
bzw. das, was sich hinter den Kulissen abspielt, extrem performant ist.
Eine Zählervariable protokolliert, wie viele Objekte die Daten gemeinsam nutzen.

*Bemerkung*:<br />
Um es gleich vorweg zu nehmen: Benötigen Sie ein Zeichenkettenobjekt, an dem viele Änderungen durchzuführen sind,
dann ist ein COW-Objekt nicht der prädestinierte Kandidat. Kann man hingegen die Beobachtung machen,
dass die benötigten Zeichenkettenobjekte in der Mehrzahl ohne Änderungen im Programm eingesetzt werden,
dann ist die COW-Strategie ein Ansatz, um Rechenzeit einzusparen.

Wenn das Programm ein Objekt ändern möchte, kann es anhand des Zählers feststellen, ob die Daten gemeinsam genutzt werden oder nicht.
Also: Referenzzähler gleich 1 bedeutet, es gibt kein zweites Hüllenobjekt, das Zugang zu diesem Objekt hat.
Etwaige Änderungen können problemlos am vorhandenen Objekt durchgeführt werden. Im Gegensatz dazu hat der Referenzzähler einen Wert größer 1.
Sollen jetzt Änderungen am Objekt erfolgen, dann ist &ndash; zu diesem Zeitpunkt, also verspätet bzw. *on demand* &ndash; eine tiefe Kopie zu erstellen
(*Abbildung* 6):


<img src="copy_on_write_06.svg" width="650">

*Abbildung* 6: Ein `CowString`-Objekt &ndash; und eine &ndash; unabhängige &ndash; Kopie.

In *Abbildung* 6 sieht man, wie in den beiden `CowString`-Objekten der Referenzzähler angepasst wurde.
Hatten wir in *Abbildung* 5 noch den Wert 2, so gibt es nun zwei Kontrollblöcke, deren Referenzzähler jeweils den Wert 1 haben.
Man kann beobachten, wie der Wert 2 gewissermaßen aufgeteilt wurde.

*Bemerkung*:<br />
Die Klasse `std::shared_ptr` und eine &bdquo;*Copy-on-Write*&rdquo;-Klasse weisen in ihrer Realisierung gewisse Ähnlichkeiten auf.
Beide Klassen verwenden Referenzzähler, um den geteilten Besitz zu zählen.

Man kann sagen, dass die *Lazy Copy*-Strategie von außen gesehen sich wie eine tiefe Kopie verhält.
Intern wird aber, soweit möglich, das Prinzip einer flachen Kopie angestrebt.
Flach heißt hier, um es auf den Punkt zu bringen, dass die Adresse des Kontrollblocks und die Instanzvariablen, die die Zeichenkette beschreiben,
kopiert werden.

Erst wenn es zu Änderungen (schreibender Zugriff) an einem der beteiligten Objekte kommt,
ist eine echte (tiefe) Kopie des Objekts zu erstellen, an dem Änderungen erfolgen.


## Etwas zur *Lazy Copy* Nomenklatur

Wir wollen die bisherigen Überlegungen zusammenfassen und dazu einige neue Begrifflichkeiten ins Spiel bringen:

  * Eine COW-Zeichenkette kann zwei Zustände annehmen: Sie besitzt den Puffer exklusiv (Zustand &bdquo;*Owning*&rdquo;)
oder teilt ihn mit anderen COW-Zeichenkettenobjekten (Zustand &bdquo;*Sharing*&rdquo;).

  * Zu Beginn der Existenz eines COW-Zeichenkettenobjekts befindet sich dieses im &bdquo;*Owning*&rdquo;-Zustand.
Zuweisungen und Initialisierungen durch Kopieren können das Objekt in den &bdquo;*Sharing*&rdquo;-Zustand versetzen.
Vor dem tatsächlichen Ausführen einer Schreiboperation muss sichergestellt sein, dass dieses sich im &bdquo;*Owning*&rdquo;-Zustand befindet.

* Der Übergang vom &bdquo;*Sharing*&rdquo;- zum &bdquo;*Owning*&rdquo;-Zustand beinhaltet sowohl das Kopieren des Kontrollblocks
  als auch das Anlegen einer neuen Zeichenkette. Diese Daten residieren nun in neuen, exklusiv zugeteilten Speicherbereichen.

* Bei einem für &bdquo;*Copy-On-Write*&rdquo; konzipierten Zeichenketten-Datentyp ist jede Operation entweder nicht-modifizierend (lesende Operation)
  oder modifizierend (schreibende Operation).
  Dadurch lässt sich leicht feststellen, ob die Zeichenkette vor der Ausführung der Operation den &bdquo;*Owning*&rdquo;-Zustand sicherstellen muss
  oder den &bdquo;*Sharing*&rdquo;-Zustand beibehalten kann.


## Entwurf einer einfachen &bdquo;*Copy-on-Write*&rdquo;-Klasse für Zeichenketten

Wir stellen nun Stück für Stück eine Klasse `CowString` vor.
Es folgt die Klassendefinition im Ganzen:

```cpp
01: class CowString
02: {
03: private:
04:     struct Controlblock
05:     {
06:         std::size_t       m_refCount;
07: 
08:         static Controlblock* create();
09:         static Controlblock* create(const char* src, std::size_t length);
10:     };
11: 
12:     Controlblock*         m_ptr;
13:     char*                 m_str;
14:     std::size_t           m_len;
15: 
16:     // ensure we have a private (unshared) copy before writing
17:     void detach           ();
18: 
19: public:
20:     // c'tor(s), d'tor
21:     CowString             ();
22:     explicit CowString    (const char* s);
23:     CowString             (const char* s, std::size_t count);
24:     explicit CowString    (std::string_view sv);
25:     ~CowString            ();
26: 
27:     // copy semantics
28:     CowString             (const CowString& other);
29:     CowString& operator=  (const CowString& other);
30: 
31:     // move semantics
32:     CowString             (CowString&& other) noexcept;
33:     CowString& operator=  (CowString&& other) noexcept;
34: 
35:     // getter
36:     std::size_t  size     () const;
37:     const char*  c_str    () const;
38:     bool         empty    () const;
39: 
40:     // type-conversion operator
41:     operator std::string_view() const;
42: 
43:     // comparison operators
44:     friend bool operator== (const CowString& a, const CowString& b);
45:     friend bool operator!= (const CowString& a, const CowString& b);
46:     friend bool operator<  (const CowString& a, const CowString& b);
47: 
48:     // read- and write-access - no exception handling
49:     char operator[] (std::size_t pos) const;  // read-only access
50:     char& operator[](std::size_t pos);        // possible write access - triggers COW
51:     
52:     char at (std::size_t pos) const;          // read-only access
53:     char& at(std::size_t pos);                // possible write access - triggers COW
54: };
```

In den Zeilen 4 bis 10 finden wir eine geschachtelte Klasse `Controlblock` vor.
Sie hat Gemeinsamkeiten mit einer *Kontrollblock*-Klasse, wie sie in Implementierungen der Smart Pointer Klasse `std::shared_ptr<T>` verwendet wird.
Der beschriebene Referenzzähler `m_refCount` wird in Zeile 6 definiert.
Da wir Nebenläufigkeiten in dieser Realisierung außer Acht lassen, genügt eine elementare Variable vom Typ `std::size_t`.
Andernfalls käme eine Klasse `std::atomic<std::size_t>` zum Zuge.

Neben dem Kontrollblock verwaltet die `CowString` die Daten einer Zeichenkette.
Die Längenvariable `m_len` beschreibt die Länge der gekapselten Zeichenkette,
die Zeigervariable `m_str` enthält die Anfangsadresse. Wie es zur Ablage der Zeichen in einem `CowString`-Objekt kommt,
beschreiben wir weiter unten.

Es folgen in den Zeilen 20 bis 34 die üblichen Zutaten in der Realisierung einer C++&ndash;Klasse.
Neben mehreren Konstruktoren und einem Destruktor unterstützt die `CowString` sowohl
die Kopier- als auch die Verschiebesemantik.

Die öffentliche Schnittstelle der `CowString` ist absichtlich knapp gehalten.
`CowString`-Objekte sollen schnelles Kopieren und schnelle Wertzuweisungen unterstützen.
Funktionalitäten, die in die Kategorie der &bdquo;Zeichenkettenverarbeitung&rdquo; fallen,
wurden weitestgehend weggelassen. Einzig und allein der Zugriff auf einzelne Zeichen
wird unterstützt. In Analogie zur `std::string`-Klasse sind dies der Index-Operator `operator[]` und eine `at`-Methode.
Der Index-Operator nimmt keine Überprüfung des Indexwerts vor, dies ist der `at`-Methode vorbehalten.

Da die Realisierung der `CowString`-Klasse gewisse Ähnlichkeiten zur `std::string_view`-Klasse besitzt
(beide Klassen verwalten im Wesentlichen die Anfangsadresse einer Zeichenkette und deren Länge),
unterstützen wir eine Konvertierung von `CowString`- und `std::string_view`-Objekten in beide Richtungen
(Konvertierungskonstruktor und Typkonvertierungsoperator).


Die `detach`-Methode aus Zeile 17 vollzieht einen Zustandswechsel eines `CowString`-Objekts 
vom Zustand &bdquo;*Sharing*&rdquo; in den Zustand &bdquo;*Owning*&rdquo;.
Diese Methode ist folglich in allen Methoden / Operatoren der `CowString`-Klasse zu rufen,
wenn ein schreibender Vorgang angestoßen wird. Bei allen lesenden Operationen ändert das `CowString`-Objekt
seinen Zustand nicht.

Noch erkennen wir an Hand der Klassendefinition nicht, wo die Zeichen der Zeichenkette und der Kontrollblock
im Speicher abgelegt werden. Zwei Adressvariablen sind in den Zeilen 12 und 13 zu diesem Zweck vorbereitet:

```cpp
Controlblock* m_ptr;
char*         m_str;
```

Diese Fragen beantworten wir nun bei der Realisierung der einzelnen Methoden der `CowString`-Klasse.
Zuvor wenden wir uns dem Herzstück der `CowString`-Klasse zu, dem Kontrollblock.


## Entwurf des Kontrollblocks der `CowString`-Klasse

Die Hauptaufgabe der Klasse `CowString` besteht darin,
für eine Zeichenkette, deren Anfangsadresse bekannt ist, Speicher zu reservieren, diesen mit den Zeichen der Zeichenkette zu belegen
und weitere Verwaltungsinformationen, zum Beispiel die Zeichenkettenlänge zu berechnen und aufzuheben.

Nun wollen wir aber noch das Feature haben, dass bei Kopien und Zuweisungen keine tiefe Kopie des `CowString`-Objekts vollzogen wird.
Dazu müssen wir zu jedem Zeitpunkt während der Lebensdauer eines `CowString`-Objekts wissen,
ob dieses aktuell nur einen oder mehrere Besitzer hat.
Gibt es nur einen Besitzer, stellen modifizierende Methodenaufrufe überhaupt kein Problem dar.
Es gibt ja nur einen einzigen Besitzer, der diese Änderungen initiiert.
Anders stellt sich die Sache dar, wenn es mehrere Besitzer gibt. Änderungsanforderungen eines Besitzers bedeuten nun,
dass dieser ein exklusives Objekt benötigt, alle anderen Besitzer hingegen wollen im Besitz des alten Objektzustands verbleiben.

Damit benötigen wir eine Zählervariable für die Anzahl der Besitzer.
Zu diesem Zweck gibt es in der Klasse `CowString` die innere Klasse `Controlblock`,
den schon zitierten Kontrollblock. Dieser verwaltet die Variable `m_refCount` zum Zählen der Besitzer.

Jetzt kommen wir auf die Fragestellung zu sprechen, wo wir die die Daten (Zeichen) der Zeichenkette in einem `CowString`-Objekt unterbringen?
In einer ersten Überlegung gibt es hier zwei Optionen: Im `CowString`-Objekt oder im Kontrollblock.
Der Kontrollblock wäre vielleicht die naheliegendere Wahl, da dann alle Daten an einem Ort abgelegt sind.
Negativ würde sich diese Vorgehensweise auf die Performanz auswirken, da dann jeder Zugriff auf die Zeichen
eine zusätzliche Indirektionsstufe hätte-
Als Erstes Zugriff auf ein `CowString`-Objekt, als Zweites der Zugriff auf den Kontrollblock, um an die Daten zu gelangen.
Ich habe mich deshalb für eine Ablage der Daten im `CowString`-Objekt entschieden.

Und gleich zur nächsten Detailfrage: Wo legen wir die Zeichen der Zeichenkette ab?
Wir könnten neben dem `Controlblock`-Objekt die Zeichen in einem zweiten, separaten Speicherbereich auf dem Heap ablegen.
Das würde aber bedeuten, dass für jede `CowString`-Instanz zwei Anforderungen an die Freispeicherverwaltung zu stellen sind.
Auch dies ist wiederum nicht sehr performant, wir beschreiten deshalb einen anderen Weg, der mit nur einer Heap-Allokation auskommt.
Wir definieren die Klasse (Struktur) `Controlblock` so, dass sie in der Lage ist,
am Ende noch einen &bdquo;nachgelagerten&rdquo; Speicherbereich zu besitzen,
der groß genug ist, um die Zeichenkette aufzunehmen.

Wie sieht dieser Ansatz aus?
Nicht übersetzungsfähig sind Strukturen der Art

```cpp
01: struct Controlblock
02: {
03:     std::size_t m_refCount;
04:     ...
05:     char        m_trailing[];
06: }
```

*Bemerkung*:<br />
Interessanterweise übersetzt der GCC-Compiler eine derartige Struktur problemlos, der MSVC-Compiler hingegen nicht.
Wir kommen nicht umhin, festzustellen, dass diese Struktur nicht dem C++-Standard entspricht.
GCC akzeptiert sie nur auf Grund einer Compiler-Erweiterung (&bdquo;*GNU Flexible Array Extension*&rdquo;).
MSVC lehnt sie gemäß dem C++-Standard korrekterweise ab.

Wir gehen deshalb wie folgt vor:


```cpp
01: struct Controlblock
02: {
03:     std::size_t m_refCount;
04:     ...
05:     // no flexible sized array
06: }
```

Die Struktur `Controlblock` soll also nur die Daten enthalten, die für die Verwaltung eines COW Kontrollblocks erforderlich sind.
Dafür führen wir das Anlegen einer `Controlblock`-Instanz etwas unorthodox durch.
Da wir die Länge der Zeichenkette, die es zu verwalten gilt, kennen,
reservieren wir den Speicher für die `Controlblock`-Instanz dynamisch &ndash; und belegen neben dem für die `Controlblock`-Struktur notwendigen Speicher
noch zusätzlichen Speicher, der die Zeichenkette (inkl. terminierendes Null-Zeichen) aufnehmen kann.

Das kann nur funktionieren, wenn Kontrollblöcke ausschließlich durch eine Hilfsfunktion erzeugt werden,
die mit diesem Wissen ausgestattet ist.
Eine Funktion `createControlblock`, die die Länge der Zeichenkette übergeben bekommt, könnte so aussehen:


```cpp
01: Controlblock* createControlblock(std::size_t length)
02: {
03:     void* mem = ::operator new (sizeof(Controlblock) + length + 1);
04:     return new (mem) Controlblock{ 1 };
05: }
```

Mit dem Operator `::operator new` wird Speicher reserviert und sonst nichts weiter.
Es erfolgt keine Initialisierung bzw. Vorbelegung des reservierten Speichers.

Diese erfolgt &ndash; im skizzierten Beispiel &ndash; mit dem so genannten *Placement new* Sprachkonstrukt:
Der `new`-Operator bekommt in dieser Variante den Speicherbereich als Parameter übergeben (hier: `mem`).
Der Speicherbereich selbst kann jetzt mit einer gewöhnlichen Initialisierungsliste vorbelegt werden.
Wir wenden das für Strukturen verfügbare Sprachmittel der &bdquo;Initialisierung eines Aggregats mit einer Initialisierungsliste&rdquo; an:

```cpp
Controlblock{ 1 };
```

Offen ist, wie auf den zusätzlich vorhandenen Speicher im Anschluss an die `struct Controlblock`-Variable zugegriffen
werden kann. Dies erfolgt mit klassischen C/C++-Sprachmitteln wie etwa `reinterpret_cast` und etwas Zeigerarithmetik:

```cpp
Controlblock* cb = createControlblock(10);
char* payload = reinterpret_cast<char*>(cb) + sizeof(struct Controlblock);
// 10 bytes past 'payload' pointer available
```

Dieser Ansatz mag etwas unorthodox und maschinennah erscheinen.
Er ist aber sehr flexibell und vor allem performant, die Schnelligkeit ist eben das Kriterium,
wenn wir eine `CowString`-Klasse implementieren.



## Realisierung der `CowString`-Klasse

Wir gehen jetzt auf die zentralen Methoden der `CowString`-Klasse im Detail ein und beginnen mit dem Kontrolblock.

### Kontrolblock

Da es mehrere Konstruktoren der `CowString`-Klasse gibt, die unterschiedliche Anforderunen an den Kontrolblock stellen,
finden wir in der Realisierung zwei Überladungen einer statischen `create`-Methode vor, um ein `Controlblock`-Objekt zu erzeugen:


```cpp
01: CowString::Controlblock* CowString::Controlblock::create()
02: {
03:     void* mem{ ::operator new(sizeof(Controlblock) + 1) };
04:     Controlblock* cb{ new (mem) Controlblock{ 1 } };
05:     char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
06:     cp[0] = '\0';
07:     return cb;
08: }
09: 
10: CowString::Controlblock* CowString::Controlblock::create(const char* src, std::size_t len)
11: {
12:     void* mem{ ::operator new(sizeof(Controlblock) + len + 1) };
13:     Controlblock* cb{ new (mem) Controlblock{ 1 } };
14:     char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
15:     std::memcpy(cp, src, len);
16:     cp[len] = '\0';
17:     return cb;
18: }
```

Mit dem globalen `new`-Operator wird Speicher allokiert (Zeilen 3 oder 13), groß genug, um den Kontrollblock und die Zeichenkette
(inkl. terminierendem Nullzeichen) aufzunehmen.
Der Kontrollblock wird mit der Aggregat-Initialisierung und der &bdquo;*Placement new*&rdquo;&ndash;Syntax 
zu Beginn des Speicherblocks ausgebreitet.

Dann wird noch die Anfangsadresse für die Zeichenkette berechnet.
Dazu benötigen wir den `reinterpret_cast`-Operator, um die Anzahl Bytes des Kontrollblocks zur Anfangsadresse
des Speicherblocks zu addieren.
In der zweiten Überladung der `create`-Methode wird eine Zeichenkette übergeben.
Wir kopieren diese mit `std::memcpy` hinter den Kontrollblock und achten auf die Null-Terminierung.

In beiden Realisierungen liefern wir die Adresse des Heap-Speichers zurück, 
der Kontrollblock und die Zeichenkette sind im Speicher ausgebreitet.

### Konstruktoren und Destruktor der `CowString`-Klasse

Die `CowString`-Klasse besitzt insgesamt vier Konstruktoren:

```cpp
01: // c'tor(s), d'tor
02: CowString             ();
03: explicit CowString    (const char* s);
04: CowString             (const char* s, std::size_t count);
05: explicit CowString    (std::string_view sv);
06: ~CowString            ();
```

Die Realisierung aller Konstruktoren ist vergleichsweise einfach, da die Hauptarbeit von den beiden `create`-Methoden erbracht wird:


```cpp
01: CowString::CowString()
02: {
03:     m_ptr = Controlblock::create();
04:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
05:     m_len = 0;
06: }
07: 
08: CowString::CowString(const char* s)
09: {
10:     m_len = std::strlen(s);
11:     m_ptr = Controlblock::create(s, m_len);
12:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
13: }
14: 
15: CowString::CowString(const char* s, std::size_t length)
16: {
17:     m_ptr = Controlblock::create(s, length);
18:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
19:     m_len = length;
20: }
21: 
22: CowString::CowString(std::string_view sv)
23: {
24:     m_ptr = Controlblock::create(sv.data(), sv.size());
25:     m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
26:     m_len = sv.size();
27: }
28: 
29: CowString::~CowString()
30: {
31:     if (m_ptr != nullptr) {
32: 
33:         m_ptr->m_refCount--;
34:         if (m_ptr->m_refCount == 0) {
35:             ::operator delete(m_ptr);
36:         }
37:     }
38: }
```

Allen Konstruktoren ist gemeinsam, dass sie nach der Erzeugung des Kontrollblocks die beiden `CowString`-Instanzvariablen `m_str` und `m_len`
initialisiert haben. Erstere ist die Anfangsadresse der Zeichenkette, zweitere deren Länge.
Der Kontrollblock schließlich ist durch die Instanzvariable `m_ptr` erreichbar.

### Kopier- und Verschiebesemantik

Zeichenketten sollten in einem C++&ndash;Programm kopiert als auch verschoben werden können.
Nicht nur das, in unserem Fall einer Klasse mit &bdquo;*Copy-on-Write*&rdquo;-Semantik sogar auf eine möglichst
&bdquo;*faule*&rdquo; Weise.
Vor diesem Hintergrund kommen wir nun auf die vier speziellen Methoden zum Kopieren und Verschieben von `CowString`-Objekten zu sprechen.
Wir starten mit dem &bdquo;Kopieren&rdquo;:

```cpp
01: CowString::CowString(const CowString& other)
02:     : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
03: {
04:     m_ptr->m_refCount++;
05: }
06: 
07: CowString& CowString::operator=(const CowString& other)
08: {
09:     if (this != &other) {
10: 
11:         m_ptr->m_refCount--;
12:         if (m_ptr->m_refCount == 0) {
13:             ::operator delete(m_ptr);
14:         }
15: 
16:         m_ptr = other.m_ptr;
17:         m_str = other.m_str;
18:         m_len = other.m_len;
19: 
20:         m_ptr->m_refCount++;
21:     }
22: 
23:     return *this;
24: }
```

Den Kopier-Konstruktor der Klasse `CowString` finden wir in den Zeilen 1 bis 5 vor.
Bei genauem Hinsehen erkennen wir in Zeile 2, dass alle Instanzvariablen der Klasse flach kopiert werden.
Wir haben also gar keine echte Kopie erstellt, sondern haben nur dem Prinzip der &bdquo;*Faulheit*&rdquo; folgend
das Nötigste getan. Vorsicht: In Zeile 4 inkrementieren wir den Zähler der Besitzer (*Owner*).
Damit können wir zu einem späteren Zeitpunkt stets entscheiden &ndash; wenn Änderungen an diesem Objekt erfolgen sollen &ndash;,
ob wir bei mehreren Besitzern verspätet eine tiefe Kopie erstellen müssen.

Der Zuweisungsoperator ist ähnlich realisiert. Da wir bei seinem Aufruf bereits ein `CowString`-Objekt vorliegen haben,
müssen wir die linke Seite der Zuweisung mit Vorsicht betrachten.
Für das Objekt auf der linken Seite der Zuweisung dekrementieren wir zunächst den Zähler der Besitzer.
Danach kopieren wir flach das Argument (rechte Seite) um und inkrementieren für dieses Objekt die Anzahl der Besitzer um Eins.
Wir sind wieder &bdquo;*faul*&rdquo; vorgegangen, und haben neben den Instanzvariablen auch die Anzahl der Besitzer für beide Objekte angepasst.


Damit sind wir beim Verschieben angelangt:

```cpp
01: CowString::CowString(CowString&& other) noexcept 
02:     : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
03: {
04:     other.m_ptr = Controlblock::create();
05:     other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
06:     other.m_len = 0;
07: }
08: 
09: CowString& CowString::operator=(CowString&& other) noexcept {
10: 
11:     if (this != &other) {
12: 
13:         m_ptr->m_refCount--;
14:         if (m_ptr->m_refCount == 0) {
15:             ::operator delete(m_ptr);
16:         }
17: 
18:         m_ptr = other.m_ptr;
19:         m_str = other.m_str;
20:         m_len = other.m_len;
21: 
22:         other.m_ptr = Controlblock::create();
23:         other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
24:         other.m_len = 0;
25:     }
26:     
27:     return *this;
28: }
```

Beim Verschieben müssen wir etwas behutsamer vorgehen.
Eine erste, naheliegende Realisierung des Verschiebe-Konstruktors könnte so aussehen:

```cpp
01: CowString::CowString(CowString&& other) noexcept 
02:     : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
03: {
04:     other.m_ptr = nullptr;
05:     other.m_str = nullptr;
06:     other.m_len = 0;
07: }
```

Die Zeilen 4, 5 und 6 sind wichtig:
Hier wird das Objekt `other` in den so genannten &bdquo;*Moved-From*&rdquo;-Zustand versetzt.
Von einem Objekt im &bdquo;*Moved-From*&rdquo;-Zustand wird erwartet, dass sich alle vorhandenen Methoden aufrufen lassen
und es infolgedessen *nicht* zu einem Absturz kommt &ndash; aber möglicherweise auch nicht zu dem Verhalten, das man erwarten würde.

Die Null-Adressen in `other.m_ptr` und `other.m_str` stellen das Problem dar:
Alle Methoden der `CowString`-Klasse erwarten hier gültige Zeiger, es findet keine Überprüfung auf `nullptr` statt.

Aus diesem Grund müssen für ein `CowString`-Objekt im &bdquo;*Moved-From*&rdquo;-Zustand hier gültige Adressen vorhanden sein.
Wir orientieren uns am Standard-Konstruktor und legen einen gültigen Kontrollblock mit einer leeren Zeichenkette an:


```cpp
01: CowString::CowString(CowString&& other) noexcept 
02:     : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
03: {
04:     other.m_ptr = Controlblock::create();
05:     other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
06:     other.m_len = 0;
07: }
08: 
09: CowString& CowString::operator=(CowString&& other) noexcept {
10: 
11:     if (this != &other) {
12: 
13:         m_ptr->m_refCount--;
14:         if (m_ptr->m_refCount == 0) {
15:             ::operator delete(m_ptr);
16:         }
17: 
18:         m_ptr = other.m_ptr;
19:         m_str = other.m_str;
20:         m_len = other.m_len;
21: 
22:         other.m_ptr = Controlblock::create();
23:         other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
24:         other.m_len = 0;
25:     }
26:     
27:     return *this;
28: }
```

In beiden Methoden wird das Objekt `other` zuerst verschoben.
Danach wird mit der `Controlblock::create()`-Methode ein valider Kontrollblock erzeugt, der eine leere Zeichenkette verwaltet.


### *getter*-Methoden und zeichenweiser Zugriff

Die drei *getter*-Methoden der `CowString`-Klasse sind schnell vorgestellt:

```cpp
01: std::size_t CowString::size() const { return m_len; }
02: const char* CowString::c_str() const { return m_str; }
03: bool CowString::empty() const { return m_len == 0; }
```

Die Zugriffsmethoden auf einzelne Zeichen der Zeichenkette sind nicht ganz trivial in ihrer Implementierung.
Wir betrachten zunächst die entsprechenden Deklarationen:

```cpp
01: // read- and write-access - no exception handling
02: char operator[](std::size_t idx) const;  // read-only access
03: char& operator[](std::size_t idx);       // possible write access
04:
05: char at (std::size_t idx) const;         // read-only access
05: char& at(std::size_t idx);               // possible write access
```

Wenn Sie die Deklarationen genau betrachten, werden Sie im Detail einige Unterschiede zur STL-Klasse `std::string` beobachten.
Hier lauten die entsprechenden Deklarationen:

```cpp
01: char& operator[]( std::size_t pos );
02: const char& operator[]( std::size_t pos ) const;
03: 
04: char& at( std::size_t pos );
05: const char& at( std::size_t pos ) const;
```

Alle vier Varianten der `std::string`-Klasse liefern, egal, ob es sich um die `const` oder non-`const` Variante handelt, eine *Referenz* eines Zeichens zurück.
Das wäre in der `CowString`-Klasse prinzipiell ebenso umsetzbar, ist aber nicht wünschenswert,
da man dann immer vom Worst-Case Fall ausgehen müsste, dass mit Hilfe der Referenz auch ein schreibender Zugriff erfolgen könnte.
Man müsste dann immer vom *Sharing*- zum *Owning*-Zustand im Objekt wechseln, was den bislang erzielten Performance Gewinn zunichte macht.

In der `CowString`-Realisierung wird deshalb strikt beim lesenden Zugriff darauf geachtet, dass Zeichen als Kopie und nicht mit einer Referenz
transportiert werden:

```cpp
01: // read-only access
02: char CowString::operator[](std::size_t idx) const {
03:     return m_str[idx];
04: }
05: 
06: // possible write access - triggers COW
07: char& CowString::operator[](std::size_t idx) {
08:     detach();
09:     return m_str[idx];
10: }
11: 
12: // read-only access
13: char CowString::at(std::size_t idx) const {
14:     if (idx >= m_len) {
15:         throw std::out_of_range("index out of range!");
16:     }
17:             
18:     return m_str[idx];
19: }
20: 
21: // possible write access - triggers COW
22: char& CowString::at(std::size_t idx) {
23:     if (idx >= m_len) {
24:         throw std::out_of_range("index out of range!");
25:     }
26:             
27:     detach();
28:     return m_str[idx];
29: }
```

Beachten Sie die Zeilen 8 und 27:
Die `at`-Methode / der Index-Operator `operator[]` könnten hier das gerufene Objekt verändern.
Deshalb kommt es jetzt zur Anwendung der &bdquo;*Copy-on-Write*&rdquo;-Strategie, also der nachträglichen Erstellung einer tiefen Kopie des aktuell vorliegenden Objekts.

Sehen wir uns die Realisierung der `detach`-Methode an:

```cpp
01: void CowString::detach()
02: {
03:     if (m_ptr->m_refCount > 1) {
04: 
05:         Controlblock* old{ m_ptr };
06:             
07:         std::size_t len{ std::strlen(m_str) };
08:         m_ptr = Controlblock::create(m_str, m_len);
09:         m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
10:         m_len = len;
11: 
12:         old->m_refCount--;
13:     }
14: }
```

Der Aufruf von `Controlblock::create` zieht das Erstellen einer tiefen Kopie der aktuellen Zeichenkette nach sich.
Ihre Anfangsadresse ist in `m_str` abgelegt und die Länge wiederum in `m_len`.

Wir haben soeben das Kernstück der &bdquo;*Copy-on-Write*&rdquo;-Strategie gesehen:
Wenn eine Objektkopie nicht mehr vermeidbar ist, wird diese zu einem späteren Zeitpunkt durchgeführt.


## &bdquo;*Copy-on-Write*&rdquo;-Zeichenketten und die STL-Klasse `std::string`

Häufig wird die Frage gestellt, warum die Klasse `std::string` aus der STL nicht das &bdquo;*Copy-on-Write*&rdquo;-Idiom
umsetzt. Die Antwort ist vergleichsweise einfach: 
Die `std::string`-Klasse besitzt ein historisch gewachsenes API, für das das &bdquo;*Copy-on-Write*&rdquo;-Idiom 
ungeeignet ist. Was ist damit konkret gemeint?

Viele der `std::string`-Methoden oder Operatoren hantieren mit Referenzen auf Daten (Zeichen)
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
so dass lesende und schreibende Zugriffe über dieselben Methoden der `std::string`-Klasse abgebildet werden können.

Nur sind wir bei diesem Ansatz mit dem Problem konfrontiert, dass wir innerhalb der `std::string`-Klasse
nicht erkennen können, ob diese Referenz außerhalb der Klasse lesend oder schreibend verwendet wird.
Wir beobachten eine gravierende Diskrepanz zwischen dem Design von der Klasse `std::string` einerseits
und Anforderungen an eine Klasse `CowString`, die für Zeichenketten *und* die &bdquo;*Copy-on-Write*&rdquo;-Strategie geeignet ist.

Man könnte natürlich &ndash; aus Sicht des &bdquo;*Copy-on-Write*&rdquo;-Idioms &ndash; das Worst-Case Szenario
des Schreibens zugrunde legen, nur wäre dies ein pessimistischer Ansatz,
der nicht zu einer praktikablen Realisierung für COW-Klassen führt.
Wenn wir eine Klasse für Zeichenketten inklusive des &bdquo;*Copy-on-Write*&rdquo;-Idioms realisieren wollen,
dann muss man die öffentliche Schnittstelle auch entsprechend anpassen.
Zum Beispiel so, dass sich die Mehrzahl der Methoden einen lesenden Zugriff zu eigen macht.

Schreibende Zugriffe hingegen müssen klar dokumentiert sein, so dass dem Benutzer klar ist,
dass es hier hinter den Kulissen zu einer tiefen Objektkopie kommt.

## Stolperfallen

Die Strategie des &bdquo;*verspäteten Kopierens*&rdquo; zieht Nebeneffekte nach sich.
Manche dieser Effekte sind offensichtlich, manch andere weniger.
Beginnen wir mit einem ersten Beispiel:

```cpp
01: void pitfall_01()
02: {
03:     CowString a{ "Hello" };
04:     std::println("a: {}", a);
05: 
06:     char& ch = a[0];
07: 
08:     CowString b{ a };
09:     std::println("b: {}", b);
10: 
11:     ch = '!';
12: 
13:     std::println("a: {}", a);
14:     std::println("b: {}", b);
15: }
```

In Zeile 6 erhalten wir in Variable `ch` eine Referenz des ersten Zeichens im `CowString`-Objekt `a`.
Mit Hilfe der Referenz verändern wir dieses Zeichen im `a`-Objekt.
Auf das `b` Objekt sollte diese Zuweisung keinen Einfluss haben.
Wie lautet die Ausgabe des Programms?

```
a: Hello
b: Hello
a: !ello
b: !ello
```

Hmmm, das kommt etwas überraschen. Erkennen Sie das Problem oder den Grund für diese möglicherweise unerwartete Ausgabe?
In Zeile 8 wird eine Kopie des `CowString`-Objekts angelegt, erreichbar über die Variable `b`.
Es handelt sich um eine *Lazy Copy*! Die Referenzvariable `ch` bezieht sich folglich auf beide Objekte!

Das folgende Beispiel ist etwas komplexer:

```cpp
01: void pitfall_02()
02: {
03:     CowString s{ "1234567890" };
04:     const char* p{ s.c_str() };
05: 
06:     {
07:         CowString other{ s };
08:         char firstChar{ s[0] };
09:     }
10: 
11:     std::println("After block:");
12:     std::println("p: {}", p);
13: }
```

In Zeile 3 legen wir ein `CowString`-Objekt an.
In Zeile 4 holen wir die Anfangsadresse der Zeichenkette ab und heben diese in der Variablen `p` auf.
In Zeile 12 verwenden wir diese Adresse, um die Zeichen in der Konsole auszugeben.
Das heißt, wir erwarten in etwa die Ausgabe `1234567890` in der Konsole.

Dem ist leider nicht so:

```
After block:
p: ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦
```

Damit stellt sich die Frage, welchen Einfluss der innere Block auf das Programm hat?
Das Anlegen einer Objektkopie sollte kein Problem sein, auch wenn die Strategie des &bdquo;*faulen*&rdquo; Kopierens
angewendet wird. Was passiert in Zeile 8?

```
char first_char{ s[0] };
```

Das erste Zeichen des Objekts `s` wird gelesen &ndash; mit dem Index-Operator `operator[]`.
Dieser Operator existiert in zwei Überladungen in der Klasse `CowString`:

```cpp
01: char operator[] (std::size_t pos) const;  // read-only access
02: char& operator[](std::size_t pos);        // possible write access
```

Damit ist fie Frage zu klären, welche Überladung in Zeile 8 zur Anwendung gelangt?
Da die Variable `firstChar` vom Typ `char` ist, könnte man geneigt sein, es ist die erste Überladung.
Nein, diese Vermutung ist falsch. Entscheidend zur Beantwortung der Frage ist,
von welchem Typ das Objekt ist, auf das der Index-Operator angewendet wird.
Damit sind wir beim Objekt `s` angekommen. Okay, offensichtlich ist dies eine Instant der Klasse `CowString`,
aber: Es ist *kein* Modifizierer `const` vorhanden. Damit wird die zweite Überladung aufgerufen!
Und ja, hier ist auf Grund der Referenz eine Indirektion mit im Spiel, aber die erste Überladung scheidet eben aus,
da diese in der Signatur `const` hat.

Die zweite Überladung des Index-Operators `operator[]` ruft implizit `detach()` auf,
damit wird für das Objekt `s` verspätet intern eine Kopie der Zeichenkette angelegt,
das Original der Zeichenkette verbleibt im Objekt `other`.
Dies alles wäre immer noch kein Problem, wenn nicht in Zeile 9 das Objekt `other` aus dem Scope fallen würde.
Damit verliert die in der Variablen `p` gespeicherte Adresse ihre Gültigkeit,
und das Programm arbeitet fehlerhaft weiter.

Was ist die Moral dieser Geschichte?
Wir wollen die Klasse `CowString` auf Grund dieser Nebeneffekte / Stolperfallen nicht einsetzen?
Falsch geraten! Wir sollten lernen, dass es nicht schicklich ist, Adressen oder Referenzen von `CowString`-Objekte für einen längeren Zeitraum aufzuheben.
Die intere Adresse der Zeichenkette eines `CowString`-Objekts hat einen  &bdquo;*non-owning*&rdquo; Charakter,
dass heißt, sie kann ungültig werden.

*Bemerkung*:<br />
Welche Änderung müsste man an dem letzten Beispiel vornehmen, so dass es fehlerfrei läuft?
(Anwort: Qualifizieren Sie das Objekt `s` mit `const`!)

Das sind keine neuen Erkenntnisse, sondern Beobachtungen, die wir auch in der STL machen können.
Sehen Sie hierzu das folgende Beispiel mit einem `std::string`- und einem `std::string_view` Objekt an:

```cpp
01: void pitfall_03()
02: {
03:     std::string s{ "Eros parturient vulputate feugiat risus" };
04:     const char* p{ s.c_str() };
05: 
06:     std::string_view sv{ s };
07:     std::println("sv: {}", sv);
08: 
09:     s.append(" ex facilisis molestie tristique fermentum.");
10: 
11:     std::println("sv: {}", sv);
12: }
```

*Ausgabe*:<br />

```
sv: Eros parturient vulputate feugiat risus
sv: ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦
```

Das `string_view`-Objekt `sv` speichert &ndash; wir unsere `CowString` Objekte &ndash;
die Anfangsadresse einer Zeichenkette ab. In unserem Beispiel eine Adresse,
die in den Instanzvariablen eines `std::string`-Objekts lebt.
Diese Adresse kann sich allerdings verändern, zum Beispiel dann, wenn in Folge des `append`-Aufrufs an `s`
der Speicher im `std::string`-Objekt neu organisiert wird!



## Anwendungsbeispiel: Häufigste in einer Textdatei auftretende Zeichenkette

Wir wollen die Klasse `CowString` an einem praxisnahen Beispiel testen:
Gesucht ist die Suche nach der in einer Textdatei am häufigsten auftretenden Zeichenkette.

Um die Sache beim Analysieren einer Textdatei etwas zu vereinfachen, legen wir &bdquo;*Lorem Ipsum*&rdquo;-Dateien zu Grunde.
Unter &bdquo;*Lorem Ipsum*&rdquo; verstehen wir so genannten Blindtext oder Fülltext. Er wird als Platzhaltertext verwendet,
um zum Beispiel Software testen zu können, die Textdateien verarbeitet, der geplante Text aber erst noch verfasst werden muss
und einfach noch nicht zur Verfügung steht. 

Der Text selbst sieht aus wie ein lateinischer Text, ist es aber nicht. Schon das erste Wort &bdquo;Lorem&rdquo; existiert nicht im Lateinischen.
Die Verteilung der Buchstaben und der Wortlänge im Text entsprechen in etwa der natürlichen lateinischen Sprache.
Dennoch ist der Text absolut unverständlich, der Betrachter soll durch den Inhalt nicht abgelenkt werden.

*Beispiel*:<br />

```
Eros parturient vulputate feugiat risus, porttitor quisque ridiculus in mauris.
Pellentesque accumsan tempus cursus ligula proin lacus senectus.
Porttitor enim pharetra varius purus mollis, felis nibh turpis elementum integer nisl.
Penatibus ultrices augue netus sit, lacinia pellentesque aliquet sapien vulputate.
Nibh nec aliquam dui pretium scelerisque, sollicitudin aliquet mus nisl bibendum leo. 
```

Wenn Sie dieses Beispiel genau ansehen, werden Sie entdecken, dass viele Wörter weniger als 15 Zeichen enthalten.
Das stellt prinzipiell erstmal kein Problem dar, nur konterkariert es den von mir beabsichtigen Performanzvergleich.
Für Zeichenketten der Länge kleiner oder gleich 15 unterstützen C++-Zeichenketten der gängigen Compiler Hersteller
die so genannte *SSO* (*Small String Optimization*).

*Small String Optimization* ist eine Technik, die von `std::string`-Implementierungen verwendet wird,
um kurze Zeichenketten direkt im String-Objekt zu speichern, anstatt für sie Speicher auf dem Heap zu reservieren.
Diese Optimierung nutzt die Tatsache, dass viele Zeichenketten in typischen Anwendungen relativ kurz sind
und daher im internen Puffer des `std::string`-Objekts gespeichert werden können, wodurch eine dynamische Speicherallokation vermieden wird.

Es wäre überhaupt kein Problem, auch die `CowString`-Klasse mit einer entsprechenden Optimierung auszustatten.
Nur hätte dies den Umfang eines einleitenden Beispiels überschritten, so dass ich darauf verzichtet habe.
Lange Rede, kurzer Sinn:
In unserem aktuellen Vergleichsbeispiel betrachten wir Textdateien mit vergleichsweise langen Zeichenketten.
Auf diese Weise kommt es bei Gebrauch der `std::string`-Klasse **nicht** zum Einsatz der *Small String Optimization* Technik:

```
Magnaeusagittis egetliberointerdum afusceelit diamduisdonec commodomaecenascongue,
hendreritnecsemper velfelisconvallis diamduisdonec velfelisconvallis elementumturpisarcu.
Tinciduntfacilisisrutrum faucibusultricesdapibus turpisarcutellus rutrumauguefaucibus
etinest egestasurnamorbi diamduisdonec ridiculusnasceturmontes.
Quisqueornaredui elitadipiscingconsectetur velfelisconvallis ultricesdapibusviverra fringillapharetraleo
elementumturpisarcu namfermentumaenean egetliberointerdum.
Porttitoraliquamtortor ametsitdolor mivestibulummollis convallisfringillapharetra ultriciesvitaesollicitudin,
arcutelluscommodo metusnullamassa seddictumlectus nasceturmontesparturient bibendumcursuslobortis duisdonectempus. 
```

Die meisten Zeichenketten in diesem Beispiel sind nun länger als 15 Zeichen, 
damit kann ein fairer Vergleich stattfinden.

*Bemerkung*:<br />
Für die Erstellung von &bdquo;*Lorem Ipsum*&rdquo;-Dateien finden Sie in diesem Projekt
eine Klasse `LoremIpsum` mit adäquaten Methoden vor.


Der Clou des Beispiels, und das soll nicht unerwähnt bleiben, liegt darin,
dass viele Zeichenketten im Ablauf des Programms zweimal in Erscheinung treten:
Zum ersten Mal beim Zerlegen einer Zeile der Textdatei und zum zweiten Mal,
wenn sie in einem Container der STL aufbewahrt werden.
Wir haben es also mit einem Anwendungsfall zu tun, in dem Zeichenketten mehrfach auftreten,
aber nicht verändert werden.

Sind wir auf der Suche nach dem häufigsten Auftreten einer Zeichenkette in einer Textdatei,
so bietet sich als STL-Container eine Hash-Tabelle an:

```cpp
std::unordered_map<std::string, std::size_t> frequenciesMap;
```

oder eben auch

```cpp
std::unordered_map<CowString, std::size_t> frequenciesMap;
```

Einzelne Einträge des `std::unordered_map`-Containers beschreiben in einem `std::pair`-Objekt eine Zeichenkette
und im zweiten Wert ihre Häufigkeit.
Damit betrachten wir zwei Funktionen `countWordFrequencies` bzw. `countWordFrequenciesCOW`:

```cpp
01: void TextfileStatistics::countWordFrequencies() {
02: 
03:     if (m_fileName.empty()) {
04:         std::println("No Filename specified!");
05:         return;
06:     }
07: 
08:     std::ifstream file{ m_fileName.data() };
09:     if (!file.good()) {
10:         std::println("File not found!");
11:         return;
12:     }
13: 
14:     std::println("File {}", m_fileName);
15:     std::println("[std::string] Starting ...");
16: 
17:     ScopedTimer watch{};
18: 
19:     std::unordered_map<std::string, std::size_t> frequenciesMap;
20: 
21:     std::string line;
22:     while (std::getline(file, line))
23:     {
24:         // process single line
25:         std::string_view sv{ line };
26: 
27:         std::size_t begin{};
28:         std::size_t end{};
29: 
30:         while (end != sv.size()) {
31: 
32:             while (std::isalpha(sv[end]))
33:                 ++end;
34: 
35:             std::string_view word{ sv.substr(begin, end - begin) };
36: 
37:             std::string s{ word };
38:             if (std::isupper(s[0])) {
39:                 s[0] = std::tolower(s[0]);
40:             }
41: 
42:             frequenciesMap[s]++;
43: 
44:             while (end != sv.size() && (sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
45:                 ++end;
46: 
47:             begin = end;
48:         }
49:     }
50: 
51:     auto pos = std::max_element(
52:         frequenciesMap.begin(),
53:         frequenciesMap.end(),
54:         [](const auto& a, const auto& b) {
55:             const auto& [word1, frequency1] = a;
56:             const auto& [word2, frequency2] = b;
57:             return frequency1 < frequency2;
58:         }
59:     );
60: 
61:     if (pos != frequenciesMap.end())
62:     {
63:         const auto& [word, frequency] = *pos;
64:         std::println("Largest frequency: {} - Word: {}", frequency, word);
65:     }
66: 
67:     std::println("Done.");
68: }
```

In der Methode `countWordFrequencies` treten `std::string`-Objekte in den Zeilen 19 und 37 auf,
das heißt sowohl beim Zerlegen einer Zeile in einzelne Wörter als auch bei der Ablage in einem `std::unordered_map<std::string, std::size_t>`-Objekt.

Nun bringen wir unsere `CowString`-Klasse ins Spiel, am Aufbau der `countWordFrequenciesCOW`-Methode ändert sich sonst recht wenig:

```cpp
01: void TextfileStatistics::countWordFrequenciesCOW() {
02: 
03:     using namespace COWString;
04: 
05:     if (m_fileName.empty()) {
06:         std::println("No Filename specified!");
07:         return;
08:     }
09: 
10:     std::ifstream file{ m_fileName.data() };
11:     if (!file.good()) {
12:         std::println("File not found!");
13:         return;
14:     }
15: 
16:     std::println("File {}", m_fileName);
17:     std::println("[CowString] Starting ...");
18: 
19:     ScopedTimer watch{};
20: 
21:     std::unordered_map<CowString, std::size_t> frequenciesMap;
22: 
23:     std::string line;
24:     while (std::getline(file, line))
25:     {
26:         // process single line
27:         std::string_view sv{ line };
28: 
29:         std::size_t begin{};
30:         std::size_t end{};
31: 
32:         while (end != sv.size()) {
33: 
34:             while (std::isalpha(sv[end]))
35:                 ++end;
36: 
37:             CowString cs{ &sv[begin], end - begin };
38: 
39:             // If it's an uppercase word, convert it
40:             // Note: This CowString currently has the state 'owning',
41:             // so a 'write' access does *not* copy the underling string
42:             if (std::isupper(cs[0])) {
43:                 cs[0] = std::tolower(cs[0]);
44:             }
45: 
46:             frequenciesMap[cs]++;
47: 
48:             while (end != sv.size() && (sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
49:                 ++end;
50: 
51:             begin = end;
52:         }
53:     }
54: 
55:     auto pos = std::max_element(
56:         frequenciesMap.begin(),
57:         frequenciesMap.end(),
58:         [](const auto& a, const auto& b) {
59:             const auto& [word1, frequency1] = a;
60:             const auto& [word2, frequency2] = b;
61:             return frequency1 < frequency2;
62:         }
63:     );
64: 
65:     if (pos != frequenciesMap.end())
66:     {
67:         const auto& [word, frequency] = *pos;
68:         std::println("Largest frequency: {} - Word: {}", frequency, word);
69:     }
70: 
71:     std::println("Done.");
72: }
```

Vorsicht, die Methode `countWordFrequenciesCOW` ist trotz ihrer starken Ähnlichkeit zur `countWordFrequencies`-Methode
nicht übersetzungsfähig! Was ist das Problem? 

Wir müssen bei Verwendung der `std::unordered_map`-Klasse behutsam vorgehen.
`std::unordered_map`-Objekte realisieren intern die Funktionalität einer *Hash*-Tabelle.
Damit müssen &ndash; zum Einfügen und Suchen &ndash; für die Schlüssel (*Keys*) Hash-Werte berechenbar sein.
Die Klasse `std::string` kann das, die Klasse `std::unordered_map<std::string, std::size_t>` ist folglich
problemlos übersetzungsfähig. 

Anders hingegen sieht es mit der Klasse `std::unordered_map<CowString, std::size_t>` aus.
Schlüssel vom Typ `CowString` sind machbar, aber die STL ist nicht in der Lage, ohne unser Zutun Hash-Werte von `CowString`-Objekten
zu berechnen.

Damit müssen wir kurz in den Namensraum `std` verzweigen und hier eine Spezialisierung für das Klassentemplate `hash`
ergänzen. Bei der Spezialisierung &bdquo;spezialisieren&rdquo; wir den Aufrufoperator `operator()`:

```cpp
01: namespace std
02: {
03:     using namespace COWString;
04: 
05:     template <>
06:     struct hash<CowString>
07:     {
08:         // Note: std::hash<const char*> hashes the pointer value, not the characters it points to
09:         // Workaround: let's use std::string_view
10: 
11:         std::size_t operator() (const CowString& cs) const {
12: 
13:             std::string_view sv{ cs };
14:             std::size_t h{ std::hash<std::string_view>{}(sv) };
15:             return h;
16:         }
17:     };
18: }
```

Eigentlich sollte die Realisierung einer benutzerdefinierten Hash-Funktion für `CowString`-Objekte kein Problem sein,
aber bei der Anfangsadresse der Zeichenkette vom Typ `const char*` stoßen wir auf ein weiteres Problem:

```
Note: std::hash<const char*> hashes the pointer value, not the characters it points to
```

Die Adresse selbst kann also nicht zur Berechnung des Hashwerts herangezogen werden.
Dafür werden wir bei der Klasse `std::string_view` fündig: Für sie gibt es eine Spezialisierung des `struct hash`-Klassentemplates,
wir bilden unser `CowString`-Objekt daher auf ein `std::string_view`-Objekt ab (Zeile 14) und verwenden diesen Wert.

Damit haben wir die letzte Hürde zur Realisierung der beiden Testmethoden
`countWordFrequencies` und `countWordFrequenciesCOW` genommen.
Wie sieht nun ein Vergleich der Laufzeiten aus?

```
File LoremIpsumVeryHuge.txt
[std::string] Starting ...
Largest frequency: 2053 - Word: famesnetussenectus
Done.
Elapsed time: 851 milliseconds.

File LoremIpsumVeryHuge.txt
[CowString] Starting ...
Largest frequency: 2053 - Word: famesnetussenectus
Done.
Elapsed time: 638 milliseconds.
```

Das sieht doch sehr interessant aus: 851 Millisekunden im Vergleich zu 638 Millisekunden.
Wir können tatsächlich die Beobachtung machen, dass die vielen Objektkopien bei Verwendung der `std::string`
stärker zu Buche schlagen also wenn wir auf die `CowString` zurückgreifen.
Das Ergebnis ermutigt uns, die &bdquo;*Copy-On-Write*&rdquo;-Kopierstrategie in adäquaten Anwendungen
stärker zu berücksichtigen.


## Fazit / Zusammenfassung

Die &bdquo;*Lazy Copy*&rdquo;- / &bdquo;*Copy-On-Write*&rdquo;-Kopierstrategie bedeutet,
dass beim Kopieren eines Objekts &bdquo;unter der Haube&rdquo; nur eine Adresse
auf die schon vorhandenen Daten des Objekts weitergereicht wird.
Eine echte und tiefe Kopie der eigentlichen Daten wird erst dann durchgeführt, wenn es sich nicht mehr vermeiden lässt,
zum Beispiel dann, wenn an einer Instanz Werte geändert werden.

Auf diese Weise entsteht für den Benutzer eines Objekts die Illusion,
dass es sich um zwei unabhängige Instanzen des Objekts handelt.

Hinter den Kulissen wird die Anzahl der Referenzen auf interne Datenstrukturen mitgezählt.
Das hat zur Folge, dass beim Verändern von Daten, die nur einmal referenziert werden,
keine separate Kopie notwendig ist und so Laufzeit eingespart werden kann.

COW-Zeichenketten eignen sich hervorragend, wenn

  * viele Kopien erstellt werden,
  * wenige Änderungen vorgenommen werden oder
  * eine effiziente Speichernutzung gewünscht ist

COW-Zeichenketten sind weniger geeignet, wenn

  * häufige Änderungen vorgenommen werden


## Literatur

Eine umfassende Einführung in das Thema &bdquo;*Copy-On-Write*&rdquo; findet man
in dem Artikel [`cow_ptr` &ndash; Der Smartpointer für Copy-On-Write](https://www.informatik-aktuell.de/entwicklung/programmiersprachen/cow-ptr-der-smartpointer-fuer-copy-on-write.html)
von Ralph Tandetzky. Die Quellen zu den Beispielen sind auf [GitHub](https://github.com/ralphtandetzky/cpp_utils) vorhanden.

In den WikiBooks findet man [hier](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-on-write) einen kurzen Überblick.

Die Realisierung der öffentlichen Schnittstelle der `CowString`-Klasse ist in dieser Fallstudie recht knapp ausgefallen.
Eine umfangreichere Realisierung einer &bdquo;*Copy-On-Write*&rdquo;-kompatiblen Klasse für Zeichenketten findet sich
[hier](https://github.com/allenvox/string-cow).


Wir auf die &bdquo;*Lorem Ipsum*&rdquo; generieren möchte,
findet [hier](https://www.lipsum.com) einen Online Generator.
Man muss nur die Anzahl der gewünschten Wörter eingeben, und schon kann
man den Text herunterladen.




<!-- End-of-File -->
