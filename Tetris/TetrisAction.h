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

//enum class TetrisActionPrio {
//
//};