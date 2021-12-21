// =====================================================================================
// XXX.cpp
// =====================================================================================

#include <windows.h>

#include "Direction.h"
#include "GameConsole.h"
#include "Snake.h"
#include "Food.h"

// c'tor
Snake::Snake()
{
    m_len = 4;
    m_tail = new COORD[m_len];

    for (int i = 0; i < m_len; i++)
    {
        COORD coord;
        coord.X = GameConsole::Width / 2 + i;
        coord.Y = GameConsole::Height / 2;
        m_tail[i] = coord;
    }

    m_head.X = GameConsole::Width / 2 + 4;
    m_head.Y = GameConsole::Height / 2;
}

Snake::Snake(const Snake & snake)
{
    m_head = snake.m_head;
    m_tail = new COORD[snake.m_len];
    for (int i = 0; i < snake.m_len; i++)
        m_tail[i] = snake.m_tail[i];
    m_len = snake.m_len;
}

 // d'tor
Snake::~Snake()
{
    delete[] m_tail;
}

 // getter
COORD Snake::Head()
{
    return m_head;
}

void Snake::Draw(GameConsole & console) const
{
    // clear snake's tail ...
    COORD tail = m_tail[0];
    console.WriteAt(' ', tail);

    // just draw element after head ...
    COORD last = m_tail[m_len - 1];
    console.WriteAt('*', last);

    // ... and head itself
    console.WriteAt('O', m_head);
}

void Snake::Grow(COORD coord)
{
    COORD * tmp = new COORD[m_len + 1];

    // copy old coordinates in new buffer
    for (int i = 0; i < m_len; i++)
        tmp[i + 1] = m_tail[i];

    // last head gets new begin of tail
    m_tail[0] = m_head;

    // set new head
    m_head = coord;

    // delete old buffer
    delete[] m_tail;

    // and switch to new buffer
    m_tail = tmp;
    m_len++;
}

bool Snake::Hits(COORD coord) const
{
    for (int i = 0; i < m_len; i++)
        if (m_tail[i] == coord)
            return true;

    if (m_head == coord)
        return true;

    return false;
}

void Snake::Move(Direction dir)
{
    // calculate next head
    COORD next = m_head;
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

    if (this->IsBorderCollision(next))
        return;  // don't move snake

    if (this->Hits(next))
        return;  // don't move snake

    // move snake in-place
    for (int i = 1; i < m_len; i++)
        m_tail[i - 1] = m_tail[i];
    m_tail[m_len - 1] = m_head;

    // set new head
    m_head = next;
}

// private helper methods
bool Snake::IsBorderCollision(COORD coord)
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
