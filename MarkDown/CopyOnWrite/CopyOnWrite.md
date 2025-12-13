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

Eine flache Kopie eines Objekts kopiert alle Instanzvariablen bitweise. Dies funktioniert problemlos,
solange die Variablen Werte elementaren Datentyps sind.
In *Abbildung* 1 finden Sie ein Objekt einer Klasse `Date` dargestellt vor:

```cpp
class Date
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

*Abbildung* 1: Zwei Objekte des Typs `Date`: Ein Original und eine Kopie.


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

*Abbildung* 2: Zwei Objekte des Typs `Date`: Ein Original und eine Kopie.

Um zu einer korrekten Kopie zu gelangen, benötigen wir die Vorgehensweise der &bdquo;tiefen Kopie&rdquo;
Eine tiefe Kopie kopiert alle Felder und erstellt Kopien des dynamisch allokierten Speichers, auf den die Felder verweisen
(*Abbildung* 3)

<img src="copy_on_write_03.svg" width="600">

*Abbildung* 3: Zwei Objekte des Typs `Date`: Ein Original und eine Kopie &ndash; mit Schwachstellen.

Um eine tiefe Kopie zu erstellen, müssen Sie einen Kopierkonstruktor schreiben und den Zuweisungsoperator überladen
und wie beschrieben implementieren.
Der automtisch erzeugten Standard-Kopierkonstruktor und der Zuweisungsoperator erzeugen flache Kopien.



#### Lazy Copy

Interessanterweise gibt es neben diesen beiden Kopierstrategien noch eine dritte Strategie,
die so genannte &bdquo;*Lazy Copy*&rdquo;-Strategie, oder auch also &bdquo;*Copy-on-Write*&rdquo; (*COW*) bezeichnet.

Die &bdquo;*Lazy Copy*&rdquo;-Strategie kombiniert die beiden oben zuvor beschriebenen Strategien.

Bei dieser Vorgehensweise benötigen wir zusätzlich zum eigentlichen Objekt ein Hüllenobjekt,
häufig als `COW_Ptr` bezeichnet. Dieses verwaltet neben den Daten des eigentlichen Objekts
eine (atomare) Zählervariable.

Wird dieses Objekt zum ersten Mal kopiert, wird *keine* tiefe Kopie angelegt.
Es wird stattdessen nur die Zählervariable inkrementiert.
Das kopierte Objekt greift auf dieselben Daten wie das Originalobjekt zu.
Solange an einem der beteiligten Objekte keine Änderung erfolgt, funktioniert dieser Ansatz.
Eine Zählervariable verfolgt, wie viele Objekte die Daten gemeinsam nutzen.

Wenn das Programm ein Objekt ändern möchte, kann es anhand des Zählers feststellen, ob die Daten gemeinsam genutzt werden.
Wenn ja, dann ist &ndash; zu diesem Zeitpunkt, also *on demand* &ndash; eine tiefe Kopie zu erstellen.

*Bemerkung*:<br />
Die Klasse `std::shared_ptr` und eine &bdquo;*Copy-on-Write*&rdquo;-Klasse weisen gewisse Ähnlichkeiten auf.
Beide Klassen verwenden Referenzzähler, die den geteilten Besitz zählen.

Man kann sagen, dass die *Lazy Copy*-Strategie sich von außen wie eine tiefe Kopie darstellt,
intern aber, soweit möglich, das Prinzip einer flachen Kopie anstrebt.
Erst wenn es zu Änderungen (schreibender Zugriff) an einem der beteiligten Objekte kommt,
ist eine echte (tiefe) Kopie zu erstellen.


## Erster Entwurf einer einfachen &bdquo;*Copy-on-Write*&rdquo;-Klasse für Zeichenketten




## &bdquo;*Copy-on-Write*&rdquo;-Klassen und die STL-Klasse `std::string`

Häufig wird die Frage gestellt, warum die Klasse `std::string` aus der STL nicht das &bdquo;*Copy-on-Write*&rdquo;-Idiom
umsetzt. Die Antwort ist vergleichsweise einfach: 
Die `std::string`-Klasse besitzt ein historisch gewachsenenes API, das für das &bdquo;*Copy-on-Write*&rdquo;-Idiom 
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
Nur sind wir bei diesem Ansatz mit dem Problem konfrontiert, dass wir innerhalb der `std::string`-Klasse
nicht erkennen können, ob diese Referenz nur lesend oder auch schreibend verwendet wird.

Man könnte natürlich &ndash; aus Sicht des &bdquo;*Copy-on-Write*&rdquo;-Idioms den Worst-Case
eines Schreibens zugrunde legen, nur wäre dies ein pessimistischer Ansatz,
der nicht zu einer praktibalen Realisierung führt.

Wenn wir eine Klasse für Zeichenketten inklusive des &bdquo;*Copy-on-Write*&rdquo;-Idioms realisieren wollen,
dann müsste man die öffentliche Schnittstelle auch anpassen.
Zum Beispiel, dass die Mehrzahl der Methoden einen lesenden Zugriff umsetzt.
Und die wenigen schreibenden Zugriffe auch klar dokumentieren, dass es hier hinter den Kuluissen
zu einer tiefen Objektkopie kommt.



## Entwurf der Pimpl-Klasse

Eine COW-Zeichenkettenklasse oder auch Implementierungen anderer COW-konformer Datenstrukturen
benötigen eine interne Hilfsklasse zur Speicherung eines aktuellen Zustands.

Das Problem, mit dem wir konfrontiert sind, könnte man formulieren als

Wir definiert man einen Struktur, gefolgt von manuell zugewiesenem „nachgelagertem Speicher“.

Nicht übersetzungsfähig sind Strukturen der Art

```cpp
struct Data
{
    size_t m;
    size_t m1;
    char trailing[];
}
```

Man geht tyischerweise wie folgt vor:


```cpp
struct Data
{
    size_t m1;
    size_t m2;
    // no flexible sized array
}
```

Instanzen einer `Data`-Struktur werden so angelegt:

```
Data* makeData(std::size_t payloadSize)
{
    void* mem = ::operator new (sizeof(Data) + payloadSize);
    return new (mem) Data{};
}
```

Mit dem Operator `::operator new` wird Speicher reserviert und sonst nichts weiter.
Es erfolgt keine Iniialisierung bzw. Vorbelegung des reservierten Speichers.

Diese erfolgt &ndash; im skizzierten Beispiel  &ndash; mit dem so genannten Placement new:
Der Aufruf des Standardkonstruktors (`Data{}`) wird aufd dem reservierten Speicher angewendet.

Offen ist, wie auf den zusätzlich vorhandenen Speicher im Anschluss an das `struct Data`-Objekts zugegriffen
werden kann. Dies erfolgt mit klassischen C/C++-Sprachmitteln wir `reinterpret_cast` und Zeigerarithmetik:

```cpp
Data* d = makeData(10);
char* payload = reinterpret_cast<char*>(data) + sizeof(Data);
// 10 bytes past 'payload' pointer available
```



