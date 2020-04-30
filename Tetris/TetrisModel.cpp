// =====================================================================================
// TetrisModel
// =====================================================================================

#include <windows.h>
#include <iostream>
#include <sstream>
#include <array> 
#include <vector> 
#include <map> 
#include <queue> 
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <cassert>
#include <memory>
#include <functional>

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

#include "ITetromino.h"
#include "Tetromino.h"
#include "Tetromino_L.h"

#include "TetrisAction.h"
#include "TetrisQueue.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

TetrisModel::TetrisModel() {
    m_board = new TetrisBoard(Rows, Cols);

 //   m_state = TetrisState::None;

    m_tetromino = nullptr; // TODO: Smart Ptr !!!
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

    pushAction(makeAction<TetrisAction::AtTop>());
   // setState(TetrisState::AtTop);

    m_gameLoop = std::async(std::launch::async, [this] () -> bool {
            return run();
        }
    );

    ::OutputDebugString("(9) nach std::async\n");
}

bool TetrisModel::run() {

   // TetrisState state = getState();

    TetrisAction action = TetrisAction::None;

    while (action != TetrisAction::GameOver) {

        action = popAction();

        switch (action) {

        case TetrisAction::AtTop:
            doActionSetToTop();
            break;

        case TetrisAction::WayDown:
     //   case TetrisAction::Accelerated:
            doActionMoveDown();
            break;

        case TetrisAction::DoRight:
            doActionMoveRight();
            break;

        case TetrisAction::DoLeft:
            doActionMoveLeft();
            break;

        case TetrisAction::AtBottom:
            doActionAtBottom();
            break;

        case TetrisAction::GameOver:
            doActionGameOver();
            break;

        default:
            // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
            ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
            break;
        }

    //    std::this_thread::sleep_for(std::chrono::milliseconds(::ModelSleepTime));

        if (! m_actionsPQ2.anyHighPrioAction() ) {
            std::this_thread::sleep_for(std::chrono::milliseconds(::ModelSleepTime));
        }
    }

    return true; // TODO: oder false
}

void TetrisModel::join() {

    m_gameLoop.get();
}

// getter/setter
//TetrisState TetrisModel::getState() {
//    return m_state;
//}
//
//void TetrisModel::setState(TetrisState state) {
//    m_state = state;
//}

void TetrisModel::createNextTetromino() {
    m_tetromino = std::make_unique<Tetromino_L>(m_board);
}

void TetrisModel::doActionSetToTop() {

    ::OutputDebugString("> doActionSetToTop\n");

    createNextTetromino();

    if (m_tetromino->canSetToTop()) {
        m_tetromino->setToTop();
        // setState(TetrisState::Normal);
        pushAction(makeAction<TetrisAction::WayDown>());
    }
    else {
        // setState(TetrisState::GameOver);
        pushAction(makeAction<TetrisAction::GameOver>());
    } 
}

void TetrisModel::doActionMoveRight() {
    if (m_tetromino->canMoveRight()) {
        m_tetromino->moveRight();
    }
}

void TetrisModel::doActionMoveLeft() {
    if (m_tetromino->canMoveLeft()) {
        m_tetromino->moveLeft();
    }
}

void TetrisModel::doActionMoveDown() {

    ::OutputDebugString("=> doActionMoveDown\n");

    if (m_tetromino->canMoveDown()) {
        m_tetromino->moveDown();
        pushAction(makeAction<TetrisAction::WayDown>());
    }
    else {
       // setState(TetrisState::AtBottom);
        pushAction(makeAction<TetrisAction::AtBottom>());
    }
}

void TetrisModel::doActionAtBottom() {

    ::OutputDebugString("=> doActionAtBottom\n");

    // rearrange field, if possible
    //while (this.board.IsBottomRowComplete()) {
    //    this.board.MoveNonEmptyRowsDown();
    //}

    // schedule next tetromino
    // setState(TetrisState::AtTop);
    pushAction(makeAction<TetrisAction::AtTop>());
}

void TetrisModel::doActionGameOver() {
}

// =====================================================================================
// observer handling

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
    assert(list.size() == 999999);   // TODO: was soll das ???? // Ach so, dass sollte übersprungen werden ...
}

// =====================================================================================
// tetris model queue actions

void TetrisModel::pushAction(const TetrisActionPair& pair) {
    {
        // RAII
        std::scoped_lock<std::mutex> lock(m_mutex);

        // don't add same action twice
        if (m_actionsPQ2.contains(pair)) {
            return;
        }
        m_actionsPQ2.push(pair);
    }
}

void TetrisModel::addActions(const std::deque<TetrisAction>& actions) {
    std::for_each(std::begin(actions), std::end(actions), [this](TetrisAction action) {
        switch (action) {
        case TetrisAction::DoLeft:
            pushAction(makeAction<TetrisAction::DoLeft>());
            break;
        case TetrisAction::DoRight:
            pushAction(makeAction<TetrisAction::DoRight>());
            break;
        case TetrisAction::DoRotate:
            pushAction(makeAction<TetrisAction::DoRotate>());
            break;
        case TetrisAction::AllWayDown:
            pushAction(makeAction<TetrisAction::AllWayDown>());
            break;
        default:
            throw std::exception("Internal Error: TetrisModel::addActions [Unexpected external event]");
        }
        }
    );

    m_actionsPQ2.dump();
}

TetrisAction TetrisModel::popAction() {

    TetrisActionPair pair;
    {
        // RAII
        std::scoped_lock<std::mutex> lock(m_mutex);
        pair = m_actionsPQ2.top();
        m_actionsPQ2.pop();
    }

    std::ostringstream oss;
    oss << "> Pop Action: " << pair << " [" << m_actionsPQ2.count() << "]\n";
    ::OutputDebugString(oss.str().data());

    auto [prio, action] = pair;
    return action;
}

// =====================================================================================
// End-of-File
// =====================================================================================