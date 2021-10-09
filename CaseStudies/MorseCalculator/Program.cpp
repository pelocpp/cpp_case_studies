// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <string_view>

#include "MorseCalculator.h"

void test_01()
{
    using namespace MorseExample;

    // retrieving size of morse alphabet table
    constexpr auto size{ MorseCalculator::size() };
    std::cout << "Size: " << size << std::endl;

    // accessing a single entry of the morse alphabet table
    constexpr auto entry{ MorseCalculator::getEntry(3) };
    std::cout << entry.first << ", " << entry.second << std::endl;

    // accessing a single entry of the morse alphabet table
    constexpr std::pair<char, std::string_view> entry2{ MorseCalculator::getEntry<5>() };
    std::cout << entry2.first << ", " << entry2.second << std::endl;
}

void test_02()
{
    using namespace MorseExample;

    std::string text{ "C IS BEAUTIFUL" };
    std::string message{ MorseCalculator::encode(text) };
    std::cout << "Result: " << message << std::endl;
}

void test_03()
{
    using namespace MorseExample;

    std::string message{
        "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / "
        "..-. --- -..- / .--- ..- -- .--. ... / --- ...- . .-. / "
        "- .... . / .-.. .- --.. -.-- / -.. --- --."
    };
    std::string text{ MorseCalculator::decode(message) };
    std::cout << "Result: " << text << std::endl;
}

void test_04()
{
    using namespace MorseExample;

    // testing 'back and forth'
    std::string text{ "The quick brown fox jumps over the lazy dog" };
    std::cout << "Input: " << text << std::endl;
    std::string message{ MorseCalculator::encode(text) };
    std::cout << "Morse message: " << std::endl << message << std::endl;

    std::string original{ MorseCalculator::decode(message) };
    std::cout << "Result: " << original << std::endl;
}

int main()
{
	//test_01();
	//test_02();
	//test_03();
	test_04();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
