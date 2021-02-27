// =====================================================================================
// ExamplesCollatzEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Polynom.h"

// testing c'tors and d'tor
void Testing_Ctors()
{
    Polynom p{ };
    std::cout << p << std::endl;

    Polynom p1{ 5.0 };
    std::cout << p1 << std::endl;

    Polynom p2{ 5.0, 6.0 };
    std::cout << p2 << std::endl;

    Polynom p3{ 5.0, 6.0, 7.0 };
    std::cout << p3 << std::endl;

    Polynom p4{ 1.0, 2.0, 3.0, 0.0, 0.0, 0.0 };
    std::cout << p4 << std::endl;

    Polynom p5{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p5 << std::endl;

    Polynom p6 = p5;
    std::cout << p6 << std::endl;

    Polynom p7{ p5 };
    std::cout << p7 << std::endl;
}

void Testing_Output()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    // testing leading zeros
    Polynom p2{ 2.0, -4.0, 0.0, 3.0, 0.0 };
    std::cout << p2 << std::endl;

    Polynom p3{ 0.0, 0.0, 0.0 };
    std::cout << p3 << std::endl;

    // testing trailing zero
    Polynom p4{ 0.0, 2.0, -4.0, 0.0, 3.0 };
    std::cout << p4 << std::endl;
}

void Testing_IsZero()
{
    Polynom p1{ };
    std::cout << std::boolalpha << p1 << " - " << "zero(): " << p1.zero() << std::endl;

    Polynom p2 = Polynom{ 1.0 };
    std::cout << std::boolalpha << p2 << " - " << "zero(): " << p2.zero() << std::endl;

    Polynom p3 = Polynom{ 0.0 };
    std::cout << std::boolalpha << p3 << " - " << "zero(): " << p3.zero() << std::endl;
}

void Testing_UnaryPolynomOperators() 
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    Polynom p2 = +p1;
    std::cout << p2 << std::endl;

    Polynom p3 = -p1;
    std::cout << p3 << std::endl;
}

void Testing_PolynomAddition()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    Polynom p2{ 3.0, 3.0, 5.0 };
    std::cout << p2 << std::endl;

    Polynom p3 = p1 + p2;
    std::cout << p3 << std::endl;
}

void Testing_PolynomSubtraction()
{
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    Polynom p2{ 3.0, 3.0, 5.0 };
    std::cout << p2 << std::endl;

    Polynom p3 = p1 - p2;
    std::cout << p3 << std::endl;
}
//
//void Testing_AssignmentOperators()
//{
//    double coeffs1[] = { 1.0, 2.0, 3.0 };
//    Polynom p1(coeffs1, 3);
//    std::cout << p1 << std::endl;
//
//    double coeffs2[] = { 3.0, 2.0, 1.0 };
//    Polynom p2(coeffs2, 3);
//    std::cout << p2 << std::endl;
//
//    p1 += p2;
//    std::cout << p1 << std::endl;
//    p1 -= p2;
//    std::cout << p1 << std::endl;
//    p1 *= p2;
//    std::cout << p1 << std::endl;
//    p1 /= p2;
//    std::cout << p1 << std::endl;
//    p1 %= p2;
//    std::cout << p1 << std::endl;
//}
//


void Testing_PolynomMultiplication()
{
    //std::vector<double> coeffs1 = { 2.0, -4.0, 0.0, 3.0 };
    Polynom p1{ 2.0, -4.0, 0.0, 3.0 };
    std::cout << p1 << std::endl;

    //std::vector<double> coeffs2 = { 3.0, 3.0, 5.0 };
    Polynom p2{ 3.0, 3.0, 5.0 };
    std::cout << p2 << std::endl;

    std::cout << p1 * p2 << std::endl;
}
//
//void Testing_ComparisonOperators()
//{
//    double coeffs1[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p1(coeffs1, 4);
//    double coeffs2[] = { 3.0, 3.0, 5.0 };
//    Polynom p2(coeffs2, 3);
//
//    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
//    std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
//    std::cout << "p1 <  p2: " << (p1 < p2) << std::endl;
//    std::cout << "p1 <= p2: " << (p1 <= p2) << std::endl;
//    std::cout << "p1 >  p2: " << (p1 > p2) << std::endl;
//    std::cout << "p1 >= p2: " << (p1 >= p2) << std::endl;
//}
//
//void Testing_Evaluation_ArraySubscriptOperator()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    std::cout << "p: " << p << std::endl << std::endl;
//
//    // values of p at 0.0, 1.0 and 2.0
//    std::cout << "p(0.0) = " << p[0.0] << std::endl;
//    std::cout << "p(1.0) = " << p[1.0] << std::endl;
//    std::cout << "p(2.0) = " << p[2.0] << std::endl;
//}
//
//void Testing_Evaluation_FunctionCallOperator()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    std::cout << "p: " << p << std::endl << std::endl;
//
//    // values of p at 0.0, 1.0 and 2.0
//    std::cout << "p(0.0) = " << p(0.0) << std::endl;
//    std::cout << "p(1.0) = " << p(1.0) << std::endl;
//    std::cout << "p(2.0) = " << p(2.0) << std::endl;
//}
//
//void Testing_Evaluation_BothVariants()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    std::cout << "p: " << p << std::endl << std::endl;
//
//    // values of p at 0.0, 1.0 and 2.0, using array subscripting operator
//    std::cout << "p(0.0) = " << p[0.0] << std::endl;
//    std::cout << "p(1.0) = " << p[1.0] << std::endl;
//    std::cout << "p(2.0) = " << p[2.0] << std::endl;
//
//    // values of p at 0.0, 1.0 and 2.0, using function call operator
//    std::cout << "p(0.0) = " << p(0.0) << std::endl;
//    std::cout << "p(1.0) = " << p(1.0) << std::endl;
//    std::cout << "p(2.0) = " << p(2.0) << std::endl;
//}
//


#if 0

void Testing_Division01()
{
    std::vector<double> values1 = { 4, -2, 6, 5, -1, 2 };
    Polynom p1(values1);
    std::cout << "p1:    " << p1 << std::endl;

    std::vector<double> values2 = { 4, 2, 0, 1 };
    Polynom p2(values2);
    std::cout << "p2:    " << p2 << std::endl;

    Polynom p3 = p1 / p2;
    std::cout << "p1/p2: " << p3 << std::endl;
}

void Testing_Division02()
{
    std::vector<double> values1 = { 1, 0, 1, -1, 3 };
    Polynom p1(values1);
    std::cout << "p1:    " << p1 << std::endl;

    std::vector<double> values2 = { -1, 1 };
    Polynom p2(values2);
    std::cout << "p2:    " << p2 << std::endl;

    Polynom p3 = p1 / p2;
    std::cout << "p1/p2: " << p3 << std::endl;
}

void Testing_Modulo()
{
    std::vector<double> values1 = { 0, -4, 8, 10, 3 };
    Polynom p1(values1);
    std::cout << "p1:    " << p1 << std::endl;

    std::vector<double> values2 = { 0, 4, 3 };
    Polynom p2(values2);
    std::cout << "p2:    " << p2 << std::endl;

    Polynom p3 = p1 % p2;
    std::cout << "p1%p2: " << p3 << std::endl;
}

void Testing_Division_ArndtBruenner()
{
    //1.)  (x4 + 3x3 + x2 - 2x) : (x + 2)
    //1.)  x3 + x2 - x 

    std::vector<double> values11 = { 0, -2, 1, 3, 1 };
    Polynom p11(values11);
    std::cout << "p1:    " << p11 << std::endl;

    std::vector<double> values12 = { 2, 1 };
    Polynom p12(values12);
    std::cout << "p2:    " << p12 << std::endl;

    Polynom p13 = p11 / p12;
    std::cout << "p1/p2: " << p13 << std::endl << std::endl;

    //2.)    (2x5 - x4 + 5x3 + 6x2 - 2x + 4) : (x3 + 2x + 4)
    //2.)    2x2 - x + 1 
    std::vector<double> values21 = { 4, -2, 6, 5, -1, 2 };
    Polynom p21(values21);
    std::cout << "p1:    " << p21 << std::endl;

    std::vector<double> values22 = { 4, 2, 0, 1 };
    Polynom p22(values22);
    std::cout << "p2:    " << p22 << std::endl;

    Polynom p23 = p21 / p22;
    std::cout << "p1/p2: " << p23 << std::endl << std::endl;


    //3.)    (-8x5 + 4x3 + x2) : (-4x3 + 2x2 + x)
    //3.)    2x2 + x 
    std::vector<double> values31 = { 0, 0, 1, 4, 0, -8 };
    Polynom p31(values31);
    std::cout << "p1:    " << p31 << std::endl;

    std::vector<double> values32 = { 0, 1, 2, -4 };
    Polynom p32(values32);
    std::cout << "p2:    " << p32 << std::endl;

    Polynom p33 = p31 / p32;
    std::cout << "p1/p2: " << p33 << std::endl << std::endl;


    //4.)    (8x4 + 8x2 - 1) : (4x2 + 2)
    //4.)    2x2 + 1     Rest  -3 

    std::vector<double> values41 = { -1, 0, 8, 0, 8 };
    Polynom p41(values41);
    std::cout << "p1:    " << p41 << std::endl;

    std::vector<double> values42 = { 2, 0, 4 };
    Polynom p42(values42);
    std::cout << "p2:    " << p42 << std::endl;

    Polynom p43 = p41 / p42;
    Polynom p43mod = p41 % p42;
    std::cout << "p1/p2: " << p43 << std::endl;
    std::cout << "p1%p2: " << p43mod << std::endl << std::endl;

    //5.)    (-3x5 - x4 + 4x3 + 3/2x + 2) : (3x + 4)
    //5.)    -x4 + x3 + 1/2  

    std::vector<double> values51 = { 2, 1.5, 0, 4, -1, -3 };
    Polynom p51(values51);
    std::cout << "p1:    " << p51 << std::endl;

    std::vector<double> values52 = { 4, 3 };
    Polynom p52(values52);
    std::cout << "p2:    " << p52 << std::endl;

    Polynom p53 = p51 / p52;
    std::cout << "p1/p2: " << p53 << std::endl << std::endl;

    //6.)    (3x4 + 10x3 + 8x2 - 4x) : (3x2 + 4x)
    //6.)    x2 + 2x     Rest  -4x 

    std::vector<double> values61 = { 0, -4, 8, 10, 3 };
    Polynom p61(values61);
    std::cout << "p1:    " << p61 << std::endl;

    std::vector<double> values62 = { 0, 4, 3 };
    Polynom p62(values62);
    std::cout << "p2:    " << p62 << std::endl;

    Polynom p63 = p61 / p62;
    Polynom p63mod = p61 % p62;
    std::cout << "p1/p2: " << p63 << std::endl;
    std::cout << "p1%p2: " << p63mod << std::endl << std::endl;

    //7.)    (2x5 - 5x4 + 2x + 1) : (-x2 + 2x + 1)
    //7.)    -2x3 + x2 + 1 

    std::vector<double> values71 = { 1, 2, 0, 0, -5, 2 };
    Polynom p71(values71);
    std::cout << "p1:    " << p71 << std::endl;

    std::vector<double> values72 = { 1, 2, -1 };
    Polynom p72(values72);
    std::cout << "p2:    " << p72 << std::endl;

    Polynom p73 = p71 / p72;
    std::cout << "p1/p2: " << p73 << std::endl << std::endl;

    //8.)    (15/4x3 + 9x2 - x - 8) : (15/4x2 + 3/2x - 4)
    //8.)    x + 2 

    std::vector<double> values81 = { -8, -1, 9, 15.0 / 4.0 };
    Polynom p81(values81);
    std::cout << "p1:    " << p81 << std::endl;

    std::vector<double> values82 = { -4, 3.0 / 2.0, 15.0 / 4.0 };
    Polynom p82(values82);
    std::cout << "p2:    " << p82 << std::endl;

    Polynom p83 = p81 / p82;
    std::cout << "p1/p2: " << p83 << std::endl << std::endl;

    //9.)    (x4 - 7x2 - 10/3x + 4/3) : (x + 2)
    //9.)    x3 - 2x2 - 3x + 8/3     Rest  -4 

    std::vector<double> values91 = { 4.0 / 3.0, -10 / 3.0, -7, 0, 1 };
    Polynom p91(values91);
    std::cout << "p1:    " << p91 << std::endl;

    std::vector<double> values92 = { 2, 1 };
    Polynom p92(values92);
    std::cout << "p2:    " << p92 << std::endl;

    Polynom p93 = p91 / p92;
    Polynom p93mod = p91 % p92;
    std::cout << "p1/p2: " << p93 << std::endl;
    std::cout << "p1%p2: " << p93mod << std::endl << std::endl;


    //10.)   (4x3 + 3x2 - 8x + 4) : (4x2 - 5x + 2)
    //10.)    x + 2 

    std::vector<double> values101 = { 4, -8, 3, 4 };
    Polynom p101(values101);
    std::cout << "p1:    " << p101 << std::endl;

    std::vector<double> values102 = { 2, -5, 4 };
    Polynom p102(values102);
    std::cout << "p2:    " << p102 << std::endl;

    Polynom p103 = p101 / p102;
    std::cout << "p1/p2: " << p103 << std::endl << std::endl;
}


void Testing_Division()
{
    // TestingDivision01();
   // TestingDivision02();
    //TestingDivision_ArndtBruenner();
    // TestingModulo();
}

#endif

// =====================================================================================
// End-of-File
// =====================================================================================
