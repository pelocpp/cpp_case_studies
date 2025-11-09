// =====================================================================================
// ProgramLinearEquationSolver.cpp
// =====================================================================================

// 2 Beispiele:
//
//https://www.youtube.com/watch?v=vaahX3Wdxu8
//
//https://www.youtube.com/watch?v=9Ule9qQaBB0

#include "Vector.h"
#include "LinearEquationSolver.h"

#include <print>

static void test_linear_equation_01() {

    LinearEquationSolver<double> solver;

    solver.equation(
        1,
        {
            { 2,  4 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_02() {

    LinearEquationSolver<double> solver;

    solver.equation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_03() {

    // Beispiel aus .pdf

    LinearEquationSolver<double> solver;

    solver.equation(
        4,
        {
            { 1, 0, 1, 0, 4 },
            { 1, 1, 0, 1, 7 },
            { 1, 1, 2, 0, 6 },
            { 1, 0, 0, 1, 5 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_04() {

    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolver<double> solver;

    solver.equation(
        3,
        {
            { 1, -1,  2, 0 },
            { -2, 1, -6, 0 },
            { 1,  0, -2, 3 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_05() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.equation(
        10,
        {
            { 1,  -2,   5,   2, -1,  1,  4, -3,  1,  5,  84 },
            { 5,   2,  -1,  -2,  2,  2, -3,  0, -1, -4, -50 },
            { 2,   0,  -4,  -1, -5,  4,  0,  3, -5,  5,  14 },
            { 5,   4,  -3,   1, -2,  3, -3, -1, -3,  1, -30 },
            { -1,  3,   1,  -4, -2,  3, -4,  4,  3,  4,  71 },
            { -1, -4,  -2,   1,  2, -3, -5, -2, -4,  2, -86 },
            { -2, -4,   0,   0,  4, -2,  0, -4,  4, -4, -38 },
            { 4,  -2,   2,   1,  3,  2, -1, -4, -1,  2,   9 },
            { 4,   3,   3,  -5,  3,  1,  3,  2, -5,  2,  32 },
            { 2,   5,  -3,  -5,  2, -3, -3, -5,  5, -1, -51 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_10() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.equation(
        3,
        {
            { 2, 3, -1, 5 },
            { 4, 4, -3, 3 },
            { -2, 3, 2, 7 }
        }
    );
    solver.print();

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_20() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.equation(
        3,
        {
            { 2, 3, -1, 5 },
            { 4, 4, -3, 3 },
            { -2, 3, 2, 7 }
        }
    );
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}


static void test_linear_equation_21() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.equation(
        3,
        {
            { 0, 2, 1, 3 },
            { 1, -2, -3, -3 },
            { 3, -1, 2, 4 }
        }
    );
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}


void test_linear_equation()
{
    //test_linear_equation_01();
    //test_linear_equation_02();
    //test_linear_equation_03();
    //test_linear_equation_04();
    //test_linear_equation_05();

    //test_linear_equation_10();

    test_linear_equation_20();
}

// =====================================================================================
// End-of-File
// =====================================================================================
