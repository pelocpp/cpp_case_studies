#include <windows.h>
#include <iostream>
#include <array> 
#include <vector> 
#include <map> 
#include <queue> 
#include <thread> 
#include <chrono>
#include <future>
#include <functional>

#include "Globals.h"
#include "Direction.h"
#include "RotationAngle.h"

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

#include "ITetromino.h"
#include "Tetromino.h"

#include "TetrisState.h"
#include "TetrisAction.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

// c'tor
Tetromino::Tetromino(ITetrisBoard* board, CellColor color) : m_board(board), m_color(color), m_anchorPoint{ 5, 2 } {
    m_rotation = RotationAngle::Degrees_0;
}

// protected interface
void Tetromino::moveAnchorLeft() {
    m_anchorPoint.moveLeft();
}

void Tetromino::moveAnchorRight() {
    m_anchorPoint.moveRight();
}

void Tetromino::moveAnchorDown() {
    m_anchorPoint.moveDown();
}

void Tetromino::rotateAnchor() {
    if (m_rotation == RotationAngle::Degrees_0) {
        m_rotation = RotationAngle::Degrees_90;
    }
    else if (m_rotation == RotationAngle::Degrees_90) {
        m_rotation = RotationAngle::Degrees_180;
    }
    else if (m_rotation == RotationAngle::Degrees_180) {
        m_rotation = RotationAngle::Degrees_270;
    }
    else if (m_rotation == RotationAngle::Degrees_270) {
        m_rotation = RotationAngle::Degrees_0;
    }
}

// public interface (movement specific methods)
void Tetromino::setToTop() {
    set();
    ViewCellList list;
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetromino::moveRight() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorRight();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetromino::moveLeft() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorLeft();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetromino::moveDown() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorDown();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetromino::rotate() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    rotateAnchor();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}


// board specific methods
void Tetromino::set() {
    update(CellState::Used);
}

void Tetromino::release() {
    update(CellState::Free);
}
