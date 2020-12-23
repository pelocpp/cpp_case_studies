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
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <future>
#include <chrono>
#include <sstream>
#include <algorithm>

#include "Globals.h"
#include "Log.h"
#include "Coordinate.h"
#include "KnightProblemBoard.h"
#include "KnightProblemSolver.h"

// =====================================================================================

namespace SpringerProblem {

    void test_00_springer_problem() {

        Coordinate coord(1, 2);
        std::cout << coord << std::endl;
    }

    void test_01_springer_problem() {

        log(std::cout, "Main: ", "findMovesSequential():");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesSequential();
        ListSolutions solutions = solver.getSolutions();
        //std::stringstream ss;
        //ss << solutions;
        //log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }

    void test_02_springer_problem() {

        log(std::cout, "Main: ", "findMovesParallel():");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesParallel();
        ListSolutions solutions = solver.getSolutions();
        //std::stringstream ss;
        //ss << solutions;
        //log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }

    void test_03_springer_problem() {

        log(std::cout, "Main: ", "findMovesParallel(0):");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesParallel(0);
        ListSolutions solutions = solver.getSolutions();
        //std::stringstream ss;
        //ss << solutions;
        //log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }

    void test_04_springer_problem() {

        log(std::cout, "Main: ", "findMovesParallel(2):");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesParallel(2);
        ListSolutions solutions = solver.getSolutions();
        std::stringstream ss;
        ss << solutions;
        log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }

    void test_05_springer_problem() {

        log(std::cout, "Main: ", "findMovesParallel(3):");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesParallel(3);
        ListSolutions solutions = solver.getSolutions();
        //std::stringstream ss;
        //ss << solutions;
        //log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }

    void test_06_springer_problem() {

        log(std::cout, "Main: ", "findMovesParallel(5):");
        KnightProblemSolver<Rows, Cols> solver;
        int count = solver.findMovesParallel(5);
        ListSolutions solutions = solver.getSolutions();
        //std::stringstream ss;
        //ss << solutions;
        //log(std::cout, ss.str());
        log(std::cout, "Found (int):         ", count);
        log(std::cout, "Found (sizeof List): ", solutions.size());
    }
}

void test_examples () {

    using namespace SpringerProblem;

    //test_01_springer_problem();
    test_02_springer_problem();
    //test_03_springer_problem();
    //test_04_springer_problem();
    // test_05_springer_problem();
    // test_06_springer_problem();
}

// =====================================================================================
// End-of-File
// =====================================================================================
