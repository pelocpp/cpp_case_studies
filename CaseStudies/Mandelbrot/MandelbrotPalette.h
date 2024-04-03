// =====================================================================================
// MandelbrotPalette.h
// =====================================================================================

#pragma once

class MandelbrotPalette
{
private:
    std::vector<COLORREF> m_palette;

public:
    // c'tor
    /* constexpr */ MandelbrotPalette();

    // operators
    /* constexpr */ COLORREF operator[] (int index) const;

private:
    /* constexpr */ void init();
};

// =====================================================================================
// End-of-File
// =====================================================================================