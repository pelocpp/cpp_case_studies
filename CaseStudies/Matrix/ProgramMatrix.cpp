// =====================================================================================
// ProgramMatrix.cpp
// =====================================================================================

#include "Matrix.h"

#include <print>

static void test_matrix_01() {

    Matrix<double> empty;
    std::println("{}", empty);
    std::println();

    Matrix<double> matrix1{ 3, 3 };
    std::println("{}", matrix1);
    std::println();

    Matrix<double> matrix2{ 3, 3  };
    matrix2.elements({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 });
    std::println("{}", matrix2);
    std::println();

    Matrix<double> matrix3{ 2, 3 };
    matrix3.elements({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 });
    std::println("{}", matrix3);
    std::println();

    Matrix<double> matrix4{ 3, 3 };
    matrix4.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    std::println("{}", matrix4);
    std::println();



    Matrix<float> matrix10{ 3, 3 };
    std::println("{}", matrix10);
    std::println();

    Matrix<float> matrix11{ 3, 3 };
    matrix11.elements({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });
    std::println("{}", matrix11);
    std::println();

    Matrix<float> matrix12{ 2, 3 };
    matrix12.elements({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });
    std::println("{}", matrix12);
    std::println();

    Matrix<float> matrix13{ 3, 3 };
    matrix13.elements({ { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } });
    std::println("{}", matrix13);
    std::println();




    Matrix<long double> matrix20{ 3, 3 };
    std::println("{}", matrix20);
    std::println();

    Matrix<long double> matrix21{ 3, 3 };
    matrix21.elements({ 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l, 7.0l, 8.0l, 9.0l });
    std::println("{}", matrix21);
    std::println();

    Matrix<long double> matrix22{ 2, 3 };
    matrix22.elements({ 1.0l, 2.0l, 3.0l, 4.0l, 5.0l, 6.0l });
    std::println("{}", matrix22);
    std::println();

    Matrix<long double> matrix23{ 3, 3 };
    matrix23.elements({ { 1.0l, 2.0l, 3.0l }, { 4.0l, 5.0l, 6.0l }, { 7.0l, 8.0l, 9.0l } });
    std::println("{}", matrix23);
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

    std::println("{}", matrix);
    std::println();
}

static void test_matrix_03() {

    Matrix<double> matrix{ 2, 3 };
    matrix.elements({ { 1, 2, 3 }, { 4, 5, 6 } });
    std::println("{}", matrix);
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
    std::println("{}", matrix);
    std::println();

    Matrix<double> t = matrix.transpose();
    std::println("{}", t);
    std::println();
}

static void test_matrix_05() {

    Matrix<double> matrix1{ 3, 3,  };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    std::println("{}", matrix1);
    std::println();

    Matrix<double> matrix2{ 3, 3,};
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    std::println("{}", matrix2);
    std::println();

    Matrix<double> sum = matrix1.add(matrix2);
    std::println("{}", sum);
    std::println();

    sum = matrix1 + matrix2;
    std::println("{}", sum);
    std::println();
}

static void test_matrix_06() {

    Matrix<double> matrix1{ 3, 3 };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    std::println("{}", matrix1);
    std::println();

    Matrix<double> matrix2{ 3, 3 };
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    std::println("{}", matrix2);
    std::println();

    Matrix<double> diff = matrix1.sub(matrix2);
    std::println("{}", diff);
    std::println();

    diff = matrix1 - matrix2;
    std::println("{}", diff);
    std::println();
}

static void test_matrix_07() {

    Matrix<double> matrix1{ 3, 3 };
    matrix1.elements({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    std::println("{}", matrix1);
    std::println();

    Matrix<double> matrix2{ 3, 3 };
    matrix2.elements({ { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } });
    std::println("{}", matrix2);
    std::println();

    Matrix<double> product = matrix1.mul(matrix2);
    std::println("{}", product);
    std::println();

    product = matrix1 * matrix2;
    std::println("{}", product);
    std::println();
}

static void test_matrix_08() {

    Matrix<double> matrix{ 5, 5 };
    matrix.unit();
    std::println("{}", matrix);
    std::println();
}

static void test_matrix_10() {

    // testing vector & matrix operations together
    Vector<double> vector{ 1.0, 2.0 };
    std::println("{}", vector);
    std::println();

    Matrix<double> matrix{ 2, 2 };
    matrix.elements({ { 3.0, 4.0 }, { 5.0, 6.0 } });
    std::println("{}", matrix);
    std::println();

    Vector<double> result { matrix.mul(vector) };
    std::println("{}", result);
    std::println();

    result = matrix * vector;
    std::println("{}", result);
    std::println();

    // testing non-rectangular matrix
    Vector<double> vector2{  1.0, 2.0, 3.0, 4.0 };
    std::println("{}", vector2);
    std::println();

    Matrix<double> matrix2{ 2, 4 };
    matrix2.elements({ { 1.0, 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0, 8.0 } });
    std::println("{}", matrix2);
    std::println();

    Vector<double> result2{ matrix2.mul(vector2) };
    std::println("{}", result2);
    std::println();

    result2 = matrix2 * vector2;
    std::println("{}", result2);
    std::println();

    // testing another non-rectangular matrix
    Vector<double> vector3{ 10.0, 11.0 };
    std::println("{}", vector3);
    std::println();

    Matrix<double> matrix3{ 4, 2 };
    matrix3.elements({ { 1.0, 2.0 }, { 3.0, 4.0 }, { 5.0, 6.0 }, { 7.0, 8.0 } });
    std::println("{}", matrix3);
    std::println();

    Vector<double> result3{ matrix3.mul(vector3) };
    std::println("{}", vector3);
    std::println();

    result3 = matrix3 * vector3;
    std::println("{}", vector3);
    std::println();
}

static void test_matrix_20()
{
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    std::println("{}", matrix);
    std::println();

    Matrix copy = matrix;
    std::println("{}", copy);
    std::println();

    Matrix anotherCopy = std::move(matrix);
    std::println("{}", matrix);
    std::println();
    std::println("{}", anotherCopy);
    std::println();
}

static void test_matrix_30()
{
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } });
    std::println("{}", matrix);
}

void test_matrix()
{
    //test_matrix_01();
    //test_matrix_02();
    //test_matrix_03();
    //test_matrix_04();
    //test_matrix_05();
    //test_matrix_06();
    //test_matrix_07();
    test_matrix_08();

    //test_matrix_10();

    //test_matrix_20();
    //test_matrix_30();
}

// =====================================================================================
// End-of-File
// =====================================================================================
