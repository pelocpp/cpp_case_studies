#include <windows.h>
#include <iostream>
#include <array> 
#include <queue> 
#include <thread> 
#include <chrono>
#include <future>
#include <cassert>

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

#include "ITetrimino.h"
#include "Tetrimino.h"
#include "Tetrimino_L.h"

#include "TetrisAction.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

Tetrimino_L::Tetrimino_L(ITetrisBoard* board) : Tetrimino(board, CellColor::Ocker) {}

// predicates
bool Tetrimino_L::canSetToTop() {
    
    assert(m_rotation == RotationAngle::Degrees_0);

    return !(m_board->getCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
        m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used);
}

bool Tetrimino_L::canMoveLeft() { return true; }

bool Tetrimino_L::canMoveRight() { return true; }

bool Tetrimino_L::canMoveDown() { 

    RotationAngle rotation = m_rotation;

    switch (rotation) {
    case RotationAngle::Degrees_0:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;


    case RotationAngle::Degrees_90:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_180:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 2)
            return false;
        if (m_board->getCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 2, m_anchorPoint.getX()).getState() == CellState::Used)
            return false;
        break;

    case RotationAngle::Degrees_270:
        if (m_anchorPoint.getY() >= m_board->getNumRows() - 1)
            return false;
        if (m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX()).getState() == CellState::Used ||
            m_board->getCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1).getState() == CellState::Used)
            return false;
        break;
    }

    return true;
}

bool Tetrimino_L::canRotate() { return true; }

bool Tetrimino_L::isCoordinateWithin(int row, int col) { return true; }

void Tetrimino_L::update(CellState state) {

    CellColor color = (state == CellState::Free) ? CellColor::LightGray : m_color;
    TetrisCell cell (state, color);

    // update model
    if (m_rotation == RotationAngle::Degrees_0) {

        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() + 1, cell);
    }
    else if (m_rotation == RotationAngle::Degrees_90) {
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1, cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX() - 1, cell);
    }
    else if (m_rotation == RotationAngle::Degrees_180) {
        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() - 1, cell);
        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY() + 1, m_anchorPoint.getX(), cell);
    }
    else if (m_rotation == RotationAngle::Degrees_270) {
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() - 1, cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX(), cell);
        m_board->setCell(m_anchorPoint.getY(), m_anchorPoint.getX() + 1, cell);
        m_board->setCell(m_anchorPoint.getY() - 1, m_anchorPoint.getX() + 1, cell);
    }
}

void Tetrimino_L::updateCellList(ViewCellList& list, const CellColor& color) {

    // update cell list
    if (m_rotation == RotationAngle::Degrees_0) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY() + 1), color));
    }
    else if (m_rotation == RotationAngle::Degrees_90) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY() + 1), color));
    }
    else if (m_rotation == RotationAngle::Degrees_180) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY() - 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 1), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1), color));
    }
    else if (m_rotation == RotationAngle::Degrees_270) {
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() - 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY()), color));
        list.add(ViewCell(CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY() - 1), color));
    }
}