// =====================================================================================
// MandelbrotPalette.h
// =====================================================================================

#pragma once

#include <vector>
#include <array>

//class MandelbrotPalette
//{
//private:
//    std::vector<COLORREF> m_palette;
//
//public:
//    // c'tor
//    /* constexpr */ MandelbrotPalette();
//
//    // operators
//    /* constexpr */ COLORREF operator[] (int index) const;
//
//private:
//    /* constexpr */ void init();
//};

class MandelbrotPalette
{
public:
    static const int NumColors{ 256 };
    static const int Limit{ 5 };

private:
    std::vector<COLORREF> m_palette;

public:
    // c'tor
    MandelbrotPalette();

    // operators
    COLORREF operator[] (size_t index) const;

//private:
public:
    void init();
};

// =====================================================================================



class MandelbrotPaletteEx
{
private:
    std::array<COLORREF, 100> m_palette = {};

public:
    // c'tor
    constexpr MandelbrotPaletteEx() {};

    // operators
    COLORREF operator[] (size_t index) const;

    //private:
public:

};


// =====================================================================================
// End-of-File
// =====================================================================================
