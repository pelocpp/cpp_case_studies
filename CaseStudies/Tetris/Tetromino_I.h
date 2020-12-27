#pragma once

class Tetromino_I : public Tetromino {

public:
    Tetromino_I(ITetrisBoard* board);

    // predicates
    bool canSetToTop() override;
    bool canMoveLeft() override;
    bool canMoveRight() override;
    bool canMoveDown() override;
    bool canRotate() override;
    bool isCoordinateWithin(int row, int col) override;

    // public interface
    void update(CellState state) override;
    void updateCellList(ViewCellList&, const CellColor&) override;
};
