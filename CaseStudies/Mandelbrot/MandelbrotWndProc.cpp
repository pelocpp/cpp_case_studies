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

    constexpr MandelbrotVersion version = getVersion();

    if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach)
    {
        mandelbrot.setHWND(hWnd);
    }

    switch (message)
    {
    case WM_SIZE:
        ::OutputDebugString(L"> WM_SIZE\n");

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

        ::OutputDebugString(L"< WM_SIZE\n");
        break;

    case WM_PAINT:
    {
        ::OutputDebugString(L"> WM_PAINT\n");

        if constexpr (
            version == MandelbrotVersion::BasicVersion ||
            version == MandelbrotVersion::RectanglesSequential ||
            version == MandelbrotVersion::RectanglesParallelBlocking)
        {
            // register start time
            LONGLONG dwStart;
            dwStart = ::GetTickCount64();

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
                // mandelbrot.paintRectanglesAsync(hdc);
                mandelbrot.paintRectanglesAsyncWithLatch(hdc);
                break;
            default:
                break;
            }

            ::EndPaint(hWnd, &ps);

            // verbose output
            ULONGLONG dwTimeEllapsed;
            dwTimeEllapsed = ::GetTickCount64() - dwStart;
            WCHAR szText[64];
            wsprintf(szText,
                L"< WM_PAINT -  %ld milliseconds\n", (DWORD)dwTimeEllapsed);
            ::OutputDebugString(szText);
        }
        else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlocking)
        {
            ::ValidateRect(hWnd, NULL);

            // cancel all drawing threads, if existing
            int doneRectangles = mandelbrot.getDoneRectangles();
            if (doneRectangles < MandelbrotRectangles::NUM_RECTS) {

                mandelbrot.setAbort(true);
                mandelbrot.waitRectanglesDone();
            }

            // launch new drawing threads
            ::OutputDebugString(L"launching new drawing threads ...\n");

            mandelbrot.setAbort(false);
            mandelbrot.resetDoneRectangles();

            HDC hDC = ::GetDC(hWnd);
            mandelbrot.startPaintingRectanglesAsync(hWnd, hDC);

            ::OutputDebugString(L"< WM_PAINT\n");
        }
        else if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach) {
            ::OutputDebugString(L"> WM_PAINT Anfang\n");
            ::ValidateRect(hWnd, NULL);
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            //::EndPaint(hWnd, &ps);
            ::OutputDebugString(L"< WM_PAINT Ende\n");
        }
    }
    break;

    case WM_DESTROY:
        ::OutputDebugString(L"> WM_DESTROY\n");

        if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlocking)
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

        ::OutputDebugString(L"< WM_DESTROY\n");
        break;

    case WM_QUIT:
        ::OutputDebugString(L"> WM_QUIT\n");
        ::OutputDebugString(L"< WM_QUIT\n");
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
