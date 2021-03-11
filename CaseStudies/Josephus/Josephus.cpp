// =====================================================================================
// Josephus.cpp
// =====================================================================================

#include <iostream>

#include "IJosephus.h"
#include "Josephus.h"

// c'tors
Josephus::Josephus() : Josephus{ NumSoldiers, DefaultPassBy } {}

Josephus::Josephus(size_t count, size_t passby) 
    : m_count{ count }, m_alive{ count }, m_passby{ passby } {}

void Josephus::eliminateAll()
{
    while (eliminateNextSoldier())
        ;
}

// =====================================================================================
// End-of-File
// =====================================================================================
