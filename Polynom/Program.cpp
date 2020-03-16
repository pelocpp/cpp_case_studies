#include <iostream>
using namespace std;

#include "Polynom.h"

void TestingCtorsDtor();
void TestingOutput();
void TestingIsZero();
void TestingAssignmentOperator();
void TestingAssignmentOperators();
void TestingPolynomAddition();
void TestingPolynomSubtraction();
void TestingPolynomMultiplication();
void TestingEvaluation_ArraySubscriptOperator();
void TestingEvaluation_FunctionCallOperator();
void TestingEvaluation_BothVariants();
void TestingComparisonOperators();
void TestingDivision();

int main()
{
    // TestingCtorsDtor();
    // TestingOutput();
    // TestingIsZero();
    //TestingAssignmentOperator();
    //TestingAssignmentOperators();
    // TestingPolynomAddition();
    // TestingPolynomSubtraction();
    //TestingPolynomMultiplication();
    //TestingEvaluation_ArraySubscriptOperator();
    //TestingEvaluation_FunctionCallOperator();
    //TestingEvaluation_BothVariants();
    //TestingComparisonOperators();
    TestingDivision();

    return 0;
}

// testing c'tors and d'tor
void TestingCtorsDtor()
{
    Polynom p;
    cout << p << endl;

    std::vector<double> coeffs1 = { 5.0 };
    Polynom p1(coeffs1);
    cout << p1 << endl;

    std::vector<double> coeffs2 = { 5.0, 6.0 };
    Polynom p2(coeffs2);
    cout << p2 << endl;

    std::vector<double> coeffs3 = { 5.0, 6.0, 7.0 };
    Polynom p3(coeffs3);
    cout << p3 << endl;

    std::vector<double> coeffs4 = { 1.0, 2.0, 3.0, 0.0, 0.0, 0.0 };
    Polynom p4(coeffs4);
    cout << p4 << endl;

    Polynom p5 = p4;
    cout << p5 << endl;

    Polynom p6 (p4);
    cout << p6 << endl;
}

void TestingOutput()
{
    std::vector<double> coeffs1 = { 2.0, -4.0, 0.0, 3.0 };
    Polynom p1(coeffs1);
    cout << p1 << endl;

    // testing leading zeros
    std::vector<double> coeffs2 = { 2.0, -4.0, 0.0, 3.0, 0.0 };
    Polynom p2(coeffs2);
    cout << p2 << endl;

    std::vector<double> coeffs3 = { 0.0, 0.0, 0.0 };
    Polynom p3(coeffs3);
    cout << p3 << endl;

    // testing trailing zero
    std::vector<double> coeffs4 = { 0.0, 2.0, -4.0, 0.0, 3.0 };
    Polynom p4(coeffs4);
    cout << p4 << endl;
}

void TestingIsZero()
{
    Polynom p;
    cout << p << " -- " << "IsZero: " << p.IsZero() << endl;

    std::vector<double> coeffs = { 1.0 };
    Polynom p1 = Polynom(coeffs);
    cout << p1 << " -- " << "IsZero: " << p1.IsZero() << endl;
}

void TestingPolynomAddition()
{
    std::vector<double> coeffs1 = { 2.0, -4.0, 0.0, 3.0 };
    Polynom p1(coeffs1);
    cout << p1 << endl;

    std::vector<double> coeffs2 = { 3.0, 3.0, 5.0 };
    Polynom p2(coeffs2);
    cout << p2 << endl;

    Polynom p3 = p1 + p2;
    cout << p3 << endl;
}

void TestingPolynomSubtraction()
{
    std::vector<double> coeffs1 = { 2.0, -4.0, 0.0, 3.0 };
    Polynom p1(coeffs1);
    cout << p1 << endl;

    std::vector<double> coeffs2 = { 3.0, 3.0, 5.0 };
    Polynom p2(coeffs2);
    cout << p2 << endl;

    Polynom p3 = p1 - p2;
    cout << p3 << endl;
}
//
//void TestingAssignmentOperators()
//{
//    double coeffs1[] = { 1.0, 2.0, 3.0 };
//    Polynom p1(coeffs1, 3);
//    cout << p1 << endl;
//
//    double coeffs2[] = { 3.0, 2.0, 1.0 };
//    Polynom p2(coeffs2, 3);
//    cout << p2 << endl;
//
//    p1 += p2;
//    cout << p1 << endl;
//    p1 -= p2;
//    cout << p1 << endl;
//    p1 *= p2;
//    cout << p1 << endl;
//    p1 /= p2;
//    cout << p1 << endl;
//    p1 %= p2;
//    cout << p1 << endl;
//}
//
//void TestingAssignmentOperator()
//{
//    double coeffs1[] = { 1.0, 2.0, 3.0 };
//    Polynom p1(coeffs1, 3);
//    cout << p1 << endl;
//
//    double coeffs2[] = { 9.0, 8.0, 7.0 };
//    Polynom p2(coeffs2, 3);
//    cout << p2 << endl;
//
//    p2 = p1;
//    cout << p1 << endl;
//}

void TestingPolynomMultiplication()
{
    std::vector<double> coeffs1 = { 2.0, -4.0, 0.0, 3.0 };
    Polynom p1(coeffs1);
    cout << p1 << endl;

    std::vector<double> coeffs2 = { 3.0, 3.0, 5.0 };
    Polynom p2(coeffs2);
    cout << p2 << endl;

    cout << p1 * p2 << endl;
}
//
//void TestingComparisonOperators()
//{
//    double coeffs1[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p1(coeffs1, 4);
//    double coeffs2[] = { 3.0, 3.0, 5.0 };
//    Polynom p2(coeffs2, 3);
//
//    cout << "p1 == p2: " << (p1 == p2) << endl;
//    cout << "p1 != p2: " << (p1 != p2) << endl;
//    cout << "p1 <  p2: " << (p1 < p2) << endl;
//    cout << "p1 <= p2: " << (p1 <= p2) << endl;
//    cout << "p1 >  p2: " << (p1 > p2) << endl;
//    cout << "p1 >= p2: " << (p1 >= p2) << endl;
//}
//
//void TestingEvaluation_ArraySubscriptOperator()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    cout << "p: " << p << endl << endl;
//
//    // values of p at 0.0, 1.0 and 2.0
//    cout << "p(0.0) = " << p[0.0] << endl;
//    cout << "p(1.0) = " << p[1.0] << endl;
//    cout << "p(2.0) = " << p[2.0] << endl;
//}
//
//void TestingEvaluation_FunctionCallOperator()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    cout << "p: " << p << endl << endl;
//
//    // values of p at 0.0, 1.0 and 2.0
//    cout << "p(0.0) = " << p(0.0) << endl;
//    cout << "p(1.0) = " << p(1.0) << endl;
//    cout << "p(2.0) = " << p(2.0) << endl;
//}
//
//void TestingEvaluation_BothVariants()
//{
//    double coeffs[] = { 2.0, -4.0, 0.0, 3.0 };
//    Polynom p(coeffs, 4);
//    cout << "p: " << p << endl << endl;
//
//    // values of p at 0.0, 1.0 and 2.0, using array subscripting operator
//    cout << "p(0.0) = " << p[0.0] << endl;
//    cout << "p(1.0) = " << p[1.0] << endl;
//    cout << "p(2.0) = " << p[2.0] << endl;
//
//    // values of p at 0.0, 1.0 and 2.0, using function call operator
//    cout << "p(0.0) = " << p(0.0) << endl;
//    cout << "p(1.0) = " << p(1.0) << endl;
//    cout << "p(2.0) = " << p(2.0) << endl;
//}
//
void TestingDivision01()
{
    std::vector<double> values1 = { 4, -2, 6, 5, -1, 2 };
    Polynom p1(values1);
    cout << "p1:    " << p1 << endl;

    std::vector<double> values2 = { 4, 2, 0, 1 };
    Polynom p2(values2);
    cout << "p2:    " << p2 << endl;

    Polynom p3 = p1 / p2;
    cout << "p1/p2: " << p3 << endl;
}

void TestingDivision02()
{
    std::vector<double> values1 = { 1, 0, 1, -1, 3 };
    Polynom p1(values1);
    cout << "p1:    " << p1 << endl;

    std::vector<double> values2 = { -1, 1 };
    Polynom p2(values2);
    cout << "p2:    " << p2 << endl;

    Polynom p3 = p1 / p2;
    cout << "p1/p2: " << p3 << endl;
}

void TestingModulo()
{
    std::vector<double> values1 = { 0, -4, 8, 10, 3 };
    Polynom p1(values1);
    cout << "p1:    " << p1 << endl;

    std::vector<double> values2 = { 0, 4, 3 };
    Polynom p2(values2);
    cout << "p2:    " << p2 << endl;

    Polynom p3 = p1 % p2;
    cout << "p1%p2: " << p3 << endl;
}

void TestingDivision_ArndtBruenner()
{
    //1.)  (x4 + 3x3 + x2 - 2x) : (x + 2)
    //1.)  x3 + x2 - x 

    std::vector<double> values11 = { 0, -2, 1, 3, 1 };
    Polynom p11(values11);
    cout << "p1:    " << p11 << endl;

    std::vector<double> values12 = { 2, 1 };
    Polynom p12(values12);
    cout << "p2:    " << p12 << endl;

    Polynom p13 = p11 / p12;
    cout << "p1/p2: " << p13 << endl << endl;

    //2.)    (2x5 - x4 + 5x3 + 6x2 - 2x + 4) : (x3 + 2x + 4)
    //2.)    2x2 - x + 1 
    std::vector<double> values21 = { 4, -2, 6, 5, -1, 2 };
    Polynom p21(values21);
    cout << "p1:    " << p21 << endl;

    std::vector<double> values22 = { 4, 2, 0, 1 };
    Polynom p22(values22);
    cout << "p2:    " << p22 << endl;

    Polynom p23 = p21 / p22;
    cout << "p1/p2: " << p23 << endl << endl;


    //3.)    (-8x5 + 4x3 + x2) : (-4x3 + 2x2 + x)
    //3.)    2x2 + x 
    std::vector<double> values31 = { 0, 0, 1, 4, 0, -8 };
    Polynom p31(values31);
    cout << "p1:    " << p31 << endl;

    std::vector<double> values32 = { 0, 1, 2, -4 };
    Polynom p32(values32);
    cout << "p2:    " << p32 << endl;

    Polynom p33 = p31 / p32;
    cout << "p1/p2: " << p33 << endl << endl;


    //4.)    (8x4 + 8x2 - 1) : (4x2 + 2)
    //4.)    2x2 + 1     Rest  -3 

    std::vector<double> values41 = { -1, 0, 8, 0, 8 };
    Polynom p41(values41);
    cout << "p1:    " << p41 << endl;

    std::vector<double> values42 = { 2, 0, 4 };
    Polynom p42(values42);
    cout << "p2:    " << p42 << endl;

    Polynom p43 = p41 / p42;
    Polynom p43mod = p41 % p42;
    cout << "p1/p2: " << p43 << endl;
    cout << "p1%p2: " << p43mod << endl << endl;

    //5.)    (-3x5 - x4 + 4x3 + 3/2x + 2) : (3x + 4)
    //5.)    -x4 + x3 + 1/2  

    std::vector<double> values51 = { 2, 1.5, 0, 4, -1, -3 };
    Polynom p51(values51);
    cout << "p1:    " << p51 << endl;

    std::vector<double> values52 = { 4, 3 };
    Polynom p52(values52);
    cout << "p2:    " << p52 << endl;

    Polynom p53 = p51 / p52;
    cout << "p1/p2: " << p53 << endl << endl;

    //6.)    (3x4 + 10x3 + 8x2 - 4x) : (3x2 + 4x)
    //6.)    x2 + 2x     Rest  -4x 

    std::vector<double> values61 = { 0, -4, 8, 10, 3 };
    Polynom p61(values61);
    cout << "p1:    " << p61 << endl;

    std::vector<double> values62 = { 0, 4, 3 };
    Polynom p62(values62);
    cout << "p2:    " << p62 << endl;

    Polynom p63 = p61 / p62;
    Polynom p63mod = p61 % p62;
    cout << "p1/p2: " << p63 << endl;
    cout << "p1%p2: " << p63mod << endl << endl;

    //7.)    (2x5 - 5x4 + 2x + 1) : (-x2 + 2x + 1)
    //7.)    -2x3 + x2 + 1 

    std::vector<double> values71 = { 1, 2, 0, 0, -5, 2 };
    Polynom p71(values71);
    cout << "p1:    " << p71 << endl;

    std::vector<double> values72 = { 1, 2, -1 };
    Polynom p72(values72);
    cout << "p2:    " << p72 << endl;

    Polynom p73 = p71 / p72;
    cout << "p1/p2: " << p73 << endl << endl;

    //8.)    (15/4x3 + 9x2 - x - 8) : (15/4x2 + 3/2x - 4)
    //8.)    x + 2 

    std::vector<double> values81 = { -8, -1, 9, 15.0 / 4.0 };
    Polynom p81(values81);
    cout << "p1:    " << p81 << endl;

    std::vector<double> values82 = { -4, 3.0 / 2.0, 15.0 / 4.0 };
    Polynom p82(values82);
    cout << "p2:    " << p82 << endl;

    Polynom p83 = p81 / p82;
    cout << "p1/p2: " << p83 << endl << endl;

    //9.)    (x4 - 7x2 - 10/3x + 4/3) : (x + 2)
    //9.)    x3 - 2x2 - 3x + 8/3     Rest  -4 

    std::vector<double> values91 = { 4.0 / 3.0, -10 / 3.0, -7, 0, 1 };
    Polynom p91(values91);
    cout << "p1:    " << p91 << endl;

    std::vector<double> values92 = { 2, 1 };
    Polynom p92(values92);
    cout << "p2:    " << p92 << endl;

    Polynom p93 = p91 / p92;
    Polynom p93mod = p91 % p92;
    cout << "p1/p2: " << p93 << endl;
    cout << "p1%p2: " << p93mod << endl << endl;


    //10.)   (4x3 + 3x2 - 8x + 4) : (4x2 - 5x + 2)
    //10.)    x + 2 

    std::vector<double> values101 = { 4, -8, 3, 4 };
    Polynom p101(values101);
    cout << "p1:    " << p101 << endl;

    std::vector<double> values102 = { 2, -5, 4 };
    Polynom p102(values102);
    cout << "p2:    " << p102 << endl;

    Polynom p103 = p101 / p102;
    cout << "p1/p2: " << p103 << endl << endl;
}


void TestingDivision()
{
    // TestingDivision01();
   // TestingDivision02();
    TestingDivision_ArndtBruenner();
    // TestingModulo();
}