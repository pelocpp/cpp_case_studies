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

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

Tetrimino::Tetrimino(ITetrisBoard* board, CellColor color) : m_board(board) {

    m_rotation= RotationAngle::Degrees_0;
    m_color = CellColor::LightGray;
}

// public interface (movement specific methods)
void Tetrimino::setToTop() {
    set();
    
    // WEITER !!!
 /*   ViewCellList list = new ViewCellList();
    this.UpdateModifiedCellList(list, this.color);
    this.board.PostChanges(list);*/
}

void Tetrimino::MoveLeft() {}

void Tetrimino::MoveRight() {}

bool Tetrimino::MoveDown() { return false;  }

void Tetrimino::Rotate() {}


// board specific methods
void Tetrimino::set() {
    update(CellState::Used);
}

void Tetrimino::release() {
    update(CellState::Free);
}
