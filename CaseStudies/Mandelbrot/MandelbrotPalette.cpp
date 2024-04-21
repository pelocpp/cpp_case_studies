// =====================================================================================
// MandelbrotPalette.cpp
// =====================================================================================

#include <stdexcept>

#include "framework.h"

#include "MandelbrotPalette.h"
#include "MandelbrotGeneral.h"

// =====================================================================================

MandelbrotPalette::MandelbrotPalette() {
   init();
}

void MandelbrotPalette::init()
{
    m_palette.reserve(NumColors);

    for (unsigned int x = 0; x < NumColors / 32; ++x) {
        m_palette.push_back(RGB(x * 32 * 255 / NumColors, 0, 0));
    }

    for (unsigned int x = 0; x < NumColors / 32; ++x) {
        m_palette.push_back(RGB(255, x * 32 * 255 / NumColors, 0));
    }

    for (unsigned int x = 0; x < NumColors / 16; ++x) {
        m_palette.push_back(RGB(((NumColors / 16 - x) * 16) * 255 / NumColors, 255, 0));
    }

    for (unsigned int x = 0; x < NumColors / 16; ++x) {
        m_palette.push_back(RGB(0, ((NumColors / 16 - x) * 16) * 255 / NumColors, x * 16 * 255 / NumColors));
    }

    for (unsigned int x = 0; x < NumColors / 16; ++x) {
        m_palette.push_back(RGB(x * 16 * 255 / NumColors, 0, 255));
    }

    for (unsigned int x = 0; x < NumColors / 4; ++x) {
        m_palette.push_back(RGB(((NumColors / 4 - x) * 4) * 255 / NumColors, x * 4 * 255 / NumColors, 255));
    }

    for (unsigned int x = 0; x < NumColors / 2; ++x) {
        m_palette.push_back(RGB(x * 2 * 255 / NumColors, 255, 255));
    }

    m_palette[NumColors - 1] = RGB(0, 0, 0);  // last color is black
}

COLORREF MandelbrotPalette::operator[] (size_t index) const {

    if (index >= NumColors) {
        throw std::out_of_range("illegal palette index");
    }

    return m_palette[index];
}


// =====================================================================================
// MandelbrotPaletteEx
// =====================================================================================


//constexpr MandelbrotPaletteEx::MandelbrotPaletteEx() {
//}

COLORREF MandelbrotPaletteEx::operator[] (size_t index) const {

    //if (index >= NumColors) {
    //    throw std::out_of_range("illegal palette index");
    //}

    return m_palette[index];
}


// =====================================================================================
// End-of-File
// =====================================================================================

//
///* constexpr */ MandelbrotPalette::MandelbrotPalette() {
//    init();
//}
//
///* constexpr */ void MandelbrotPalette::init()
//{
//    m_palette.reserve(NumColors);
//
//    for (unsigned int x = 0; x < NumColors / 32; ++x) {
//        m_palette.push_back(RGB(x * 32 * 255 / NumColors, 0, 0));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 32; ++x) {
//        m_palette.push_back(RGB(255, x * 32 * 255 / NumColors, 0));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 16; ++x) {
//        m_palette.push_back(RGB(((NumColors / 16 - x) * 16) * 255 / NumColors, 255, 0));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 16; ++x) {
//        m_palette.push_back(RGB(0, ((NumColors / 16 - x) * 16) * 255 / NumColors, x * 16 * 255 / NumColors));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 16; ++x) {
//        m_palette.push_back(RGB(x * 16 * 255 / NumColors, 0, 255));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 4; ++x) {
//        m_palette.push_back(RGB(((NumColors / 4 - x) * 4) * 255 / NumColors, x * 4 * 255 / NumColors, 255));
//    }
//
//    for (unsigned int x = 0; x < NumColors / 2; ++x) {
//        m_palette.push_back(RGB(x * 2 * 255 / NumColors, 255, 255));
//    }
//
//    m_palette[NumColors - 1] = RGB(0, 0, 0);  // last color is black
//}
//
///* constexpr */ COLORREF MandelbrotPalette::operator[] (int index) const {
//
//    if (index >= NumColors) {
//        throw std::out_of_range("illegal palette index");
//    }
//
//    return m_palette[index];
//}
