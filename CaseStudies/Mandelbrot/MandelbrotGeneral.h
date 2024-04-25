// =====================================================================================
// MandelbrotGeneral.h
// =====================================================================================

#pragma once

// =====================================================================================

enum class MandelbrotVersion
{
    BasicVersion = 1,                            // single rectangle, nonresponsive
    RectanglesSequential = 2,                    // multiple rectangles, sequential, nonresponsive (blocking)
    RectanglesParallelBlocking = 3,              // multiple rectangles, parallel, nonresponsive (blocking)
    RectanglesParallelBlockingUsingLatch = 4,    // multiple rectangles, parallel, nonresponsive (blocking), using std::latch
    RectanglesParallelNonBlockingClassic = 5,    // multiple rectangles, parallel, responsive (non blocking)
    RectanglesParallelNonBlockingStopToken = 6,  // multiple rectangles, parallel, responsive (non blocking), using std::stop_token
    ProducerConsumerBasedApproach = 7            // multiple rectangles, parallel, responsive (non blocking)
};

constexpr MandelbrotVersion getVersion() {
    return MandelbrotVersion::RectanglesParallelNonBlockingStopToken;
}

// =====================================================================================

using TFloatingPoint = float;                    // float or double or long double

// =====================================================================================

template <typename T>
struct MandelbrotParams
{
    // original limits
    static constexpr T XMIN{ (T)-2.0 };  // minimum x-value (real part)
    static constexpr T XMAX{ (T)+0.75 };  // maximum x-value (real part)
    static constexpr T YMIN{ (T)-1.25 };  // minimum y-value (imaginary part)
    static constexpr T YMAX{ (T)+1.25 };  // maximum y-value (imaginary part)
};

//struct Pixel
//{
//    int m_x;
//    int m_y;
//    COLORREF m_cr;
//};

struct Rectangle
{
    size_t m_left;
    size_t m_top;
    size_t m_right;
    size_t m_bottom;
};

struct MandelbrotRectangles
{
    static constexpr size_t NUM_ROWS { 4 };
    static constexpr size_t NUM_COLS { 4 };

    //static constexpr size_t NUM_ROWS{ 1 };
    //static constexpr size_t NUM_COLS{ 2 };

    static constexpr size_t NUM_RECTS{ (NUM_ROWS * NUM_COLS) };
};

struct MandelbrotWindowDimension
{
    static constexpr size_t WindowHeight{ 2 * 200 };
    static constexpr size_t WindowWidth{ 2 * 250 };
};

// =====================================================================================
// End-of-File
// =====================================================================================
