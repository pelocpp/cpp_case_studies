// =====================================================================================
// PalindromCalculator.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <tuple>
#include <optional>

#include "Number.h"
#include "PalindromCalculator.h"

constexpr bool Verbose = false;

std::tuple<std::optional<Number>, Number, size_t>
PalindromCalculator::calcPalindrom(const Number& start, size_t steps)
{
    Number n{ start };
    for (size_t i{}; i != steps; i++) {

        if constexpr (Verbose) {
            std::cout << "Number:  " << n << std::endl;
        }

        if (n.symmetric()) {
            return { n, start, i };
        }

        Number m{ n.reverse() };
        n = n.add(m);

        if constexpr (Verbose) {
            std::cout << "Inverse: " << m << std::endl;
        }
    }

    return { std::nullopt, start, steps };
}

std::tuple<size_t, size_t, size_t>
PalindromCalculator::forthEulerProblem()
{
    size_t i{ 1 }, j{ 1 };
    size_t candidate{ 1 };

    for (size_t n{ 111 }; n != 999; ++n)
    {
        for (size_t m{ 111 }; m != 999; ++m)
        {
            if (n < m)
            {
                size_t prod{ n * m };
                std::string s{ std::to_string(prod) };
                Number num{ s };

                if (num.symmetric() and prod > candidate)
                {
                    i = n;
                    j = m;
                    candidate = i * j;
                }
            }
        }
    }

    return { candidate, i, j };
}

// =====================================================================================
// End-of-File
// =====================================================================================
