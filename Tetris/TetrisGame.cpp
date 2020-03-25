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

TetrisGame::TetrisGame() {
    m_subsystem = new ConsoleSubsystem(Cols, Rows);
    m_subsystem->initConsole();
    m_subsystem->showConsole();

    m_model = new TetrisModel();
}

TetrisGame::~TetrisGame() {
    delete m_model;
    delete m_subsystem;
}

void TetrisGame::play() {

    m_model->play();
}
