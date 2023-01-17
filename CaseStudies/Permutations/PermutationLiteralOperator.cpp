// =====================================================================================
// PermutationLiteralOperator.cpp
// =====================================================================================

#include <iostream>
#include <string>

#include "Permutation.h"

// literal operator
Permutation<int> operator"" _perm(unsigned long long int value) {

    Permutation<int> p;

    while (value != 0) {

        int rest{ value % 10 };
        p.insertAtFront(rest);
        value = value / 10;
    }

    return p;
}
 
// =====================================================================================
// End-of-File
// =====================================================================================

