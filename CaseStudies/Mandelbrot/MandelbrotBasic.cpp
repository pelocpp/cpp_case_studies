// =====================================================================================
// MandelbrotBasic.cpp
// Variant 01: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotGeneral.h"
#include "MandelbrotBasic.h"

#include "MandelbrotPalette.h"

#include <complex>

// TODO : Das muss anders werden
extern MandelbrotPalette g_palette;


// c'tor(s)
MandelbrotBasic::MandelbrotBasic() {}

// public interface
void MandelbrotBasic::paint(HDC hDC) {

    for (size_t y{}; y != m_clientHeight; y++)
    {
        for (size_t x{}; x != m_clientWidth; x++) {

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence<TFloatingPoint>(number) };
            COLORREF cr{ g_palette[iterations - 1] };

            // ::SetPixelV(hDC, (int)x, (int)y, cr);
            drawPixel(hDC, (int)x, (int)y, cr);
        }
    }
}

void MandelbrotBasic::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    ::SetPixelV(hdc, x, y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
