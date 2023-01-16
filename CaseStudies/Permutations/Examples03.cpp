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

// =====================================================================================
// End-of-File
// =====================================================================================
