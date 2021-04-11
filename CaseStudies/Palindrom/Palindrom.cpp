// =====================================================================================
// Palindrom.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <tuple>
#include <optional>
//#include <algorithm>
//#include <stdexcept>

#include "Number.h"
#include "Palindrom.h"

std::tuple<std::optional<Number>, Number, size_t>
Palindrom::calcPalindrom(const Number& start, size_t steps)
{
    Number n{ start };
    for (size_t i{}; i != steps; i++) {

        if (n.symmetric()) {
            return std::make_tuple(n, start, i + 1);
        }

        Number m{ n.reverse() };
        n = n + m;
    }

    return std::make_tuple(std::nullopt, start, steps);
}

// =====================================================================================
// End-of-File
// =====================================================================================
