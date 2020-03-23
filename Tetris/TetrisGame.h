class TetrisGame {
public:
    // c'tor(s)
    TetrisGame();

    // public interface
    void play();

private:
    IUISubsystem* m_subsystem;
};