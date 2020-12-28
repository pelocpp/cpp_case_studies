// =====================================================================================
// Examples02.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "PermutationEx.h"
#include "PermutationArrayEx.h"
#include "PermutationCalculatorEx.h"

void Test01_Permutation_Ex_01();
void Test02_PermutationArray_Ex();
void Test03_PermutationCalculator_Ex();
void Test04_PermutationEnumeration_Ex();

void Test01_Permutation_Ex_01()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationEx<char> p1("ABC");
    std::cout << p1 << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p1.insertAtFront('Z');
    std::cout << p1 << std::endl;

    PermutationEx<char> p2("12345");
    std::cout << p2 << " [Number of Elements: " << p2.grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        char c = p2[i];
        std::cout << i << ": " << c << std::endl;
    }

    PermutationEx<char> p3 = p2;
    std::cout << "Testing removeAt: " << p3 << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        p3 = p3.removeAt(0);
        std::cout << i << ": " << p3 << std::endl;
    }
}

void Test01_Permutation_Ex_02()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationEx<short> p({ 1, 2, 3, 4 });
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
    PermutationEx<char> p("ABC");
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
