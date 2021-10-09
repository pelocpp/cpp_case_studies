// =====================================================================================
// MorseAlphabet.h
// =====================================================================================

#pragma once

namespace MorseExample {

    using namespace std::literals::string_view_literals;

    using MorseAlphabet = std::array<std::pair<char, std::string_view>, 26>;

    class MorseCalculator
    {
    public:
        static std::string encode(const std::string& message);
        static std::string decode(const std::string& message);

    private:
        static std::string charToMorse(char ch);
        static char morseToChar(const std::string& morse);

        static constexpr MorseAlphabet m_alphabet
        { {
            { 'A', ".-"sv },   { 'B', "-..."sv },
            { 'C', "-.-."sv }, { 'D', "-.."sv },
            { 'E', "."sv },    { 'F', "..-."sv },
            { 'G', "--."sv },  { 'H', "...."sv },
            { 'I', ".."sv },   { 'J', ".---"sv },
            { 'K', "-.-"sv },  { 'L', ".-.."sv },
            { 'M', "--"sv },   { 'N', "-."sv },
            { 'O', "---"sv },  { 'P', ".--."sv },
            { 'Q', "--.-"sv }, { 'R', ".-."sv },
            { 'S', "..."sv },  { 'T', "-"sv },
            { 'U', "..-"sv },  { 'V', "...-"sv },
            { 'W', ".--"sv },  { 'X', "-..-"sv },
            { 'Y', "-.--"sv }, { 'Z', "--.."sv },
        } } ;

    public:
        static inline constexpr size_t size ()
        {
            return m_alphabet.size();
        }

        static inline constexpr std::pair<char, std::string_view> getEntry (const int index)
        {
            return m_alphabet[index];
        }

        template <int INDEX>
        static inline constexpr std::pair<char, std::string_view> getEntry()
        {
            return m_alphabet[INDEX];
        };
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================