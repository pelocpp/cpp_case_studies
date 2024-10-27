// =====================================================================================
// MandelbrotRectanglesParallelNonBlockingClassic.cpp
// Variant 05: Parallel - Non Blocking - Classic Variant
// =====================================================================================

#include "MandelbrotCommon.h"
#include "Mandelbrot_05_RectanglesParallelNonBlockingClassic.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesParallelNonBlockingClassic::MandelbrotRectanglesParallelNonBlockingClassic() 
    : m_doneRectangles{ MandelbrotRectangles::NUM_RECTS }
{}

//public interface
void MandelbrotRectanglesParallelNonBlockingClassic::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {

    // clear member data
    resetDoneRectangles();

    m_tasks.clear();
    m_futures.clear();

    // setup tasks
    m_tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        m_tasks.begin(),
        m_tasks.end(),
        [this] () {
            return std::packaged_task<size_t(HWND, HDC, struct Rectangle)> {
                [this](HWND hWnd, HDC hDC, struct Rectangle rect) {
                    return paintRectangle(hWnd, hDC, rect);
                }
            };
        }
    );

    // retrieve futures from these tasks
    m_futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        m_tasks.begin(),
        m_tasks.end(),
        m_futures.begin(),
        [](std::packaged_task<size_t(HWND, HDC, struct Rectangle)>& task) {
            return task.get_future();
        }
    );

    // launch these tasks each in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            auto task{ std::move(m_tasks.front()) };
            m_tasks.pop_front();

            std::jthread t{ std::move(task), hWnd, hDC, rect };
            t.detach();
        }
    }
}

void MandelbrotRectanglesParallelNonBlockingClassic::waitRectanglesDone() {

    while (!m_futures.empty()) {

        std::future<size_t> future = std::move(m_futures.front());
        m_futures.pop_front();
        size_t numPixels{ future.get() };

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"   ... %zu pixels painted", numPixels);
        OutputDebugString(szText);
    }
}

// private helper functions
size_t MandelbrotRectanglesParallelNonBlockingClassic::paintRectangle(HWND hWnd, HDC hDC, struct Rectangle rect) {

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            // premature end of drawing
            if (m_abort == true) {
                goto m_label;
            }

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            COLORREF color{ g_palette[iterations - 1] };
            ++numPixels;

            drawPixel(hDC, (int)x, (int)y, color);
        }
    }

    m_label:

    incDoneRectangles();
    if (getDoneRectangles() == MandelbrotRectangles::NUM_RECTS) {

        ::ReleaseDC(hWnd, hDC);
    }

    return numPixels;
}

void MandelbrotRectanglesParallelNonBlockingClassic::drawPixel(HDC hdc, size_t x, size_t y, COLORREF color) const
{
    // RAII lock
    std::lock_guard<std::mutex> guard{ m_mutex };

    ::SetPixelV(hdc, (int) x, (int) y, color);
}


// =====================================================================================
// End-of-File
// =====================================================================================
