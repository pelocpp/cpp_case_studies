#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>

#include "Coordinate.h"
#include "KnightProblemSolver.h"

KnightProblemSolver::KnightProblemSolver() : KnightProblemSolver(8, 8) {}

KnightProblemSolver::KnightProblemSolver(int height, int width) {

    m_height = height;
    m_width = width;
    m_moveNumber = 0;
}

ListSolutions KnightProblemSolver::getSolutions() {
    // return a copy 
    return ListSolutions(m_solutions);
}

void KnightProblemSolver::verifyCoordinate(size_t col, size_t row) const {
    if (row >= m_height || col >= m_width) {
        throw std::range_error("");
    }
}

int& KnightProblemSolver::at(size_t row, size_t col) {
    verifyCoordinate(col, row);
    return m_board[col][row];
}

const int& KnightProblemSolver::at(size_t row, size_t col) const {
    verifyCoordinate(col, row);
    return m_board[col][row];
}

void KnightProblemSolver::findMovesSequential() {
    // reset data structures

    // TODO: DAs geht doch nur zum ersten Mal ... danach muss halt irgendwie überall 0 rein ?!?!?!?

    m_board.resize(m_width);
    for (std::vector<int>& column : m_board) {
        column.resize(m_height);
    }

    m_current.clear();

    // stopwatch
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // start at lower left corner            
    Coordinate start = Coordinate(m_height - 1, 0);
    findMovesSequential(start);

    // stopwatch
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "[Value] Elapsed time in milliseconds = " << duration << "[microsecs]" << std::endl;

    m_moveNumber = 0;
}

// private helper - algorithm to solve the Knight's Tour problem
void KnightProblemSolver::findMovesSequential(const Coordinate& coord)
{
    setKnightMoveAt(coord);
    m_current.push_back(coord);

    if (isSolution())
    {
        // need a copy of the current solution
        // List<Coordinate> copy = new List<Coordinate>(current);
        Solution copy(m_current);

        // add found solution to the list of all solutions
        m_solutions.push_back(copy);
    }
    else
    {
        // determine list of possible next moves
        std::vector<Coordinate> nextMoves = NextKnightMoves(coord);

        // do next moves sequential
        for (Coordinate coord : nextMoves) {
            findMovesSequential(coord);
        }
    }

    unsetKnightMoveAt(coord);
    m_current.pop_back();
}

// occupy square on the chess board
void KnightProblemSolver::setKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber++;
    at(coord.getRow(), coord.getCol()) = m_moveNumber;
}

// release square on the chess board
void KnightProblemSolver::unsetKnightMoveAt(const Coordinate& coord)
{
    m_moveNumber--;
    at(coord.getRow(), coord.getCol()) = 0;
}

// checks, whether coordinate does exist on the chess board
bool KnightProblemSolver::inRange(int row, int col)
{
    return (row >= 0) && (row < m_height) && (col >= 0) && (col < m_width);
}

// checks, whether coordinate is valid and is still not taken
bool KnightProblemSolver::canMoveTo(int row, int col)
{
    return inRange(row, col) && (at(row, col) <= 0);
}

// verify, whether current list of moves is a solution
bool KnightProblemSolver::isSolution()
{
    return m_moveNumber >= m_height * m_width;
}

std::vector<Coordinate> KnightProblemSolver::NextKnightMoves(const Coordinate& coord)
{
    std::vector<Coordinate> result;

    if (canMoveTo(coord.getRow() + 2, coord.getCol() + 1))
    {
        result.push_back(Coordinate(coord.getRow() + 2, coord.getCol() + 1));
    }
    if (canMoveTo(coord.getRow() + 1, coord.getCol() + 2))
    {
        result.push_back(Coordinate(coord.getRow() + 1, coord.getCol() + 2));
    }
    if (canMoveTo(coord.getRow() - 2, coord.getCol() + 1))
    {
        result.push_back(Coordinate(coord.getRow() - 2, coord.getCol() + 1));
    }
    if (canMoveTo(coord.getRow() - 1, coord.getCol() + 2))
    {
        result.push_back(Coordinate(coord.getRow() - 1, coord.getCol() + 2));
    }
    if (canMoveTo(coord.getRow() + 2, coord.getCol() - 1))
    {
        result.push_back(Coordinate(coord.getRow() + 2, coord.getCol() - 1));
    }
    if (canMoveTo(coord.getRow() + 1, coord.getCol() - 2))
    {
        result.push_back(Coordinate(coord.getRow() + 1, coord.getCol() - 2));
    }
    if (canMoveTo(coord.getRow() - 2, coord.getCol() - 1))
    {
        result.push_back(Coordinate(coord.getRow() - 2, coord.getCol() - 1));
    }
    if (canMoveTo(coord.getRow() - 1, coord.getCol() - 2))
    {
        result.push_back(Coordinate(coord.getRow() - 1, coord.getCol() - 2));
    }

    return result;
}
