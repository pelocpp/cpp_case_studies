#pragma once

class Coordinate {

    friend std::ostream& operator<< (std::ostream&, const Coordinate&);

public:
    Coordinate();
    Coordinate(int, int);
    Coordinate(const Coordinate&) = default;  //TODO: ?????????

    // move semantics
    //Coordinate(Coordinate&&) = default; //TODO: ?????????
    //Coordinate& operator= (Coordinate&&) = default; //TODO: ?????????

public:
    // getter/setter
    inline int getRow() const { return m_row; }
    inline int getCol() const { return m_col; }

    // public interface
    Coordinate fromOffset(int rowOfs, int colOfs) const;

private:
    int m_row;
    int m_col;
};
