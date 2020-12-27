#pragma once

class Tetromino : public ITetromino {

public:
    Tetromino(ITetrisBoard* board, CellColor color);

protected:
    CellPoint m_anchorPoint;
    RotationAngle m_rotation;
    CellColor m_color;
    ITetrisBoard* m_board;

protected:
    // protected interface (anchor movement methods)
    void moveAnchorRight();
    void moveAnchorLeft();
    void moveAnchorDown();
    void rotateAnchor();

public:
    // public interface (movement specific methods)
    void setToTop() override;
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void rotate() override;

    // board specific methods
    void set() override;
    void release() override;
};
