// =====================================================================================
// MandelbrotWndProc_04_RectanglesParallelBlockingUsingLatch.cpp
// Mandelbrot Application Window Procedure
// Variant 04: Parallel - Blocking - Using Latch
// =====================================================================================

#include "MandelbrotRectanglesParallelBlockingUsingLatch.h"

LRESULT CALLBACK MandelbrotWndProcRectanglesParallelBlockingUsingLatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotRectanglesParallelBlockingUsingLatch mandelbrot;

    switch (message)
    {
    case WM_SIZE:
        ::OutputDebugString(L"> WM_SIZE");

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);

        ::OutputDebugString(L"< WM_SIZE");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        // register start time
        ULONGLONG dwStart{ ::GetTickCount64() };

        PAINTSTRUCT ps;
        HDC hdc = ::BeginPaint(hWnd, &ps);
        mandelbrot.paintRectanglesAsyncWithLatch(hdc);
        ::EndPaint(hWnd, &ps);

        // verbose output
        ULONGLONG dwTimeEllapsed{ ::GetTickCount64() - dwStart };
        WCHAR szText[64];
        wsprintf(szText,
            L"< WM_PAINT -  %ld milliseconds\n", (DWORD)dwTimeEllapsed);
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
