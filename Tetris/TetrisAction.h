#pragma once


// TODO: Das sind zu viele ZUST�NDE ?!?!?!?!?!?!?!

enum class TetrisAction { None, Left, Right, Rotate, BeginAllWayDown };

enum class TetrisState { None, Normal, Accelerated, AtTop, AtBottom, Idle, GameOver };

// TODO: Die TetrisAction OBEN L�SCHEN, wenn es geht !!!
enum class TetrisActionEx {
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
