#include <windows.h>
#include <iostream>
#include <array> 
#include <queue> 
#include <thread> 
#include <chrono>
#include <future>
#include <cassert>
#include <memory>

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

#include "ITetrimino.h"
#include "Tetrimino.h"
#include "Tetrimino_L.h"

#include "TetrisAction.h"
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

    pushAction(TetrisActionEx::AtTop);
   // setState(TetrisState::AtTop);

    m_gameLoop = std::async(std::launch::async, [this] () -> bool {
            return run();
        }
    );

    ::OutputDebugString("(9) nach std::async\n");
}

bool TetrisModel::run() {

   // TetrisState state = getState();

    TetrisActionEx action = TetrisActionEx::None;

    while (action != TetrisActionEx::GameOver) {

        action = popAction();

        switch (action) {

        case TetrisActionEx::AtTop:
            doActionSetToTop();
            break;

        case TetrisActionEx::WayDown:
     //   case TetrisActionEx::Accelerated:
            doActionMoveDown();
            break;

        case TetrisActionEx::DoRight:
            doActionMoveRight();
            break;

        case TetrisActionEx::DoLeft:
            doActionMoveLeft();
            break;

        case TetrisActionEx::AtBottom:
            doActionAtBottom();
            break;

        case TetrisActionEx::GameOver:
            doActionGameOver();
            break;

        default:
            // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
            ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(ModelSleep));
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



// TODO TODO: DIe müssen möglicherweise THREAD SAFE gemacht werden !!!!!!!!!!!!!!!!

void TetrisModel::pushAction(TetrisActionEx action) {
    m_actions.push_back(action);
}

void TetrisModel::addActions(const std::deque<TetrisActionEx>& actions) {

    std::deque<TetrisActionEx>::iterator it = m_actions.begin();
    m_actions.insert(it, actions.begin(), actions.end());
}

TetrisActionEx TetrisModel::popAction() {
    TetrisActionEx tmp = m_actions.front();
    m_actions.pop_front();
    return tmp;
}

// TODO TODO: DIe müssen möglicherweise THREAD SAFE gemacht werden !!!!!!!!!!!!!!!!


void TetrisModel::createNextTetrimino() {
    m_tetromino = std::make_unique<Tetrimino_L>(m_board);
}

void TetrisModel::doActionSetToTop() {

    ::OutputDebugString("> doActionSetToTop\n");

    createNextTetrimino();

    if (m_tetromino->canSetToTop()) {
        m_tetromino->setToTop();
        // setState(TetrisState::Normal);
        pushAction(TetrisActionEx::WayDown);
    }
    else {
        // setState(TetrisState::GameOver);
        pushAction(TetrisActionEx::GameOver);
    }
}

void TetrisModel::doActionMoveRight() {

    if (m_tetromino->canMoveRight())
        m_tetromino->moveRight();
}

void TetrisModel::doActionMoveLeft() {


    if (m_tetromino->canMoveLeft())
        m_tetromino->moveLeft();
}

void TetrisModel::doActionMoveDown() {

    ::OutputDebugString("=> doActionMoveDown\n");

    if (m_tetromino->canMoveDown()) {
        m_tetromino->moveDown();
        pushAction(TetrisActionEx::WayDown);
    }
    else {
       // setState(TetrisState::AtBottom);
        pushAction(TetrisActionEx::AtBottom);
    }
}

void TetrisModel::doActionAtBottom() {

    ::OutputDebugString("=> doActionAtBottom\n");

    // rearrange field, if possible
    //while (this.board.IsBottomRowComplete()) {
    //    this.board.MoveNonEmptyRowsDown();
    //}

    // schedule next tetrimino
    // setState(TetrisState::AtTop);
    pushAction(TetrisActionEx::AtTop);
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