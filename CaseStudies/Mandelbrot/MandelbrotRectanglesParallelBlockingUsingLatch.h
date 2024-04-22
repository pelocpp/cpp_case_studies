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
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;

private:
    // private helper functions
    // std::pair<std::wstring, size_t> paintRectangleAsync(HDC hDC, struct Rectangle rect) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================

