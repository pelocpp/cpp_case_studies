// =====================================================================================
// Examples01.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

void Test01_Permutation_Script();
void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void Test01_Permutation_Script()
{
    Permutation p1("ABC");
    std::cout << p1 << std::endl;

    Permutation p2("12345");
    std::cout << p2 << " (Anzahl der Elemente: " << p2.grade() << ')' << std::endl;

    Permutation p3("ABC");
    for (int i = 0; i < p3.grade(); i++)
    {
        char ch = p3[i];
        std::cout << i << ": " << ch << std::endl;
    }

    Permutation p4("ABC");
    std::cout << p4 << " (Grad: " << p4.grade() << ')' << std::endl;
    p4.insertAtFront('D');
    std::cout << p4 << " (Grad: " << p4.grade() << ')' << std::endl;
}

void Test01_Permutation()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation p1("ABC");
    std::cout << p1 << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p1.insertAtFront('Z');
    std::cout << p1 << std::endl;

    Permutation p2("12345");
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
    Permutation p("ABC");
    std::cout << p << std::endl;
    Permutation q("CBA");
    std::cout << q << std::endl << std::endl;

    PermutationArray array(2);
    array.insert(p);
    array.insert(q);
    std::cout << array << std::endl;
}

void Test03_PermutationCalculator()
{
    Permutation p("ABCD");
    PermutationCalculator calc;
    PermutationArray result = calc.calculate(p);
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
