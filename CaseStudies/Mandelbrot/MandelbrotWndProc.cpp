// =====================================================================================
// MandelbrotWndProc.cpp // Mandelbrot Application Window Procedure
// =====================================================================================

#include "framework.h"

#include "Mandelbrot.h"

#include <complex>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <thread>
#include <future>
#include <utility>
#include <functional> 
#include <mutex>

#include "MandelbrotPalette.h"
#include "MandelbrotHelper.h"

// #define MAX_LOADSTRING 100

LRESULT CALLBACK MandelbrotWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Mandelbrot mandelbrot;

    constexpr MandelbrotVersion version{ getVersion() };

    if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach)
    {
        mandelbrot.setHWND(hWnd);
    }

    switch (message)
    {
    case WM_SIZE:
        ::OutputDebugString(L"> WM_SIZE");

        RECT rect;
        ::GetClientRect(hWnd, &rect);
        mandelbrot.setClientWidth(rect.right);
        mandelbrot.setClientHeight(rect.bottom);
        mandelbrot.computeRects();

        if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach)
        {
            mandelbrot.setHWND(hWnd);
            mandelbrot.startCalculationThread();  // launch calculation threads
            mandelbrot.startDrawingThread();      // launch single drawing thread
        }

        ::OutputDebugString(L"< WM_SIZE");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT");

        if constexpr (
            version == MandelbrotVersion::BasicVersion ||
            version == MandelbrotVersion::RectanglesSequential ||
            version == MandelbrotVersion::RectanglesParallelBlocking || 
            version == MandelbrotVersion::RectanglesParallelBlockingUsingLatch)
        {
            // register start time
            ULONGLONG dwStart{ ::GetTickCount64() };

            PAINTSTRUCT ps;
            HDC hdc = ::BeginPaint(hWnd, &ps);

            switch (version)
            {
            case MandelbrotVersion::BasicVersion:
                mandelbrot.paint(hdc);
                break;
            case MandelbrotVersion::RectanglesSequential:
                mandelbrot.paintRectangles(hdc);
                break;
            case MandelbrotVersion::RectanglesParallelBlocking:
                mandelbrot.paintRectanglesAsync(hdc);
                break;
            case MandelbrotVersion::RectanglesParallelBlockingUsingLatch:
                mandelbrot.paintRectanglesAsyncWithLatch(hdc);
                break;
            default:
                break;
            }

            ::EndPaint(hWnd, &ps);

            // verbose output
            ULONGLONG dwTimeEllapsed{ ::GetTickCount64() - dwStart };
            WCHAR szText[64];
            wsprintf(szText,
                L"< WM_PAINT -  %ld milliseconds\n", (DWORD)dwTimeEllapsed);
            ::OutputDebugString(szText);
        }
        else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingClassic)
        {
            // using 'bool flag' 

            ::OutputDebugString(L"> Start ...");

            ::ValidateRect(hWnd, NULL);

            // cancel all drawing threads, if existing
            size_t doneRectangles = mandelbrot.getDoneRectangles();
            if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

                ::OutputDebugString(L"> Requesting Abort ...");

                mandelbrot.setAbort(true);
                mandelbrot.waitRectanglesDone();
            }

            // launch new drawing threads
            ::OutputDebugString(L"> Launching new drawing threads ...");

            mandelbrot.setAbort(false);
            mandelbrot.resetDoneRectangles();

            HDC hDC = ::GetDC(hWnd);
            mandelbrot.startPaintingRectanglesAsync(hWnd, hDC);

            ::OutputDebugString(L"< WM_PAINT");
        }
        else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingStopToken)
        {
            // using std::jthread and std::stop_token 

            ::OutputDebugString(L"> Start ...");

            ::ValidateRect(hWnd, NULL);

            // cancel all drawing threads, if existing
            size_t doneRectangles = mandelbrot.getDoneRectangles();
            if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

                ::OutputDebugString(L"> Requesting Stop ...");

                // requesting stop 
                mandelbrot.requestAbort();
                mandelbrot.waitRectanglesDone();
            }

            // launch new drawing threads
            ::OutputDebugString(L"> Launching new drawing threads ...");

            mandelbrot.resetDoneRectangles();

            HDC hDC = ::GetDC(hWnd);
            mandelbrot.startPaintingRectanglesAsyncEx(hWnd, hDC);

            ::OutputDebugString(L"< WM_PAINT");
        }
        else if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach) {
            ::OutputDebugString(L"> WM_PAINT Anfang");
            ::ValidateRect(hWnd, NULL);
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            //::EndPaint(hWnd, &ps);
            ::OutputDebugString(L"< WM_PAINT Ende");
        }
    }
    break;

    case WM_DESTROY:
        ::OutputDebugString(L"> WM_DESTROY");

        if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingClassic ||
            version == MandelbrotVersion::RectanglesParallelNonBlockingStopToken)
        {
            // cancel all drawing threads, if existing
            int doneRectangles = mandelbrot.getDoneRectangles();
            if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

                mandelbrot.setAbort(true);
                mandelbrot.waitRectanglesDone();
            }
        }
        else if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach)
        {
            mandelbrot.setAbort(true);
        }

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
