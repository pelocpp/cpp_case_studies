// =====================================================================================
// GrayCodeCalculator.cpp
// =====================================================================================

#include <iostream>
#include <list>
#include <algorithm> 

#include "GrayCodeCalculator.h"

std::list<std::list<bool>> GrayCodeCalculator::calculate(size_t length)
{
    if (length == 1) {
        return calculateRankOne();
    }
    else {
        std::list<std::list<bool>> tmp{ calculate(length - 1) };

        // need a new Gray Code list
        std::list<std::list<bool>> result;

        // copy old entries and extend them with 'false'
        std::for_each(
            std::begin(tmp),
            std::end(tmp),
            [&](const std::list<bool>& v) {
                std::list<bool> ex{ v };
                ex.push_front(false);
                result.push_back(ex);
            }
        );

        // mirror old entries and extend them with 'true'
        std::for_each(
            std::rbegin(tmp),
            std::rend(tmp),
            [&](const std::list<bool>& v) {
                std::list<bool> ex{ v };
                ex.push_front(true);
                result.push_back(ex);
            }
        );

        return result;
    }
}

std::list<std::list<bool>> GrayCodeCalculator::calculateRankOne()
{
    return { { false } , { true } };
}

void GrayCodeCalculator::print(std::list<std::list<bool>> result)
{
    for (std::list<bool> code : result) {
        for (bool bit : code) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
