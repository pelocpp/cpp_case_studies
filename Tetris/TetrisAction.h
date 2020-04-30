// =====================================================================================
// TetrisAction: enums and miscellaneous functions
// =====================================================================================

#pragma once

// =====================================================================================
// tetris actions: internal and external (keyboard)

enum class TetrisAction {
    None,          //
    AtTop,         // set next tetromino at top
    WayDown,       // move tetromino down
    DoLeft,        // move tetromino right (external action)
    DoRight,       // move tetromino left  (external action)
    DoRotate,      // rotate tetromino (external action)
    AllWayDown,    // move tetromino all rows down (external action)
    AtBottom,      // (( tetromino has reached bottom, TODO: do we need this state ?? ))
    GameOver       // game is over
};

enum class TetrisActionPrio {
    Low,
    Normal,
    High
};

using TetrisActionPair = std::pair<TetrisActionPrio, TetrisAction>;

extern std::ostream& operator<< (std::ostream&, const TetrisActionPair&); 
extern bool operator== (const TetrisActionPair&, const TetrisActionPair&);

// =====================================================================================
// central location to provide priority to tetris actions

template <TetrisAction action>
TetrisActionPair makeAction() {
    if constexpr (action == TetrisAction::AtTop) {
        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtTop);
    }
    if constexpr (action == TetrisAction::WayDown) {
        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::WayDown);
    }
    if constexpr (action == TetrisAction::DoLeft) {
        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoLeft);
    }
    if constexpr (action == TetrisAction::DoRight) {
        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoRight);
    }
    if constexpr (action == TetrisAction::DoRotate) {
        return std::make_pair(TetrisActionPrio::High, TetrisAction::DoRotate);
    }
    if constexpr (action == TetrisAction::AllWayDown) {
        return std::make_pair(TetrisActionPrio::High, TetrisAction::AllWayDown);
    }
    if constexpr (action == TetrisAction::AtBottom) {
        return std::make_pair(TetrisActionPrio::Normal, TetrisAction::AtBottom);
    }
    if constexpr (action == TetrisAction::GameOver) {
        return std::make_pair(TetrisActionPrio::High, TetrisAction::GameOver);
    }
}

// =====================================================================================
// tracing actions

template <bool>
inline void traceAction(TetrisAction action);

template <>
inline void traceAction<true>(TetrisAction action) {

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
inline void traceAction<false>(TetrisAction action) {}

// =====================================================================================
// End-of-File
// =====================================================================================