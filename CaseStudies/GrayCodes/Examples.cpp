// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <vector>

#include "GrayCodeCalculator.h"

void Test_01()
{
    //GrayCodeCalculator calc;
    std::vector<std::vector<bool>> codes = GrayCodeCalculator::calculate(5);


    std::cout << codes.size() << " 3-Bit-Gray-Codes found:" << std::endl;

    GrayCodeCalculator::print(codes);


    //calc.SetLength(5);
    //codes = calc.Calculate();
    //cout << calc.GetLength() << "-Bit-Gray-Code:" << endl;
    //cout << codes << endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
