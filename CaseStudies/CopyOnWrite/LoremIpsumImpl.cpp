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

LoremIpsum::LoremIpsum() : LoremIpsum{ 4, 12, 5, 8, 6 }
{
}

LoremIpsum::LoremIpsum(std::size_t minNumWords, std::size_t maxNumWords, std::size_t minNumSentences, std::size_t maxNumSentences, std::size_t numParagraphs) :
    m_minNumWords{ minNumWords }, m_maxNumWords{ maxNumWords },
    m_minNumSentences{ minNumSentences }, m_maxNumSentences{ maxNumSentences }, m_numParagraphs{ numParagraphs },
    m_originalWords{}, m_longWords{}, 
    m_device{}, m_engine{ m_device() }
{
    m_originalWords =
    {
#include "LoremIpsumOriginalWords.inl"
    };

    m_wordDistribution = std::uniform_int_distribution<std::size_t>(0, m_originalWords.size() - 1);
    m_wordsDistribution = std::uniform_int_distribution<std::size_t>(minNumWords, maxNumWords);
    m_sentencesDistribution = std::uniform_int_distribution<std::size_t>(minNumSentences, maxNumSentences);
}


//
//LoremIpsum::LoremIpsum()
//    : m_originalWords{}, m_longWords{}, m_device{}, m_engine{ m_device() }
//{
//    m_originalWords =
//    {
//#include "LoremIpsumOriginalWords.inl"
//    };
//
//    m_wordDistribution = std::uniform_int_distribution<std::size_t>(0, m_originalWords.size() - 1);
//    m_wordsDistribution = std::uniform_int_distribution<std::size_t>(4, 12);
//    m_sentencesDistribution = std::uniform_int_distribution<std::size_t>(5, 8);
//}

// generates a random word
void LoremIpsum::generateWord(std::ostream& os)
{
    // create random integer value i, uniformly distributed between 0 and max
    //auto max{ static_cast<int>(m_originalWords.size()) - 1 };
    //auto dist{ std::uniform_int_distribution<int>(0, max) };
   // auto index{ dist(m_engine) };

    auto index{ m_wordDistribution(m_engine) };
    

    // retrieve word from list of existing words
    auto word{ m_originalWords.at(index) };
    os << word;
}

// generate a random sentence
void LoremIpsum::generateSentence(std::ostream& os)
{
    //// create random integer value numWords,
    //// uniformly distributed between minNumWords and maxNumWords
    //auto dist{ std::uniform_int_distribution<std::size_t>(minNumWords, maxNumWords) };
    //std::size_t numWords{ dist(m_engine) };

    //std::vector<std::string> words;
    //words.resize(numWords);

    //// create vector of words from list of existing words
    //std::generate(
    //    words.begin(),
    //    words.end(),
    //    [&] () { return generateWord(); }
    //);

    //// include a comma for better readability :)
    //bool includecomma{ (numWords >= (maxNumWords * 4) / 5) };

    //// create a sentence of these words
    //std::string sentence{ std::accumulate(
    //    words.begin(),
    //    words.end(),
    //    std::string{},
    //    [&, i = 0](const std::string a, const std::string& next) mutable {

    //        std::string result{ a };
    //        result += next;

    //        if (includecomma && i == (numWords / 2) - 1) {
    //            result += ",";
    //        }
    //        if (i != numWords - 1) {
    //            result += " ";
    //        }
    //        ++i;
    //        return result;
    //    }
    //) };

    //sentence += ".";
    //sentence.at(0) = std::toupper(sentence.at(0));
    //return sentence;





   // std::string result;

    // create random integer value numWords,
    // uniformly distributed between minNumWords and maxNumWords
    //auto dist{ std::uniform_int_distribution<std::size_t>(minNumWords, maxNumWords) };
    //std::size_t numWords{ dist(m_engine) };

    

    std::size_t numWords{ m_wordsDistribution(m_engine) };

    bool includecomma = (numWords >= (m_maxNumWords * 4) / 5);
    for (std::size_t i{}; i != numWords; ++i)
    {
        generateWord(os);

        if (includecomma && i == (numWords / 2) - 1)
        {
            //result += ",";
            os << ',';
        }
        if (i != numWords - 1)
        {
            //result += " ";
            os << ' ';
        }
    }
   // result += ".";
    os << '.';
  //  result.at(0) = std::toupper(result.at(0));
    //return result;
}

void LoremIpsum::generateParagraph(std::ostream& os)
{
    // create random integer value numWords,
    // uniformly distributed between minNumSentences and maxNumSentences
    //std::uniform_int_distribution<std::size_t> dist(minNumSentences, maxNumSentences);
    //std::size_t sentences{ dist(m_engine) };


      std::size_t sentences{ m_sentencesDistribution(m_engine) };

    //std::string result{ "\t" };
  //  std::string result{ };

    for (std::size_t i{}; i != sentences; ++i)
    {
        //std::string sentence{ generateSentence(minNumWords, maxNumWords) };
        //result += sentence;

        generateSentence(os);
        os << ' ';

       // result += " ";

        //   result += generateSentence(minNumWords, maxNumWords) += " ";
    }

    os << '\n';

   // result += "\n";
   // os << result;
    //   return result;
}

void LoremIpsum::generateParagraphList(std::ostream& os)
{
    for (std::size_t i{}; i != m_numParagraphs; ++i)
    {
        generateParagraph(os);
        os << '\n';
    }
}


void LoremIpsum::generateLoremIpsum(std::string_view fileName)
{
    enum class Mode { STDOUT, FILE };

    Mode             mode;
    std::streambuf*  buf;
    std::ofstream    of;
    std::ostream     out{nullptr};

    if (! fileName.empty())
    {
        of.open(fileName.data());
        buf = of.rdbuf();
        mode = Mode::FILE;
    }
    else
    {
        buf = std::cout.rdbuf();
        mode = Mode::STDOUT;
    }

    out.rdbuf(buf);  // attach to out

    generateParagraphList(out);

    if (mode == Mode::FILE) {
        of.close();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
