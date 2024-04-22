// =====================================================================================
// MandelbrotRectanglesSequential.cpp
// Variant 02: Rectangles Sequential
// =====================================================================================

#pragma once

#include "MandelbrotGeneral.h"
#include "MandelbrotRectanglesSequential.h"
#include "MandelbrotPalette.h"

#include <complex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesSequential::MandelbrotRectanglesSequential() {}

void MandelbrotRectanglesSequential::paintRectanglesSequential(HDC hDC) const {

    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            paintRectangle(hDC, rectangle);
        }
    }
}

void MandelbrotRectanglesSequential::paintRectangle(HDC hDC, struct Rectangle rect) const {

    for (size_t y{ rect.m_top }; y < rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x < rect.m_right; x++) {

            std::complex<TFloatingPoint> number {
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence<TFloatingPoint>(number) };
            COLORREF color{ g_palette[iterations - 1] };
            
            // ::SetPixelV(hDC, (int) x, (int) y, color);
            drawPixel(hDC, (int)x, (int)y, color);
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
