// =====================================================================================
// MandelbrotRectanglesSequential.cpp
// Variant 02: Rectangles Sequential
// =====================================================================================

#include "MandelbrotGeneral.h"
#include "MandelbrotRectanglesSequential.h"
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

void MandelbrotRectanglesSequential::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    ::SetPixelV(hdc, x, y, color);
}


// =====================================================================================
// End-of-File
// =====================================================================================
