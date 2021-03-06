// =====================================================================================
// Examples02.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "PermutationEx.h"
#include "PermutationArrayEx.h"
#include "PermutationCalculatorEx.h"

void Test01_Permutation_Ex_01();
void Test02_PermutationArray_Ex();
void Test03_PermutationCalculator_Ex_01();
void Test03_PermutationCalculator_Ex_02();
void Test04_PermutationEnumeration_Ex();

void Test01_Permutation_Ex_01()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationEx<char> p1{ 'A', 'B', 'C' };
    std::cout << p1 << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p1.insertAtFront('Z');
    std::cout << p1 << std::endl;

    PermutationEx<char> p2{ '1', '2', '3', '4', '5' };
    std::cout << p2 << " [Number of Elements: " << p2.grade() << ']' << std::endl;

    PermutationEx<int> p3{ 1, 2, 3, 4, 5 };
    std::cout << p3 << " [Number of Elements: " << p3.grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p3.grade(); i++)
    {
        int n = p3[i];
        std::cout << i << ": " << n << std::endl;
    }

    PermutationEx<int> p4 = p3;
    std::cout << "Testing removeAt: " << p4 << std::endl;
    for (int i = 0; i < p4.grade(); i++)
    {
        p3 = p3.removeAt(0);
        std::cout << i << ": " << p3 << std::endl;
    }
}

void Test01_Permutation_Ex_02()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationEx<short> p{ 1, 2, 3, 4 };
    std::cout << p << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront(5);
    std::cout << p << std::endl;
    std::cout << p << " [Number of Elements: " << p.grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p.grade(); i++)
    {
        int n = p[i];
        std::cout << i << ": " << n << std::endl;
    }

    std::cout << "Testing removeAt: " << p << std::endl;
    for (int count = p.grade(), i = 0; i < count; i++)
    {
        p = p.removeAt(0);
        std::cout << i << ": " << p << std::endl;
    }
}

void Test02_PermutationArray_Ex()
{
    PermutationEx<int> p({ 1, 2, 3, 4 });
    std::cout << p << std::endl;
    PermutationEx<int> q({ 4, 3, 2, 1 });
    std::cout << q << std::endl << std::endl;

    PermutationArrayEx<int> array(2);
    array.insert(p);
    array.insert(q);
    std::cout << array << std::endl;
}

void Test03_PermutationCalculator_Ex_01()
{
    PermutationEx<char> p{ 'A', 'B', 'C' };
    PermutationCalculatorEx<char> calc;
    PermutationArrayEx<char> result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test03_PermutationCalculator_Ex_02()
{
    PermutationEx<int> p({ 1, 2, 3, 4 });
    PermutationCalculatorEx<int> calc;
    PermutationArrayEx<int> result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test03_PermutationCalculator_Ex_03()
{
    PermutationEx<char> p{ 'X', 'Y', 'Z' };
    PermutationCalculatorEx<char> calc;
    PermutationArrayEx<char> result = calc.calculateEx(p);
    std::cout << result << std::endl;
}

void Test04_PermutationEnumeration_Ex()
{
    //Permutation p("ABCD");
    //PermutationCalculator calc;
    //calc.SetPermutation(p);
    //calc.Calculate();

    //calc.Reset();
    //while (calc.MoveNext())
    //{
    //    Permutation q = calc.Current();
    //    std::cout << "Next Permutation: " << q << std::endl;
    //}
}

// =====================================================================================
// End-of-File
// =====================================================================================
