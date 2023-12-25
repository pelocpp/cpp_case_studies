// ===========================================================================
// PythagoreanTriple.h
// ===========================================================================

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <format>

class PythagoreanTriple
{
private:
   std::array<size_t, 3> m_numbers;

public:
    PythagoreanTriple();
    PythagoreanTriple(size_t x, size_t y, size_t z);

    size_t circumference();
    std::string toString();
};

// ===========================================================================
// End-of-File
// ===========================================================================
