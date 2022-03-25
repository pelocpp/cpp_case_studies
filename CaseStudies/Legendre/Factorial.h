// =====================================================================================
// Factorial.h
// =====================================================================================

#pragma once

#include <iostream>
#include <cmath>

#include "PrimeDictionary.h"

class Factorial
{
private:
    size_t m_n;
    size_t m_value;

public:
    // c'tors
    Factorial();
    Factorial(size_t n);

    // getter / setter
    size_t getNumber() const;
    void setNumber(size_t);
    size_t getValue() const;

    // public interface
    void factorialRecursive();
    void factorialIterative();
    PrimeDictionary factorialLegendre();

private:
    // private helper
    static size_t factorialRecursive(size_t n);
    static bool isPrime(size_t);
};

// =====================================================================================
// End-of-File
// =====================================================================================
