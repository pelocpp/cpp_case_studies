// =====================================================================================
// MandelbrotBase.cpp
// =====================================================================================

#include "MandelbrotCommon.h"
#include "MandelbrotBase.h"

#include "MandelbrotPalette.h"

#include <thread>
#include <mutex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;


MandelbrotBase::MandelbrotBase() :
    m_clientWidth{}, m_clientHeight{}, m_rects{}
{}

// proteced interface
void MandelbrotBase::computeRects(int rows, int cols)
{
    // adjust total client width and height according to number of rectangles
    size_t clientWidth{ m_clientWidth - (m_clientWidth % cols) };
    size_t clientHeight{ m_clientHeight - (m_clientHeight % rows) };

    // calculate size of a single rectangle
    size_t rectWidth{ clientWidth / cols };
    size_t rectHeight{ clientHeight / rows };

    // calculate coordinates of each rectangle
    for (size_t i{}; i != rows; i++)
    {
        for (size_t j{}; j != cols; j++) {

            m_rects[i][j] = {
                (j * rectWidth), (i * rectHeight),
                ((j + 1) * rectWidth - 1), ((i + 1) * rectHeight - 1)
            };
        }
    }
}

// protected helper functions
std::pair<std::wstring, size_t> MandelbrotBase::paintRectangle(HDC hDC) const
{
    return paintRectangle(hDC, m_rects[0][0]);
}

std::pair<std::wstring, size_t> MandelbrotBase::paintRectangle(HDC hdc, struct Rectangle rect) const
{
    std::jthread::id tid{ std::this_thread::get_id() };

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            std::complex<TFloatingPoint> comp {
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(comp) };
            COLORREF color{ g_palette[iterations - 1] };

            // draw pixel - either directly or thread safe
            drawPixel(hdc, (int) x, (int) y, color);
            ++numPixels;
        }
    }

    std::wstringstream ss;
    ss << tid;

    return { ss.str(), numPixels };
}

// =====================================================================================
// End-of-File
// =====================================================================================
