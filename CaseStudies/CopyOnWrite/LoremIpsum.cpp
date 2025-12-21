// =====================================================================================
// LoremIpsum.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include <algorithm>
#include <numeric>
#include <print>
#include <random>
#include <string>
#include <vector>

// https://github.com/Nikkicodes2/lipsum-cpp/blob/master/src/lipsum.hpp

extern std::vector<std::string> lipsumVecOriginal;

std::string generateWord()
{
    static auto rd = std::random_device{};
    static auto gen = std::mt19937{ rd() };

    auto a{ 0 }; // first distribution parameter (minimum value)
    auto b{ static_cast<int>(lipsumVecOriginal.size()) - 1 }; // second distribution parameter (maximum value)

    auto dist = std::uniform_int_distribution<int> (a, b);
    auto index = dist(gen);
    const auto& word = lipsumVecOriginal.at(index);

    return word;
}

std::string generateSentence(int minNumWords = 4, int maxNumWords = 12)
{
    static auto rd = std::random_device{};
    static auto gen = std::mt19937{ rd() };

    auto dist = std::uniform_int_distribution<int>(minNumWords, maxNumWords);

    int numWords = dist(gen);
    bool includecomma = (numWords >= (maxNumWords * 4) / 5);

    std::vector<std::string> words;
    words.resize(numWords);

    // create vector of words
    std::generate(
        words.begin(),
        words.end(),
        [] () {
            return generateWord();
        }
    );

    // create a sentence of these words
    std::string sentence = std::accumulate(
        words.begin(),
        words.end(),
        std::string{},
        [&, i = 0](const std::string a, const std::string& next) mutable {
            std::string result{ a };
            result += next;

            if (includecomma && i == (numWords / 2) - 1)
            {
                result += ",";
            }
            if (i != numWords - 1)
            {
                result += " ";
            }
            ++i;
            return result;
        }
    );

    sentence += ".";
    sentence.at(0) = std::toupper(sentence.at(0));
    return sentence;
}

std::string generateParagraph(int minNumSentences = 5, int maxNumSentences = 8, int minNumWords = 4, int maxNumWords = 12)
{
    //std::string result{ "\t" };
    std::string result{ };

    static auto rd = std::random_device{};
    static auto gen = std::mt19937{ rd() };
    
    std::uniform_int_distribution<> dist(minNumSentences, maxNumSentences);
    
    int sentences = dist(gen);

    for (int i = 0; i < sentences; ++i)
    {
        std::string sentence{ generateSentence(minNumWords, maxNumWords) };
        result += sentence;
        result += " ";

     //   result += generateSentence(minNumWords, maxNumWords) += " ";
    }
    
    result += "\n";
    return result;
}

std::string generateParagraphList(int numParagraphs, int minSent, int maxSent, int minWord, int maxWord)
{
    std::string result;
    for (int i = 0; i < numParagraphs; ++i)
    {
        result += generateParagraph(minSent, maxSent, minWord, maxWord);
    }
    return result;
}


int lorem_ipsum()
{
    return 0;
}

void test_lorem_ipsum_01()
{
    std::string word{};

    word = generateWord();
    std::println("Word: {}", word);

    word = generateWord();
    std::println("Word: {}", word);

    word = generateWord();
    std::println("Word: {}", word);
}

void test_lorem_ipsum_02()
{
    std::string sentence{};

    sentence = generateSentence(3, 5);
    std::println("Sentence: {}", sentence);

    sentence = generateSentence(3, 5);
    std::println("Sentence: {}", sentence);

    sentence = generateSentence(3, 5);
    std::println("Sentence: {}", sentence);
}

void test_lorem_ipsum_03()
{
    std::string paragraph = generateParagraph(3, 5);
    std::println("Paragraph:");
    std::println("{}", paragraph);
}

void test_lorem_ipsum()
{
   // test_lorem_ipsum_01();
   // test_lorem_ipsum_02();
    test_lorem_ipsum_03();
}


// =====================================================================================
// End-of-File
// =====================================================================================
