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

class MandelbrotProducerConsumerBasedApproach : public MandelbrotBase
{
private:
    // data
    mutable std::mutex m_mutex;
    std::condition_variable m_conditionPixelsAvailable;  // TODO  Auch mutable ???

    std::stop_source m_source;
    std::atomic<bool> m_done;
    std::atomic<int> m_doneRectangles;


    std::deque<std::packaged_task<size_t(std::stop_token, struct Rectangle, size_t, size_t)>> m_calculationTasks;
    std::deque<std::future<size_t>> m_calculationFutures;  // TODO: Was mache ich mit diesen Futures

    std::packaged_task<void(std::stop_token)> m_drawingTask;
    std::future<void> m_drawingFuture;  // TODO: Was mache ich mit dieser Futures

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
    bool getDone () { return m_done; }

    //// -----------------------------------------------------
    //// Neuer Ansatz:
    //// Daten
    //std::latch m_latch{ MandelbrotRectangles::NUM_RECTS + 1 };
    //std::atomic<bool> m_pendingTasks{ false };

    //// Neuer Ansatz
    //void taskDone() { m_latch.count_down(); }

    //bool tasksPending() { return m_pendingTasks; }

    ////     std::latch m_latch{ MandelbrotRectangles::NUM_RECTS + 1 };

    //void resetLatch() { m_latch = std::latch{ MandelbrotRectangles::NUM_RECTS + 1 }; }

    //void waitForPendingThreads() { m_latch.wait(); }

    // -----------------------------------------------------
    // ZWEITER Neuer Ansatz:
    // Daten

    // TO BE DONE: std::unique_ptr !!!!
    
    //std::latch* m_latch = nullptr;

    //std::atomic<bool> m_pendingTasks{ false };

    //// Neuer Ansatz
    //void taskDone() { m_latch->count_down(); }

    //bool tasksPending() { return m_pendingTasks; }
    //void setPendingTasks() { m_pendingTasks = true; }
    //void clearPendingTasks() { m_pendingTasks = false; }

    ////     std::latch m_latch{ MandelbrotRectangles::NUM_RECTS + 1 };

    //void resetLatch() { 
    //    delete m_latch;
    //    m_latch = new std::latch{ MandelbrotRectangles::NUM_RECTS + 1 }; 
    //}

    //void waitForPendingThreads() {
    //    m_latch->wait();
    //    
    //    clearPendingTasks();
    //}

    // ------------------------------------------------------

        // DRITTER Neuer Ansatz:
    //// Daten
    std::atomic<int> m_tasksCounter { 0 };  // MandelbrotRectangles::NUM_RECTS + 1 

    bool tasksPending() { return m_tasksCounter > 0; } 

    void taskDone() { -- m_tasksCounter; }

    void resetTasksCounter(int counter) { m_tasksCounter = counter; }

 //    void reseTasksCounter(int value) { m_tasksCounter = MandelbrotRectangles::NUM_RECTS + 1; }

    void waitForPendingTasks() { 
        waitAllThreadsDone();
    }

    // ------------------------------------------------------




public:
    // public interface
    //void waitRectanglesDone();
    void clearAllQueues();

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
    size_t computePixelOfRectangle(std::stop_token token, struct Rectangle rect, size_t maxWidth, size_t maxHeight);
    void drawQueuedPixels(std::stop_token token);

private:
    // private helper functions
   // size_t paintRectangle(std::stop_token, HWND, HDC, struct Rectangle);

private:
   virtual void drawPixel(HDC, int, int, COLORREF) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================

