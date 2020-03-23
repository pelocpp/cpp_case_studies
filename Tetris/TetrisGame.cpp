#include <windows.h>
#include <iostream>
#include <thread> 
#include <chrono>

#include "Direction.h"
#include "Globals.h"
#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"
#include "TetrisGame.h"

TetrisGame::TetrisGame() {
    m_subsystem = new ConsoleSubsystem(Cols, Rows);
    m_subsystem->initConsole();
    m_subsystem->showConsole();
}

void TetrisGame::play() {

    while (true) {

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
