// =====================================================================================
// Program.cpp
// =====================================================================================

// Google: "Primfaktorzerlegung legendre"

// https://userpages.uni-koblenz.de/~krapf/Sommersemester%202018/Proseminar%20Primzahlen/Ausarbeitung2.pdf

#include <iostream>
#include <iomanip>

#include "Factorial.h"
#include "BinomialCoefficient.h"

// function prototypes
void Test01();
void Test02();
void Test03();
void Test04();
void Test05();
void Test06();
void Test10();
void Test11();
void Test12();

void Test01()
{
    Factorial f;

    for (size_t i{ 1 }; i != 30; ++i)
    {
        f.set(i);
        f.factorialIterative();
        size_t result = f.value();
        std::cout 
            << std::setw(2) << std::setfill('0') << i << " : " << result 
            << std::endl;
    }
}

void Test02()
{
    Factorial f(5);
    f.factorialIterative();
    std::cout << f.get() << "! = " << f.value() << std::endl;

    f.set(10);
    f.factorialRecursive();
    std::cout << f.get() << "! = " << f.value() << std::endl;
}

void Test03()
{
    PrimeDictionary dict{};
    dict.set(2, 4);  // 2 hoch 4
    dict.set(3, 2);  // 3 hoch 2
    dict.set(5, 0);  // 5 hoch 0
    dict.set(7, 1);  // 7 hoch 1
    std::cout << dict << std::endl;

    size_t key = 3;
    size_t value = dict.get(key);
    std::cout << "Value at " << key << ": " << value << std::endl;
    dict.set(key, 22);
    value = dict.get(key);
    std::cout << "Value at " << key << ": " << value << std::endl;
}

void Test04()
{
    Factorial f(10);
    PrimeDictionary primes = f.factorialLegendre();
    std::cout << primes << std::endl;
}

void Test05()
{
    Factorial f(2012);
    PrimeDictionary primes = f.factorialLegendre();
    std::cout << primes << std::endl;

    size_t numFactorsOf5 = primes.get(5);
    std::cout << "Factors of 5: " << numFactorsOf5 << "." << std::endl;
}

void Test06()
{
    Factorial f(10000);
    PrimeDictionary primes = f.factorialLegendre();
    std::cout << primes << std::endl;

    size_t numFactorsOf5 = primes.get(5);
    std::cout << "Factors of 5: " << numFactorsOf5 << "." << std::endl;
}

void Test10()
{
    Factorial f1(10);
    PrimeDictionary dict1 = f1.factorialLegendre();
    Factorial f2(5);
    PrimeDictionary dict2 = f2.factorialLegendre();
    dict1.reduce(dict2);
    std::cout << dict1 << std::endl;
}

void Test11()
{
    BinomialCoefficient coeff;

    for (size_t i = 1; i != 10; ++i)
    {
        coeff.setUpper(2 * i);
        coeff.setLower(i);
        coeff.calculate();

        std::cout
            << "Binomial "
            << coeff
            << " = "
            << coeff.value() << std::endl;
    }
}

void Test12()
{
    BinomialCoefficient coeff;

    coeff.setUpper(10);
    coeff.setLower(5);
    coeff.calculate();

    std::cout
        << "Binomial "
        << coeff
        << " = "
        << coeff.value() << std::endl;

    PrimeDictionary result = coeff.calculateLegendre();

    std::cout
        << "Binomial "
        << coeff
        << " = "
        << result << std::endl;
}

void Test13()
{
    BinomialCoefficient bin;

    for (size_t i{ 1 }; i != 25; i++)
    {
        bin.setUpper(2 * i);
        bin.setLower(i);
        PrimeDictionary result = bin.calculateLegendre();

        std::cout
            << "Binomial ("
            << std::setw(2) << bin.getUpper()
            << ", "
            << std::setw(2) << bin.getLower()
            << ") = "
            << result << std::endl;
    }
}

int main()
{
    Test01();
    Test02();
    Test03();
    Test04();
    Test05();
    Test06();
    Test10();
    Test11();
    Test12();
    Test13();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
