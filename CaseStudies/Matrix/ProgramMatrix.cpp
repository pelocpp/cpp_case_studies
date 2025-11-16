// =====================================================================================
// ProgramMatrix.cpp
// =====================================================================================

#include "Matrix.h"

#include <print>

static void test_matrix_01() {

    Matrix<double> empty;
    empty.print();
    std::println();

    Matrix<double> matrix1{ 3, 3 };
    matrix1.print();
    std::println();

    Matrix<double> matrix2{ 3, 3  };
    matrix2.elements({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 });
    matrix2.print();
    std::println();

    Matrix<double> matrix3{ 2, 3 };
    matrix3.elements({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 });
    matrix3.print();
    std::println();

    Matrix<double> matrix4{ 3, 3 };
    matrix4.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    matrix4.print();
    std::println();



    Matrix<float> matrix10{ 3, 3 };
    matrix10.print();
    std::println();

    Matrix<float> matrix11{ 3, 3 };
    matrix11.elements({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
    matrix11.print();
    std::println();

    Matrix<float> matrix12{ 2, 3 };
    matrix12.elements({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });
    matrix12.print();
    std::println();

    Matrix<float> matrix13{ 3, 3 };
    matrix13.elements({ { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } });
    matrix13.print();
    std::println();




    Matrix<long double> matrix20{ 3, 3 };
    matrix20.print();
    std::println();

    Matrix<long double> matrix21{ 3, 3 };
    matrix21.elements({ 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l, 7.0l, 8.0l, 9.0l });
    matrix21.print();
    std::println();

    Matrix<long double> matrix22{ 2, 3 };
    matrix22.elements({ 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l });
    matrix22.print();
    std::println();

    Matrix<long double> matrix23{ 3, 3 };
    matrix23.elements({ { 1.0l, 2.0l, 3.0l }, { 4.0l, 5.0l, 6.0l }, { 7.0l, 8.0l, 9.0l } });
    matrix23.print();
    std::println();
}

static void test_matrix_02() {

    Matrix<double> matrix{ 3, 3 };

    try
    {
        matrix.elements({ { 1, 2, 3 }, { 4, 5, 6 } });    // uncomplete list of elements
    }
    catch (std::invalid_argument const& ex)
    {
        std::println("{}", ex.what());
    }
    catch (std::exception const& ex)
    {
        std::println("{}", ex.what());
    }

    matrix.print();  
    std::println();
}

static void test_matrix_03() {

    Matrix<double> matrix{ 2, 3 };
    matrix.elements({ { 1, 2, 3 }, { 4, 5, 6 } });
    matrix.print();
    std::println();

    auto value = matrix.at(0, 2);
    std::println("Value: {}", value);

    matrix.at(0, 2) = 123.0;
    std::println("Value: {}", matrix.at(0, 2));

    value = matrix(1, 2);
    std::println("Value: {}", value);

    matrix(1, 2) = 456.0;
    std::println("Value: {}", matrix(1, 2));
}

static void test_matrix_04() {

    Matrix<double> matrix{ 2, 3 };
    matrix.elements({ { 1, 2, 3 }, { 4, 5, 6 } });
    matrix.print();
    std::println();

    Matrix<double> t = matrix.transpose();
    t.print();
    std::println();
}

static void test_matrix_05() {

    Matrix<double> matrix1{ 3, 3,  };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    matrix1.print();
    std::println();

    Matrix<double> matrix2{ 3, 3,};
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    matrix2.print();
    std::println();

    Matrix<double> sum = matrix1.add(matrix2);
    sum.print();
    std::println();

    sum = matrix1 + matrix2;
    sum.print();
    std::println();
}

static void test_matrix_06() {

    Matrix<double> matrix1{ 3, 3 };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    matrix1.print();
    std::println();

    Matrix<double> matrix2{ 3, 3 };
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    matrix2.print();
    std::println();

    Matrix<double> diff = matrix1.sub(matrix2);
    diff.print();
    std::println();

    diff = matrix1 - matrix2;
    diff.print();
    std::println();
}

static void test_matrix_07() {

    Matrix<double> matrix1{ 3, 3 };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    matrix1.print();
    std::println();

    Matrix<double> matrix2{ 3, 3 };
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    matrix2.print();
    std::println();

    Matrix<double> product = matrix1.mul(matrix2);
    product.print();
    std::println();

    product = matrix1 * matrix2;
    product.print();
    std::println();
}

static void test_matrix_20()
{
    Matrix<double> matrix{ 3, 3,  };
    matrix.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    matrix.print();
    std::println();

    Matrix copy = matrix;
    copy.print();
    std::println();

    Matrix anotherCopy = std::move(matrix);
    matrix.print();
    std::println();
    anotherCopy.print();
    std::println();
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

    test_matrix_20();
}

// =====================================================================================
// End-of-File
// =====================================================================================
