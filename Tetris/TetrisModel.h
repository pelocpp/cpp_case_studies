#pragma once

class TetrisModel : public ITetrisModel { 

private:
    ITetrisBoard*                m_board;      // tetris game area
    std::unique_ptr<ITetrimino>  m_tetromino;  // current tetromino
    std::future<bool>            m_gameLoop;   // internal game loop

   // TetrisState m_state;     // current state of model

    std::deque<TetrisActionEx>   m_actions;   // internal game loop

public:
    TetrisModel();
    ~TetrisModel();

    // properties
    int getNumRows() override;
    int getNumCols() override;

    //void setState(TetrisState state) override;
    //TetrisState getState() override;

    void pushAction(TetrisActionEx) override;
    void addActions(const std::deque<TetrisActionEx>&) override;
    TetrisActionEx popAction() override;

    // tetrimino management
    void createNextTetrimino() override;

    // action requests (internally and externally initiated)
    void doActionSetToTop() override;
    void doActionMoveRight() override;
    void doActionMoveLeft() override;
    void doActionMoveDown() override;
    void doActionAtBottom() override;
    void doActionGameOver() override;

    // implementation of interface 'ITetrisBoardListener'
    void attach(ITetrisBoardObserver* observer) override;
    void detach(ITetrisBoardObserver* observer) override;
    void notifyAll(const ViewCellList& list) override;

private:
    // internal helper methods
    void start() override;
    bool run() override;
    void join() override;
};
