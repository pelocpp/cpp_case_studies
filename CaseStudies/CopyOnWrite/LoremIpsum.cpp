// =====================================================================================
// LoremIpsum.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================


#include "LoremIpsum.h"


//#include <algorithm>    // std::generate
//#include <numeric>      // std::accumulate
#include <print>        // std::println
//#include <random>       // std::random_device, std::mt19937, std::uniform_int_distribution
//#include <string>       // std::string
//#include <vector>       // std:.vector
//#include <cstddef>      // std::size_t

// https://github.com/Nikkicodes2/lipsum-cpp/blob/master/src/lipsum.hpp
//
//extern std::vector<std::string> lipsumVecOriginal;
//
//std::string generateWord()
//{
//    // using a pseudo-random generator (so called Mersenne Twister 19937)
//    static auto rd{ std::random_device{} };
//    static auto gen{ std::mt19937{ rd() } };
//  
//    // create random integer value i, uniformly distributed between 0 and max
//    auto max{ static_cast<int>(lipsumVecOriginal.size()) - 1 };
//    auto dist{ std::uniform_int_distribution<int>(0, max) };
//    auto index{ dist(gen) };
//    
//    // retrieve word from list of existing words
//    const auto& word{ lipsumVecOriginal.at(index) };
//    return word;
//}
//
//std::string generateSentence(int minNumWords = 4, int maxNumWords = 12)
//{
//    // using a pseudo-random generator (so called Mersenne Twister 19937)
//    static auto rd{ std::random_device{} };
//    static auto gen{ std::mt19937{ rd() } };
//
//    // create random integer value numWords,
//    // uniformly distributed between minNumWords and maxNumWords
//    auto dist{ std::uniform_int_distribution<int>(minNumWords, maxNumWords) };
//    int numWords{ dist(gen) };
//
//    std::vector<std::string> words;
//    words.resize(numWords);
//
//    // create vector of words from list of existing words
//    std::generate(
//        words.begin(),
//        words.end(),
//        [] () {
//            return generateWord();
//        }
//    );
//
//    // include a comma for better readability :)
//    bool includecomma{ (numWords >= (maxNumWords * 4) / 5) };
//
//    // create a sentence of these words
//    std::string sentence{ std::accumulate(
//        words.begin(),
//        words.end(),
//        std::string{},
//        [&, i = 0](const std::string a, const std::string& next) mutable {
//
//            std::string result{ a };
//            result += next;
//
//            if (includecomma && i == (numWords / 2) - 1) {
//                result += ",";
//            }
//            if (i != numWords - 1) {
//                result += " ";
//            }
//            ++i;
//            return result;
//        }
//    ) };
//
//    sentence += ".";
//    sentence.at(0) = std::toupper(sentence.at(0));
//    return sentence;
//}
//
//std::string generateParagraph(int minNumSentences = 5, int maxNumSentences = 8, int minNumWords = 4, int maxNumWords = 12)
//{
//    // using a pseudo-random generator (so called Mersenne Twister 19937)
//    static auto rd{ std::random_device{} };
//    static auto gen{ std::mt19937{ rd() } };
//    
//    // create random integer value numWords,
//    // uniformly distributed between minNumSentences and maxNumSentences
//    std::uniform_int_distribution<> dist(minNumSentences, maxNumSentences);  
//    int sentences{ dist(gen) };
//
//    //std::string result{ "\t" };
//    std::string result{ };
//
//    for (std::size_t i{}; i != sentences; ++i)
//    {
//        std::string sentence{ generateSentence(minNumWords, maxNumWords) };
//        result += sentence;
//        result += " ";
//
//     //   result += generateSentence(minNumWords, maxNumWords) += " ";
//    }
//    
//    result += "\n";
//    return result;
//}
//
//std::string generateParagraphList(int numParagraphs, int minSent, int maxSent, int minWord, int maxWord)
//{
//    std::string result;
//    for (std::size_t i{}; i != numParagraphs; ++i)
//    {
//        result += generateParagraph(minSent, maxSent, minWord, maxWord);
//    }
//    return result;
//}
//

//void test_lorem_ipsum_01()
//{
//    std::string word{};
//
//    word = generateWord();
//    std::println("Word: {}", word);
//
//    word = generateWord();
//    std::println("Word: {}", word);
//
//    word = generateWord();
//    std::println("Word: {}", word);
//}
//
//void test_lorem_ipsum_02()
//{
//    std::string sentence{};
//
//    sentence = generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//
//    sentence = generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//
//    sentence = generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//}
//
//void test_lorem_ipsum_03()
//{
//    std::string paragraph = generateParagraph(3, 5);
//    std::println("Paragraph:");
//    std::println("{}", paragraph);
//}



void test_lorem_ipsum_10()
{
    std::string word{};

    LoremIpsum loremIpsum{};

    word = loremIpsum.generateWord();
    std::println("Word: {}", word);

    word = loremIpsum.generateWord();
    std::println("Word: {}", word);

    word = loremIpsum.generateWord();
    std::println("Word: {}", word);
}


void test_lorem_ipsum_11()
{
    std::string sentence{};

    LoremIpsum loremIpsum{};

    sentence = loremIpsum.generateSentence(3, 5);
    std::println("Sentence: {}", sentence);

    sentence = loremIpsum.generateSentence(3, 5);
    std::println("Sentence: {}", sentence);

    sentence = loremIpsum.generateSentence(3, 5);
    std::println("Sentence: {}", sentence);
}

void test_lorem_ipsum_12()
{
    LoremIpsum loremIpsum{};

    std::string paragraph = loremIpsum.generateParagraph(3, 5);
    std::println("Paragraph:");
    std::println("{}", paragraph);
}

void test_lorem_ipsum_13()
{
    LoremIpsum loremIpsum{};

    std::string list = loremIpsum.generateParagraphList(100);
    std::println("Paragraph List:");
    std::println("{}", list);
}

void test_lorem_ipsum()
{
   // test_lorem_ipsum_01();
   // test_lorem_ipsum_02();
    // test_lorem_ipsum_03();

    //test_lorem_ipsum_10();
   // test_lorem_ipsum_11();
  //  test_lorem_ipsum_12();
    test_lorem_ipsum_13();
}


// =====================================================================================
// End-of-File
// =====================================================================================
