#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <windows.h>
#include <iostream>
#include <array>
#include <vector> 
#include <map> 
#include <queue> 
#include <deque> 
#include <thread> 
#include <chrono>
#include <future>
#include <functional>

#include "Globals.h"
#include "Direction.h"
#include "RotationAngle.h"

#include "CellColor.h"
#include "CellState.h"
#include "CellPoint.h"
#include "ViewCell.h"
#include "ViewCellList.h"
#include "TetrisCell.h"

#include "IKeyboardObserver.h"
#include "IKeyboardListener.h"
#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

#include "ITetrisBoardObserver.h"
#include "ITetrisBoardListener.h"

#include "ITetrisBoard.h"
#include "TetrisBoard.h"

#include "ITetromino.h"
#include "Tetromino.h"

#include "TetrisState.h"
#include "TetrisAction.h"
#include "TetrisQueue.h"
#include "ITetrisModel.h"
#include "TetrisModel.h"

#include "TetrisGame.h"

// TODO: Tetromino    RENAME

// TODO: Allgemein : Da wird viel mit Zeigern gearbeitet ====>  Unique_Ptr !!!!!!!!!!!

// TODO: Allgemein : Da wird viel mit Zeigern gearbeitet ====>  Oder Referenzen bei der Parameter Übergabe

// TODO : Alle Methoden mit Kleinbuchstaben am Anfang !!!

// TODO: Bei CellPoint und diesen vielen kleinen Klassen: inline ergänzen !!!

// TODO: Das Programm soll sich am Ende selbst beenden ===> Alle Destruktoren sollten korrekt aufräumen !!!!


// TODO: Gute Anleitung
// https://www.freetetris.org/game.php


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    TetrisGame game;
    // TODO: start und init KANN man zusammenlegen ...
    game.init();
    game.start();
    game.join();

    ::OutputDebugString("BBBBBBBBBBBB\n");

    game.stop();


    ::OutputDebugString("CCCCCCCCCCC\n");

    //char ch;
    //std::cin >> ch;
    //std::cout << "Done.";
}


//WEITER https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
//
//WEITER https://docs.microsoft.com/en-us/windows/console/low-level-console-input-functions


void doTestOutput() {

    //ConsoleSubsystem subsystem (100, 30);
    //subsystem.initConsole();
    //subsystem.showConsole();

    //unsigned char block = 32;     // 218
    //int col = 2;

    //::COORD coord{ col, col };
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.Y++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.Y++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.X++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord = {20, 2};
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.X++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.X++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);

    //coord.Y++;
    //subsystem.writeAtTest(ConsoleBackground::DARKBLUE, block, coord);
}