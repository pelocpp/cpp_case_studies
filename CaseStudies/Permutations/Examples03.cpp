// =====================================================================================
// Examples03.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

#include "Permutation.h"
#include "PermutationContainer.h"
#include "PermutationCalculator.h"

// testing permutations calculation
void Test_PermutationCalculator_01()
{
    Permutation<char> p{ 'A', 'B', 'C' };
    PermutationContainer<char> result = PermutationCalculator<char>::calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_02()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    PermutationContainer<int> result = PermutationCalculator<int>::calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_03()
{
    using namespace std::complex_literals;
    Permutation<std::complex<double>> p({ 1. + 2i, 3. + 4i, 5. + 6i });
    PermutationContainer<std::complex<double>> result = PermutationCalculator<std::complex<double>>::calculate(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_04()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    PermutationContainer<int> result = PermutationCalculator<int>::calculate(p);
    for (const auto& perm : result) {
        std::cout << "Next Permutation: " << perm << std::endl;
    }
}

void Test_PermutationCalculator_05()
{
    Permutation<char> p{ 'A', 'B', 'C' };
    PermutationContainer<char> result{};
    result = PermutationCalculator<char>::calculate(p);
    std::cout << result << std::endl;
    result = PermutationCalculator<char>::calculateEx(p);
    std::cout << result << std::endl;
}

void Test_PermutationCalculator_06()
{
    Permutation<int> p({ 1, 2, 3, 4 });
    PermutationContainer<int> result{};
    result = PermutationCalculator<int>::calculate(p);
    std::cout << result << std::endl;
    result = PermutationCalculator<int>::calculateEx(p);
    std::cout << result << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
