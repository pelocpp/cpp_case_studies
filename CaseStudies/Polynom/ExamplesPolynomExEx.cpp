// =====================================================================================
// ExamplesPolynomExEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <concepts>

#include "PolynomEx.h"

// testing concepts
void test_Concepts()
{
    PolynomEx<float> p1{ 1.0, 2.0, 3.0 };
    std::cout << p1 << std::endl;

    PolynomEx<double> p2{ 4.0, 5.0, 6.0 };
    std::cout << p2 << std::endl;

    PolynomEx<long double> p3{ 7.0, 8.0, 9.0 };
    std::cout << p3 << std::endl;

    // dooesn't compile: "the associated constraints are not satisfied"
    //PolynomEx<long> p4{ 1, 2, 3 };
    //PolynomEx<int> p5{ 4, 5, 6 };
}

// =====================================================================================
// End-of-File
// =====================================================================================

