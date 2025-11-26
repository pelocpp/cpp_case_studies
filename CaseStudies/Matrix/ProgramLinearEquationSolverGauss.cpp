// =====================================================================================
// ProgramLinearEquationSolverGauss.cpp
// =====================================================================================

// 2 Beispiele:
//
//https://www.youtube.com/watch?v=vaahX3Wdxu8
//
//https://www.youtube.com/watch?v=9Ule9qQaBB0

#include "Vector.h"
#include "LinearEquationSolverGauss.h"

#include <print>

static void test_linear_equation_solver_gauss_01() {

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        1,
        {
            { 2.0,  4.0 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_02() {

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  2.0,  3.0, -1.0, -9.0 },
            {  1.0, -2.0,  1.0,  9.0 },
            { -1.0,  1.0,  2.0,  0.0 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_03() {

    // Beispiel aus .pdf

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        4,
        {
            { 1.0, 0.0, 1.0, 0.0, 4.0 },
            { 1.0, 1.0, 0.0, 1.0, 7.0 },
            { 1.0, 1.0, 2.0, 0.0, 6.0 },
            { 1.0, 0.0, 0.0, 1.0, 5.0 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_04() {

    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  1.0, -1.0,  2.0, 0.0 },
            { -2.0,  1.0, -6.0, 0.0 },
            {  1.0,  0.0, -2.0, 3.0 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_05() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        10,
        {
            {  1.0,  -2.0,   5.0,   2.0, -1.0,  1.0,  4.0, -3.0,  1.0,  5.0,  84.0 },
            {  5.0,   2.0,  -1.0,  -2.0,  2.0,  2.0, -3.0,  0.0, -1.0, -4.0, -50.0 },
            {  2.0,   0.0,  -4.0,  -1.0, -5.0,  4.0,  0.0,  3.0, -5.0,  5.0,  14.0 },
            {  5.0,   4.0,  -3.0,   1.0, -2.0,  3.0, -3.0, -1.0, -3.0,  1.0, -30.0 },
            { -1.0,   3.0,   1.0,  -4.0, -2.0,  3.0, -4.0,  4.0,  3.0,  4.0,  71.0 },
            { -1.0,  -4.0,  -2.0,   1.0,  2.0, -3.0, -5.0, -2.0, -4.0,  2.0, -86.0 },
            { -2.0,  -4.0,   0.0,   0.0,  4.0, -2.0,  0.0, -4.0,  4.0, -4.0, -38.0 },
            {  4.0,  -2.0,   2.0,   1.0,  3.0,  2.0, -1.0, -4.0, -1.0,  2.0,   9.0 },
            {  4.0,   3.0,   3.0,  -5.0,  3.0,  1.0,  3.0,  2.0, -5.0,  2.0,  32.0 },
            {  2.0,   5.0,  -3.0,  -5.0,  2.0, -3.0, -3.0, -5.0,  5.0, -1.0, -51.0 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_06() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            { 2, 1, -1, 8 },
            { -3, -1, 2, -11 },
            { -2, 1, 2, -3 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_10() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  2, 3, -1, 5 },
            {  4, 4, -3, 3 },
            { -2, 3,  2, 7 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_20() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
        }
    );
    std::println("{}", solver);

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_21() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
        }
    );
    std::println("{}", solver);

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_22() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
        }
    );
    std::println("{}", solver);

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}



static void test_linear_equation_solver_gauss_24() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            { 0,  2,  1,  3 },
            { 1, -2, -3, -3 },
            { 3, -1,  2,  4 }
        }
    );
    std::println("{}", solver);

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}



static void test_linear_equation_solver_gauss_30() {

    // Ronald Mak, p. 273
    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        2,
        {
            { 0.0001, 2, 2 },
            {      1, 1, 2 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}



static void test_linear_equation_solver_gauss_31() {

    // Ronald Mak, p. 269
    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}



static void test_linear_equation_solver_gauss_32() {

    // Ronald Mak, p. 269
    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    std::println("{}", solver);

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}


static void test_linear_equation_solver_gauss_33() {

    // Ronald Mak, p. 269
    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    std::println("{}", solver);

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}



static void test_linear_equation_solver_gauss_40() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
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
    std::println("{}", solver);

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_41() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
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
    std::println("{}", solver);

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_42() {

    // Larger example, created by ChatGPT

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
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
    std::println("{}", solver);

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}


static void test_linear_equation_solver_gauss_51() {

    // Ronald Mak, p. 269
    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );

    std::println("Solving Equation:");
    std::println("{}", solver);

    solver.eliminateForward();

    solver.substituteBack();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);
}

static void test_linear_equation_solver_gauss_52() {

    // aus https://www.youtube.com/watch?v=vaahX3Wdxu8

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );

    std::println("Solving Equation:");
    std::println("{}", solver);

    Vector<double> row1{  2.0,  3.0, -1.0, -9.0 };
    Vector<double> row2{  1.0, -2.0,  1.0,  9.0 };
    Vector<double> row3{ -1.0,  1.0,  2.0,  0.0 };

    double pivot{ 1.0/2.0 };

    row2 = row2 - row1 * pivot;
    std::println("2. row");
    std::println("{}", row2);

    pivot = -1.0 / 2;
    row3 = row3 - row1 * pivot;
    std::println("3. row");
    std::println("{}", row3);

    pivot = -5.0 / 7;
    row3 = row3 - row2 * pivot;
    std::println("3. row");
    std::println("{}", row3);

    std::println("Using LinearEquationSolver:");

    solver.eliminateForward();
    solver.substituteBack();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);

    // verification of result:
}

static void test_linear_equation_solver_gauss_53() {

    // Ronald Mak, p. 269

    LinearEquationSolverGauss<double> solver;

    solver.setEquation(
        4,
        {
            {  3.0,  1.0, -5.0,  4.0, -18.0 },
            {  2.0, -3.0,  3.0, -2.0,  19.0 },
            {  5.0, -3.0,  4.0,  1.0,  22.0 },
            { -2.0,  4.0, -3.0, -5.0, -14.0 }      // Using corrected value
        }
    );

    std::println("Solving Equation:");
    std::println("{}", solver);
    std::println();

    // ---------------------------------------------
    // ---------------------------------------------

    Vector<double> row1{  3.0,  1.0, -5.0,  4.0, -18.0 };
    Vector<double> row2{  2.0, -3.0,  3.0, -2.0,  19.0 };
    Vector<double> row3{  5.0, -3.0,  4.0,  1.0,  22.0 };
    Vector<double> row4{ -2.0,  4.0, -3.0, -5.0, -14.0 };   // Using corrected value

    // ---------------------------------------------
    // ---------------------------------------------

    std::println("2. column:");
    std::println();

    double pivot{ 2.0 / 3.0 };
    row2 = row2 - row1 * pivot;
    std::println("2. row");
    std::println("{}", row2);

    pivot = 5.0 / 3.0;
    row3 = row3 - row1 * pivot;
    std::println("3. row");
    std::println("{}", row3);

    pivot = -2.0 / 3.0;
    row4 = row4 - row1 * pivot;
    std::println("4. row");
    std::println("{}", row4);
    
    // ---------------------------------------------

    std::println("3. column:");
    std::println();

    pivot = 14.0 / 11.0;
    row3 = row3 - row2 * pivot;
    std::println("3. row");
    std::println("{}", row3);
   
    pivot = -14.0 / 11.0;
    row4 = row4 - row2 * pivot;
    std::println("4. row");
    std::println("{}", row4);

    // ---------------------------------------------

    std::println("4. column:");
    std::println();

    pivot = 57.0 / 141.0;

    row4 = row4 - row3 * pivot;
    std::println("4. row");
    std::println("{}", row4);

    // ---------------------------------------------


    solver.eliminateForward();
    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    std::println("{}", solution);


    // ---------------------------------------------

    // Hmmm , habe die Lösung aus dem Buch --- setze die Lösung in die Matrix ein:

    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
    {
        {  3,  1, -5,  4 }, 
        {  2, -3,  3, -2 },
        {  5, -3,  4,  1 },
        { -2,  4, -3, -5 }    // Using corrected value
    });

    Matrix<double> vector{ 4, 1 };
    vector.elements({ 1, -2, 3, -1 } );

    Matrix<double> result{ 4, 1 };
    result = matrix.mul(vector);

    std::println("{}", result);
}


void test_linear_equation_solver_gauss()
{
    //test_linear_equation_solver_gauss_01();           // { 2 }
    //test_linear_equation_solver_gauss_02();         // { 1,     -3,  2 }
    //test_linear_equation_solver_gauss_03();         // { 4,  2,  0,  1}
    //test_linear_equation_solver_gauss_04();         // { 2,  1,   -0.5 }
    //test_linear_equation_solver_gauss_05();         // {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10 }
    //test_linear_equation_solver_gauss_06();             //  { 2, 3, -1}

    //test_linear_equation_solver_gauss_10();           // { 2.875,   1.25,    4.5 }
    //
    //test_linear_equation_solver_gauss_20();           // { 2.875,   1.25,    4.5 }  // simple
    //test_linear_equation_solver_gauss_21();          // { 2.875,   1.25,    4.5 }  // pivot
    //test_linear_equation_solver_gauss_22();            // { 2.875,   1.25,    4.5 }  // permutation vector

    ////Ronald Mak
    //test_linear_equation_solver_gauss_30();
    //test_linear_equation_solver_gauss_31();
    //test_linear_equation_solver_gauss_32();
    //test_linear_equation_solver_gauss_33();

    //test_linear_equation_solver_gauss_40();   // korrekt
    //test_linear_equation_solver_gauss_41();   // korrekt
    //test_linear_equation_solver_gauss_42();   // korrekt

    //test_linear_equation_solver_gauss_51();
    //test_linear_equation_solver_gauss_52();
    test_linear_equation_solver_gauss_53();   // Ronald Mak, korrigierte Matrix
}

// =====================================================================================
// End-of-File
// =====================================================================================
