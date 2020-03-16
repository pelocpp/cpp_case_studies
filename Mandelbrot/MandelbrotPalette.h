// =====================================================================================
// End-of-File
// =====================================================================================

#pragma once

class MandelbrotPalette {
private:
    std::vector<COLORREF> m_palette;

public:
    // c'tor
    MandelbrotPalette();

    // operators
    const COLORREF operator[]  (int index) const;

private:
    void init();
};

// =====================================================================================
// End-of-File
// =====================================================================================