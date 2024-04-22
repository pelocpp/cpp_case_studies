// =====================================================================================
// MandelbrotBasic.h
// Variant: Basic Version
// =====================================================================================

#pragma once

#include "MandelbrotBase.h"

class MandelbrotBasic : public MandelbrotBase
{
public:
    // c'tor
    MandelbrotBasic();

    // public interface
    void paint(HDC);

private:
    virtual void drawPixel(HDC hdc, int x, int y, COLORREF color) const override;

};

// =====================================================================================
// End-of-File
// =====================================================================================
