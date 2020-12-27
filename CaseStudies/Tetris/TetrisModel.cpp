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
#include "ITetrisModel.h"
#include "TetrisModel.h"

TetrisModel::TetrisModel() {
    // WIESO mit new ???
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

bool TetrisModel::run() {

    bool gameOver = false;
    while (!gameOver && !m_exitGame) {

        TetrisState state = getState();
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

        waitForAction();  // Der Name dieser Methode passt nicht 
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

// action requests (internally initiated)
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

void TetrisModel::doActionAtBottom() {

    // rearrange field, if possible
    while (m_board->isBottomRowComplete()) {
        m_board->moveNonEmptyRowsDown();
    }

    // schedule next tetromino
    setState(TetrisState::State_AtTop);
}

void TetrisModel::doActionWayDown() {

    if (m_tetromino->canMoveDown()) {
        m_tetromino->moveDown();
    }
    else {
        setState(TetrisState::State_AtBottom);
    }
}

void TetrisModel::doActionGameOver() {
}

// action requests (externally initiated)
void TetrisModel::doActionMoveRight() {
    if (m_state != TetrisState::State_WayDown)
        return;

    if (m_tetromino->canMoveRight()) {
        m_tetromino->moveRight();
    }
}

void TetrisModel::doActionMoveLeft() {
    if (m_state != TetrisState::State_WayDown)
        return;

    if (m_tetromino->canMoveLeft()) {
        m_tetromino->moveLeft();
    }
}

void TetrisModel::doActionRotate() {
    if (m_state != TetrisState::State_WayDown)
        return;

    if (m_tetromino->canRotate()) {
        m_tetromino->rotate();
    }
}

void TetrisModel::doActionMoveDown() {
    if (m_state != TetrisState::State_WayDown)
        return;

    if (m_tetromino->canMoveDown()) {
        m_tetromino->moveDown();
    }
    else {
        setState(TetrisState::State_AtBottom);
    }
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
    assert(list.size() == 999999);   // TODO: was soll das ???? // Ach so, dass sollte �bersprungen werden ...
}

// =====================================================================================
// queue related functions

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
                default:
                    // Log.i(Globals.LogTag, "Internal ERROR: Should never be reached");
                    ::OutputDebugString("Internal ERROR [TetrisModel::waitForAction]: Should never be reached\n");
                    break;
                }
            }

            return false;
        });
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================