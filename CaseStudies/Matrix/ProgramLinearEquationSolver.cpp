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

    LinearEquationSolver solver;

    solver.setEquation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );
    solver.print();

    bool success{ solver.solve() };
    if (success) {

        const Vector<double>& solution = solver.solution();
        solution.print();
    }
}

static void test_linear_equation_02() {

    // Beispiel auf .pdf

    LinearEquationSolver solver;

    solver.setEquation(
        4,
        {
            { 1, 0, 1, 0, 4 },
            { 1, 1, 0, 1, 7 },
            { 1, 1, 2, 0, 6 },
            { 1, 0, 0, 1, 5 }
        }
    );
    solver.print();

    bool success{ solver.solve() };
    if (success) {

        const Vector<double>& solution = solver.solution();
        solution.print();
    }
}

static void test_linear_equation_03() {

    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolver solver;

    solver.setEquation(
        3,
        {
            { 1, -1,  2, 0 },
            { -2, 1, -6, 0 },
            { 1,  0, -2, 3 },
        }
    );
    solver.print();

    bool success{ solver.solve() };
    if (success) {

        const Vector<double>& solution = solver.solution();
        solution.print();
    }
}

void test_linear_equation()
{
    // test_linear_equation_01();
    // test_linear_equation_02();
    test_linear_equation_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
