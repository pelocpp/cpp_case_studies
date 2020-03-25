class TetrisGame {
public:
    // c'tor(s)/d'tor
    TetrisGame();
    ~TetrisGame();

    // public interface
    void play();

private:
    IUISubsystem* m_subsystem;
    ITetrisModel* m_model;
};