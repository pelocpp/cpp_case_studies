// =====================================================================================
// BigPrimeNumbers.h
// =====================================================================================

#pragma once

class BigPrimeNumbers
{
public:
   static bool isPrime(size_t);
   static bool isPrime(BigInteger);

   static std::pair<size_t, size_t>  factorize(size_t);
   static std::pair<BigInteger, BigInteger>  factorize(BigInteger);
};

// =====================================================================================
// End-of-File
// =====================================================================================
