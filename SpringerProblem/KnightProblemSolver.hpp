// =====================================================================================
// KnightProblemSolver.hpp
// =====================================================================================

#pragma once

#include "Coordinate.h"
#include "KnightProblemBoard.hpp"

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

// =========================================================================================

template<typename ...Args>
static void log(std::ostream& os, Args ...args)
{
    std::stringstream ss;
    std::thread::id currentThreadId = std::this_thread::get_id();
    ss << "[" << std::setw(5) << std::right << currentThreadId << "]: ";
    (ss << ... << args) << std::endl;
    os << ss.str();
}

// =========================================================================================





using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;

template <int HEIGHT, int WIDTH>
class KnightProblemSolver {

public:
    KnightProblemSolver();

public:
    // getter/setter
    int getHeight() const { return HEIGHT; } 
    int getWidth() const { return WIDTH; }

    ListSolutions getSolutions();

    // public interface
    int findMovesSequential();
    int findMovesParallel(int maxDepth = 1);  // 0 == seq, >= 1 par
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
    KnightProblemBoard<HEIGHT, WIDTH> m_board;        // chess board
    ListSolutions                     m_solutions;    // list of found solutions
    Solution                          m_current;      // solution being in construction
    int                               m_moveNumber;   // number of last knight's move

    static std::mutex                 s_mutex;
};

// ================================================================================
// public interface

template <int HEIGHT, int WIDTH>
KnightProblemSolver<HEIGHT, WIDTH>::KnightProblemSolver() : m_moveNumber{0}  {}

template <int HEIGHT, int WIDTH>
ListSolutions KnightProblemSolver<HEIGHT, WIDTH>::getSolutions() {
    // return m_solutions;
    return { m_solutions };
}

template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::findMovesSequential() {

    // reset data structures
    m_board.clearBoard();
    m_solutions.clear();
    m_current.clear();
    m_moveNumber = 0;

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start{ HEIGHT - 1, 0 };
    log(std::cout, "   ... starting seq solver at ", start);
    int count = findMovesSequential(start);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    log(std::cout, "Elapsed time = ", duration, " [msecs]");

     return static_cast<int> (m_solutions.size());
    //return count;
}

template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::findMovesParallel(int maxDepth)
{
    // reset data structures
    m_board.clearBoard();
    m_solutions.clear();
    m_current.clear();
    m_moveNumber = 0;

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start{ HEIGHT - 1, 0 };
    log(std::cout, "   ... starting par solver at ", start);
    int count = findMovesParallel(start, maxDepth);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    log(std::cout, "Elapsed time = ", duration, " [msecs]");

    // return static_cast<int> (m_solutions.size());
    return count;
}

// ================================================================================
// private interface

// private helper - algorithm to solve the Knight's Tour problem
template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::findMovesSequential(const Coordinate& coord)
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
        for (Coordinate move : nextMoves) {
            findMovesSequential(move);
        }
    }

    unsetKnightMoveAt(coord);
    m_current.pop_back();

    return static_cast<int> (m_solutions.size());
}

template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::findMovesParallel(const Coordinate& coord, int maxDepth) {

    setKnightMoveAt(coord);
    m_current.push_back(coord);

    // determine list of possible next moves
    std::vector<Coordinate> nextMoves = nextKnightMoves(coord);
    std::deque<std::future<int>> futures;

    int result{};

    //for (unsigned int i = 0; i < nextMoves.size(); i++) {

    //    Coordinate nextCoord = nextMoves.at(i);

    //    // make a copy of the solver including the current board
    //    KnightProblemSolver slaveSolver = *this;

    //    if (maxDepth > 0) {

    //        std::future<int> future = std::async(std::launch::async, std::move(slaveSolver), nextCoord, maxDepth - 1);
    //        futures.push_back(std::move(future));

    //    }
    //    else {


    //        slaveSolver.findMovesSequential(nextCoord);
    //        result += slaveSolver.countSolutions();
    //    }
    //}

    for (Coordinate move : nextMoves) {

        // make a copy of the solver including the current board
        KnightProblemSolver slaveSolver = *this;

        if (maxDepth > 0) {
            // do next moves parallel or ...
            std::future<int> future = std::async(std::launch::async, std::move(slaveSolver), move, maxDepth - 1);
            futures.push_back(std::move(future));
        }
        else {
            // ... do next moves sequential
            log(std::cout, "   ... launching seq solver at ", move);
            slaveSolver.findMovesSequential(move);
            result += slaveSolver.countSolutions();

            // need to copy all found solutions from other solver to the current solver
            ListSolutions solutions = slaveSolver.getSolutions();
            log(std::cout, "   ...   calculated solutions FROM ", move, " => ", solutions.size());

            //log(std::cout, "   ...       vorher  (copy): ", m_solutions.size());
            //// std::copy(std::begin(solutions), std::end(solutions), std::back_inserter(m_solutions));
            //m_solutions.insert(std::end(m_solutions), std::begin(solutions), std::end(solutions));
            //log(std::cout, "   ...       nachher (copy): ", m_solutions.size());

            //{
            //    // RAII
            //    std::scoped_lock<std::mutex> lock(s_mutex);
            //    m_solutions.insert(std::end(m_solutions), std::begin(solutions), std::end(solutions));
            //}
        }
    }

    // block async tasks, if any, now and compute final result
    // (just use references to access non-copyable objects)
    for (std::future<int>& future : futures)
    {
        int partialResult = future.get();
        log(std::cout, "   ...   RETRIEVED from future: ", partialResult);

        result += partialResult;
    }

    //int count = static_cast<int>(futures.size());
    //for (int i = 0; i < count; i++)
    //{
    //    std::future<int> future = std::move(futures.front());
    //    futures.pop_front();

    //    int partialResult = future.get();
    //    log(std::cout, "   ...   RETRIEVED from future: ", partialResult);

    //    result += partialResult;
    //}

    unsetKnightMoveAt(coord);
    m_current.pop_back();

    // std::cout << "     parallel ===>  " << result << std::endl;
    return result;
}

// =========================================================================================

// functor notation - needed for std::async
template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::operator()(const Coordinate& coord, int maxDepth) {

    log(std::cout, "   operator() ... launching par solver at ", coord, ", maxDepth = ", maxDepth);

    int count = findMovesParallel(coord, maxDepth);
    return count;
}

// =========================================================================================

template <int HEIGHT, int WIDTH>
int KnightProblemSolver<HEIGHT, WIDTH>::countSolutions() {
    return static_cast<int> (m_solutions.size());
}

// occupy square on the chess board
template <int HEIGHT, int WIDTH>
void KnightProblemSolver<HEIGHT, WIDTH>::setKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber++;
    m_board.at(coord) = m_moveNumber;
}

// release square on the chess board
template <int HEIGHT, int WIDTH>
void KnightProblemSolver<HEIGHT, WIDTH>::unsetKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber--;
    m_board.at(coord) = 0;
}

//  checks, whether coordinate does exist on the chess board
template <int HEIGHT, int WIDTH>
bool KnightProblemSolver<HEIGHT, WIDTH>::inRange(const Coordinate& coord)
{
    return (coord.getRow() >= 0) && (coord.getRow() < HEIGHT) && (coord.getCol() >= 0) && (coord.getCol() < WIDTH);
}

// checks, whether coordinate is valid and is still not taken
template <int HEIGHT, int WIDTH>
bool KnightProblemSolver<HEIGHT, WIDTH>::canMoveTo(const Coordinate& coord)
{
    return inRange(coord) && (m_board.at(coord) <= 0);
}

// verify, whether current list of moves is a solution
template <int HEIGHT, int WIDTH>
bool KnightProblemSolver<HEIGHT, WIDTH>::isSolution()
{
    return m_moveNumber >= HEIGHT * WIDTH;
}

template <int HEIGHT, int WIDTH>
std::vector<Coordinate> KnightProblemSolver<HEIGHT, WIDTH>::nextKnightMoves(const Coordinate& coord)
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

template <int HEIGHT, int WIDTH>
std::mutex KnightProblemSolver<HEIGHT, WIDTH>::s_mutex;

// =====================================================================================
// End-of-File
// =====================================================================================

