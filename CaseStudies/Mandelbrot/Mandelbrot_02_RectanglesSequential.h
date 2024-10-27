// =====================================================================================
// Mandelbrot_02_RectanglesSequential.h
// Variant 02: Drawing Rectangles Sequential
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

class MandelbrotRectanglesSequential : public MandelbrotBase
{
public:
    // c'tor(s)
    MandelbrotRectanglesSequential();

public:
    // public interface
    void paintRectangles(HDC hDC) const;

private:
    virtual void drawPixel(HDC hdc, size_t x, size_t y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
