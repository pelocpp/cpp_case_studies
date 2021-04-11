// =====================================================================================
// PalindromCalculator.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <string_view>
#include <tuple>
#include <optional>

#include "Number.h"
#include "PalindromCalculator.h"

constexpr bool Verbose = true;

std::tuple<std::optional<Number>, Number, size_t>
PalindromCalculator::calcPalindrom(const Number& start, size_t steps)
{
    Number n{ start };
    for (size_t i{}; i != steps; i++) {

        if constexpr (Verbose) {
            std::cout << "Number:  " << n << std::endl;
        }

        if (n.symmetric()) {
            return std::make_tuple(n, start, i + 1);
        }

        Number m{ n.reverse() };
        n = n + m;

        if constexpr (Verbose) {
            std::cout << "Inverse: " << m << std::endl;
        }
    }

    return std::make_tuple(std::nullopt, start, steps);
}

// =====================================================================================
// End-of-File
// =====================================================================================
