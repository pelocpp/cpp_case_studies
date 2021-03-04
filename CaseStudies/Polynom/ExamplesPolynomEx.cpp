// =====================================================================================
// ExamplesPolynomEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "PolynomEx.h"

using ScalarType = float;

// testing c'tors and d'tor
void test_Ctors_Ex()
{
    PolynomEx<ScalarType> p{ };
    std::cout << p << std::endl;

    PolynomEx<ScalarType> p1{ 1.0 };
    std::cout << p1 << std::endl;

    PolynomEx<ScalarType> p2{ 1.0, 2.0, 3.0 };
    std::cout << p2 << std::endl;

    PolynomEx<ScalarType> p3{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p3 << std::endl;

    PolynomEx<ScalarType> p4{ -1.0, 0.0, -2.0, 0.0, -3.0 };
    std::cout << p4 << std::endl;

    PolynomEx<ScalarType> p5{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p5 << std::endl;

    PolynomEx<ScalarType> p6 = p5;
    std::cout << p6 << std::endl;

    PolynomEx<ScalarType> p7{ p5 };
    std::cout << p7 << std::endl;
}

void test_RemoveTrailingZeros_Ex()
{
    PolynomEx<ScalarType> p1{ };
    std::cout << p1 << std::endl;

    PolynomEx<ScalarType> p2{ 0.0 };
    std::cout << p2 << std::endl;

    PolynomEx<ScalarType> p3{ 0.0, 0.0 };
    std::cout << p3 << std::endl;

    PolynomEx<ScalarType> p4{ 0.0, 0.0, 0.0 };
    std::cout << p4 << std::endl;

    PolynomEx<ScalarType> p5{ 1.0 };
    std::cout << p5 << std::endl;

    PolynomEx<ScalarType> p6{ 1.0, 0.0 };
    std::cout << p6 << std::endl;

    PolynomEx<ScalarType> p7{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p7 << std::endl;

    PolynomEx<ScalarType> p8{ 1.0, 0.0, 2.0, 0.0, 3.0, 0.0 };
    std::cout << p8 << std::endl;

    PolynomEx<ScalarType> p9{ 1.0, 0.0, 2.0, 0.0, 3.0, 0.0, 0.0 };
    std::cout << p9 << std::endl;
}

void test_Output_Ex()
{
    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    // testing leading zeros
    PolynomEx<ScalarType> p2{ 2.0, -4.0, 0.0, 3.0, 0.0 };
    std::cout << p2 << std::endl;

    PolynomEx<ScalarType> p3{ 0.0, 0.0, 0.0 };
    std::cout << p3 << std::endl;

    // testing trailing zero
    PolynomEx<ScalarType> p4{ 0.0, 2.0, -4.0, 0.0, 3.0 };
    std::cout << p4 << std::endl;
}

void test_Zero_Ex()
{
    PolynomEx<ScalarType> p1{ };
    std::cout << std::boolalpha << p1 << " - " << "zero(): " << p1.zero() << std::endl;

    PolynomEx<ScalarType> p2 = PolynomEx<ScalarType>{ 1.0 };
    std::cout << std::boolalpha << p2 << " - " << "zero(): " << p2.zero() << std::endl;

    PolynomEx<ScalarType> p3 = PolynomEx<ScalarType>{ 0.0 };
    std::cout << std::boolalpha << p3 << " - " << "zero(): " << p3.zero() << std::endl;
}

void test_Rank_Ex()
{
    PolynomEx<ScalarType> p{ };
    std::cout << p << " - " << "rank(): " << p.rank() << std::endl;

    PolynomEx<ScalarType> p1{ 1.0 };
    std::cout << p1 << " - " << "rank(): " << p1.rank() << std::endl;

    PolynomEx<ScalarType> p2{ 1.0, 2.0 };
    std::cout << p2 << " - " << "rank(): " << p2.rank() << std::endl;

    PolynomEx<ScalarType> p3{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p3 << " - " << "rank(): " << p3.rank() << std::endl;
}

void test_UnaryPolynomOperators_Ex()
{
    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    PolynomEx<ScalarType> p2 = +p1;
    std::cout << p2 << std::endl;

    PolynomEx<ScalarType> p3 = -p1;
    std::cout << p3 << std::endl;
}

void test_Addition_Ex()
{
    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    PolynomEx<ScalarType> p2{ 3.0, 3.0, 5.0 };
    PolynomEx<ScalarType> p3 = p1 + p2;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    PolynomEx<ScalarType> p4{ 1.0, 2.0, 3.0 };
    PolynomEx<ScalarType> p5{ -1.0, -2.0, -3.0 };
    PolynomEx<ScalarType> p6{ p4 + p5 };
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    std::cout << p6 << std::endl;
}

void test_Subtraction_Ex()
{
    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    PolynomEx<ScalarType> p2{ 3.0, 3.0, 5.0 };
    PolynomEx<ScalarType> p3 = p1 - p2;
    std::cout << p2 << std::endl;
    std::cout << p1 << std::endl;
    std::cout << p3 << std::endl;

    PolynomEx<ScalarType> p4{ -1.0, -2.0, -3.0 };
    PolynomEx<ScalarType> p5{ -1.0, -2.0, -3.0 };
    PolynomEx<ScalarType> p6{ p4 - p5 };
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    std::cout << p6 << std::endl;
}

void test_Multiplication_Ex()
{
    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    PolynomEx<ScalarType> p2{ 3.0, 3.0, 5.0 };
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p1 * p2 << std::endl;
}

void test_Division_Ex()
{
    PolynomEx<ScalarType> p1{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
    PolynomEx<ScalarType> p2{ 4.0, 2.0, 0.0, 1.0 };
    PolynomEx<ScalarType> p3{ p1 / p2 };
    std::cout << "p1:    " << p1 << std::endl;
    std::cout << "p2:    " << p2 << std::endl;
    std::cout << "p1/p2: " << p3 << std::endl;

    PolynomEx<ScalarType> p4{ 1.0, 0.0, 1.0, -1.0, 3.0 };
    PolynomEx<ScalarType> p5{ -1.0, 1.0 };
    PolynomEx<ScalarType> p6{ p1 / p2 };
    std::cout << "p4:    " << p4 << std::endl;
    std::cout << "p5:    " << p5 << std::endl;
    std::cout << "p4/p5: " << p6 << std::endl;

    // examples from Arndt Bruenner
    //1.)  Division: (x4 + 3x3 + x2 - 2x) : (x + 2)
    //1.)  Resultat: x3 + x2 - x 
    PolynomEx<ScalarType> p11{ 0.0, -2.0, 1.0, 3.0, 1.0 };
    PolynomEx<ScalarType> p12{ 2.0, 1.0 };
    PolynomEx<ScalarType> p13{ p11 / p12 };
    std::cout << "p1:    " << p11 << std::endl;
    std::cout << "p2:    " << p12 << std::endl;
    std::cout << "p1/p2: " << p13 << std::endl << std::endl;

    //2.) Division: (2x5 - x4 + 5x3 + 6x2 - 2x + 4) : (x3 + 2x + 4)
    //2.) Resultat:  2x2 - x + 1 
    PolynomEx<ScalarType> p21{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
    PolynomEx<ScalarType> p22{ 4.0, 2.0, 0.0, 1.0 };
    PolynomEx<ScalarType> p23{ p21 / p22 };
    std::cout << "p1:    " << p21 << std::endl;
    std::cout << "p2:    " << p22 << std::endl;
    std::cout << "p1/p2: " << p23 << std::endl << std::endl;

    //3.) Division:  (-8x5 + 4x3 + x2) : (-4x3 + 2x2 + x)
    //3.) Resultat:  2x2 + x 
    PolynomEx<ScalarType> p31{ 0.0, 0.0, 1.0, 4.0, 0.0, -8.0 };
    PolynomEx<ScalarType> p32{ 0.0, 1.0, 2.0, -4.0 };
    PolynomEx<ScalarType> p33{ p31 / p32 };
    std::cout << "p1:    " << p31 << std::endl;
    std::cout << "p2:    " << p32 << std::endl;
    std::cout << "p1/p2: " << p33 << std::endl << std::endl;

    //4.) Division:  (8x4 + 8x2 - 1) : (4x2 + 2)
    //4.) Resultat:  2x2 + 1     Rest  -3 
    PolynomEx<ScalarType> p41{ -1.0, 0.0, 8.0, 0.0, 8.0 };
    PolynomEx<ScalarType> p42{ 2.0, 0.0, 4.0 };
    PolynomEx<ScalarType> p43{ p41 / p42 };
    PolynomEx<ScalarType> p43mod{ p41 % p42 };
    std::cout << "p1:    " << p41 << std::endl;
    std::cout << "p2:    " << p42 << std::endl;
    std::cout << "p1/p2: " << p43 << std::endl;
    std::cout << "p1%p2: " << p43mod << std::endl << std::endl;

    //5.) Division:  (-3x5 - x4 + 4x3 + 3/2x + 2) : (3x + 4)
    //5.) Resultat:  -x4 + x3 + 1/2  
    PolynomEx<ScalarType> p51{ 2.0, 1.5, 0.0, 4.0, -1.0, -3.0 };
    PolynomEx<ScalarType> p52{ 4.0, 3.0 };
    PolynomEx<ScalarType> p53{ p51 / p52 };
    std::cout << "p1:    " << p51 << std::endl;
    std::cout << "p2:    " << p52 << std::endl;
    std::cout << "p1/p2: " << p53 << std::endl << std::endl;

    //6.) Division:  (3x4 + 10x3 + 8x2 - 4x) : (3x2 + 4x)
    //6.) Resultat:  x2 + 2x     Rest  -4x 
    PolynomEx<ScalarType> p61{ 0.0, -4.0, 8.0, 10.0, 3.0 };
    PolynomEx<ScalarType> p62{ 0.0, 4.0, 3.0 };
    PolynomEx<ScalarType> p63{ p61 / p62 };
    PolynomEx<ScalarType> p63mod{ p61 % p62 };
    std::cout << "p1:    " << p61 << std::endl;
    std::cout << "p2:    " << p62 << std::endl;
    std::cout << "p1/p2: " << p63 << std::endl;
    std::cout << "p1%p2: " << p63mod << std::endl << std::endl;

    //7.) Division: (2x5 - 5x4 + 2x + 1) : (-x2 + 2x + 1)
    //7.) Resultat: -2x3 + x2 + 1 
    PolynomEx<ScalarType> p71{ 1.0, 2.0, 0.0, 0.0, -5.0, 2.0 };
    PolynomEx<ScalarType> p72{ 1.0, 2.0, -1.0 };
    PolynomEx<ScalarType> p73{ p71 / p72 };
    std::cout << "p1:    " << p71 << std::endl;
    std::cout << "p2:    " << p72 << std::endl;
    std::cout << "p1/p2: " << p73 << std::endl << std::endl;

    //8.) Division:  (15/4x3 + 9x2 - x - 8) : (15/4x2 + 3/2x - 4)
    //8.) Resultat:  x + 2 
    PolynomEx<ScalarType> p81{ -8.0, -1.0, 9.0, 15.0 / 4.0 };
    PolynomEx<ScalarType> p82{ -4.0, 3.0 / 2.0, 15.0 / 4.0 };
    PolynomEx<ScalarType> p83{ p81 / p82 };
    std::cout << "p1:    " << p81 << std::endl;
    std::cout << "p2:    " << p82 << std::endl;
    std::cout << "p1/p2: " << p83 << std::endl << std::endl;

    //9.) Division: (x4 - 7x2 - 10/3x + 4/3) : (x + 2)
    //9.) Resultat: x3 - 2x2 - 3x + 8/3     Rest  -4 
    PolynomEx<ScalarType> p91{ (ScalarType)(4.0 / 3.0),  (ScalarType)(-10.0 / 3.0), -7.0, 0.0, 1.0 };
    PolynomEx<ScalarType> p92{ 2.0, 1.0 };
    PolynomEx<ScalarType> p93{ p91 / p92 };
    PolynomEx<ScalarType> p93mod{ p91 % p92 };
    std::cout << "p1:    " << p91 << std::endl;
    std::cout << "p2:    " << p92 << std::endl;
    std::cout << "p1/p2: " << p93 << std::endl;
    std::cout << "p1%p2: " << p93mod << std::endl << std::endl;

    //10.) Division: (4x3 + 3x2 - 8x + 4) : (4x2 - 5x + 2)
    //10.) Resultat:  x + 2 
    PolynomEx<ScalarType> p101{ 4.0, -8.0, 3.0, 4.0 };
    PolynomEx<ScalarType> p102{ 2.0, -5.0, 4.0 };
    PolynomEx<ScalarType> p103{ p101 / p102 };
    std::cout << "p1:    " << p101 << std::endl;
    std::cout << "p2:    " << p102 << std::endl;
    std::cout << "p1/p2: " << p103 << std::endl << std::endl;
}

void test_Modulo_Ex()
{
    PolynomEx<ScalarType> p1{ 0.0, -4.0, 8.0, 10.0, 3.0 };
    PolynomEx<ScalarType> p2{ 0.0, 4.0, 3.0 };
    PolynomEx<ScalarType> p3{ p1 % p2 };
    std::cout << "p1:    " << p1 << std::endl;
    std::cout << "p2:    " << p2 << std::endl;
    std::cout << "p1%p2: " << p3 << std::endl;
}

void test_AssignmentOperators_Ex()
{
    PolynomEx<ScalarType> p1{ 1.0, 2.0, 3.0 };
    std::cout << p1 << std::endl;

    PolynomEx<ScalarType> p2{ 3.0, 2.0, 1.0 };
    std::cout << p2 << std::endl;

    p1 += p2;
    std::cout << p1 << std::endl;
    p1 -= p2;
    std::cout << p1 << std::endl;
    p1 *= p2;
    std::cout << p1 << std::endl;
    p1 /= p2;
    std::cout << p1 << std::endl;
    p1 %= p2;
    std::cout << p1 << std::endl;
}

void test_Evaluation_Ex()
{
    PolynomEx<ScalarType> p1{ 1.0 };
    std::cout << "p1: " << p1 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p1(0.0) = " << p1(0.0) << std::endl;
    std::cout << "p1(1.0) = " << p1(1.0) << std::endl;
    std::cout << "p1(2.0) = " << p1(2.0) << std::endl;

    PolynomEx<ScalarType> p2{ 1.0, 3.0 };
    std::cout << "p2: " << p2 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p2(0.0) = " << p2(0.0) << std::endl;
    std::cout << "p2(1.0) = " << p2(1.0) << std::endl;
    std::cout << "p2(2.0) = " << p2(2.0) << std::endl;

    PolynomEx<ScalarType> p3{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << "p3: " << p3 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p3(0.0) = " << p3(0.0) << std::endl;
    std::cout << "p3(1.0) = " << p3(1.0) << std::endl;
    std::cout << "p3(2.0) = " << p3(2.0) << std::endl;
}

void test_ComparisonOperators_Ex()
{

    PolynomEx<ScalarType> p1{ 2.0, -4.0, 0.0, 3.0 };
    PolynomEx<ScalarType> p2{ 2.0, -4.0, 0.0, 3.0 };

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    // PolynomEx<ScalarType> p2{ 3.0, 3.0, 5.0 };

    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;

    //std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
    //std::cout << "p1 <  p2: " << (p1 < p2) << std::endl;
    //std::cout << "p1 <= p2: " << (p1 <= p2) << std::endl;
    //std::cout << "p1 >  p2: " << (p1 > p2) << std::endl;
    //std::cout << "p1 >= p2: " << (p1 >= p2) << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
