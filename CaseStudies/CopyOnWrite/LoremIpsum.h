// =====================================================================================
// LoremIpsum.h // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#pragma once

#include <random>       // std::random_device, std::mt19937, std::uniform_int_distribution
#include <string_view>  // std::string_view
#include <vector>       // std:.vector

class LoremIpsum
{
public:
    LoremIpsum();

private:
    std::mt19937                  m_mt;  // pseudo-random generator (so called Mersenne Twister 19937)

    // using a pseudo-random generator (so called Mersenne Twister 19937)
    //auto rd{ std::random_device{} };
    //auto gen{ std::mt19937{ rd() } };

    std::vector<std::string_view> m_originalWords;
    std::vector<std::string_view> m_longWords;

public:

    std::string generateWord          ();
    std::string generateSentence      (int minNumWords = 4, int maxNumWords = 12);
    std::string generateParagraph     (int minNumSentences = 5, int maxNumSentences = 8, int minNumWords = 4, int maxNumWords = 12);
    std::string generateParagraphList (int paraCount = 5, int minSent = 5, int maxSent = 8, int minWord = 4, int maxWord = 12);

    void generateLoremIpsum           (std::string_view fileName);

    enum class Mode { STDOUT, FILE };


};

// =====================================================================================
// End-of-File
// =====================================================================================
