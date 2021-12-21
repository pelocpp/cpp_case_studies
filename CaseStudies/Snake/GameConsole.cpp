// =====================================================================================
// GameConsole.cpp
// =====================================================================================

#include <windows.h>

#include "Direction.h"
#include "GameConsole.h"

 // c'tor
GameConsole::GameConsole()
{
    m_hStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);
    m_hStdin = ::GetStdHandle(STD_INPUT_HANDLE);

    ::SetConsoleTitle("Snake (Version 1.00)");
    ::SetConsoleTextAttribute(
        m_hStdout,
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
    );

    // EncodingName: "Western European (Windows)", BodyName: "iso-8859-1", CodePage: 1252
    UINT codePageID = 1252;
    ::SetConsoleOutputCP(codePageID);

    m_lastVirtualKey = -1;
    m_lastValidArrow = Direction::Right;
    m_isEscapeHit = false;

    this->DrawBorder();

    ::FlushConsoleInputBuffer(m_hStdin);
}

GameConsole::~GameConsole()
{
    ::CloseHandle(m_hStdin);
    ::CloseHandle(m_hStdout);
}

// getter
Direction GameConsole::LastValidArrow()
{
    return m_lastValidArrow;
}

bool GameConsole::IsEscapeHit()
{
    return m_isEscapeHit;
}

// public interface
void GameConsole::Setup()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    BOOL b = ::GetConsoleScreenBufferInfo(m_hStdout, &info);

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Right = GameConsole::Width;
    rect.Bottom = GameConsole::Height;
    b = ::SetConsoleWindowInfo(m_hStdout, TRUE, &rect);

    COORD coord;
    coord.X = GameConsole::Width + 2;
    coord.Y = GameConsole::Height + 2;
    b = ::SetConsoleScreenBufferSize(m_hStdout, coord);
}

// public interface: input
bool GameConsole::InputAvailable()
{
    DWORD dwNumEvents;
    ::GetNumberOfConsoleInputEvents(m_hStdin, &dwNumEvents);
    if (dwNumEvents == 0)
        return false;

    // retrieve last pressed key
    WORD lastVirtualKey = 0;
    for (unsigned int i = 0; i < dwNumEvents; i++) {

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

void GameConsole::ReadInput()
{
    switch (m_lastVirtualKey)
    {
    case VK_UP:
        if (m_lastValidArrow != Direction::Down)
            m_lastValidArrow = Direction::Up;
        break;
    case VK_DOWN:
        if (m_lastValidArrow != Direction::Up)
            m_lastValidArrow = Direction::Down;
        break;
    case VK_RIGHT:
        if (m_lastValidArrow != Direction::Left)
            m_lastValidArrow = Direction::Right;
        break;
    case VK_LEFT:
        if (m_lastValidArrow != Direction::Right)
            m_lastValidArrow = Direction::Left;
        break;
    case VK_ESCAPE:
        m_isEscapeHit = true;
        break;

    default:
        break;  // ignoring any other keys ...
    }
}

// public interface: output
void GameConsole::Clear()
{
    // retrieve information about the output screen buffer
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!::GetConsoleScreenBufferInfo(m_hStdout, &info))
        return;

    // calculate number of character cells in the current buffer
    DWORD dwConsoleSize = info.dwSize.X * info.dwSize.Y;

    // fill the entire screen with blanks
    COORD home ={ 0, 0 };    // home for cursor 
    DWORD charsWritten;
    ::FillConsoleOutputCharacter(
        m_hStdout, ' ', dwConsoleSize, home, &charsWritten
    );

    // set the buffer's attributes accordingly
    ::FillConsoleOutputAttribute(
        m_hStdout, info.wAttributes, dwConsoleSize, home, &charsWritten
    );

    // put cursor in upper left corner
    ::SetConsoleCursorPosition(m_hStdout, home);
}

void GameConsole::DrawBorder()
{
    COORD coord ={ 0, 0 };
    this->WriteAt(Box_Left_Upper, coord);

    for (int i = 1; i < Height - 1; i++) {
        coord.X = 0;
        coord.Y = i;
        this->WriteAt(Box_Vert, coord);
    }

    coord.X = 0;
    coord.Y = Height - 1;
    this->WriteAt(Box_Left_Lower, coord);

    coord.X = Width - 1;
    coord.Y = 0;
    this->WriteAt(Box_Right_Upper, coord);

    for (int i = 1; i < Height - 1; i++) {
        coord.X = Width - 1;
        coord.Y = i;
        this->WriteAt(Box_Vert, coord);
    }

    coord.X = Width - 1;
    coord.Y = Height - 1;
    this->WriteAt(Box_Right_Lower, coord);

    for (int j = 1; j < Width - 1; j++) {
        coord.X = j;
        coord.Y = 0;
        this->WriteAt(Box_Horiz, coord);
    }

    for (int j = 1; j < Width - 1; j++) {
        coord.X = j;
        coord.Y = Height - 1;
        this->WriteAt(Box_Horiz, coord);
    }
 }

void GameConsole::WriteAt(char ch, COORD coord)
{
    if (!::SetConsoleCursorPosition(m_hStdout, coord))
        return;

    char buf[]{ ch };
    // buf[0] = ch;        // TODO Zeile löschen ...
    DWORD numCharsWritten;
    ::WriteConsole(m_hStdout, buf, 1, &numCharsWritten, (void*) 0);
}

// =====================================================================================
// End-of-File
// =====================================================================================
