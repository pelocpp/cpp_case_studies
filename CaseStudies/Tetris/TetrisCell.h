#pragma once

class TetrisCell {
private:
    CellState m_state;
    CellColor m_color;

public:
    // c'tors
    TetrisCell();
    TetrisCell(CellState state, CellColor color);

    // getter/setter
    CellState getState();
    void setState(CellState state);
    CellColor getColor();
    void setColor(CellColor color);
};