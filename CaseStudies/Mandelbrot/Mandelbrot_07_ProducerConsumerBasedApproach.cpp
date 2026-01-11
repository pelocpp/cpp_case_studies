// =====================================================================================
// Mandelbrot_07_ProducerConsumerBasedApproach.cpp
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#include "MandelbrotCommon.h"
#include "Mandelbrot_07_ProducerConsumerBasedApproach.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>
#include <thread>
#include <algorithm>
#include <chrono>
#include <cassert>

// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)

// TODO: Da fehlen Default Vorbelegungen ...
MandelbrotProducerConsumerBasedApproach::MandelbrotProducerConsumerBasedApproach() 
    : m_hWnd{}
{
    // no pending threads yet
    m_drawingDone = true;
    m_calculationsDone = true;
    m_numRectanglesCalculated = 0;
}

void MandelbrotProducerConsumerBasedApproach::setHWND(HWND hWnd)
{
    m_hWnd = hWnd;
}

void MandelbrotProducerConsumerBasedApproach::addPixel(const Pixel& pixel)
{
    std::size_t currentSize{};

    {
        std::lock_guard<std::mutex> guard{ m_mutexPixelsQueue };
        m_pixelsQueue.push_back(pixel);
        currentSize = m_pixelsQueue.size();
    }

    if (currentSize > 10) {
        m_conditionPixelsAvailable.notify_one();  // wakeup drawing thread, if waiting
    }
}

std::size_t MandelbrotProducerConsumerBasedApproach::computePixelsOfRectangle (std::stop_token token, struct Rectangle rect, std::size_t maxWidth, std::size_t maxHeight) {

    ::OutputDebugString(L"> computePixelsOfRectangle\n");

    std::size_t numPixels{};

    for (std::size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (std::size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            // premature end of drawing
            if (token.stop_requested()) {
                goto loopEnd;
            }

            std::complex<TFloatingPoint> comp { 
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight) 
            };

            std::size_t iterations{ g_palette.computeSequence(comp) };
            COLORREF color{ g_palette[iterations - 1] };

            // enter pixel into queue (queue is thread safe)
            Pixel pixel{ x, y, color };
            addPixel(pixel);
            ++numPixels;
        }
    }

loopEnd:

    bool calculationsDone{};

    {
        std::lock_guard<std::mutex> guard{ m_mutexRectanglesCalculated };

        m_numRectanglesCalculated++;
        if (m_numRectanglesCalculated == MandelbrotRectangles::NUM_RECTS) {
            m_calculationsDone = true;
        }

        calculationsDone = m_calculationsDone;
    }

    if (calculationsDone) {

        // last calculation threads inserts "end-of-pixels-queue" marker
        Pixel pixel{ SIZE_MAX, SIZE_MAX, 0 };
        addPixel(pixel);
    }

    // print some statistics
    WCHAR szText[128];
    ::swprintf(szText, 128, L"< computePixelsOfRectangle - computed %zu pixels\n", numPixels);
    ::OutputDebugString(szText);

    return numPixels;
}

std::size_t MandelbrotProducerConsumerBasedApproach::drawQueuedPixels(std::stop_token token) {

    ::OutputDebugString(L"> drawQueuedPixels\n");

    WCHAR szText[128];
    std::size_t numPixels{};
    std::deque<Pixel> pixels;

    // retrieve a handle to a device context for the client area of a specified window 
    HDC hDC{ ::GetDC(m_hWnd) };
    assert(hDC != NULL);

    while (! token.stop_requested())
    {
        // RAII
        {
            // std::unique_lock guard{ m_mutexPixelsQueue };
            std::unique_lock guard{ m_mutexPixelsQueue };

            // wait for next available pixels
            bool stopRequested {
                m_conditionPixelsAvailable.wait(
                    guard,
                    token,
                    [&] () { 
                        return m_pixelsQueue.size() != 0;
                    }
                )
            };

            // using length of queue to decide 'end-of-drawing' state
            if (m_pixelsQueue.size() == 0) {
                ::swprintf(szText, 128, L"> drawQueuedPixels: Stop Requested (2) #### - drawn so far: %zu\n", numPixels);
                ::OutputDebugString(szText);
                break;
            }

            // double buffer pattern
            std::swap(pixels, m_pixelsQueue);
        }

        while (pixels.size() != 0 && !token.stop_requested()) {
           
            Pixel p = pixels.front();
            pixels.pop_front();
            
            // end of queue reached?
            if (p.m_x == SIZE_MAX && p.m_y == SIZE_MAX) {

                {
                    std::lock_guard<std::mutex> guard{ m_mutexDrawingDone };
                    m_drawingDone = true;
                }

                goto loopEnd;
            }
            else {
                drawPixel(hDC, p.m_x, p.m_y, p.m_cr);
                numPixels++;
            }
        }
    }

loopEnd:

    // there is only a single drawing thread, being responsible for the graphics context
    ::ReleaseDC(m_hWnd, hDC);

    ::swprintf(szText, 128, L"< drawQueuedPixels - drawed %zu pixels.\n", numPixels);
    ::OutputDebugString(szText);

    // calculating time
    std::chrono::high_resolution_clock::time_point endTime{ std::chrono::high_resolution_clock::now() };
    double msecs{ std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - m_begin).count() };
    msecs /= 1000.0;
    ::swprintf(szText, 128, L"| Drawing took %lf seconds.\n", msecs);
    ::OutputDebugString(szText);

    return numPixels;
}

void MandelbrotProducerConsumerBasedApproach::drawPixel(HDC hdc, std::size_t x, std::size_t y, COLORREF color) const
{
    ::SetPixelV(hdc, (int) x, (int) y, color);
}

void MandelbrotProducerConsumerBasedApproach::prepareAllThreads(int rows, int cols)
{
    prepareCalculationThreads(rows, cols);
    prepareDrawingThread();
}

void MandelbrotProducerConsumerBasedApproach::prepareCalculationThreads(int rows, int cols) {

    // setup tasks
    m_calculationTasks.clear();
    m_calculationTasks.resize(MandelbrotRectangles::NUM_RECTS);

    std::generate(
        m_calculationTasks.begin(),
        m_calculationTasks.end(),
        [this] () {
            return std::packaged_task<std::size_t(std::stop_token, struct Rectangle, std::size_t, std::size_t)> {
                [this](std::stop_token token, struct Rectangle rect, std::size_t width, std::size_t height) {
                    return computePixelsOfRectangle(token, rect, width, height);
                }
            };
        }
    );

    // retrieve futures from these tasks
    m_calculationFutures.clear();
    m_calculationFutures.resize(MandelbrotRectangles::NUM_RECTS);

    std::transform(
        m_calculationTasks.begin(),
        m_calculationTasks.end(),
        m_calculationFutures.begin(),
        [](std::packaged_task<std::size_t(std::stop_token, struct Rectangle, std::size_t, std::size_t)>& task) {
            return task.get_future();
        }
    );
}

void MandelbrotProducerConsumerBasedApproach::prepareDrawingThread() {

    std::packaged_task <std::size_t(std::stop_token)> task{
        [this] (std::stop_token token) { return drawQueuedPixels(token); }
    };

    m_drawingTask = std::move (task);
    m_drawingFuture = m_drawingTask.get_future();
}

void MandelbrotProducerConsumerBasedApproach::launchAllThreads()
{
    // clear queue of computed pixels
    {
        std::lock_guard<std::mutex> guard{ m_mutexPixelsQueue };
        m_pixelsQueue.clear();
    }

    // clear boolean flag to observe drawing thread
    {
        std::lock_guard<std::mutex> guard{ m_mutexDrawingDone };
        m_drawingDone = false;
    }

    // reset counter variable of so far computed rextangles
    {
        std::lock_guard<std::mutex> guard{ m_mutexRectanglesCalculated };
        m_numRectanglesCalculated = 0;
        m_calculationsDone = false;
    }

    // creating a new std::stop_source object for this execution cycle
    m_source = std::stop_source{};

    // need stop_token object
    std::stop_token token{ m_source.get_token() };

    // std::chrono::system_clock::time_point m_begin = std::chrono::system_clock::now();
    m_begin = std::chrono::high_resolution_clock::now();

    launchCalculationThreads(token);
    launchDrawingThread(token);
}

void MandelbrotProducerConsumerBasedApproach::launchCalculationThreads(std::stop_token token) {

    // execute each task in a separate thread
    for (const auto& row : m_rects)
    {
        for (const auto& rect : row) {

            std::packaged_task<std::size_t(std::stop_token, struct Rectangle, std::size_t, std::size_t)> task {
                std::move(m_calculationTasks.front())
            };

            m_calculationTasks.pop_front();

            std::jthread t{ std::move(task), token, rect, m_clientWidth, m_clientHeight };
            t.detach();
        }
    }
}

void MandelbrotProducerConsumerBasedApproach::launchDrawingThread(std::stop_token token) {

    std::jthread t{ std::move(m_drawingTask), token };
    t.detach();
}

void MandelbrotProducerConsumerBasedApproach::cancelActiveThreadsIfAny()
{
    bool drawingDone;

    ::OutputDebugString(L"< cancelActiveThreadsIfAny\n");

    {
        // need thread safe context to read current value of 'm_drawingDone'
        std::lock_guard<std::mutex> guard{ m_mutexDrawingDone };
        drawingDone = m_drawingDone;
    }

    if (! drawingDone) {

        requestStop();
        waitAllThreadsDone();
    }

    ::OutputDebugString(L"> cancelActiveThreadsIfAny\n");
}

void MandelbrotProducerConsumerBasedApproach::requestStop() 
{ 
    m_source.request_stop();
}

void MandelbrotProducerConsumerBasedApproach::waitAllThreadsDone()
{
    WCHAR szText[64];
    std::size_t numPixels{};

    // print some statistics
    ::OutputDebugString(L"> waitAllThreadsDone\n");

    // which threads should we stop at first ... I think this doesn't matter

    // wait for the end of all calculation threads
    while (! m_calculationFutures.empty()) {

        ::OutputDebugString(L"| waiting end of calculation thread ...\n");

        std::future<std::size_t> future{ std::move(m_calculationFutures.front()) };
        m_calculationFutures.pop_front();

        // wait for end of a calculation thread
        numPixels = future.get();

        // print some statistics
        ::swprintf(szText, 64, L"| end of calculation thread: %zu pixels calculated.\n", numPixels);
        ::OutputDebugString(szText);
    }

    {
        ::OutputDebugString(L"| waiting end of drawing thread ...\n");

        // wait for end of single drawing thread
        numPixels = m_drawingFuture.get();

        // print some statistics
        ::swprintf(szText, 64, L"| end of drawing thread: %zu pixels drawn.\n", numPixels);
        ::OutputDebugString(szText);
    }

    ::OutputDebugString(L"> waitAllThreadsDone\n");
}

// =====================================================================================
// End-of-File
// =====================================================================================
