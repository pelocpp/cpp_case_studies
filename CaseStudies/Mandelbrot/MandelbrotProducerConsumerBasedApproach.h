// =====================================================================================
// MandelbrotProducerConsumerBasedApproach.h
// Variant 07: Parallel - Non Blocking - Producer Consumer Based Approach
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

//#include <thread>
#include <mutex>
#include <deque>
#include <queue>
#include <future>
#include <condition_variable>
#include <stop_token>



// TO BE DONE: Warum sind die Member int und nicht size_t

struct Pixel
{
    int      m_x;
    int      m_y;
    COLORREF m_cr;
};




// TO BE DONE: Welcher Container hat die schnellsten insert am Begin // entfernen am Ende

class MandelbrotProducerConsumerBasedApproach : public MandelbrotBase
{
private:
     mutable std::mutex m_mutex;
     std::condition_variable m_conditionPixelsAvailable;  // TODO  Auch mutable ???

     std::stop_source m_source;
     std::atomic<bool> m_done;

     std::deque<std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>> m_calculationTasks;
     std::deque<std::future<size_t>> m_calculationFutures;  // TODO: Was mache ich mit diesen Futures

     std::packaged_task<void(std::stop_token)> m_drawingTask;
     std::future<void> m_drawingFuture;  // TODO: Was mache ich mit dieser Futures

    // "producer/consumer" based data
    HWND m_hWnd;
    HDC  m_hDC;

    std::queue<Pixel> m_pixels;       // !!!!!!!!!!!!!!!!!!! ANDERER Container ?!?!?!?!?
                                       // Da hätten wir doch eine Blocking Thread Safe Queoe !!!!!!!!!!!

public:
    // c'tor(s)
    MandelbrotProducerConsumerBasedApproach();

    // getter / setter
    //int  getDoneRectangles() { return m_doneRectangles; }
    //void incDoneRectangles() { ++m_doneRectangles; }
    //void resetDoneRectangles() { m_doneRectangles = 0; }

    // void requestAbort() { m_source.request_stop(); }

    bool getDone () { return m_done; }

public:
    // public interface
    //void waitRectanglesDone();

    void setHWND(HWND hWnd);

    void prepareAllThreads(int rows, int cols);
    void launchAllThreads();
    void waitAllThreadsDone();

private:
    void prepareCalculationThreads(int rows, int cols);
    void prepareDrawingThread();

    void launchCalculationThreads(std::stop_token);
    void launchDrawingThread(std::stop_token);

    void addPixel(Pixel);
    // void notify();
    size_t computePixels(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    void drawPixelXXX(std::stop_token token);

private:
    // private helper functions
   // size_t paintRectangle(std::stop_token, HWND, HDC, struct Rectangle);

private:
   virtual void drawPixel(HDC, int, int, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

