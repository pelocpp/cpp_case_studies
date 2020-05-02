#pragma once

class TetrisModel : public ITetrisModel { 

private:
    ITetrisBoard*                m_board;      // tetris game area
    std::unique_ptr<ITetromino>  m_tetromino;  // current tetromino
    std::future<bool>            m_gameLoop;   // internal game loop

   // TetrisState m_state;     // current state of model

    std::deque<TetrisAction>    m_actions;    // queue of pending actions 

 //   std::priority_queue<TetrisActionPair> m_actionsPQ;    // priority queue of pending actions 

    TetrisState m_state;


    TetrisQueue<TetrisActionPair> m_actionsPQ2;    // priority queue of pending actions
    std::mutex m_mutex;  // protect priority queue against concurrent access


    // TODO: Den Comparer schreiben !!! so dass die Prio stimmt !!!!!!

public:
    TetrisModel();
    ~TetrisModel();

    // properties
    int getNumRows() override;
    int getNumCols() override;

    void setState(TetrisState state) override;
    TetrisState getState() override;

    // void pushAction(TetrisAction) override;
    void pushAction(const TetrisActionPair&) override;
    void addActions(const std::deque<TetrisAction>&) override;
    std::deque<TetrisAction> getActions() override;
   // TetrisAction popAction() override;

    // tetromino management
    void createNextTetromino() override;

    // action requests (internally and externally initiated)
    void doActionSetToTop() override;

    void doActionMoveRight() override;
    void doActionMoveLeft() override;
    void doActionMoveDown() override;
    void doActionAtBottom() override;
    void doActionGameOver() override;

    void doActionSetToTopEx();
    void doActionMoveDownEx();
    void doActionAtBottomEx();
    void doActionGameOverEx();

    // implementation of interface 'ITetrisBoardListener'
    void attach(ITetrisBoardObserver* observer) override;
    void detach(ITetrisBoardObserver* observer) override;
    void notifyAll(const ViewCellList& list) override;

private:
    // internal helper methods
    void start() override;
    bool run() override;
    bool runRevised() override;

    void join() override;
};
