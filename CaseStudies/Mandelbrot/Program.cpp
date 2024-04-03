// =====================================================================================
// Program.cpp // Mandelbrot Application Entry Point
// =====================================================================================


// =====================================================================================

// TBD: Die einzelnen Varianten können mit constexpr auskommentiert werden !!!

// Irgendeine Variante könnte std::latch anwenden !!!

// Werden die Arrays speicher konform initialisiert ?????????????

// TODO: Geht diese Palette nicht mit constexpr ?????????  Da gibt es Linker Error ....

// TODO: Hmmm, viele long Variablen köntnen size_t sein .
 

// TODO: jede Menge const einfügen .........

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

#define MAX_LOADSTRING 100

// global Variables:
HINSTANCE hInst;                        // current instance
WCHAR szTitle[MAX_LOADSTRING];          // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];    // the main window class name

// forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    ::LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    ::LoadStringW(hInstance, IDC_MANDELBROT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // main message loop
    while (::GetMessage(&msg, nullptr, 0, 0))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MANDELBROT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return ::RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = ::CreateWindowW(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        300,
        30,
        Mandelbrot::WindowWidth,
        Mandelbrot::WindowHeight,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            mandelbrot.startCalculationThread(); // launch calculation threads
            mandelbrot.startDrawingThread();     // launch single drawing thread
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
                mandelbrot.paintRectanglesAsync(hdc);
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
        else if constexpr  (version == MandelbrotVersion::ProducerConsumerBasedApproach) {
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
