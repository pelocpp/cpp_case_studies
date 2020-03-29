#pragma once

class TetrisGame : public ITetrisBoardObserver, public IKeyboardObserver {
public:
    // c'tor(s)/d'tor
    TetrisGame();
    ~TetrisGame();

    // public interface
    void init();
    void start();
    void join();
    void stop();

private:

    IUISubsystem* m_subsystem;
    
    // WOZU ist das ein Zeiger !!! überflüssig
    ITetrisModel* m_model;

    // implementation of interface 'ITetrisBoardObserver'
    void update(const ViewCellList&) override;

    // implementation of interface 'IKeyboardObserver'
    void update(std::deque<unsigned short>) override;

public:
    static unsigned int toWin32Color(CellColor);
};