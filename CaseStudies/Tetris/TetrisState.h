// =====================================================================================
// TetrisState enum
// =====================================================================================

#pragma once

enum class TetrisState {
    None,             
    State_AtTop,      // set next tetromino at top
    State_WayDown,    // move tetromino one row down
    State_AtBottom,   // tetromino has reached bottom
    State_GameOver    // game is over
};

// =====================================================================================
// tracing utility funtions

template <bool>
inline void traceState(TetrisState action);

template <>
inline void traceState<true>(TetrisState action) {
    if (action == TetrisState::State_AtTop) {
        ::OutputDebugString("=> TetrisState::State_AtTop\n");
    }
    else if (action == TetrisState::State_WayDown) {
        ::OutputDebugString("=> TetrisState::State_WayDown\n");
    }
    else if (action == TetrisState::State_AtBottom) {
        ::OutputDebugString("=> TetrisState::State_AtBottom\n");
    }
    else if (action == TetrisState::State_GameOver) {
        ::OutputDebugString("=> TetrisState::State_GameOver\n");
    }
    else {
        ::OutputDebugString("=> Unknown TetrisState - Internal Error!\n");
    }
}

template <>
inline void traceState<false>(TetrisState action) {}

// =====================================================================================
// End-of-File
// =====================================================================================
