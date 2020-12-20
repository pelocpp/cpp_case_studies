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
#include "KnightProblemBoard.h"
#include "KnightProblemSolver.h"

std::mutex  KnightProblemSolver::m_mutex;

KnightProblemSolver::KnightProblemSolver() : KnightProblemSolver(8, 8) {}

// PeLo TODO ---- Es gibt doch so was die Konstruktor delegieren !?!?!
KnightProblemSolver::KnightProblemSolver(int height, int width) {

    m_height = height;
    m_width = width;
    m_moveNumber = 0;    // PeLo ACHTUNG !!!!!!!!!!!!!!!!!!!!! Hier wird move number auf 0 gesetzt

    //   clearBoard();
}

// TODO: das passt irgendwie nicht: ein  dim versus zwei dim
//void KnightProblemSolver::clearBoard() {
//    for (unsigned int i = 0; i < m_board.size(); i++) {
//        m_board[i].fill(0);
//    }
//}

ListSolutions KnightProblemSolver::getSolutions() {
    return ListSolutions{ m_solutions }; // return a copy 
}


int KnightProblemSolver::findMovesSequential() {
    // reset data structures

    // TODO: PeLo irgendwie muss das board auf Null gesetzt werden 



    // reset data structures
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start{ m_height - 1, 0 };
    findMovesSequential(start);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "[Value] Elapsed time in milliseconds = " << duration << "[microsecs]" << std::endl;

    return static_cast<int> (m_solutions.size());  
}

// private helper - algorithm to solve the Knight's Tour problem
void KnightProblemSolver::findMovesSequential(const Coordinate& coord)
{
    setKnightMoveAt(coord);
    m_current.push_back(coord);

    if (isSolution())
    {
        // need a copy of the current solution
        Solution copy{ m_current };

        // add found solution to the list of all solutions
        m_solutions.push_back(copy);
    }
    else
    {
        // determine list of possible next moves
        std::vector<Coordinate> nextMoves = nextKnightMoves(coord);

        // do next moves sequential
        for (Coordinate coord : nextMoves) {
            findMovesSequential(coord);
        }
    }

    unsetKnightMoveAt(coord);
    m_current.pop_back();
}

// PeLo TODO Nur wegen Asnc !!!!
//int KnightProblemSolver::operator()(const Coordinate& coord) {
//    findMovesSequential(coord);
//
//    std::stringstream ss;
//    ss << "     ##########   " << countSolutions() << std::endl;
//    std::cout << ss.str();
//    ss.clear();
//
//    return countSolutions();
//}

// Zweite Version - wegen Parallilisierung
int KnightProblemSolver::operator()(const Coordinate& coord, int maxDepth) {
    int count = findMovesParallel(coord, maxDepth);

    std::stringstream ss;
    ss << "     ##########   " << count << std::endl;
    std::cout << ss.str();
    ss.clear();

    return count;
}

int KnightProblemSolver::findMovesParallel()
{

// TODO: PeLo irgendwie muss das board auf Null gesetzt werden

    // reset data structures
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start{ m_height - 1, 0 };
    findMovesParallel(start, true);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "[Value] Elapsed time in milliseconds = " << duration << "[microsecs]" << std::endl;

    return static_cast<int> (m_solutions.size());
}


// private helper - algorithm to solve the Knight's Tour problem
// using an parallel approach
//void KnightProblemSolver::findMovesParallel(const Coordinate& coord) {
//
//    setKnightMoveAt(coord);
//    m_current.push_back(coord);
//
//    if (isSolution()) {
//        // need a copy of the current solution
//        Solution copy{ m_current };
//
//        // add found solution *thread safe* to the list of all solutions
//        std::scoped_lock<std::mutex> lock(m_mutex);
//        m_solutions.push_back(copy);
//    }
//    else {
//        // determine list of possible next moves
//        std::vector<Coordinate> nextMoves = nextKnightMoves(coord);
//
//        for (unsigned int i = 0; i < nextMoves.size(); i++) {
//
//            Coordinate c = nextMoves.at(i);
//
//            KnightProblemSolver slaveSolver (this);
//
//            auto f = std::async(static_cast<void(KnightProblemSolver::*)(const Coordinate&)>  ( &KnightProblemSolver::findMovesSequential), &slaveSolver, c);
//            f.get();   // DAS IST SYNCHRON ; ICH WEIß
//
//            std::cout << "FOUND: " << slaveSolver.getSolutions().size() << std::endl;
//        }
//    }
//
//    unsetKnightMoveAt(coord);
//    m_current.pop_back();
//}


// Zweiter Versuch - geht vermutlich !!!! ABER OHNE ZWEITEN PARAMETER
//void KnightProblemSolver::findMovesParallel(const Coordinate& coord) {
//
//    setKnightMoveAt(coord);
//    m_current.push_back(coord);
//
//    // determine list of possible next moves
//    std::vector<Coordinate> nextMoves = nextKnightMoves(coord);
//    std::deque<std::future<int>> futures;
//
//    for (unsigned int i = 0; i < nextMoves.size(); i++) {
//
//       Coordinate nextCoord = nextMoves.at(i);
//
//       // make a copy of the solver including the current board
//       KnightProblemSolver slaveSolver = *this;
//
//       // BEGIN: SEQ
//        //slaveSolver.findMovesSequential(nextCoord);
//        //std::cout << "     ########   " << slaveSolver.countSolutions() <<  std::endl;
//        // END: SEQ   ***/
//
//        // BEGIN: PAR
//         std::future<int> future = std::async(std::launch::async, std::move(slaveSolver), nextCoord);
//          futures.push_back(std::move(future));
//        // END: PER
//    }
//
//    // block async tasks in this method and compute final result
//    int result{};
//
//    // das mit der Bedingung verstehe ich NICHT !=!=!
//     int count = static_cast<int>(futures.size());
//     for (int i = 0; i < count; i++) 
//     {
//        std::future<int> future = std::move(futures.front());
//        futures.pop_front();
//
//        int partialResult = future.get();
//        std::cout << "     parallel: partialResult --->  " << partialResult << std::endl;
//
//        result += partialResult;
//    }
//
//    std::cout << "     parallel ===>  " << result << std::endl;
//
//    unsetKnightMoveAt(coord);
//    m_current.pop_back();
//}

// -----------------------------------------------------------------------

// ZWEITER VERSUCH - Die Ebene tiefer parallelisieren !!!
int KnightProblemSolver::findMovesParallel(int maxDepth)
{

    // TODO: PeLo irgendwie muss das board auf Null gesetzt werden

    // reset data structures
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start{ m_height - 1, 0 };
    int count = findMovesParallel(start, maxDepth);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "[Value] Elapsed time in milliseconds = " << duration << "[microsecs]" << std::endl;

    // return static_cast<int> (m_solutions.size());
    return count;
}

int KnightProblemSolver::findMovesParallel(const Coordinate& coord, int maxDepth) {

    setKnightMoveAt(coord);
    m_current.push_back(coord);

    // determine list of possible next moves
    std::vector<Coordinate> nextMoves = nextKnightMoves(coord);
    std::deque<std::future<int>> futures;

    // das mit dem result ist vertreut ... das ist so nicht schön ....
    int result{};

    for (unsigned int i = 0; i < nextMoves.size(); i++) {

        Coordinate nextCoord = nextMoves.at(i);

        // make a copy of the solver including the current board
        KnightProblemSolver slaveSolver = *this;

        if (maxDepth > 0) {
            // do next moves parallel or ...

            // BEGIN: PAR
            std::future<int> future = std::async(std::launch::async, std::move(slaveSolver), nextCoord, maxDepth - 1);
            futures.push_back(std::move(future));
            // END: PER
        }
        else {

            // BEGIN: SEQ
             slaveSolver.findMovesSequential(nextCoord);
             result += slaveSolver.countSolutions();
             // std::cout << "     ########   " << result <<  std::endl;
             // END: SEQ   ***/
        }
    }

    // block async tasks in this method and compute final result

    // das mit der Bedingung verstehe ich NICHT !=!=!
    int count = static_cast<int>(futures.size());
    for (int i = 0; i < count; i++)
    {
        std::future<int> future = std::move(futures.front());
        futures.pop_front();

        int partialResult = future.get();
        // std::cout << "     parallel: partialResult --->  " << partialResult << std::endl;

        result += partialResult;
    }

   // std::cout << "     parallel ===>  " << result << std::endl;

    unsetKnightMoveAt(coord);
    m_current.pop_back();

    return result;
}

// =========================================================================================

int KnightProblemSolver::countSolutions() {
    return static_cast<int> (m_solutions.size());
}

// occupy square on the chess board
void KnightProblemSolver::setKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber++;
    m_board.at(coord) = m_moveNumber;
}

// release square on the chess board
void KnightProblemSolver::unsetKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber--;
    m_board.at(coord) = 0;
}

//  checks, whether coordinate does exist on the chess board
bool KnightProblemSolver::inRange(const Coordinate& coord)
{
    return (coord.getRow() >= 0) && (coord.getRow() < m_height) && (coord.getCol() >= 0) && (coord.getCol() < m_width);
}

// checks, whether coordinate is valid and is still not taken
bool KnightProblemSolver::canMoveTo(const Coordinate& coord)
{
    return inRange(coord) && (m_board.at(coord) <= 0);
}

// verify, whether current list of moves is a solution
bool KnightProblemSolver::isSolution()
{
    return m_moveNumber >= m_height * m_width;
}

std::vector<Coordinate> KnightProblemSolver::nextKnightMoves(const Coordinate& coord)
{
    std::vector<Coordinate> result;

    if (Coordinate tmp{ coord.fromOffset(2, 1) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(1, 2) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(-2, 1) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(-1, 2) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(2, -1) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(1, -2) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(-2, -1) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }
    if (Coordinate tmp{ coord.fromOffset(-1, -2) }; canMoveTo(tmp))
    {
        result.push_back(tmp);
    }

    return result;
}