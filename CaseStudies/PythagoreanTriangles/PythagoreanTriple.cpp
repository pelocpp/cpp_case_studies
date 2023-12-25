// ===========================================================================
// PythagoreanTriple.cpp
// ===========================================================================

#include "PythagoreanTriple.h"

PythagoreanTriple::PythagoreanTriple()
    : PythagoreanTriple{ 0, 0, 0 }
{}

PythagoreanTriple::PythagoreanTriple(size_t x, size_t y, size_t z)
    : m_numbers{ x, y, z }
{}

size_t PythagoreanTriple::circumference() {

    return m_numbers[0] + m_numbers[1] + m_numbers[2];
}

std::string PythagoreanTriple::toString() {

    return std::format("[{:02},{:02},{:02}]",
        m_numbers[0], m_numbers[1], m_numbers[2]);
}

// ===========================================================================
// End-of-File
// ===========================================================================
