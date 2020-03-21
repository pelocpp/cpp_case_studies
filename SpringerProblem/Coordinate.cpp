#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>

#include "Coordinate.h"

Coordinate::Coordinate() : Coordinate(0, 0) {};

Coordinate::Coordinate(int row, int col) : m_row{ row }, m_col{ col } {}

Coordinate Coordinate::fromOffset(int rowOfs, int colOfs) const {

    return { m_row + rowOfs, m_col + colOfs };
}

std::ostream& operator<< (std::ostream& os, const Coordinate& coordinate) {
    os << "(" << coordinate.m_row << "," << coordinate.m_col << ")";
    return os;
}
