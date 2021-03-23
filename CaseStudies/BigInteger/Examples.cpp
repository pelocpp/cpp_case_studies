// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>

#include "BigInteger.h"
#include "BigFaculty.h"
#include "BigMersenne.h"

//#include <sstream>
//#include <numeric>
//#include <iomanip>

void Test_TypeConversion_Ctors()
{
    // testing type conversion c'tors

//#define SHRT_MIN    (-32768)
//#define SHRT_MAX      32767
//#define USHRT_MAX     0xffff
//#define INT_MIN     (-2147483647 - 1)
//#define INT_MAX       2147483647
//#define UINT_MAX      0xffffffff
//#define LONG_MIN    (-2147483647L - 1)
//#define LONG_MAX      2147483647L
//#define ULONG_MAX     0xffffffffUL
//#define LLONG_MAX     9223372036854775807i64
//#define LLONG_MIN   (-9223372036854775807i64 - 1)
//#define ULLONG_MAX    0xffffffffffffffffui64

    BigInteger n1{ 123 };
    std::cout << n1 << std::endl;

    BigInteger n2{ INT_MIN + 1 };
    std::cout << n2 << std::endl;

    BigInteger n3{ INT_MAX };
    std::cout << n3 << std::endl;

    BigInteger n4{ 1213213213 };
    std::cout << n4 << std::endl;

}
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

void Test01_BigInteger()
{
    BigInteger b{"1.2.3.4.567890"};
    std::cout << "=====================" << std::endl;
    std::cout << b << std::endl;
}

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

void Test_Sub()
{
    //// testing subtraction
    //BigInteger n1("999");
    //BigInteger n2("900");
    //cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    //n1 = BigInteger("999");
    //n2 = BigInteger("998");
    //cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    //n1 = BigInteger("999");
    //n2 = BigInteger("999");
    //cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    //n1 = BigInteger("11111");
    //n2 = BigInteger("222");
    //cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;

    //n1 = BigInteger("1000000");
    //n2 = BigInteger("1");
    //cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;
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

void Test_Division ()
{
    BigInteger n1{ 6682850 };
    BigInteger n2{ 196 };
    std::cout << n1 << " / " << n2 << " = " << (n1 / n2) << std::endl;
}

void Test_Faculty(int limit)
{
    for (BigInteger n{ 1 }; n != BigInteger { limit }; ++n)
    {
        BigInteger f{ BigFaculty::faculty(n) };
        std::cout << "Faculty of " << n << ": " << f << std::endl;
    }
}

void Test_Power(int limit)
{
    BigInteger two { 2 };
    for (int n{ 1 }; n != limit; ++n)
    {
        BigInteger f{ two.pow(n)};
        std::cout << "2 ^ " << n << ": " << f << std::endl;
    }
}

void Test_Mersenne_01()
{
    BigInteger mersenne { BigMersenne::number(11213) };

    std::cout << "Mersenne: " << mersenne << std::endl;
    std::cout << "Number of Digits: " << mersenne.size() << std::endl;
   // std::cout << "Computation Time: {0}", sw.ElapsedMilliseconds);
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


        //    mersenne.Cardinality, sw.ElapsedMilliseconds);
        //Console.WriteLine();

        // std::cout << "Computation Time: {0}", sw.ElapsedMilliseconds);
    }


}

// =====================================================================================
// End-of-File
// =====================================================================================
