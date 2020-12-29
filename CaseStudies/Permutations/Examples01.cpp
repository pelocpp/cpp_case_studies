// =====================================================================================
// Examples01.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void Test01_Permutation()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation p1{ "ABC" };
    std::cout << p1 << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p1.insertAtFront('Z');
    std::cout << p1 << std::endl;

    Permutation p2{ '1', '2', '3' , '4' , '5' };
    std::cout << p2 << " [Number of Elements: " << p2.grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        char c = p2[i];
        std::cout << i << ": " << c << std::endl;
    }

    Permutation p3 = p2;
    std::cout << "Testing removeAt: " << p3 << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        p3 = p3.removeAt(0);
        std::cout << i << ": " << p3 << std::endl;
    }
}

void Test02_PermutationArray()
{
    Permutation p{ "ABC" };
    Permutation q{ "CBA" };
    PermutationArray array(2);
    array.insert(p);
    array.insert(q);
    std::cout << array << std::endl;
}

void Test02_PermutationArray_02()
{
    PermutationArray array(4);
    array.emplace({ "ABC" });
    array.emplace({ "CBA" });
    std::cout << array << std::endl;
    array.emplace({ 'B', 'C', 'A' });
    array.emplace({ 'B', 'A', 'C' });
    std::cout << array << std::endl;
}

void Test03_PermutationCalculator()
{
    Permutation p("ABC");
    PermutationCalculator calc;
    PermutationArray result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test03_PermutationCalculator_02()
{
    Permutation p("ABC");
    PermutationCalculator calc;
    PermutationArray result = calc.calculateEx(p);
    std::cout << result << std::endl;
}

void Test04_PermutationEnumeration()
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
