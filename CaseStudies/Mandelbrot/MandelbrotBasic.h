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
};

// =====================================================================================
// End-of-File
// =====================================================================================
