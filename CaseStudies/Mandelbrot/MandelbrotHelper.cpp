// =====================================================================================
// MandelbrotHelper.cpp
// =====================================================================================

#include "framework.h"

#include "MandelbrotPalette.h"
#include "MandelbrotHelper.h"

#include <thread>
#include <algorithm>
#include <utility>
#include <functional> 
#include <latch>
#include <chrono>
#include <stop_token>

// =====================================================================================

Mandelbrot::Mandelbrot() :
    m_abort{ false }, m_doneRectangles{ MandelbrotRectangles::NUM_RECTS },
    m_clientWidth{}, m_clientHeight{}, m_numRows{}, m_numCols{},
    m_hWnd{}, m_hDC{}, m_rects{}, m_palette{}
{}

void Mandelbrot::computeRects()
{
    // adjust total client width and height according to number of rectangles
    size_t clientWidth = m_clientWidth - (m_clientWidth % MandelbrotRectangles::NUM_COLS);
    size_t clientHeight = m_clientHeight - (m_clientHeight % MandelbrotRectangles::NUM_ROWS);

    // calculate size of a single rectangle
    size_t rectWidth = clientWidth / MandelbrotRectangles::NUM_COLS;
    size_t rectHeight = clientHeight / MandelbrotRectangles::NUM_ROWS;

    // calculate coordinates of each rectangle
    for (int i = 0; i < MandelbrotRectangles::NUM_ROWS; i++) 
    {
        for (int j = 0; j < MandelbrotRectangles::NUM_COLS; j++) {

            m_rects[i][j] = RECT {
                (LONG)(j * rectWidth), (LONG)(i * rectHeight),
                (LONG)((j + 1) * rectWidth - 1), (LONG)((i + 1) * rectHeight - 1)
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

    return std::complex<T> {
        XMIN + (XMAX - XMIN) * x / maxWidth,
        YMAX + (YMIN - YMAX) * y / maxHeight
    };
}

void Mandelbrot::paint(HDC hDC) {

    using T = double;

    for (int y = 0; y < m_clientHeight; y++) 
    {
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

void Mandelbrot::paintRectanglesAsync (HDC hDC) {

    // setup tasks
    std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [this] () {
            return std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> {
                [this](HDC hDC, RECT rect) {
                    return paintRectAsync(hDC, rect); 
                }
            };
        }
    );

    // retrieve futures from these tasks
    std::deque<std::future<std::pair<std::wstring, long>>> futures;
    futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        tasks.begin(),
        tasks.end(),
        futures.begin(),
        [](std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>& task) {
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

    // retrieve results
    while (!futures.empty()) {

        auto future{ std::move(futures.front()) };
        futures.pop_front();
        const auto& [tid, pixels] = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64,
            L"Thread %ls:  painted %ld pixels", tid.c_str(), pixels);
        OutputDebugString(szText);
    }
}

void Mandelbrot::paintRectanglesAsyncWithLatch(HDC hDC) {

    // working with a latch object
    std::latch paintedAllRectangles{ MandelbrotRectangles::NUM_RECTS };

    // setup tasks
    std::deque<std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [&, this]() {
            return std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)> {
                [&, this](HDC hDC, RECT rect) {
                    auto result = paintRectAsync(hDC, rect);
                    paintedAllRectangles.count_down();
                    return result;
                }
            };
        }
    );

    // retrieve futures from these tasks
    std::deque<std::future<std::pair<std::wstring, long>>> futures;
    futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        tasks.begin(),
        tasks.end(),
        futures.begin(),
        [](std::packaged_task<std::pair<std::wstring, long>(HDC, RECT)>& task) {
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
            L"Thread %ls:  painted %ld pixels", tid.c_str(), pixels);
        OutputDebugString(szText);
    }
}

// ====================================================================================

void Mandelbrot::startPaintingRectanglesAsync(HWND hWnd, HDC hDC) {

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
            return std::packaged_task<long(HWND, HDC, RECT)> {
                [this](HWND hWnd, HDC hDC, RECT rect) {
                    return startPaintRectAsync(hWnd, hDC, rect);
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
        [](std::packaged_task<long(HWND, HDC, RECT)>& task) {
            return task.get_future();
        }
    );

    // launch these tasks each in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            auto task{ std::move(m_tasks.front()) };
            m_tasks.pop_front();

            std::thread t{ std::move(task), hWnd, hDC, rect };
            t.detach();
        }
    }
}

void Mandelbrot::startPaintingRectanglesAsyncEx(HWND hWnd, HDC hDC) {

    // clear member data
    resetDoneRectangles();

    m_tasksEx.clear();
    m_futures.clear();

    // setup tasks
    m_tasksEx.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        m_tasksEx.begin(),
        m_tasksEx.end(),
        [this]() {
            return std::packaged_task<long(std::stop_token, HWND, HDC, RECT)> {
                [this](std::stop_token token, HWND hWnd, HDC hDC, RECT rect) {
                    return startPaintRectAsyncEx(token, hWnd, hDC, rect);
                    }
            };
        }
    );

    // retrieve futures from these tasks
    m_futures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        m_tasksEx.begin(),
        m_tasksEx.end(),
        m_futures.begin(),
        [](std::packaged_task<long(std::stop_token, HWND, HDC, RECT)>& task) {
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

            auto task{ std::move(m_tasksEx.front()) };
            m_tasksEx.pop_front();

            std::jthread thread{ std::move(task), token, hWnd, hDC, rect };
            thread.detach();
        }
    }
}

void Mandelbrot::waitRectanglesDone() {

    while (!m_futures.empty()) {

        std::future<long> future = std::move(m_futures.front());
        m_futures.pop_front();
        long numPixels = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64,
            L"   ... %ld pixels painted", numPixels);
        OutputDebugString(szText);
    }
}

// =====================================================================================

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
                std::lock_guard<std::mutex> lock(m_mutex);
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
                goto m_label;
            }

            std::complex<T> number = getComplex<T, MandelbrotParams<T>>(
                x,
                y,
                m_clientWidth,
                m_clientHeight
            );

            long iterations{ computeSequence(number) };
            COLORREF cr{ m_palette[iterations - 1] };
            ++numPixels;

            {
                // RAII lock
                std::lock_guard<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    m_label:

    incDoneRectangles();
    if (getDoneRectangles() == MandelbrotRectangles::NUM_RECTS) {

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
                std::lock_guard<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, x, y, cr);
            }
        }
    }

    m_label:

    incDoneRectangles();
    if (getDoneRectangles() == MandelbrotRectangles::NUM_RECTS) {

        ::ReleaseDC(hWnd, hDC);
    }

    return numPixels;
}

// =====================================================================================

// AB hier weiter ...


template <typename T>
long Mandelbrot::computeSequence(std::complex<T> point) const
{
    std::complex<T> number(0.0);

    long count{};
    while (count < Mandelbrot::NumColors && std::abs(number) < Mandelbrot::Limit) {
        number = number * number + point;
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
    std::lock_guard<std::mutex> lock(m_mutex);

    m_pixels.push(pixel);
    if (m_pixels.size() > 10) {
        m_conditionPixelsAvailable.notify_one();   // wakeup drawing thread
    }
}

void Mandelbrot::notify() {
    std::lock_guard<std::mutex> lock(m_mutex);    // TBD:      Den Lock weglassen !!!!!!!!!!!!!!!!!!!!!
    m_conditionPixelsAvailable.notify_one();       // wakeup drawing thread
}

long Mandelbrot::computePixel(RECT rect, long maxWidth, long maxHeight) {

    ::OutputDebugString(L"> computePixel Begin");

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

    ::OutputDebugString(L"< computePixel End");

    return numPixels;
}

void Mandelbrot::drawPixel() {

    ::OutputDebugString(L"> drawPixel Begin");

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
        wsprintf(szText, L"Variante 06: painting %d pixel", (int) m_pixels.size());
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

    ::OutputDebugString(L"< drawPixel Begin");
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