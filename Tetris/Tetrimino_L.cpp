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
#include "Tetrimino_L.h"

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

Tetrimino_L::Tetrimino_L(ITetrisBoard* board) : Tetrimino(board, CellColor::Ocker) {

    // m_anchorPoint = CellPoint(5, 2);
    m_anchorPoint.setX(5);
    m_anchorPoint.setY(2);
}

// predicates
bool Tetrimino_L::canSetToTop() { return true; }

bool Tetrimino_L::canMoveLeft() { return true; }

bool Tetrimino_L::canMoveRight() { return true; }

bool Tetrimino_L::canMoveDown() { return true; }

bool Tetrimino_L::canRotate() { return true; }

bool Tetrimino_L::isCoordinateWithin(int row, int col) { return true; }

void Tetrimino_L::update(CellState state) {

    CellColor color = (state == CellState::Free) ? CellColor::LightGray : m_color;

    TetrisCell cell (state, color);

    ::OutputDebugString("(4a) >> update\n");

    // update model
    if (m_rotation == RotationAngle::Degrees_0) {

        // TODO: Fehler gefunden -- das kann wieder weg ...

        //int xxx = m_anchorPoint.getY() - 1;
        //int yyy = m_anchorPoint.getX();

        //char szBuf[128];
        //wsprintf(szBuf, "X = %d, Y = %d\n", xxx, yyy);
        //::OutputDebugString(szBuf);

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

    ::OutputDebugString("(4b) << update\n");
}


void Tetrimino_L::updateCellList(ViewCellList& list, const CellColor& color) {

    // update cell list
    if (m_rotation == RotationAngle::Degrees_0) {
        list.add(ViewCell(color, CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() - 1)));
        list.add(ViewCell(color, CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY())));
        list.add(ViewCell(color, CellPoint(m_anchorPoint.getX(), m_anchorPoint.getY() + 1)));
        list.add(ViewCell(color, CellPoint(m_anchorPoint.getX() + 1, m_anchorPoint.getY() + 1)));
    }
    //else if (m_rotation == RotationAngle::Degrees_90) {
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() - 1, this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX(), this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() + 1, this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() - 1, this.anchorPoint.getY() + 1)));
    //}
    //else if (m_rotation == RotationAngle::Degrees_180) {
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() - 1, this.anchorPoint.getY() - 1)));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX(), this.anchorPoint.getY() - 1)));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX(), this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX(), this.anchorPoint.getY() + 1)));
    //}
    //else if (m_rotation == RotationAngle::Degrees_270) {
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() - 1, this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX(), this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() + 1, this.anchorPoint.getY())));
    //    list.Add(new ViewCell(color, new CellPoint(this.anchorPoint.getX() + 1, this.anchorPoint.getY() - 1)));
    //}
}