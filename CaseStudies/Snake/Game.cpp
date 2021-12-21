// =====================================================================================
// XXX.cpp
// =====================================================================================

#include <windows.h>

#include "Direction.h"
#include "GameConsole.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"

// c'tor
Game::Game()
{
    m_console.Setup();
}

// public interface
void Game::Play()
{
    Direction dir = m_console.LastValidArrow();

    m_food.CreateCollisionFree(m_snake);
    while (true)
    {
        m_food.Draw(m_console);
        m_snake.Draw(m_console);

        if (m_console.InputAvailable())
        {
            m_console.ReadInput();
            dir = m_console.LastValidArrow();
        }

        m_snake.Move(dir);

        if (m_snake.Hits(m_food.Position()))
        {
            m_snake.Grow(m_food.Position());
            m_food.CreateCollisionFree(m_snake);
        }

        ::Sleep(Pause);   // TODO: EIn anderes Sleep !!! std::thread !!!
        if (m_console.IsEscapeHit())
            break;
    }

    m_console.Clear();
}

// =====================================================================================
// End-of-File
// =====================================================================================
