// =====================================================================================
// MandelbrotRectanglesParallelBlockingUsingLatch.h
// Variant 04: Parallel - Blocking - Using Latch
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <mutex>

class MandelbrotRectanglesParallelBlockingUsingLatch : public MandelbrotBase
{
private:
    mutable std::mutex m_mutex;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelBlockingUsingLatch();

public:
    // public interface
    void paintRectanglesAsyncWithLatch(HDC hDC) const;

private:
    virtual void drawPixel(HDC hdc, size_t x, size_t y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

