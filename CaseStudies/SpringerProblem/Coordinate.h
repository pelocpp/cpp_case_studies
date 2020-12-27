// =====================================================================================
// Coordinate.h
// =====================================================================================

#pragma once

#include <iostream>
template <typename T>
class Coordinate {

public:
    Coordinate() : Coordinate(T{}, T{}) {};
    Coordinate(T row, T col) : m_row{ row }, m_col{ col } {}

public:
    // getter/setter
    inline T getRow() const noexcept { return m_row; }
    inline T getCol() const noexcept { return m_col; }

    // public interface
    Coordinate<T> fromOffset(T rowOfs, T colOfs) const noexcept {
        return { static_cast<T>(m_row + rowOfs), static_cast<T>(m_col + colOfs) };
    }

private:
    T m_row;
    T m_col;
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, const Coordinate<T>& coordinate) {
    os << "(" << coordinate.getRow() << "," << coordinate.getCol() << ")";
    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================