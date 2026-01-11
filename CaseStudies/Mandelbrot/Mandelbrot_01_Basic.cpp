// =====================================================================================
// Mandelbrot_01_Basic.cpp
// Variant 01: Basic Version
// =====================================================================================

#include "MandelbrotCommon.h"
#include "Mandelbrot_01_Basic.h"
#include "MandelbrotPalette.h"

#include <complex>

// TODO : Das muss anders werden
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotBasic::MandelbrotBasic() {}

void MandelbrotBasic::drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const
{
    ::SetPixelV(hdc, (int) x, (int) y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
