// =====================================================================================
// Mendelbrot Set with C++: Different Approaches
// =====================================================================================

#pragma once

namespace MandelbrotBasisVersion {

    enum class MandelbrotVersion {
        BasicVersion,                    // single rectangle, nonresponsive
        RectanglesSequential,            // multiple rectangles, sequential, nonresponsive (blocking)
        RectanglesParallelBlocking,      // multiple rectangles, parallel, nonresponsive (blocking)
        RectanglesParallelNonBlocking,   // multiple rectangles, parallel, responsive (non blocking)
        ProducerConsumerBasedApproach    // multiple rectangles, parallel, responsive (non blocking)
    };

    template <typename T>
    class MandelbrotParams {
    public:
        // original limits
        static constexpr T XMIN = -2.0;   // minimum x-value (real part)
        static constexpr T XMAX = +0.75;  // maximum x-value (real part)
        static constexpr T YMIN = -1.25;  // minimum y-value (imaginary part)
        static constexpr T YMAX = +1.25;  // maximum y-value (imaginary part)
    };

    struct Pixel {
        int m_x;
        int m_y;
        COLORREF m_cr;
    };

    class MandelbrotRectangles {
    public:
        static constexpr size_t NUM_ROWS = 1;  
        static constexpr size_t NUM_COLS = 1;  
        static constexpr size_t NUM_RECTS = (NUM_ROWS * NUM_COLS);
    }; 

    class Mandelbrot {
    public:
        static const int NumColors = 256;
        static const int Limit = 5;

        static const int WindowHeight = 450;
        static const int WindowWidth = 500;

    private:
        MandelbrotVersion m_version;

        long m_clientWidth;
        long m_clientHeight;

        int m_NumRows;
        int m_NumCols;

        MandelbrotPalette m_palette;

        std::array <
            std::array <RECT, MandelbrotRectangles::NUM_COLS>, 
            MandelbrotRectangles::NUM_ROWS> m_rects;

        std::deque<std::packaged_task<long(HWND, HDC, RECT)>> m_tasks;
        std::deque<std::future<long>> m_futures;

        std::mutex m_mutex;
        std::atomic<bool> m_abort;
        std::atomic<int> m_doneRectangles;

        std::condition_variable m_conditionPixelsAvailable;
        std::queue <Pixel> m_pixels;

        // "producer/consumer" based data
        HWND m_hWnd;
        HDC m_hDC;

        std::deque<std::packaged_task<long(RECT, long, long)>> m_CalculationTasks;
        std::deque<std::future<long>> m_CalculationFutures;
        std::packaged_task<long()> m_DrawingTask;
        std::future<long> m_DrawingFuture;

    public:
        // c'tor
        Mandelbrot();

        // getter/setter
        MandelbrotVersion getVersion() { return m_version; }

        void setClientWidth(long clientWidth) { m_clientWidth = clientWidth; }
        long getClientWidth() { return m_clientWidth; }

        void setClientHeight(long clientHeight) { m_clientHeight = clientHeight; }
        long getClientHeight() { return m_clientHeight; }

        void setAbort(bool flag) { m_abort = flag; }
        bool getAbort() { return m_abort; }

        int getDoneRectangles() { return m_doneRectangles; }
        void incDoneRectangles() {++m_doneRectangles; }
        void resetDoneRectangles() { m_doneRectangles = 0; }

        // public interface
        void computeRects();
        void paint(HDC);
        void paintRectangles(HDC);
        void paintRectanglesAsync(HDC);

        void startPaintingRectanglesAsync(HWND, HDC);
        void waitRectanglesDone();

        // public "producer - consumer" interface

        // TODO: Welche dieser MEthoden können privat deklariert werden .....
        void setHWND(HWND hWnd);
        void addPixel(Pixel);
        void notify();
        long computePixel(RECT rect, long maxWidth, long maxHeight);
        long drawPixel();
        void startCalculationThread();
        void startDrawingThread();

    private:
        // private helper methods
        void paintRect(HDC, RECT);
        std::pair<std::wstring, long> paintRectAsync(HDC, RECT);
        long startPaintRectAsync(HWND, HDC, RECT);

        template <typename T = float, typename MANDELBROT_COORDINATES>
        std::complex<T> getComplex(long x, long y, long max_x, long max_y);

        long computeSequence(std::complex<float> point);
    };
};

// =====================================================================================
// End-of-File
// =====================================================================================
