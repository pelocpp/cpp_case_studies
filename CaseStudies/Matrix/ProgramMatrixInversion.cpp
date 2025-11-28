// =====================================================================================
// ProgramMatrixInversion.cpp
// =====================================================================================

#include "MatrixInversion.h"

#include <print>

static void test_invertable_matrix_01() {

    MatrixInversion<double> inverter;

    Matrix<double> matrix{ 3, 3 };

    matrix.elements
    ({
        { 2.0, 1.0, 1.0 },
        { 4.0, -6.0, 0.0 },
        { -2.0, 7.0, 2.0 }
    });
    
    std::println("{}", matrix);
    std::println();

    inverter.set(matrix);
    inverter.invert();
}

static void test_invertable_matrix_02() {

    // gefunden in
    // https://www.max-academy.de/contentPlayer/631a4c19593a5c00653096cc/5ecfa05611a83100658d0b25

    MatrixInversion<double> inverter;

    Matrix<double> matrix{ 4, 4 };

    matrix.elements
    ({
        { 1.0, 1.0, 3.0, 2.0 },
        { 2.0, 2.0, 0.0, -1.0 },
        { 4.0, 0.0, 3.0, 2.0 },
        { 0.0, 1.0, 2.0, 0.0 }
    });

    std::println("{}", matrix);
    std::println();

    inverter.set(matrix);
    inverter.invert();
}

void test_invertable_matrix() {

    // test_invertable_matrix_01();
    test_invertable_matrix_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
