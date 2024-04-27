// =====================================================================================
// MandelbrotWndProc_04_RectanglesParallelNonBlockingClassic.cpp
// Mandelbrot Application Window Procedure
// Variant 07: Parallel - Non Blocking - Stop Token
// =====================================================================================

#include "MandelbrotProducerConsumerBasedApproach.h"

LRESULT CALLBACK MandelbrotWndProcProducerConsumerBasedApproach(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotProducerConsumerBasedApproach mandelbrot;

    switch (message)
    {
    case WM_SIZE:
        ::OutputDebugString(L"> WM_SIZE");

        // cancel all threads, if any existing
        bool done = mandelbrot.getDone();
        if (!done) {

            ::OutputDebugString(L"> Requesting Abort ...");
            mandelbrot.waitAllThreadsDone();
        }

        // clear queues
        mandelbrot.clearAllQueues();

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);

        mandelbrot.setHWND(hWnd);
        mandelbrot.prepareAllThreads(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);  // XXX
        mandelbrot.launchAllThreads();  // launch calculation threads and single drawing thread

        ::OutputDebugString(L"< WM_SIZE");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        ::ValidateRect(hWnd, NULL);

        ::OutputDebugString(L"< WM_PAINT");
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY");

        // cancel all drawing threads, if existing
        //int doneRectangles{ mandelbrot.getDoneRectangles() };
        //if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

        //    mandelbrot.waitRectanglesDone();
        //}

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
