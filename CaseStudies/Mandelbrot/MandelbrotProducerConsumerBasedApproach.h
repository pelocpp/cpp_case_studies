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


// TO BE DONE: Warum sind die Member int und nicht size_t

struct Pixel
{
    int      m_x;
    int      m_y;
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
    mutable std::mutex            m_mutexQueue;
    std::condition_variable_any   m_conditionPixelsAvailable;  // TODO  Auch mutable ??? Eher nein !!!

    std::stop_source              m_source;

    std::deque<std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>> m_calculationTasks;
    std::deque<std::future<size_t>>             m_calculationFutures;

    std::packaged_task<size_t(std::stop_token)> m_drawingTask;
    std::future<size_t>                         m_drawingFuture;

    // "producer/consumer" based data
    HWND m_hWnd;
    HDC  m_hDC;

    std::queue<Pixel> m_pixels;   // !!!!!!!!!!!!!!!!!!! ANDERER Container ?!?!?!?!?
                                  // Da hätten wir doch eine Blocking Thread Safe Queoe !!!!!!!!!!!

                                  // brauche da einen Container mit SCHNELL insert am Anfang und SCHNELL entfernen am Ende

public:
    // c'tor(s)
    MandelbrotProducerConsumerBasedApproach();

    // getter / setter
    //int  getDoneRectangles() { return m_doneRectangles; }
    //void incDoneRectangles() { ++m_doneRectangles; }
    //void resetDoneRectangles() { m_doneRectangles = 0; }

    void requestStop() { m_source.request_stop(); }

   //  bool getDone () { return m_done; }

    // ------------------------------------------------------

    // DRITTER Neuer Ansatz:
    // Daten

    mutable std::mutex        m_mutexDone;

    int m_doneRectangles = 0;  // In den Konstruktor aufnehmen !!!!!!!!!!!!!!!!!!!!!!!!

    bool m_done = true;     // In den Konstruktor aufnehmen !!!!!!!!!!!!!!!!!!!!!!!!

    // std::atomic<bool>         m_done;
    // std::atomic<int>          m_doneRectangles;
    // std::atomic<int>       m_tasksCounter { 0 };  // MandelbrotRectangles::NUM_RECTS + 1 

    //bool tasksPending() { return m_tasksCounter > 0; } 

    //void taskDone() { -- m_tasksCounter; }

    //void resetTasksCounter(int counter) { m_tasksCounter = counter; }

    //void waitForPendingTasks() { 
    //    waitAllThreadsDone();
    //}

    // ------------------------------------------------------

public:
    // public interface
    void setHWND(HWND hWnd);
    void clearAllQueues();
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
    size_t computePixelOfRectangle(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    size_t drawQueuedPixels(std::stop_token token);

private:
   virtual void drawPixel(HDC, int, int, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

