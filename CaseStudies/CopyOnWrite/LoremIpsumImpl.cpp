// =====================================================================================
// LoremIpsumImpl.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "LoremIpsum.h"

#include <algorithm>    // std::generate
#include <cstddef>      // std::size_t
#include <numeric>      // std::accumulate
//#include <print>        // std::println
//#include <random>       // std::random_device, std::mt19937, std::uniform_int_distribution
#include <string>       // std::string
#include <string_view>  // std::string_view
#include <vector>       // std:.vector

LoremIpsum::LoremIpsum()
    : m_originalWords {}, m_longWords{}
{
    m_mt = std::mt19937{ std::random_device{} () };

    m_originalWords = 
    {
#include "LoremIpsumOriginalWords.inl"
    };
}

// generates a random word
std::string LoremIpsum::generateWord()
{

    // using a pseudo-random generator (so called Mersenne Twister 19937)
    //static auto rd{ std::random_device{} };
    //static auto gen{ std::mt19937{ rd() } };

    // create random integer value i, uniformly distributed between 0 and max
    auto max{ static_cast<int>(m_originalWords.size()) - 1 };
    auto dist{ std::uniform_int_distribution<int>(0, max) };
    auto index{ dist(m_mt) };

    // retrieve word from list of existing words
    auto word{ m_originalWords.at(index) };
    std::string s{ word };
    return s;
}

// generate a random sentence
std::string LoremIpsum::generateSentence(int minNumWords, int maxNumWords)
{
    // using a pseudo-random generator (so called Mersenne Twister 19937)
    //static auto rd{ std::random_device{} };
    //static auto gen{ std::mt19937{ rd() } };

    // create random integer value numWords,
    // uniformly distributed between minNumWords and maxNumWords
    auto dist{ std::uniform_int_distribution<int>(minNumWords, maxNumWords) };
    int numWords{ dist(m_mt) };

    std::vector<std::string> words;
    words.resize(numWords);

    // create vector of words from list of existing words
    std::generate(
        words.begin(),
        words.end(),
        [this]() {
            return generateWord();
        }
    );

    // include a comma for better readability :)
    bool includecomma{ (numWords >= (maxNumWords * 4) / 5) };

    // create a sentence of these words
    std::string sentence{ std::accumulate(
        words.begin(),
        words.end(),
        std::string{},
        [&, i = 0](const std::string a, const std::string& next) mutable {

            std::string result{ a };
            result += next;

            if (includecomma && i == (numWords / 2) - 1) {
                result += ",";
            }
            if (i != numWords - 1) {
                result += " ";
            }
            ++i;
            return result;
        }
    ) };

    sentence += ".";
    sentence.at(0) = std::toupper(sentence.at(0));
    return sentence;
}

std::string LoremIpsum::generateParagraph(int minNumSentences, int maxNumSentences, int minNumWords, int maxNumWords)
{
    // using a pseudo-random generator (so called Mersenne Twister 19937)
    //static auto rd{ std::random_device{} };
    //static auto gen{ std::mt19937{ rd() } };

    // create random integer value numWords,
    // uniformly distributed between minNumSentences and maxNumSentences
    std::uniform_int_distribution<> dist(minNumSentences, maxNumSentences);
    int sentences{ dist(m_mt) };

    //std::string result{ "\t" };
    std::string result{ };

    for (std::size_t i{}; i != sentences; ++i)
    {
        std::string sentence{ generateSentence(minNumWords, maxNumWords) };
        result += sentence;
        result += " ";

        //   result += generateSentence(minNumWords, maxNumWords) += " ";
    }

    result += "\n";
    return result;
}

std::string LoremIpsum::generateParagraphList(int numParagraphs, int minSent, int maxSent, int minWord, int maxWord)
{
    std::string result;
    for (std::size_t i{}; i != numParagraphs; ++i)
    {
        result += generateParagraph(minSent, maxSent, minWord, maxWord);
        result += "\n";
    }
    return result;
}

// =====================================================================================
// End-of-File
// =====================================================================================
