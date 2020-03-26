#pragma once

class Tetrimino_L : public Tetrimino {

public:
    Tetrimino_L(ITetrisBoard* board);

public:
    // predicates
    bool canSetToTop() override;
    bool canMoveLeft() override;
    bool canMoveRight() override;
    bool canMoveDown() override;
    bool canRotate() override;


protected:
    bool isCoordinateWithin(int row, int col) override;

    void update(CellState state) override;
    void updateCellList(ViewCellList&, const CellColor&) override;
};
