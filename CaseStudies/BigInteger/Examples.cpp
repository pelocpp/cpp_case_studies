// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string_view>
#include <vector>
#include <algorithm>
#include <chrono>

#include "BigInteger.h"
#include "BigFaculty.h"
#include "BigMersenne.h"
#include "BigPerfectNumbers.h"
#include "BigPrimeNumbers.h"

// =====================================================================================
// markdown examples

void Test_Script_01()
{
    // testing c'tors
    BigInteger n1{ "1234567" };
    std::cout << n1 << std::endl;

    BigInteger n2{ "-1234567" };
    std::cout << n2 << std::endl;

    BigInteger n3{ "123.456.789.012.345.678" };
    std::cout << n3 << std::endl;
}

void Test_Script_02()
{
    // testing addition
    BigInteger n1{ "11111111" };
    BigInteger n2{ "22222222" };
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

    n1 = BigInteger{ "99999999999999" };
    n2 = BigInteger{ "1" };
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;
}

void Test_Script_03()
{
    // testing subtraction
    BigInteger n1{ "999" };
    BigInteger n2{ "900" };
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger{ "999" };
    n2 = BigInteger{ "998" };
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger{ "999" };
    n2 = BigInteger{ "999" };
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger{ "11111" };
    n2 = BigInteger{ "222" };
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger{ "1000000" };
    n2 = BigInteger{ "1" };
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
}

// =====================================================================================
// literals

void Test_Literals()
{
    // testing literals
    BigInteger n{};

    n = 1_big;
    std::cout << n << std::endl;

    n = 1234567890_big;
    std::cout << n << std::endl;

    n = -1234567890_big;
    std::cout << n << std::endl;

    n = 111111111111111111111111111111111111111111111111111111_big;
    std::cout << n << std::endl;

    n = 111'111'111'111'111'111'111'111'111'111'111'111'111'111'111'111'111'111_big;
    std::cout << n << std::endl;
}

// =====================================================================================
// conversion c'tors

void Test_TypeConversion_Ctors()
{
    // testing type conversion c'tors
    BigInteger n1{ 123 };
    std::cout << n1 << std::endl;

    BigInteger n2{ INT_MIN + 1 };
    std::cout << n2 << std::endl;

    BigInteger n3{ INT_MAX };
    std::cout << n3 << std::endl;

    BigInteger n4{ 1213213213 };
    std::cout << n4 << std::endl;
}

// =====================================================================================
// leading zeros

void Test01_BigInteger_LeadingZeros()
{
    BigInteger b0{};
    std::cout << b0 << std::endl;

    BigInteger b1{ "0" };
    std::cout << b1 << std::endl;

    BigInteger b2{ "00" };
    std::cout << b2 << std::endl;

    BigInteger b3{ "000" };
    std::cout << b3 << std::endl;

    BigInteger b4{"0123"};
    std::cout << b4 << std::endl;

    BigInteger b5{ "00123" };
    std::cout << b5 << std::endl;

    BigInteger b6{ "0001234" };
    std::cout << b6 << std::endl;

    BigInteger b7{ "00012345" };
    std::cout << b7 << std::endl;
}

// =====================================================================================
// leading addition

void Test_Add()
{
    // testing addition
    BigInteger n1 = BigInteger("11111111");
    BigInteger n2 = BigInteger("22222222");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

    n1 = BigInteger("99999999999999");
    n2 = BigInteger("1");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;
}

void Test_AddWithSign()
{
    // testing c'tors
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;
    std::cout << std::endl;
}

// =====================================================================================
// leading subtraction

void Test_Sub()
{
    // testing subtraction
    BigInteger n1("999");
    BigInteger n2("900");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("999");
    n2 = BigInteger("998");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("999");
    n2 = BigInteger("999");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("11111");
    n2 = BigInteger("222");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("1000000");
    n2 = BigInteger("1");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
}

void TestSubWithSign()
{
    // testing c'tors
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------

    n1 = BigInteger("222");
    n2 = BigInteger("333");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("-222");
    n2 = BigInteger("333");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("222");
    n2 = BigInteger("-333");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;

    n1 = BigInteger("-222");
    n2 = BigInteger("-333");
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
}

// =====================================================================================
// leading multiplication

void Test_Mul_01_Unsigned()
{
    // testing unsigned mul operation
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger(99);
    n2 = BigInteger(99);
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    // ??????????????????????????????? TODO: Stimmt hier das Ergebnis ???
    n1 = BigInteger{ 9999999999 };
    n2 = BigInteger{ 9999999999 };
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    // testing multiplication
    n1 = BigInteger("1212121212");
    n2 = BigInteger("4343434343");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    // multiplication example from script
    n1 = BigInteger("973018");
    n2 = BigInteger("9758");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    // testing multiplication
    n1 = BigInteger("3");
    n2 = BigInteger("50");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;
}

void Test_Mul_02_Signed()
{
    // testing signed mul operation
    BigInteger n1;
    BigInteger n2;

    n1 = BigInteger("333");
    n2 = BigInteger("222");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("222");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    n1 = BigInteger("333");
    n2 = BigInteger("-222");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;

    n1 = BigInteger("-333");
    n2 = BigInteger("-222");
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;
    std::cout << std::endl;
}

// =====================================================================================
// leading division

void Test_Division ()
{
    BigInteger n1{ 6682850 };
    BigInteger n2{ 196 };
    std::cout << n1 << " / " << n2 << " = " << (n1 / n2) << std::endl;
}

void Test_DivisionPowerByTwo()
{
    BigInteger huge{ "2.475.880.078.570.760.549.798.248.448" };

    while (huge != 1_big)
    {
        std::cout << huge << " / 2 = ";
        huge = huge / 2_big;
        std::cout << huge << std::endl;
    }
}

// =====================================================================================
// leading faculty

void Test_Faculty_01(size_t limit)
{
    for (size_t n{ 1 }; n != limit; ++n)
    {
        size_t f{ BigFaculty::faculty(n) };
        std::cout << "Faculty of " << n << ": " << f << std::endl;
    }
}

void Test_Faculty_02(long long limit)
{
    for (BigInteger n{ 1 }; n != BigInteger{ limit }; ++n)
    {
        BigInteger f{ BigFaculty::faculty(n) };
        std::cout << "Faculty of " << n << ": " << std::left << f << std::endl;
    }
}

// =====================================================================================
// leading power

void Test_Power(int limit)
{
    BigInteger two { 2 };
    for (int n{ 1 }; n != limit; ++n)
    {
        BigInteger f{ two.pow(n)};
        std::cout << "2 ^ " << n << ": " << f << std::endl;
    }

    BigInteger minus_three{ -3 };
    for (int n{ 1 }; n != limit; ++n)
    {
        BigInteger f{ minus_three.pow(n) };
        std::cout << "-3 ^ " << n << ": " << f << std::endl;
    }
}

// =====================================================================================
// leading mersenne

void Test_Mersenne_01()
{
    BigInteger mersenne { BigMersenne::number(11213) };
    std::cout << "Mersenne: " << std::endl;
    std::cout << mersenne(16) << std::endl;
    std::cout << "Number of Digits: " << mersenne.size() << std::endl;
}

void Test_Mersenne_02()
{
    std::vector<int> power {
        2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607,
        1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941,
        11213, 19937, 21701, 23209, 44497, 86243,
        110503, 132049, 216091, 756839, 859433 
    };

    for (int i = 0; i < power.size(); i++)
    {
        BigInteger mersenne{ BigMersenne::number(power[i]) };
        std::cout << (i+1) << ".th Mersenne Prime:" << (i + 1);
        std::cout << mersenne << std::endl;
        std::cout << "Number of Digits: " << mersenne.size() << std::endl;
    }
}

// =====================================================================================
// perfect numbers

void Test_01_PerfectNumbers()
{
    for (size_t i{ 2 }; i != 10000; ++i) {
        if (BigPerfectNumbers::isPerfect(i)) {
            std::cout << i << " is *prefect*" << std::endl;
        }
    }
}

void Test_02_PerfectNumbers()
{
    std::chrono::system_clock::time_point begin{ std::chrono::system_clock::now() };

    BigInteger limit{ 500 };
    for (BigInteger n{ 2 }; n != limit; ++n) {
        if (BigPerfectNumbers::isPerfect(n)) {
            std::cout << n << " is *prefect*" << std::endl;
        }
    }

    std::chrono::system_clock::time_point end{ std::chrono::system_clock::now() };
    std::chrono::system_clock::duration duration{ end - begin };
    double ticks{ std::chrono::duration<double>(duration).count() };
    std::cout << ticks << " seconds." << std::endl;
}

void Test_03_PerfectNumbers()
{
    std::chrono::system_clock::time_point begin{ std::chrono::system_clock::now() };

    // https://en.wikipedia.org/wiki/List_of_perfect_numbers
    std::vector<BigInteger> candidates
    {
        6_big,
        28_big,
        496_big,
        8'128_big,
        33'550'336_big,
        8'589'869'056_big,
        137'438'691'328_big,
        2'305'843'008'139'952'128_big,
        2'658'455'991'569'831'744'654'692'615'953'842'176_big,
        191'561'942'608'236'107'294'793'378'084'303'638'130'997'321'548'169'216_big
    };

    std::for_each(std::begin(candidates), std::end(candidates), [](const BigInteger& candidate) {
        if (BigPerfectNumbers::isPerfect(candidate)) {
            std::cout << candidate << " is *prefect*" << std::endl;
        }
    });

    std::chrono::system_clock::time_point end{ std::chrono::system_clock::now() };
    std::chrono::system_clock::duration duration{ end - begin };
    double ticks{ std::chrono::duration<double>(duration).count() };
    std::cout << ticks << " seconds." << std::endl;
}

// =====================================================================================
// prime numbers

void Test_Range(int max)
{
    int count{};
    for (int i{ 2 }; i != max; ++i)
    {
        if (BigPrimeNumbers::isPrime(i)) {
            std::cout << "  found " << i << std::endl;
            ++count;
        }
    }

    std::cout << count << " prime numbers up to " << (max-1) << "." << std::endl;
}

void Test_Range()
{
    BigInteger lower{ 10000 };
    BigInteger upper{ 11001 };
    BigInteger count{};

    for (BigInteger i{ lower }; i != upper; ++i)
    {
        if (BigPrimeNumbers::isPrime(i)) {
            std::cout << "  found " << i << std::endl;
            count++;
        }
    }

    std::cout 
        << count << " prime numbers between " << lower << " and " 
        << (upper - 1_big) << "." << std::endl;
}

void Test_Factorize_01()
{
    size_t number{ ((size_t)13821503) * ((size_t)13821503) };
    std::pair<size_t, size_t> result{ BigPrimeNumbers::hasPrimeFactor(number) };

    if (result.first != 1) {
        std::cout 
            << "Found factors " << result.first << " and " 
            << result.second << "." << std::endl;
    }
    else {
        std::cout << number << " is prime." << std::endl;
    }
}

void Test_Factorize_02()
{
    std::chrono::system_clock::time_point begin{ std::chrono::system_clock::now() };

    BigInteger number{ 13821503_big * 13821503_big };

    std::pair<BigInteger, BigInteger> result{ BigPrimeNumbers::hasPrimeFactor(number) };

    if (result.first != 1_big)
    {
        std::cout
            << "Found factors " << result.first << " and "
            << result.second << "." << std::endl;
    }
    else
    {
        std::cout << number << " is prime." << std::endl;
    }

    std::chrono::system_clock::time_point end{ std::chrono::system_clock::now() };
    std::chrono::system_clock::duration duration{ end - begin };
    double ticks{ std::chrono::duration<double>(duration).count() };
    std::cout << ticks << " seconds." << std::endl;
}

void Test_Factorize_03()
{
    // testing getPrimeFactors
    size_t candidate{ 44100 };  // 44100 = 2 * 2 * 3 * 3 * 5 * 5 * 7 * 7

    std::vector<size_t> factors{ BigPrimeNumbers::getPrimeFactors(candidate) };

    std::cout << "Prime factorization of " << candidate << ':' << std::endl;
    std::for_each(std::begin(factors), std::end(factors), [](size_t factor) {
        std::cout << "  found factor " << factor << std::endl;
    });
    std::cout << "Done." << std::endl;
}

void Test_Factorize_04()
{
    // testing getPrimeFactors
    BigInteger candidate{ 44100_big };  // 44100 = 2 * 2 * 3 * 3 * 5 * 5 * 7 * 7

    std::vector<BigInteger> factors{ BigPrimeNumbers::getPrimeFactors(candidate) };

    std::cout << "Prime factorization of " << candidate << ':' << std::endl;
    std::for_each(std::begin(factors), std::end(factors), [](const BigInteger& factor) {
        std::cout << "  found factor " << factor << std::endl;
        });
    std::cout << "Done." << std::endl;
}

// =====================================================================================
// perfect numbers

void Test_TypeConversionOperators()
{
    BigInteger n{ "-12345" };

    int k = n;
    long l = n;
    long long ll = n;

    std::cout << k << std::endl << l << std::endl << ll << std::endl;
}

// =====================================================================================
// formatting output

void Test_Formatting_Output()
{
    // testing c'tors
    BigInteger n1{ "12345678901234567890123456789012345678901234567890" };
    std::cout << n1(4) << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
