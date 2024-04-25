// =====================================================================================
// MandelbrotRectanglesParallelNonBlockingStopToken.h
// Variant 06: Parallel - Non Blocking - Stop Token
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <mutex>
#include <deque>
#include <future>

class MandelbrotRectanglesParallelNonBlockingStopToken : public MandelbrotBase
{
private:
    mutable std::mutex m_mutex;

    std::atomic<int> m_doneRectangles;
  //  std::atomic<bool> m_abort;
    std::stop_source m_source;

    std::deque<std::packaged_task<size_t(HWND, HDC, struct Rectangle)>> m_tasks;
    std::deque<std::future<size_t>> m_futures;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelNonBlockingStopToken();

    // getter / setter
    int  getDoneRectangles() { return m_doneRectangles; }
    void incDoneRectangles() { ++m_doneRectangles; }
    void resetDoneRectangles() { m_doneRectangles = 0; }

  //  void setAbort(bool flag) { m_abort = flag; }
    //  bool getAbort() const { return m_abort; }
    void requestAbort() { m_source.request_stop(); }

public:
    // public interface
    void startPaintingRectanglesAsync(HWND hWnd, HDC hDC);
    void waitRectanglesDone();

private:
    // private helper functions
    size_t startPaintRectAsync(std::stop_token token, HWND hWnd, HDC hDC, struct Rectangle rect);

private:
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

