// =====================================================================================
// TetrisAction: enums and miscellaneous functions
// =====================================================================================

#include <windows.h>
#include <iostream>
#include <array> 
#include <vector> 
#include <map> 
#include <queue> 
#include <thread> 
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

#include "TetrisAction.h"

// =====================================================================================
// maps just for dumping tetris actions

std::map<TetrisAction, std::string> tetrisActionIdentifiers{
    {  TetrisAction::None,       "None"       },
    {  TetrisAction::AtTop,      "AtTop"      },
    {  TetrisAction::WayDown,    "WayDown"    },
    {  TetrisAction::DoLeft,     "DoLeft"     },
    {  TetrisAction::DoRight,    "DoRight"    },
    {  TetrisAction::DoRotate,   "DoRotate"   },
    {  TetrisAction::AllWayDown, "AllWayDown" },
    {  TetrisAction::AtBottom,   "AtBottom"   },
    {  TetrisAction::GameOver,   "GameOver"   }
};

std::map<TetrisActionPrio, std::string> tetrisActionPrioIdentifiers{
    {  TetrisActionPrio::Low,    "Low"    },
    {  TetrisActionPrio::Normal, "Normal" },
    {  TetrisActionPrio::High,    "High"  }
};

bool operator== (const TetrisActionPair& lhs, const TetrisActionPair& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

std::ostream& operator<< (std::ostream& os, const TetrisActionPair& pair) {
    os 
        << "Prio: " << tetrisActionPrioIdentifiers[pair.first] 
        << ", Action: " << tetrisActionIdentifiers[pair.second];
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================