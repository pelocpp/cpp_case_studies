// =====================================================================================
// CollatzIterator.cpp
// =====================================================================================

#include <iostream>

#include "CollatzIterator.h"

// c'tor
CollatzIterator::CollatzIterator(int start) : m_start{ start }, m_current{ start } {}

// operator(s)
int CollatzIterator::operator*() const { return m_current; }

CollatzIterator& CollatzIterator::operator++() {

    m_last = m_current;

    m_current = (m_current % 2 == 0)
        ? m_current = m_current / 2
        : m_current = 3 * m_current + 1;

    return *this;
}

bool CollatzIterator::operator!=(const CollatzIterator& seq) const
{ 
    // return m_current != seq.m_current;
    return m_last != seq.m_current;
}

// =====================================================================================
// End-of-File
// =====================================================================================
