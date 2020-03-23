#include <iostream>
#include <array>

#include "Globals.h"

#include "CellColor.h"
#include "CellState.h"
#include "TetrisCell.h"
#include "ITetrisBoard.h"
#include "TetrisBoard.h"

//c'tors
TetrisBoard::TetrisBoard(int rows, int cols) : m_numRows(rows), m_numCols(cols) {}

// properties
TetrisCell TetrisBoard::getCell(int row, int col) {
    return m_board[row][col];
}

void TetrisBoard::setCell(int row, int col, TetrisCell cell) {
    m_board[row][col] = cell;
}

// public interface
void TetrisBoard::clear() {
    // reset internal state of board
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numCols; j++) {
            m_board[i][j].setColor(CellColor::LightGray);
            m_board[i][j].setState(CellState::Free);
        }
    }
}

