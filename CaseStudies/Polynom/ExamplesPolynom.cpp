// =====================================================================================
// ExamplesPolynom.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Polynom.h"

// testing examples from script
void test_script_01()
{
    Polynom p1{ };
    Polynom p2{ -5.0, +6.0, -7.0 };

    std::cout << p1 << std::endl;
    std::cout << p1.rank() << std::endl;
    std::cout << std::boolalpha << p1.zero() << std::endl;

    std::cout << p2 << std::endl;
    std::cout << p2.rank() << std::endl;
    std::cout << std::boolalpha << p2.zero() << std::endl;

    Polynom p{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p << std::endl;
}

// testing examples from script
void test_script_02()
{
    //Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    //Polynom p2{ 3.0, 3.0, 5.0 };
    //Polynom p3 = p1 - p2;
    //std::cout << p1 << std::endl;
    //std::cout << p2 << std::endl;
    //std::cout << p3 << std::endl;

    //Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    //Polynom p2{ 3.0, 3.0, 5.0 };
    //std::cout << "p1*p2: " << p1 * p2 << std::endl;

    //Polynom p1{ 0, -4, 8, 10, 3 };
    //Polynom p2{ 0, 4, 3 };
    //std::cout << "p1%p2: " << p1 % p2 << std::endl;

    //Polynom p1{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
    //Polynom p2{ 4.0, 2.0, 0.0, 1.0 };
    //std::cout << p1 << std::endl;
    //std::cout << p2 << std::endl;
    //std::cout << "p1/p2: " << p1 / p2 << std::endl;

    Polynom p1{ 1.0, 2.0, 3.0 };
    Polynom p2{ 3.0, 2.0, 1.0 };
    std::cout << p1 << std::endl;
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

// testing c'tors and d'tor
void test_Ctors()
{
    Polynom p{ };
    std::cout << p << std::endl;

    Polynom p1{ 1.0 };
    std::cout << p1 << std::endl;

    Polynom p2{ 1.0, 2.0, 3.0 };
    std::cout << p2 << std::endl;

    Polynom p3{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p3 << std::endl;

    Polynom p4{ -1.0, 0.0, -2.0, 0.0, -3.0 };
    std::cout << p4 << std::endl;

    Polynom p5{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p5 << std::endl;

    Polynom p6 = p5;
    std::cout << p6 << std::endl;

    Polynom p7{ p5 };
    std::cout << p7 << std::endl;
}

void test_RemoveLeadingZeros()
{
    Polynom p1{ };
    std::cout << p1 << std::endl;

    Polynom p2{ 0.0 };
    std::cout << p2 << std::endl;

    Polynom p3{ 0.0, 0.0 };
    std::cout << p3 << std::endl;

    Polynom p4{ 0.0, 0.0, 0.0 };
    std::cout << p4 << std::endl;

    Polynom p5{ 1.0 };
    std::cout << p5 << std::endl;

    Polynom p6{ 1.0, 0.0 };
    std::cout << p6 << std::endl;

    Polynom p7{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p7 << std::endl;

    Polynom p8{ 1.0, 0.0, 2.0, 0.0, 3.0, 0.0 };
    std::cout << p8 << std::endl;

    Polynom p9{ 1.0, 0.0, 2.0, 0.0, 3.0, 0.0, 0.0 };
    std::cout << p9 << std::endl;
}

void test_Output()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    // testing leading zeros
    Polynom p2{ 0.0, 0.0, 0.0 };
    std::cout << p2 << std::endl;

    // testing trailing zero
    Polynom p3{ 0.0, 0.0, 2.0, -4.0, 0.0, 3.0 };
    std::cout << p3 << std::endl;
}

void test_Zero()
{
    Polynom p1{ };
    std::cout << std::boolalpha << p1 << " - " << "zero(): " << p1.zero() << std::endl;

    Polynom p2 = Polynom{ 1.0 };
    std::cout << std::boolalpha << p2 << " - " << "zero(): " << p2.zero() << std::endl;

    Polynom p3 = Polynom{ 0.0 };
    std::cout << std::boolalpha << p3 << " - " << "zero(): " << p3.zero() << std::endl;
}

void test_Rank()
{
    Polynom p{ };
    std::cout << p << " - " << "rank(): " << p.rank() << std::endl;

    Polynom p1{ 1.0 };
    std::cout << p1 << " - " << "rank(): " << p1.rank() << std::endl;

    Polynom p2{ 1.0, 2.0 };
    std::cout << p2 << " - " << "rank(): " << p2.rank() << std::endl;

    Polynom p3{ 1.0, 0.0, 2.0, 0.0, 3.0 };
    std::cout << p3 << " - " << "rank(): " << p3.rank() << std::endl;
}

void test_UnaryPolynomOperators() 
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    Polynom p2 = +p1;
    std::cout << p2 << std::endl;

    Polynom p3 = -p1;
    std::cout << p3 << std::endl;
}

void test_Addition()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    Polynom p2{ 3.0, 3.0, 5.0 };
    Polynom p3 = p1 + p2;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    Polynom p4{ 1.0, 2.0, 3.0 };
    Polynom p5{ -1.0, -2.0, -3.0 };
    Polynom p6{ p4 + p5 };
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    std::cout << p6 << std::endl;
}

void test_Subtraction()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    Polynom p2{ 3.0, 3.0, 5.0 };
    Polynom p3 = p1 - p2;
    std::cout << p2 << std::endl;
    std::cout << p1 << std::endl;
    std::cout << p3 << std::endl;

    Polynom p4{ -1.0, -2.0, -3.0 };
    Polynom p5{ -1.0, -2.0, -3.0 };
    Polynom p6{ p4 - p5 };
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    std::cout << p6 << std::endl;
}

void test_Multiplication()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    Polynom p2{ 3.0, 3.0, 5.0 };
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p1 * p2 << std::endl;
}

void test_Division()
{
    Polynom p1{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
    Polynom p2{ 4.0, 2.0, 0.0, 1.0 };
    Polynom p3{ p1 / p2 };
    std::cout << "p1:    " << p1 << std::endl;
    std::cout << "p2:    " << p2 << std::endl;
    std::cout << "p1/p2: " << p3 << std::endl;

    Polynom p4{ 1.0, 0.0, 1.0, -1.0, 3.0 };
    Polynom p5{ -1.0, 1.0 };
    Polynom p6{ p1 / p2 };
    std::cout << "p4:    " << p4 << std::endl;
    std::cout << "p5:    " << p5 << std::endl;
    std::cout << "p4/p5: " << p6 << std::endl;

    // examples from Arndt Bruenner
    //1.)  Division: (x4 + 3x3 + x2 - 2x) : (x + 2)
    //1.)  Resultat: x3 + x2 - x 
    Polynom p11{ 0.0, -2.0, 1.0, 3.0, 1.0 };
    Polynom p12{ 2.0, 1.0 };
    Polynom p13{ p11 / p12 };
    std::cout << "p1:    " << p11 << std::endl;
    std::cout << "p2:    " << p12 << std::endl;
    std::cout << "p1/p2: " << p13 << std::endl << std::endl;

    //2.) Division: (2x5 - x4 + 5x3 + 6x2 - 2x + 4) : (x3 + 2x + 4)
    //2.) Resultat:  2x2 - x + 1 
    Polynom p21{ 4.0, -2.0, 6.0, 5.0, -1.0, 2.0 };
    Polynom p22{ 4.0, 2.0, 0.0, 1.0 };
    Polynom p23{ p21 / p22 };
    std::cout << "p1:    " << p21 << std::endl;
    std::cout << "p2:    " << p22 << std::endl;
    std::cout << "p1/p2: " << p23 << std::endl << std::endl;

    //3.) Division:  (-8x5 + 4x3 + x2) : (-4x3 + 2x2 + x)
    //3.) Resultat:  2x2 + x 
    Polynom p31{ 0.0, 0.0, 1.0, 4.0, 0.0, -8.0 };
    Polynom p32{ 0.0, 1.0, 2.0, -4.0 };
    Polynom p33{ p31 / p32 };
    std::cout << "p1:    " << p31 << std::endl;
    std::cout << "p2:    " << p32 << std::endl;
    std::cout << "p1/p2: " << p33 << std::endl << std::endl;

    //4.) Division:  (8x4 + 8x2 - 1) : (4x2 + 2)
    //4.) Resultat:  2x2 + 1     Rest  -3 
    Polynom p41{ -1.0, 0.0, 8.0, 0.0, 8.0 };
    Polynom p42{ 2.0, 0.0, 4.0 };
    Polynom p43{ p41 / p42 };
    Polynom p43mod{ p41 % p42 };
    std::cout << "p1:    " << p41 << std::endl;
    std::cout << "p2:    " << p42 << std::endl;
    std::cout << "p1/p2: " << p43 << std::endl;
    std::cout << "p1%p2: " << p43mod << std::endl << std::endl;

    //5.) Division:  (-3x5 - x4 + 4x3 + 3/2x + 2) : (3x + 4)
    //5.) Resultat:  -x4 + x3 + 1/2  
    Polynom p51{ 2.0, 1.5, 0.0, 4.0, -1.0, -3.0 };
    Polynom p52{ 4.0, 3.0 };
    Polynom p53{ p51 / p52 };
    std::cout << "p1:    " << p51 << std::endl;
    std::cout << "p2:    " << p52 << std::endl;
    std::cout << "p1/p2: " << p53 << std::endl << std::endl;

    //6.) Division:  (3x4 + 10x3 + 8x2 - 4x) : (3x2 + 4x)
    //6.) Resultat:  x2 + 2x     Rest  -4x 
    Polynom p61{ 0.0, -4.0, 8.0, 10.0, 3.0 };
    Polynom p62{ 0.0, 4.0, 3.0 };
    Polynom p63{ p61 / p62 };
    Polynom p63mod{ p61 % p62 };
    std::cout << "p1:    " << p61 << std::endl;
    std::cout << "p2:    " << p62 << std::endl;
    std::cout << "p1/p2: " << p63 << std::endl;
    std::cout << "p1%p2: " << p63mod << std::endl << std::endl;

    //7.) Division: (2x5 - 5x4 + 2x + 1) : (-x2 + 2x + 1)
    //7.) Resultat: -2x3 + x2 + 1 
    Polynom p71{ 1.0, 2.0, 0.0, 0.0, -5.0, 2.0 };
    Polynom p72{ 1.0, 2.0, -1.0 };
    Polynom p73{ p71 / p72 };
    std::cout << "p1:    " << p71 << std::endl;
    std::cout << "p2:    " << p72 << std::endl;
    std::cout << "p1/p2: " << p73 << std::endl << std::endl;

    //8.) Division:  (15/4x3 + 9x2 - x - 8) : (15/4x2 + 3/2x - 4)
    //8.) Resultat:  x + 2 
    Polynom p81{ -8.0, -1.0, 9.0, 15.0/4.0 };
    Polynom p82{ -4.0, 3.0/2.0, 15.0 / 4.0 };
    Polynom p83{ p81 / p82 };
    std::cout << "p1:    " << p81 << std::endl;
    std::cout << "p2:    " << p82 << std::endl;
    std::cout << "p1/p2: " << p83 << std::endl << std::endl;

    //9.) Division: (x4 - 7x2 - 10/3x + 4/3) : (x + 2)
    //9.) Resultat: x3 - 2x2 - 3x + 8/3     Rest  -4 
    Polynom p91{ 4.0/3.0, -10.0 / 3.0, -7.0, 0.0, 1.0 };
    Polynom p92{ 2.0, 1.0 };
    Polynom p93{ p91 / p92 };
    Polynom p93mod{ p91 % p92 };
    std::cout << "p1:    " << p91 << std::endl;
    std::cout << "p2:    " << p92 << std::endl;
    std::cout << "p1/p2: " << p93 << std::endl;
    std::cout << "p1%p2: " << p93mod << std::endl << std::endl;

    //10.) Division: (4x3 + 3x2 - 8x + 4) : (4x2 - 5x + 2)
    //10.) Resultat:  x + 2 
    Polynom p101{ 4.0, -8.0, 3.0, 4.0 };
    Polynom p102{ 2.0, -5.0, 4.0 };
    Polynom p103{ p101 / p102 };
    std::cout << "p1:    " << p101 << std::endl;
    std::cout << "p2:    " << p102 << std::endl;
    std::cout << "p1/p2: " << p103 << std::endl << std::endl;
}

void test_Modulo()
{
    Polynom p1{ 0.0, -4.0, 8.0, 10.0, 3.0 };
    Polynom p2{ 0.0, 4.0, 3.0 };
    Polynom p3{ p1 % p2 };
    std::cout << "p1:    " << p1 << std::endl;
    std::cout << "p2:    " << p2 << std::endl;
    std::cout << "p1%p2: " << p3 << std::endl;
}

void test_AssignmentOperators()
{
    Polynom p1{ 1.0, 2.0, 3.0 };
    std::cout << p1 << std::endl;

    Polynom p2{ 3.0, 2.0, 1.0 };
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

void test_Evaluation()
{
    Polynom p1{ 1.0 };
    std::cout << "p1: " << p1 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p1(0.0) = " << p1(0.0) << std::endl;
    std::cout << "p1(1.0) = " << p1(1.0) << std::endl;
    std::cout << "p1(2.0) = " << p1(2.0) << std::endl;

    Polynom p2{ 1.0, 3.0 };
    std::cout << "p2: " << p2 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p2(0.0) = " << p2(0.0) << std::endl;
    std::cout << "p2(1.0) = " << p2(1.0) << std::endl;
    std::cout << "p2(2.0) = " << p2(2.0) << std::endl;

    Polynom p3{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << "p3: " << p3 << std::endl;

    // values of p at 0.0, 1.0 and 2.0
    std::cout << "p3(0.0) = " << p3(0.0) << std::endl;
    std::cout << "p3(1.0) = " << p3(1.0) << std::endl;
    std::cout << "p3(2.0) = " << p3(2.0) << std::endl;
}

void test_ComparisonOperators()
{

    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    Polynom p2{ 2.0, -4.0, 0.0, 3.0 };

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    // Polynom p2{ 3.0, 3.0, 5.0 };

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
