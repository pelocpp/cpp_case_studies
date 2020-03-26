class ViewCell {

private:
    CellColor m_color;
    CellPoint m_point;

public:
    // c'tors
     ViewCell();
     ViewCell(CellColor color, CellPoint point);

    // getter/setter
    CellColor getColor();
    void setColor(CellColor color);
    CellPoint getPoint();
    void setPoint(CellPoint point);
};