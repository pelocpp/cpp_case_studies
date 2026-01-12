// =====================================================================================
// MandelbrotCommon.h
// =====================================================================================

#pragma once

#include <cstddef>                               // std::size_t

// =====================================================================================

// Palette 
inline constexpr std::size_t NumColors = 256;
inline constexpr std::size_t Limit = 4;

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
    return MandelbrotVersion::BasicVersion;
}

// =====================================================================================

using TFloatingPoint = float;                    // float or double or long double

// =====================================================================================

template <typename T>
struct MandelbrotParams
{
    // original limits
    //static constexpr T XMIN{ (T) -2.0  };  // minimum x-value (real part)
    //static constexpr T XMAX{ (T) +0.75 };  // maximum x-value (real part)
    //static constexpr T YMIN{ (T) -1.25 };  // minimum y-value (imaginary part)
    //static constexpr T YMAX{ (T) +1.25 };  // maximum y-value (imaginary part)

    //static constexpr T XMIN{ (T)-0.745468 };  // minimum x-value (real part)
    //static constexpr T XMAX{ (T)-0.745385 };  // maximum x-value (real part)
    //static constexpr T YMIN{ (T)+0.112975 };  // minimum y-value (imaginary part)
    //static constexpr T YMAX{ (T)+0.113044 };  // maximum y-value (imaginary part)


    //double XMIN = -0.745468;  // minimum x-value (real part)
    //double XMAX = -0.745385;  // maximum x-value (real part)
    //double YMIN = +0.112975;  // minimum y-value (imaginary part)
    //double YMAX = +0.113044;  // maximum y-value (imaginary part)


    // Christian Kormanyos: well-known, classic Mandelbrot 
    static constexpr T XCENTER{ (T) -0.75 };          // centered x-value (real part)
    static constexpr T YCENTER{ (T) 0.0 };            // centered x-value (imaginary part)
    static constexpr T HalfWidth{ (T) 1.35 };         // half width of rectangle

    static constexpr T XMIN{ XCENTER - HalfWidth };   // minimum x-value (real part)
    static constexpr T XMAX{ XCENTER + HalfWidth };   // maximum x-value (real part)
    static constexpr T YMIN{ YCENTER - HalfWidth };   // minimum y-value (imaginary part)
    static constexpr T YMAX{ YCENTER + HalfWidth };   // maximum y-value (imaginary part)

    // Christian Kormanyos: Swirly Seahorses and Mini Mandelbrot - does't work
    //static constexpr T XCENTER{ (T) 0.7453983606667815 };   // centered x-value (real part)
    //static constexpr T YCENTER{ (T) 0.1125046349959942 };   // centered x-value (imaginary part)
    //static constexpr T HalfWidth{ (T) 1.76e-12 };           // half width of rectangle

    //static constexpr T XMIN{ XCENTER - HalfWidth };   // minimum x-value (real part)
    //static constexpr T XMAX{ XCENTER + HalfWidth };   // maximum x-value (real part)
    //static constexpr T YMIN{ YCENTER - HalfWidth };   // minimum y-value (imaginary part)
    //static constexpr T YMAX{ YCENTER + HalfWidth };   // maximum y-value (imaginary part)
};

struct Rectangle
{
    std::size_t m_left;
    std::size_t m_top;
    std::size_t m_right;
    std::size_t m_bottom;
};

struct MandelbrotRectangles
{
    static constexpr std::size_t NUM_ROWS { 6 };
    static constexpr std::size_t NUM_COLS { 6 };

    static constexpr std::size_t NUM_RECTS{ (NUM_ROWS * NUM_COLS) };
};

struct MandelbrotWindowDimension
{
    static constexpr std::size_t WindowHeight{ 2 * 200 };
    static constexpr std::size_t WindowWidth{ 2 * 250 };
};

// =====================================================================================
// End-of-File
// =====================================================================================
