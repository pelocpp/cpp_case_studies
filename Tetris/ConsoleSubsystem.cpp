#include <windows.h>

#include "Direction.h"
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
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

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

    drawBorder();
}

void ConsoleSubsystem::closeConsole() {

}

// getter
bool ConsoleSubsystem::isInputAvailable() {
    return false;
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