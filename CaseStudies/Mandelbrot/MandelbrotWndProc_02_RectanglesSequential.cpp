// =====================================================================================
// MandelbrotWndProc_02_RectanglesSequential.cpp
// Mandelbrot Application Window Procedure
// Variant 02: Rectangles Sequential
// =====================================================================================

#include "MandelbrotRectanglesSequential.h"

LRESULT CALLBACK MandelbrotWndProcRectanglesSequential(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotRectanglesSequential mandelbrot;

    switch (message)
    {
    case WM_SIZE:
        ::OutputDebugString(L"> WM_SIZE");

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects();

        ::OutputDebugString(L"< WM_SIZE");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        // register start time
        ULONGLONG dwStart{ ::GetTickCount64() };

        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hWnd, &ps);
        mandelbrot.paintRectanglesSequential(hdc);
        ::EndPaint(hWnd, &ps);

        // verbose output
        ULONGLONG dwTimeEllapsed{ ::GetTickCount64() - dwStart };
        WCHAR szText[64];
        wsprintf(szText,
            L"< WM_PAINT -  %ld milliseconds\n", (DWORD) dwTimeEllapsed);
        ::OutputDebugString(szText);
    }
    break;

    case WM_DESTROY:
        ::OutputDebugString(L"> WM_DESTROY");
        ::PostQuitMessage(0);
        ::OutputDebugString(L"< WM_DESTROY");
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
