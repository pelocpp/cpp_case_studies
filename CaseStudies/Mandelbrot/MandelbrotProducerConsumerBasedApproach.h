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
    // data
    mutable std::mutex                    m_mutexQueue;
    mutable std::condition_variable_any   m_conditionPixelsAvailable;

    HWND m_hWnd;
    HDC  m_hDC;

    std::stop_source              m_source;

    std::deque<std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>> m_calculationTasks;
    std::deque<std::future<size_t>>             m_calculationFutures;

    std::packaged_task<size_t(std::stop_token)> m_drawingTask;
    std::future<size_t>                         m_drawingFuture;


    std::queue<Pixel> m_pixels;   // !!!!!!!!!!!!!!!!!!! ANDERER Container ?!?!?!?!?
                                  // Da hätten wir doch eine Blocking Thread Safe Queoe !!!!!!!!!!!

                                  // brauche da einen Container mit SCHNELL insert am Anfang und SCHNELL entfernen am Ende

public:
    // c'tor(s)
    MandelbrotProducerConsumerBasedApproach();

    // getter / setter
    void requestStop() { m_source.request_stop(); }

    // ------------------------------------------------------

    // DRITTER Neuer Ansatz:
    // Daten

    mutable std::mutex        m_mutexDone;

    int m_doneRectangles = 0;  // In den Konstruktor aufnehmen !!!!!!!!!!!!!!!!!!!!!!!!

    bool m_done = true;     // In den Konstruktor aufnehmen !!!!!!!!!!!!!!!!!!!!!!!!


    // ------------------------------------------------------

public:
    // public interface
    void setHWND(HWND hWnd);
    void clearAllQueues();
    void prepareAllThreads(int rows, int cols);
    void launchAllThreads();
    void waitAllThreadsDone();

private:
    // private helper methods
    void prepareCalculationThreads(int rows, int cols);
    void prepareDrawingThread();
    void launchCalculationThreads(std::stop_token);
    void launchDrawingThread(std::stop_token);

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

