// =====================================================================================
// MandelbrotProducerConsumerBasedApproach.h
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"
#include "Pixel.h"

#include <mutex>
#include <atomic>
#include <latch>
#include <deque>
#include <queue>
#include <stack>
#include <future>
#include <condition_variable>
#include <stop_token>

// TO BE DONE: Welcher Container hat die schnellsten insert am Begin // entfernen am Ende

// TO BE DONE: Möglcierweise für die Thread Prozeduren Namen vergeben,
// dann werden die Namen der Container kürzer
// using YXY = size_t(std::stop_token, struct Rectangle, size_t, size_t);


class MandelbrotProducerConsumerBasedApproach : public MandelbrotBase
{
private:
    // GDI specific data
    HWND                                        m_hWnd;

    // handling of miscellaneous packaged tasks (computation and drawing)
    using ComputationTaskSignature = std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>;
    using DrawingTaskSignature = std::packaged_task<size_t(std::stop_token)>;

    std::deque<ComputationTaskSignature>        m_calculationTasks;
    std::deque<std::future<size_t>>             m_calculationFutures;
    DrawingTaskSignature                        m_drawingTask;
    std::future<size_t>                         m_drawingFuture;

    // concurrency data to secure "Producer-Consumer" implementation
    mutable std::mutex                          m_mutexPixelsQueue;
    mutable std::condition_variable_any         m_conditionPixelsAvailable;

    // storing computed pixels to draw
                                                // Da hätten wir doch eine Blocking Thread Safe Queoe !!!!!!!!!!!
                                                // brauche da einen Container mit SCHNELL insert am Anfang und SCHNELL entfernen am Ende
    std::deque<Pixel>                           m_pixelsQueue;

    // data to handle premature ending of worker threads
    mutable std::mutex   m_mutexDone;             // <========== da brauche ich vielleicht 2 verschiedene Mutexe !!!!!
    std::stop_source     m_source;
    // size_t               m_doneRectangles;

    // count number of rectangles being calculated
    mutable std::mutex                         m_mutexRectanglesCalculated;
    size_t                                     m_numRectanglesCalculated;
    bool                                       m_calculationsDone;


    // watching a single thread drawing pixels
    mutable std::mutex                         m_mutexDrawingDone;
    bool                                       m_drawingDone;

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
    size_t computePixelsOfRectangle(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    size_t drawQueuedPixels(std::stop_token token);
    // void notify();

private:
   virtual void drawPixel(HDC, size_t, size_t, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

