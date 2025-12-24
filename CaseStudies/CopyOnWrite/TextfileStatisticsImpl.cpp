// =====================================================================================
// TextfileStatisticsImpl.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "../ScopedTimer.h"

#include "CowString.h"
#include "TextfileStatistics.h"

#include <cctype>          // std::toupper
#include <cstddef>         // std::size_t
#include <fstream>         // std::ifstream
#include <print>           // std::println
#include <queue>           // std::priority_queue
#include <string>          // std::string
#include <string_view>     // std::string_view
#include <unordered_map>   // std::unordered_map
#include <vector>          // std::vector

// c'tor
TextfileStatistics::TextfileStatistics()
    : m_fileName{}
{
}

// getter / setter
void TextfileStatistics::setFilename(std::string_view fileName) {
    m_fileName = fileName;
}

std::string_view TextfileStatistics::getFilename() {
    return m_fileName;
}

// public interface
void TextfileStatistics::countWordFrequencies() {

    if (m_fileName.empty()) {
        std::println("No Filename specified!");
        return;
    }

    std::ifstream file{ m_fileName.data() };
    if (!file.good()) {
        std::println("File not found!");
        return;
    }

    std::println("File {}", m_fileName);
    std::println("[std::string] Starting ...");

    ScopedTimer watch{};

    std::unordered_map<std::string, std::size_t> frequenciesMap;

    std::string line;
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

void TextfileStatistics::countWordFrequenciesCOW() {

    using namespace COWString;

    if (m_fileName.empty()) {
        std::println("No Filename specified!");
        return;
    }

    std::ifstream file{ m_fileName.data() };
    if (!file.good()) {
        std::println("File not found!");
        return;
    }

    std::println("File {}", m_fileName);
    std::println("[CowString] Starting ...");

    ScopedTimer watch{};

    std::unordered_map<CowString, std::size_t> frequenciesMap;

    std::string line;
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
            // so a 'write' access does *not* copy the underling string
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

void TextfileStatistics::computeMostFrequentWords() {

    if (m_fileName.empty()) {
        std::println("No Filename specified!");
        return;
    }

    std::ifstream file{ m_fileName.data() };
    if (!file.good()) {
        std::println("File not found!");
        return;
    }

    std::println("File {}", m_fileName);
    std::println("[std::string] Starting ...");

    ScopedTimer watch{};

    std::unordered_map<std::string, std::size_t> frequenciesMap;

    std::string line;
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

            frequenciesMap[s]++;

            while (end != sv.size() && (sv[end] == ' ' || sv[end] == '.' || sv[end] == ','))
                ++end;

            begin = end;
        }
    }
    std::println("Done Creating Dictionary");

    using Entry = std::pair<std::size_t, std::string>;

    auto cmp = [](const Entry& a, const Entry& b) {
        return a.first > b.first; // min-heap
        };

    std::priority_queue<Entry, std::vector<Entry>, decltype(cmp)> top10(cmp);

    for (const auto& [key, value] : frequenciesMap) {

        if (top10.size() < 10) {
            top10.emplace(value, key);
        }
        else if (value > top10.top().first) {
            top10.pop();
            top10.emplace(value, key);
        }
    }

    // output results (largest last ==> reverse if needed)
    while (!top10.empty()) {
      //  std::cout << top10.top().second << ": " << top10.top().first << '\n';

        std::println("{}: {}", top10.top().second, top10.top().first);

        top10.pop();
    }

    std::println("Done.");
}

void TextfileStatistics::computeMostFrequentWordsCOW() {
}

// =====================================================================================
// End-of-File
// =====================================================================================
