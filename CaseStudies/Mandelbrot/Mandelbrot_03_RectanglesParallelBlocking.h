// =====================================================================================
// Mandelbrot_03_RectanglesParallelBlocking.h
// Variant 03: Parallel - Blocking
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <cstddef>    // std::size_t
#include <mutex>      // std::mutex

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
    virtual void drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
