// =====================================================================================
// BigPrimeNumbers.h
// =====================================================================================

#pragma once

class BigPrimeNumbers
{
public:
    static bool isPrime(size_t);
    static bool isPrime(const BigInteger&);

    static std::pair<size_t, size_t> hasPrimeFactor(size_t);
    static std::pair<BigInteger, BigInteger> hasPrimeFactor(const BigInteger&);

    static std::vector<size_t> getPrimeFactors(size_t);
    static std::vector<BigInteger> getPrimeFactors(BigInteger);
};

// =====================================================================================
// End-of-File
// =====================================================================================
