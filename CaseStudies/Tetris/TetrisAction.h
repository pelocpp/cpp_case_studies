// =====================================================================================
// TetrisAction: enums and miscellaneous functions
// =====================================================================================

#pragma once

// =====================================================================================
// tetris actions: externally triggered (keyboard) events

enum class TetrisAction {
    None,          //
    DoLeft,        // move tetromino right (external action)
    DoRight,       // move tetromino left  (external action)
    DoRotate,      // rotate tetromino (external action)
    DoDown,        // move tetromino one row down (external action)
    DoExitGame     // force 'exit game'
};

// =====================================================================================
// tracing utility funtions

template <bool>
inline void traceAction(TetrisAction action);

template <>
inline void traceAction<true>(TetrisAction action) {
    if (action == TetrisAction::DoLeft) {
        ::OutputDebugString("=> TetrisAction::DoLeft\n");
    }
    else if (action == TetrisAction::DoRight) {
        ::OutputDebugString("=> TetrisAction::DoRight\n");
    }
    else if (action == TetrisAction::DoRotate) {
        ::OutputDebugString("=> TetrisAction::DoRotate\n");
    }
    else if (action == TetrisAction::DoDown) {
        ::OutputDebugString("=> TetrisAction::DoDown\n");
    }
    else if (action == TetrisAction::DoExitGame) {
        ::OutputDebugString("=> TetrisAction::DoExitGame\n");
    }
    else {
        ::OutputDebugString("=> Unknown TetrisAction - Internal Error!\n");
    }
}

template <>
inline void traceAction<false>(TetrisAction action) {}

// =====================================================================================
// End-of-File
// =====================================================================================