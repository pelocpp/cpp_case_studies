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

    std::string MorseCalculator::charToMorse(char ch) const
    {
        ch = std::toupper(ch);

        auto it = std::find_if(std::begin(m_alphabet), std::end(m_alphabet), [&](const auto& entry) {
            return entry.first == ch;
            }
        );

        return (it != std::end(m_alphabet)) ? std::string{ (*it).second } : std::string{};
    }

    char MorseCalculator::morseToChar(const std::string& morse) const
    {
        auto it = std::find_if(std::begin(m_alphabet), std::end(m_alphabet), [&](const auto& entry) {
            return entry.second == morse;
            }
        );

        return (it != std::end(m_alphabet)) ? (*it).first : '\0';
    }

    std::string MorseCalculator::encode(const std::string& message) const
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

        // remove last blank , if any
        if (result.size() != 0) {
            result.pop_back();
        }

        return result;
    }

    // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

    std::string MorseCalculator::decode(const std::string& message) const
    {
        std::string tmp{ message };
        char delimiter{ '/' };
        std::vector<std::string> words;
        std::string word;

        std::string result{};

        // splitting a stream with std::getline (delimiter needn't to be a white space)
        std::istringstream tokenStream(tmp);
        while (std::getline(tokenStream, word, delimiter)) {
            words.push_back(word);
        }

        std::for_each(std::begin(words), std::end(words), [&](const std::string& word) {
            // splitting a stream with STL iterator interface 
            std::istringstream iss(word);
            auto begin = std::istream_iterator<std::string>{ iss };
            auto end = std::istream_iterator<std::string>{};

            // constructs the container with the contents of the range
            std::vector<std::string> letters{ begin, end };

            std::for_each(std::begin(letters), std::end(letters), [&](std::string morse) {
                char ch{ morseToChar(morse) };
                result.push_back(ch);
                });
            });

        return result;
    }
}

void test_01()
{
    using namespace MorseExample;

    // small benchmark test
    std::string s{ "" };
    std::cout << s << std::endl;

    s.pop_back();
    std::cout << s << std::endl;
}

void test_02()
{
    using namespace MorseExample;

    // accessing a single entry of the morse alphabet table
    constexpr auto& entry = morseAlphabetTable[3];
    std::cout << entry.first << ", " << entry.second << std::endl;
}

void test_03()
{
    using namespace MorseExample;

    constexpr MorseCalculator calc;
    std::string text{ "C IS BEAUTIFUL" };
    std::string message = calc.encode(text);
    std::cout << "Result: " << message << std::endl;
}

void test_04()
{
    using namespace MorseExample;

    constexpr MorseCalculator calc;
    std::string message{
        "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / "
        "..-. --- -..- / .--- ..- -- .--. ... / --- ...- . .-. / "
        "- .... . / .-.. .- --.. -.-- / -.. --- --."
    };
    std::string text = calc.decode(message);
    std::cout << "Result: " << text << std::endl;
}

void test_05()
{
    using namespace MorseExample;

    constexpr MorseCalculator calc;

    // testing 'back and forth'
    std::string text{ "The quick brown fox jumps over the lazy dog" };
    std::cout << "Input: " << text << std::endl;
    std::string message = calc.encode(text);
    std::cout << "Morse message: " << message << std::endl;

    std::string original = calc.decode(message);
    std::cout << "Result: " << original << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
