// =====================================================================================
// MorseAlphabet.h
// =====================================================================================

#pragma once

// TODO: hmm, wie wäre es mit static ... alle Elemente dieser Klasse 


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
        std::string charToMorse(char ch) const;
        char morseToChar(const std::string& morse) const;

    public:
        std::string encode(const std::string& message) const;
        std::string decode(const std::string& message) const;
    };

}



// =====================================================================================
// End-of-File
// =====================================================================================