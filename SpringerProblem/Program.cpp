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
#include <vector>
#include <array>
#include <list>
#include <mutex>
#include <algorithm>

#include "Coordinate.h"
#include "KnightProblemBoard.h"
#include "KnightProblemSolver.h"

// PeLo TODO:   Das Future sollte mit return die Anzahl der Lösungen zurückliefern !!!!












// =====================================================================================
// http://peterloos.de/index.php/m-multithreading/m-multithreading-tpl/58-a-mt-knights-problem
// =====================================================================================

// TODO: Die Methoden sollte man alle klein schreiben !!!

// TODO: Das mit dem GameBoard und dem int sollte man templatizieren .....

// TODO: Die Lösungen als Event // mit Lambdas ausgeben ...

// typedefs

//class Coordinate;
//using GameBoard = std::vector<std::vector<int>>;
//using Solution = std::vector<Coordinate>;
//using ListSolutions = std::list<Solution>;

// =====================================================================================

// TODO 1: Der Name ist blöd -- ChessField -- siehe auch Marc Gregoire

// TODO 2: m_row und m_col mit getter und setter schützen !!!




// =====================================================================================

// TODO 2: Den Solver als Schablone machen: int , short und long sind mögliche Kandidaten für die Suche ....

// TODO: Da werden viele Koordinaten by Value übergeben ... geht das auch per Referenz



// =====================================================================================

void test_01_springer_problem() {

    Coordinate coord(1, 2);
    std::cout << coord << std::endl;
}

void test_02_springer_problem() {

    //[Value] Elapsed time in milliseconds = 149[microsecs]
    //    Found: 32

    KnightProblemSolver solver(5, 4);
    solver.findMovesSequential();
    ListSolutions solutions = solver.getSolutions();

    int counter = 0;
    for (Solution s : solutions) {
        std::cout << counter << ":" << std::endl;

        for (Coordinate coord : s) {
            std::cout << coord << " ";
        }
    }

    std::cout << "Found: " << solutions.size() << std::endl;
}

void test_09_springer_problem() {

    //[Value] Elapsed time in milliseconds = 7152[microsecs]
//Found: 304

    KnightProblemSolver solver(5, 6);
    solver.findMovesSequential();
    ListSolutions solutions = solver.getSolutions();

    //int counter = 0;
    //for (Solution s : solutions) {
    //    std::cout << counter << ": ";

    //    for (Coordinate coord : s) {
    //        std::cout << coord << " ";
    //    }
    //    counter++;
    //    std::cout << std::endl;
    //}

    std::cout << "Found: " << solutions.size() <<  std::endl;
}

void test_10_springer_problem() {

    KnightProblemSolver solver(5, 4);
    solver.findMovesParallel();
    ListSolutions solutions = solver.getSolutions();

    //int counter = 0;
    //for (Solution s : solutions) {
    //    std::cout << counter << ": ";

    //    for (Coordinate coord : s) {
    //        std::cout << coord << " ";
    //    }
    //    counter++;
    //    std::cout << std::endl;
    //}

    std::cout << "Found: " << solutions.size() << std::endl;
}

void test_20_springer_problem() {

    KnightProblemSolver solver(5, 6);
    int count = solver.findMovesParallel(4);
    ListSolutions solutions = solver.getSolutions();

    //int counter = 0;
    //for (Solution s : solutions) {
    //    std::cout << counter << ": ";

    //    for (Coordinate coord : s) {
    //        std::cout << coord << " ";
    //    }
    //    counter++;
    //    std::cout << std::endl;
    //}

    // std::cout << "Found: " << solutions.size() << std::endl;
    std::cout << "Found: " << count << std::endl;
}

// =====================================================================================

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //test_02_springer_problem();
   //test_09_springer_problem();
   //test_10_springer_problem();

   test_20_springer_problem();

    return 0;
}

// =====================================================================================
