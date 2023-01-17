// =====================================================================================
// Examples04.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

#include "Permutation.h"
#include "PermutationContainer.h"

// testing user defined literal operator
void Test_UDL_01()
{
    Permutation<int> p { 12345_perm };
    std::cout << p << std::endl;
}

void Test_UDL_02()
{
    PermutationContainer<int> container { 
        123_perm, 132_perm, 213_perm, 231_perm, 312_perm,321_perm
    };

    for (const auto& perm : container) {
        std::cout << "Permutation: " << perm << std::endl;
    }
}


// =====================================================================================
// End-of-File
// =====================================================================================
