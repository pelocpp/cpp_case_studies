#include <iostream>
#include <string>

#include "CellColor.h"
#include "CellPoint.h"
#include "ViewCell.h"

// c'tors
ViewCell::ViewCell() : m_color(CellColor::LightGray) {}
ViewCell::ViewCell(CellPoint point, CellColor color) : m_point(point), m_color(color) {}

// getter/setter
CellColor ViewCell::getColor() const noexcept { return m_color; }
void ViewCell::setColor(CellColor color) noexcept { m_color = color; }
CellPoint ViewCell::getPoint() const noexcept { return m_point; }
void ViewCell::setPoint(CellPoint point) noexcept { m_point = point; }
