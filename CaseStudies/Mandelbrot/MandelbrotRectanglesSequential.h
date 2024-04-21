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
    void paintRectanglesSequential(HDC hDC) const;

private:
    void paintRectangle(HDC hDC, struct Rectangle rect) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
