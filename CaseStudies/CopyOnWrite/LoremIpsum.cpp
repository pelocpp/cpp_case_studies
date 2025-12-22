// =====================================================================================
// LoremIpsum.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "LoremIpsum.h"

//#include <algorithm>    // std::generate
//#include <numeric>      // std::accumulate
//#include <print>        // std::println
//#include <random>       // std::random_device, std::mt19937, std::uniform_int_distribution
//#include <string>       // std::string
//#include <vector>       // std:.vector


//
//void test_lorem_ipsum_10()
//{
//    std::string word{};
//
//    LoremIpsum loremIpsum{};
//
//    word = loremIpsum.generateWord();
//    std::println("Word: {}", word);
//
//    word = loremIpsum.generateWord();
//    std::println("Word: {}", word);
//
//    word = loremIpsum.generateWord();
//    std::println("Word: {}", word);
//}
//
//
//void test_lorem_ipsum_11()
//{
//    std::string sentence{};
//
//    LoremIpsum loremIpsum{};
//
//    sentence = loremIpsum.generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//
//    sentence = loremIpsum.generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//
//    sentence = loremIpsum.generateSentence(3, 5);
//    std::println("Sentence: {}", sentence);
//}
//
//void test_lorem_ipsum_12()
//{
//    LoremIpsum loremIpsum{};
//
//    std::string paragraph = loremIpsum.generateParagraph(3, 5);
//    std::println("Paragraph:");
//    std::println("{}", paragraph);
//}
//
//void test_lorem_ipsum_13()
//{
//    LoremIpsum loremIpsum{};
//
//    std::string list = loremIpsum.generateParagraphList(100);
//    std::println("Paragraph List:");
//    std::println("{}", list);
//}


void test_lorem_ipsum_20()
{
    LoremIpsum loremIpsum{};

    loremIpsum.generateLoremIpsum("Hans.txt");
    loremIpsum.generateLoremIpsum("");
}


void test_lorem_ipsum()
{
   // test_lorem_ipsum_01();
   // test_lorem_ipsum_02();
    // test_lorem_ipsum_03();

    //test_lorem_ipsum_10();
   // test_lorem_ipsum_11();
  //  test_lorem_ipsum_12();
  //  test_lorem_ipsum_13();

    test_lorem_ipsum_20();
}


// =====================================================================================
// End-of-File
// =====================================================================================
