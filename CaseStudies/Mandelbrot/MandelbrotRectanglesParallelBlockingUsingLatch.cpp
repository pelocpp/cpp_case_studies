// =====================================================================================
// MandelbrotRectanglesParallelBlockingUsingLatch.cpp
// Variant 04: Parallel - Blocking - Using Latch
// =====================================================================================

#pragma once

#include "MandelbrotGeneral.h"
#include "MandelbrotRectanglesParallelBlockingUsingLatch.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <algorithm>
//#include <mutex>
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
        [&, this]() {
            return std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)> {
                [&, this](HDC hDC, struct Rectangle rect) {
                    auto result = paintRectangleAsync(hDC, rect);
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

            std::thread thread{ std::move(task), hDC, rect };
            thread.detach();
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

// private helper functions
//std::pair<std::wstring, size_t> MandelbrotRectanglesParallelBlockingUsingLatch::paintRectangleAsync(HDC hDC, struct Rectangle rect) const {
//
//    std::thread::id tid{ std::this_thread::get_id() };
//
//    size_t numPixels{};
//
//    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
//    {
//        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
//        {
//            std::complex<TFloatingPoint> number{
//                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
//            };
//
//            size_t iterations{ computeSequence(number) };
//            COLORREF cr{ g_palette[iterations - 1] };
//            ++numPixels;
//
//            {
//                // RAII lock
//                std::lock_guard<std::mutex> lock{ m_mutex };
//                ::SetPixelV(hDC, (int) x, (int) y, cr);
//            }
//        }
//    }
//
//    std::wstringstream ss;
//    ss << tid;
//
//    return { ss.str(), numPixels };
//}

// =====================================================================================
// End-of-File
// =====================================================================================
