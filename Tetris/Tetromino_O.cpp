#include <windows.h>
#include <iostream>
#include <array> 
#include <vector> 
#include <map> 
#include <queue> 
#include <thread> 
#include <chrono>
#include <future>
#include <cassert>
#include <functional>

#include "Globals.h"
#include "Direction.h"
#include "RotationAngle.h"

#include "CellColor.h"
#include "CellState.h"
#include "CellPoint.h"
#include "ViewCell.h"
#include "ViewCellList.h"
#include "TetrisCell.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetromino.h"
#include "Tetromino.h"
#include "Tetromino_O.h"

#include "TetrisState.h"
#include "TetrisAction.h" 
#include "ITetrisModel.h"
#include "TetrisModel.h"

Tetromino_O::Tetromino_O(ITetrisBoard* board) : Tetromino(board, CellColor::Yellow) {}

// predicates
bool Tetromino_O::canSetToTop() {
    assert(m_rotation == RotationAngle::Degrees_0);

    return !(m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used);
}

bool Tetromino_O::canMoveLeft() {

    if (m_anchorPoint.getX() == 0)
        return false;
    if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used)
        return false;

    return true;
}

bool Tetromino_O::canMoveRight() {

    if (m_anchorPoint.getX() >= m_board->getNumColumns() - 2)
        return false;
    if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 2).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 2).getState() == CellState::Used)
        return false;

    return true;
}

bool Tetromino_O::canMoveDown() {

    if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
        return false;
    if (m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX() + 1).getState() == CellState::Used)
        return false;

    return true;
}

bool Tetromino_O::canRotate() {
    return true;
}

bool Tetromino_O::isCoordinateWithin(int row, int col) { return true; }

void Tetromino_O::update(CellState state) {

    CellColor color = (state == CellState::Free) ? CellColor::LightGray : m_color;
    TetrisCell cell(state, color);

    // update model
    m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
    m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1, cell);
    m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX(), cell);
    m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1, cell);
}

void Tetromino_O::updateCellList(ViewCellList& list, const CellColor& color) {
    // update cell list
    list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
    list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY()), color));
    list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1), color));
    list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY() + 1), color));
}
