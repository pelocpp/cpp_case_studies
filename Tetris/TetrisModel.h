#pragma once

class TetrisModel : public ITetris {

public:
    int getNumRows() override;
    int getNumCols() override;
};
