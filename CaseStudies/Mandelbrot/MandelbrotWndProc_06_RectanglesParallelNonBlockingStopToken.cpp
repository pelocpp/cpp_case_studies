// =====================================================================================
// MandelbrotWndProc_04_RectanglesParallelNonBlockingClassic.cpp
// Mandelbrot Application Window Procedure
// Variant 06: Parallel - Non Blocking - Stop Token
// =====================================================================================

#include "MandelbrotRectanglesParallelNonBlockingStopToken.h"

LRESULT CALLBACK MandelbrotWndProcRectanglesParallelNonBlockingStopToken(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotRectanglesParallelNonBlockingStopToken mandelbrot;

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

        ::ValidateRect(hWnd, NULL);

        // cancel all drawing threads, if existing
        size_t doneRectangles = mandelbrot.getDoneRectangles();
        if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

            ::OutputDebugString(L"> Requesting Abort ...");

            mandelbrot.requestAbort();
            mandelbrot.waitRectanglesDone();
        }

        // launch new drawing threads
        ::OutputDebugString(L"> Launching new drawing threads ...");

        mandelbrot.resetDoneRectangles();

        HDC hDC = ::GetDC(hWnd);
        mandelbrot.startPaintingRectanglesAsync(hWnd, hDC);

        ::OutputDebugString(L"< WM_PAINT");
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY");

        // cancel all drawing threads, if existing
        int doneRectangles{ mandelbrot.getDoneRectangles() };
        if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

            mandelbrot.waitRectanglesDone();
        }

        ::PostQuitMessage(0);

        ::OutputDebugString(L"< WM_DESTROY");
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
