// =====================================================================================
// MandelbrotProducerConsumerBasedApproach.cpp
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#include "MandelbrotGeneral.h"
#include "MandelbrotProducerConsumerBasedApproach.h"
#include "MandelbrotPalette.h"

#include <complex>
#include <deque>
#include <future>
#include <mutex>
#include <thread>



// ACHTUNG !!!!!!!!!!!!!!!!!!!!!!!

// ALLE QUEUES ... Tasks, futures, Pixels müssen beim "Neustart" geleert sein !!!!!!!!!!!!


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

size_t MandelbrotProducerConsumerBasedApproach::computePixels(struct Rectangle rect, size_t maxWidth, size_t maxHeight) {

    ::OutputDebugString(L"> computePixels Begin");

    size_t numPixels{};

    for (size_t y{ rect.m_top }; y != rect.m_bottom; y++)
    {
        for (size_t x{ rect.m_left }; x != rect.m_right; x++)
        {
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

    ::OutputDebugString(L"< computePixels End");

    return numPixels;
}

void MandelbrotProducerConsumerBasedApproach::drawPixelXXX() {

    ::OutputDebugString(L"> drawPixelXXX Begin");

    while (true) {

        std::unique_lock guard(m_mutex);

        // are pixels available ?
        m_conditionPixelsAvailable.wait(
            guard,
            [&] () { 
                return m_pixels.size() > 0;
            }
        );

        //// premature end of drawing
        //if (m_abort == true) {
        //    break;
        //}

        //WCHAR szText[32];
        //wsprintf(szText, L"ProducerConsumerBasedApproach: painting %d pixel", (int) m_pixels.size());
        //::OutputDebugString(szText);

        if (m_pixels.size() > 0) {

            size_t size = m_pixels.size();
            while (size != 0) {
                Pixel p = m_pixels.front();
                m_pixels.pop();

            //     ::SetPixelV(m_hDC, (int) p.m_x, (int) p.m_y, p.m_cr);
                drawPixel(m_hDC, p.m_x, p.m_y, p.m_cr);
                
                --size;
            }
        }
    }

    ::OutputDebugString(L"< drawPixel Begin");
}

// Hmmm, das ist der geerbte Vertrag ?!?!?!
void MandelbrotProducerConsumerBasedApproach::drawPixel(HDC hdc, int x, int y, COLORREF color) const
{
    ::SetPixelV(hdc, x, y, color);
}




// TODO: Da müssen Cols und Rows übergeben werden !!!!!
void MandelbrotProducerConsumerBasedApproach::prepareCalculationThreads() {


    // TO BE DONE: DAS geht mit std::generate ...


    // define tasks, store corresponding futures
    for (size_t j{}; j != MandelbrotRectangles::NUM_ROWS; j++)
    {
        for (size_t i{}; i != MandelbrotRectangles::NUM_COLS; i++)
        {
            std::packaged_task <size_t(struct Rectangle, size_t, size_t)> task{
                [this](struct Rectangle rect, size_t width, size_t height) {
                    return computePixels(rect, width, height);
                }
            };

            std::future<size_t> future = task.get_future();

            m_calculationTasks.push_back(std::move(task));
            m_calculationFutures.push_back(std::move(future));
        }
    }

}
 
// TODO: Da müssen Cols und Rows übergeben werden !!!!!
void MandelbrotProducerConsumerBasedApproach::startCalculationThreads() {


    // execute each task in a separate thread
    for (int j = 0; j < MandelbrotRectangles::NUM_ROWS; j++)
    {
        for (int i = 0; i < MandelbrotRectangles::NUM_COLS; i++)
        {
            std::packaged_task<size_t(struct Rectangle, size_t, size_t)> task{
                std::move(m_calculationTasks.front())
            };

            m_calculationTasks.pop_front();

            std::jthread t(std::move(task), m_rects[j][i], m_clientWidth, m_clientHeight);
            t.detach();
        }
    }

}

void MandelbrotProducerConsumerBasedApproach::prepareDrawingThread() {

    //std::packaged_task<void()> task{
    //    std::bind(&MandelbrotProducerConsumerBasedApproach::drawPixelXXX, this)
    //};

    std::packaged_task <void()> task{
        [this]() { return drawPixelXXX(); }
    };

    m_drawingFuture = task.get_future();
    m_drawingTask = std::move (task);

    //std::thread t(std::move(task));
    //t.detach();
}

void MandelbrotProducerConsumerBasedApproach::startDrawingThread() {

    //std::packaged_task<void()> task{
    //    std::bind(&MandelbrotProducerConsumerBasedApproach::drawPixelXXX, this)
    //};

    //m_drawingFuture = task.get_future();
    ////m_DrawingTask = std::move (task);

    std::thread t(std::move(task));
    t.detach();
}

// =====================================================================================
// End-of-File
// =====================================================================================

