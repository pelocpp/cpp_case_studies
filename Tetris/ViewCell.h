#pragma once

class ViewCell {

private:
    CellPoint m_point;
    CellColor m_color;

public:
    // c'tors
     ViewCell();
     ViewCell(CellPoint point, CellColor color);

    // getter/setter
    CellColor getColor() const noexcept;
    void setColor(CellColor color) noexcept;
    CellPoint getPoint() const noexcept;
    void setPoint(CellPoint point) noexcept;
};