// =====================================================================================
// MandelbrotProducerConsumerBasedApproach.h
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

//#include <thread>
#include <mutex>
#include <latch>
#include <deque>
#include <queue>
#include <future>
#include <condition_variable>
#include <stop_token>


struct Pixel
{
    size_t   m_x;
    size_t   m_y;
    COLORREF m_cr;
};


// TO BE DONE: Welcher Container hat die schnellsten insert am Begin // entfernen am Ende

// TO BE DONE: Möglcierweise für die Thread Prozeduren Namen vergeben,
// dann werden die Namen der Container kürzer
// using YXY = size_t(std::stop_token, struct Rectangle, size_t, size_t);


class MandelbrotProducerConsumerBasedApproach : public MandelbrotBase
{
private:
    // GDI specific data
    HWND m_hWnd;
    HDC  m_hDC;

    // handling of miscellaneous packaged tasks (computation and drawing)
    using ComputationTaskSignature = std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>;

    std::deque<ComputationTaskSignature>        m_calculationTasks;
    std::deque<std::future<size_t>>             m_calculationFutures;
    std::packaged_task<size_t(std::stop_token)> m_drawingTask;
    std::future<size_t>                         m_drawingFuture;

    // concurrency data to handle "Producer-Consumer" implementation
    mutable std::mutex   m_mutexPixelsQueue;
    mutable std::condition_variable_any  m_conditionPixelsAvailable;

    // storing computed pixels to draw
    std::queue<Pixel>    m_pixels;      // !!!!!!!!!!!!!!!!!!! ANDERER Container ?!?!?!?!?
                                        // Da hätten wir doch eine Blocking Thread Safe Queoe !!!!!!!!!!!
                                        // brauche da einen Container mit SCHNELL insert am Anfang und SCHNELL entfernen am Ende
    
    // data to handle premature ending of worker threads
    mutable std::mutex   m_mutexDone;
    std::stop_source     m_source;
    int                  m_doneRectangles;
    bool                 m_done;

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

    void addPixel(Pixel);
    size_t computePixelsOfRectangle(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    size_t drawQueuedPixels(std::stop_token token);
    // void notify();

private:
   virtual void drawPixel(HDC, size_t, size_t, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

