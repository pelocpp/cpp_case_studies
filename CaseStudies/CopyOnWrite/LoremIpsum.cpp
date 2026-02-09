// =====================================================================================
// LoremIpsum.cpp // Copy-on-Write
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

#include "LoremIpsum.h"

static void test_lorem_ipsum_01()
{
    LoremIpsum loremIpsum{};

    loremIpsum.generateLoremIpsum("Hans.txt");
    loremIpsum.generateLoremIpsum("");
}

static void test_lorem_ipsum_02()
{
    LoremIpsum loremIpsum{ 8, 12, 4, 8, 3 };
    loremIpsum.generateLoremIpsum("");
}

static void test_lorem_ipsum_03()
{
    LoremIpsum loremIpsum{ 8, 12, 4, 8, 3 };
    loremIpsum.setLongWords();
    loremIpsum.generateLoremIpsum("");
}

static void test_lorem_ipsum_04()
{
    LoremIpsum loremIpsum{ 8, 12, 4, 8, 3 };
    loremIpsum.setLongWords();
    loremIpsum.generateLoremIpsum("LoremIpsum.txt");
}

static void test_lorem_ipsum_05()
{
    LoremIpsum loremIpsum{ 8, 12, 4, 8, 5000 };
    loremIpsum.setLongWords();
    loremIpsum.generateLoremIpsum("LoremIpsum.txt");
}

static void test_lorem_ipsum_06()
{
    LoremIpsum loremIpsum{ 10, 14, 4, 8, 15000 };
    loremIpsum.setLongWords();
    loremIpsum.generateLoremIpsum("LoremIpsum.txt");
}

void main_lorem_ipsum()
{
    test_lorem_ipsum_01();
    test_lorem_ipsum_02();
    test_lorem_ipsum_03();
    test_lorem_ipsum_04();
    test_lorem_ipsum_05();
    test_lorem_ipsum_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
