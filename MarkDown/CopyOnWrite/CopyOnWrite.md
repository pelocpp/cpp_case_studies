<!-- CopyOnWrite.md -->


# Copy on Write 

## Literatur

https://www.informatik-aktuell.de/entwicklung/programmiersprachen/cow-ptr-der-smartpointer-fuer-copy-on-write.html

https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-on-write

https://github.com/ralphtandetzky/cpp_utils

Noch eine String Implementierung:

https://github.com/allenvox/string-cow



Hmm, für den Text ?!?!?

https://stackoverflow.com/questions/1649028/how-to-implement-copy-on-write




## Kopieren auf eine andere Weise

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


## Unterschiedliche  Möglichkeiten des Kopierens von Objekten

Eine der häufigsten Operationen in einem Programm ist das Kopieren von Objekten.
Ein Objekt steht in objektorientierten Programmiersprachen für einen zusammengesetzter Datentyp.
Das Kopieren eines Objekts beschreibt daher den Vorgang, bei dem alle Attribute (Instanzvariablen) eines Objekts
in ein anderes Objekt desselben Datentyps kopiert werden.

Warum will man überhaupt ein Objekt kopieren? WEITER ......

Eine gute Frage ... und zu


Ein Objekt kann kopiert werden, um seine Daten ganz oder teilweise in einem neuen Kontext wiederzuverwenden.

#### Flache Kopie 

Eine flache Kopie eines Objekts kopiert alle Feldwerte. Dies funktioniert gut, wenn
die Felder Werte sind, ist aber möglicherweise nicht das, was Sie für Felder wünschen, die auf
dynamisch allokierten Speicher verweisen. Der Zeiger wird kopiert, aber der Speicher, auf den er verweist,
wird nicht kopiert – das Feld im Originalobjekt und in der Kopie verweist dann auf denselben
dynamisch allokierten Speicher, was in der Regel nicht gewünscht ist. Der
Standard-Kopierkonstruktor und der Standard-Zuweisungsoperator erstellen flache Kopien.

#### Tiefe Kopie

Eine tiefe Kopie kopiert alle Felder und erstellt Kopien des dynamisch allokierten Speichers, auf den die Felder verweisen.
Um eine tiefe Kopie zu erstellen, müssen Sie einen Kopierkonstruktor schreiben und den Zuweisungsoperator überladen, da die Kopie sonst auf das Original verweist, was katastrophale Folgen haben kann.

#### Lazy Copy

Eine Lazy Copy kombiniert die beiden oben genannten Strategien.
Beim ersten Kopieren eines Objekts wird eine (schnelle) flache Kopie erstellt.
Ein Zähler verfolgt, wie viele Objekte die Daten gemeinsam nutzen.

Wenn das Programm ein Objekt ändern möchte, kann es anhand des Zählers feststellen, ob die Daten gemeinsam genutzt werden,
und gegebenenfalls eine tiefe Kopie erstellen.
Lazy Copy verhält sich von außen wie eine tiefe Kopie, nutzt aber nach Möglichkeit die Geschwindigkeit einer flachen Kopie.

Der Nachteil sind die relativ hohen, aber konstanten Basiskosten aufgrund des Zählers.






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



