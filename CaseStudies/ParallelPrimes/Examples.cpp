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

void Test_01()
{
    // there is no possibility to reset a std::latch object
    //{
    //    PrimeNumberCalculator calculator;
    //    calculator.minimum(2);
    //    calculator.maximum(100);
    //    calculator.threadCount(4);
    //    calculator.calcPrimes();
    //}
    //{
    //    PrimeNumberCalculator calculator;
    //    calculator.minimum(2);
    //    calculator.maximum(1'000);
    //    calculator.threadCount(4);
    //    calculator.calcPrimes();
    //}
    {
        PrimeNumberCalculator calculator;
        calculator.minimum(2);
        calculator.maximum(1'000'000);
        calculator.threadCount(6);
        calculator.calcPrimes();
    }
}

void Test_02()
{
    // there is no possibility to reset a std::latch object
    {
        PrimeNumberCalculator calculator;
        calculator.minimum(2);
        calculator.maximum(100);
        calculator.calcPrimesEx();
    }
    {
        PrimeNumberCalculator calculator;
        calculator.minimum(2);
        calculator.maximum(1'000);
        calculator.calcPrimesEx();
    }
    {
        PrimeNumberCalculator calculator;
        calculator.minimum(2);
        calculator.maximum(1'000'000);
        calculator.calcPrimes();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
