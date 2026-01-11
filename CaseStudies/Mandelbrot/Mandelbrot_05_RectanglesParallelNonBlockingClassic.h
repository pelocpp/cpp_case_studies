// =====================================================================================
// Mandelbrot_05_RectanglesParallelNonBlockingClassic.h
// Variant 05: Parallel - Non Blocking - Classic Variant
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <deque>     // std::deque
#include <future>    // std::packaged_task, std::future
#include <mutex>     // std::mutex
// #include <thread>
#include <cstddef>   // std::size_t

class MandelbrotRectanglesParallelNonBlockingClassic : public MandelbrotBase
{
private:
    mutable std::mutex m_mutex;

    std::atomic<std::size_t>  m_doneRectangles;
    std::atomic<bool>    m_abort;

    std::deque<std::packaged_task<std::size_t(HWND, HDC, struct Rectangle)>> m_tasks;
    std::deque<std::future<std::size_t>>                                     m_futures;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelNonBlockingClassic();

    // getter / setter
    std::size_t getDoneRectangles() { return m_doneRectangles; }
    void incDoneRectangles()   { ++m_doneRectangles; }
    void resetDoneRectangles() { m_doneRectangles = 0; }

    void setAbort(bool flag)   { m_abort = flag; }

public:
    // public interface
    void startPaintingRectanglesAsync(HWND hWnd, HDC hDC);
    void waitRectanglesDone();
    
private:
    // private helper functions
    std::size_t paintRectangle(HWND, HDC, struct Rectangle);

private:
    virtual void drawPixel(HDC, std::size_t x, std::size_t y, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

