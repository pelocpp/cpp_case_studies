// =====================================================================================
// MandelbrotRectanglesParallelBlocking.h
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
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;

private:
    // private helper functions
    // std::pair<std::wstring, size_t> paintRectangleAsync(HDC hDC, struct Rectangle rect) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
