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

bool BigPrimeNumbers::isPrime(const BigInteger& number)
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

std::pair<size_t, size_t> BigPrimeNumbers::hasPrimeFactor(size_t number)
{
    std::pair<size_t, size_t> result{ 1 , number };

    // factorizing a long variable using a very simple approach
    for (long i{ 2 }; i != number; ++i)
    {
        if ((number % i) == 0)
        {
            result.first = i;
            result.second = number / i;
            break;
        }
    }

    return result;
}

std::pair<BigInteger, BigInteger> BigPrimeNumbers::hasPrimeFactor(const BigInteger& number)
{
    // std::pair<BigInteger, BigInteger> result{ 1_big , number };
    std::pair<BigInteger, BigInteger> result{ (BigInteger) 1 , number };

    // factorizing a big integer object using a very simple approach
    for (BigInteger i{ 2 }; i != number; ++i)
    {
        BigInteger tmp{ number % i };
        if (tmp.zero())
        {
            result.first = i;
            result.second = number / i;
            break;
        }
    }

    return result;
}

std::vector<size_t> BigPrimeNumbers::getPrimeFactors(size_t number)
{
    std::vector<size_t> factors;
    size_t factor{ 2 };

    while (number != 1)
    {
        if (number % factor == 0)
        {
            // store found factor in result vector
            factors.push_back(factor);

            // divide number through this prime factor
            number = number / factor;

            // remove same prime factor, if any
            while (number % factor == 0) {
                number = number / factor;
            }
        }

        factor++;
    }

    return factors;
}

std::vector<BigInteger> BigPrimeNumbers::getPrimeFactors(BigInteger number)
{
    std::vector<BigInteger> factors;
    BigInteger factor{ 2 };

    while (number != 1_big)
    {
        if (number % factor == 0_big)
        {
            // store found factor in result vector
            factors.push_back(factor);

            // divide number through this prime factor
            number = number / factor;

            // remove same prime factor, if any
            while (number % factor == 0_big) {
                number = number / factor;
            }
        }

        factor++;
    }

    return factors;
}

// =====================================================================================
// End-of-File
// =====================================================================================
