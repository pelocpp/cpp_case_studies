// =====================================================================================
// HouseOfSantaClausRanges.cpp
// =====================================================================================

#include <iostream>
#include <array>
#include <ranges>
#include <vector>
#include <algorithm>

#include "HouseOfSantaClaus.h"
#include "HouseOfSantaClausRanges.h"

void HouseOfSantaClausRanges::solve()
{
    auto range = std::views::iota(Min, Max + 1);
    std::ranges::for_each(range, [this] (int n) {
        if (isSolution(n)) {
            addSolution(n);
        }
    });
}

void HouseOfSantaClausRanges::numberToDigits(int number)
{
    std::generate(
        std::rbegin(m_digits), 
        std::rend(m_digits),
        [=]() mutable {
            int digit = number % 10;
            number /= 10;
            return digit;
        }
    );
}

bool HouseOfSantaClausRanges::checkValidRangeOfDigits()
{
    auto it = std::ranges::find_if(m_digits, [](int digit) { 
        return digit == 0 || digit > 5; }
    );
    return it == std::end(m_digits);
}

bool HouseOfSantaClausRanges::checkSelfLoops()
{
    auto it = std::adjacent_find(std::begin(m_digits), std::end(m_digits));
    return it == std::end(m_digits);
}

bool HouseOfSantaClausRanges::checkValidEdges()
{
    auto it = std::adjacent_find(
        std::begin(m_digits), 
        std::end(m_digits), 
        [](int a, int b) {
            if ((a == 1 and b == 5) or (a == 5 and b == 1) or
                (a == 2 and b == 5) or (a == 5 and b == 2)) {
                return true;
            }
            else
                return false;  
        }
    );
    return it == std::end(m_digits);
}

bool HouseOfSantaClausRanges::checkForDuplicateEdges()
{
    std::vector<std::pair<int, int>> edges;

    // prevent warning 'discarding return value
    // of function with 'nodiscard' attribute'
    static_cast<void>(
        std::adjacent_find(
            std::begin(m_digits),
            std::end(m_digits),
            [&](int a, int b) {
                edges.push_back((a < b) 
                    ? std::pair{ a, b }
                    : std::pair{ b, a }
                );
                return false;
            }
        )
    );

    auto start = std::begin(edges);
    bool result = std::all_of(
        std::begin(edges),
        std::end(edges),
        [&](const auto& pair) {
            ++start;
            auto it = std::find(start, std::end(edges), pair);
            return (it == std::end(edges));
        }
    );

    return result;
}

// =====================================================================================
// End-of-File
// =====================================================================================
