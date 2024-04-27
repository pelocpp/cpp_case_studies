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

    //std::atomic<int> m_doneRectangles;
    //std::stop_source m_source;

    //std::deque<std::packaged_task<size_t(std::stop_token, HWND, HDC, struct Rectangle)>> m_tasks;
    //std::deque<std::future<size_t>> m_futures;

     std::deque<std::packaged_task<size_t(struct Rectangle, size_t, size_t)>> m_calculationTasks;
     std::deque<std::future<size_t>> m_calculationFutures;


     std::packaged_task<void()> m_drawingTask;
     std::future<void> m_drawingFuture;


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

public:
    // public interface
    //void startPaintingRectanglesAsync(HWND hWnd, HDC hDC);
    //void waitRectanglesDone();

    void setHWND(HWND hWnd);
    void addPixel(Pixel);
    // void notify();
    size_t computePixels(struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    void drawPixelXXX();


    void prepareCalculationThreads();
    void prepareDrawingThread();

    void startCalculationThreads();
    void startDrawingThread();


private:
    // Hmmm, das ist der geerbte Vertrag ?!?!?!
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;

    // WELCHE hehen hier private

private:
    // private helper functions
   // size_t paintRectangle(std::stop_token, HWND, HDC, struct Rectangle);

private:
   // virtual void drawPixel(HDC, int x, int y, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

