#pragma once

class ITetrimino {

public:
    // TODO : was muss hier public -- was kann protected sein ?!?!

    // TODO : Alle Methoden mit Kleinbúchstaben am Anfang !!!

    // predicates
    virtual bool canSetToTop() = 0;
    virtual bool canMoveLeft() = 0;
    virtual bool canMoveRight() = 0;
    virtual bool canMoveDown() = 0;
    virtual bool canRotate() = 0;
    virtual bool isCoordinateWithin(int row, int col) = 0;

    // movement specific methods
    virtual void setToTop() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual bool MoveDown() = 0;
    virtual void Rotate() = 0;

    // board specific methods
    virtual void set() = 0;
    virtual void release() = 0;

    virtual void update(CellState state) = 0;
};