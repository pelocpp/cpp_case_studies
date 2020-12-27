#include "CellColor.h"
#include "CellState.h"

#include "TetrisCell.h"

// c'tors
TetrisCell::TetrisCell() : TetrisCell (CellState::Free, CellColor::LightGray) {}

TetrisCell::TetrisCell(CellState state, CellColor color) {
    m_state = state;
    m_color = color;
}

// getter/setter
CellState TetrisCell::getState() {
    return m_state;
}

void TetrisCell::setState(CellState state) {
    m_state = state;
}

CellColor TetrisCell::getColor() {
    return m_color;
}

void TetrisCell::setColor(CellColor color) {
    m_color = color;
}
