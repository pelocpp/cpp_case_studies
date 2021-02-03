// =====================================================================================
// Coordinate.cpp
// =====================================================================================

#include <iostream>

#include "Coordinate.h"

// public interface
Coordinate Coordinate::fromOffset(size_t rowOfs, size_t colOfs) const noexcept {
    return { m_row + rowOfs, m_col + colOfs };
}

std::ostream& operator<< (std::ostream& os, const Coordinate& coord) {
    os << "{" << coord.m_row << "," << coord.m_col << "}";
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
