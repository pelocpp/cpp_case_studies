// =====================================================================================
// JosephusListImpl.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <forward_list>

#include "Soldier.h"
#include "IJosephus.h"
#include "Josephus.h"
#include "JosephusListImpl.h"

// c'tors
JosephusListImpl::JosephusListImpl() : JosephusListImpl{ NumSoldiers, DefaultPassBy } {}

JosephusListImpl::JosephusListImpl(size_t count, size_t passby) : Josephus{ count, passby } {
    initScenario();
}

// private helper methods
void JosephusListImpl::initScenario()
{
    for (size_t i = 0; i != m_count; ++i) {
        m_soldiers.push_front(Soldier{ m_count - i });
    }

    m_current = m_soldiers.begin();
}

bool JosephusListImpl::eliminateNextSoldier()
{
    // more than one soldier alive?
    if (m_alive == 1)
        return false;

    // locate next soldier
    std::forward_list<Soldier>::iterator preceding;

    for (size_t i = 0; i != m_passby - 1; ++i) {

        preceding = m_current;
        ++m_current;

        if (m_current == m_soldiers.end()) {
            preceding = m_soldiers.before_begin();
            m_current = m_soldiers.begin();
        }
    }

    m_lastEliminated = (*m_current).getNumber();

    ++m_current;
    if (m_current == m_soldiers.end()) {
        m_current = m_soldiers.begin();
    }

    // remove soldier from list
    m_soldiers.erase_after(preceding);
    m_alive--;

    return true;
}

// output
std::ostream& operator<< (std::ostream& os, const JosephusListImpl& josephus)
{
    os << '[';
    for (size_t i = 1; const Soldier & soldier : josephus.m_soldiers) {
        os << soldier();
        if (i < josephus.m_alive) {
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
