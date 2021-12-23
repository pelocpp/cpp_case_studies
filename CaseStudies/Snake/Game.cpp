// =====================================================================================
// Game.cpp
// =====================================================================================

#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>

#include "Direction.h"
#include "GameConsole.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"

// c'tor
Game::Game()
{
    m_console.setup();
}

// public interface
void Game::play()
{
    Direction dir = m_console.isLastValidArrow();

    m_food.createCollisionFree(m_snake);
    while (true)
    {
        m_food.draw(m_console);
        m_snake.draw(m_console);

        if (m_console.isInputAvailable())
        {
            m_console.readInput();
            dir = m_console.isLastValidArrow();
        }

        m_snake.move(dir);

        if (m_snake.hits(m_food.getPosition()))
        {
            m_snake.grow(m_food.getPosition());
            m_food.createCollisionFree(m_snake);
        }

        ::Sleep(Pause);   // TODO: EIn anderes Sleep !!! std::thread !!!
        if (m_console.isEscapeHit())
            break;
    }

    m_console.clear();
}

// =====================================================================================
// End-of-File
// =====================================================================================
