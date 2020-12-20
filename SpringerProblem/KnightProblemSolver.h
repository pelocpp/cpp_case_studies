#pragma once

using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;

const int Rows = 6;
const int Cols = 6;

//using GameBoard = std::array<std::array<int, Cols>, Rows>;

class KnightProblemSolver {

public:
    KnightProblemSolver();
    KnightProblemSolver(int rows, int cols);  // PeLO TODO: Das muss mit der Schablone verschwinden !!!

public:
    // getter/setter
    int getHeight() const { return m_height; }    // PeLO TODO: Das muss mit der Schablone verschwinden !!!
    int getWidth() const { return m_width; }      // PeLO TODO: Das muss mit der Schablone verschwinden !!!
    int setHeight(int rows) { m_height = rows; }  // PeLO TODO: Das muss mit der Schablone verschwinden !!!
    int setWidth(int cols) { m_width = cols; }     // PeLO TODO: Das muss mit der Schablone verschwinden !!!

    ListSolutions getSolutions();

    // public interface
    int findMovesSequential();
    int findMovesParallel();
    int findMovesParallel(int maxDepth);
    int operator()(const Coordinate& coord, int maxDepth);

    int countSolutions();

private:
    // internal helper methods

    void clearBoard();  // TODO : klären, wie der implementiert wird !!!!!!!!!!!

   // void verifyCoordinate(const Coordinate& coord) const;
    //int& at(const Coordinate& coord);
    //const int& at(const Coordinate& coord) const;

    // void setBoard(std::unique_ptr<KnightProblemBoard<Rows, Cols>> board);

    void setKnightMoveAt(const Coordinate& coord);
    void unsetKnightMoveAt(const Coordinate& coord);
    bool inRange(const Coordinate& coord);
    bool canMoveTo(const Coordinate& coord);
    bool isSolution();
    std::vector<Coordinate> nextKnightMoves(const Coordinate& coord);

    void findMovesSequential(const Coordinate& coord);
    int findMovesParallel(const Coordinate& coord, int maxDepth);

private:
    int                            m_height;      // height of board
    int                            m_width;       // width of board
   // GameBoard                    m_board;       // chess board


    KnightProblemBoard<Rows, Cols> m_board;       // chess board
    
    ListSolutions                  m_solutions;   // list of found solutions
    Solution                       m_current;     // solution being in construction
    int                            m_moveNumber;  // number of last knight's move

    // threading utils
    static std::mutex   m_mutex;        // concurrent access protection
};
