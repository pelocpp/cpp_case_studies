#pragma once

class ITetromino {

public:
    // TODO : was muss hier public -- was kann protected sein ?!?!

    // TODO : Alle Methoden mit Kleinbuchstaben am Anfang !!!

    // predicates
    virtual bool canSetToTop() = 0;
    virtual bool canMoveLeft() = 0;
    virtual bool canMoveRight() = 0;
    virtual bool canMoveDown() = 0;
    virtual bool canRotate() = 0;
    virtual bool isCoordinateWithin(int row, int col) = 0;   // TODO: Diese Routine ist bei Android nicht dabei !!!!

    // movement specific methods
    virtual void setToTop() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveDown() = 0;
    virtual void Rotate() = 0;

    // board specific methods
    virtual void set() = 0;
    virtual void release() = 0;

    virtual void update(CellState state) = 0;
    virtual void updateCellList(ViewCellList&, const CellColor&) = 0;
};