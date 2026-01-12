// =====================================================================================
// Mandelbrot_03_RectanglesParallelBlocking.cpp
// Variant 03: Parallel - Blocking
// =====================================================================================

#include "MandelbrotCommon.h"
#include "MandelbrotPalette.h"
#include "Mandelbrot_03_RectanglesParallelBlocking.h"

#include <complex>
#include <deque>
#include <future>
#include <algorithm>

// c'tor(s)
MandelbrotRectanglesParallelBlocking::MandelbrotRectanglesParallelBlocking() {}

// public interface
void MandelbrotRectanglesParallelBlocking::paintRectanglesAsync (HDC hDC) const {

    // setup tasks
    std::deque<std::packaged_task<std::pair<std::wstring, std::size_t>(HDC, struct Rectangle)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [this] () {
            return std::packaged_task<std::pair<std::wstring, std::size_t>(HDC, struct Rectangle)> {
                [this](HDC hDC, struct Rectangle rect) {
                    return paintRectangle(hDC, rect);
                }
            };
        }
    );

    // retrieve futures from these tasks
    std::deque<std::future<std::pair<std::wstring, std::size_t>>> futures;
    futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        tasks.begin(),
        tasks.end(),
        futures.begin(),
        [](std::packaged_task<std::pair<std::wstring, std::size_t>(HDC, struct Rectangle)>& task) {
            return task.get_future();
        }
    );

    // launch these tasks each in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            auto task{ std::move(tasks.front()) };
            tasks.pop_front();

            std::jthread t{ std::move(task), hDC, rect };
            t.detach();
        }
    }

    // retrieve results
    while (!futures.empty()) {

        auto future{ std::move(futures.front()) };
        futures.pop_front();
        const auto& [tid, pixels] = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"Thread %ls:  painted %zu pixels\n", tid.c_str(), pixels);
        ::OutputDebugString(szText);
    }
}


void MandelbrotRectanglesParallelBlocking::drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const
{
    // RAII lock
    std::lock_guard<std::mutex> guard{ m_mutex };
    ::SetPixelV(hdc, (int) x, (int) y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
