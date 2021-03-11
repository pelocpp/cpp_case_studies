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
    init();
}

// public interface
bool JosephusArrayImpl::eliminateNextSoldier()
{
    // more than one soldier alive?
    if (m_alive == 1) {
        return false;
    }

    for (int i = 0; i < m_passby - 1; i++) {
        moveToNextAliveSoldier();
        nextIndex();  // skip found alive soldier
    }

    moveToNextAliveSoldier();

    // kill 'n'.th soldier
    m_soldiers[m_current] = false;
    m_alive--;
    m_lastEliminated = m_current + 1;

    // compute index of last alive soldier
    if (m_alive == 1) {

        std::array<bool, NumSoldiers>::iterator it = std::find_if(
            std::begin(m_soldiers),
            std::end(m_soldiers),
            [](bool b) {
                return b == true;
            }
        );

        m_lastAlive = it - std::begin(m_soldiers) + 1;
    }

    return true;
}

// private helper methods
void JosephusArrayImpl::init()
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

// output
std::ostream& operator<< (std::ostream& os, JosephusArrayImpl& j)
{
     os << '[';
     size_t save = j.m_current;  // save current state of position index
     j.m_current = 0;

     int count = 0;
     do {
         j.moveToNextAliveSoldier();
         os << (j.m_current + 1);

         count++;
         if (count < j.alive())
             os << ',';
         
         j.nextIndex();
     }
     while (count < j.alive());

     os << ']';
     j.m_current = save;  // restore current state of position index
     return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
