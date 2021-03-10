// =====================================================================================
// JosephusArrayImpl.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <array>

#include "Soldier.h"
#include "IJosephus.h"
#include "Josephus.h"
#include "JosephusArrayImpl.h"

// c'tors
JosephusArrayImpl::JosephusArrayImpl() : JosephusArrayImpl{ NumSoldiers, DefaultPassBy } {}

JosephusArrayImpl::JosephusArrayImpl(size_t count, size_t passby) : Josephus{ count, passby } {
    initScenario();
}

// private helper methods
void JosephusArrayImpl::initScenario()
{
    for (bool& entry : m_soldiers) {
        entry = true;
    }

    m_current = 0;
}

void JosephusArrayImpl::moveToNextAliveSoldier()
 {
    while (m_soldiers[m_current] == false) {
        nextIndex(); // move index to next entry
    }
}

void JosephusArrayImpl::nextIndex()
{
    // move index to next entry
    m_current++;
    if (m_current >= m_count) {
        m_current = 0;
    }
}

// getter/setter
size_t JosephusArrayImpl::lastAlive() const { return m_lastAlive; }


// ??????????????????????????????????????????
//size_t JosephusArrayImpl::lastAlive() const
//{
//    std::array<bool, NumSoldiers>::const_iterator it = std::find_if(std::begin(m_soldiers), std::end(m_soldiers), [](bool b) { return b == true; });
//
//    m_lastAlive = it - std::begin(m_soldiers);
//    //if (m_lastAlive == 0) {
//    //    moveToNextAliveSoldier();
//    //    m_lastAlive = m_current + 1;
//    //}
//
//    //return m_lastAlive;
//}

size_t JosephusArrayImpl::LAST_ALIVE()
{
    std::array<bool, NumSoldiers>::iterator it = std::find_if(
        std::begin(m_soldiers),
        std::end(m_soldiers), 
        [](bool b) {
            return b == true;
        });
    m_lastAlive = it - std::begin(m_soldiers) + 1;
    return m_lastAlive;
}

bool JosephusArrayImpl::eliminateNextSoldier()
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
std::ostream& operator<< (std::ostream& os, const JosephusArrayImpl& j)
{
    os << '[';
    for (size_t i = 1; const Soldier & soldier : j.m_soldiers) {
        os << soldier();
        if (i < j.m_alive) {
            os << ',';
            ++i;
        }
    }
    os << ']';
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
