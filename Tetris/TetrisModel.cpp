#include <windows.h>
#include <iostream>
#include <array> 
#include <thread> 
#include <chrono>
#include <future>
#include <cassert>

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
#include "Tetrimino_L.h"

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

TetrisModel::TetrisModel() {
    m_board = new TetrisBoard(Rows, Cols);
    m_state = TetrisState::None;
    m_curr = nullptr; // TODO: Smart Ptr !!!
}

TetrisModel::~TetrisModel() {
    delete m_board;
}

int TetrisModel::getNumRows() {
    return Rows;
}

int TetrisModel::getNumCols() {
    return Cols;
}

// game commands
void TetrisModel::start() {

    m_board->clear();
    setState(TetrisState::AtTop);

    m_futureGameLoop = std::async(std::launch::async, [this] () -> bool {
            return run();
        }
    );

    ::OutputDebugString("(9) nach std::async\n");
}

bool TetrisModel::run() {

    while (true) {

        ::OutputDebugString("(1) TetrisModel::play\n");

        TetrisState state = getState();

        switch (state) {

        case TetrisState::AtTop:
            doActionSetToTop();
            break;

        case TetrisState::Normal:
        case TetrisState::Accelerated:
            doActionMoveDown();
            break;

        case TetrisState::AtBottom:
            doActionAtBottom();
            break;

        case TetrisState::GameOver:
            doActionGameOver();
            break;

        default:
            // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
            ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return true; // TODO: oder false
}

void TetrisModel::join() {

    m_futureGameLoop.get();
}


void TetrisModel::stop() {

    // TODO: Hier muss irgendwie der Thread gestoppt werden ?!"?

}

// getter/setter
TetrisState TetrisModel::getState() {
    return m_state;
}

void TetrisModel::setState(TetrisState state) {
    m_state = state;
}

ITetrimino* TetrisModel::attachTetrimino() {
    m_curr = new Tetrimino_L(m_board);

    // TODO: Warum muss AttachTetrimino einen Wert zurückliefern ????

    return m_curr;
}

void TetrisModel::detachTetrimino() {
    delete m_curr;
}

void TetrisModel::doActionSetToTop() {

    ::OutputDebugString("(2) doActionSetToTop\n");

    assert(getState() == TetrisState::AtTop);

    // create new tetrimino
    m_curr = attachTetrimino();

    if (m_curr->canSetToTop()) {
        m_curr->setToTop();
        setState(TetrisState::Normal);
    }
    else {
        setState(TetrisState::GameOver);
    }
}

void TetrisModel::doActionMoveDown() {

    ::OutputDebugString("(3) doActionMoveDown\n");

    assert(getState() == TetrisState::Normal || getState() == TetrisState::Accelerated);

    if (m_curr->canMoveDown()) {
        m_curr->moveDown();
    }
    else {
        setState(TetrisState::AtBottom);
    }
}

void TetrisModel::doActionAtBottom() {
}

void TetrisModel::doActionGameOver() {
}

void TetrisModel::attach(ITetrisBoardObserver* observer) {
    m_board->attach(observer);
}

void TetrisModel::detach(ITetrisBoardObserver* observer) {
    // TODO: Wie war das mit erase und remove
    m_board->detach(observer);
}

void TetrisModel::notifyAll(const ViewCellList& list) {
    // should never be called
    ::OutputDebugString("Internal Error: TetrisModel::notifyAll\n");
    assert(list.size() == 999999);
}