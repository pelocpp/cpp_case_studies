// =====================================================================================
// Mandelbrot_03_RectanglesParallelBlocking.h
// Variant 03: Parallel - Blocking
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <mutex>

class MandelbrotRectanglesParallelBlocking : public MandelbrotBase
{
private:
    mutable std::mutex m_mutex;

public:
    // c'tor(s)
    MandelbrotRectanglesParallelBlocking();

public:
    // public interface
    void paintRectanglesAsync(HDC hDC) const;

private:
    virtual void drawPixel(HDC hdc, size_t x, size_t y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
