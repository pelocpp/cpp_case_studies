// =====================================================================================
// Game.cpp
// =====================================================================================

#include <windows.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
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
    Direction direction = m_console.isLastValidArrow();

    m_food.createCollisionFree(m_snake);
    while (true)
    {
        m_food.draw(m_console);
        m_snake.draw(m_console);

        if (m_console.isInputAvailable())
        {
            m_console.readInput();
            direction = m_console.isLastValidArrow();
        }

        m_snake.move(direction);

        if (m_snake.hits(m_food.getPosition()))
        {
            m_snake.grow(m_food.getPosition());
            m_food.createCollisionFree(m_snake);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (m_console.isEscapeHit())
            break;
    }

    m_console.clear();
}

// =====================================================================================
// End-of-File
// =====================================================================================
