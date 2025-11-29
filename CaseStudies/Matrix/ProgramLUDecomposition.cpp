// =====================================================================================
// ProgramLUDecomposition.cpp
// =====================================================================================

#include "LUDecomposition.h"

#include <print>

static void test_lu_decomposition_01()
{
    // aus ChatGPT - Ergebnis stimmmt
    Matrix<double> matrix{ 2, 2 };
    matrix.elements(
        { 2.0, 3.0, 4.0, 7.0 }
    );
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
}

static void test_lu_decomposition_02()
{
    // aus ChatGPT - Ergebnis stimmmt
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ 2.0, 1.0, 1.0, 4.0, -6.0, 0.0, -2.0, 7.0, 2.0 });
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
}

static void test_lu_decomposition_03()
{
    // aus ChatGPT - Ergebnis stimmmt // allerdings kleine Rundungsfehler
    Matrix<double> matrix{ 4, 4 };

    matrix.elements(
    {
        {  3,  1, -5,  4 },
        {  2, -3,  3, -2 },
        {  5, -3,  4,  1 },
        { -2,  4, -3, -5 } 
    });
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }
}


static void test_lu_decomposition_10()
{
    // aus ChatGPT - dieses Beispiel verwende ich bei der Invertierung von Matrizen
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ 
        { 2.0, 1.0, 1.0 } ,
        { 4.0, -6.0, 0.0 } ,
        { -2.0, 7.0, 2.0 } 
        });
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }
}

static void test_lu_decomposition_11()
{
    // aus ChatGPT - dieses Beispiel verwende ich bei der Lösung eines linearen Gleichungssystems
    Matrix<double> matrix{ 3, 3 };
    matrix.elements({ { 2.0, 3.0, 1.0 } , { 4.0, 7.0, -1.0 } , { -2.0, 4.0, 5.0 } });
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }
}

static void test_lu_decomposition_20()
{
    // aus Ronald Mak - mit Fehlerkorrektur
    // Ergebnis richtig // kleine Rundungsfehler
    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
    { 
        {  3.0,  1.0, -5.0,  4.0  },
        {  2.0, -3.0,  3.0, -2.0  },
        {  5.0, -3.0,  4.0,  1.0  },
        { -2.0,  4.0, -3.0, -5.0  }
    });
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_simple();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    // verify result
    const Matrix<double>& lower{ lu.getLowerMatrix() };
    const Matrix<double>& upper{ lu.getUpperMatrix() };
    Matrix<double> product{ lower * upper };

    std::println("{}", product);
    std::println();

    if (matrix == product) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }
}

static void test_lu_decomposition_30()
{
    // gefunden in
    // https://www.max-academy.de/contentPlayer/631a4c19593a5c00653096cc/5ecfa05611a83100658d0b25

    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
        {
            { 1.0,  1.0,  3.0,  2.0 },
            { 2.0,  2.0,  0.0, -1.0 },
            { 4.0,  0.0,  3.0,  2.0 },
            { 0.0,  1.0,  2.0,  0.0 }
        }
    );
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_pivot();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    std::println("Permutation Matrix");
    std::println("{}", lu.getPermMatrix());

    // verify result
    const Matrix<double>& lower = lu.getLowerMatrix();
    const Matrix<double>& upper = lu.getUpperMatrix();
    Matrix<double> lowerTimesUpper = lower * upper;

    const Matrix<double>& perm = lu.getPermMatrix();
    Matrix<double> permTimesMatrix = perm * matrix;

    if (lowerTimesUpper == permTimesMatrix) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }

    std::println("{}", lowerTimesUpper);
    std::println();
    std::println("{}", permTimesMatrix);
    std::println();
}

static void test_lu_decomposition_31()
{
    // aus ChatGPT

    Matrix<double> matrix{ 3, 3 };
    matrix.elements(
    {
        { 0.0,  2.0,  1.0 },
        { 1.0,  0.0,  3.0 },
        { 4.0,  5.0,  6.0 }
    }
    );
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_pivot();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    std::println("Permutation Matrix");
    std::println("{}", lu.getPermMatrix());

    // verify result
    const Matrix<double>& lower = lu.getLowerMatrix();
    const Matrix<double>& upper = lu.getUpperMatrix();
    Matrix<double> lowerTimesUpper = lower * upper;

    const Matrix<double>& perm = lu.getPermMatrix();
    Matrix<double> permTimesMatrix = perm * matrix;

    if (lowerTimesUpper == permTimesMatrix) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }

    std::println("{}", lowerTimesUpper);
    std::println();
    std::println("{}", permTimesMatrix);
    std::println();
}

static void test_lu_decomposition_32()
{
    // aus ChatGPT

    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
        {
            { 0.0,  2.0,  3.0, 1.0 },
            { 0.0,  0.0,  4.0, 2.0 },
            { 5.0,  1.0,  0.0, 0.0 },
            { 0.0,  6.0,  2.0, 8.0 }
        }
    );
    std::println("{}", matrix);
    std::println();

    LU_Decomposition<double> lu{ matrix };
    lu.decompose_pivot();

    std::println("Matrix");
    std::println("{}", lu.getMatrix());

    std::println("Lower Triangular Matrix");
    std::println("{}", lu.getLowerMatrix());

    std::println("Upper Triangular Matrix");
    std::println("{}", lu.getUpperMatrix());

    std::println("Permutation Matrix");
    std::println("{}", lu.getPermMatrix());

    // verify result
    const Matrix<double>& lower = lu.getLowerMatrix();
    const Matrix<double>& upper = lu.getUpperMatrix();
    Matrix<double> lowerTimesUpper = lower * upper;

    const Matrix<double>& perm = lu.getPermMatrix();
    Matrix<double> permTimesMatrix = perm * matrix;

    if (lowerTimesUpper == permTimesMatrix) {
        std::println("Result correct!");
    }
    else {
        std::println("Result NOT correct!");
    }

    std::println("{}", lowerTimesUpper);
    std::println();
    std::println("{}", permTimesMatrix);
    std::println();
}

void test_lu_decomposition()
{
    //test_lu_decomposition_01();
    //test_lu_decomposition_02();
    //test_lu_decomposition_03();
    //test_lu_decomposition_10();
    //test_lu_decomposition_11();
    //test_lu_decomposition_20();

    //test_lu_decomposition_30();
    //test_lu_decomposition_31();
    //test_lu_decomposition_32();
}

// =====================================================================================
// End-of-File
// =====================================================================================
