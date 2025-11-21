// =====================================================================================
// ProgramDeterminant.cpp
// =====================================================================================

#include "Matrix.h"
#include "Determinant.h"

#include <print>

static void test_minor_01() {

    Matrix<double> matrix{ 2, 2 };
    matrix.elements({ { 1.0, 2.0  }, { 3.0, 4.0 } });
    matrix.print();
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = minor(matrix, row, col);
            min.print();
            std::println();
        }
    }
}

static void test_minor_02() {

    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    matrix.print();
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = minor(matrix, row, col);
            min.print();
            std::println();
        }
    }
}

static void test_minor_03() {

    Matrix<double> matrix{ 4, 4 };
    matrix.elements({ { 1.0, 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0, 8.0 }, { 9.0, 10.0, 11.0, 12.0 }, { 13.0, 14.0, 15.0, 16.0 } });
    matrix.print();
    std::println();

    for (std::size_t row{}; row != matrix.rows(); ++row) {

        for (std::size_t col{}; col != matrix.cols(); ++col) {

            std::println("Minor ==> row={}, col={}", row, col);

            Matrix<double> min = minor(matrix, row, col);
            min.print();
            std::println();
        }
    }
}



static void test_determinant_01() {

    Matrix<double> matrix{ 1, 1 };
    matrix.elements({ 1.0 });
    matrix.print();
    std::println();

    double det{ determinant<double>(matrix) };
    std::println("Determinant: {}", det);


    Matrix<double> matrix1{ 2, 2 };
    matrix1.elements({ { 1.0, 2.0 }, { 3.0, 4.0 } });
    matrix1.print();
    std::println();

    det = determinant<double>(matrix1);
    std::println("Determinant: {}", det);
}


void test_determinant()
{
    //test_minor_01();
    //test_minor_02();
    test_minor_03();

  //  test_determinant_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
