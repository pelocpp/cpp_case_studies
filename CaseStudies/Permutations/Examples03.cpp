// =====================================================================================
// Examples03.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>

#include "Permutation.h"
#include "PermutationContainer.h"
#include "PermutationCalculator.h"

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
    while (true) {
        p = p.removeAt(0);
        std::cout << p << std::endl;
        if (p.grade() == 0) {
            break;
        }
    }
}

void Test_Permutation_02()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation<int> p({ 1, 2, 3, 4 });
    std::cout << p << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront(0);
    std::cout << p << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (size_t i{}; i != p.grade(); ++i)
    {
        int ch = p[i];
        std::cout << i << ": " << ch << std::endl;
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
    Permutation<int> p({ 1, 2, 3, 4, 5 });
    std::cout << p << std::endl;

    for (int element : p) {
        std::cout << element << std::endl;
    }
}

void Test_PermutationContainer_01()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    Permutation<int> q({ 4, 3, 2, 1 });
    std::cout << p << std::endl;
    std::cout << q << std::endl << std::endl;

    PermutationContainer<int> container(2);
    container.insert(p);
    container.insert(q);
    std::cout << container << std::endl;
}

void Test_PermutationContainer_02()
{
    using namespace std::complex_literals;
    Permutation<std::complex<double>> p({ 1. + 2i, 3. + 4i, 5. + 6i });
    Permutation<std::complex<double>> q({ 1. - 2i, 3. - 4i, 5. - 6i });
    std::cout << p << std::endl;
    std::cout << q << std::endl << std::endl;

    PermutationContainer<std::complex<double>> container(2);
    container.insert(p);
    container.insert(q);

    for (const Permutation<std::complex<double>>& p : container) {
        std::cout << p << std::endl;
    }
}

void Test_PermutationCalculator_01()
{
    Permutation<char> p{ 'A', 'B', 'C' };
    PermutationCalculator<char> calc;
    PermutationContainer<char> result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_02()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    PermutationCalculator<int> calc;
    PermutationContainer<int> result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_03()
{
    using namespace std::complex_literals;
    Permutation<std::complex<double>> p({ 1. + 2i, 3. + 4i, 5. + 6i });
    PermutationCalculator<std::complex<double>> calc;
    PermutationContainer<std::complex<double>> result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_04()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    PermutationCalculator<int> calc;
    PermutationContainer<int> result = calc.calculate(p);

    for (const auto& perm : result) {
        std::cout << "Next Permutation: " << perm << std::endl;
    }
}

void Test_PermutationEnumeration_01()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    for (auto n : p) {
        std::cout << "Next Element: " << n << std::endl;
    }
}


// =====================================================================================
// End-of-File
// =====================================================================================
