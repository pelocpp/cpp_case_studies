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


// TODO: Hmmm, das muss global irgendwo anders hin ....
extern MandelbrotPalette g_palette;

// c'tor(s)

// TODO: Da fehlen Default Vorbelegungen ...
MandelbrotProducerConsumerBasedApproach::MandelbrotProducerConsumerBasedApproach() 
    : m_mutex{}, m_hWnd{}, m_hDC{}
{}

void MandelbrotProducerConsumerBasedApproach::setHWND(HWND hWnd)
{
    m_hWnd = hWnd;
    m_hDC = ::GetDC(m_hWnd);
}


void MandelbrotProducerConsumerBasedApproach::addPixel(Pixel pixel)
{
    std::lock_guard<std::mutex> lock{ m_mutex };

    m_pixels.push(pixel);
    if (m_pixels.size() > 10) {
        m_conditionPixelsAvailable.notify_one();   // wakeup drawing thread
    }

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // a) der notity aus der Sperre raus !!!

    // b) das geht mit einer andere n Lock Klasse !!!!!!!!!!!!
}

size_t MandelbrotProducerConsumerBasedApproach::computePixelOfRectangle(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight) {

    ::OutputDebugString(L"> computePixelOfRectangle");

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
            // premature end of drawing
            if (token.stop_requested()) {
                ::OutputDebugString(L"> computePixelOfRectangle: STOP REQUESTED");
                goto loopEnd;
            }

            std::complex<TFloatingPoint> comp { 
                getComplex<TFloatingPoint>(x, y, m_clientWidth, m_clientHeight) 
            };

            size_t iterations{ computeSequence(comp) };
            COLORREF color{ g_palette[iterations - 1] };

            // enter pixel into queue (queue is thread safe)
            Pixel pixel{ (int) x, (int) y, color };
            addPixel(pixel);
            ++numPixels;
        }

        // notity painting thread row per row
        // // TO BE DONE; Das mit dem notify muss genau betrachtet werden !!!!!
      //  notify();
    }

    loopEnd:
    ::OutputDebugString(L"< computePixelOfRectangle");

    return numPixels;
}

void MandelbrotProducerConsumerBasedApproach::drawQueuedPixels(std::stop_token token) {

    ::OutputDebugString(L"> drawQueuedPixels");

    size_t numPixels{};

    // Uhhhhhhhhh - wie wird diese Endlos Schleife sauber beendet ?????????????????????
    while (true) {

        // TODO Hmmmmmm, komme ich da mit eine STop Callback Routine besser raus ??????????

        // premature end of drawing
        if (token.stop_requested()) {
            ::OutputDebugString(L"> drawQueuedPixels: STOP REQUESTED");
            break;
        }

        std::unique_lock guard{ m_mutex };

        // are pixels available ?
        m_conditionPixelsAvailable.wait(
            guard,
            [&] () { 
                return m_pixels.size() > 0;
            }
        );

        //WCHAR szText[32];
        //wsprintf(szText, L"ProducerConsumerBasedApproach: painting %d pixel", (int) m_pixels.size());
        //::OutputDebugString(szText);

        if (m_pixels.size() > 0) {

            size_t size = m_pixels.size();
            while (size != 0) {
                Pixel p = m_pixels.front();
                m_pixels.pop();

                drawPixel(m_hDC, p.m_x, p.m_y, p.m_cr); numPixels;
                
                --size;
            }
        }
    }

    // print some statistics
    WCHAR szText[64];
    ::swprintf(szText, 64, L"| drawed %zu pixels.", numPixels);
    OutputDebugString(szText);

    // there is only a single drawing thread - being responsible for the graphics context
    ::ReleaseDC(m_hWnd, m_hDC);

    // regular end of calculation and drawing pixels reached
    m_done = true;

    ::OutputDebugString(L"< drawPixel");
}

// Hmmm, das ist der geerbte Vertrag ?!?!?!
void MandelbrotProducerConsumerBasedApproach::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    ::SetPixelV(hdc, x, y, color);
}

void MandelbrotProducerConsumerBasedApproach::clearAllQueues() {

}

void MandelbrotProducerConsumerBasedApproach::prepareAllThreads(int rows, int cols)
{
    prepareCalculationThreads(rows, cols);
    prepareDrawingThread();
}

// TODO: Da m�ssen Cols und Rows �bergeben werden !!!!!
void MandelbrotProducerConsumerBasedApproach::prepareCalculationThreads(int rows, int cols) {


    // TO BE DONE: DAS geht mit std::generate ...

    // define tasks, store corresponding futures
    for (size_t j{}; j != rows; j++)
    {
        for (size_t i{}; i != cols; i++)
        {
            std::packaged_task <size_t(std::stop_token, struct Rectangle, size_t, size_t)> task{
                [this] (std::stop_token token, struct Rectangle rect, size_t width, size_t height) {
                    return computePixelOfRectangle(token, rect, width, height);
                }
            };

            std::future<size_t> future = task.get_future();

            m_calculationTasks.push_back(std::move(task));
            m_calculationFutures.push_back(std::move(future));
        }
    }
}


void MandelbrotProducerConsumerBasedApproach::prepareDrawingThread() {

    std::packaged_task <void(std::stop_token)> task{
        [this] (std::stop_token token) { return drawQueuedPixels(token); }
    };

    m_drawingFuture = task.get_future();
    m_drawingTask = std::move (task);

    //std::thread t(std::move(task));
    //t.detach();
}

void MandelbrotProducerConsumerBasedApproach::launchAllThreads()
{
    // starting another phase of calculation and drawing pixels
    m_done = false;

    // creating a new std::stop_source object for this execution
    m_source = std::stop_source{};

    // need stop_token object
    std::stop_token token{ m_source.get_token() };

    launchCalculationThreads(token);

    launchDrawingThread(token);
}

// TODO: Da m�ssen Cols und Rows �bergeben werden !!!!!
// TODO: dAS SOLLte ohne 2 for-Schleifen gehen !!!
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

            std::jthread t(std::move(task), token, m_rects[j][i], m_clientWidth, m_clientHeight);
            t.detach();
        }
    }
}

void MandelbrotProducerConsumerBasedApproach::launchDrawingThread(std::stop_token token) {

    std::thread t(std::move(m_drawingTask), token);
    t.detach();
}

void MandelbrotProducerConsumerBasedApproach::waitAllThreadsDone()
{
    // wait for the end of all calculation threads
    while (! m_calculationFutures.empty()) {

        std::future<size_t> future = std::move(m_calculationFutures.front());
        m_calculationFutures.pop_front();
        size_t numPixels = future.get();

        // print some statistics
        WCHAR szText[64];
        ::swprintf(szText, 64, L"   ... %zu pixels painted", numPixels);
        OutputDebugString(szText);
    }

    // wait for end of single drawing thread
    if (m_drawingFuture.valid()) {
        m_drawingFuture.get();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
