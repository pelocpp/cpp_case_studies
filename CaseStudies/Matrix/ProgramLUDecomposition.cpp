// =====================================================================================
// ProgramLUDecomposition.cpp
// =====================================================================================

#include "LU_Decomposition.h"

#include <print>

static void test_lu_decomposition_01() {

    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    lu.printMatrix();
    std::println();
    
    lu.printUpperTriangularMatrix();
    std::println();

    lu.printLowerTriangularMatrix();
    std::println();
}

void test_lu_decomposition()
{
    test_lu_decomposition_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
