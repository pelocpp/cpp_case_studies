// =====================================================================================
// BigPrimeNumbers.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>

#include "BigInteger.h"
#include "BigPrimeNumbers.h"

bool BigPrimeNumbers::isPrime(size_t number)
{
    // the smallest prime number is 2
    if (number == 0 or number == 1 or number == 2)
        return number == 2;

    // even numbers other than 2 are not prime
    if (number % 2 == 0)
        return false;

    // check odd divisors from 3 to the half of the number
    // (in lack of a high precision sqare root function) 
    size_t end = number / 2 + 1;
    for (long i = 3; i <= end; i += 2) {
        if (number % i == 0)
            return false;
    }

    // found prime number
    return true;
}

bool BigPrimeNumbers::isPrime(BigInteger number)
{
    // the smallest prime number is 2
    if (number <= 2_big)
        return number == 2_big;

    // even numbers other than 2 are not prime
    if (number % 2_big == 0_big)
        return false;

    // check odd divisors from 3 to the half of the number
    // (in lack of a high precision sqare root function) 
    BigInteger end = number / 2_big + 1_big;
    for (BigInteger i{ 3 }; i <= end; i += 2_big) {
        BigInteger tmp{ number % i };
        if (tmp.zero())
            return false;
    }

    // found prime number
    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
