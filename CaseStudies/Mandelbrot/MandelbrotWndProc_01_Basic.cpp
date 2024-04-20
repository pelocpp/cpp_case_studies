// =====================================================================================
// MandelbrotWndProcBasic.cpp // Mandelbrot Application Window Procedure
// Variant: BasicVersion
// =====================================================================================

#include "framework.h"
#include "Mandelbrot.h"


#include "MandelbrotGeneral.h"
#include "MandelbrotBasic.h"

//
//#include <complex>
//#include <vector>
//#include <array>
//#include <queue>
//#include <deque>
//#include <thread>
//#include <future>
//#include <utility>
//#include <functional> 
//#include <mutex>
//
//#include "MandelbrotPalette.h"
//#include "MandelbrotHelper.h"

// #define MAX_LOADSTRING 100

LRESULT CALLBACK MandelbrotWndProcBasic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // static Mandelbrot mandelbrot;
    static MandelbrotBasic mandelbrot;

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
        mandelbrot.paint(hdc);
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
