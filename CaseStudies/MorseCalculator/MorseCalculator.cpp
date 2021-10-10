// =====================================================================================
// MorseCalculator.cpp
// =====================================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <string_view>

#include "MorseCalculator.h"

namespace MorseExample {

    std::string MorseCalculator::charToMorse(char ch)
    {
        ch = std::toupper(ch);

        auto it = std::find_if(
            std::begin(m_alphabet),
            std::end(m_alphabet),
            [&](const auto& entry) {
                return entry.first == ch;
            }
        );

        return (it != std::end(m_alphabet))
            ? std::string{ (*it).second }
            : std::string{};
    }

    char MorseCalculator::morseToChar(const std::string& morse)
    {
        auto it = std::find_if(
            std::begin(m_alphabet), 
            std::end(m_alphabet),
            [&](const auto& entry) {
                return entry.second == morse;
            }
        );

        return (it != std::end(m_alphabet)) ? (*it).first : '\0';
    }

    std::string MorseCalculator::encode(const std::string& message)
    {
        std::string result;

        std::for_each(
            std::begin(message),
            std::end(message),
            [&](const char ch) {
                if (ch == ' ') {
                    result.push_back('/');
                }
                else {
                    std::string morse = charToMorse(ch);
                    result.append(morse);
                    result.push_back(' ');
                }
            }
        );

        return result;
    }

    std::string MorseCalculator::decode(const std::string& message)
    {
        std::string tmp{ message };
        char delimiter{ '/' };
        std::vector<std::string> words;
        std::string word;

        std::string result{};

        // splitting a stream with std::getline
        // (delimiter does't need to be a white space)
        std::istringstream tokenStream(tmp);
        while (std::getline(tokenStream, word, delimiter)) {
            words.push_back(word);
        }

        std::for_each(
            std::begin(words), 
            std::end(words),
            [&](const std::string& word) {
                // splitting a stream with STL iterator interface 
                std::istringstream iss(word);
                auto begin = std::istream_iterator<std::string>{ iss };
                auto end = std::istream_iterator<std::string>{};

                // constructs the container with the contents of the range
                std::vector<std::string> letters{ begin, end };

                std::for_each(
                    std::begin(letters),
                    std::end(letters), 
                    [&](std::string morse) {
                        char ch{ morseToChar(morse) };
                        result.push_back(ch);
                    }
                );

                result.push_back(' ');
            }
        );

        return result;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
