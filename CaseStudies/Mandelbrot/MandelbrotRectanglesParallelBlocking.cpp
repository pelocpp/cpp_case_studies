// =====================================================================================
// MandelbrotRectanglesSequential.cpp
// Variant 03: Parallel - Blocking
// =====================================================================================

#pragma once

#include "MandelbrotGeneral.h"
#include "MandelbrotRectanglesParallelBlocking.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)
MandelbrotRectanglesParallelBlocking::MandelbrotRectanglesParallelBlocking() {}

// public interface
void MandelbrotRectanglesParallelBlocking::paintRectanglesAsync (HDC hDC) const {

    // setup tasks
    std::deque<std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [this] () {
            return std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)> {
                [this](HDC hDC, struct Rectangle rect) {
                    return paintRectangleAsync(hDC, rect);
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
        }
    }

    // retrieve results
    while (!futures.empty()) {

        auto future{ std::move(futures.front()) };
        futures.pop_front();
        const auto& [tid, pixels] = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64,
            L"Thread %ls:  painted %zu pixels", tid.c_str(), pixels);
        ::OutputDebugString(szText);
    }
}

// private helper functions
//std::pair<std::wstring, size_t> MandelbrotRectanglesParallelBlocking::paintRectangleAsync(HDC hDC, struct Rectangle rect) const {
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
