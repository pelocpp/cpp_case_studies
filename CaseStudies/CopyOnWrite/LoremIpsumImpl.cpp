// =====================================================================================
// LoremIpsumImpl.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "LoremIpsum.h"

#include <algorithm>       // std::generate
#include <cstddef>         // std::size_t
#include <numeric>         // std::accumulate
#include <string>          // std::string
#include <string_view>     // std::string_view
#include <vector>          // std:.vector
#include <iostream>        // std::cout
#include <fstream>         // std::ofstream

// c'tor(s)
LoremIpsum::LoremIpsum() : LoremIpsum{ 4, 12, 5, 8, 6 }
{
}

LoremIpsum::LoremIpsum(
    std::size_t minNumWords, std::size_t maxNumWords, 
    std::size_t minNumSentences, std::size_t maxNumSentences,
    std::size_t numParagraphs) 
  :
    m_minNumWords{ minNumWords }, m_maxNumWords{ maxNumWords },
    m_minNumSentences{ minNumSentences }, m_maxNumSentences{ maxNumSentences }, m_numParagraphs{ numParagraphs },
    m_words{},
    m_device{}, m_engine{ m_device() }
{
    m_words =
    {
#include "LoremIpsumOriginalWords.inl"
    };

    m_wordDistribution = std::uniform_int_distribution<std::size_t>(0, m_words.size() - 1);
    m_wordsDistribution = std::uniform_int_distribution<std::size_t>(minNumWords, maxNumWords);
    m_sentencesDistribution = std::uniform_int_distribution<std::size_t>(minNumSentences, maxNumSentences);
}

// public interface
void LoremIpsum::generateLoremIpsum(std::string_view fileName)
{
    enum class Mode { STDOUT, FILE };

    std::streambuf* buf;
    std::ofstream    of;
    std::ostream     out{ nullptr };
    Mode             mode;

    if (!fileName.empty()) {
        of.open(fileName.data());
        buf = of.rdbuf();
        mode = Mode::FILE;
    }
    else {
        buf = std::cout.rdbuf();
        mode = Mode::STDOUT;
    }

    out.rdbuf(buf);  // attach to out

    generateParagraphList(out);

    if (mode == Mode::FILE) {
        of.close();
    }
}

void LoremIpsum::setOriginalWords()
{
    m_words =
    {
#include "LoremIpsumOriginalWords.inl"
    };

    m_wordDistribution = std::uniform_int_distribution<std::size_t>(0, m_words.size() - 1);
}

void LoremIpsum::setLongWords()
{
    m_words =
    {
#include "LoremIpsumLongWords.inl"
    };

    m_wordDistribution = std::uniform_int_distribution<std::size_t>(0, m_words.size() - 1);
}

// private helper methods
void LoremIpsum::generateFirstWord(std::ostream& os)
{
    // create random integer value i, uniformly distributed between 0 and max
    auto index{ m_wordDistribution(m_engine) };
    
    // retrieve word from list of existing words
    auto word{ m_words.at(index) };

    // word is first of current sentence, capitalize first character 
    char upperCh{ word[0] - ('a' -  'A') };
    auto rest{ word.substr (1)};

    os << upperCh;
    os << rest;
}

void LoremIpsum::generateNextWord(std::ostream& os)
{
    // create random integer value i, uniformly distributed between 0 and max
    auto index{ m_wordDistribution(m_engine) };

    // retrieve word from list of existing words
    auto word{ m_words.at(index) };
    os << word;
}

// generate a random sentence
void LoremIpsum::generateSentence(std::ostream& os)
{
    // create random integer value numWords,
    // uniformly distributed between minNumWords and maxNumWords
    std::size_t numWords{ m_wordsDistribution(m_engine) };

    generateFirstWord(os);
    os << ' ';

    bool includecomma = (numWords >= (m_maxNumWords * 4) / 5);
    for (std::size_t i{ 1 }; i != numWords; ++i)
    {
        generateNextWord(os);

        if (includecomma && i == (numWords / 2) - 1) {
            os << ',';
        }

        if (i != numWords - 1) {
            os << ' ';
        }
    }

    os << '.';
}

void LoremIpsum::generateParagraph(std::ostream& os)
{
    // create random integer value numWords,
    // uniformly distributed between minNumSentences and maxNumSentences
    std::size_t sentences{ m_sentencesDistribution(m_engine) };

    for (std::size_t i{}; i != sentences; ++i)
    {
        generateSentence(os);
        os << ' ';
    }

    os << '\n';
}

void LoremIpsum::generateParagraphList(std::ostream& os)
{
    for (std::size_t i{}; i != m_numParagraphs; ++i)
    {
        generateParagraph(os);
        os << '\n';
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
