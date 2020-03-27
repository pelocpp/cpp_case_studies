#pragma once

class CellPoint {

private:
    int m_x;
    int m_y;

public:
    // c'tors
    CellPoint();
    CellPoint(int x, int y);

    // getter
    int getX();
    int getY();

    // operators
    friend bool operator== (const CellPoint&, const CellPoint&);

    // public interface
    void moveLeft() noexcept;
    void moveRight() noexcept;
    void moveDown() noexcept;
    std::string toString();
};