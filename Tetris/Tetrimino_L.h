#pragma once

class Tetrimino_L : public Tetrimino {

public:
    Tetrimino_L(ITetrisBoard* board);

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
