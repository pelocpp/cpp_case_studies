// =====================================================================================
// Coordinate.h
// =====================================================================================

#pragma once

#include <iostream>

class Coordinate {

    friend std::ostream& operator<< (std::ostream&, const Coordinate&);

public:
    Coordinate() = default;
    Coordinate(size_t row, size_t col) : m_row{ row }, m_col{ col } {}

public:
    // getter/setter
    inline size_t getRow() const noexcept { return m_row; }
    inline size_t getCol() const noexcept { return m_col; }

    // public interface
    Coordinate fromOffset(size_t rowOfs, size_t colOfs) const noexcept;

private:
    size_t m_row{};
    size_t m_col{};
};

// =====================================================================================
// End-of-File
// =====================================================================================
