#include <iostream>
#include <string> 
#include <sstream> 

#include "CellPoint.h"

// c'tors
// TODO: ist das mit -1,- 1eine gute Wahl ????
CellPoint::CellPoint() :CellPoint (-1, -1) {};

CellPoint::CellPoint(int x, int y) : m_x(x), m_y(y) {}

// getter/setter
int CellPoint::getX() { return m_x; }
int CellPoint::getY() { return m_y; }
void CellPoint::setX(int x) { m_x = x; }
void CellPoint::setY(int y) { m_y = y; }

// operators
// TODO: muss der überschrieben weden ?? Value type
 //   public boolean equals(Object obj) {

bool operator== (const CellPoint& lhs, const CellPoint& rhs) {
    return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
}

// public interface
std::string CellPoint::tostring() {
    std::stringstream ss;
    ss << "X=" << m_x << ", Y=" << m_y;
    return ss.str();
}
