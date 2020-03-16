#pragma once


using GameBoard = std::vector<std::vector<int>>;

class KnightProblemSolver {

public:
    KnightProblemSolver();
    KnightProblemSolver(int rows, int cols);

public:
    // getter/setter
    int getHeight() const { return m_height; }
    int getWidth() const { return m_width; }
    int setHeight(int rows) { m_height = rows; }
    int setWidth(int cols) { m_width = cols; }

    ListSolutions getSolutions();

    // public interface
    void findMovesSequential();

private:
    // internal helper methods
    void verifyCoordinate(size_t col, size_t row) const;
    int& at(size_t row, size_t col);
    const int& at(size_t row, size_t col) const;

    void findMovesSequential(const Coordinate& coord);
    void setKnightMoveAt(const Coordinate& coord);
    void unsetKnightMoveAt(const Coordinate& coord);
    bool inRange(int row, int col);
    bool canMoveTo(int row, int col);
    bool isSolution();
    std::vector<Coordinate> NextKnightMoves(const Coordinate& coord);

private:
    size_t         m_height;      // height of board
    size_t         m_width;       // width of board
    GameBoard      m_board;       // chess board
    ListSolutions  m_solutions;   // list of found solutions
    Solution       m_current;     // solution being in construction
    int            m_moveNumber;  // number of last knight's move
};

