#include <windows.h>
#include <future>
#include <list>
#include <chrono>
#include <deque>

#include "Globals.h"
#include "Direction.h"

#include "IKeyboardObserver.h"
#include "IKeyboardListener.h"
#include "IUISubsystem.h"
#include "ConsoleSubsystem.h"

// c'tor(s)
ConsoleSubsystem::ConsoleSubsystem(int width, int height)
    : m_width(width), m_height(height) {

    m_hStdin = (HANDLE) 0;
    m_hStdout = (HANDLE)0;

    // snake stuff ?!=?!?!?!
    m_lastVirtualKey =0;    // TODO: Das ist sinvoller nil wert !?!?!?!
    m_lastValidArrow = Direction::None;
    m_isEscapeHit = false;
}

// properties
int ConsoleSubsystem::getWidth() {
    return m_width;
}

int ConsoleSubsystem::getHeight() {
    return m_height;
}

void ConsoleSubsystem::initConsole() {
    m_hStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);
    m_hStdin = ::GetStdHandle(STD_INPUT_HANDLE);

    ::SetConsoleTitle("Tetris (Version 0.01)");
    ::SetConsoleTextAttribute(
        m_hStdout,
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

//#define BACKGROUND_BLUE      0x0010 // background color contains blue.
//#define BACKGROUND_GREEN     0x0020 // background color contains green.
//#define BACKGROUND_RED   


    // EncodingName: "IBM PC Code Page", CodePage: 437
    UINT codePageID = 437;
    ::SetConsoleOutputCP(codePageID);

    m_lastVirtualKey = -1;
    m_lastValidArrow = Direction::Right;
    m_isEscapeHit = false;

    ::FlushConsoleInputBuffer(m_hStdin);
}

// public interface
void ConsoleSubsystem::showConsole() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    BOOL b = ::GetConsoleScreenBufferInfo(m_hStdout, &info);

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Right = m_width;
    rect.Bottom = m_height;
    b = ::SetConsoleWindowInfo(m_hStdout, TRUE, &rect);

    COORD coord;
    coord.X = m_width + 2;
    coord.Y = m_height + 2;
    b = ::SetConsoleScreenBufferSize(m_hStdout, coord);

    // hide cursor in Windows console
    CONSOLE_CURSOR_INFO curInfo;
    ::GetConsoleCursorInfo(m_hStdout, &curInfo);
    curInfo.bVisible = FALSE;
    ::SetConsoleCursorInfo(m_hStdout, &curInfo);

    drawBorder();
}

void ConsoleSubsystem::closeConsole() {
    ::CloseHandle(m_hStdin);
    ::CloseHandle(m_hStdout);
}

// getter
bool ConsoleSubsystem::isInputAvailable() {

    DWORD dwNumEvents;
    ::GetNumberOfConsoleInputEvents(m_hStdin, &dwNumEvents);
    if (dwNumEvents == 0)
        return false;

    // retrieve last pressed key
    WORD lastVirtualKey = 0;
    for (unsigned int i = 0; i < dwNumEvents; i++)
    {
        INPUT_RECORD evt;
        DWORD dwEventsRead;

        // read a single event from the console's input buffer
        // and remove it from the buffer
        ::ReadConsoleInput(m_hStdin, &evt, 1, &dwEventsRead);

        // store key code, if a key was pressed
        if (evt.EventType == KEY_EVENT && evt.Event.KeyEvent.bKeyDown == TRUE)
            lastVirtualKey = evt.Event.KeyEvent.wVirtualKeyCode;
    }

    // simple error handling, should never be reached
    if (lastVirtualKey == 0)
        return false;

    m_lastVirtualKey = lastVirtualKey;
    return true;
}

bool ConsoleSubsystem::isEscapeHit() {
    return false;
}

void ConsoleSubsystem::writeAt(char ch, COORD coord)
{
    if (!::SetConsoleCursorPosition(m_hStdout, coord))
        return;

    char buf[1];
    buf[0] = ch;
    DWORD numCharsWritten;
    ::WriteConsole(m_hStdout, buf, 1, &numCharsWritten, (void*)0);
}

void ConsoleSubsystem::writeAt(char ch, unsigned int color, COORD coord)
{
    if (!::SetConsoleCursorPosition(m_hStdout, coord))
        return;

    ::SetConsoleTextAttribute(m_hStdout, color);

    char buf[1];
    buf[0] = ch;
    DWORD numCharsWritten;
    ::WriteConsole(m_hStdout, buf, 1, &numCharsWritten, (void*)0);
}

void ConsoleSubsystem::drawBorder()
{
    COORD coord = { 0, 0 };
    writeAt(Box_Left_Upper, coord);
    for (int i = 1; i < m_height - 1; i++)
    {
        coord.X = 0;
        coord.Y = i;
        writeAt(Box_Vert, coord);
    }
    coord.X = 0;
    coord.Y = m_height - 1;
    writeAt(Box_Left_Lower, coord);

    coord.X = m_width - 1;
    coord.Y = 0;
    writeAt(Box_Right_Upper, coord);
    for (int i = 1; i < m_height - 1; i++)
    {
        coord.X = m_width - 1;
        coord.Y = i;
        writeAt(Box_Vert, coord);
    }
    coord.X = m_width - 1;
    coord.Y = m_height - 1;
    writeAt(Box_Right_Lower, coord);

    for (int j = 1; j < m_width - 1; j++)
    {
        coord.X = j;
        coord.Y = 0;
        writeAt(Box_Horiz, coord);
    }
    for (int j = 1; j < m_width - 1; j++)
    {
        coord.X = j;
        coord.Y = m_height - 1;
        writeAt(Box_Horiz, coord);
    }
}

void ConsoleSubsystem::writeAtTest(unsigned int color, char ch, COORD coord) {

   ::SetConsoleTextAttribute(m_hStdout, color);

    if (!::SetConsoleCursorPosition(m_hStdout, coord))
        return;

    char buf[1];
    buf[0] = ch;
    DWORD numCharsWritten;
    ::WriteConsole(m_hStdout, buf, 1, &numCharsWritten, (void*)0);

}

bool ConsoleSubsystem::checkInputAvailable() {

    std::deque<unsigned short> keys;

    while (m_enableKeyboardLogging) {

        // ::OutputDebugString("Check keys ...\n");

        keys = {};  // clear keys queue

        DWORD dwNumEvents;
        ::GetNumberOfConsoleInputEvents(m_hStdin, &dwNumEvents);
        if (dwNumEvents > 0) {

            // retrieve last pressed keys
            WORD lastVirtualKey = 0;
            for (unsigned int i = 0; i < dwNumEvents; i++)
            {
                INPUT_RECORD evt;
                DWORD dwEventsRead;

                // read a single event from the console's input buffer
                // and remove it from the buffer
                ::ReadConsoleInput(m_hStdin, &evt, 1, &dwEventsRead);

                // store key code, if a key was pressed
                if (evt.EventType == KEY_EVENT && evt.Event.KeyEvent.bKeyDown == TRUE) {

                    lastVirtualKey = evt.Event.KeyEvent.wVirtualKeyCode;

                    if (isValidKey(lastVirtualKey)) {

                        char szText[128];
                        ::wsprintf(szText, "> Key: %d\n", lastVirtualKey);
                        ::OutputDebugString(szText);

                        keys.push_back(lastVirtualKey);
                    }
                }
            }

            if (!keys.empty()) {
                notifyAll(keys);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(InputLoggerSleep));
    }

    ::OutputDebugString("Done KeyboardLogging\n");
    return true;
}

bool ConsoleSubsystem::isValidKey(unsigned short key) { 

    if (key == VK_LEFT || key == VK_UP || key == VK_RIGHT || key == VK_DOWN || key == VK_ESCAPE) {
        return true;
    }

    return false;
}

void ConsoleSubsystem::startKeyboardLogging() {

    m_enableKeyboardLogging = true;

    // STL Algo mem_fn  std::mem_fn

    futureKeyboardLogger = std::async(std::launch::async, [this]() -> bool {
        return checkInputAvailable();
        }
    );
}

void ConsoleSubsystem::stopKeyboardLogging() {

    m_enableKeyboardLogging = false;

    // wait until logging thread has terminated
    futureKeyboardLogger.get();
}

// implementation of interface 'IKeyboardListener'
void ConsoleSubsystem::attach(IKeyboardObserver* observer) {
    m_observer.push_back(observer);
}

void ConsoleSubsystem::detach(IKeyboardObserver* observer) {
    // TODO: Wie war das mit erase und remove
    m_observer.remove(observer);
}

void ConsoleSubsystem::notifyAll(std::deque<unsigned short> keys) {
    for (auto observer : m_observer) {
        observer->update(keys);
    }
}