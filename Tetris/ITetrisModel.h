#pragma once

class ITetrisModel : public ITetrisBoardListener {
public:
    // properties
    virtual int getNumRows() = 0;
    virtual int getNumCols() = 0;

    // game commands
    virtual void start() = 0;
    virtual bool run() = 0;
    virtual void join() = 0;

    //virtual void setState(TetrisState state) = 0;
    //virtual TetrisState getState() = 0;

    //virtual void pushAction(TetrisAction) = 0;
    //virtual void addActions(const std::deque<TetrisAction>&) = 0;
    //virtual TetrisAction popAction() = 0;

    virtual void pushAction(const TetrisActionPair&) = 0;
    virtual void addActions(const std::deque<TetrisAction>&) = 0;
    virtual TetrisAction popAction() = 0;

    // action requests (internally and externally initiated)
    virtual void doActionSetToTop() = 0;
    virtual void doActionMoveRight() = 0;
    virtual void doActionMoveLeft() = 0;
    virtual void doActionMoveDown() = 0;
    virtual void doActionAtBottom() = 0;
    virtual void doActionGameOver() = 0;

    // tetromino management
    virtual void createNextTetromino() = 0;
};
