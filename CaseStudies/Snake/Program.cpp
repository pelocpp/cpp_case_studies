// =====================================================================================
// Program.cpp
// =====================================================================================

// TODO im text aufführen: aggregate initialization using designated initializers

// TODO static constexpr char Box_Left_Upper = ((char)201);   // TODO \xnn

#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>

#include "Direction.h"
#include "GameConsole.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"

int main()
{
    Game game;
    game.play();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
