// =====================================================================================
// MandelbrotBase.h
// =====================================================================================

#pragma once

#include <complex>
#include <array>

#include "MandelbrotGeneral.h"
#include "MandelbrotPalette.h"

class MandelbrotBase
{
public:
    static const int Limit{ 5 };

public:
    // c'tor(s)
    MandelbrotBase();

protected:
    std::array<std::array <struct Rectangle, MandelbrotRectangles::NUM_COLS>, MandelbrotRectangles::NUM_ROWS> m_rects;

protected:
    size_t m_clientWidth;
    size_t m_clientHeight;

protected:
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const = 0;

public:
    // getter/setter
    void setClientWidth(size_t clientWidth) { m_clientWidth = clientWidth; }
    size_t getClientWidth() const { return m_clientWidth; }

    void setClientHeight(size_t clientHeight) { m_clientHeight = clientHeight; }
    size_t getClientHeight() const { return m_clientHeight; }

    // public interface
    void computeRects(int rows, int cols);

public:
    // public helper functions
    std::pair<std::wstring, size_t> paintRectangle(HDC hDC, struct Rectangle rect) const;
    std::pair<std::wstring, size_t> paintRectangle(HDC hDC) const;

protected:
    // protected helper templated methods
    template <typename T>
    std::complex<T> getComplex(size_t x, size_t y, size_t maxWidth, size_t maxHeight) const
    {
        // short hand constants for the Mandelbrot coordinates system
        static T XMIN { MandelbrotParams<T>::XMIN };
        static T XMAX { MandelbrotParams<T>::XMAX };
        static T YMIN { MandelbrotParams<T>::YMIN };
        static T YMAX { MandelbrotParams<T>::YMAX };

        return std::complex<T> {
            XMIN + (XMAX - XMIN) * x / maxWidth, 
            YMAX + (YMIN - YMAX) * y / maxHeight
        };
    }

    template <typename T>
    size_t computeSequence(std::complex<T> point) const
    {
        std::complex<T> number{};
        size_t count{};

        while (count != MandelbrotPalette::NumColors && std::abs(number) < Limit) {
            number = number * number + point;
            ++count;
        }

        return count;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
