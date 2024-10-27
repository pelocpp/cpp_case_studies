// =====================================================================================
// Mandelbrot_05_RectanglesParallelNonBlockingClassic.h
// Variant 05: Parallel - Non Blocking - Classic Variant
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <thread>
#include <mutex>
#include <deque>
#include <future>

class MandelbrotRectanglesParallelNonBlockingClassic : public MandelbrotBase
{
private:
    mutable std::mutex m_mutex;

    std::atomic<size_t>  m_doneRectangles;
    std::atomic<bool>    m_abort;

    std::deque<std::packaged_task<size_t(HWND, HDC, struct Rectangle)>> m_tasks;
    std::deque<std::future<size_t>> m_futures;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelNonBlockingClassic();

    // getter / setter
    size_t getDoneRectangles() { return m_doneRectangles; }
    void incDoneRectangles()   { ++m_doneRectangles; }
    void resetDoneRectangles() { m_doneRectangles = 0; }

    void setAbort(bool flag)   { m_abort = flag; }

public:
    // public interface
    void startPaintingRectanglesAsync(HWND hWnd, HDC hDC);
    void waitRectanglesDone();
    
private:
    // private helper functions
    size_t paintRectangle(HWND, HDC, struct Rectangle);

private:
    virtual void drawPixel(HDC, size_t x, size_t y, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

