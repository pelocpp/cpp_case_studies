#include <windows.h>
#include <iostream>
#include <array> 
#include <vector> 
#include <map> 
#include <queue> 
#include <deque> 
#include <thread> 
#include <chrono>
#include <future>
#include <algorithm>
#include <functional>

#include "Globals.h"
#include "Direction.h"
#include "RotationAngle.h"

#include "CellColor.h"
#include "CellState.h"
#include "CellPoint.h"
#include "ViewCell.h"
#include "ViewCellList.h"
#include "TetrisCell.h"

#include "IKeyboardObserver.h"
#include "IKeyboardListener.h"
#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetromino.h"
#include "Tetromino.h"

#include "TetrisState.h"
#include "TetrisAction.h"
#include "TetrisQueue.h"
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

    // TODO: Wo ist das detach ????
    m_subsystem->attach(this);
    m_subsystem->startKeyboardLogging();

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

    ::OutputDebugString("AAAAAAAAAAA\n");
}

void TetrisGame::stop() {

    ::OutputDebugString("Stopping Game\n");
    m_subsystem->stopKeyboardLogging();

    m_subsystem->closeConsole();
}

void TetrisGame::update(const ViewCellList& list) {

    //char szBuf[128];
    //wsprintf(szBuf, "Yeahhhhhhhhhh TetrisGame::update ==> Length of List: %d\n", list.size());
    //::OutputDebugString(szBuf);

    // second approach
    std::for_each(std::begin(list), std::end(list), [=] (const ViewCell& cell) {
        
        CellColor color = cell.getColor();
        CellPoint point = cell.getPoint();

        unsigned int win32Col = TetrisGame::toWin32Color(color);
        COORD coord{ static_cast<short>(point.getX()), static_cast<short>(point.getY()) };

        // char ch, unsigned int color, COORD coord
        m_subsystem->writeAt(' ', win32Col, coord);
    });
}

void TetrisGame::update(std::deque<unsigned short> keys) {

    //char szBuf[128];
    //wsprintf(szBuf, "Ooopsie==> Length of Input List: %d\n", keys.size());
    //::OutputDebugString(szBuf);

    // transform UI subsystem based data into model conform data

    std::deque<TetrisAction> actions;
    
    std::transform(
        keys.begin(),
        keys.end(), 
        std::back_inserter(actions),
        [](unsigned short key) -> TetrisAction {
            TetrisAction result;
            switch (key)
            {
            case VK_LEFT:
                result = TetrisAction::DoLeft;
                break;
            case VK_UP:
                result = TetrisAction::DoRotate;
                break;
            case VK_RIGHT:
                result = TetrisAction::DoRight;
                break;
            case VK_DOWN:
                result = TetrisAction::DoAllWayDown;
                break;
            case VK_ESCAPE:
                throw std::exception("Internal Error: TetrisGame::update [Unexpected key event]");
                // TODO: Das NONE passt hier nicht !!!!
                //result = TetrisAction::None;
                //break;
            default:
                throw std::exception("Internal Error: TetrisGame::update [Unexpected key event]");
                // TODO: Das NONE passt hier nicht !!!!
                //result = TetrisAction::None;
                //break;
            }
            return result;
        }
    );

    //wsprintf(szBuf, "Ooopsie==> Length of Output List: %d\n", actions.size());
    //::OutputDebugString(szBuf);

    // TODO: WIRD die REIHENFOLGE derEvents bei der Abarbeitung beachtet !?!?!?!?!?!
    m_model->addActions(actions);
}

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