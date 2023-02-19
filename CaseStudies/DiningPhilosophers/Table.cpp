// ===========================================================================
// Table.cpp
// ===========================================================================

#include "DiningPhilosophers.h"
#include "Table.h"

Table::Table() : m_numForksInUse{} {}

Fork& Table::operator[] (size_t index)
{
    size_t seat{ index % 5 };
    return m_forks[seat];
}

void Table::incrementNumForks() {
    m_numForksInUse.fetch_add(2);
}

void Table::decrementNumForks() {
    m_numForksInUse.fetch_sub(2);
}

int Table::numForks() const {
    return m_numForksInUse.load();
}

// ===========================================================================
// End-of-File
// ===========================================================================
