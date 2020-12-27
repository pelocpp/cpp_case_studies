// =====================================================================================
// Lambda Methods
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

namespace MandelbrotBasisVersion {

    constexpr MandelbrotVersion g_version = MandelbrotVersion::ProducerConsumerBasedApproach;

    Mandelbrot::Mandelbrot() {
        m_version = g_version;
        m_abort = false;
        m_doneRectangles = MandelbrotRectangles::NUM_RECTS;
    }

    void Mandelbrot::computeRects() {

        // adjust total client width and height according to number of rectangles
        long clientWidth = m_clientWidth - (m_clientWidth % MandelbrotRectangles::NUM_COLS);
        long clientHeight = m_clientHeight - (m_clientHeight % MandelbrotRectangles::NUM_ROWS);

        // calculate size of a single rectangle
        long rectWidth = clientWidth / MandelbrotRectangles::NUM_COLS;
        long rectHeight = clientHeight / MandelbrotRectangles::NUM_ROWS;

        // calculate coordinates of each rectangle
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                m_rects[j][i] = {
                    (LONG)(i * rectWidth),
                    (LONG)(j * rectHeight),
                    (LONG)((i + 1) * rectWidth - 1),
                    (LONG)((j + 1) * rectHeight - 1)
                };
            }
        }
    }

    template <typename T, typename MANDELBROT_COORDINATES>
    std::complex<T> Mandelbrot::getComplex(
        long x,
        long y,
        long maxWidth,
        long maxHeight)
    {
        // short hand constants for the Mandelbrot coordinates system
        static constexpr T XMIN = MANDELBROT_COORDINATES::XMIN;
        static constexpr T XMAX = MANDELBROT_COORDINATES::XMAX;
        static constexpr T YMIN = MANDELBROT_COORDINATES::YMIN;
        static constexpr T YMAX = MANDELBROT_COORDINATES::YMAX;

        return std::complex<T>(
            XMIN + (XMAX - XMIN) * x / maxWidth,
            YMAX + (YMIN - YMAX) * y / maxHeight
            );
    }

    void Mandelbrot::paint(HDC hDC) {

        using T = double;

        for (int y = 0; y < m_clientHeight; y++) {

            for (int x = 0; x < m_clientWidth; x++) {

                std::complex<T> c = getComplex<T, MandelbrotParams<T>>(
                    x, 
                    y,
                    m_clientWidth,
                    m_clientHeight);

                long iterations = computeSequence(c);
                COLORREF cr = m_palette[iterations - 1];
                ::SetPixelV(hDC, (int) x, (int) y, cr);
            }
        }
    }

    void Mandelbrot::paintRectangles(HDC hDC) {

        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
                paintRect(hDC, m_rects[j][i]);
            }
        }
    }

    void Mandelbrot::paintRectanglesAsync(HDC hDC) {

        std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;
        std::deque<std::future<std::pair<std::wstring, long>>> futures;

        // define tasks, store corresponding futures
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                using namespace std::placeholders;
                std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task{
                    std::bind(&Mandelbrot::paintRectAsync, this, _1, _2)
                };
                std::future<std::pair<std::wstring, long>> future = task.get_future();

                tasks.push_back(std::move(task));
                futures.push_back(std::move (future));
            }
        }

        // execute each task in a separate thread
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task =
                    std::move(tasks.front());

                tasks.pop_front();

                std::thread t(std::move(task), hDC, m_rects[j][i]);
                t.detach();
            }
        }

        // get the results
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                std::future<std::pair<std::wstring, long>> future =
                    std::move(futures.front());

                futures.pop_front();

                auto [tid, pixels]  = future.get();

                // print some statistics
                WCHAR szText[64];
                ::swprintf(szText, 64,
                    L"thread %ls:  painted %ld pixels\n", tid.c_str(), pixels);
                OutputDebugString(szText);
            }
        }
    }

    void Mandelbrot::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {

        m_doneRectangles = 0;

        m_tasks.clear();
        m_futures.clear();

        // define tasks, store corresponding futures
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                using namespace std::placeholders;
                std::packaged_task<long(HWND, HDC, RECT)> task{
                    std::bind(&Mandelbrot::startPaintRectAsync, this, _1, _2, _3)
                };
                std::future<long> future = task.get_future();

                m_tasks.push_back(std::move(task));
                m_futures.push_back(std::move(future));
            }
        }

        // execute each task in a separate thread
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                std::packaged_task<long(HWND, HDC, RECT)> task =
                    std::move(m_tasks.front());

                m_tasks.pop_front();

                std::thread t(std::move(task), hWnd, hDC, m_rects[j][i]);
                t.detach();
            }
        }
    }

    void Mandelbrot::waitRectanglesDone() {

        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                std::future<long> future = std::move(m_futures.front());
                m_futures.pop_front();
                long numPixels = future.get();

                // print some statistics
                WCHAR szText[64];
                ::swprintf(szText, 64,
                    L"   ... %ld pixels painted\n", numPixels);
                OutputDebugString(szText);
            }
        }
    }

    void Mandelbrot::paintRect(HDC hDC, RECT rect) {

        using T = double;

        for (int y = rect.top; y < rect.bottom; y++) {

            for (int x = rect.left; x < rect.right; x++) {

                std::complex<T> c = getComplex<T, MandelbrotParams<T>>(
                    x,
                    y,
                    m_clientWidth,
                    m_clientHeight);

                long iterations = computeSequence(c);
                COLORREF cr = m_palette[iterations - 1];
                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    std::pair<std::wstring, long> Mandelbrot::paintRectAsync(HDC hDC, RECT rect) {

        using T = double;

        std::thread::id tid = std::this_thread::get_id();

        long numPixels = 0;

        for (int y = rect.top; y < rect.bottom; y++) {

            for (int x = rect.left; x < rect.right; x++) {

                std::complex<T> c = getComplex<T, MandelbrotParams<T>>(
                    x,
                    y,
                    m_clientWidth,
                    m_clientHeight);

                unsigned int iterations = computeSequence(c);
                COLORREF cr = m_palette[iterations - 1];
                ++numPixels;

                // RAII lock
                std::scoped_lock<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, x, y, cr);
            }
        }

        std::wstringstream ss;
        ss << tid;

        return std::make_pair(ss.str(), numPixels);
    }

    long Mandelbrot::startPaintRectAsync(HWND hWnd, HDC hDC, RECT rect) {

        using T = double;

        long numPixels = 0;

        for (int y = rect.top; y < rect.bottom; y++) {

            for (int x = rect.left; x < rect.right; x++) {

                // premature end of drawing
                if (m_abort == true) {
                    break;
                }

                std::complex<T> c = getComplex<T, MandelbrotParams<T>>(
                    x,
                    y,
                    m_clientWidth,
                    m_clientHeight);

                unsigned int iterations = computeSequence(c);
                COLORREF cr = m_palette[iterations - 1];
                ++numPixels;

                // RAII lock
                std::scoped_lock<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, x, y, cr);
            }
        }

        m_doneRectangles++;
        if (m_doneRectangles == MandelbrotRectangles::NUM_RECTS) {

            ::ReleaseDC(hWnd, hDC);
        }

        return numPixels;
    }

    long Mandelbrot::computeSequence(std::complex<float> point)
    {
        std::complex<float> c(0.0);

        long count = 0;
        while (count < Mandelbrot::NumColors && std::abs(c) < Mandelbrot::Limit) {
            c = c * c + point;
            ++count;
        }

        return count;
    }

    void Mandelbrot::setHWND(HWND hWnd) {
        m_hWnd = hWnd;
        m_hDC = ::GetDC(m_hWnd);
    }

    void Mandelbrot::addPixel(Pixel pixel) {
        std::scoped_lock<std::mutex> lock(m_mutex);
        m_pixels.push(pixel);

        if (m_pixels.size() > 10) {
            m_conditionPixelsAvailable.notify_one();   // wakeup drawing thread
        }
    }

    void Mandelbrot::notify() {
       // std::scoped_lock<std::mutex> lock(g_mutex);
        m_conditionPixelsAvailable.notify_one();   // wakeup drawing thread
    }

    long Mandelbrot::computePixel(RECT rect, long maxWidth, long maxHeight) {

        ::OutputDebugString(L"> computePixel Begin\n");

        using T = double;

        long numPixels = 0;

        for (int y = rect.top; y < rect.bottom; y++) {

            for (int x = rect.left; x < rect.right; x++) {

                std::complex<T> c = getComplex<T, MandelbrotParams<T>>(
                    x,
                    y,
                    m_clientWidth,
                    m_clientHeight);

                long iterations = computeSequence(c);
                COLORREF cr = m_palette[iterations - 1];

                // enter pixel into queue (queue is thread safe)
                ++numPixels;
                Pixel pixel{ x, y, cr };
                addPixel(pixel);
            }

            // notity painting thread row per row
            notify();
        }

        ::OutputDebugString(L"< computePixel End\n");

        return numPixels;
    }

    long Mandelbrot::drawPixel() {

        ::OutputDebugString(L"> drawPixel Begin\n");

        long numPixels = 0;

        while (true) {

            std::unique_lock guard(m_mutex);

            // are pixels available ?
            m_conditionPixelsAvailable.wait(
                guard,
                [&]() { 
                    return m_pixels.size() > 0;
                }
            );

            WCHAR szText[32];
            wsprintf(szText,
                L"Variante 06: painting %lld pixel\n", m_pixels.size());
            ::OutputDebugString(szText);

            if (m_pixels.size() > 0) {

                size_t size = m_pixels.size();
                while (size != 0) {
                    Pixel p = m_pixels.front();
                    m_pixels.pop();
                    ::SetPixelV(m_hDC, p.m_x, p.m_y, p.m_cr);
                    --size;
                }
            }
        }

        ::OutputDebugString(L"< drawPixel Begin\n");

        return numPixels;
    }

    void Mandelbrot::startCalculationThread() {

        // define tasks, store corresponding futures
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                using namespace std::placeholders;
                std::packaged_task<long(RECT, long, long)> task{
                    std::bind(&Mandelbrot::computePixel, this, _1, _2, _3)
                };
                std::future<long> future = task.get_future();

                m_CalculationTasks.push_back(std::move(task));
                m_CalculationFutures.push_back(std::move(future));
            }
        }

        // execute each task in a separate thread
        for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
            for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

                std::packaged_task<long(RECT, long, long)> task =
                    std::move(m_CalculationTasks.front());

                m_CalculationTasks.pop_front();

                std::thread t(std::move(task), m_rects[j][i], m_clientWidth, m_clientHeight);
                t.detach();
            }
        }
    }

    void Mandelbrot::startDrawingThread() {

        std::packaged_task<long()> task {
            std::bind(&Mandelbrot::drawPixel, this)
        };

        m_DrawingFuture = task.get_future();
      //  m_DrawingTask = std::move (task);

        std::thread t(std::move(task));
        t.detach();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================