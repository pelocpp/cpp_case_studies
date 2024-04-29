// =====================================================================================
// MandelbrotWndProc_07_ProducerConsumerBasedApproach.cpp
// Mandelbrot Application Window Procedure
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#include "MandelbrotProducerConsumerBasedApproach.h"

LRESULT CALLBACK MandelbrotWndProcProducerConsumerBasedApproach(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static MandelbrotProducerConsumerBasedApproach mandelbrot;

    switch (message)
    {
    case WM_SIZE:
    {
        ::OutputDebugString(L"> WM_SIZE");

        // cancel all threads, if any existing
        bool done;

        {
            std::lock_guard<std::mutex> guard{ mandelbrot.m_mutexDone };

            done = mandelbrot.m_done;
        }

        if (!done) {

            ::OutputDebugString(L"> m_done ==> false");

            mandelbrot.requestStop();
            mandelbrot.waitAllThreadsDone();
            mandelbrot.m_done = true;

            ::OutputDebugString(L"> m_done ==> true");
        }

        // clear queues
        mandelbrot.clearAllQueues();

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.setHWND(hWnd);

        ::OutputDebugString(L"< WM_SIZE");
    }

        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        ::ValidateRect(hWnd, NULL);

        mandelbrot.computeRects(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);
        mandelbrot.prepareAllThreads(MandelbrotRectangles::NUM_ROWS, MandelbrotRectangles::NUM_COLS);
        mandelbrot.launchAllThreads();  // launch calculation threads and single drawing thread

        ::OutputDebugString(L"< WM_PAINT");
    }
    break;

    case WM_DESTROY:
    {
        ::OutputDebugString(L"> WM_DESTROY");

        // cancel all threads, if any existing
        {
            std::lock_guard<std::mutex> guard{ mandelbrot.m_mutexDone };

            if (!mandelbrot.m_done) {

                mandelbrot.requestStop();
                mandelbrot.waitAllThreadsDone();
               // mandelbrot.m_done = true;   // nicht notwendig
            }
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
