// =====================================================================================
// ProgramMatrixDeterminant.cpp
// =====================================================================================

#include "Matrix.h"
#include "MatrixDeterminant.h"

#include <print>

static void test_minor_01() {

    Matrix<double> matrix{ 2, 2 };
    matrix.elements({ { 1.0, 2.0  }, { 3.0, 4.0 } });
    std::println("{}", matrix);
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = MatrixDeterminant<double>::minor(matrix, row, col);
            std::println("{}", min);
            std::println();
        }
    }
}

static void test_minor_02() {

    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    std::println("{}", matrix);
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = MatrixDeterminant<double>::minor(matrix, row, col);
            std::println("{}", min);
            std::println();
        }
    }
}

static void test_minor_03() {

    Matrix<double> matrix{ 4, 4 };
    matrix.elements({ { 1.0, 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0, 8.0 }, { 9.0, 10.0, 11.0, 12.0 }, { 13.0, 14.0, 15.0, 16.0 } });
    std::println("{}", matrix);
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = MatrixDeterminant<double>::minor(matrix, row, col);
            std::println("{}", min);
            std::println();
        }
    }
}



static void test_determinant_01() {

    Matrix<double> matrix{ 1, 1 };
    matrix.elements({ 1.0 });
    std::println("{}", matrix);
    std::println();

    MatrixDeterminant<double> md{ matrix };
    double det{ md.determinant() };
    std::println("Determinant: {}", det);


    Matrix<double> matrix1{ 2, 2 };
    matrix1.elements({ { 1.0, 2.0 }, { 3.0, 4.0 } });
    std::println("{}", matrix1);
    std::println();

    MatrixDeterminant<double> md1{ matrix1 };
    det = md1.determinant();
    std::println("Determinant: {}", det);
}


void test_determinant()
{
    test_minor_01();
    test_minor_02();
    test_minor_03();

    test_determinant_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
