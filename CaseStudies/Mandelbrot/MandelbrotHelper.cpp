// =====================================================================================
// MandelbrotHelper.cpp
// =====================================================================================

#include "framework.h"

#include "MandelbrotPalette.h"
#include "MandelbrotHelper.h"

#include <thread>
#include <utility>
#include <functional> 
#include <latch>
#include <chrono>
#include <stop_token>

// =====================================================================================

//Mandelbrot::Mandelbrot() :
//    m_abort{ false }, m_doneRectangles{ MandelbrotRectangles::NUM_RECTS } ,
//    m_clientWidth{}, m_clientHeight{}, m_NumRows{}, m_NumCols{},
//    m_hWnd{}, m_hDC{}, m_rects{}, m_palette{}
//{}

Mandelbrot::Mandelbrot() :
    m_abort{ false }, m_doneRectangles{ MandelbrotRectangles::NUM_RECTS },
    m_clientWidth{}, m_clientHeight{}, m_NumRows{}, m_NumCols{},
    m_hWnd{}, m_hDC{}, m_rects{}, m_palette{}
{}

void Mandelbrot::computeRects()
{
    // adjust total client width and height according to number of rectangles
    long clientWidth = m_clientWidth - (m_clientWidth % MandelbrotRectangles::NUM_COLS);
    long clientHeight = m_clientHeight - (m_clientHeight % MandelbrotRectangles::NUM_ROWS);

    // calculate size of a single rectangle
    long rectWidth = clientWidth / MandelbrotRectangles::NUM_COLS;
    long rectHeight = clientHeight / MandelbrotRectangles::NUM_ROWS;

    // calculate coordinates of each rectangle
    for (int i = 0; i < MandelbrotRectangles::NUM_ROWS; i++) {
        for (int j = 0; j < MandelbrotRectangles::NUM_COLS; j++) {

            m_rects[i][j] = {
                (LONG)(j * rectWidth),
                (LONG)(i * rectHeight),
                (LONG)((j + 1) * rectWidth - 1),
                (LONG)((i + 1) * rectHeight - 1)
            };
        }
    }
}

template <typename T, typename MANDELBROT_COORDINATES>
constexpr std::complex<T> Mandelbrot::getComplex(
    long x,
    long y,
    long maxWidth,
    long maxHeight) const
{
    // short hand constants for the Mandelbrot coordinates system
    static constexpr T XMIN = MANDELBROT_COORDINATES::XMIN;
    static constexpr T XMAX = MANDELBROT_COORDINATES::XMAX;
    static constexpr T YMIN = MANDELBROT_COORDINATES::YMIN;
    static constexpr T YMAX = MANDELBROT_COORDINATES::YMAX;

    return std::complex<T>{
        XMIN + (XMAX - XMIN) * x / maxWidth,
        YMAX + (YMIN - YMAX) * y / maxHeight
    };
}

void Mandelbrot::paint(HDC hDC) {

    using T = double;

    for (int y = 0; y < m_clientHeight; y++) {

        for (int x = 0; x < m_clientWidth; x++) {

            std::complex<T> number { 
                getComplex<T, MandelbrotParams<T>>(x, y, m_clientWidth, m_clientHeight)
            };

            long iterations{ computeSequence(number) };

            COLORREF cr{ m_palette[iterations - 1] };
            
            ::SetPixelV(hDC, (int) x, (int) y, cr);
        }
    }
}

void Mandelbrot::paintRectangles(HDC hDC) {

    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {
            paintRect(hDC, rectangle);
        }
    }
}


// https://stackoverflow.com/questions/28652422/stdpackaged-task-with-stdbindfunc-this-within-class

// Hmmm: [this](int a, int b){ return somefunc(a, b); } is more readable, about the same number of keys to type
// as std::bind(&foo::somefunc, this, _1, _2), 

//void Mandelbrot::paintRectanglesAsync_LEGACY(HDC hDC) {
//
//    std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;
//    std::deque<std::future<std::pair<std::wstring, long>>> futures;
//
//    // define tasks, store corresponding futures
//    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
//        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            using namespace std::placeholders;
//            std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task{
//                std::bind(&Mandelbrot::paintRectAsync, this, _1, _2)
//            };
//
//            std::future<std::pair<std::wstring, long>> future = task.get_future();
//            tasks.push_back(std::move(task));
//            futures.push_back(std::move (future));
//        }
//    }
//
//    // execute each task in a separate thread
//    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
//        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task =
//                std::move(tasks.front());
//
//            tasks.pop_front();
//
//            std::thread t(std::move(task), hDC, m_rects[j][i]);
//            t.detach();
//        }
//    }
//
//    // get the results
//    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
//        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            std::future<std::pair<std::wstring, long>> future =
//                std::move(futures.front());
//
//            futures.pop_front();
//
//            auto [tid, pixels] = future.get();
//
//            // print some statistics
//            WCHAR szText[64];
//            ::swprintf(szText, 64,
//                L"thread %ls:  painted %ld pixels\n", tid.c_str(), pixels);
//            OutputDebugString(szText);
//        }
//    }
//}

// NEU
void Mandelbrot::paintRectanglesAsync (HDC hDC) {

    std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;

    std::deque<std::future<std::pair<std::wstring, long>>> futures;

    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task{
                [=, this](HDC hDC, RECT rect) {
                    return paintRectAsync(hDC, rect); 
                }
            };

            std::future<std::pair<std::wstring, long>> future{ task.get_future() };

            tasks.push_back(std::move(task));

            futures.push_back(std::move(future));
        }
    }

    // execute each task in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            auto task{ std::move(tasks.front()) };
            tasks.pop_front();

            std::thread t(std::move(task), hDC, rectangle);
            t.detach();
        }
    }

    // get the results
    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            std::future<std::pair<std::wstring, long>> future{
                std::move(futures.front()) 
            };
            futures.pop_front();

            const auto& [tid, pixels] = future.get();

            // print some statistics
            WCHAR szText[64];
            ::swprintf(szText, 64,
                L"Thread %ls:  painted %ld pixels\n", tid.c_str(), pixels);
            OutputDebugString(szText);
        }
    }
}

void Mandelbrot::paintRectanglesAsyncWithLatch(HDC hDC) {

    std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;

    std::deque<std::future<std::pair<std::wstring, long>>> futures;

    std::latch paintedAllRectangles{ MandelbrotRectangles::NUM_RECTS };

    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> task {

                [&, this] (HDC hDC, RECT rect) mutable {

                    auto result = paintRectAsync(hDC, rectangle);

                    paintedAllRectangles.count_down();

                    return result;
                }
            };

            std::future<std::pair<std::wstring, long>> future{ task.get_future() };

            tasks.push_back(std::move(task));
            futures.push_back(std::move(future));
        }
    }

    // execute each task in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            auto task{ std::move(tasks.front()) };
            tasks.pop_front();

            std::thread t(std::move(task), hDC, rectangle);
            t.detach();
        }
    }

    // block until work is done
    paintedAllRectangles.wait();
    OutputDebugString(L"All calculations done :)");

    // get the results
    for (const auto& row : m_rects)
    {
        for (const auto& rectangle : row) {

            auto future{ std::move(futures.front()) };
            futures.pop_front();

            const auto& [tid, pixels] = future.get();

            // print some statistics
            WCHAR szText[64];
            ::swprintf(szText, 64,
                L"thread %ls:  painted %ld pixels\n", tid.c_str(), pixels);
            OutputDebugString(szText);
        }
    }
}

// ====================================================================================

// Legacy
//void Mandelbrot::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {
//
//    m_doneRectangles = 0;
//
//    m_tasks.clear();
//    m_futures.clear();
//
//    // define tasks, store corresponding futures
//    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++)
//    {
//        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            using namespace std::placeholders;
//            std::packaged_task<long(HWND, HDC, RECT)> task{
//                std::bind(&Mandelbrot::startPaintRectAsync, this, _1, _2, _3)
//            };
//            std::future<long> future = task.get_future();
//
//            m_tasks.push_back(std::move(task));
//            m_futures.push_back(std::move(future));
//        }
//    }
//
//    // execute each task in a separate thread
//    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
//        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            std::packaged_task<long(HWND, HDC, RECT)> task =
//                std::move(m_tasks.front());
//
//            m_tasks.pop_front();
//
//            std::thread t(std::move(task), hWnd, hDC, m_rects[j][i]);
//            t.detach();
//        }
//    }
//}

void Mandelbrot::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {

    m_doneRectangles = 0;

    m_tasks.clear();
    m_futures.clear();

    // define tasks, store corresponding futures
    //for (int j{}; j != MandelbrotRectangles::NUM_ROWS; j++)
    //{
    //    for (int i{}; i != MandelbrotRectangles::NUM_COLS; i++) {

    //        std::packaged_task<long(HWND, HDC, RECT)> task {
    //            [this] (HWND hWnd, HDC hDC, RECT rect) { 
    //                return startPaintRectAsync(hWnd, hDC, rect); 
    //            }
    //        };

    //        std::future<long> future{ task.get_future() };

    //        m_tasks.push_back(std::move(task));

    //        m_futures.push_back(std::move(future));
    //    }
    //}

    for (int j{}; j != MandelbrotRectangles::NUM_ROWS * MandelbrotRectangles::NUM_COLS; j++) {

        std::packaged_task<long(HWND, HDC, RECT)> task {
            [this] (HWND hWnd, HDC hDC, RECT rect) { 
                return startPaintRectAsync(hWnd, hDC, rect); 
            }
        };

        std::future<long> future{ task.get_future() };
        m_tasks.push_back(std::move(task));
        m_futures.push_back(std::move(future));
    }

    // execute each task in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            std::packaged_task<long(HWND, HDC, RECT)> task{
                std::move(m_tasks.front()) 
            };

            m_tasks.pop_front();

            std::thread t{ std::move(task), hWnd, hDC, rect };
            t.detach();
        }
    }
}

void Mandelbrot::startPaintingRectanglesAsyncEx(std::stop_source source, HWND hWnd, HDC hDC) {

    m_doneRectangles = 0;

    m_tasksEx.clear();
    m_futures.clear();

    // define tasks, store corresponding futures

    // DAS GEHT MIT ZWEIMAL std::generator: Erst den Vektor mit std::packaged_task befüllen,
    // dann deb 2, Vektor mit den Futures befüllen

    for (int j{}; j != MandelbrotRectangles::NUM_ROWS * MandelbrotRectangles::NUM_COLS; j++) {

        std::packaged_task<long(std::stop_token, HWND, HDC, RECT)> task{
            [this](std::stop_token token, HWND hWnd, HDC hDC, RECT rect) {
                return startPaintRectAsyncEx(token, hWnd, hDC, rect);
            }
        };

        std::future<long> future{ task.get_future() };
        m_tasksEx.push_back(std::move(task));
        m_futures.push_back(std::move(future));
    }

    // need stop_source and stop_token objects
    std::stop_token token{ source.get_token() };

    // execute each task in a separate thread

    // Hmmm: Ginge auch mit geschachteltem std:for_each .... und Lambda
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            std::packaged_task<long(std::stop_token, HWND, HDC, RECT)> task{
                std::move(m_tasksEx.front())
            };

            m_tasksEx.pop_front();

            std::jthread t{ std::move(task), token, hWnd, hDC, rect };
            t.detach();
        }
    }
}


//void Mandelbrot::waitRectanglesDone() {
//
//    // Hmmmmm .. wieso 2 Schleifen ??????????????????????????
//
//    for (int j{}; j < MandelbrotRectangles::NUM_ROWS; j++) {
//
//        for (int i{}; i < MandelbrotRectangles::NUM_COLS; i++) {
//
//            std::future<long> future = std::move(m_futures.front());
//            m_futures.pop_front();
//            long numPixels = future.get();
//
//            // print some statistics
//            WCHAR szText[64];
//            ::swprintf(szText, 64,
//                L"   ... %ld pixels painted\n", numPixels);
//            OutputDebugString(szText);
//        }
//    }
//}

void Mandelbrot::waitRectanglesDone() {

    while (!m_futures.empty()) {

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

void Mandelbrot::paintRect(HDC hDC, RECT rect) {

    using T = double;

    for (int y{ rect.top }; y < rect.bottom; y++) {

        for (int x{ rect.left }; x < rect.right; x++) {

            std::complex<T> number{
                getComplex<T, MandelbrotParams<T>>(x, y, m_clientWidth, m_clientHeight)
            };

            long iterations{ computeSequence(number) };

            COLORREF cr{ m_palette[iterations - 1] };

            ::SetPixelV(hDC, x, y, cr);
        }
    }
}

std::pair<std::wstring, long> Mandelbrot::paintRectAsync(HDC hDC, RECT rect) {

    using T = double;

    std::thread::id tid{ std::this_thread::get_id() };

    long numPixels{};

    for (int y{ rect.top }; y < rect.bottom; y++) {

        for (int x{ rect.left }; x < rect.right; x++) {

            std::complex<T> number{
                getComplex<T, MandelbrotParams<T>>(x, y, m_clientWidth, m_clientHeight)
            };

            long iterations{ computeSequence(number) };

            COLORREF cr{ m_palette[iterations - 1] };

            ++numPixels;

            {
                // RAII lock
                std::scoped_lock<std::mutex> lock(m_mutex);

                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    std::wstringstream ss;
    ss << tid;

    return std::make_pair(ss.str(), numPixels);
}

long Mandelbrot::startPaintRectAsync(HWND hWnd, HDC hDC, RECT rect) {

    using T = double;

    long numPixels{};

    for (int y = rect.top; y < rect.bottom; y++) {

        for (int x = rect.left; x < rect.right; x++) {

            // premature end of drawing
            if (m_abort == true) {
                // break;
                ::OutputDebugString(L"premature end of drawing ...");
                goto m_label;
            }

            std::complex<T> number = getComplex<T, MandelbrotParams<T>>(
                x,
                y,
                m_clientWidth,
                m_clientHeight);

            long iterations{ computeSequence(number) };

            COLORREF cr{ m_palette[iterations - 1] };

            ++numPixels;

            {
                // RAII lock
                std::scoped_lock<std::mutex> lock(m_mutex);

                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    m_label:

    m_doneRectangles++;

    if (m_doneRectangles == MandelbrotRectangles::NUM_RECTS) {

        ::ReleaseDC(hWnd, hDC);
    }

    return numPixels;
}

long Mandelbrot::startPaintRectAsyncEx(std::stop_token token, HWND hWnd, HDC hDC, RECT rect) {

    using T = double;

    long numPixels{};

    for (int y = rect.top; y < rect.bottom; y++) {

        for (int x = rect.left; x < rect.right; x++) {

            // premature end of drawing
            if (token.stop_requested()) {
                ::OutputDebugString(L"premature end of drawing ...");
                goto m_label;
            }

            std::complex<T> number = getComplex<T, MandelbrotParams<T>>(
                x,
                y,
                m_clientWidth,
                m_clientHeight);

            long iterations{ computeSequence(number) };

            COLORREF cr{ m_palette[iterations - 1] };

            ++numPixels;

            {
                // RAII lock
                std::scoped_lock<std::mutex> lock(m_mutex);

                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    m_label:

    m_doneRectangles++;

    if (m_doneRectangles == MandelbrotRectangles::NUM_RECTS) {

        ::ReleaseDC(hWnd, hDC);
    }

    return numPixels;
}

    
template <typename T>
long Mandelbrot::computeSequence(std::complex<T> point) const
{
    std::complex<T> c(0.0);

    long count{};
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

void Mandelbrot::addPixel(Pixel pixel)
{
    std::scoped_lock<std::mutex> lock(m_mutex);

    m_pixels.push(pixel);
    if (m_pixels.size() > 10) {
        m_conditionPixelsAvailable.notify_one();   // wakeup drawing thread
    }
}

void Mandelbrot::notify() {
    std::scoped_lock<std::mutex> lock(m_mutex);
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

void Mandelbrot::drawPixel() {

    ::OutputDebugString(L"> drawPixel Begin\n");

    while (true) {

        std::unique_lock guard(m_mutex);

        // are pixels available ?
        m_conditionPixelsAvailable.wait(
            guard,
            [&]() { 
                return m_pixels.size() > 0;
            }
        );

        //// premature end of drawing
        //if (m_abort == true) {
        //    break;
        //}

        WCHAR szText[32];
        wsprintf(szText, L"Variante 06: painting %d pixel\n", (int) m_pixels.size());
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
}

void Mandelbrot::startCalculationThread() {

    // define tasks, store corresponding futures
    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

            using namespace std::placeholders;
            std::packaged_task<long(RECT, long, long)> task {
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

    std::packaged_task<void()> task {
        std::bind(&Mandelbrot::drawPixel, this)
    };

    m_DrawingFuture = task.get_future();
    //m_DrawingTask = std::move (task);

    std::thread t(std::move(task));
    t.detach();
}

// =====================================================================================
// End-of-File
// =====================================================================================