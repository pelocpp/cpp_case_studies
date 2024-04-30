// =====================================================================================
// MandelbrotProducerConsumerBasedApproach.cpp
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#include "MandelbrotCommon.h"
#include "MandelbrotProducerConsumerBasedApproach.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>

// ACHTUNG !!!!!!!!!!!!!!!!!!!!!!!

// ALLE QUEUES ... Tasks, futures, Pixels m�ssen beim "Neustart" geleert sein !!!!!!!!!!!!
// Wie ist da bei den anderen Varianten


// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)

// TODO: Da fehlen Default Vorbelegungen ...
MandelbrotProducerConsumerBasedApproach::MandelbrotProducerConsumerBasedApproach() 
    : m_mutexPixelsQueue{}, m_hWnd{}, m_hDC{}
{
    // no pending threads yet
    m_doneRectangles = 0;
    m_done = true;
}

void MandelbrotProducerConsumerBasedApproach::setHWND(HWND hWnd)
{
    m_hWnd = hWnd;
    m_hDC = ::GetDC(m_hWnd);
}

void MandelbrotProducerConsumerBasedApproach::addPixel(Pixel pixel)
{
    std::unique_lock<std::mutex> lock{ m_mutexPixelsQueue };

    m_pixels.push(pixel);

    size_t currentSize = m_pixels.size();

    lock.unlock();

    if (currentSize > 10) {
        m_conditionPixelsAvailable.notify_one();  // wakeup drawing thread, if waiting
    }
}

size_t MandelbrotProducerConsumerBasedApproach::computePixelsOfRectangle (std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight) {

    ::OutputDebugString(L"> STD::JTHREAD: computePixelsOfRectangle");

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            // premature end of drawing
            if (token.stop_requested()) {
                ::OutputDebugString(L"> computePixelsOfRectangle: Stop Requested <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
                goto loopEnd;
            }

            std::complex<TFloatingPoint> comp { 
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight) 
            };

            size_t iterations{ computeSequence(comp) };
            COLORREF color{ g_palette[iterations - 1] };

            // enter pixel into queue (queue is thread safe)
            Pixel pixel{ x, y, color };
            addPixel(pixel);
            ++numPixels;
        }

        // notity painting thread row per row
        // // TO BE DONE; Das mit dem notify muss genau betrachtet werden !!!!!
        //  notify();
    }

loopEnd:

    bool done{};

    {
        std::lock_guard<std::mutex> guard{ m_mutexDone };

        m_doneRectangles++;
        if (m_doneRectangles == MandelbrotRectangles::NUM_RECTS) {
            m_done = true;
        }

        done = m_done;
    }

    if (done) {

        // last calculation threads inserts "end-of-pixels-queue" marker
        Pixel pixel{ SIZE_MAX, SIZE_MAX, 0 };
        addPixel(pixel);
    }

    // print some statistics
    WCHAR szText[64];
    ::swprintf(szText, 64, L"< STD::JTHREAD: computePixelsOfRectangle - computed %zu pixels", numPixels);
    ::OutputDebugString(szText);

    return numPixels;
}

size_t MandelbrotProducerConsumerBasedApproach::drawQueuedPixels(std::stop_token token) {

    ::OutputDebugString(L"> STD::JTHREAD: drawQueuedPixels");

    WCHAR szText[128];
    size_t numPixels{};

    std::queue<Pixel> pixels;

    // Uhhhhhhhhh - wie wird diese Endlos Schleife sauber beendet ?????????????????????
    // while (! token.stop_requested()) {
    while (true)
    {
        if (token.stop_requested()) {
            ::OutputDebugString(L"> computePixelsOfRectangle: Stop Requested (1) ################################");
            break;
        }
 
        // RAII
        {
            std::unique_lock guard{ m_mutexPixelsQueue };

            // wait for next available pixels
            // TO BE DONE: Der Name stopRequested ist vermutlich schlecht --- logisch falsch herum
            bool stopRequested{
                m_conditionPixelsAvailable.wait(
                    guard,
                    token,
                    [&]() { return m_pixels.size() != 0; }
                )
            };

            //  DIESER ZUGRIFF IST PROBLEMATISCH : ich checke jetzt die Condition ?!?!?!?!?!
            if (m_pixels.size() == 0) {
                ::swprintf(szText, 128, L"> drawQueuedPixels:         Stop Requested (2) ################################ - drawn so far: %zu", numPixels);
                ::OutputDebugString(szText);
                break;
            }
                 
            // double buffer pattern
            std::swap(pixels, m_pixels);
        }

        while (! pixels.empty()) { 

            Pixel p = pixels.front();
            pixels.pop();

            // end of queue reached?
            if (p.m_x == SIZE_MAX && p.m_y == SIZE_MAX) {
                goto loopEnd;
            }
            else {
                drawPixel(m_hDC, p.m_x, p.m_y, p.m_cr);
                numPixels++;
            }
        }
    }

    loopEnd:

    // there is only a single drawing thread - being responsible for the graphics context
    ::ReleaseDC(m_hWnd, m_hDC);

    {
        std::lock_guard<std::mutex> guard{ m_mutexDone };

        m_doneRectangles++;
        if (m_doneRectangles == MandelbrotRectangles::NUM_RECTS) {
            m_done = true;
        }
    }

    ::swprintf(szText, 64, L"< STD::JTHREAD: drawQueuedPixels - drawed %zu pixels", numPixels);
    ::OutputDebugString(szText);

    return numPixels;
}


void MandelbrotProducerConsumerBasedApproach::drawPixel(HDC hdc, size_t x, size_t y, COLORREF color) const
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
            return std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)> {
                [this](std::stop_token token, struct Rectangle rect, size_t width, size_t height) {
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
        [](std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>& task) {
            return task.get_future();
        }
    );
}

void MandelbrotProducerConsumerBasedApproach::prepareDrawingThread() {

    std::packaged_task <size_t(std::stop_token)> task{
        [this] (std::stop_token token) { return drawQueuedPixels(token); }
    };

    m_drawingTask = std::move (task);
    m_drawingFuture = m_drawingTask.get_future();

    // need "swap idiom" to clear pixels queue
    {
        std::lock_guard<std::mutex> lock{ m_mutexPixelsQueue };

        std::queue<Pixel> empty{};
        std::swap(m_pixels, empty);
    }
}

void MandelbrotProducerConsumerBasedApproach::launchAllThreads()
{
    // starting another phase of calculation and drawing pixels
    {
        std::lock_guard<std::mutex> guard{ m_mutexDone };

        m_done = false;
        m_doneRectangles = 0;
    }

    // creating a new std::stop_source object for this execution cycle
    m_source = std::stop_source{};

    // need stop_token object
    std::stop_token token{ m_source.get_token() };

    launchCalculationThreads(token);

    launchDrawingThread(token);
}

// TODO: Da m�ssen Cols und Rows �bergeben werden !!!!!
// TODO: dAS SOLLte ohne 2 for-Schleifen gehen !!!
// Hmmm, das Problem ist das mit dem Zugriff auf m_rects[j][i] ...
void MandelbrotProducerConsumerBasedApproach::launchCalculationThreads(std::stop_token token) {

    // execute each task in a separate thread
    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++)
    {
        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++)
        {
            std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)> task{
                std::move(m_calculationTasks.front())
            };

            m_calculationTasks.pop_front();

            std::jthread t{ std::move(task), token, m_rects[j][i], m_clientWidth, m_clientHeight };
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
    bool done;

    {
        // need thread safe context to read current value of 'm_done'
        std::lock_guard<std::mutex> guard{ m_mutexDone };
        done = m_done;
    }

    if (!done) {

        requestStop();
        waitAllThreadsDone();
        m_done = true;
    }
}

void MandelbrotProducerConsumerBasedApproach::requestStop() 
{ 
    m_source.request_stop();
}

void MandelbrotProducerConsumerBasedApproach::waitAllThreadsDone()
{
    WCHAR szText[64];
    size_t numPixels{};

    // print some statistics
    ::OutputDebugString(L"> waitAllThreadsDone");

    {
        ::OutputDebugString(L"  waiting end of drawing thread ...");

        // wait for end of single drawing thread
        numPixels = m_drawingFuture.get();

        // print some statistics
        ::swprintf(szText, 64, L"  end of drawing thread: %zu pixels drawn", numPixels);
        ::OutputDebugString(szText);
    }

    // wait for the end of all calculation threads
    while (! m_calculationFutures.empty()) {

        std::future<size_t> future = std::move(m_calculationFutures.front());
        m_calculationFutures.pop_front();

        ::OutputDebugString(L"  waiting end of calculation thread ...");

        // wait for end of a calculation thread
        numPixels = future.get();

        // print some statistics
        ::swprintf(szText, 64, L"  end of calculation thread: %zu pixels calculated", numPixels);
        ::OutputDebugString(szText);
    }

    ::OutputDebugString(L"> waitAllThreadsDone");
}

// =====================================================================================
// End-of-File
// =====================================================================================
