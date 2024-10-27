// =====================================================================================
// Mandelbrot_01_Basic.h
// Variant 01: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

class MandelbrotBasic : public MandelbrotBase
{
public:
    // c'tor
    MandelbrotBasic();

private:
    virtual void drawPixel(HDC, size_t, size_t, COLORREF) const override;

};

// =====================================================================================
// End-of-File
// =====================================================================================
