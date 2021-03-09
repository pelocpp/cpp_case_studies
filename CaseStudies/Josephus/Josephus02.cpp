// =====================================================================================
// JosephusEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <array>

#include "Soldier.h"
#include "JosephusEx.h"

// c'tors
JosephusEx::JosephusEx() {}

//JosephusEx::JosephusEx(size_t count) : m_count{ count }, m_alive{ count } {
//    initScenario();
//}

// private helper methods
void JosephusEx::initScenario()
{
    //for (size_t i = 0; i != m_count; ++i) {
    //    m_soldiers.push_front(Soldier{ m_count - i });
    //}

    for (bool& entry : m_soldiers) {
        entry = true;
    }

    m_current = 0;
}

void JosephusEx::moveToNextAliveSoldier()
 {
    while (m_soldiers[m_current] == false) {
        nextIndex(); // move index to next entry
    }

}

void JosephusEx::nextIndex()
{
    // move index to next entry
    m_current++;
    if (m_current >= m_count) {
        m_current = 0;
    }
}

size_t JosephusEx::lastAlive()
{
    if (m_lastAlive == 0) {
        moveToNextAliveSoldier();
        m_lastAlive = m_current + 1;
    }

    return m_lastAlive;
}

bool JosephusEx::eliminateNextSoldier()
{
    // more than one soldier alive?
    if (m_alive == 1)
        return false;

    for (int i = 0; i < m_passby - 1; i++) {
        moveToNextAliveSoldier();
        nextIndex();  // skip found alive soldier
    }

    moveToNextAliveSoldier();

    // kill 'n'.th soldier
    m_soldiers[m_current] = false;
    m_alive--;
    m_lastEliminated = m_current + 1;

    return true;
}

// output
std::ostream& operator<< (std::ostream& os, JosephusEx& j)
{
    //os << '[';
    //for (size_t i = 1; const Soldier & soldier : josephus.m_soldiers) {
    //    os << soldier();
    //    if (i < josephus.m_alive) {
    //        os << ',';
    //        ++i;
    //    }
    //}
    //os << ']';
    //return os;

    os << '[';
    size_t save = j.m_current;  // save current state of position index
    j.m_current = 0;

    size_t count = 0;
    do {
        j.moveToNextAliveSoldier();
        os << (j.m_current + 1);

        count++;
        if (count < j.alive()) {
            os << ',';
        }
        j.nextIndex();
    }
    while (count != j.alive());

    os << ']';
    j.m_current = save;  // restore current state of position index
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
