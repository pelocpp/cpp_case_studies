// =====================================================================================
// XXX.cpp
// =====================================================================================

#include <windows.h>
#include <time.h>   // TODO: Der kann dann mal weg

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
    ::srand((unsigned int) ::time((time_t*)0));
}

// getter
COORD Food::Position()
{
    return m_coord;
}

// public interface
void Food::CreateCollisionFree(const Snake & snake)
{
    COORD tmp;
    while (true)
    {
        // create new food at random
        int iX = rand() % (GameConsole::Width - 2);
        int iY = rand() % (GameConsole::Height - 2);

        tmp.X = iX + 1;
        tmp.Y = iY + 1;

        if (snake.Hits(tmp))
            continue;
        else
            break;
    }

    m_coord = tmp;
}

void Food::Draw(GameConsole & console)
{
    console.WriteAt('X', m_coord);
}

// =====================================================================================
// End-of-File
// =====================================================================================
