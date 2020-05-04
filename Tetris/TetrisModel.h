#pragma once

class TetrisModel : public ITetrisModel { 

private:
    ITetrisBoard*                m_board;      // tetris game area
    std::unique_ptr<ITetromino>  m_tetromino;  // current tetromino
    std::future<bool>            m_gameLoop;   // internal game loop

    TetrisState                  m_state;      // current state of model
    std::deque<TetrisAction>     m_actions;    // queue of pending actions 
    std::mutex                   m_mutex;      // protect queue against concurrent access
    std::condition_variable      m_condition;  // handle condition 'external event'

    int                          m_sleepTime;  // regular sleep time between two steps
    bool                         m_exitGame;   // user request 'exit game'

public:
    TetrisModel();
    ~TetrisModel();

    // properties
    int getNumRows() override;
    int getNumCols() override;

    void setState(TetrisState state) override;
    TetrisState getState() override;

    // void pushAction(TetrisAction) override;
    //void pushAction(const TetrisActionPair&) override;
    void pushActions(const std::deque<TetrisAction>&) override;
    std::deque<TetrisAction> getActions() override;
    void clearActions() override;
   // TetrisAction popAction() override;
    void waitForAction() override;

    // tetromino management
    void createNextTetromino() override;

    // action requests (internally and externally initiated)
    void doActionSetToTop() override;

    void doActionMoveRight() override;
    void doActionMoveLeft() override;
    void doActionRotate() override;
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
