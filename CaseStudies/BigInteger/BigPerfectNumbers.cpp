// =====================================================================================
// BigPerfectNumbers.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>

#include "BigInteger.h"
#include "BigPerfectNumbers.h"

bool BigPerfectNumbers::isPerfect(size_t n)
{
    int sumOfDivisors{ 1 };

    for (int i = 2; i < n / 2 + 1; i = i + 1)
    {
        if (n % i == 0)
        {
            sumOfDivisors = sumOfDivisors + i;
        }
    }

    return (n == sumOfDivisors) ? true : false;
}

bool BigPerfectNumbers::isPerfect(const BigInteger& n)
{
    BigInteger sumOfDivisors{ 1 };
    BigInteger limit{ n / 2_big + 1_big };

    for (BigInteger i{ 2 }; i != limit; ++i)
    {
        if (n % i == 0_big)
        {
            sumOfDivisors = sumOfDivisors + i;
        }
    }

    return (n == sumOfDivisors) ? true : false;
}

// =====================================================================================
// End-of-File
// =====================================================================================
