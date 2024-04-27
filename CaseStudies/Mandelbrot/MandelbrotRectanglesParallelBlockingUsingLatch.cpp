// =====================================================================================
// MandelbrotRectanglesParallelBlockingUsingLatch.cpp
// Variant 04: Parallel - Blocking - Using Latch
// =====================================================================================

#include "MandelbrotCommon.h"
#include "MandelbrotRectanglesParallelBlockingUsingLatch.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <algorithm>
#include <latch>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesParallelBlockingUsingLatch::MandelbrotRectanglesParallelBlockingUsingLatch() {}

// public interface
void MandelbrotRectanglesParallelBlockingUsingLatch::paintRectanglesAsyncWithLatch(HDC hDC) const {

    // working with a latch object
    std::latch paintedAllRectangles{ MandelbrotRectangles::NUM_RECTS };

    // setup tasks
    std::deque<std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [&, this] () {
            return std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)> {
                [&, this](HDC hDC, struct Rectangle rect) {
                    auto result = paintRectangle(hDC, rect);
                    paintedAllRectangles.count_down();
                    return result;
                }
            };
        }
    );

    // retrieve futures from these tasks
    std::deque<std::future<std::pair<std::wstring, size_t>>> futures;
    futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        tasks.begin(),
        tasks.end(),
        futures.begin(),
        [](std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)>& task) {
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

    // block until all work is done
    paintedAllRectangles.wait();
    OutputDebugString(L"All calculations done :)");

    // retrieve results
    while (!futures.empty()) {

        auto future{ std::move(futures.front()) };
        futures.pop_front();
        const auto& [tid, pixels] = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64,
            L"Thread %ls:  painted %zi pixels", tid.c_str(), pixels);
        OutputDebugString(szText);
    }
}

void MandelbrotRectanglesParallelBlockingUsingLatch::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    // RAII lock
    std::lock_guard<std::mutex> lock{ m_mutex };
    ::SetPixelV(hdc, x, y, color);
}

// =====================================================================================
// End-of-File
// =====================================================================================
