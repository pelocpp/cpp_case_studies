// =====================================================================================
// MandelbrotBasic.cpp
// Variant 01: Basic Version
// =====================================================================================

#include "MandelbrotGeneral.h"
#include "MandelbrotBasic.h"
#include "MandelbrotPalette.h"

#include <complex>

// TODO : Das muss anders werden
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotBasic::MandelbrotBasic() {}

void MandelbrotBasic::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    ::SetPixelV(hdc, x, y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
