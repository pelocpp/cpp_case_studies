// =====================================================================================
// MandelbrotWndProc_05_RectanglesParallelNonBlockingClassic.cpp
// Mandelbrot Application Window Procedure
// Variant 05: Parallel - Non Blocking - Classic
// =====================================================================================

#include "Mandelbrot_05_RectanglesParallelNonBlockingClassic.h"

LRESULT CALLBACK MandelbrotWndProcRectanglesParallelNonBlockingClassic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotRectanglesParallelNonBlockingClassic mandelbrot;

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

        ::ValidateRect(hWnd, NULL);

        // cancel all drawing threads, if existing
        size_t doneRectangles{ mandelbrot.getDoneRectangles() };
        if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

            ::OutputDebugString(L"> Requesting Abort ...\n");

            mandelbrot.setAbort(true);
            mandelbrot.waitRectanglesDone();
        }

        // launch new drawing threads
        ::OutputDebugString(L"> Launching new drawing threads ...\n");

        mandelbrot.setAbort(false);
        mandelbrot.resetDoneRectangles();

        HDC hDC{ ::GetDC(hWnd) };
        mandelbrot.startPaintingRectanglesAsync(hWnd, hDC);

        ::OutputDebugString(L"< WM_PAINT\n");
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY\n");

        // cancel all drawing threads, if existing
        size_t doneRectangles{ mandelbrot.getDoneRectangles() };
        if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

            mandelbrot.setAbort(true);
            mandelbrot.waitRectanglesDone();
        }

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
