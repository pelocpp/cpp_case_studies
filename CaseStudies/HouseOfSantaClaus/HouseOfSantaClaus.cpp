// =====================================================================================
// HouseOfSantaClaus.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <chrono>

#include "HouseOfSantaClaus.h"

bool HouseOfSantaClaus::isSolution(int number)
{
    numberToDigits(number);

    // verify range of numbers (1..5)
    if (!checkValidRangeOfDigits())
        return false;

    // exclude consecutive identical digits
    if (!checkSelfLoops())
        return false;

    // exclude edges between 1 and 5 or 2 and 5
    if (!checkValidEdges())
        return false;

    // exclude duplicate edges
    if (!checkForDuplicateEdges())
        return false;

    return true;
}

void HouseOfSantaClaus::addSolution(int number)
{
    m_solutions.push_back(number);
}

void HouseOfSantaClaus::printSolution(std::ostream& os, int number) const
{
    if (number >= 10)
    {
        int rest = number % 10;
        printSolution(os, number / 10);
        os << "->" << rest;
    }
    else
        os << number;
}

std::ostream& operator<< (std::ostream& os, const HouseOfSantaClaus& house)
{
    std::for_each(
        std::begin(house.m_solutions), 
        std::end(house.m_solutions),
        [&, newLine = false](auto number) mutable {
            house.printSolution(os, number);
            if (newLine) {
                os << std::endl;
            }
            else {
                os << "   ";
            }
            newLine = not newLine;
        }
    );

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
