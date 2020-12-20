// =====================================================================================
// KnightProblemSolver.hpp
// =====================================================================================

#pragma once

#include "Coordinate.h"
#include "KnightProblemBoard.hpp"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <future>
#include <chrono>
#include <sstream>
#include <algorithm>

using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;

//const int Rows = 4;   == HEIGHT
//const int Cols = 7;   == WIDTH

//using GameBoard = std::array<std::array<int, Cols>, Rows>;

template <int ROWS, int COLS>
class KnightProblemSolver {

public:
    KnightProblemSolver();

public:
    // getter/setter
    int getHeight() const { return ROWS; } 
    int getWidth() const { return COLS; }

    ListSolutions getSolutions();

    // public interface
    int findMovesSequential();
    int findMovesParallel();   // TODO : mit Vorbelegunswert eliminieren ...
    int findMovesParallel(int maxDepth);

    int countSolutions();

    // needed for std::async
    int operator()(const Coordinate& coord, int maxDepth);

private:
    // internal helper methods
    void setKnightMoveAt(const Coordinate& coord);
    void unsetKnightMoveAt(const Coordinate& coord);
    std::vector<Coordinate> nextKnightMoves(const Coordinate& coord);
    bool inRange(const Coordinate& coord);
    bool canMoveTo(const Coordinate& coord);
    bool isSolution();

    int findMovesSequential(const Coordinate& coord);
    int findMovesParallel(const Coordinate& coord, int maxDepth);

private:
    int                            m_height;      // height of board
    int                            m_width;       // width of board

    KnightProblemBoard<ROWS, COLS> m_board;       // chess board

    ListSolutions                  m_solutions;   // list of found solutions
    Solution                       m_current;     // solution being in construction
    int                            m_moveNumber;  // number of last knight's move
};

// ================================================================================
// public interface

template <int ROWS, int COLS>
KnightProblemSolver<ROWS, COLS>::KnightProblemSolver() {

    m_height = ROWS;
    m_width = COLS;
    m_moveNumber = 0;    // PeLo ACHTUNG !!!!!!!!!!!!!!!!!!!!! Hier wird move number auf 0 gesetzt
}

template <int ROWS, int COLS>
ListSolutions KnightProblemSolver<ROWS, COLS>::getSolutions() {
    return ListSolutions{ m_solutions }; // return a copy 
}

template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::findMovesSequential() {

    // reset data structures
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();
    m_board.clearBoard();

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

template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::findMovesParallel()
{
    // reset data structures
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();
    m_board.clearBoard();

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

// ================================================================================
// private interface

// private helper - algorithm to solve the Knight's Tour problem
template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::findMovesSequential(const Coordinate& coord)
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

    return static_cast<int> (m_solutions.size());
}

template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::findMovesParallel(int maxDepth)
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

template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::findMovesParallel(const Coordinate& coord, int maxDepth) {

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

// Zweite Version - wegen Parallelisierung
template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::operator()(const Coordinate& coord, int maxDepth) {
    int count = findMovesParallel(coord, maxDepth);

    std::stringstream ss;
    ss << "     ##########   " << count << std::endl;
    std::cout << ss.str();
    ss.clear();

    return count;
}

// =========================================================================================

template <int ROWS, int COLS>
int KnightProblemSolver<ROWS, COLS>::countSolutions() {
    return static_cast<int> (m_solutions.size());
}

// occupy square on the chess board
template <int ROWS, int COLS>
void KnightProblemSolver<ROWS, COLS>::setKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber++;
    m_board.at(coord) = m_moveNumber;
}

// release square on the chess board
template <int ROWS, int COLS>
void KnightProblemSolver<ROWS, COLS>::unsetKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber--;
    m_board.at(coord) = 0;
}

//  checks, whether coordinate does exist on the chess board
template <int ROWS, int COLS>
bool KnightProblemSolver<ROWS, COLS>::inRange(const Coordinate& coord)
{
    return (coord.getRow() >= 0) && (coord.getRow() < m_height) && (coord.getCol() >= 0) && (coord.getCol() < m_width);
}

// checks, whether coordinate is valid and is still not taken
template <int ROWS, int COLS>
bool KnightProblemSolver<ROWS, COLS>::canMoveTo(const Coordinate& coord)
{
    return inRange(coord) && (m_board.at(coord) <= 0);
}

// verify, whether current list of moves is a solution
template <int ROWS, int COLS>
bool KnightProblemSolver<ROWS, COLS>::isSolution()
{
    return m_moveNumber >= m_height * m_width;
}

template <int ROWS, int COLS>
std::vector<Coordinate> KnightProblemSolver<ROWS, COLS>::nextKnightMoves(const Coordinate& coord)
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

// =====================================================================================
// End-of-File
// =====================================================================================