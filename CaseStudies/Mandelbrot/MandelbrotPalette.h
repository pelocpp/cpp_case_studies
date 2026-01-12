// =====================================================================================
// MandelbrotPalette.h
// =====================================================================================

#pragma once

#include "framework.h"

#include <array>
#include <complex>
#include <vector>
#include <cmath>


// =====================================================================================

class MandelbrotPalette
{
public:
    static const int NumColors{ 256 };
    static const int Limit{ 4 };

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

    template <typename T>
    size_t computeSequence(std::complex<T> point) const
    {
        std::complex<T> number{};
        std::size_t count{};

        while (count != NumColors && static_cast<T>(std::abs(number)) < Limit) {
            number = number * number + point;
            ++count;
        }

        return count;
    }
};

// =====================================================================================

class MandelbrotPalette100
{
public:

    static const int NumColors{ 100 };
    static const int Limit{ 4 };

    //static const int NumColors{ 200 };
    //static const int Limit{ 5 };

private:

    //std::array<COLORREF, NumColors> m_palette =
    //{
    //    RGB(255, 0, 0),
    //    RGB(255, 8, 0),
    //    RGB(255, 15, 0),
    //    RGB(255, 23, 0),
    //    RGB(255, 31, 0),
    //    RGB(255, 38, 0),
    //    RGB(255, 46, 0),
    //    RGB(255, 54, 0),
    //    RGB(255, 61, 0),
    //    RGB(255, 69, 0),
    //    RGB(255, 77, 0),
    //    RGB(255, 84, 0),
    //    RGB(255, 92, 0),
    //    RGB(255, 99, 0),
    //    RGB(255, 107, 0),
    //    RGB(255, 115, 0),
    //    RGB(255, 122, 0),
    //    RGB(255, 130, 0),
    //    RGB(255, 138, 0),
    //    RGB(255, 145, 0),
    //    RGB(255, 153, 0),
    //    RGB(255, 161, 0),
    //    RGB(255, 168, 0),
    //    RGB(255, 176, 0),
    //    RGB(255, 184, 0),
    //    RGB(255, 191, 0),
    //    RGB(255, 199, 0),
    //    RGB(255, 207, 0),
    //    RGB(255, 214, 0),
    //    RGB(255, 222, 0),
    //    RGB(255, 230, 0),
    //    RGB(255, 237, 0),
    //    RGB(255, 245, 0),
    //    RGB(255, 252, 0),
    //    RGB(250, 255, 0),
    //    RGB(242, 255, 0),
    //    RGB(235, 255, 0),
    //    RGB(227, 255, 0),
    //    RGB(219, 255, 0),
    //    RGB(212, 255, 0),
    //    RGB(204, 255, 0),
    //    RGB(196, 255, 0),
    //    RGB(189, 255, 0),
    //    RGB(181, 255, 0),
    //    RGB(173, 255, 0),
    //    RGB(166, 255, 0),
    //    RGB(158, 255, 0),
    //    RGB(150, 255, 0),
    //    RGB(143, 255, 0),
    //    RGB(135, 255, 0),
    //    RGB(128, 255, 0),
    //    RGB(120, 255, 0),
    //    RGB(112, 255, 0),
    //    RGB(105, 255, 0),
    //    RGB(97, 255, 0),
    //    RGB(89, 255, 0),
    //    RGB(82, 255, 0),
    //    RGB(74, 255, 0),
    //    RGB(66, 255, 0),
    //    RGB(59, 255, 0),
    //    RGB(51, 255, 0),
    //    RGB(43, 255, 0),
    //    RGB(36, 255, 0),
    //    RGB(28, 255, 0),
    //    RGB(20, 255, 0),
    //    RGB(13, 255, 0),
    //    RGB(5, 255, 0),
    //    RGB(0, 255, 3),
    //    RGB(0, 255, 10),
    //    RGB(0, 255, 18),
    //    RGB(0, 255, 25),
    //    RGB(0, 255, 33),
    //    RGB(0, 255, 41),
    //    RGB(0, 255, 48),
    //    RGB(0, 255, 56),
    //    RGB(0, 255, 64),
    //    RGB(0, 255, 71),
    //    RGB(0, 255, 79),
    //    RGB(0, 255, 87),
    //    RGB(0, 255, 94),
    //    RGB(0, 255, 102),
    //    RGB(0, 255, 110),
    //    RGB(0, 255, 117),
    //    RGB(0, 255, 125),
    //    RGB(0, 255, 133),
    //    RGB(0, 255, 140),
    //    RGB(0, 255, 148),
    //    RGB(0, 255, 156),
    //    RGB(0, 255, 163),
    //    RGB(0, 255, 171),
    //    RGB(0, 255, 178),
    //    RGB(0, 255, 186),
    //    RGB(0, 255, 194),
    //    RGB(0, 255, 201),
    //    RGB(0, 255, 209),
    //    RGB(0, 255, 217),
    //    RGB(0, 255, 224),
    //    RGB(0, 255, 232),
    //    RGB(0, 255, 240),
    //    RGB(0, 255, 247),
    //    RGB(0, 255, 255),
    //    RGB(0, 247, 255),
    //    RGB(0, 240, 255),
    //    RGB(0, 232, 255),
    //    RGB(0, 224, 255),
    //    RGB(0, 217, 255),
    //    RGB(0, 209, 255),
    //    RGB(0, 201, 255),
    //    RGB(0, 194, 255),
    //    RGB(0, 186, 255),
    //    RGB(0, 178, 255),
    //    RGB(0, 171, 255),
    //    RGB(0, 163, 255),
    //    RGB(0, 156, 255),
    //    RGB(0, 148, 255),
    //    RGB(0, 140, 255),
    //    RGB(0, 133, 255),
    //    RGB(0, 125, 255),
    //    RGB(0, 117, 255),
    //    RGB(0, 110, 255),
    //    RGB(0, 102, 255),
    //    RGB(0, 94, 255),
    //    RGB(0, 87, 255),
    //    RGB(0, 79, 255),
    //    RGB(0, 71, 255),
    //    RGB(0, 64, 255),
    //    RGB(0, 56, 255),
    //    RGB(0, 48, 255),
    //    RGB(0, 41, 255),
    //    RGB(0, 33, 255),
    //    RGB(0, 26, 255),
    //    RGB(0, 18, 255),
    //    RGB(0, 10, 255),
    //    RGB(0, 3, 255),
    //    RGB(5, 0, 255),
    //    RGB(13, 0, 255),
    //    RGB(20, 0, 255),
    //    RGB(28, 0, 255),
    //    RGB(36, 0, 255),
    //    RGB(43, 0, 255),
    //    RGB(51, 0, 255),
    //    RGB(59, 0, 255),
    //    RGB(66, 0, 255),
    //    RGB(74, 0, 255),
    //    RGB(82, 0, 255),
    //    RGB(89, 0, 255),
    //    RGB(97, 0, 255),
    //    RGB(105, 0, 255),
    //    RGB(112, 0, 255),
    //    RGB(120, 0, 255),
    //    RGB(128, 0, 255),
    //    RGB(135, 0, 255),
    //    RGB(143, 0, 255),
    //    RGB(150, 0, 255),
    //    RGB(158, 0, 255),
    //    RGB(166, 0, 255),
    //    RGB(173, 0, 255),
    //    RGB(181, 0, 255),
    //    RGB(189, 0, 255),
    //    RGB(196, 0, 255),
    //    RGB(204, 0, 255),
    //    RGB(212, 0, 255),
    //    RGB(219, 0, 255),
    //    RGB(227, 0, 255),
    //    RGB(235, 0, 255),
    //    RGB(242, 0, 255),
    //    RGB(250, 0, 255),
    //    RGB(255, 0, 252),
    //    RGB(255, 0, 245),
    //    RGB(255, 0, 237),
    //    RGB(255, 0, 229),
    //    RGB(255, 0, 222),
    //    RGB(255, 0, 214),
    //    RGB(255, 0, 207),
    //    RGB(255, 0, 199),
    //    RGB(255, 0, 191),
    //    RGB(255, 0, 184),
    //    RGB(255, 0, 176),
    //    RGB(255, 0, 168),
    //    RGB(255, 0, 161),
    //    RGB(255, 0, 153),
    //    RGB(255, 0, 145),
    //    RGB(255, 0, 138),
    //    RGB(255, 0, 130),
    //    RGB(255, 0, 122),
    //    RGB(255, 0, 115),
    //    RGB(255, 0, 107),
    //    RGB(255, 0, 99),
    //    RGB(255, 0, 92),
    //    RGB(255, 0, 84),
    //    RGB(255, 0, 77),
    //    RGB(255, 0, 69),
    //    RGB(255, 0, 61),
    //    RGB(255, 0, 54),
    //    RGB(255, 0, 46),
    //    RGB(255, 0, 38),
    //    RGB(255, 0, 31),
    //    RGB(255, 0, 23),
    //    RGB(255, 0, 15),
    //    RGB(255, 0, 8)
    //};

    std::array<COLORREF, NumColors> m_palette;


    //std::array<COLORREF, NumColors> m_palette =
    //{
    //    RGB(255, 0, 0),
    //    RGB(255, 15, 0),
    //    RGB(255, 31, 0),
    //    RGB(255, 46, 0),
    //    RGB(255, 61, 0),
    //    RGB(255, 77, 0),
    //    RGB(255, 92, 0),
    //    RGB(255, 107, 0),
    //    RGB(255, 122, 0),
    //    RGB(255, 138, 0),
    //    RGB(255, 153, 0),
    //    RGB(255, 168, 0),
    //    RGB(255, 184, 0),
    //    RGB(255, 199, 0),
    //    RGB(255, 214, 0),
    //    RGB(255, 230, 0),
    //    RGB(255, 245, 0),
    //    RGB(250, 255, 0),
    //    RGB(235, 255, 0),
    //    RGB(219, 255, 0),
    //    RGB(204, 255, 0),
    //    RGB(189, 255, 0),
    //    RGB(173, 255, 0),
    //    RGB(158, 255, 0),
    //    RGB(143, 255, 0),
    //    RGB(128, 255, 0),
    //    RGB(112, 255, 0),
    //    RGB(97, 255, 0),
    //    RGB(82, 255, 0),
    //    RGB(66, 255, 0),
    //    RGB(51, 255, 0),
    //    RGB(36, 255, 0),
    //    RGB(20, 255, 0),
    //    RGB(5, 255, 0),
    //    RGB(0, 255, 10),
    //    RGB(0, 255, 25),
    //    RGB(0, 255, 41),
    //    RGB(0, 255, 56),
    //    RGB(0, 255, 71),
    //    RGB(0, 255, 87),
    //    RGB(0, 255, 102),
    //    RGB(0, 255, 117),
    //    RGB(0, 255, 133),
    //    RGB(0, 255, 148),
    //    RGB(0, 255, 163),
    //    RGB(0, 255, 178),
    //    RGB(0, 255, 194),
    //    RGB(0, 255, 209),
    //    RGB(0, 255, 224),
    //    RGB(0, 255, 240),
    //    RGB(0, 255, 255),
    //    RGB(0, 240, 255),
    //    RGB(0, 224, 255),
    //    RGB(0, 209, 255),
    //    RGB(0, 194, 255),
    //    RGB(0, 178, 255),
    //    RGB(0, 163, 255),
    //    RGB(0, 148, 255),
    //    RGB(0, 133, 255),
    //    RGB(0, 117, 255),
    //    RGB(0, 102, 255),
    //    RGB(0, 87, 255),
    //    RGB(0, 71, 255),
    //    RGB(0, 56, 255),
    //    RGB(0, 41, 255),
    //    RGB(0, 26, 255),
    //    RGB(0, 10, 255),
    //    RGB(5, 0, 255),
    //    RGB(20, 0, 255),
    //    RGB(36, 0, 255),
    //    RGB(51, 0, 255),
    //    RGB(66, 0, 255),
    //    RGB(82, 0, 255),
    //    RGB(97, 0, 255),
    //    RGB(112, 0, 255),
    //    RGB(128, 0, 255),
    //    RGB(143, 0, 255),
    //    RGB(158, 0, 255),
    //    RGB(173, 0, 255),
    //    RGB(189, 0, 255),
    //    RGB(204, 0, 255),
    //    RGB(219, 0, 255),
    //    RGB(235, 0, 255),
    //    RGB(250, 0, 255),
    //    RGB(255, 0, 245),
    //    RGB(255, 0, 229),
    //    RGB(255, 0, 214),
    //    RGB(255, 0, 199),
    //    RGB(255, 0, 184),
    //    RGB(255, 0, 168),
    //    RGB(255, 0, 153),
    //    RGB(255, 0, 138),
    //    RGB(255, 0, 122),
    //    RGB(255, 0, 107),
    //    RGB(255, 0, 92),
    //    RGB(255, 0, 77),
    //    RGB(255, 0, 61),
    //    RGB(255, 0, 46),
    //    RGB(255, 0, 31),
    //    RGB(255, 0, 15)
    //};

public:
    // c'tor
    constexpr MandelbrotPalette100() 
        : m_palette
    {
        RGB(255, 0, 0),
        RGB(255, 15, 0),
        RGB(255, 31, 0),
        RGB(255, 46, 0),
        RGB(255, 61, 0),
        RGB(255, 77, 0),
        RGB(255, 92, 0),
        RGB(255, 107, 0),
        RGB(255, 122, 0),
        RGB(255, 138, 0),
        RGB(255, 153, 0),
        RGB(255, 168, 0),
        RGB(255, 184, 0),
        RGB(255, 199, 0),
        RGB(255, 214, 0),
        RGB(255, 230, 0),
        RGB(255, 245, 0),
        RGB(250, 255, 0),
        RGB(235, 255, 0),
        RGB(219, 255, 0),
        RGB(204, 255, 0),
        RGB(189, 255, 0),
        RGB(173, 255, 0),
        RGB(158, 255, 0),
        RGB(143, 255, 0),
        RGB(128, 255, 0),
        RGB(112, 255, 0),
        RGB(97, 255, 0),
        RGB(82, 255, 0),
        RGB(66, 255, 0),
        RGB(51, 255, 0),
        RGB(36, 255, 0),
        RGB(20, 255, 0),
        RGB(5, 255, 0),
        RGB(0, 255, 10),
        RGB(0, 255, 25),
        RGB(0, 255, 41),
        RGB(0, 255, 56),
        RGB(0, 255, 71),
        RGB(0, 255, 87),
        RGB(0, 255, 102),
        RGB(0, 255, 117),
        RGB(0, 255, 133),
        RGB(0, 255, 148),
        RGB(0, 255, 163),
        RGB(0, 255, 178),
        RGB(0, 255, 194),
        RGB(0, 255, 209),
        RGB(0, 255, 224),
        RGB(0, 255, 240),
        RGB(0, 255, 255),
        RGB(0, 240, 255),
        RGB(0, 224, 255),
        RGB(0, 209, 255),
        RGB(0, 194, 255),
        RGB(0, 178, 255),
        RGB(0, 163, 255),
        RGB(0, 148, 255),
        RGB(0, 133, 255),
        RGB(0, 117, 255),
        RGB(0, 102, 255),
        RGB(0, 87, 255),
        RGB(0, 71, 255),
        RGB(0, 56, 255),
        RGB(0, 41, 255),
        RGB(0, 26, 255),
        RGB(0, 10, 255),
        RGB(5, 0, 255),
        RGB(20, 0, 255),
        RGB(36, 0, 255),
        RGB(51, 0, 255),
        RGB(66, 0, 255),
        RGB(82, 0, 255),
        RGB(97, 0, 255),
        RGB(112, 0, 255),
        RGB(128, 0, 255),
        RGB(143, 0, 255),
        RGB(158, 0, 255),
        RGB(173, 0, 255),
        RGB(189, 0, 255),
        RGB(204, 0, 255),
        RGB(219, 0, 255),
        RGB(235, 0, 255),
        RGB(250, 0, 255),
        RGB(255, 0, 245),
        RGB(255, 0, 229),
        RGB(255, 0, 214),
        RGB(255, 0, 199),
        RGB(255, 0, 184),
        RGB(255, 0, 168),
        RGB(255, 0, 153),
        RGB(255, 0, 138),
        RGB(255, 0, 122),
        RGB(255, 0, 107),
        RGB(255, 0, 92),
        RGB(255, 0, 77),
        RGB(255, 0, 61),
        RGB(255, 0, 46),
        RGB(255, 0, 31),
        RGB(255, 0, 15)
    } {};

    // operators
    constexpr COLORREF operator[] (size_t index) const
    {
        return m_palette[index];
    }
};

// =====================================================================================

//extern MandelbrotPalette    g_palette;
//extern MandelbrotPalette100 g_palette100;

// =====================================================================================
// End-of-File
// =====================================================================================


// 2. Versuch: Irgendwie eine constexpr Palette ..............

template <std::size_t NumColors, std::size_t Limit>
class MandelbrotPaletteEx
{
public:
    //static const int NumColors{ 256 };
    //static const int Limit{ 4 };

private:
    std::array<COLORREF, NumColors> m_palette;

public:
    // c'tor
    constexpr MandelbrotPaletteEx() = default; // falsch, nur damit es übersetzt

    // operators
    constexpr COLORREF operator[] (size_t index) const
    {
        return m_palette[index];
    }

public:
    template <typename T>
    size_t computeSequence(std::complex<T> point) const
    {
        std::complex<T> number{};
        std::size_t count{};

        while (count != NumColors && static_cast<T>(std::abs(number)) < Limit) {
            number = number * number + point;
            ++count;
        }

        return count;
    }
};

//
//MandelbrotPaletteEx::MandelbrotPaletteEx<256, 4> ()
//{
//    m_palette = {
//
//    };
//}
//
//
//
//MandelbrotPaletteEx<256, 4>  g_palette
//{
//    m_palette = {
//
//    };
//}
//
//MandelbrotPaletteEx<100, 4> g_palette100
//{
//
//}

// =====================================================================================


template <std::size_t NumColors = 256, std::size_t Limit = 4>
class MandelbrotPaletteExEx
{
public:


private:
   // std::vector<COLORREF, NumColors> m_palette;
    std::vector<COLORREF> m_palette;

public:
    // c'tor
    /*constexpr*/ MandelbrotPaletteExEx() {

        make_hsv_palette(NumColors);
    }

    // operators
    /*constexpr*/ COLORREF operator[] (size_t index) const
    {
        if (index >= NumColors) {
            throw std::out_of_range("illegal palette index");
        }

        return m_palette[index];
    }

public:
    template <typename T>
    size_t computeSequence(std::complex<T> point) const
    {
        std::complex<T> number{};
        std::size_t count{};

        while (count != NumColors && static_cast<T>(std::abs(number)) < Limit) {
            number = number * number + point;
            ++count;
        }

        return count;
    }

private:

    //struct RGB {
    //    unsigned char r, g, b;
    //};

    COLORREF hsv_to_rgb(double h, double s, double v)
    {
        double c = v * s;
        double x = c * (1.0 - std::fabs(fmod(h / 60.0, 2) - 1.0));
        double m = v - c;

        double r, g, b;

        if (h < 60) { r = c; g = x; b = 0; }
        else if (h < 120) { r = x; g = c; b = 0; }
        else if (h < 180) { r = 0; g = c; b = x; }
        else if (h < 240) { r = 0; g = x; b = c; }
        else if (h < 300) { r = x; g = 0; b = c; }
        else { r = c; g = 0; b = x; }

        return RGB(r, g, b);

        //return {
        //    (unsigned char)((r + m) * 255),
        //    (unsigned char)((g + m) * 255),
        //    (unsigned char)((b + m) * 255)
        //};
    }

    // std::vector<RGB> make_hsv_palette(int size)
    void make_hsv_palette(int size)
    {
       // std::vector<RGB> palette(size);

        m_palette.resize(size);

        for (int i = 0; i < size; ++i) {
            double t = (double)i / size;
            double hue = 360.0 * t;   // cycle through all colors
            m_palette[i] = hsv_to_rgb(hue, 1.0, 1.0);
        }
      //  return palette;
    }
};

extern MandelbrotPaletteExEx<256, 4> g_palette;