// =====================================================================================
// TetrisState enum
// =====================================================================================

#pragma once

enum class TetrisState {
    None,          //
    State_AtTop,         // set next tetromino at top
    State_WayDown,       // move tetromino one row down
    State_AllWayDown,    // move tetromino all rows down
    State_AtBottom,      // (( tetromino has reached bottom, TODO: do we need this state ?? ))
    State_GameOver       // game is over
};

// =====================================================================================
// End-of-File
// =====================================================================================