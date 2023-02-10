// =====================================================================================
// Examples01.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

#include "Permutation.h"

// testing permutations
void Test_Permutation_01()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation<char> p{ 'A', 'B', 'C' };
    std::cout << p << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront('Z');
    std::cout << p << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (size_t i{}; i != p.grade(); ++i)
    {
        char ch = p[i];
        std::cout << i << ": " << ch << std::endl;
    }

    std::cout << "Testing removeAt: " << std::endl;
    do
    {
        p = p.removeAt(0);
        std::cout << p << std::endl;
    }
    while (p.grade() != 0);
}

void Test_Permutation_02()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation p{ 1, 2, 3, 4, 5 };
    std::cout << p << " (Anzahl der Elemente: " << p.grade() << ')' << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront(0);
    std::cout << p << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (size_t i{}; i != p.grade(); ++i)
    {
        int n = p[i];
        std::cout << i << ": " << n << std::endl;
    }

    std::cout << "Testing removeAt: " << std::endl;
    while (true) {
        p = p.removeAt(0);
        std::cout << p << std::endl;
        if (p.grade() == 0) {
            break;
        }
    }
}

void Test_Permutation_03()
{
    std::cout << "Testing Range-Based Loop: " << std::endl;
    Permutation<int> p{ 1, 2, 3, 4, 5 };
    std::cout << p << std::endl;

    for (int element : p) {
        std::cout << element << std::endl;
    }
}

void Test_Permutation_04()
{
    Permutation<int> p{ 1, 2, 3, 4 };
    for (int n : p) {
        std::cout << "Next Element: " << n << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
