#include <iostream>
#include <string>

#include "CellColor.h"
#include "CellPoint.h"
#include "ViewCell.h"

// c'tors
ViewCell::ViewCell() : m_color(CellColor::LightGray) {}
ViewCell::ViewCell(CellColor color, CellPoint point) : m_color(color), m_point(point) {}

// getter/setter
CellColor ViewCell::getColor() { return m_color; }
void ViewCell::setColor(CellColor color) { m_color = color; }
CellPoint ViewCell::getPoint() { return m_point; }
void ViewCell::setPoint(CellPoint point) { m_point = point; }
