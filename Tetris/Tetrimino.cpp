#include <windows.h>
#include <iostream>
#include <array> 
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

#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetrimino.h"
#include "Tetrimino.h"

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

Tetrimino::Tetrimino(ITetrisBoard* board, CellColor color) : m_board(board), m_color(color) {

    m_rotation = RotationAngle::Degrees_0;
}

void Tetrimino::moveAnchorLeft() {
    m_anchorPoint.setX(m_anchorPoint.getX() - 1);
}

void Tetrimino::moveAnchorRight() {
    m_anchorPoint.setX(m_anchorPoint.getX() + 1);
}

void Tetrimino::moveAnchorDown() {
    m_anchorPoint.setY(m_anchorPoint.getY() + 1);
}




// public interface (movement specific methods)
void Tetrimino::setToTop() {
    set();
    
    ViewCellList list;

    updateCellList(list, m_color);
    m_board->notifyAll(list);
}

void Tetrimino::moveLeft() {}

void Tetrimino::moveRight() {}

bool Tetrimino::moveDown() {
    if (!canMoveDown())
        return false;

    ViewCellList list;
    release();
    updateCellList(list, CellColor::LightGray);
    moveAnchorDown();
    set();
    updateCellList(list, m_color);
    m_board->notifyAll(list);

    return true;
}

void Tetrimino::Rotate() {}


// board specific methods
void Tetrimino::set() {
    update(CellState::Used);
}

void Tetrimino::release() {
    update(CellState::Free);
}
