#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>

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
    TetrisCell empty;
    std::for_each(
        std::begin(m_board), 
        std::end(m_board),
        [=] (std::array<TetrisCell, Cols> row) {
            row.fill(empty);
        }
    );

    // TODO: mit Iteratoren schreiben !!!

    // TODO: Klasse CellColor: DA MÜSSEN SINGLETONS HIN !!!!!

    // TODO: Beachten: Die Klasse sollte dann immutable sein 

    // update view

    ViewCellList list;
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numCols; j++) {
            ViewCell cell (CellPoint(j, i), CellColor::LightGray);
            list.add(cell);
        }
    }
    notifyAll(list);
}

bool TetrisBoard::isBottomRowComplete() {
    bool isComplete = true;
    for (int j = 0; j < m_numCols; j++) {
        if (m_board[m_numRows - 1][j].getState() != CellState::Used) {
            isComplete = false;
            break;
        }
    }

    return isComplete;
}

void TetrisBoard::moveNonEmptyRowsDown() {
    int startRow = m_numRows - 1;
    while (!isRowEmpty(startRow))
        startRow--;

    ViewCellList list;
    for (int i = m_numRows - 2; i >= startRow; i--) {
        copySingleRow(list, i);
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

// private helper methods
bool TetrisBoard::isRowEmpty(int i) {
    bool isEmpty = true;
    for (int j = 0; j < m_numCols; j++) {
        if (m_board[i][j].getState() == CellState::Used) {
            isEmpty = false;
            break;
        }
    }

    return isEmpty;
}

void TetrisBoard::copySingleRow(ViewCellList& list, int row) {

    for (int j = 0; j < m_numCols; j++) {
        // create cell to update any view
        CellColor color{ m_board[row][j].getColor() };
        CellPoint point{ j, row + 1 };
        ViewCell cell{ point, color };
        list.add(cell);

        // Finally copy block one row down ...
        // Note: TetrisCell is a 'value type', so '=' works fine ---
        // in case of a reference type: clone needed (deep copy) !!!
        m_board[row + 1][j] = m_board[row][j];
    }
}
