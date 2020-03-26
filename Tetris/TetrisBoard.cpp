#include <iostream>
#include <array>
#include <vector>
#include <list>

#include "Globals.h"

#include "CellColor.h"
#include "CellPoint.h"
#include "CellState.h"
#include "ViewCell.h"
#include "ViewCellList.h"
#include "TetrisCell.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

//c'tors
TetrisBoard::TetrisBoard(int rows, int cols) : m_numRows(rows), m_numCols(cols) {}

// getter/setter
int TetrisBoard::getNumRows() {
    return m_numRows;
}

int TetrisBoard::getNumColumns() {
    return m_numCols;
}

TetrisCell TetrisBoard::getCell(int row, int col) {
    return m_board[row][col];
}

void TetrisBoard::setCell(int row, int col, const TetrisCell& cell) {
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

    // update view
    ViewCellList list;

    // TODO: mit Iteratoren schreiben !!!

    // TODO: Klasse CellColor: DA M�SSEN SINGLETONS HIN !!!!!
    // TODO: Beachten: Die Klasse sollte dann immutable sein 

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numCols; j++) {
            ViewCell cell (CellColor::LightGray, CellPoint(j, i));
            list.add(cell);
        }
    }

    notifyAll(list);
}


// implementation of interface 'ITetrisBoardListener'
void TetrisBoard::attach(ITetrisBoardObserver* observer) {
    m_observer.push_back(observer);
}

void TetrisBoard::detach(ITetrisBoardObserver* observer) {
    // TODO: Wie war das mit erase und remove
    m_observer.remove(observer);
}

void TetrisBoard::notifyAll(const ViewCellList& list) {
    for (auto observer : m_observer) {
        observer->update(list);
    }
}