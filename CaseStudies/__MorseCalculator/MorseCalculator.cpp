// =====================================================================================
// MorseAlphabet.cpp
// =====================================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <string_view>

namespace MorseExample {

    using MorseAlphabet = std::array<std::pair<char, std::string_view>, 26>;

    constexpr auto morseAlphabetTable = [] {

        using namespace std::literals::string_view_literals;

        MorseAlphabet alphabet{};

        alphabet[0] = { 'A', ".-"sv };
        alphabet[1] = { 'B', "-..."sv };
        alphabet[2] = { 'C', "-.-."sv };
        alphabet[3] = { 'D', "-.."sv };
        alphabet[4] = { 'E', "."sv };
        alphabet[5] = { 'F', "..-."sv };
        alphabet[6] = { 'G', "--."sv };
        alphabet[7] = { 'H', "...."sv };
        alphabet[8] = { 'I', ".."sv };
        alphabet[9] = { 'J', ".---"sv };
        alphabet[10] = { 'K', "-.-"sv };
        alphabet[11] = { 'L', ".-.."sv };
        alphabet[12] = { 'M', "--"sv };
        alphabet[13] = { 'N', "-."sv };
        alphabet[14] = { 'O', "---"sv };
        alphabet[15] = { 'P', ".--."sv };
        alphabet[16] = { 'Q', "--.-"sv };
        alphabet[17] = { 'R', ".-."sv };
        alphabet[18] = { 'S', "..."sv };
        alphabet[19] = { 'T', "-"sv };
        alphabet[20] = { 'U', "..-"sv };
        alphabet[21] = { 'V', "...-"sv };
        alphabet[22] = { 'W', ".--"sv };
        alphabet[23] = { 'X', "-..-"sv };
        alphabet[24] = { 'Y', "-.--"sv };
        alphabet[25] = { 'Z', "--.."sv };

        return alphabet;
    } ();

    class MorseCalculator
    {
    private:
        MorseAlphabet m_alphabet;

    public:
        // c'tors
        constexpr MorseCalculator() : m_alphabet{ morseAlphabetTable } {}

    private:
        std::string charToMorse(char ch) const
        {
            ch = std::toupper(ch);

            auto it = std::find_if(std::begin(m_alphabet), std::end(m_alphabet), [&](const auto& entry) {
                return entry.first == ch;
                }
            );

            return (it != std::end(m_alphabet)) ? std::string{ (*it).second } : std::string{};
        }

        char morseToChar(const std::string& morse) const
        {
            auto it = std::find_if(std::begin(m_alphabet), std::end(m_alphabet), [&](const auto& entry) {
                return entry.second == morse;
                }
            );

            return (it != std::end(m_alphabet)) ? (*it).first : '\0';
        }

    public:
        std::string encode(const std::string& message) const
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

        std::string decode(const std::string& message) const
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
    };

    void test_023_x()
    {
        // small benchmark test
        std::string s{ "" };
        std::cout << s << std::endl;

        s.pop_back();
        std::cout << s << std::endl;
    }

    void test_023_a()
    {
        // accessing a single entry of the morse alphabet table
        constexpr auto& entry = morseAlphabetTable[3];
        std::cout << entry.first << ", " << entry.second << std::endl;
    }

    void test_023_b()
    {
        constexpr MorseCalculator calc;
        std::string text{ "C IS BEAUTIFUL" };
        std::string message = calc.encode(text);
        std::cout << "Result: " << message << std::endl;
    }

    void test_023_c()
    {
        constexpr MorseCalculator calc;
        std::string message{
            "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / "
            "..-. --- -..- / .--- ..- -- .--. ... / --- ...- . .-. / "
            "- .... . / .-.. .- --.. -.-- / -.. --- --."
        };
        std::string text = calc.decode(message);
        std::cout << "Result: " << text << std::endl;
    }

    void test_023_d()
    {
        constexpr MorseCalculator calc;

        // testing 'back and forth'
        std::string text{ "The quick brown fox jumps over the lazy dog" };
        std::cout << "Input: " << text << std::endl;
        std::string message = calc.encode(text);
        std::cout << "Morse message: " << message << std::endl;

        std::string original = calc.decode(message);
        std::cout << "Result: " << original << std::endl;
    }
}

void test_23()
{
    using namespace MorseExample;
    test_023_a();
    test_023_b();
    test_023_c();
    test_023_d();
}

// =========================================================

// =====================================================================================
// End-of-File
// =====================================================================================
