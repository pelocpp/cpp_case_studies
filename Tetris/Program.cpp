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

// TODO: Bei CellPoint und diesen vielen kleinen Klassen: inline ergänzen !!!


void doGame() {
    TetrisGame game;

    // TODO: start und init KANN man zusammenlegen ...
    game.init();
    game.start();
    game.join();
    std::cout << "Done.";
}


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

// Handler function will be called on separate thread!
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT: // Ctrl+C
        ::OutputDebugString("CTRL_C_EVENT\n");
        break;
    case CTRL_BREAK_EVENT: // Ctrl+Break
        ::OutputDebugString("CTRL_BREAK_EVENT\n");
        break;
    case CTRL_CLOSE_EVENT: // Closing the console window
        ::OutputDebugString("CTRL_CLOSE_EVENT\n");
        break;
    case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
        ::OutputDebugString("CTRL_LOGOFF_EVENT\n");
        break;
    case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
        ::OutputDebugString("CTRL_SHUTDOWN_EVENT\n");
        break;
    }

    // Return TRUE if handled this message, further handler functions won't be called.
    // Return FALSE to pass this message to further handlers until default handler calls ExitProcess().
    return FALSE;
}

int main()
{
    ::SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

    doGame();
    char ch;
    std::cin >> ch;
}


//WEITER https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
//
//WEITER https://docs.microsoft.com/en-us/windows/console/low-level-console-input-functions