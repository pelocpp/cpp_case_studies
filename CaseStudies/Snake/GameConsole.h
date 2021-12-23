// =====================================================================================
// GameConsole.h
// =====================================================================================

class GameConsole
{
public:
    static constexpr int Width = 40;
    static constexpr int Height = 10;

private:
    // some classic 'box-drawing characters'
    static constexpr char Box_Left_Upper = ((char)201);   // TODO \xnn
    static constexpr char Box_Right_Upper = ((char)187);
    static constexpr char Box_Left_Lower = ((char)200);
    static constexpr char Box_Right_Lower = ((char)188);
    static constexpr char Box_Horiz = ((char)205);
    static constexpr char Box_Vert = ((char)186);

private:
    HANDLE m_hStdin;
    HANDLE m_hStdout;

    WORD m_lastVirtualKey;
    Direction m_lastValidArrow;
    bool m_isEscapeHit;

    public:
    // c'tor / d'tor
    GameConsole();
    ~GameConsole();

    // getter
    bool isInputAvailable();
    bool isEscapeHit() const;

    // public interface
    void setup();

    // public interface: input
    Direction isLastValidArrow() const;
    void readInput();

    // public interface: output
    void clear();
    void drawBorder();
    void writeAt(char ch, const COORD& coord);
};

// =====================================================================================
// End-of-File
// =====================================================================================
