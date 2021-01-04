// =====================================================================================
// CollatzSequence.cpp
// =====================================================================================

#include <iostream>
#include <string>

#include "CollatzIterator.h"
#include "CollatzSequence.h"

// c'tor(s)
CollatzSequence::CollatzSequence(int start) : m_start{ start } {}

// iterator support
CollatzIterator CollatzSequence::begin() const { return { m_start }; }
CollatzIterator CollatzSequence::end()   const { return { 1 }; }

// =====================================================================================
// End-of-File
// =====================================================================================
