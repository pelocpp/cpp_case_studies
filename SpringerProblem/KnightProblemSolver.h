#pragma once

using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;

const int Rows = 5;
const int Cols = 5;

using GameBoard = std::array<std::array<int, Cols>, Rows>;

class KnightProblemSolver {

public:
    KnightProblemSolver();
    KnightProblemSolver(int rows, int cols);
    KnightProblemSolver(KnightProblemSolver* parent);  //  TODO: Evtl. geht auch Referenz oder copy c'tor

public:
    // getter/setter
    int getHeight() const { return m_height; }
    int getWidth() const { return m_width; }
    int setHeight(int rows) { m_height = rows; }
    int setWidth(int cols) { m_width = cols; }

    ListSolutions getSolutions();

    // public interface
    void findMovesSequential();
    void findMovesParallel();

private:
    // internal helper methods
    void clearBoard();
    void verifyCoordinate(const Coordinate& coord) const;
    int& at(const Coordinate& coord);
    const int& at(const Coordinate& coord) const;
    void setKnightMoveAt(const Coordinate& coord);
    void unsetKnightMoveAt(const Coordinate& coord);
    bool inRange(const Coordinate& coord);
    bool canMoveTo(const Coordinate& coord);
    bool isSolution();
    std::vector<Coordinate> nextKnightMoves(const Coordinate& coord);

    void findMovesSequential(const Coordinate& coord);
    void findMovesParallel(const Coordinate& coord);

private:
    int                 m_height;      // height of board
    int                 m_width;       // width of board
    GameBoard           m_board;       // chess board
    ListSolutions       m_solutions;   // list of found solutions
    Solution            m_current;     // solution being in construction
    int                 m_moveNumber;  // number of last knight's move

    // threading utils
    static std::mutex   m_mutex;        // concurrent access protection
};
