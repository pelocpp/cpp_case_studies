// =====================================================================================
// Program.cpp // Mandelbrot Application Entry Point
// =====================================================================================

// =====================================================================================

// TBD: Die einzelnen Varianten können mit constexpr auskommentiert werden !!!

// TBD: Irgendeine Variante könnte std::latch anwenden !!!

// TBD: Werden die Arrays speicher konform initialisiert ?????????????

// TODO: Geht diese Palette nicht mit constexpr ?????????  Da gibt es Linker Error ....

// TODO: Hmmm, viele long Variablen köntnen size_t sein .
 
// TODO: jede Menge const einfügen .........

// RANGE BASED For-Loop

////
//{
//    // short hand constants for the Mandelbrot coordinates system
//    static constexpr T XMIN = MANDELBROT_COORDINATES::XMIN;
//    static constexpr T XMAX = MANDELBROT_COORDINATES::XMAX;
//    static constexpr T YMIN = MANDELBROT_COORDINATES::YMIN;
//    static constexpr T YMAX = MANDELBROT_COORDINATES::YMAX;

// vorsicht ergeben lokale constexpr Variablen Sinn ...............

// Die letzte Variante stürzt ab, wenn man Close drückt ...


// Das geht auch mit einer Call back Funktion ... und dann ohne Polling ...
//             // premature end of drawing
//if (token.stop_requested()) {
//    goto m_label;
//}


// =====================================================================================


#include "framework.h"

#include "Mandelbrot.h"

#include "MandelbrotCommon.h"
#include "MandelbrotBasic.h"

#include "MandelbrotPalette.h"

// =====================================================================================

extern LRESULT CALLBACK MandelbrotWndProcBasic(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcRectanglesSequential(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcRectanglesParallelBlocking(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcRectanglesParallelBlockingUsingLatch(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcRectanglesParallelNonBlockingClassic(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcRectanglesParallelNonBlockingStopToken(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK MandelbrotWndProcProducerConsumerBasedApproach(HWND, UINT, WPARAM, LPARAM);

// =====================================================================================

constexpr MandelbrotVersion version{ getVersion() };

// =====================================================================================


// TODO: Hmmm, das muss global irgendwo anders hin ....
MandelbrotPalette g_palette{};

// =====================================================================================

#define MAX_LOADSTRING 256

// global Variables:
HINSTANCE hInst;                        // current instance
WCHAR szTitle[MAX_LOADSTRING];          // title bar text
WCHAR szWindowClass[MAX_LOADSTRING];    // the main window class name

// forward declarations of functions included in this code module:
ATOM                       MyRegisterClass(HINSTANCE hInstance);
BOOL                       InitInstance(HINSTANCE, int);
INT_PTR CALLBACK           About(HWND, UINT, WPARAM, LPARAM);

extern LRESULT CALLBACK    MandelbrotWndProc(HWND, UINT, WPARAM, LPARAM);

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
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MANDELBROT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if constexpr (version == MandelbrotVersion::BasicVersion)
    {
        wcex.lpfnWndProc = MandelbrotWndProcBasic;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Basic Version");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesSequential)
    {
        wcex.lpfnWndProc = MandelbrotWndProcRectanglesSequential;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Sequential");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesParallelBlocking)
    {
        wcex.lpfnWndProc = MandelbrotWndProcRectanglesParallelBlocking;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Blocking");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesParallelBlockingUsingLatch)
    {
        wcex.lpfnWndProc = MandelbrotWndProcRectanglesParallelBlockingUsingLatch;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Blocking - Using Latch");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingClassic)
    {
        wcex.lpfnWndProc = MandelbrotWndProcRectanglesParallelNonBlockingClassic;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Non Blocking - Classic");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingStopToken)
    {
        wcex.lpfnWndProc = MandelbrotWndProcRectanglesParallelNonBlockingStopToken;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Non Blocking - Stop Token");
    }
    else if constexpr (version == MandelbrotVersion::RectanglesParallelNonBlockingStopToken)
    {
        wcex.lpfnWndProc = MandelbrotWndProcProducerConsumerBasedApproach;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Non Blocking - Stop Token");
    }
    else if constexpr (version == MandelbrotVersion::ProducerConsumerBasedApproach)
    {
        wcex.lpfnWndProc = MandelbrotWndProcProducerConsumerBasedApproach;
        wcscat_s(szTitle, MAX_LOADSTRING, L" - Rectangles Parallel - Non Blocking - Producer Consumer Based Approach");
    }

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
        MandelbrotWindowDimension::WindowWidth,
        MandelbrotWindowDimension::WindowHeight,
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

// =====================================================================================
// End-of-File
// =====================================================================================
