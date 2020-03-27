class ViewCell {

private:
    CellPoint m_point;
    CellColor m_color;

public:
    // c'tors
     ViewCell();
     ViewCell(CellPoint point, CellColor color);

    // getter/setter
    CellColor getColor() noexcept;
    void setColor(CellColor color) noexcept;
    CellPoint getPoint() noexcept;
    void setPoint(CellPoint point) noexcept;
};