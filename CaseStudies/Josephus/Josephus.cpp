// =====================================================================================
// Josephus.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <forward_list>

#include "Soldier.h"
#include "Josephus.h"

// c'tors
Josephus::Josephus() : Josephus{ 17 } {}   // TODO :Beachte die Konstruktor Delegation

Josephus::Josephus(size_t count) : m_count{ count }, m_alive{ count }, m_lastEliminated {0 } {
    createLinkedList();
}

// private helper methods
void Josephus::createLinkedList()
{
    for (size_t i = 0; i != m_count; ++i) {
        m_soldiers.push_front(Soldier{ m_count - i });
    }

    m_current = m_soldiers.begin();
}

// output
std::ostream& operator<< (std::ostream& os, const Josephus& josephus)
{
    os << '[';

    // C++ 20: Da geht ein int i =0; JAAAAAAAAAAAAAAAAAAA
    for (size_t i = 0;  const Soldier& soldier : josephus.m_soldiers) {
        os << soldier() << ',';    // TO be done: Das letzte Komma ...............
    }

    os << ']';
    return os;
}



bool Josephus::eliminateNextSoldier()
{
    // more than one soldier?
    if (m_alive == 1)
        return false;

    // locate next soldier
    // TODO: ist das -1 hier richtig ?!?!?!
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
    // std::forward_list<Soldier>::iterator iter = m_soldiers.erase_after(m_current);
    // m_soldiers.erase_after(m_current);
    m_soldiers.erase_after(preceding);

    m_alive--;
    // m_lastEliminated = (*m_current).getNumber();

    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
