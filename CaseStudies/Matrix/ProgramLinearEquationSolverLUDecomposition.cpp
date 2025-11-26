// =====================================================================================
// ProgramLinearEquationSolverLUDecomposition.cpp
// =====================================================================================

#include "Vector.h"
#include "LinearEquationSolverLUDecomposition.h"

#include <print>

static void test_linear_equation_solver_lu_decomposition_01()
{
    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolverLUDecomposition<double> solver{ 3 };

    Matrix<double> matrix{ 3, 3 };
    matrix.elements
    ({ 
        {  2.0,  3.0,  1.0 },
        {  4.0,  7.0, -1.0 },
        { -2.0,  4.0,  5.0 }
    });
    solver.setEquation(matrix);

    Vector<double> rhs{ 1.0, 2.0, 3.0 };
    solver.setRightHandSide(rhs);
    std::println("{}", solver);

    solver.solve();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);

    // verify solution
    Vector<double> vector = matrix * solution;

    std::println("Right.hand Side: {}", rhs);
    std::println("Solution:        {}", solution);

    //if (vector == solution) {
    //    std::println("Ok.");
    //}
}

static void test_linear_equation_solver_lu_decomposition_02()
{
    // aus Buch Ronald Mak

    LinearEquationSolverLUDecomposition<double> solver{ 4 };

    solver.setEquation(
        {
            {  3.0,  1.0, -5.0,  4.0  },
            {  2.0, -3.0,  3.0, -2.0  },
            {  5.0, -3.0,  4.0,  1.0  },
            { -2.0,  4.0, -3.0, -5.0  },
        }
    );

    solver.setRightHandSide({ -18.0, 19.0, 22.0, -14.0 });
    std::println("{}", solver);

    solver.solve();

    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_lu_decomposition_03()
{
    // aus Internet // 10*10 Gleichung

    LinearEquationSolverLUDecomposition<double> solver{ 10 };

    solver.setEquation(
        {
            { 1,  -2,   5,   2, -1,  1,  4, -3,  1,  5 },
            { 5,   2,  -1,  -2,  2,  2, -3,  0, -1, -4 },
            { 2,   0,  -4,  -1, -5,  4,  0,  3, -5,  5 },
            { 5,   4,  -3,   1, -2,  3, -3, -1, -3,  1 },
            { -1,  3,   1,  -4, -2,  3, -4,  4,  3,  4 },
            { -1, -4,  -2,   1,  2, -3, -5, -2, -4,  2 },
            { -2, -4,   0,   0,  4, -2,  0, -4,  4, -4 },
            { 4,  -2,   2,   1,  3,  2, -1, -4, -1,  2 },
            { 4,   3,   3,  -5,  3,  1,  3,  2, -5,  2 },
            { 2,   5,  -3,  -5,  2, -3, -3, -5,  5, -1 }
        }
    );

    solver.setRightHandSide({ 84, -50, 14, -30, 71, -86, -38, 9, 32, -51 });
    std::println("{}", solver);

    solver.solve();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}


void test_linear_equation_solver_lu_decomposition()
{
    test_linear_equation_solver_lu_decomposition_01();     // 
    test_linear_equation_solver_lu_decomposition_02();     //  Ronald Mak // geht
    test_linear_equation_solver_lu_decomposition_03();     // Geht  
}

// =====================================================================================
// End-of-File
// =====================================================================================
