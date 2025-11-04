// =====================================================================================
// ProgramMatrix.cpp
// =====================================================================================

#include "Matrix.h"

#include <print>

void test_01() {

    Matrix<double> empty;
    empty.print();

    Matrix<double> matrix{ 3, 3 };
    matrix.print();

    //Matrix<double> matrix2{ 3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
    //matrix2.print();

    //Matrix<double> matrix3{ 2, 3, { 1, 2, 3, 4, 5, 6 } };
    //matrix3.print();
}


//void test_02() {
//
//    Matrix<double> matrix{ 3, 3 };
//    matrix.print();
//
//    Matrix<double> matrix2{ 3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
//    matrix2.print();
//
//    Matrix<double> matrix3{ 2, 3, { 1, 2, 3, 4, 5, 6 } };
//    matrix3.print();
//}
//
//void test_03() {
//
//    Matrix<double> matrix2{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };  // Diese Liste ist unvollständig ?????????????
//    matrix2.print();
//}
//
//void test_04() {
//
//    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
//    matrix.print();
//
//    auto value = matrix.at(0, 2);
//    std::println("Value: {}", value);
//
//    matrix.at(0, 2) = 33;
//    std::println("Value: {}", matrix.at(0, 2));
//
//    matrix.print();
//
//    const Matrix<double> constMatrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
//
//    value = constMatrix.at(0, 2);
//    std::println("Value: {}", value);
//
//    constMatrix.print();
//}
//
//void test_05() {
//
//    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
//    Matrix<double> copy{ matrix };
//
//    matrix.print();
//    copy.print();
//}
//
//void test_06() {
//
//    Matrix<double> matrix{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 } } };
//    matrix.print();
//
//    Matrix<double> t = matrix.transpose();
//    t.print();
//}
//
//void test_07() {
//
//    Matrix<double> matrix1{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } } };
//    matrix1.print();
//
//    Matrix<double> matrix2{ 3, 3, { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } } };
//    matrix2.print();
//
//    Matrix<double> sum = matrix1.add(matrix2);
//    sum.print();
//}
//
//void test_08() {
//
//    Matrix<double> matrix1{ 3, 3, { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } } };
//    matrix1.print();
//
//    Matrix<double> matrix2{ 3, 3, { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } } };
//    matrix2.print();
//
//    Matrix<double> sum = matrix1.sub(matrix2);
//    sum.print();
//}
//
//void test_09() {
//
//    Matrix<double> matrix1{ 2, 3, { { 1, 2, 3 }, { 4, 5, 6 }} };
//    //matrix1.print();
//
//    Matrix<double> matrix2{ 3, 2, { { 1, 4 }, { 2, 5 }, { 3, 6 } } };
//    // matrix2.print();
//
//    Matrix<double> product = matrix1.mul(matrix2);
//    product.print();
//}

// =====================================================================================
// End-of-File
// =====================================================================================
