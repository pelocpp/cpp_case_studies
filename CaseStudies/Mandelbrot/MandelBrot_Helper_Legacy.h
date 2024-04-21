#pragma once

#if 0

// =====================================================================================
// MandelbrotHelper.h // Mandelbrot Set with C++: Different Approaches
// =====================================================================================

#pragma once

#include "MandelbrotPalette.h"

#include <complex>
#include <array>
#include <queue>
#include <deque>
#include <future>
#include <mutex>
#include <atomic>
#include <stop_token>
#include <thread>
//
//// =====================================================================================
//
//enum class MandelbrotVersion
//{
//    BasicVersion = 1,                            // single rectangle, nonresponsive
//    RectanglesSequential = 2,                    // multiple rectangles, sequential, nonresponsive (blocking)
//    RectanglesParallelBlocking = 3,              // multiple rectangles, parallel, nonresponsive (blocking)
//    RectanglesParallelBlockingUsingLatch = 4,    // multiple rectangles, parallel, nonresponsive (blocking), using std::latch
//    RectanglesParallelNonBlockingClassic = 5,    // multiple rectangles, parallel, responsive (non blocking)
//    RectanglesParallelNonBlockingStopToken = 6,  // multiple rectangles, parallel, responsive (non blocking), using std::stop_token
//    ProducerConsumerBasedApproach = 7            // multiple rectangles, parallel, responsive (non blocking)
//};
//
//constexpr MandelbrotVersion getVersion() { 
//    return MandelbrotVersion::BasicVersion;
//}
//
//// =====================================================================================
//
//using TFloatingPoint = float;  // float or double or long double
// 
//// =====================================================================================
//
//template <typename T>
//struct MandelbrotParams
//{
//    // original limits
//    static constexpr T XMIN{ (T) -2.0  };  // minimum x-value (real part)
//    static constexpr T XMAX{ (T) +0.75 };  // maximum x-value (real part)
//    static constexpr T YMIN{ (T) -1.25 };  // minimum y-value (imaginary part)
//    static constexpr T YMAX{ (T) +1.25 };  // maximum y-value (imaginary part)
//};
//
//struct Pixel 
//{
//    int m_x;
//    int m_y;
//    COLORREF m_cr;
//};
//
//struct Rectangle
//{
//    size_t m_left;
//    size_t m_top;
//    size_t m_right;
//    size_t m_bottom;
//};
//
//struct MandelbrotRectangles
//{
////static constexpr size_t NUM_ROWS { 4 };
////static constexpr size_t NUM_COLS { 4 };
//
//    static constexpr size_t NUM_ROWS{ 1 };
//    static constexpr size_t NUM_COLS{ 2 };
//
//    static constexpr size_t NUM_RECTS{ (NUM_ROWS * NUM_COLS) };
//}; 
//
//struct MandelbrotWindowDimension
//{
//    static constexpr size_t WindowHeight{ 200 };
//    static constexpr size_t WindowWidth{ 500 };
//};

// =====================================================================================



class Mandelbrot
{
public:
    //  static const int NumColors{ 256 };
    static const int Limit{ 5 };

    //static const int WindowHeight{ 450 };
    //static const int WindowWidth{ 500 };

    //static const int WindowHeight{ MandelbrotWindowDimension::WindowHeight };
    //static const int WindowWidth{ MandelbrotWindowDimension::WindowWidth };

private:
    size_t m_clientWidth;
    size_t m_clientHeight;

    size_t m_numRows;
    size_t m_numCols;

    MandelbrotPalette m_palette{};    // const möglicherweise wieder entfernen ..........

    //std::array <
    //    std::array <RECT, MandelbrotRectangles::NUM_COLS>, 
    //        MandelbrotRectangles::NUM_ROWS> m_rects;

    std::array <
        std::array <struct Rectangle, MandelbrotRectangles::NUM_COLS>,
        MandelbrotRectangles::NUM_ROWS> m_rects;

    std::deque<std::packaged_task<size_t(HWND, HDC, struct Rectangle)>> m_tasks;
    std::deque<std::packaged_task<size_t(std::stop_token, HWND, HDC, struct Rectangle)>> m_tasksEx;
    std::deque<std::future<size_t>> m_futures;

    mutable std::mutex m_mutex;
    std::atomic<bool> m_abort;
    std::atomic<int> m_doneRectangles;
    std::stop_source m_source;

    std::condition_variable m_conditionPixelsAvailable;
    std::queue <Pixel> m_pixels;

    // "producer/consumer" based data
    HWND m_hWnd;
    HDC m_hDC;

    std::deque<std::packaged_task<size_t(struct Rectangle, size_t, size_t)>> m_CalculationTasks;
    std::deque<std::future<size_t>> m_CalculationFutures;
    std::packaged_task<size_t()> m_DrawingTask;
    std::future<void> m_DrawingFuture;

public:
    // c'tor
    Mandelbrot();

    // getter/setter
    void setClientWidth(size_t clientWidth) { m_clientWidth = clientWidth; }
    size_t getClientWidth() const { return m_clientWidth; }

    void setClientHeight(size_t clientHeight) { m_clientHeight = clientHeight; }
    size_t getClientHeight() const { return m_clientHeight; }

    int  getDoneRectangles() { return m_doneRectangles; }
    void incDoneRectangles() { ++m_doneRectangles; }
    void resetDoneRectangles() { m_doneRectangles = 0; }

    // 1. Variante
    void setAbort(bool flag) { m_abort = flag; }
    bool getAbort() const { return m_abort; }

    // 2. Variante
    void requestAbort() { m_source.request_stop(); }

    // public interface
    void computeRects();
    void paint(HDC);
    void paintRectangles(HDC);
    void paintRectanglesAsync(HDC hDC);
    void paintRectanglesAsyncWithLatch(HDC hDC);

    // Redesign
    void startPaintingRectanglesAsync(HWND, HDC);
    void startPaintingRectanglesAsyncEx(HWND, HDC);
    void waitRectanglesDone();

    // public "producer - consumer" interface

    // TODO: Welche dieser MEthoden können privat deklariert werden .....
    void setHWND(HWND hWnd);
    void addPixel(Pixel);
    void notify();
    size_t computePixel(struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    void drawPixel();
    void startCalculationThread();
    void startDrawingThread();

private:
    // private helper methods
    void paintRect(HDC, struct Rectangle);
    std::pair<std::wstring, size_t> paintRectAsync(HDC, struct Rectangle);
    size_t startPaintRectAsync(HWND, HDC, struct Rectangle);
    size_t startPaintRectAsyncEx(std::stop_token token, HWND, HDC, struct Rectangle);

    template <typename T>
    constexpr std::complex<T> getComplex(size_t x, size_t y, size_t max_x, size_t max_y) const;

    template <typename T>
    size_t computeSequence(std::complex<T> point) const;
};


#endif

// =====================================================================================
// End-of-File
// =====================================================================================

