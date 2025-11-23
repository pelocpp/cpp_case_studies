// =====================================================================================
// ProgramMatrixInverter.cpp
// =====================================================================================

#include "MatrixInverter.h"

#include <print>

static void test_invertable_matrix_01() {

    MatrixInverter<double> inverter;

    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 2.0, 1.0, 1.0 } , { 4.0, -6.0, 0.0 } , { -2.0, 7.0, 2.0 } });
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
