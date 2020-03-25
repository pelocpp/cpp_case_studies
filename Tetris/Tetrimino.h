#pragma once

class Tetrimino : public ITetrimino {
public:
    Tetrimino(ITetrisBoard* board, CellColor color);

protected:
    ITetrisBoard* m_board;
    CellPoint m_anchorPoint;
    RotationAngle m_rotation;
    CellColor m_color;

    // predicates
    virtual bool canSetToTop() = 0;
    virtual bool canMoveLeft() = 0;
    virtual bool canMoveRight() = 0;
    virtual bool canMoveDown() = 0;
    virtual bool canRotate() = 0;
    virtual bool isCoordinateWithin(int row, int col) = 0;

public:
    // public interface (movement specific methods)
    void setToTop() override;
    void MoveLeft() override;
    void MoveRight() override;
    bool MoveDown() override;
    void Rotate() override;

    // board specific methods
    void set() override;
    void release() override;
};
