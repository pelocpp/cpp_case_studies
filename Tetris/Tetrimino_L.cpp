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
#include "CellState.h"
#include "CellPoint.h"
#include "TetrisCell.h"

#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetrimino.h"
#include "Tetrimino.h"
#include "Tetrimino_L.h"

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

Tetrimino_L::Tetrimino_L(ITetrisBoard* board) : Tetrimino(board, CellColor::Ocker) {


}

// predicates
bool Tetrimino_L::canSetToTop() { return false; }

bool Tetrimino_L::canMoveLeft() { return false; }

bool Tetrimino_L::canMoveRight() { return false; }

bool Tetrimino_L::canMoveDown() { return false; }

bool Tetrimino_L::canRotate() { return false; }

bool Tetrimino_L::isCoordinateWithin(int row, int col) { return false; }

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
