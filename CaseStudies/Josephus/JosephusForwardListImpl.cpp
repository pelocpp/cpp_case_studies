// =====================================================================================
// JosephusListImpl.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <forward_list>

#include "Soldier.h"
#include "IJosephus.h"
#include "Josephus.h"
#include "JosephusForwardListImpl.h"

// c'tors
JosephusForwardListImpl::JosephusForwardListImpl() 
    : JosephusForwardListImpl{ NumSoldiers, DefaultPassBy } {}

JosephusForwardListImpl::JosephusForwardListImpl(size_t count, size_t passby)
    : Josephus{ count, passby } {
    init();
}

// public interface
bool JosephusForwardListImpl::eliminateNextSoldier()
{
    // more than one soldier alive?
    if (m_alive == 1) {
        return false;
    }

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

    // compute index of last alive soldier
    if (m_alive == 1) {
        m_lastAlive = (*m_current).getNumber();
    }

    return true;
}

// private helper methods
void JosephusForwardListImpl::init()
{
    for (size_t i = 0; i != m_count; ++i) {
        m_soldiers.push_front(Soldier{ m_count - i });
    }

    m_current = m_soldiers.begin();
}

// output
std::ostream& operator<< (std::ostream& os, const JosephusForwardListImpl& josephus)
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
