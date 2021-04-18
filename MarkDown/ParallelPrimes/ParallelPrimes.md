<!-- ParallelPrimes.md -->

<!-- Parallele Berechnung von Primzahlen mit Hindernissen -->

Die Suche nach Primzahlen &ndash; also Zahlen, die nur durch sich selbst und durch eins teilbar sind &ndash;  war lange Zeit
eine der zentralsten Bestandteile der Zahlentheorie. Primzahlenjäger können neben den zahlreichen Erkenntnissen
der Zahlentheoretiker heutzutage auf eine zusätzliche Hilfestellung zurückgreifen, den Computer.
Wir wollen im Folgenden ein Programm entwickeln, das mit Hilfe mehrerer Threads zu zwei fest gegebenen
natürlichen Zahlen *n* und *m* die Summe aller Primzahlen *p* mit *n* &leq; *p* &leq; *m* bestimmt.

<!--more-->

# Lernziele

  * Klasse `std::latch`
  * Atomare Operationen (`std::atomic<T>`)
  * Gegenseitiger Ausschluss (`std::mutex`)
  * `std::async` und `std::future<T>` in der Anwendung
  * STL-Algorithmen `std::swap` und `std::merge`
  * Bereichsbasierte `for`-Wiederholungsschleife (Range-based `for`-Loop)

# Einführung

Für die Identifizierung einer natürlichen Zahl als Primzahl benutzen wir das einfachste (und zugegeben auch langweiligste) Verfahren,
die Zahl &ndash; nennen wir sie *n* &ndash; der Reihe nach solange durch alle natürlichen Zahlen 2, 3, ... zu dividieren,
bis entweder eine Division den Rest 0 zurückliefert (und damit ein Primfaktor gefunden wurde)
oder aber der Dividend den Wert *n* annimmt. In diesem Fall besitzt die Zahl keine Primfaktoren, wir haben eine Primzahl gefunden.
Natürlich genügt es, *n* nur durch all die Zahlen zu dividieren, die kleiner oder gleich als die Quadratwurzel von *n* sind.

Zur Bestimmung der Primzahleigenschaft implementieren Sie eine statische Methode `isPrime`:

```cpp
static bool isPrime(size_t number);
```

`isPrime` liefert `true` zurück, wenn der aktuelle Parameter `number` prim ist, andernfalls `false`:
Das zentrale Anliegen der Anwendung besteht in der Verteilung der Primzahlenberechnungen auf mehrere Threads (Sekundärthreads).
Jeder dieser Sekundärthreads entnimmt aus einem zentralen Datenobjekt den nächsten Kandidaten,
der auf seine Primzahleigenschaft hin zu untersuchen ist.
Das zentrale Datenobjekt stellt sicher, dass unter keinen Umständen zwei Sekundärthreads dieselbe Zahl auf ihre Primzahleigenschaft untersuchen!

Im primären Thread der Anwendung finden nur verwaltungstechnische Tätigkeiten statt. Es werden also keine Primzahlen berechnet. Zu den Aufgaben des Primärthreads zählen:

  * Verwaltung einer unteren und oberen Grenze n bzw. m aller zu untersuchenden Zahlen mit *n* &leq; *m*.
  * Verwaltung der Anzahl der Sekundärthreads, die Primzahlen berechnen.
  * Anzeige der Anzahl der durch einen Sekundärthread gefundenen Primzahlen.
  * Anzeige der Anzahl aller gefundenen Primzahlen eines bestimmten Bereichs.

Ein Architekturbild zur Realisierung mit den zuvor skizzierten Realisierungsgedanken finden Sie in [Abbildung 1] vor.
Auf der rechten Seite ist das zentrale Datenobjekt dargestellt (Klasse `PrimeNumberCalculator`).
Mittels öffentlicher Eigenschaften lassen sich die obere und untere Grenze zum Suchen nach Primzahlen setzen.
Die private Instanzvariable `m_next` kann nur intern im Objekt benutzt werden – und
dies vorzugsweise nur von der öffentlichen Methode `calcPrimes`.

Auf der linken Seite erkennt man eine beliebige Anzahl von *n* Threads T<sub>1</sub>, ... T<sub>n</sub>, die jeder für sich mit Hilfe
der `calcPrimes`-Methode auf der Suche nach Primzahlen sind. In der Realisierung von `calcPrimes` muss sichergestellt sein,
dass zwei (quasi-)parallele Aufrufe von `calcPrimes` niemals dieselbe Zahl analysieren:

###### {#abbildung_1_application_overview}

{{< figure src="/img/parallelprimes/MultiThreadingPrimeCalculatorArchitecture.png" width="60%" >}}

*Abbildung* 1: Architektur einer parallelen Primzahlen-Anwendung.


Die Ausgabe der Anwendung könnte wie in [Abbildung 2] gezeigt aussehen.
Es sollten die IDs aller Threads ausgegeben werden, die sich an der Suche nach Primzahlen beteiligen &ndash;
und auch die Anzahl der gefundenen Primzahlen, die jeder Thread separat berechnet hat.
Die Summe aller Werte müsste dann den korrekten Summenwert aller Primzahlen in einem bestimmten Zahlenbereich widerspiegeln:

###### {#abbildung_2_parallelprimes_output_01}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="60%" >}}

*Abbildung* 2: Ausgabe der Ergebnisse in der Konsole.

Nach dem Start der Anwendung werden die Sekundärthreads erzeugt und gestartet.
Ist ein Sekundärthread mit der Berechnung der Primzahlen fertig, beendet er sich und zeigt die Anzahl der von ihm ermittelten Primzahlen
in der Konsole an. Sind alle Threads mit ihren Berechnungen fertig, wird in der letzten Zeile das Endergebnis,
also die Summe aller gefundenen Primzahlen, dargestellt.

In einer zweiten Variation der Anwendung werden die Primzahlen auch selbst ausgegeben, also nicht nur deren Anzahl.
Dies ist bei recht großen Zahlenbereichen etwas kritisch, da es dann sehr viele Primzahlen gibt.
In [Abbildung 3] finden Sie das Resultat aller Primzahlen im Bereich von 2 bis 1000 vor:

###### {#abbildung_3_parallelprimes_output_02}

{{< figure src="/img/parallelprimes/ParallelPrimesOutput01.png" width="60%" >}}

*Abbildung* 3: Ausgabe der Ergebnisse mit allen berechneten Primzahlen.

















// =====================================================================================


TODO: Beschreiben warum die Futures notwending sind !!!!!!!!!

// =====================================================================================


# Lösung

> Quellcode: Siehe auch [Github](https://github.com/pelocpp/cpp_case_studies.git).

## Klasse `CollatzIterator`

Kommen wir jetzt auf die Iterator-Klasse zu sprechen. Vom obigen Code-Fragment können wir ableiten, dass die folgenden drei Operatoren vorhanden sein müssen:

  * `operator*` &ndash; Dereferenzieren eines Iterator-Objekts (in Analogie zu einem C/C++&ndash;Zeiger).
  * `operator++` &ndash; Inkrementiert das Iterator-Objekt, damit dieses auf das nächste Element im Container verweist &ndash; es genügt die Präfix-Version des Operators.
  * `operator!=` &ndash; Überprüfung, ob die Wiederholungsschleife enden soll. Dies ist der Fall, wenn der Iterator dieselbe Position erreicht hat, die `end()` beschreibt.

*Hinweis*:
Mit diesen drei Operatoren lassen sich Iterator-Klassen implementieren,
die im Kontext einer bereichsbasierten `for`-Wiederholungsschleife einsetzbar sind.
Für andere STL-Algorithmen, wie zum Beispiel `std::find` oder `std::copy`, um nur zwei von ihnen exemplarisch zu nennen,
sind zusätzliche Klassenelemente notwendig. Wir werden an anderer Stelle darauf näher eingehen.

Wie lässt sich nun eine Zahlenfolge und das Iteratorkonzept von C++ miteinander verbinden?
In der Iteratorklasse ist die Realisierung in der Berechnung der Zahlenfolge unterzubringen.
Der `++`&ndash;Operator ist diejenige Stelle, an der von einem Folgenglied zum nächsten weitergegangen wird.
Mit dem `*`&ndash;Operator kann man auf das aktuelle Folgenglied zugreifen.
Die Bestimmung des Iterationsendes obliegt dem `!=`&ndash;Operator.

Instanzen der Iteratorklasse werden in der Regel von einer zweiten Klasse zur Verfügung gestellt, eben dem Container.
Diese Klasse nimmt typischerweise die Initialisierungswerte für die Zahlenfolge entgegen und belegt damit die Iteratorenobjekte vor.
Diese zweite Klasse &ndash; wir bezeichen sie als _Bereichs_&ndash; oder _Sequenzklasse_ &ndash; besitzt zwei Methoden `begin()` und `end()`,
die als Rückgabewert ein Iteratorobjekt für das erste Folgenglied bzw. das Ende der Auflistung repräsentieren.
Die Initialisierungswerte der Bereichsklasse gehen mehr oder weniger in die Iteratorenobjekt für Start und Ende der Zahlenfolge ein.

Genug der allgemeinen Theorie, lassen Sie uns einen Blick auf die Iteratorklasse `CollatzIterator`
zur Berechnung der teuflischen Folge werfen ([Listing 1]):

###### {#listing_01_collatziterator_interface}

```cpp
01: class CollatzIterator
02: {
03: public:
04:     using iterator_category = std::forward_iterator_tag;
05:     using value_type = int;
06:     using difference_type = int;
07:     using pointer = int*;
08:     using reference = int&;
09: 
10: private:
11:     int m_start{ 1 };
12:     int m_current{ 1 };
13:     int m_last{ };
14: 
15: public:
16:     // c'tors
17:     CollatzIterator() = default;
18:     CollatzIterator(int start);
19: 
20:     // operators
21:     int operator*() const;
22:     CollatzIterator& operator++();
23:     bool operator!=(const CollatzIterator&) const;
24: };
```

*Listing* 1: Klasse `CollatzIterator`: Definition.

[Listing 1] demonstriert einige Neuerungen von C++. Da wären zum Beispiel Initialisierer für Instanzvariablen (Zeilen 11 bis 13).
Mit ihrer Hilfe sollte es nicht mehr passieren, dass Instanzvariablen von Klassen ohne Vorbelegungswerte auftreten.
Dieses Feature hat zur Folge, dass man nicht mehr zwingend den Default-Konstruktor einer Klasse ausprogrammieren muss.
Mit der Kurzschreibweise in Zeile 17 ist erreicht, dass die Klasse einen Default-Konstruktor besitzt und die Instanzvariablen
auf Basis ihrer jeweiligen Initialisierer vorbelegt werden.
Die Zeilen 4 bis 8 bezeichnet man als *Iterator Traits* (zu Deutsch etwa *Iterator Spuren*),
sie sind wichtig für die Integration des Iterators in die STL.
Eine mögliche Realisierung der `CollatzIterator`-Klasse folgt in [Listing 2]:

###### {#listing_02_collatziterator_implementation}

```cpp
01: // c'tor
02: CollatzIterator::CollatzIterator(int start) : m_start{ start }, m_current{ start } {}
03: 
04: // operator(s)
05: int CollatzIterator::operator*() const { return m_current; }
06: 
07: CollatzIterator& CollatzIterator::operator++()
08: {
09:     m_current = (m_current % 2 == 0)
10:         ? m_current = m_current / 2
11:         : m_current = 3 * m_current + 1;
12: 
13:     return *this;
14: }
15: 
16: bool CollatzIterator::operator!=(const CollatzIterator& seq) const
17: { 
18:     return m_current != seq.m_current;
19: }
```

*Listing* 2: Klasse `CollatzIterator`: Implementierung.

## Klasse `CollatzSequence`

Nun benötigen wir noch eine Klasse für die Zahlenfolge, also die Containerklasse.
Im Wesentlichen legt sie nur den Startwert für die Folge fest
und stellt zwei Iteratorobjekte für Start und Ende der Zahlenfolge zur Verfügung ([Listing 3]):

###### {#listing_03_collatzsequence_interface}

```cpp
01: // forward declaration of iterator class
02: class CollatzIterator;
03: 
04: class CollatzSequence
05: {
06: private:
07:     int m_start{ 1 };
08: 
09: public:
10:     // c'tor(s)
11:     CollatzSequence() = default;
12:     CollatzSequence(int start);
13: 
14:     // iterator support
15:     CollatzIterator begin() const;
16:     CollatzIterator end()   const;
17: };
```

*Listing* 3: Klasse `CollatzSequence`: Definition.

Die `CollatzSequence`-Klassendefinition enthält keine Überraschungen bis auf eine Subtilität
in Bezug auf die beiden Klassen `CollatzIterator` und `CollatzSequence`,
die wir ansprechen müssen: Container- und Iteratorklassen sind &ndash; das liegt in der Natur der Sache &ndash; normalerweise
eng miteinander verknüpft:

  * Die Containerklasse muss die beiden Methoden `begin()` und `end()` implementieren. Diese beiden Methoden liefern Iteratorenobjekte zurück.
  * Ein Iteratorobjekt kennt in der Regel seine Containerklasse, folglich muss im Iteratorobjekt eine Referenz (bzw. eine Zeigervariable) auf den dazugehörigen Container vorhanden sein.

Diese Art des gegenseitigen Referenzierens hat zur Folge, dass wir den Container vor dem Iterator definieren müssen und umgekehrt.
Darüber hinaus benötigt der Iterator normalerweise Zugriff auf (private) Containermethoden und Datenelemente,
um seine Arbeit erledigen zu können.
Aus diesem Grund lautet das typische Muster zum Definieren von Container- und Iteratorklassen wie folgt:

  * Vorwärtsdeklaration der Iteratorklasse.
  * Definition (Implementierung) der Containerklasse.
  * Definition der Iteratorklasse als Freund (`friend`) in der Containerklasse.
  * Definition (Implementierung) der Iteratorklasse.

In unserem Anwendungsfall &ndash; Realisierung von Zahlenfolgen mit C++&ndash;Iteratoren &ndash; liegt der Iteration kein Container zugrunde.
Alle Informationen zu den iterierenden Werten residieren in der Iteratorklasse, die Containerklasse muss also keine `friend`-Deklaration der Iteratorklasse haben ([Listing 4]):

###### {#listing_04_collatzsequence_implementation}

```cpp
01: // c'tor(s)
02: CollatzSequence::CollatzSequence(int start) : m_start{ start } {}
03: 
04: // iterator support
05: CollatzIterator CollatzSequence::begin() const { return { m_start }; }
06: CollatzIterator CollatzSequence::end()   const { return { 1 }; }

```

*Listing* 4: Klasse `CollatzSequence`: Implementierung.

Das C++11&ndash;Sprachfeature der &ldquo;Uniform Initialization&rdquo; kann auch zusammen mit einer `return`-Anweisung auftreten.
Betrachten Sie die beiden Zeilen 5 und 6 von [Listing 4]. Es steht auf Grund der Definition
der Methoden `begin()` und `end()` fest, dass diese ein Objekt des Typs `CollatzIterator` zurückliefern müssen.
Wozu dann

```cpp
return { CollatzIterator { m_start } };
```

bzw.

```cpp
return { CollatzIterator { 1 } };
```

schreiben, wenn die Information des Klassentyps `CollatzIterator` überflüssig ist bzw. dem Compiler bekannt ist.
Nun können wir unsere erste teuflische Folge berechnen. Wir verzichten zunächst noch auf den Einsatz einer Containerklasse
und testen ausschließlich Iteratorobjekte:

```cpp
CollatzIterator iter{ 7 };
CollatzIterator end{ 1 };

while (iter != end) {
    std::cout << *iter << ' ';
    ++iter;
}
```

*Ausgabe*:

```
7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2
```

Wenn Sie die Ausgabe genau betrachten, können Sie einen kleinen Schönheitsfehler erkennen: Richtig erkannt, 
die Folge sollte den Wert 1 als letztes Element und nicht die 2 haben.
Dies ist nicht ganz trivial lösbar, aber wenn wir an zwei Stellen im Quellcode geschickt eingreifen, haben wir auch dieses Problem behoben:

  * Beobachtung 1: In der Festlegung des Ende-Iteratorobjekts sind wir ein wenig gekniffen: Der Wert 1 ist eigentlich der einzig mögliche Wert,
    der sich hier anbietet. Da er aber das Ende der Zahlenfolge ist, wird er von der Iteration ausgenommen, was wir vermeiden wollen.

  * Beobachtung 2: Des Rätsels Lösung liegt an einer ganz anderen Stelle in der Iteratorklasse verborgen: Es ist der `operator!=`, den wir in einer ersten Version
    seiner Realisierung etwas &ldquo;unterschätzt&rdquo; haben:  

    ```cpp
    bool CollatzIterator::operator!=(const CollatzIterator& seq) const
    { 
        return m_current != seq.m_current;
    }
    ```

    Vergleichen wir den Wert von `m_current` mit dem Wert `seq.m_current` eines anderen Iteratorobjekts, ist es eigentlich schon zu spät:
    Das Ende-Iteratorobjekt wartet hier mit dem Wert 1 auf, wir können das Element 1 in der Zahlenfolge so nicht mehr als gültigen Wert erklären.
    Wollten wir den Wert 1 mit in die Zahlenfolge aufnehmen, dürfen wir beim Vergleich nicht den aktuellen Wert vergleichen,
    sondern müssen hier quasi auf den Vorgänger von `m_current` zurückgreifen. Damit benötigen wir neben `m_current` noch eine zweite Instanzvariable `m_last`,
    die den Vorgänger von `m_current` repräsentiert.

  * Beobachtung 3: Für die beiden Operatoren `++` und `!=` benötigen wir eine geringfügig modifizierte Realisierung:

    ```cpp
    CollatzIterator& CollatzIterator::operator++()
    {
        m_last = m_current;
    
        m_current = (m_current % 2 == 0)
            ? m_current = m_current / 2
            : m_current = 3 * m_current + 1;
    
        return *this;
    }
    
    bool CollatzIterator::operator!=(const CollatzIterator& seq) const
    { 
        return m_last != seq.m_current;
    }
    ```

Wenn Sie diese Änderungen in der Implementierung der `CollatzIterator`-Klassen einbringen,
werden Sie in der Ausgabe die 1 als letztes Element der Zahlenfolge vorfinden!

Jetzt können wir eigentlich aus dem vollen Schöpfen und unsere Container- und Iteratorklasse gegen zahlreiche STL-Algorithmen testen.
Wir fangen mit einer bereichsbasierten `for`-Wiederholungsschleife an. Diese benötigt die Container-Klasse
unserer Realisierung (nicht die Iteratorklasse),
die jeweiligen Iteratorobjekte werden &ndash; für uns nicht sichtbar &ndash; durch Anweisungen angefordert,
die der Übersetzer generiert:

```cpp
CollatzSequence seq{ 17 };
for (int n : seq) {
    std::cout << n << ' ';
}
```

*Ausgabe*:

```
17 52 26 13 40 20 10 5 16 8 4 2 1
```

Die bereichsbasierte `for`-Wiederholungsschleife erwartet am Containerobjekt &ndash; hier: Klasse `CollatzSequence` &ndash; 
eine Implementierung der beiden Methoden `begin()` und `end()`. An den zurückgelieferten Objekten wiederum müssen die
drei Operatoren `operator++()`, `operator!=()` und `operator*()` vorhanden sein. Anderfalls wäre ein derartiges Code-Fragment nicht übersetzungsfähig.

Für die nachfolgenden Code-Fragmente muss die Iteratorklasse noch weitere Auskünfte bereitstellen.
Wir sind beim Themenkreis der so genannten &ldquo;Iterator Traits&rdquo; &ndash; zu Deutsch etwa &ldquo;Iterator Spuren&rdquo; &ndash; angekommen.
Die Anforderung lässt sich vergleichsweise einfach durch fünf `using`-Deklarationen erfüllen:

```cpp
using iterator_category = std::forward_iterator_tag;
using value_type = int;
using difference_type = int;
using pointer = int*;
using reference = int&;
```

## `CollatzIterator` und `CollatzSequence` im Zusammenspiel mit STL-Algorithmen

Wir stellen als Erstes eine Anwendung des `std::copy`-Algorithmus vor:

```cpp
CollatzSequence seq{ 17 };
std::ostream_iterator<int> out{ std::cout, "  " };
std::copy(std::begin(seq), std::end(seq), out);
```

*Ausgabe*:

```
17  52  26  13  40  20  10  5  16  8  4  2  1
```

Wollten wir die Summe aller Folgenglieder bestimmen, kann man den Algorithmus `std::accumulate` anwenden. 
Besitzt dieser keinen vierten Parameter und wird der dritte Parameter mit dem Wert 0 vorbelegt, erhalten wir die Summe
der Elemente in der Aufzählung zurück:

```cpp
CollatzSequence seq{ 17 };
int sum = std::accumulate(std::begin(seq), std::end(seq), 0);
std::cout << sum << std::endl;
```

*Ausgabe*:

```
214
```

Ist nicht die Summe, sondern die Anzahl der Folgenglieder gesucht, erhalten wir die Anwort von dem Algorithmus `std::distance`:

```cpp
CollatzSequence seq{ 17 };
int count = std::distance(std::begin(seq), std::end(seq));
std::cout << count << std::endl;
```

*Ausgabe*:

```
13
```

*Hinweis*:
Ohne eine entsprechenden Definition der &ldquo;Iterator Traits&rdquo; in der Klasse `CollatzIterator` ([Listing 1])
ist der Algorithmus-Aufruf `std::distance` nicht übersetzungsfähig! 
Die Fehlermeldung ist leider nicht einfach verständlich, bei genauem Hinsehen kann man erkennen,
dass die zum Zählen der Elemente notwendige Information des Abstands zweier Elemente fehlt:

```
Failed to specialize function template ... std::iterator_traits<remove_cv<remove_reference<_Ty>::type>::type>>::difference_type
```

Um einen Standard-Vektor (`std::vector<>`) mit den Elementen der Zahlenfolge zu füllen, 
bietet sich eine Kombination von `std::copy` mit `std::back_inserter` an:

```cpp
std::vector<int> numbers{ };
CollatzSequence seq{ 7 };
std::copy(std::begin(seq), std::end(seq), std::back_inserter(numbers));

for (int number : numbers) {
    std::cout << number << std::endl;
}
```

*Ausgabe*:

```
7
22
11
34
17
52
26
13
40
20
10
5
16
8
4
2
1
```

Die letzte Ausgabe können wir &ndash; im Kontext des `std::accumulate` Algorithmus &ndash; etwas umfangreicher gestalten.
Sie erinnnern sich: Das erste Mal hatten wir `std::accumulate` eingesetzt, um die Folgenglieder zu addieren.
Dieses Mal verwenden wir `std::accumulate`, um als Resultat eine Zeichenkette zu erzeugen, die die Folgenglieder nach gewissen Vorgaben weiterverarbeitet:

```cpp
CollatzSequence seq{ 7 };

std::string s = std::accumulate(
    std::begin(seq),
    std::end(seq),
    std::string(""), // first element
    [counter = 0] (const std::string& first, const auto& next) mutable {
        counter++;
        std::ostringstream ss;
        ss << "[" << std::setfill('0') << std::setw(2) << counter << "]"
            << ": " << std::setfill(' ') << std::setw(5)
            << std::right << next << std::endl;

        return first + ss.str();
    }
);

std::cout << s << std::endl;
```

*Ausgabe*:

```
[01]:     7
[02]:    22
[03]:    11
[04]:    34
[05]:    17
[06]:    52
[07]:    26
[08]:    13
[09]:    40
[10]:    20
[11]:    10
[12]:     5
[13]:    16
[14]:     8
[15]:     4
[16]:     2
[17]:     1
```

# There&lsquo;s more

In diesem Abschnitt bietet es sich an, eine Schwachstelle in der Definition der Iteratorklasse `CollatzIterator` zu beseitigen.
Nicht jede Zahlenfolge muss Elemente des Typs `int` haben, `long`, `short`, `__int64` etc. wären auch geeignetete Kandidaten.
Wir sind bei Templates angekommen: Eine Implementierung zweier Klassen `CollatzIteratorEx<T>` und `CollatzSequenceEx<T>`
finden Sie unter [Github](https://github.com/pelocpp/cpp_case_studies.git) vor.

# There&lsquo;s much more

In C++ 20 wird ein neues Sprachkonzept, genannt *Concepts* eingeführt, eine clevere Vorgehensweise,
um Restriktionen für Datentypen festzulegen, die eine Template-Funktion oder -klasse annehmen kann.
Während Iteratorkategorien und -eigenschaften gleich bleiben, ändert sich die Art und Weise, *wie* Sie diese erzwingen:
mit *Tags* bis C++ 17 (so wie wir es auch in dieser Fallstudie getan haben),
mit *Concepts*  in C++ 20.

Beispielsweise würden Sie anstelle des Tags `std::forward_iterator_tag` Ihren Iterator mit dem
`std::forward_iterator`-*Konzept* markieren. Dieser neue Mechanismus hilft dabei,
bessere Definitionen für Iteratoren zu erhalten
und Fehlermeldungen des Compilers werden besser lesbarer.

Im Augenblick ist die Umsetzung von *Concepts* und *Ranges* im Visual C++ Compiler noch nicht abgeschlossen,
so dass ich eine Aktualisierung dieses Artikels noch in die (nahe) Zukunft verschiebe.
Erste Schritte in diese Richtung werden vermutlich so aussehen, dass die Klasse `CollatzSequenceEx`
in einen *Range* bzw. in eine *View* umzusetzen ist. Dazu gibt es eine Hilfsklasse `std::ranges::view_interface`:

```cpp
template <class T>
class CollatzViewExEx : public std::ranges::view_interface<CollatzViewExEx<T>> {
public:
    CollatzViewExEx() = default;
    CollatzViewExEx(T start) : m_start(start), m_begin(start), m_end () {}

    auto begin() const { return m_begin; }
    auto end() const { return m_end; }

private:
    T m_start;

    CollatzIteratorEx<T> m_begin;
    CollatzIteratorEx<T> m_end;
};
```

Immerhin lässt sich mit diesem ersten kleinen Schritt bereits ein `CollatzViewExEx`-Objekt
mit einer bereichsbasierten `for`-Wiederholungsschleife traversieren:

```
CollatzViewExEx view{ 7 };
for (int n : view) {
    std::cout << n << " - ";
}
```

*Ausgabe*:

```
7 - 22 - 11 - 34 - 17 - 52 - 26 - 13 - 40 - 20 - 10 - 5 - 16 - 8 - 4 - 2 - 1 -
```

Sollten Sie mit den neuartigen C++ Konzepten bzgl. *Ranges* und *Concepts* (mit Visual C++)
bessere Fortschritte erzielen, würde ich mich über eine Nachricht freuen :-)

<!-- Links Definitions -->

[Listing 1]: #listing_01_ijosephus_interface
[Listing 2]: #listing_02_josephus_interface
[Listing 3]: #listing_03_josephus_implementation
[Listing 4]: #listing_04_josephusarrayimpl_interface
[Listing 5]: #listing_05_josephusarrayimpl_implementation
[Listing 6]: #listing_06_class_soldier
[Listing 7]: #listing_07_josephusforwardlistimpl_interface
[Listing 8]: #listing_08_josephusforwardlistimpl_implementation

[Abbildung 1]:  #abbildung_1_application_overview
[Abbildung 2]:  #abbildung_2_parallelprimes_output_01
[Abbildung 3]:  #abbildung_3_parallelprimes_output_02

<!-- End-of-File -->
