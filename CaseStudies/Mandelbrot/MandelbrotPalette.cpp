// =====================================================================================
// MandelbrotPalette.cpp
// =====================================================================================

#include <complex>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <thread>
#include <future>
#include <utility>
#include <functional> 
#include <mutex>

#include "framework.h"

#include "MandelbrotPalette.h"
#include "MandelbrotHelper.h"

// =====================================================================================

/* constexpr */ MandelbrotPalette::MandelbrotPalette() {
    init();
}

/* constexpr */ void MandelbrotPalette::init()
{
    m_palette.reserve(Mandelbrot::NumColors);

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 32; ++x) {
        m_palette.push_back(RGB(x * 32 * 255 / Mandelbrot::NumColors, 0, 0));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 32; ++x) {
        m_palette.push_back(RGB(255, x * 32 * 255 / Mandelbrot::NumColors, 0));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 16; ++x) {
        m_palette.push_back(RGB(((Mandelbrot::NumColors / 16 - x) * 16) * 255 / Mandelbrot::NumColors, 255, 0));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 16; ++x) {
        m_palette.push_back(RGB(0, ((Mandelbrot::NumColors / 16 - x) * 16) * 255 / Mandelbrot::NumColors, x * 16 * 255 / Mandelbrot::NumColors));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 16; ++x) {
        m_palette.push_back(RGB(x * 16 * 255 / Mandelbrot::NumColors, 0, 255));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 4; ++x) {
        m_palette.push_back(RGB(((Mandelbrot::NumColors / 4 - x) * 4) * 255 / Mandelbrot::NumColors, x * 4 * 255 / Mandelbrot::NumColors, 255));
    }

    for (unsigned int x = 0; x < Mandelbrot::NumColors / 2; ++x) {
        m_palette.push_back(RGB(x * 2 * 255 / Mandelbrot::NumColors, 255, 255));
    }

    m_palette[Mandelbrot::NumColors - 1] = RGB(0, 0, 0);  // last color is black
}

/* constexpr */ COLORREF MandelbrotPalette::operator[] (int index) const {

    if (index >= Mandelbrot::NumColors) {
        throw std::out_of_range("illegal palette index");
    }

    return m_palette[index];
}

// =====================================================================================
// End-of-File
// =====================================================================================
