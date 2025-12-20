#include <iostream> // Für Ein- und Ausgabe (cout)
#include <string>   // Für std::string
#include <vector>   // Für std::vector
#include <sstream>  // Für std::stringstream zum Zerlegen des Textes
#include <algorithm> // Für std::sort

// Oder auch:

// string_view
// https://www.modernescpp.com/index.php/c-17-avoid-copying-with-std-string-view/

int main() {
    std::string text = "Dies ist ein Beispieltext, um Woerter nach Laenge zu sortieren";
    std::vector<std::string> woerter;
    std::stringstream ss(text); // Stringstream erstellen, um Text zu verarbeiten
    std::string wort;

    // 1. Wörter auslesen
    // Der >> Operator liest bis zum nächsten Leerzeichen
    while (ss >> wort) {
        woerter.push_back(wort); // Wort zum Vektor hinzufügen
    }

    // 2. Wörter nach Länge sortieren
    // std::sort mit einem Lambda-Ausdruck als Vergleichsfunktion
    std::sort(woerter.begin(), woerter.end(), [](const std::string& a, const std::string& b) {
        return a.length() < b.length(); // Sortiert aufsteigend nach Länge
        });

    // 3. Sortierte Wörter ausgeben
    std::cout << "Woerter nach Laenge sortiert:" << std::endl;
    for (const std::string& w : woerter) {
        std::cout << w << " (Laenge: " << w.length() << ")" << std::endl;
    }

    return 0;
}
