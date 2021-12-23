// =====================================================================================
// Food.cpp
// =====================================================================================

#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>

#include "Direction.h"
#include "GameConsole.h"
#include "Snake.h"
#include "Food.h"

// c'tor
Food::Food()
{
    m_coord.X = -1;
    m_coord.Y = -1;

    // init random generator
   // ::srand((unsigned int) ::time((time_t*)0));
}

// public interface
void Food::createCollisionFree(const Snake & snake)
{
    COORD tmp{};
    while (true)
    {
        // create new food at random
        //SHORT iX{ rand() % (GameConsole::Width - 2) };
        //SHORT iY{ rand() % (GameConsole::Height - 2) };

        // simulating still some calculation time ...
        SHORT iX{ m_device() % (GameConsole::Width - 2) };
        SHORT iY{ m_device() % (GameConsole::Height - 2) };




        tmp.X = iX + 1;
        tmp.Y = iY + 1;

        if (snake.hits(tmp))
            continue;
        else
            break;
    }

    m_coord = tmp;
}

void Food::draw(GameConsole& console)
{
    console.writeAt('X', m_coord);
}

// =====================================================================================
// End-of-File
// =====================================================================================
