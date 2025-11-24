// =====================================================================================
// ProgramLUDecomposition.cpp
// =====================================================================================

#include "LU_Decomposition.h"

#include <print>

static void test_lu_decomposition_01()
{
    // aus ChatGPT - Ergebnis stimmmt
    Matrix<double> matrix{ 2, 2 };
    matrix.elements({ 2.0, 3.0, 4.0, 7.0 });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    lu.printMatrix();
    std::println();

    lu.printLowerTriangularMatrix();
    std::println();

    lu.printUpperTriangularMatrix();
    std::println();

    // verify result
    const Matrix<double> lower = lu.getLowerMatrix();
    const Matrix<double> upper = lu.getUpperMatrix();
    Matrix<double> prod = lower * upper;

    // Hmm, das habe ich nicht ???????????
    //if (matrix != prod) {
    //    std::println();
    //}

    prod.print();
    std::println();
}

static void test_lu_decomposition_02()
{
    // aus ChatGPT - Ergebnis stimmmt
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ 2.0, 1.0, 1.0, 4.0, -6.0, 0.0, -2.0, 7.0, 2.0 });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    lu.printMatrix();
    std::println();

    lu.printLowerTriangularMatrix();
    std::println();

    lu.printUpperTriangularMatrix();
    std::println();

    // verify result
    const Matrix<double> lower = lu.getLowerMatrix();
    const Matrix<double> upper = lu.getUpperMatrix();
    Matrix<double> prod = lower * upper;

    // Hmm, das habe ich nicht ???????????
    //if (matrix != prod) {
    //    std::println();
    //}

    prod.print();
    std::println();
}

static void test_lu_decomposition_03()
{
    // aus ChatGPT - Ergebnis stimmmt
    Matrix<double> matrix{ 4, 4 };

    matrix.elements(
    {
        {  3,  1, -5,  4 },
        {  2, -3,  3, -2 },
        {  5, -3,  4,  1 },
        { -2,  4, -3, -5 } 
    });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    lu.printMatrix();
    std::println();

    lu.printLowerTriangularMatrix();
    std::println();

    lu.printUpperTriangularMatrix();
    std::println();

    // verify result
    const Matrix<double> lower = lu.getLowerMatrix();
    const Matrix<double> upper = lu.getUpperMatrix();
    Matrix<double> prod = lower * upper;

    // Hmm, das habe ich nicht ???????????
    //if (matrix != prod) {
    //    std::println();
    //}

    prod.print();
    std::println();
}


static void test_lu_decomposition_10()
{
    // aus ChatGPT - dieses Beispiel verwende ich bei der Invertierung von Matrizen
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 2.0, 1.0, 1.0 } , { 4.0, -6.0, 0.0 } , { -2.0, 7.0, 2.0 } });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    lu.printMatrix();
    std::println();

    lu.printLowerTriangularMatrix();
    std::println();

    lu.printUpperTriangularMatrix();
    std::println();

    // verify result
    const Matrix<double> lower = lu.getLowerMatrix();
    const Matrix<double> upper = lu.getUpperMatrix();
    Matrix<double> prod = lower * upper;
    prod.print();
    std::println();
}

static void test_lu_decomposition_11()
{
    // aus ChatGPT - dieses Beispiel verwende ich bei der Lösung eines linearen Gleichungssystems
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 2.0, 3.0, 1.0 } , { 4.0, 7.0, -1.0 } , { -2.0, 4.0, 5.0 } });
    matrix.print();
    std::println();

    LU_Decomposition<double> lu{ matrix };

    lu.decompose();

    //lu.printMatrix();
    //std::println();

    lu.printLowerTriangularMatrix();
    std::println();

    lu.printUpperTriangularMatrix();
    std::println();

    //// verify result
    //const Matrix<double> lower = lu.getLowerMatrix();
    //const Matrix<double> upper = lu.getUpperMatrix();
    //Matrix<double> prod = lower * upper;
    //prod.print();
    //std::println();
}


void test_lu_decomposition()
{
    //test_lu_decomposition_01();
   // test_lu_decomposition_02();
    //test_lu_decomposition_03();

    // test_lu_decomposition_10();
    test_lu_decomposition_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================
