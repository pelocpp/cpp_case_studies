#include <windows.h>
#include <iostream>
#include <array> 
#include <thread> 
#include <chrono>
#include <future>

#include "Globals.h"
#include "Direction.h"
#include "RotationAngle.h"

#include "CellColor.h"
#include "CellState.h"
#include "CellPoint.h"
#include "ViewCell.h"
#include "ViewCellList.h"
#include "TetrisCell.h"

#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetrimino.h"
#include "Tetrimino.h"

#include "TetrisState.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

// TODO: Allgemein : Da wird viel mit Zeigern gearbeitet ====>  Unique_Ptr !!!!!!!!!!!

// TODO: Allgemein : Da wird viel mit Zeigern gearbeitet ====>  Oder Referenzen bei der Parameter Übergabe

// TODO : Alle Methoden mit Kleinbúchstaben am Anfang !!!

int main()
{
    TetrisGame game;

    // TODO: start und init KANN man zusammenlegen ...
    game.init();
    game.start();
    game.join();
    std::cout << "Done.";
    return 0;
}


//WEITER https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
//
//WEITER https://docs.microsoft.com/en-us/windows/console/low-level-console-input-functions