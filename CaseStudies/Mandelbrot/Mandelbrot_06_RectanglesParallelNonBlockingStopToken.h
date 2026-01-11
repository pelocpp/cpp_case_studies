// =====================================================================================
// Mandelbrot_06_RectanglesParallelNonBlockingStopToken.h
// Variant 06: Parallel - Non Blocking - Stop Token
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <cstddef>
#include <deque>
#include <future>
#include <mutex>
#include <stop_token>
#include <thread>

class MandelbrotRectanglesParallelNonBlockingStopToken : public MandelbrotBase
{
private:
    mutable std::mutex    m_mutex;

    std::atomic<std::size_t>   m_doneRectangles;
    std::stop_source           m_source;

    std::deque<std::packaged_task<std::size_t(std::stop_token, HWND, HDC, struct Rectangle)>> m_tasks;
    std::deque<std::future<std::size_t>>                                                      m_futures;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelNonBlockingStopToken();

    // getter / setter
    std::size_t getDoneRectangles()   { return m_doneRectangles; }
    void   incDoneRectangles()        { ++m_doneRectangles; }
    void   resetDoneRectangles()      { m_doneRectangles = 0; }

    void   requestStop()              { m_source.request_stop(); }

public:
    // public interface
    void startPaintingRectanglesAsync(HWND hWnd, HDC hDC);
    void waitRectanglesDone();

private:
    // private helper functions
    std::size_t paintRectangle(std::stop_token, HWND, HDC, struct Rectangle);

private:
    virtual void drawPixel(HDC, std::size_t x, std::size_t y, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
