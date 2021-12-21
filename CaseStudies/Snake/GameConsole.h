// =====================================================================================
// GameConsole.h
// =====================================================================================

class GameConsole
{
public:
    static const int Width = 40;
    static const int Height = 10;

private:
    // some classic 'box-drawing characters'
    static const char Box_Left_Upper = ((char)201);
    static const char Box_Right_Upper = ((char)187);
    static const char Box_Left_Lower = ((char)200);
    static const char Box_Right_Lower = ((char)188);
    static const char Box_Horiz = ((char)205);
    static const char Box_Vert = ((char)186);

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
    bool InputAvailable();
    bool IsEscapeHit();

    // public interface
    void Setup();

    // public interface: input
    Direction LastValidArrow();
    void ReadInput();

    // public interface: output
    void Clear();
    void DrawBorder();
    void WriteAt(char ch, COORD coord);
};

// =====================================================================================
// End-of-File
// =====================================================================================
