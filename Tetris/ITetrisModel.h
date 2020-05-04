#pragma once

class ITetrisModel : public ITetrisBoardListener {
public:
    // properties
    virtual int getNumRows() = 0;
    virtual int getNumCols() = 0;
    virtual void setState(TetrisState state) = 0;
    virtual TetrisState getState() = 0;

    // game commands
    virtual void start() = 0;
    virtual bool run() = 0;
    virtual void join() = 0;

    // manage incoming requests (keyboard)
    virtual void pushActions(const std::deque<TetrisAction>&) = 0;
    virtual std::deque<TetrisAction> getActionsNoOwnership() = 0;
    virtual void clearActions() = 0;
    virtual void waitForAction() = 0;

    // action requests (internally initiated)
    virtual void doActionSetToTop() = 0;
    virtual void doActionWayDown() = 0;
    virtual void doActionAtBottom() = 0;
    virtual void doActionGameOver() = 0;

    // action requests (externally initiated)
    virtual void doActionMoveRight() = 0;
    virtual void doActionMoveLeft() = 0;
    virtual void doActionRotate() = 0;
    virtual void doActionMoveDown() = 0;

private:
    // tetromino management
    virtual void createNextTetromino() = 0;
};
