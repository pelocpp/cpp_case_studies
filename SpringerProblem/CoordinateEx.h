// =====================================================================================
// CoordinateEx.h
// =====================================================================================


#pragma once

using Coordinate = std::pair<int, int>;

Coordinate makeCoord() {
    return { 0, 0 };
}

Coordinate makeCoord(int row, int col) {
    return { row, col };
}

Coordinate fromOffset(const Coordinate& coord, int rowOfs, int colOfs) {
    return { std::get<0>(coord) + rowOfs, std::get<1>(coord) + colOfs };
}

inline int getRow(const Coordinate& coord) { return std::get<0>(coord); }
inline int getCol(const Coordinate& coord) { return std::get<1>(coord); }

std::ostream& operator<< (std::ostream& os, const Coordinate& coord) {
    os << "(" << std::get<0>(coord) << "," << std::get<1>(coord) << ")";
    return os;
}


// =====================================================================================
// End-of-File
// =====================================================================================
