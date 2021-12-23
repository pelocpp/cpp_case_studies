// =====================================================================================
// Snake.cpp
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
Snake::Snake()
{
    for (uint16_t i = 0; i != InitialLength; i++) {
        m_tail.emplace_back(
           static_cast<SHORT> (GameConsole::Width / 2 + i),
           static_cast<SHORT> (GameConsole::Height / 2)
        );
    }

    m_head.X = GameConsole::Width / 2 + 4;
    m_head.Y = GameConsole::Height / 2;
}

void Snake::draw(GameConsole& console) const
{
    // clear snake's tail ...
    COORD tail = m_tail[0];
    console.writeAt(' ', tail);

    // just draw element after head ...
    COORD last = m_tail[m_tail.size() - 1];
    console.writeAt('*', last);

    // ... and head itself
    console.writeAt('O', m_head);
}

void Snake::grow(COORD coord)
{
    // last head gets new begin of tail
    m_tail.insert(m_tail.begin(), m_head);

    // set new head
    m_head = coord;
}

bool Snake::hits(COORD coord) const
{
    for (size_t i{}; i != m_tail.size(); i++) {
        if (m_tail[i] == coord)
            return true;
    }

    if (m_head == coord)
        return true;

    return false;
}

void Snake::move(Direction dir)
{
    // calculate next head
    COORD next{ m_head };
    switch (dir)
    {
    case Direction::Right:
        next.X = m_head.X + 1;
        next.Y = m_head.Y;
        break;

    case Direction::Left:
        next.X = m_head.X - 1;
        next.Y = m_head.Y;
        break;

    case Direction::Up:
        next.X = m_head.X;
        next.Y = m_head.Y - 1;
        break;

    case Direction::Down:
        next.X = m_head.X;
        next.Y = m_head.Y + 1;
        break;
    }

    if (this->isBorderCollision(next))
        return;  // don't move snake

    if (this->hits(next))
        return;  // don't move snake

    // move snake in-place
    for (size_t i = 1; i != m_tail.size(); i++)
        m_tail[i - 1] = m_tail[i];
    m_tail[m_tail.size() - 1] = m_head;

    // set new head
    m_head = next;
}

// private helper methods
bool Snake::isBorderCollision(COORD coord)
{
    // handle collision with border
    if (coord.X == 0 || coord.X == GameConsole::Width - 1)
        return true;
    if (coord.Y == 0 || coord.Y == GameConsole::Height - 1)
        return true;

    return false;
}

// helper function
bool operator== (const COORD & coord1, const COORD & coord2)
{
    return coord1.X == coord2.X && coord1.Y == coord2.Y;
}

// =====================================================================================
// End-of-File
// =====================================================================================
