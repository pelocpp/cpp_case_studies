// =====================================================================================
// HouseOfSantaClausIterative.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <array>
#include <chrono>

#include "HouseOfSantaClaus.h"
#include "HouseOfSantaClausIterative.h"

void HouseOfSantaClausIterative::solve ()
{
    for (int n = Min; n <= Max; n++) {
        if (isSolution(n)) {
            addSolution(n);
        }
    }
}

void HouseOfSantaClausIterative::numberToDigits(int number)
{
    for (int i = 8; i >= 0; i--) {
        m_digits[i] = number % 10;
        number /= 10;
    }
}

bool HouseOfSantaClausIterative::checkValidRangeOfDigits()
{
    for (int i = 0; i < 9; i++) {
        if (m_digits[i] == 0 || m_digits[i] > 5)
            return false;
    }
    return true;
}

bool HouseOfSantaClausIterative::checkSelfLoops()
{
    for (size_t i = 1; i != 9; i++) {
        if (m_digits[i - 1] == m_digits[i])
            return false;
    }
    return true;
}

bool HouseOfSantaClausIterative::checkValidEdges()
{
    for (size_t i = 1; i != 9; i++) {

        int a = m_digits[i];
        int b = m_digits[i - 1];

        if ((a == 1 and b == 5) or (a == 5 and b == 1) or
            (a == 2 and b == 5) or (a == 5 and b == 2)) {
            return false;
        }
    }

    return true;
}

bool HouseOfSantaClausIterative::checkForDuplicateEdges()
{
    for (size_t i = 1; i != 9; i++) {

        int edge1 = m_digits[i - 1] * 10 + m_digits[i];
        int edge2 = m_digits[i] * 10 + m_digits[i - 1];

        for (size_t j = i; j != 8; j++) {
            int edge = m_digits[j] * 10 + m_digits[j + 1];
            if (edge == edge1 || edge == edge2)
                return false;
        }
    }

    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
