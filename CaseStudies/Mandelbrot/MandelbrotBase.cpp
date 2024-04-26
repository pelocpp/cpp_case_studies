// =====================================================================================
// MandelbrotBase.cpp
// =====================================================================================

#include "MandelbrotGeneral.h"
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

// protected helper functions
std::pair<std::wstring, size_t> MandelbrotBase::paintRectangleAsync(HDC hdc, struct Rectangle rect) const
{
    std::thread::id tid{ std::this_thread::get_id() };

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            COLORREF color{ g_palette[iterations - 1] };
            ++numPixels;

            // virtual !!!!!!!!!!!!!
            drawPixel(hdc, (int) x, (int) y, color);

            //{
            //    // RAII lock
            //     hier eine virtual function in der abgeleiteten Klasse
            //    dann auch die Basic-FUntion umleiten auf diese !!!!!!!
            //    std::lock_guard<std::mutex> lock{ m_mutex };
            //    ::SetPixelV(hDC, (int)x, (int)y, cr);
            //}
        }
    }

    std::wstringstream ss;
    ss << tid;

    return { ss.str(), numPixels };
}


// =====================================================================================
// End-of-File
// =====================================================================================
