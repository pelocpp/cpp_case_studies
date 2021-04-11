// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <tuple>
#include <optional>

#include "Number.h"
#include "Palindrom.h"

// =====================================================================================
// markdown examples

void Test_Constructors()
{
    // testing c'tors
    Number n1{ "1234567" };
    std::cout << n1 << std::endl;

    Number n2{ "123.456.789.012.345.678" };
    std::cout << n2 << std::endl;
}

// =====================================================================================
// addition

void Test_Add()
{
    // testing addition // 3.333
    Number n1 = Number("1111");
    Number n2 = Number("2222");
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 16.665
    n1 = Number("7777");
    n2 = Number("8888");
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 2.258
    n1 = Number("1282");
    n2 = Number("976");
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 100.000.000.000.000
    n1 = Number("99999999999999");
    n2 = Number("1");
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;
}

// =====================================================================================
// palindrom

void Test_Palindrom_01()
{
    Number start{ "89" };
    size_t count{ 20 }; // choose 100 for success

    const auto& [palindrom, begin, steps] = Palindrom::calcPalindrom(start, count);
    std::cout << "Searching palindrom beginning at " << begin << " [" << steps << " steps]:" << std::endl;

    if (palindrom.has_value()) {
        std::cout << "Found palindrom: " << palindrom.value() << std::endl;
    }
    else {
        std::cout << "No palindrom found!" << std::endl;
    }
}

void Test_Palindrom_02()
{

}

// =====================================================================================
// End-of-File
// =====================================================================================
