// =====================================================================================
// Program.cpp
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <mutex>
#include <future>
#include <chrono>
#include <sstream>
#include <memory>
#include <algorithm>

#include "Coordinate.h"
#include "KnightProblemBoard.hpp"
#include "KnightProblemSolver.hpp"

// =====================================================================================
// http://peterloos.de/index.php/m-multithreading/m-multithreading-tpl/58-a-mt-knights-problem
// =====================================================================================

// PeLo TODO:   Das Future sollte mit return die Anzahl der Lösungen zurückliefern !!!!

// TODO: Die Lösungen als Event // mit Lambdas ausgeben ...

// TODO: Da werden viele Koordinaten by Value übergeben ... geht das auch per Referenz

// =====================================================================================

    //int counter = 0;
    //for (Solution s : solutions) {
    //    std::cout << counter << ": ";

    //    for (Coordinate coord : s) {
    //        std::cout << coord << " ";
    //    }
    //    counter++;
    //    std::cout << std::endl;
    //}



// =====================================================================================

constexpr int Rows = 5;
constexpr int Cols = 4;

// =====================================================================================


void test_00_springer_problem() {

    Coordinate coord(1, 2);
    std::cout << coord << std::endl;
}

void test_01_springer_problem() {

    log(std::cout, "Main: ", "findMovesSequential():");
    KnightProblemSolver<Rows, Cols> solver;
    int count = solver.findMovesSequential();
    ListSolutions solutions = solver.getSolutions();

    log(std::cout, "Found (int):         ", count);
    log(std::cout, "Found (sizeof List): ", solutions.size());
}

void test_02_springer_problem() {

    log(std::cout, "Main: ", "findMovesParallel():");
    KnightProblemSolver<Rows, Cols> solver;
    int count = solver.findMovesParallel();
    ListSolutions solutions = solver.getSolutions();

    log(std::cout, "Found (int):         ", count);
    log(std::cout, "Found (sizeof List): ", solutions.size());
}

void test_03_springer_problem() {

    log(std::cout, "Main: ", "findMovesParallel(0):");
    KnightProblemSolver<Rows, Cols> solver;
    int count = solver.findMovesParallel(0);
    ListSolutions solutions = solver.getSolutions();

    log(std::cout, "Found (int):         ", count);
    log(std::cout, "Found (sizeof List): ", solutions.size());
}

void test_04_springer_problem() {

    log(std::cout, "Main: ", "findMovesParallel(2):");
    KnightProblemSolver<Rows, Cols> solver;
    int count = solver.findMovesParallel(2);
    ListSolutions solutions = solver.getSolutions();

    log(std::cout, "Found (int):         ", count);
    log(std::cout, "Found (sizeof List): ", solutions.size());
}

void test_05_springer_problem() {

    log(std::cout, "Main: ", "findMovesParallel(3):");
    KnightProblemSolver<Rows, Cols> solver;
    int count = solver.findMovesParallel(3);
    ListSolutions solutions = solver.getSolutions();

    log(std::cout, "Found (int):         ", count);
    log(std::cout, "Found (sizeof List): ", solutions.size());
}

// ==== ================================================================================

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //test_01_springer_problem();
    test_02_springer_problem();
    //test_03_springer_problem();
    //test_04_springer_problem();
    // test_05_springer_problem();

    return 0;
}


// =====================================================================================
// End-of-File
// =====================================================================================