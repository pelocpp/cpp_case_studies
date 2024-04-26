// =====================================================================================
// MandelbrotRectanglesSequential.h
// Variant 02: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

class MandelbrotRectanglesSequential : public MandelbrotBase
{
public:
    // c'tor(s)
    MandelbrotRectanglesSequential();

public:
    // public interface
    void paintRectangles(HDC hDC) const;

private:
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;
};

// =====================================================================================
// End-of-File
// =====================================================================================
