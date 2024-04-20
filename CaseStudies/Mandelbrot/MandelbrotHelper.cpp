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

constexpr uint8_t MY_POLYNOM = 0x07;
constexpr int TABLE_SIZE = 256;

template<uint8_t POLYNOM>
constexpr auto crcTable = [] {
    std::array<uint8_t, TABLE_SIZE> A = {};
    for (int i = 0; i < TABLE_SIZE; i++) {
        A[i] = i;
        for (int j = 0; j < 8; j++) {
            if ((A[i] & 0x80) != 0) {
                A[i] = (uint8_t)((A[i] << 1) ^ POLYNOM);
            }
            else {
                A[i] <<= 1;
            }
        }
    }
    return A;
    }();


constexpr auto   XXX = []() {
   // std::array<COLORREF, 100> m_palette = {};
   MandelbrotPaletteEx palette;
    // palette.init();
    return palette;
    }();


auto constexpr ConstValue = []() {
    /* several lines of code ... - "very complex" computation */
    return 123;
    }();


// constexpr MandelbrotPalette palette;    // const möglicherweise wieder entfernen ..........
//
//auto constexpr MandelbrotPaletteEx = []() {
//    /* several lines of code ... - "very complex" computation */
//    return MandelbrotPalette();
//}
//();

//constexpr auto crcTable = [] {
//    MandelbrotPalette palette;
//    palette.init();
//    return palette;
//    }();



// =====================================================================================

Mandelbrot::Mandelbrot() :
    m_abort{ false }, m_doneRectangles{ MandelbrotRectangles::NUM_RECTS },
    m_clientWidth{}, m_clientHeight{}, m_numRows{}, m_numCols{},
    m_hWnd{}, m_hDC{}, m_rects{}
{}

void Mandelbrot::computeRects()
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

template <typename T>
constexpr std::complex<T> Mandelbrot::getComplex(
    size_t x,
    size_t y,
    size_t maxWidth,
    size_t maxHeight) const
{
    // short hand constants for the Mandelbrot coordinates system
    static T XMIN = MandelbrotParams<T>::XMIN;
    static T XMAX = MandelbrotParams<T>::XMAX;
    static T YMIN = MandelbrotParams<T>::YMIN;
    static T YMAX = MandelbrotParams<T>::YMAX;

    return std::complex<T> {
        XMIN + (XMAX - XMIN) * x / maxWidth, YMAX + (YMIN - YMAX) * y / maxHeight
    };
}

void Mandelbrot::paint(HDC hDC) {

    for (size_t y{}; y != m_clientHeight; y++)
    {
        for (size_t x{}; x != m_clientWidth; x++) {

            std::complex<TFloatingPoint> number {
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
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
    std::deque<std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)>> tasks;
    tasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        tasks.begin(),
        tasks.end(),
        [this] () {
            return std::packaged_task<std::pair<std::wstring, size_t>(HDC, struct Rectangle)> {
                [this](HDC hDC, struct Rectangle rect) {
                    return paintRectAsync(hDC, rect); 
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

void Mandelbrot::paintRectanglesAsyncWithLatch(HDC hDC) {

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
                    auto result = paintRectAsync(hDC, rect);
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
            return std::packaged_task<size_t(HWND, HDC, struct Rectangle)> {
                [this](HWND hWnd, HDC hDC, struct Rectangle rect) {
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
            return std::packaged_task<size_t(std::stop_token, HWND, HDC, struct Rectangle)> {
                [this](std::stop_token token, HWND hWnd, HDC hDC, struct Rectangle rect) {
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
        [](std::packaged_task<size_t(std::stop_token, HWND, HDC, struct Rectangle)>& task) {
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

        std::future<size_t> future = std::move(m_futures.front());
        m_futures.pop_front();
        size_t numPixels = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"   ... %zu pixels painted", numPixels);
        OutputDebugString(szText);
    }
}

// =====================================================================================

void Mandelbrot::paintRect(HDC hDC, struct Rectangle rect) {

    for (size_t y{ rect.m_top }; y < rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x < rect.m_right; x++) {

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            COLORREF cr{ m_palette[iterations - 1] };
            ::SetPixelV(hDC, (int) x, (int) y, cr);
        }
    }
}

std::pair<std::wstring, size_t> Mandelbrot::paintRectAsync(HDC hDC, struct Rectangle rect) {

    std::thread::id tid{ std::this_thread::get_id() };

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x != rect.m_right; x++) {

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            COLORREF cr{ m_palette[iterations - 1] };
            ++numPixels;

            {
                // RAII lock
                std::lock_guard<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, (int) x, (int) y, cr);
            }
        }
    }

    std::wstringstream ss;
    ss << tid;

    return { ss.str(), numPixels };
}

size_t Mandelbrot::startPaintRectAsync(HWND hWnd, HDC hDC, struct Rectangle rect) {

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x != rect.m_right; x++) {

            // premature end of drawing
            if (m_abort == true) {
                goto m_label;
            }

            std::complex<TFloatingPoint> number{
                getComplex<TFloatingPoint>( x, y, m_clientWidth, m_clientHeight)
            };

            size_t iterations{ computeSequence(number) };
            COLORREF cr{ m_palette[iterations - 1] };
            ++numPixels;

            {
                // RAII lock
                std::lock_guard<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, (int) x, (int) y, cr);
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

size_t Mandelbrot::startPaintRectAsyncEx(std::stop_token token, HWND hWnd, HDC hDC, struct Rectangle rect) {

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x != rect.m_right; x++) {

            // premature end of drawing
            if (token.stop_requested()) {
                goto m_label;
            }

            std::complex<TFloatingPoint> number{ 
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight) 
            };

            size_t iterations{ computeSequence(number) };
            COLORREF cr{ m_palette[iterations - 1] };
            ++numPixels;

            {
                // RAII lock
                std::lock_guard<std::mutex> lock(m_mutex);
                ::SetPixelV(hDC, (int) x, (int) y, cr);
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
size_t Mandelbrot::computeSequence(std::complex<T> point) const
{
    std::complex<T> number(0.0);

    size_t count{};

    while (count != Mandelbrot::NumColors && std::abs(number) < Mandelbrot::Limit) {
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

size_t Mandelbrot::computePixel(struct Rectangle rect, size_t maxWidth, size_t maxHeight) {

    ::OutputDebugString(L"> computePixel Begin");

    size_t numPixels = 0;

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++) {

        for (size_t x{ rect.m_left }; x != rect.m_right; x++) {

            std::complex<TFloatingPoint> comp { 
                getComplex<TFloatingPoint>( x, y, m_clientWidth, m_clientHeight) 
            };

            size_t iterations = computeSequence(comp);

            COLORREF cr{ m_palette[iterations - 1] };

            // enter pixel into queue (queue is thread safe)
            ++numPixels;
            Pixel pixel{ (int) x, (int) y, cr };
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
                ::SetPixelV(m_hDC, (int) p.m_x, (int) p.m_y, p.m_cr);
                --size;
            }
        }
    }

    ::OutputDebugString(L"< drawPixel Begin");
}

void Mandelbrot::startCalculationThread() {

    // define tasks, store corresponding futures
    for (size_t j{}; j != MandelbrotRectangles::NUM_ROWS; j++) {
        for (size_t i{}; i != MandelbrotRectangles::NUM_COLS; i++) {

            using namespace std::placeholders;
            std::packaged_task<size_t(struct Rectangle, size_t, size_t)> task {
                std::bind(&Mandelbrot::computePixel, this, _1, _2, _3)
            };
            std::future<size_t> future = task.get_future();

            m_CalculationTasks.push_back(std::move(task));
            m_CalculationFutures.push_back(std::move(future));
        }
    }

    // execute each task in a separate thread
    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++) {
        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++) {

            std::packaged_task<size_t(struct Rectangle, size_t, size_t)> task =
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