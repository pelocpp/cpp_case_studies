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

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);

        mandelbrot.setHWND(hWnd);

        mandelbrot.prepareCalculationThreads();  // XXX
        mandelbrot.prepareDrawingThread();       // XXX

        mandelbrot.startCalculationThreads();  // launch calculation threads
        mandelbrot.startDrawingThread();       // launch single drawing thread

        ::OutputDebugString(L"< WM_SIZE");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        ::ValidateRect(hWnd, NULL);

        // cancel drawing thread, if existing
        //size_t doneRectangles = mandelbrot.getDoneRectangles();
        //if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

        //    ::OutputDebugString(L"> Requesting Abort ...");

        //    mandelbrot.requestAbort();
        //    mandelbrot.waitRectanglesDone();
        //}

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
