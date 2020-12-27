#include <iostream>
#include <string> 
#include <sstream> 

#include "CellPoint.h"

// c'tors
// TODO: ist das mit -1,- 1 eine gute Wahl ????
CellPoint::CellPoint() :CellPoint (-1, -1) {};

CellPoint::CellPoint(int x, int y) : m_x(x), m_y(y) {}

// getter/setter
int CellPoint::getX() { return m_x; }
int CellPoint::getY() { return m_y; }

// operators
bool operator== (const CellPoint& lhs, const CellPoint& rhs) {
    return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
}

// public interface
void CellPoint::moveLeft() noexcept {
    --m_x;
}

void CellPoint::moveRight() noexcept {
    ++m_x;
}

void CellPoint::moveDown() noexcept {
    ++m_y;
}

std::string CellPoint::toString() {
    std::ostringstream ss;
    ss << "X=" << m_x << ", Y=" << m_y;
    return ss.str();
}