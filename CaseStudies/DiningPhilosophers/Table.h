// ===========================================================================
// Table.h
// ===========================================================================

#pragma once

#include <array>
#include <atomic>

#include "DiningPhilosophers.h"
#include "Fork.h"

class Table
{
private:
    std::array<Fork, NumPhilosophers> m_forks;
    std::atomic<int> m_numForksInUse;

public:
    Table();

    // index operator
    Fork& operator[] (size_t index);

    // public interface
    void incrementNumForks();
    void decrementNumForks();
    int numForks() const;
};

// ===========================================================================
// End-of-File
// ===========================================================================
