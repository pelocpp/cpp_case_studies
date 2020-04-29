#pragma once

enum class TetrisAction {
    None,          //
    AtTop,         // set next tetromino at top
    WayDown,       // move tetromino down
    DoLeft,        // move tetromino right
    DoRight,       // move tetromino left
    DoRotate,      // rotate tetromino
    AllWayDown,    // move tetromino all rows down
    AtBottom,      // (( tetromino has reached bottom, TODO: do we need this state ?? ))
    GameOver       // game is over
};

enum class TetrisActionPrio {
    Low,
    Normal,
    High
};

using TetrisActionPair = std::pair<TetrisActionPrio, TetrisAction>;

template <TetrisAction action>
TetrisActionPair makeAction() {

    if constexpr (action == TetrisAction::AllWayDown) {
        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AllWayDown);
    }

    if constexpr (action == TetrisAction::AllWayDown) {
        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AllWayDown);
    }
}

template <bool>
void traceAction(TetrisAction action);

template <>
void traceAction<true>(TetrisAction action) {

    if (action == TetrisAction::AtTop) {
        ::OutputDebugString("=> next action => AtTop\n");
    }
    else if (action == TetrisAction::WayDown) {
        ::OutputDebugString("=> next action => WayDown\n");
    }
    else if (action == TetrisAction::DoLeft) {
        ::OutputDebugString("=> next action => DoLeft\n");
    }
    else if (action == TetrisAction::DoRight) {
        ::OutputDebugString("=> next action => DoRight\n");
    }
    else if (action == TetrisAction::DoRotate) {
        ::OutputDebugString("=> next action => DoRotate\n");
    }
    else if (action == TetrisAction::AllWayDown) {
        ::OutputDebugString("=> next action => AllWayDown\n");
    }
    else if (action == TetrisAction::AtBottom) {
        ::OutputDebugString("=> next action => AtBottom\n");
    }
    else if (action == TetrisAction::GameOver) {
        ::OutputDebugString("=> next action => GameOver\n");
    }
    else {
        ::OutputDebugString("=> unknown action => Internal Error!\n");
    }
}

template <>
void traceAction<false>(TetrisAction action) {}