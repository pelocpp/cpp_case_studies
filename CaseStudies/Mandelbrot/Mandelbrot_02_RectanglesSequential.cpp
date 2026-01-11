// =====================================================================================
// Mandelbrot_02_RectanglesSequential.cpp
// Variant 02: Rectangles Sequential
// =====================================================================================

#include "MandelbrotCommon.h"
#include "Mandelbrot_02_RectanglesSequential.h"
#include "MandelbrotPalette.h"

#include <complex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesSequential::MandelbrotRectanglesSequential() {}

void MandelbrotRectanglesSequential::paintRectangles(HDC hDC) const {

    for (const auto& row : m_rects) {

        for (const auto& rectangle : row) {

            paintRectangle(hDC, rectangle);
        }
    }
}

void MandelbrotRectanglesSequential::drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const
{
    ::SetPixelV(hdc, (int) x, (int) y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
