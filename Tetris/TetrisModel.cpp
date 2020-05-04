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
#include <condition_variable>
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
#include "Tetromino_I.h"
#include "Tetromino_O.h"

#include "TetrisState.h"
#include "TetrisAction.h"
#include "TetrisQueue.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

TetrisModel::TetrisModel() {
    m_board = new TetrisBoard(TetrisGlobals::Rows, TetrisGlobals::Cols);
    m_state = TetrisState::None;
    m_tetromino = nullptr; // TODO: Smart Ptr !!!

    m_sleepTime = TetrisGlobals::ModelSleepTime;
    m_exitGame = false;
}

TetrisModel::~TetrisModel() {
    delete m_board;
}

// getter/setter
int TetrisModel::getNumRows() {
    return TetrisGlobals::Rows;
}

int TetrisModel::getNumCols() {
    return TetrisGlobals::Cols;
}

TetrisState TetrisModel::getState() {
    return m_state;
}

void TetrisModel::setState(TetrisState state) {
    m_state = state;
}

// game commands
void TetrisModel::start() {

    m_board->clear();

    setState(TetrisState::State_AtTop);

    m_gameLoop = std::async(std::launch::async, [this] () -> bool {
            return run();
        }
    );
}

// DIESE GEHT ... ich versuche jetzt, die actions raus zu ziehen ?!?!?!
//bool TetrisModel::run() {
//
//    bool gameOver = false;
//
//    TetrisState state = TetrisState::None;
//
//    std::deque<TetrisAction> latestActions;
//
//    while (!gameOver && !m_exitGame) {
//
//        state = getState();
//
//        switch (state) {
//
//        case TetrisState::State_AtTop:
//            doActionSetToTop();
//            break;
//
//        case TetrisState::State_WayDown:
//
//            latestActions = getActions();
//            while (latestActions.size() > 0) {
//
//                TetrisAction action = latestActions.back();
//                latestActions.pop_back();
//
//                switch (action) {
//                case TetrisAction::DoRight:
//                    doActionMoveRight();
//                    break;
//                case TetrisAction::DoLeft:
//                    doActionMoveLeft();
//                    break;
//                case TetrisAction::DoRotate:
//                    doActionRotate();
//                    break;
//                case TetrisAction::DoAllWayDown:
//                    setState(TetrisState::State_AllWayDown);
//                    break;
//                default:
//                    // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
//                    ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
//                    break;
//                }
//            }
//
//            doActionMoveDown();
//            break;
//
//        case TetrisState::State_AllWayDown:
//            // TODO: Hier könnte man die Sleep Zeit verkürzen
//            doActionMoveDown();
//            break;
//
//        case TetrisState::State_AtBottom:
//            doActionAtBottom();
//            break;
//
//        case TetrisState::State_GameOver:
//            doActionGameOver();
//            gameOver = true;
//            break;
//
//        default:
//            // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
//            ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
//            break;
//        }
//
//        // std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));
//        waitForAction();
//    }
//
//    return true; // TODO: oder false
//}


bool TetrisModel::run() {

    bool gameOver = false;

    TetrisState state = TetrisState::None;

    std::deque<TetrisAction> latestActions;

    while (!gameOver && !m_exitGame) {

        state = getState();

        switch (state) {

        case TetrisState::State_AtTop:
            doActionSetToTop();
            break;

        case TetrisState::State_WayDown:
            doActionWayDown();
            break;

        case TetrisState::State_AtBottom:
            doActionAtBottom();
            break;

        case TetrisState::State_GameOver:
            doActionGameOver();
            gameOver = true;
            break;

        default:
            // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
            ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
            break;
        }

        // std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));
        waitForAction();
    }

    return true; // TODO: oder false
}

void TetrisModel::join() {

    m_gameLoop.get();
}

void TetrisModel::createNextTetromino() {
   //  m_tetromino = std::make_unique<Tetromino_L>(m_board);

    constexpr int MaxTetriminos = 3;
    static int next = 0;

    if (next % MaxTetriminos == 0)
        m_tetromino = std::make_unique<Tetromino_L>(m_board);
    else if (next % MaxTetriminos == 1)
        m_tetromino = std::make_unique<Tetromino_O>(m_board);
    else if (next % MaxTetriminos == 2)
        m_tetromino = std::make_unique<Tetromino_I>(m_board);

    next++;
    if (next == MaxTetriminos) {
        next = 0;
    }
}

void TetrisModel::doActionSetToTop() {

    createNextTetromino();

    clearActions();

    if (m_tetromino->canSetToTop()) {
        m_tetromino->setToTop();
        setState(TetrisState::State_WayDown);
    }
    else {
        setState(TetrisState::State_GameOver);
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

void TetrisModel::doActionRotate() {
    if (m_tetromino->canRotate()) {
        m_tetromino->rotate();
    }
}

void TetrisModel::doActionMoveDown() {
    if (m_tetromino->canMoveDown()) {
        m_tetromino->moveDown();
    }
}

 void TetrisModel::doActionWayDown() {
 
     if (m_tetromino->canMoveDown()) {
         m_tetromino->moveDown();
     }
     else {
         setState(TetrisState::State_AtBottom);
     }
 }

void TetrisModel::doActionAtBottom() {

    // rearrange field, if possible
    while (m_board->isBottomRowComplete()) {
        m_board->moveNonEmptyRowsDown();
    }

    // schedule next tetromino
    setState(TetrisState::State_AtTop);
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

//void TetrisModel::pushAction(const TetrisActionPair& pair) {
//    {
//        // RAII
//        std::scoped_lock<std::mutex> lock(m_mutex);
//
//        // don't add same action twice
//        //if (m_actions.contains(pair)) {
//        //    return;
//        //}
//
//        m_actions.push_back(pair.second);
//    }
//}


void TetrisModel::pushActions(const std::deque<TetrisAction>& actions) {
    {
        // RAII
        std::scoped_lock<std::mutex> lock(m_mutex);

        // special case: 'exit game' requested?
        auto ret = std::find_if(std::begin(actions), std::end(actions), [this](const TetrisAction action) {

            if (action == TetrisAction::DoExitGame) {
                m_exitGame = true;
                return true;
            }
            else {
                return false;
            }
        });

        // TODO: Hmmm, hier werden doppelte Keys aufgenommen !

        std::copy(std::begin(actions), std::end(actions), back_inserter(m_actions));

        // wakeup game loop
        m_condition.notify_one();
    }

    // after 'critical section'
    //char szText[128];
    //::wsprintf(szText, "> #actions now %d\n", m_actions.size());
    //::OutputDebugString(szText);
}

void TetrisModel::clearActions() {
    {
        // RAII
        std::scoped_lock<std::mutex> lock(m_mutex);
        m_actions.clear();  // clear common queue
    }
}

std::deque<TetrisAction> TetrisModel::getActions() {
    std::deque<TetrisAction> actions;
    {
        // RAII
        std::scoped_lock<std::mutex> lock(m_mutex);

        //try {
        //    std::scoped_lock<std::mutex> lock(m_mutex);
        //}
        //catch (std::exception ex) {
        //    ::OutputDebugString(ex.what());
        //}

        actions = m_actions;  // get copy of current actions
        m_actions.clear();    // clear common queue
    }

    return actions;
}

std::deque<TetrisAction> TetrisModel::getActionsNoOwnership() {

    std::deque<TetrisAction> actions = m_actions;  // get copy of current actions
    m_actions.clear();    // clear common queue
    return actions;
}

void TetrisModel::waitForAction() {
    {
        // RAII
        std::unique_lock guard(m_mutex);
        m_condition.wait_for(guard, std::chrono::milliseconds(m_sleepTime), [this]() {

            std::deque<TetrisAction> latestActions = getActionsNoOwnership();

            // char szText[128];
            // ::wsprintf(szText, "> IN wait_for: %d actions\n", latestActions.size());
            // ::OutputDebugString(szText);

            while (latestActions.size() > 0) {

                TetrisAction action = latestActions.back();
                latestActions.pop_back();

                switch (action) {
                case TetrisAction::DoRight:
                    doActionMoveRight();
                    break;
                case TetrisAction::DoLeft:
                    doActionMoveLeft();
                    break;
                case TetrisAction::DoRotate:
                    doActionRotate();
                    break;
                case TetrisAction::DoDown:
                    doActionMoveDown();
                    break;
                //case TetrisAction::DoAllWayDown:
                //    setState(TetrisState::State_AllWayDown);
                //    break;
                default:
                    // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
                    ::OutputDebugString("(99) Internal ERROR : Should never be reached\n");
                    break;
                }
            }

            //if (m_actions.size() > 0) {
            //    return true;
            //}
            //else {
            //    return false;
            //}

            return false;
        });
    }
}

//TetrisAction TetrisModel::popAction() {
//
//    TetrisAction action;
//    {
//        // RAII
//        std::scoped_lock<std::mutex> lock(m_mutex);
//        action = m_actions.front();
//        m_actions.pop_front();
//    }
//
//    //std::ostringstream oss;
//    //oss << "> Pop Action: " << pair << " [" << m_actionsPQ2.count() << "]\n";
//    //::OutputDebugString(oss.str().data());
//
//    return action;
//}

//void TetrisModel::pushAction(const TetrisActionPair& pair) {
//    {
//        // RAII
//        std::scoped_lock<std::mutex> lock(m_mutex);
//
//        // don't add same action twice
//        if (m_actionsPQ2.contains(pair)) {
//            return;
//        }
//        m_actionsPQ2.push(pair);
//    }
//}

//void TetrisModel::addActions(const std::deque<TetrisAction>& actions) {
//    std::for_each(std::begin(actions), std::end(actions), [this](TetrisAction action) {
//        switch (action) {
//        case TetrisAction::DoLeft:
//            pushAction(makeAction<TetrisAction::DoLeft>());
//            break;
//        case TetrisAction::DoRight:
//            pushAction(makeAction<TetrisAction::DoRight>());
//            break;
//        case TetrisAction::DoRotate:
//            pushAction(makeAction<TetrisAction::DoRotate>());
//            break;
//        case TetrisAction::AllWayDown:
//            pushAction(makeAction<TetrisAction::AllWayDown>());
//            break;
//        default:
//            throw std::exception("Internal Error: TetrisModel::addActions [Unexpected external event]");
//        }
//        }
//    );
//
//   // m_actionsPQ2.dump();
//}

//TetrisAction TetrisModel::popAction() {
//
//    TetrisActionPair pair;
//    {
//        // RAII
//        std::scoped_lock<std::mutex> lock(m_mutex);
//        pair = m_actionsPQ2.top();
//        m_actionsPQ2.pop();
//    }
//
//    std::ostringstream oss;
//    oss << "> Pop Action: " << pair << " [" << m_actionsPQ2.count() << "]\n";
//    ::OutputDebugString(oss.str().data());
//
//    auto [prio, action] = pair;
//    return action;
//}

// =====================================================================================
// End-of-File
// =====================================================================================