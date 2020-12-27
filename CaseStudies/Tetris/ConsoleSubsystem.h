#pragma once

class ConsoleSubsystem : public IUISubsystem {

private:
    // TODO: Das könnte woanders hin ....
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

    std::future<bool> futureKeyboardLogger;
    bool m_enableKeyboardLogging;

    // TODO: Wie sieht das mit SMART POINTER AUS ??????
    std::list<IKeyboardObserver*> m_observer;

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

    void startKeyboardLogging() override;
    void stopKeyboardLogging() override;

    // getter
    bool isInputAvailable() override;
    bool isEscapeHit() override;

    // implementation of interface 'ITetrisBoardListener'
    void attach(IKeyboardObserver* observer) override;
    void detach(IKeyboardObserver* observer) override;
    void notifyAll(std::deque<unsigned short>) override;

public:
    void drawBorder();
    void writeAt(char ch, COORD coord) override;
    void writeAt(char ch, unsigned int color, COORD coord) override;
    void writeAtTest(unsigned int color, char ch, COORD coord) override;


private:
    // private helper methods
    bool checkInputAvailable();
    bool isValidKey(unsigned short);
};