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

    // TODO: die list mit einem Iterator durchlaufen ...
    for (int i = 0; i < list.size(); i++) {

        ViewCell cell = list.at(i);

        CellColor color = cell.getColor();
        CellPoint point = cell.getPoint();

        unsigned int win32Col = toWin32Color(color);
        COORD coord{ static_cast<short>(point.getX()), static_cast<short>(point.getY()) };

        // char ch, unsigned int color, COORD coord
        m_subsystem->writeAt(' ', win32Col, coord);
    }
}

// TODO: static machen ....
unsigned int TetrisGame::toWin32Color(CellColor color) {

    unsigned int win32Color =
        (color == CellColor::LightGray) ? ConsoleBackground::GRAY :
        (color == CellColor::Cyan) ? ConsoleBackground::CYAN :
        (color == CellColor::Blue) ? ConsoleBackground::BLUE :
       // (color == CellColor::Ocker) ? ConsoleBackground::BLACK :
        (color == CellColor::Ocker) ? ConsoleBackground::RED :
        (color == CellColor::Yellow) ? ConsoleBackground::YELLOW :
        (color == CellColor::Green) ? ConsoleBackground::GREEN :
        (color == CellColor::Magenta) ? ConsoleBackground::MAGENTA :
        ConsoleBackground::RED;

    return win32Color;
}