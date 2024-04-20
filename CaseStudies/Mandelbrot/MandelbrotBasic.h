// =====================================================================================
// MandelbrotBasic.h 
// Variant: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotParent.h"

#include <complex>
#include <array>

class MandelbrotBasic : public MandelbrotParent
{
private:
size_t m_clientWidth;
size_t m_clientHeight;

// Das könnte nach Parent .........
std::array <std::array <struct Rectangle, MandelbrotRectangles::NUM_COLS>, MandelbrotRectangles::NUM_ROWS> m_rects;

public:
// c'tor
MandelbrotBasic();

// getter/setter
void setClientWidth(size_t clientWidth) { m_clientWidth = clientWidth; }
size_t getClientWidth() const { return m_clientWidth; }

void setClientHeight(size_t clientHeight) { m_clientHeight = clientHeight; }
size_t getClientHeight() const { return m_clientHeight; }

// public interface
void computeRects();
void paint(HDC);

// private helper methods
private:
template <typename T>
std::complex<T> getComplex(size_t x, size_t y, size_t maxWidth, size_t maxHeight) const;

template <typename T>
size_t computeSequence(std::complex<T> point) const;

};

// =====================================================================================
// End-of-File
// =====================================================================================
