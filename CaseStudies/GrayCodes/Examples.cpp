// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <list>

#include "GrayCodeCalculator.h"

void Test_01()
{
    // testing 1-Bit-Gray-Codes
    std::list<std::list<bool>> codes = GrayCodeCalculator::calculate(1);
    std::cout << codes.size() << " 1-Bit-Gray-Codes found:" << std::endl;
    GrayCodeCalculator::print(codes);
    std::cout << std::endl;

    // testing 2-Bit-Gray-Codes
    codes = GrayCodeCalculator::calculate(2);
    std::cout << codes.size() << " 2-Bit-Gray-Codes found:" << std::endl;
    GrayCodeCalculator::print(codes);
    std::cout << std::endl;

    // testing 3-Bit-Gray-Codes
    codes = GrayCodeCalculator::calculate(3);
    std::cout << codes.size() << " 3-Bit-Gray-Codes found:" << std::endl;
    GrayCodeCalculator::print(codes);
    std::cout << std::endl;

    // testing 4-Bit-Gray-Codes
    codes = GrayCodeCalculator::calculate(4);
    std::cout << codes.size() << " 4-Bit-Gray-Codes found:" << std::endl;
    GrayCodeCalculator::print(codes);
    std::cout << std::endl;

    // testing 5-Bit-Gray-Codes
    codes = GrayCodeCalculator::calculate(5);
    std::cout << codes.size() << " 5-Bit-Gray-Codes found:" << std::endl;
    GrayCodeCalculator::print(codes);
}

// =====================================================================================
// End-of-File
// =====================================================================================
