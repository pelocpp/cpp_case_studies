#pragma once

class Coordinate {

    friend std::ostream& operator<< (std::ostream&, const Coordinate&);

public:
    Coordinate();
    Coordinate(int, int);
    Coordinate(const Coordinate&) = default;

    // move semantics
    Coordinate(Coordinate&&) = default;
    Coordinate& operator= (Coordinate&&) = default;

public:
    // getter/setter
    inline int getRow() const { return m_row; }
    inline int getCol() const { return m_col; }

private:
    int m_row;
    int m_col;
};

using Solution = std::vector<Coordinate>;
using ListSolutions = std::list<Solution>;