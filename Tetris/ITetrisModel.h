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

    virtual void pushAction(TetrisActionEx) = 0;
    virtual TetrisActionEx popAction() = 0;

    // action requests (internally and externally initiated)
    virtual void doActionSetToTop() = 0;
    virtual void doActionMoveDown() = 0;
    virtual void doActionAtBottom() = 0;
    virtual void doActionGameOver() = 0;

    // tetrimino management
    virtual void createNextTetrimino() = 0;
};
