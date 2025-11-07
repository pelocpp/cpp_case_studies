// =====================================================================================
// ProgramMatrix.cpp
// =====================================================================================

#include "Matrix.h"

#include <print>

static void test_matrix_01() {

    Matrix<double> empty;
    empty.print();

    Matrix<double> matrix1{ 3, 3 };
    matrix1.print();

    Matrix<double> matrix2{ 3, 3, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 } };
    matrix2.print();

    Matrix<double> matrix3{ 2, 3, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 } };
    matrix3.print();

    Matrix<double> matrix4{ 3, 3, { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } } };
    matrix4.print();



    Matrix<float> matrix10{ 3, 3 };
    matrix10.print();

    Matrix<float> matrix11{ 3, 3, { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f } };
    matrix11.print();

    Matrix<float> matrix12{ 2, 3, { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f } };
    matrix12.print();

    Matrix<float> matrix13{ 3, 3, { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } } };
    matrix13.print();




    Matrix<long double> matrix20{ 3, 3 };
    matrix20.print();

    Matrix<long double> matrix21{ 3, 3, { 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l, 7.0l, 8.0l, 9.0l } };
    matrix21.print();

    Matrix<long double> matrix22{ 2, 3, { 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l } };
    matrix22.print();

    Matrix<long double> matrix23{ 3, 3, { { 1.0l, 2.0l, 3.0l }, { 4.0l, 5.0l, 6.0l }, { 7.0l, 8.0l, 9.0l } } };
    matrix23.print();
}


static void test_matrix_02() {

    Matrix<double> matrix{ 3, 3 };
    matrix.print();

    Matrix<double> matrix2{ 3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
    matrix2.print();

    Matrix<double> matrix3{ 2, 3, { 1, 2, 3, 4, 5, 6 } };
    matrix3.print();
}

static void test_matrix_03() {

    Matrix<double> matrix2{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };  // Diese Liste ist unvollständig ?????????????
    matrix2.print();
}

static void test_matrix_04() {

    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
    matrix.print();

    auto value = matrix.at(0, 2);
    std::println("Value: {}", value);

    matrix.at(0, 2) = 33;
    std::println("Value: {}", matrix.at(0, 2));

    matrix.print();

    const Matrix<double> constMatrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };

    value = constMatrix.at(0, 2);
    std::println("Value: {}", value);

    constMatrix.print();
}

static void test_matrix_05() {

    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
    Matrix<double> copy{ matrix };

    matrix.print();
    copy.print();
}

static void test_matrix_06() {

    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
    matrix.print();

    Matrix<double> t = matrix.transpose();
    t.print();
}

static void test_matrix_07() {

    Matrix<double> matrix1{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } } };
    matrix1.print();

    Matrix<double> matrix2{ 3, 3, { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } } };
    matrix2.print();

    Matrix<double> sum = matrix1.add(matrix2);
    sum.print();
}

static void test_matrix_08() {

    Matrix<double> matrix1{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } } };
    matrix1.print();

    Matrix<double> matrix2{ 3, 3, { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } } };
    matrix2.print();

    Matrix<double> sum = matrix1.sub(matrix2);
    sum.print();
}

static void test_matrix_09() {

    Matrix<double> matrix1{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 }} };
    matrix1.print();

    Matrix<double> matrix2{ 3, 2, { { 1, 4 }, { 2, 5 }, { 3, 6 } } };
    matrix2.print();

    Matrix<double> product = matrix1.mul(matrix2);
    product.print();
}

static void test_matrix_20()
{
    Matrix<double> matrix{ 3, 3, { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } } };
    matrix.print();

    Matrix copy = matrix;
    copy.print();

    Matrix anotherCopy = std::move(matrix);
    matrix.print();
    anotherCopy.print();

}

void test_matrix()
{
    test_matrix_01();
    test_matrix_02();
    test_matrix_03();
    test_matrix_04();
    test_matrix_05();
    test_matrix_06();
    test_matrix_07();
    test_matrix_08();
    test_matrix_09();
    test_matrix_20();
}

// =====================================================================================
// End-of-File
// =====================================================================================
