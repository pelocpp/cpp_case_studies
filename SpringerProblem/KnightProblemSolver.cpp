#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <mutex>
#include <future>
#include <chrono>

#include "Coordinate.h"
#include "KnightProblemSolver.h"

std::mutex  KnightProblemSolver::m_mutex;

KnightProblemSolver::KnightProblemSolver() : KnightProblemSolver(8, 8) {}

KnightProblemSolver::KnightProblemSolver(int height, int width) {

    m_height = height;
    m_width = width;
    m_moveNumber = 0;

    clearBoard();
}

KnightProblemSolver::KnightProblemSolver(KnightProblemSolver* parent)
 {
    m_height = parent->m_height;
    m_width = parent->m_width;

    // need copy of original chess board (!)
    m_board = parent->m_board;

    // need copy of solution being in construction
    m_current = parent->m_current;

    // need *empty* list of solutions
    m_solutions.clear();

    m_moveNumber = parent->m_moveNumber;
}



void KnightProblemSolver::clearBoard() {
    for (unsigned int i = 0; i < m_board.size(); i++) {
        m_board[i].fill(0);
    }
}

ListSolutions KnightProblemSolver::getSolutions() {
    return ListSolutions{ m_solutions }; // return a copy 
}

void KnightProblemSolver::verifyCoordinate(const Coordinate& coord) const {
    if (coord.getRow() >= m_height || coord.getCol() >= m_width) {
        throw std::range_error("");
    }
}

int& KnightProblemSolver::at(const Coordinate& coord) {
  //  verifyCoordinate(coord);
    return m_board[coord.getCol()][coord.getRow()];
}

const int& KnightProblemSolver::at(const Coordinate& coord) const {
  //  verifyCoordinate(coord);
    return m_board[coord.getCol()][coord.getRow()];
}

void KnightProblemSolver::findMovesSequential() {
    // reset data structures

    // TODO: DAs geht doch nur zum ersten Mal ... danach muss halt irgendwie überall 0 rein ?!?!?!?

    // TODO: Das ist jetzt erst mal altes Zeugs ... muss das wirklich da rein ?!?!?!?

    //m_board.resize(m_width);
    //for (std::vector<int>& column : m_board) {
    //    column.resize(m_height);
    //}

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
}

void KnightProblemSolver::findMovesParallel() {
    m_current.clear();
    m_moveNumber = 0;
    m_solutions.clear();

    // start at lower left corner            
    Coordinate start{ m_height - 1, 0 };
    findMovesParallel(start);
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

// private helper - algorithm to solve the Knight's Tour problem
// using an parallel approach
void KnightProblemSolver::findMovesParallel(const Coordinate& coord) {

    setKnightMoveAt(coord);
    m_current.push_back(coord);

    if (isSolution()) {
        // need a copy of the current solution
        Solution copy{ m_current };

        // add found solution *thread safe* to the list of all solutions
        std::scoped_lock<std::mutex> lock(m_mutex);
        m_solutions.push_back(copy);
    }
    else {
        // determine list of possible next moves
        std::vector<Coordinate> nextMoves = nextKnightMoves(coord);

        for (unsigned int i = 0; i < nextMoves.size(); i++) {

            Coordinate c = nextMoves.at(i);

            KnightProblemSolver slaveSolver (this);

            auto f = std::async(static_cast<void(KnightProblemSolver::*)(const Coordinate&)>  ( &KnightProblemSolver::findMovesSequential), &slaveSolver, c);
            f.get();   // DAS IST SYNCHRON ; ICH WEIß

            std::cout << "FOUND: " << slaveSolver.getSolutions().size() << std::endl;
        }
    }

    unsetKnightMoveAt(coord);
    m_current.pop_back();
}



// occupy square on the chess board
void KnightProblemSolver::setKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber++;
    at(coord) = m_moveNumber;
}

// release square on the chess board
void KnightProblemSolver::unsetKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber--;
    at(coord) = 0;
}

//  checks, whether coordinate does exist on the chess board
bool KnightProblemSolver::inRange(const Coordinate& coord)
{
    return (coord.getRow() >= 0) && (coord.getRow() < m_height) && (coord.getCol() >= 0) && (coord.getCol() < m_width);
}

// checks, whether coordinate is valid and is still not taken
bool KnightProblemSolver::canMoveTo(const Coordinate& coord)
{
    return inRange(coord) && (at(coord) <= 0);
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