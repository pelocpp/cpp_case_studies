// =====================================================================================
// ProgramLinearEquationSolverLUDecomposition.cpp
// =====================================================================================

#include "Vector.h"
#include "LinearEquationSolverLUDecomposition.h"

#include <print>

static void test_linear_equation_lu_decomposition_01()
{
    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolverLUDecomposition<double> solver{ 3 };

    solver.setEquation(
        {
            {  2.0,  3.0,  1.0 },
            {  4.0,  7.0, -1.0 },
            { -2.0,  4.0,  5.0 }
        }
    );

    solver.setRightHandSide({ 1.0, 2.0, 3.0 });
    solver.print();
    solver.solve();

    const Vector<double>& solution = solver.solution();
    solution.print();
}

void test_linear_equation_lu_decomposition()
{
    test_linear_equation_lu_decomposition_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
