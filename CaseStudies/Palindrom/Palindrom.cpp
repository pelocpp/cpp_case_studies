// =====================================================================================
// Palindrom.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <tuple>
//#include <algorithm>
//#include <stdexcept>

#include "Number.h"
#include "Palindrom.h"

std::tuple<Number, Number, int> Palindrom::calcPalindrom() const
{
    auto result = std::make_tuple <Number, Number, int> (Number{}, Number{}, 0);
    return result;
}

// =====================================================================================
// End-of-File
// =====================================================================================
