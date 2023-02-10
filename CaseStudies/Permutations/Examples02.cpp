// =====================================================================================
// Examples02.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

#include "Permutation.h"
#include "PermutationContainer.h"

// testing permutations container
void Test_PermutationContainer_01()
{
    Permutation<int> p{ 1, 2, 3, 4 };
    Permutation<int> q{ 4, 3, 2, 1 };
    std::cout << p << std::endl;
    std::cout << q << std::endl;

    PermutationContainer<int> container{};
    container.insert(p);
    container.insert(q);
    std::cout << container << std::endl;
}

void Test_PermutationContainer_02()
{
    using namespace std::complex_literals;
    Permutation<std::complex<double>> p{ 1. + 2i, 3. + 4i, 5. + 6i };
    Permutation<std::complex<double>> q{ 1. - 2i, 3. - 4i, 5. - 6i };
    std::cout << p << std::endl;
    std::cout << q << std::endl << std::endl;

   // PermutationContainer<std::complex<double>> container(2);
    PermutationContainer<std::complex<double>> container{};
    container.insert(p);
    container.insert(q);

    for (const Permutation<std::complex<double>>& p : container) {
        std::cout << p << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
