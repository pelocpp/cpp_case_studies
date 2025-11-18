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

    solver.setEquation(
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

    solver.setEquation(
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

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_04() {

    // aus https://www.mathebibel.de/gauss-algorithmus

    LinearEquationSolver<double> solver;

    solver.setEquation(
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

    solver.setEquation(
        10,
        {
            {  1,   -2,   5,   2, -1,  1,  4, -3,  1,  5,  84 },
            {  5,   2,  -1,  -2,  2,  2, -3,  0, -1, -4, -50 },
            {  2,   0,  -4,  -1, -5,  4,  0,  3, -5,  5,  14 },
            {  5,   4,  -3,   1, -2,  3, -3, -1, -3,  1, -30 },
            { -1,   3,   1,  -4, -2,  3, -4,  4,  3,  4,  71 },
            { -1,  -4,  -2,   1,  2, -3, -5, -2, -4,  2, -86 },
            { -2,  -4,   0,   0,  4, -2,  0, -4,  4, -4, -38 },
            {  4,  -2,   2,   1,  3,  2, -1, -4, -1,  2,   9 },
            {  4,   3,   3,  -5,  3,  1,  3,  2, -5,  2,  32 },
            {  2,   5,  -3,  -5,  2, -3, -3, -5,  5, -1, -51 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_06() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            { 2, 1, -1, 8 },
            { -3, -1, 2, -11 },
            { -2, 1, 2, -3 }
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

    solver.setEquation(
        3,
        {
            {  2, 3, -1, 5 },
            {  4, 4, -3, 3 },
            { -2, 3,  2, 7 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_20() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
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

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
        }
    );
    solver.print();

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_22() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            {  2,  3, -1,  5 },
            {  4,  4, -3,  3 },
            { -2,  3,  2,  7 }
        }
    );
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}



static void test_linear_equation_24() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            { 0,  2,  1,  3 },
            { 1, -2, -3, -3 },
            { 3, -1,  2,  4 }
        }
    );
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}



static void test_linear_equation_30() {

    // Ronald Mak, p. 273
    LinearEquationSolver<double> solver;

    solver.setEquation(
        2,
        {
            { 0.0001, 2, 2 },
            {      1, 1, 2 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}



static void test_linear_equation_31() {

    // Ronald Mak, p. 269
    LinearEquationSolver<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}



static void test_linear_equation_32() {

    // Ronald Mak, p. 269
    LinearEquationSolver<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    solver.print();

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    solution.print();
}


static void test_linear_equation_33() {

    // Ronald Mak, p. 269
    LinearEquationSolver<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}



static void test_linear_equation_40() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

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
    solver.print();

    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_41() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

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
    solver.print();

    solver.solve_02_pivot();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_42() {

    // Larger example, created by ChatGPT

    LinearEquationSolver<double> solver;

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
    solver.print();

    solver.solve_03_permutation_vector();
    const Vector<double>& solution = solver.solution();
    solution.print();
}


static void test_linear_equation_51() {

    // Ronald Mak, p. 269
    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );

    std::println("Solving Equation:");
    solver.print();

    solver.eliminateForward();

    solver.substitueBack();
    const Vector<double>& solution = solver.solution();
    solution.print();
}

static void test_linear_equation_52() {

    // aus https://www.youtube.com/watch?v=vaahX3Wdxu8

    LinearEquationSolver<double> solver;

    solver.setEquation(
        3,
        {
            { 2,  3, -1, -9 },
            { 1, -2,  1,  9 },
            { -1, 1,  2,  0 }
        }
    );

    std::println("Solving Equation:");
    solver.print();

    Vector<double> row1{ 4, {  2,  3, -1, -9 } };
    Vector<double> row2{ 4, {  1, -2,  1,  9 } };
    Vector<double> row3{ 4, { -1,  1,  2,  0 } };

    double pivot{ 1.0/2.0 };

    row2 = row2 - row1 * pivot;
    std::println("2. row");
    row2.print();

    pivot = -1.0 / 2;
    row3 = row3 - row1 * pivot;
    std::println("3. row");
    row3.print();

    pivot = -5.0 / 7;
    row3 = row3 - row2 * pivot;
    std::println("3. row");
    row3.print();

    std::println("Using LinearEquationSolver:");

    solver.eliminateForward();
    solver.substitueBack();
    const Vector<double>& solution = solver.solution();
    solution.print();

    // verification of result:
}

static void test_linear_equation_53() {

    // Ronald Mak, p. 269

    LinearEquationSolver<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -3, -14 }
        }
    );

    std::println("Solving Equation:");
    solver.print();

    // ---------------------------------------------
    // ---------------------------------------------

    Vector<double> row1{ 5, { 3,  1, -5,  4, -18 } };
    Vector<double> row2{ 5, { 2, -3,  3, -2,  19 } };
    Vector<double> row3{ 5, { 5, -3,  4,  1,  22 } };
    Vector<double> row4{ 5, {-2,  4, -3, -3, -14 } };

    // ---------------------------------------------
    // ---------------------------------------------

    std::println("2. column:");
    std::println();

    double pivot{ 2.0 / 3.0 };
    row2 = row2 - row1 * pivot;
    std::println("2. row");
    row2.print();

    pivot = 5.0 / 3.0;
    row3 = row3 - row1 * pivot;
    std::println("3. row");
    row3.print();

    pivot = -2.0 / 3.0;
    row4 = row4 - row1 * pivot;
    std::println("4. row");
    row4.print();
    
    // ---------------------------------------------

    std::println("3. column:");
    std::println();

    pivot = 14.0 / 11.0;
    row3 = row3 - row2 * pivot;
    std::println("3. row");
    row3.print();
   
    pivot = -14.0 / 11.0;
    row4 = row4 - row2 * pivot;
    std::println("4. row");
    row4.print();

    // ---------------------------------------------

    std::println("4. column:");
    std::println();

    pivot = 57.0 / 141.0;

    row4 = row4 - row3 * pivot;
    std::println("4. row");
    row4.print();

    // ---------------------------------------------

    solver.eliminateForward();
    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();

    // ---------------------------------------------

    // Hmmm , habe die Lösung aus dem Buch --- setze die Lösung in die Matrix ein:

    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
    {
        { 3,  1, -5,  4 }, 
        { 2, -3,  3, -2 },
        { 5, -3,  4,  1 },
        { -2,  4, -3, -3 }
    });

    Matrix<double> vector{ 4, 1 };
    vector.elements({ 1, -2, 3, -1 } );

    //Matrix<double> vector{ 1, 4 };
    //matrix.elements({ 1, -2, 3, -1 });

    Matrix<double> result{ 4, 1 };
    result = matrix.mul(vector);

    result.print();
}


static void test_linear_equation_54() {

    // Ronald Mak, p. 269
    // Suche nach einem Fehler

    // ALSO ES GIBT DA ZWEI BAUSTELLEN:

    // 4. Element in der 4. Gleichung:  -5 an statt -3
    // ODER
    // 4. Element der rechten Seite: -16 an Statt -14

    // NAchdem auf Seite 275 es in der 4. Gleichung   { -2,  4, -3, -5, -14 }

    LinearEquationSolver<double> solver;

    solver.setEquation(
        4,
        {
            {  3,  1, -5,  4, -18 },
            {  2, -3,  3, -2,  19 },
            {  5, -3,  4,  1,  22 },
            { -2,  4, -3, -5, -14 }
        }
    );

    std::println("Solving Equation:");
    solver.print();


    solver.solve_01_simple();
    const Vector<double>& solution = solver.solution();
    solution.print();


    // ---------------------------------------------
    // ---------------------------------------------

    //Vector<double> row1{ 5, { 3,  1, -5,  4, -18 } };
    //Vector<double> row2{ 5, { 2, -3,  3, -2,  19 } };
    //Vector<double> row3{ 5, { 5, -3,  4,  1,  22 } };
    //Vector<double> row4{ 5, {-2,  4, -3, -3, -14 } };

    //// ---------------------------------------------
    //// ---------------------------------------------

    //std::println("2. column:");
    //std::println();

    //double pivot{ 2.0 / 3.0 };
    //row2 = row2 - row1 * pivot;
    //std::println("2. row");
    //row2.print();

    //pivot = 5.0 / 3.0;
    //row3 = row3 - row1 * pivot;
    //std::println("3. row");
    //row3.print();

    //pivot = -2.0 / 3.0;
    //row4 = row4 - row1 * pivot;
    //std::println("4. row");
    //row4.print();

    //// ---------------------------------------------

    //std::println("3. column:");
    //std::println();

    //pivot = 14.0 / 11.0;
    //row3 = row3 - row2 * pivot;
    //std::println("3. row");
    //row3.print();

    //pivot = -14.0 / 11.0;
    //row4 = row4 - row2 * pivot;
    //std::println("4. row");
    //row4.print();

    //// ---------------------------------------------

    //std::println("4. column:");
    //std::println();

    //pivot = 57.0 / 141.0;

    //row4 = row4 - row3 * pivot;
    //std::println("4. row");
    //row4.print();

    //// ---------------------------------------------

    //solver.eliminateForward();
    //solver.solve_01_simple();
    //const Vector<double>& solution = solver.solution();
    //solution.print();

    // ---------------------------------------------

    // Hmmm , habe die Lösung aus dem Buch --- setze die Lösung in die Matrix ein:

 //   { -2, 4, -3, -5, -14 }

    std::println("---------------------------");


    Matrix<double> matrix{ 4, 4 };
    matrix.elements(
        {
            { 3,  1, -5,  4 },
            { 2, -3,  3, -2 },
            { 5, -3,  4,  1 },
            { -2,  4, -3, -5 }
        });

    Matrix<double> vector{ 4, 1 };
    vector.elements({ 1, -2, 3, -1 });

    //Matrix<double> vector{ 1, 4 };
    //matrix.elements({ 1, -2, 3, -1 });

    Matrix<double> result{ 4, 1 };
    result = matrix.mul(vector);

    result.print();
}


void test_linear_equation()
{
    //test_linear_equation_01();           // { 2 }
    //test_linear_equation_02();         // { 1,     -3,  2 }
    //test_linear_equation_03();         // { 4,  2,  0,  1}
    //test_linear_equation_04();         // { 2,  1,   -0.5 }
    //test_linear_equation_05();         // {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10 }
    //test_linear_equation_06();             //  { 2, 3, -1}

    //test_linear_equation_10();           // { 2.875,   1.25,    4.5 }
    
    //test_linear_equation_20();           // { 2.875,   1.25,    4.5 }  // simple
    //test_linear_equation_21();          // { 2.875,   1.25,    4.5 }  // pivot
    //test_linear_equation_22();            // { 2.875,   1.25,    4.5 }  // permutation vector

    //Ronald Mak
    //test_linear_equation_30();
  // test_linear_equation_31();
    //test_linear_equation_32();
   // test_linear_equation_33();

    //test_linear_equation_40();   // korrekt
    //test_linear_equation_41();   // korrekt
  //  test_linear_equation_42();   // korrekt

  // test_linear_equation_50();
   //test_linear_equation_51();
   // test_linear_equation_52();
  // test_linear_equation_53();
   test_linear_equation_54();
}



// =====================================================================================
// End-of-File
// =====================================================================================
