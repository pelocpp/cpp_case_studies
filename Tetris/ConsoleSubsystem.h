#pragma once

class ConsoleSubsystem : public IUISubsystem {

private:
    // some classic 'box-drawing characters'
    static const char Box_Left_Upper = ((char)201);
    static const char Box_Right_Upper = ((char)187);
    static const char Box_Left_Lower = ((char)200);
    static const char Box_Right_Lower = ((char)188);
    static const char Box_Horiz = ((char)205);
    static const char Box_Vert = ((char)186);

private:
    int m_width;
    int m_height;

    HANDLE m_hStdin;
    HANDLE m_hStdout;

    // snake stuff ?!=?!?!?!
    WORD m_lastVirtualKey;
    Direction m_lastValidArrow;
    bool m_isEscapeHit;

public:
    // c'tor(s)
    ConsoleSubsystem(int width, int height);

    // properties
    int getWidth() override;
    int getHeight() override;

    // public interface
    void initConsole() override;
    void showConsole() override;
    void closeConsole() override;

    // getter
    bool isInputAvailable() override;
    bool isEscapeHit() override;

private:
    void writeAt(char ch, COORD coord);
    void drawBorder();
};