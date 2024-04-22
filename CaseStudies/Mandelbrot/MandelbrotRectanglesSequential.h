// =====================================================================================
// MandelbrotRectanglesSequential.h
// Variant: Basic Version
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
    void paintRectanglesSequential(HDC hDC) const;

private:
    void paintRectangle(HDC hDC, struct Rectangle rect) const;

private:
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;

};

// =====================================================================================
// End-of-File
// =====================================================================================
