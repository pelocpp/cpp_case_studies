// =====================================================================================
// Program.cpp
// =====================================================================================

// TODO: size_t ???
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//void Test01_XXX();
//
//
//int main()
//{   
//    Test01_XXX();
//
//    return 0;
//}


#include "PrimeDictionary.h"
#include "Factorial.h"
#include "BinomialCoefficient.h"


// P22 : Noch der AP noch vorzubereiten bzw. darauf hinzuweisen:
// Klassenmethoden und -elemente
// Hinweisen aus - rekursive Methoden

// function prototypes
void Test00_Overflow();
void Test01();
void Test02();
void Test03_Test_2012();
void Test10();
void Test11();
void Test12();
void Test20();


void Test00_Overflow()
{
    Factorial f;

    for (int i = 1; i < 20; i++)
    {
        f.setNumber(i);
        f.factorialIterative();
        size_t result = f.getValue();
        std::cout << i << " : " << result << std::endl;
    }
}


void Test01()
{
    Factorial f(5);
    f.factorialIterative();
    std::cout << f.getNumber() << "! = " << f.getValue() << std::endl;

    f.setNumber(10);
    f.factorialRecursive();
    std::cout << f.getNumber() << "! = " << f.getValue() << std::endl;
}

void Test02()
{
    Factorial f(5);
    PrimeDictionary primes = f.factorialLegendre();
    std::cout << primes << std::endl;

    f.setNumber(10);
    primes = f.factorialLegendre();
    std::cout << primes << std::endl;
}

void Test03_Test_2012()
{
    Factorial f(2012);
    PrimeDictionary primes = f.factorialLegendre();
    std::cout << primes << std::endl;

    size_t numFactorsOf5 = primes.getValue(5);
    std::cout << "Factors of 5: " << numFactorsOf5 << "." << std::endl;
}

void Test10()
{
    BinomialCoefficient bin;
    for (int i = 1; i < 10; i++)
    {
        bin.SetUpperNumber(2 * i);
        bin.SetLowerNumber(i);
        bin.Calculate();
        size_t coeff = bin.GetValue();
        std::cout
            << "Binomial ("
            << bin.GetUpperNumber()
            << ", "
            << bin.GetLowerNumber()
            << ") = "
            << bin.GetValue() << std::endl;
    }
}

void Test11()
{
    BinomialCoefficient bin;
    bin.SetUpperNumber(7);
    bin.SetLowerNumber(3);

    PrimeDictionary result = bin.CalculateLegendre();

    std::cout
        << "Binomial ("
        << bin.GetUpperNumber()
        << ", "
        << bin.GetLowerNumber()
        << ") = "
        << result << std::endl;
}

void Test12()
{
    BinomialCoefficient bin;
    for (int i = 1; i < 25; i++)
    {
        bin.SetUpperNumber(2 * i);
        bin.SetLowerNumber(i);
        PrimeDictionary result = bin.CalculateLegendre();

        //std::cout
        //    << "Binomial ("
        //    << bin.GetUpperNumber()
        //    << ", "
        //    << bin.GetLowerNumber()
        //    << ") = "
        //    << result << std::endl;

        std::cout << result << std::endl;
    }
}


void Test20()
{
    PrimeDictionary dict{};
    dict.insert(2, 4);  // 2 hoch 4
    dict.insert(3, 2);  // 3 hoch 2
    dict.insert(5, 0);  // 5 hoch 0
    dict.insert(7, 1);  // 7 hoch 1
    std::cout << dict << std::endl;

    size_t key = 3;
    size_t value = dict.getValue(key);
    std::cout << "Value at " << key << ": " << value << std::endl;
}

int main()
{
    Test00_Overflow();
    Test01();
    Test02();
    Test03_Test_2012();
    Test10();
    Test11();
    Test12();
    Test20();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
