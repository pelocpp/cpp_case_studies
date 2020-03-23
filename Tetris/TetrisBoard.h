#pragma once

class TetrisBoard : public ITetrisBoard {
public:

    //c'tors
    TetrisBoard(int rows, int cols);

    // properties
    TetrisCell getCell(int row, int col) override;
    void setCell(int row, int col, TetrisCell cell) override;

    // public interface
    void clear() override;

private:
    int m_numRows;
    int m_numCols;

    std::array<std::array<TetrisCell, Cols>, Rows> m_board;
};
