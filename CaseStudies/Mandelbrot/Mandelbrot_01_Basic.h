// =====================================================================================
// Mandelbrot_01_Basic.h
// Variant 01: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

#include <cstddef>    // std::size_t

class MandelbrotBasic : public MandelbrotBase
{
public:
    // c'tor
    MandelbrotBasic();

private:
    virtual void drawPixel(HDC, std::size_t, std::size_t, COLORREF) const override;

};

// =====================================================================================
// End-of-File
// =====================================================================================
