// =====================================================================================
// Mandelbrot_06_RectanglesParallelNonBlockingStopToken.cpp
// Variant 06: Parallel - Non Blocking - Stop Token
// =====================================================================================

#include "MandelbrotCommon.h"
#include "Mandelbrot_06_RectanglesParallelNonBlockingStopToken.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>
#include <thread>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesParallelNonBlockingStopToken::MandelbrotRectanglesParallelNonBlockingStopToken()
    : m_doneRectangles{ MandelbrotRectangles::NUM_RECTS }
{}

//public interface
void MandelbrotRectanglesParallelNonBlockingStopToken::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {

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
            return std::packaged_task<std::size_t(std::stop_token, HWND, HDC, struct Rectangle)> {
                [this](std::stop_token token, HWND hWnd, HDC hDC, struct Rectangle rect) {
                    return paintRectangle(token, hWnd, hDC, rect);
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
        [](std::packaged_task<std::size_t(std::stop_token, HWND, HDC, struct Rectangle)>& task) {
            return task.get_future();
        }
    );

    // creating a new std::stop_source object for this execution
    m_source = std::stop_source{};

    // need stop_token object
    std::stop_token token{ m_source.get_token() };

    // launch these tasks each in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            auto task{ std::move(m_tasks.front()) };
            m_tasks.pop_front();

            std::jthread t{ std::move(task), token, hWnd, hDC, rect };
            t.detach();
        }
    }
}

void MandelbrotRectanglesParallelNonBlockingStopToken::waitRectanglesDone() {

    while (!m_futures.empty()) {

        std::future<std::size_t> future{ std::move(m_futures.front()) };
        m_futures.pop_front();
        std::size_t numPixels = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"   ... %zu pixels painted", numPixels);
        OutputDebugString(szText);
    }
}

// private helper functions
std::size_t MandelbrotRectanglesParallelNonBlockingStopToken::paintRectangle(std::stop_token token, HWND hWnd, HDC hDC, struct Rectangle rect) {

    std::size_t numPixels{};
    bool prematureEndOfPainting{ false };

    for (std::size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (std::size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            // premature end of drawing
            if (token.stop_requested()) {
                prematureEndOfPainting = true;
                goto loopEnd;
            }

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            std::size_t iterations{ computeSequence(number) };
            COLORREF color{ g_palette[iterations - 1] };
            ++numPixels;

            drawPixel(hDC, (int) x, (int) y, color);
        }
    }

    loopEnd:
    incDoneRectangles();
    if (getDoneRectangles() == MandelbrotRectangles::NUM_RECTS) {

        ::ReleaseDC(hWnd, hDC);
    }

    if (!prematureEndOfPainting) {

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"   ... %zu pixels painted", numPixels);
        OutputDebugString(szText);
    }
    
    return numPixels;
}

void MandelbrotRectanglesParallelNonBlockingStopToken::drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const
{
    // RAII lock
    std::lock_guard<std::mutex> guard{ m_mutex };

    ::SetPixelV(hdc, (int) x, (int) y, color);
}


// =====================================================================================
// End-of-File
// =====================================================================================
