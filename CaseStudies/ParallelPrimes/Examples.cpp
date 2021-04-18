// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <atomic>
#include <mutex> 

#include "PrimeNumberCalculator.h"

void Test_01()
{
    PrimeNumberCalculator calculator;
    calculator.minimum(2);
    calculator.maximum(100);
    calculator.threadCount(4);
    calculator.calcPrimes();

    calculator.minimum(2);
    calculator.maximum(1'000);
    calculator.threadCount(6);
    calculator.calcPrimes();

    calculator.minimum(2);
    calculator.maximum(1'000'000);
    calculator.threadCount(12);
    calculator.calcPrimes();
}

void Test_02()
{
    PrimeNumberCalculator calculator;
    calculator.minimum(2);
    calculator.maximum(100);
    calculator.threadCount(4);
    calculator.calcPrimesEx();

    calculator.minimum(2);
    calculator.maximum(1'000);
    calculator.threadCount(4);
    calculator.calcPrimesEx();
}

// =====================================================================================
// End-of-File
// =====================================================================================
