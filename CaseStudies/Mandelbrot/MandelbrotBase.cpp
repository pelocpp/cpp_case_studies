// =====================================================================================
// MandelbrotBase.cpp
// =====================================================================================

#pragma once

#include "MandelbrotGeneral.h"
#include "MandelbrotBase.h"

#include "MandelbrotPalette.h"

MandelbrotBase::MandelbrotBase() :
    m_clientWidth{}, m_clientHeight{}, m_rects{}
{}


// proteced interface
void MandelbrotBase::computeRects()
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

// =====================================================================================
// End-of-File
// =====================================================================================
