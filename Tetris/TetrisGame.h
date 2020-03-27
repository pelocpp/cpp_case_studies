#pragma once

class TetrisGame : public ITetrisBoardObserver {
public:
    // c'tor(s)/d'tor
    TetrisGame();
    ~TetrisGame();

    // public interface
    void init();
    void start();
    void join();

private:
    IUISubsystem* m_subsystem;
    ITetrisModel* m_model;

    // implementation of interface 'ITetrisBoardObserver'
    void update(const ViewCellList&) override;

public:
    static unsigned int toWin32Color(CellColor);
};