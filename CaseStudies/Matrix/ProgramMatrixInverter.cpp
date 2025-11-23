// =====================================================================================
// ProgramMatrixInverter.cpp
// =====================================================================================

#include "MatrixInverter.h"

#include <print>

static void test_invertable_matrix_01() {

    MatrixInverter<double> inverter;

    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 2, 1, 1} , { 4, -6, 0 } , { -2, 7, 2 } });
    matrix.print();
    std::println();

    inverter.set(matrix);

    inverter.invert();
}

void test_invertable_matrix() {

    test_invertable_matrix_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
