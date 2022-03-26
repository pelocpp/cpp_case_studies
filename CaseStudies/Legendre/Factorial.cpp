// =====================================================================================
// Factorial.cpp
// =====================================================================================

#include "Factorial.h"

// c'tors
Factorial::Factorial() : m_n{ 1 }, m_value{ 1 } {}

Factorial::Factorial(size_t n) : m_n{ n }, m_value{ } {}

// getter / setter
size_t Factorial::get() const
{
    return m_n;
}

void Factorial::set(size_t n)
{
    m_n = n;
}

size_t Factorial::value() const
{
    return m_value;
}

// public interface
void Factorial::factorialIterative()
{
    m_value = 1;

    if (m_n <= 1) {
        return;
    }
    else {
        for (int i{ 2 }; i <= m_n; ++i)
            m_value *= i;
    }
}

void Factorial::factorialRecursive()
{
    m_value = factorialRecursive(m_n);
}

PrimeDictionary Factorial::factorialLegendre()
{
    // algorithm of Legendre
    PrimeDictionary result{};
    size_t prime{ 2 };
    while (prime <= m_n) {

        if (size_t quo, exp; isPrime(prime)) {
            quo = m_n / prime;
            exp = 0;

            while (quo != 0) {
                exp += quo;
                quo /= prime;
            }

            result.set(prime, exp);
        }

        prime++;
    }

    return result;
}

// private helpers
size_t Factorial::factorialRecursive(size_t n)
{
    return (n <= 1) ? 1 : n * factorialRecursive(n - 1);
}

bool Factorial::isPrime(size_t number)
{
    // the smallest prime number is 2
    if (number <= 2) {
        return number == 2;
    }

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

    return true;
}

// =====================================================================================
// End-of-File
// =====================================================================================
