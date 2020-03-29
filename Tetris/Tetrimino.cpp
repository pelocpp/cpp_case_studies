#include <windows.h>
#include <iostream>
#include <array> 
#include <queue> 
#include <thread> 
#include <chrono>
#include <future>

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

#include "ITetrimino.h"
#include "Tetrimino.h"

#include "TetrisAction.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

Tetrimino::Tetrimino(ITetrisBoard* board, CellColor color) : m_board(board), m_color(color), m_anchorPoint{ 5, 2 } {

    m_rotation = RotationAngle::Degrees_0;
}

void Tetrimino::moveAnchorLeft() {
    m_anchorPoint.moveLeft();
}

void Tetrimino::moveAnchorRight() {
    m_anchorPoint.moveRight();
}

void Tetrimino::moveAnchorDown() {
    m_anchorPoint.moveDown();
}


// public interface (movement specific methods)
void Tetrimino::setToTop() {
    set();
    ViewCellList list;
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetrimino::moveRight() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorRight();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetrimino::moveLeft() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorLeft();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetrimino::moveDown() {

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorDown();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetrimino::Rotate() {}


// board specific methods
void Tetrimino::set() {
    update(CellState::Used);
}

void Tetrimino::release() {
    update(CellState::Free);
}
