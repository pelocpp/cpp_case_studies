// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <tuple>
#include <optional>

#include "Number.h"
#include "PalindromCalculator.h"

// =====================================================================================
// helper function

void calcPalindrom(const Number&, size_t);

// =====================================================================================
// markdown constructors

void Test_Markdown()
{
    Number n{ "1234321" };
    std::cout << std::boolalpha << n.symmetric() << std::endl;

    Number n1{ "12345" };
    Number m1{ n.reverse() };
    std::cout << n1 << std::endl;
    std::cout << m1 << std::endl;

    Number n2{ "1282" };
    std::cout << n2 << std::endl;
    Number n3{ "976" };
    std::cout << "+ " << n3 << std::endl;
    Number n4{ n2.add(n3) };
    std::cout << n4 << std::endl;
}

// =====================================================================================
// constructors

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
    Number n1{ "1111" };
    Number n2{ "2222" };
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 16.665
    n1 = Number{ "7777" };
    n2 = Number{ "8888" };
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 2.258
    n1 = Number{ "1282" };
    n2 = Number{ "976" };
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;

    // 100.000.000.000.000
    n1 = Number{ "99999999999999" };
    n2 = Number{ "1" };
    std::cout << n1 << " + " << n2 << " = " << n1.add(n2) << std::endl;
}

// =====================================================================================
// palindrom

void Test_Palindrom_01()
{
    Number start{ "89" };
    size_t count{ 100 }; // choose 100 for success

    const auto& [palindrom, begin, steps] {
        PalindromCalculator::calcPalindrom(start, count)
    };

    std::cout 
        << "Searching palindrom beginning at " << begin 
        << " [" << steps << " steps]:" << std::endl;

    if (palindrom.has_value()) {
        std::cout << "Found palindrom: " << palindrom.value() << std::endl;
    }
    else {
        std::cout << "No palindrom found!" << std::endl;
    }
}

void Test_Palindrom_02()
{
    Number start{ "89" };
    size_t count{ 100 }; // choose 100 for success

    std::tuple<std::optional<Number>, Number, size_t> result{
        PalindromCalculator::calcPalindrom(start, count)
    };

    std::cout 
        << "Searching palindrom beginning at " << std::get<1>(result) 
        << " [" << std::get<2>(result) << " steps]:" << std::endl;

    if (std::get<0>(result).has_value()) {
        std::cout << "Found palindrom: " << std::get<0>(result).value() << std::endl;
    }
    else {
        std::cout << "No palindrom found!" << std::endl;
    }
}

void Test_Palindrom_03()
{
    Number start{ "1.186.060.307.891.929.990" };
    size_t count{ 270 };
    calcPalindrom(start, count);
}

void Test_Palindrom_04()
{
    Number start{ "13.968.441.660.506.503.386.020" };
    size_t count{ 300 };
    calcPalindrom(start, count);
}

void Test_Palindrom_05()
{
    Number start{ "107.000.020.928.910" };
    size_t count{ 200 };
    calcPalindrom(start, count);
}

void Test_Palindrom_06()
{
    Number start{ "89" };
    size_t count{ 500 };
    calcPalindrom(start, count);
}

void calcPalindrom(const Number& start, size_t count)
{
    std::tuple<std::optional<Number>, Number, size_t> result{
        PalindromCalculator::calcPalindrom(start, count) 
    };

    std::cout
        << "Searching palindrom beginning at " << std::get<1>(result)
        << " [" << std::get<2>(result) << " steps]:" << std::endl;

    if (std::get<0>(result).has_value()) {
        std::cout << "Found palindrom: " << std::get<0>(result).value() << std::endl;
    }
    else {
        std::cout << "No palindrom found!" << std::endl;
    }
}

void Test_FourthEulerProblem()
{
    std::tuple<size_t, size_t, size_t> solution{ PalindromCalculator::forthEulerProblem() };

    std::cout << "Solution of fourth Euler problem:" << std::endl;
    std::cout 
        << std::get<1>(solution) << " * " << std::get<2>(solution) 
        << " = " << std::get<0>(solution) << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
