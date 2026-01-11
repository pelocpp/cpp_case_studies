// =====================================================================================
// Mandelbrot_07_ProducerConsumerBasedApproach.h
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"
#include "Pixel.h"

#include <chrono>
#include <condition_variable>
#include <cstddef>                 // std::size_t
#include <deque>
#include <future>
#include <latch>
#include <mutex>
#include <queue>
#include <stack>
#include <stop_token>

// TO BE DONE: Welcher Container hat die schnellsten insert am Begin // entfernen am Ende


class MandelbrotProducerConsumerBasedApproach : public MandelbrotBase
{
private:
    // GDI specific data
    HWND                                           m_hWnd;

    // handling of miscellaneous packaged tasks (computation and drawing)
    using ComputationTaskSignature = std::packaged_task<std::size_t(std::stop_token, struct Rectangle, std::size_t, std::size_t)>;
    using DrawingTaskSignature = std::packaged_task<std::size_t(std::stop_token)>;

    std::deque<ComputationTaskSignature>           m_calculationTasks;
    DrawingTaskSignature                           m_drawingTask;
    std::deque<std::future<std::size_t>>           m_calculationFutures;
    std::future<std::size_t>                       m_drawingFuture;

    // concurrency data to secure "Producer-Consumer" implementation
    mutable std::mutex                             m_mutexPixelsQueue;
    mutable std::condition_variable_any            m_conditionPixelsAvailable;

    // storing computed pixels to draw
    std::deque<Pixel>                              m_pixelsQueue;

    // data to handle premature ending of worker threads
    std::stop_source                               m_source;

    // count number of rectangles being calculated
    mutable std::mutex                             m_mutexRectanglesCalculated;
    std::size_t                                         m_numRectanglesCalculated;
    bool                                           m_calculationsDone;

    // watching a single thread drawing pixels
    mutable std::mutex                             m_mutexDrawingDone;
    bool                                           m_drawingDone;

    // stop watch
    std::chrono::high_resolution_clock::time_point m_begin;

public:
    // c'tor(s)
    MandelbrotProducerConsumerBasedApproach();

    // ------------------------------------------------------

public:
    // public interface
    void setHWND(HWND hWnd);
    void prepareAllThreads(int rows, int cols);
    void launchAllThreads();
    void cancelActiveThreadsIfAny();

private:
    // private helper methods
    void prepareCalculationThreads(int rows, int cols);
    void prepareDrawingThread();
    void launchCalculationThreads(std::stop_token);
    void launchDrawingThread(std::stop_token);
    void requestStop();
    void waitAllThreadsDone();

    void addPixel(const Pixel& pixel);
    std::size_t computePixelsOfRectangle(std::stop_token token, struct Rectangle rect, std::size_t maxWidth, std::size_t maxHeight);
    std::size_t drawQueuedPixels(std::stop_token token);
    // void notify();

private:
   virtual void drawPixel(HDC, std::size_t, std::size_t, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

