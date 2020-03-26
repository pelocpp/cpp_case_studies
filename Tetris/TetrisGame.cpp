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

void TetrisGame::init() {

    // TODO: Komme nicht direkt an das BOARD heran ... also ein Umweg ?!?!
    // TODO: In einer Redesign-Phase klären, ob das so bleibt ?!?!?!

    m_model->attach(this);
    
    // TODO: Wo ist das detach ????
}

void TetrisGame::start() {

    m_model->start();
}

void TetrisGame::join() {

    m_model->join();
}

void TetrisGame::update(const ViewCellList& list) {

    // TODO: OutputDebugString hier einbauen .....

    char szBuf[128];
    wsprintf(szBuf, "Yeahhhhhhhhhh TetrisGame::update ==> Length of List: %d\n", list.size());
    ::OutputDebugString(szBuf);
}