// =====================================================================================
// FrequencyCount.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "../ScopedTimer.h"

#include "CowString.h"

#include <algorithm>       // std::max_element
#include <fstream>         // std::ifstream
#include <iostream>        // inout/output
#include <print>           // std::println
#include <sstream>         // std::stringstream
#include <string>          // std::string
#include <string_view>     // std::string_view
#include <unordered_map>   // std::unordered_map
#include <vector>          // std::vector
#include <cctype>          // std::isalpha, std::isupper, std::tolower

static void test_frequency_count_01() 
{
    std::string text = "Dies ist ein Beispieltext, um Woerter nach Laenge zu sortieren";
    std::vector<std::string> woerter;
    std::stringstream ss(text);  // Stringstream erstellen, um Text zu verarbeiten
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
}

static void test_frequency_count_02()
{
    std::ifstream file{ "LoremIpsum.txt" };
    std::string line;

    while (std::getline(file, line))
    {
        // process single line
        std::println(">>> {}", line);

        std::stringstream ss{ line };
        std::string word;
        while (ss >> word) {
            std::println("   ###  {}", word);
        }
    }
}

static void test_frequency_count_03()
{
    std::ifstream file{ "LoremIpsum.txt" };
    std::string line;

    std::unordered_map<std::string, std::size_t> frequenciesMap;

    while (std::getline(file, line))
    {
        // process single line
        std::println(">>> {}", line);

        std::stringstream ss{ line };
        std::string word;
        while (ss >> word) {
            std::println("   ###  {}", word);

            frequenciesMap[word]++; // If word does not exist, it is automatically inserted with value 0.
        }
    }
}

static void test_frequency_count_04()
{
    std::ifstream file{ "LoremIpsum.txt" };
    std::string line;

    while (std::getline(file, line))
    {
        // process single line
        std::println(">>> {}", line);

        std::string_view sv{ line };

        std::size_t begin{};
        std::size_t end{};

        while (end != sv.size()) {

            while (  std::isalpha(sv[end]))
                ++end;

            std::string_view word{ sv.substr (begin, end - begin)};
            std::println("    ??? {}", word);

            while (end != sv.size() && ( sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
                ++end;

            begin = end;
        }
    }
}

static void test_frequency_count_05()
{
    // std::string_view fileName{ "LoremIpsumLarge.txt" };
    // std::string_view fileName{ "LoremIpsumHuge.txt" };
    std::string_view fileName{ "LoremIpsumVeryHuge.txt" };

    std::ifstream file{ fileName.data()};

    if (!file.good()) {
        std::println("File not found!");
        return;
    }

    std::string line;

    std::println("File {}", fileName);
    std::println("Starting ...");

    std::unordered_map<std::string, std::size_t> frequenciesMap;

    ScopedTimer watch{};

    while (std::getline(file, line))
    {
        // process single line
        std::string_view sv{ line };

        std::size_t begin{};
        std::size_t end{};

        while (end != sv.size()) {

            while (std::isalpha(sv[end]))
                ++end;

            std::string_view word{ sv.substr(begin, end - begin) };

            std::string s{ word };
            if (std::isupper(s[0])) {
                s[0] = std::tolower(s[0]);
            }

            // if word does not exist, it is automatically inserted with value 0
            frequenciesMap[s]++;

            while (end != sv.size() && (sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
                ++end;

            begin = end;
        }
    }
    std::println("Done Creating Dictionary");

    auto pos = std::max_element(
        frequenciesMap.begin(),
        frequenciesMap.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );

    if (pos != frequenciesMap.end())
    {
        const auto& [word, frequency] = *pos;
        std::println("Largest frequency: {} - Word: {}", frequency, word);
    }

    std::println("Done.");
}


static void test_frequency_count_06()
{
    using namespace CowStringSimple;

    // std::string_view fileName{ "LoremIpsumLarge.txt" };
    // std::string_view fileName{ "LoremIpsumHuge.txt" };
    std::string_view fileName{ "LoremIpsumVeryHuge.txt" };

    std::ifstream file{ fileName.data() };

    if (!file.good()) {
        std::println("File not found!");
        return;
    }

    std::string line;

    std::println("File {}", fileName);
    std::println("Starting ...");

    std::unordered_map<CowString, std::size_t> frequenciesMap;

    ScopedTimer watch{};

    while (std::getline(file, line))
    {
        // process single line
        std::string_view sv{ line };

        std::size_t begin{};
        std::size_t end{};

        while (end != sv.size()) {

            while (std::isalpha(sv[end]))
                ++end;

            CowString cs{ &sv[begin], end - begin };

            // If it's an uppercase word, convert it
            // Note: This CowString currently has the state 'owning',
            // so this 'write' access does *copy* the underling string
            if (std::isupper(cs[0])) {
                cs[0] = std::tolower(cs[0]);
            }

            // if word does not exist, it is automatically inserted with value 0
            frequenciesMap[cs]++;

            while (end != sv.size() && (sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
                ++end;

            begin = end;
        }
    }
    std::println("Done Creating Dictionary");

    auto pos = std::max_element(
        frequenciesMap.begin(),
        frequenciesMap.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    );

    if (pos != frequenciesMap.end())
    {
        const auto& [word, frequency] = *pos;
        std::println("Largest frequency: {} - Word: {}", frequency, word.c_str());
    }

    std::println("Done.");
}

void test_frequency_count()
{
    //test_frequency_count_01();
    // test_frequency_count_02();
    // test_frequency_count_03();
    //test_frequency_count_04();

    test_frequency_count_05();
    std::println();
    std::println();
    test_frequency_count_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================

