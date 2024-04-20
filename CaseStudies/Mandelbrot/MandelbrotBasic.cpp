// =====================================================================================
// MandelbrotBasic.cpp
// Variant: Basic Version
// =====================================================================================

#pragma once

#include "framework.h"

#include "MandelbrotGeneral.h"
#include "MandelbrotBasic.h"


#include "MandelbrotPalette.h"

#include <complex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotBasic::MandelbrotBasic() //:
    //m_abort{ false }, m_doneRectangles{ MandelbrotRectangles::NUM_RECTS },
    //m_clientWidth{}, m_clientHeight{}, m_numRows{}, m_numCols{},
    //m_hWnd{}, m_hDC{}, m_rects{}
{}

// public interface
void MandelbrotBasic::computeRects()
{
    // adjust total client width and height according to number of rectangles
    size_t clientWidth{ m_clientWidth - (m_clientWidth % MandelbrotRectangles::NUM_COLS) };
    size_t clientHeight{ m_clientHeight - (m_clientHeight % MandelbrotRectangles::NUM_ROWS) };

    // calculate size of a single rectangle
    size_t rectWidth{ clientWidth / MandelbrotRectangles::NUM_COLS };
    size_t rectHeight{ clientHeight / MandelbrotRectangles::NUM_ROWS };

    // calculate coordinates of each rectangle
    for (size_t i{}; i != MandelbrotRectangles::NUM_ROWS; i++)
    {
        for (size_t j{}; j != MandelbrotRectangles::NUM_COLS; j++) {
                
            m_rects[i][j] = {
                (j * rectWidth), (i * rectHeight),
                ((j + 1) * rectWidth - 1), ((i + 1) * rectHeight - 1)
            };
        }
    }
}

void MandelbrotBasic::paint(HDC hDC) {

    for (size_t y{}; y != m_clientHeight; y++)
    {
        for (size_t x{}; x != m_clientWidth; x++) {

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            // COLORREF cr{ m_palette[iterations - 1] };
            COLORREF cr{ g_palette[iterations - 1] };
            ::SetPixelV(hDC, (int)x, (int)y, cr);
        }
    }
}

// private helper methods
template <typename T>
std::complex<T> MandelbrotBasic::getComplex(size_t x, size_t y, size_t maxWidth, size_t maxHeight) const
{
    // short hand constants for the Mandelbrot coordinates system
    static T XMIN = MandelbrotParams<T>::XMIN;
    static T XMAX = MandelbrotParams<T>::XMAX;
    static T YMIN = MandelbrotParams<T>::YMIN;
    static T YMAX = MandelbrotParams<T>::YMAX;

    return std::complex<T> {
        XMIN + (XMAX - XMIN) * x / maxWidth, YMAX + (YMIN - YMAX) * y / maxHeight
    };
}


template <typename T>
size_t MandelbrotBasic::computeSequence(std::complex<T> point) const
{
    std::complex<T> number{};
    size_t count{};

    while (count != NumColors && std::abs(number) < Limit) {
        number = number * number + point;
        ++count;
    }

    return count;
}


// =====================================================================================
// End-of-File
// =====================================================================================
