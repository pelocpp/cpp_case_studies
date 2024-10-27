// =====================================================================================
// MandelbrotWndProc_07_ProducerConsumerBasedApproach.cpp
// Mandelbrot Application Window Procedure
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#include "Mandelbrot_07_ProducerConsumerBasedApproach.h"

LRESULT CALLBACK MandelbrotWndProcProducerConsumerBasedApproach(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotProducerConsumerBasedApproach mandelbrot;

    switch (message)
    {
    case WM_SIZE:
    {
        ::OutputDebugString(L"> WM_SIZE");

        // cancel all threads, if any existing
        mandelbrot.cancelActiveThreadsIfAny();

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);

        ::OutputDebugString(L"< WM_SIZE");
    }
    break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        ::ValidateRect(hWnd, NULL);

        mandelbrot.setHWND(hWnd);
        mandelbrot.prepareAllThreads(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);
        mandelbrot.launchAllThreads();  // launch calculation threads and single drawing thread

        ::OutputDebugString(L"< WM_PAINT");
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY");

        // cancel active threads, if any existing
        mandelbrot.cancelActiveThreadsIfAny();

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
