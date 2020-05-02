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
#include "Tetromino_I.h"

#include "TetrisState.h"
#include "TetrisAction.h"
#include "TetrisQueue.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

Tetromino_I::Tetromino_I(ITetrisBoard* board) : Tetromino(board, CellColor::Cyan) {}

// predicates
bool Tetromino_I::canSetToTop() {
    assert(m_rotation == RotationAngle::Degrees_0);

    return !(m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 2).getState() == CellState::Used);
}

bool Tetromino_I::canMoveLeft() {
    // check fields to the left of the tetrimino
    switch (m_rotation) {
    case RotationAngle::Degrees_0:
        if (m_anchorPoint.getX() == 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 2).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_90:
        if (m_anchorPoint.getX() == 0)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX() - 1).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_180:
        if (m_anchorPoint.getX() == 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 3).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_270:
        if (m_anchorPoint.getX() == 0)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 2, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used)
            return false;
        break;
    }

    return true;
}

bool Tetromino_I::canMoveRight() {
    // check fields to the left of the tetrimino
    switch (m_rotation) {
    case RotationAngle::Degrees_0:
        if (m_anchorPoint.getX() == m_board->getNumColumns() - 3)
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 3).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_90:
        if (m_anchorPoint.getX() == m_board->getNumColumns() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_180:
        if (m_anchorPoint.getX() == m_board->getNumColumns() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 2).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_270:
        if (m_anchorPoint.getX() == m_board->getNumColumns() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 2, m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;
    }

    return true;
}

bool Tetromino_I::canMoveDown() {

    // check for bottom line & check fields below tetrimino
    switch (m_rotation) {
    case RotationAngle::Degrees_0:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 2).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_90:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 3)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 3, m_anchorPoint.getX()).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_180:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 2).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_270:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX()).getState() == CellState::Used)
            return false;
        break;
    }

    return true;
}

bool Tetromino_I::canRotate() {

    switch (m_rotation) {
    case RotationAngle::Degrees_0:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX()).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_90:
        if ((m_anchorPoint.getX() < 2) || (m_anchorPoint.getX() >= m_board->getNumColumns() - 1))
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 2).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_180:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() - 2, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_270:
        if ((m_anchorPoint.getX() < 1) || (m_anchorPoint.getX() >= m_board->getNumColumns() - 2))
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 2).getState() == CellState::Used)
            return false;
        break;
    }

    return true;
}

bool Tetromino_I::isCoordinateWithin(int row, int col) { return true; }

void Tetromino_I::update(CellState state) {

    CellColor color = (state == CellState::Free) ? CellColor::LightGray : m_color;
    TetrisCell cell(state, color);

    // update model
    if (m_rotation == RotationAngle::Degrees_0) {
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 2, cell);
    }
    else if (m_rotation == RotationAngle::Degrees_90) {
        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX(), cell);
    }
    else if (m_rotation == RotationAngle::Degrees_180) {
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 2, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1, cell);
    }
    else if (m_rotation == RotationAngle::Degrees_270) {
        m_board->setCell(m_anchorPoint.getY() - 2, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX(), cell);
    }
}

void Tetromino_I::updateCellList(ViewCellList& list, const CellColor& color) {
    // update cell list
    if (m_rotation == RotationAngle::Degrees_0) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 2, m_anchorPoint.getY()), color));
    }
    else if (m_rotation == RotationAngle::Degrees_90) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 2), color));
    }
    else if (m_rotation == RotationAngle::Degrees_180) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 2, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY()), color));
    }
    else if (m_rotation == RotationAngle::Degrees_270) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 2), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1), color));
    }
}
