#pragma once

class TetrisModel : public ITetrisModel { 

private:
    ITetrisBoard* m_board;   // tetris game area
    ITetrimino* m_curr;      // current tetrimino
    TetrisState m_state;     // current state of model

    // ERSTE ANSÄTZE FÜR EINEN WORKER THREAD
    std::future<bool>        m_futureGameLoop;

public:
    TetrisModel();
    ~TetrisModel();

    int getNumRows() override;
    int getNumCols() override;

    void start() override;
    bool play() override;   // TODO: Der Name ist auch im Game vorhanden !?!?!?!
    void stop() override;

    void setState(TetrisState state) override;
    TetrisState getState() override;

    ITetrimino* attachTetrimino() override;
    void detachTetrimino() override;

    // action requests (internally and externally initiated)
    void doActionSetToTop();
    void doActionMoveDown();
    void doActionAtBottom();
    void doActionGameOver();
};
