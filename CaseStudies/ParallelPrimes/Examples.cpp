// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <latch>

#include "PrimeNumberCalculator.h"

// =====================================================================================

void Test_00()
{
    constexpr size_t val = 7;

    size_t end1{ static_cast<size_t>(std::sqrt(val)) };

    double end2{ ceil(std::sqrt(val)) };

    size_t end3{ static_cast<size_t>(ceil(std::sqrt(val))) };

    std::cout << std::sqrt(val) << std::endl;
    std::cout << end1 << std::endl;
    std::cout << end2 << std::endl;
    std::cout << end3 << std::endl;
}

//void Test_01()
//{
//    PrimeNumberCalculator calculator;
//    calculator.calcPrimes();
//}

void Test_02()
{
    PrimeNumberCalculator calculator;
    calculator.calcPrimesEx();
}

void Test_03()
{
    PrimeNumberCalculator calculator;
    calculator.calcPrimesExEx();
}

// =====================================================================================
// End-of-File
// =====================================================================================
