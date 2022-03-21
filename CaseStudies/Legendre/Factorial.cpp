// =====================================================================================
// Factorial.cpp
// =====================================================================================

#include <iostream>

#include "Factorial.h"
#include "PrimeDictionary.h"


Factorial::Factorial() : m_n{ 1 }, m_value{ 1 } {}

// size_t KANN NICHT -1 sein 
Factorial::Factorial(size_t n) : m_n{ (n >= 1) ? n : 1 }, m_value{ } {}


// getter / setter
size_t Factorial::getNumber() const
{
    return m_n;
}

void Factorial::setNumber(size_t n)
{
    m_n = (n >= 1) ? n : 1;
}

size_t Factorial::getValue() const
{
    return m_value;
}

// public interface
void Factorial::factorialIterative()
{
    if (m_n <= 1)
        m_value = 1;

    m_value = 1;
    for (int i = 2; i <= m_n; i++)
        m_value *= i;
}

void Factorial::factorialRecursive()
{
    m_value = factorialRecursive(m_n);
}

PrimeDictionary Factorial::factorialLegendre()
{
    // calculate number of primes in base number
    size_t count{ 1 };
    size_t tmp{ 3 };

    while (tmp <= m_n)
    {
        if (isPrime(tmp))
            count++;
        tmp++;
    }

    // allocate dictionary with appropriate size on the stack
    PrimeDictionary result{};

    // now apply algorithm of Legendre
    size_t prime{ 2 };
    while (prime <= m_n)
    {
        if (isPrime(prime))
        {
            size_t quo = m_n / prime;
            size_t exp = 0;

            while (quo != 0)
            {
                exp += quo;
                quo /= prime;
            }

            result.insert(prime, exp);
        }
        prime++;
    }

    return result;
}

// private helpers
size_t Factorial::factorialRecursive(size_t n)
{
    if (n <= 1)
        return 1;
    else
        return n * factorialRecursive(n - 1);
}

//bool Factorial::IsPrime(long n)
//{
//    if (n <= 1)
//        return false;
//
//    for (long i = 2; i * i <= n; i++)
//    {
//        if (n % i == 0)
//            return false;
//    }
//
//    return true;
//}

bool Factorial::isPrime(size_t number)
{
    // the smallest prime number is 2
    if (number <= 2) {
        return number == 2;
    }

    // even numbers other than 2 are not prime
    if (number % 2 == 0) {
        return false;
    }

    // check odd divisors from 3 to the square root of the number
    size_t end{ static_cast<size_t>(std::ceil(std::sqrt(number))) };
    for (size_t i{ 3 }; i <= end; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    // found prime number
    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
