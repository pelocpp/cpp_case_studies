// =====================================================================================
// LoremIpsum.h // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#pragma once

#include <cstddef>                 // std::size_t
#include <ostream>                 // std::ostream
#include <random>                  // std::random_device, std::mt19937, std::uniform_int_distribution
#include <string_view>             // std::string_view
#include <vector>                  // std::vector

class LoremIpsum
{
private:
    std::size_t                    m_minNumWords;
    std::size_t                    m_maxNumWords;
    std::size_t                    m_minNumSentences;
    std::size_t                    m_maxNumSentences;
    std::size_t                    m_numParagraphs;

    std::vector<std::string_view>  m_words;

    std::random_device             m_device;
    std::mt19937                   m_engine;

    std::uniform_int_distribution<std::size_t>  m_wordDistribution;
    std::uniform_int_distribution<std::size_t>  m_wordsDistribution;
    std::uniform_int_distribution<std::size_t>  m_sentencesDistribution;

public:
    // c'tor(s)
    LoremIpsum();
    LoremIpsum(
        std::size_t minNumWords, std::size_t maxNumWords, 
        std::size_t minNumSentences, std::size_t maxNumSentences, 
        std::size_t numParagraphs
    );

    // public interface
    void generateLoremIpsum        (std::string_view fileName);
    void setOriginalWords();
    void setLongWords();

private:
    // private helper methods
    void generateFirstWord         (std::ostream& os);
    void generateNextWord          (std::ostream& os);
    void generateSentence          (std::ostream& os);
    void generateParagraph         (std::ostream& os);
    void generateParagraphList     (std::ostream& os);
};

// =====================================================================================
// End-of-File
// =====================================================================================
