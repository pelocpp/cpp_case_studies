// =====================================================================================
// MandelbrotWndProc_02_RectanglesSequential.cpp
// Mandelbrot Application Window Procedure
// Variant 02: Drawing Rectangles Sequential
// =====================================================================================

#include "Mandelbrot_02_RectanglesSequential.h"

LRESULT CALLBACK MandelbrotWndProcRectanglesSequential(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotRectanglesSequential mandelbrot;

    switch (message)
    {
    case WM_SIZE:
    {
        ::OutputDebugString(L"> WM_SIZE\n");

        RECT rect{};
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);

        ::OutputDebugString(L"< WM_SIZE\n");
    }
    break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT\n");

        // register start time
        ULONGLONG dwStart{ ::GetTickCount64() };

        PAINTSTRUCT ps{};
        HDC hdc = ::BeginPaint(hWnd, &ps);
        mandelbrot.paintRectangles(hdc);
        ::EndPaint(hWnd, &ps);

        // verbose output
        ULONGLONG dwTimeEllapsed{ ::GetTickCount64() - dwStart };
        WCHAR szText[64];
        wsprintf(szText, L"< WM_PAINT -  %ld milliseconds\n", (DWORD) dwTimeEllapsed);
        ::OutputDebugString(szText);
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY\n");
        ::PostQuitMessage(0);
        ::OutputDebugString(L"< WM_DESTROY\n");
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
