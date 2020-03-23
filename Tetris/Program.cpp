#include <windows.h>
#include <iostream>

#include "Direction.h"
#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"
#include "TetrisGame.h"

int main()
{
    TetrisGame game;
    game.play();
    return 0;
}
