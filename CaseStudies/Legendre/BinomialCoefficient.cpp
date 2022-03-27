// =====================================================================================
// BinomialCoefficient.cpp
// =====================================================================================

#include "Factorial.h"
#include "BinomialCoefficient.h"

// c'tors
BinomialCoefficient::BinomialCoefficient() 
    : m_n{ 1 }, m_k{ 1 }, m_value{ 1 } {}

BinomialCoefficient::BinomialCoefficient (size_t n, size_t k) 
    : m_n{ n }, m_k{ k }, m_value{ 0 } {}

// getter / setter
size_t BinomialCoefficient::getUpper() const
{
	return m_n;
}

size_t BinomialCoefficient::getLower() const
{
	return m_k;
}

void BinomialCoefficient::setUpper(size_t n)
{
    m_n = n;
}

void BinomialCoefficient::setLower(size_t k)
{
    m_k = k;
}

size_t BinomialCoefficient::value() const
{
	return m_value;
}

// public interface
void BinomialCoefficient::calculate ()
{
    if (m_k == 0 || m_k == m_n) {
        m_value = 1;
    }
    else {
        size_t a{ 1 }, b{ 1 };
        for (size_t i{ m_n - m_k + 1 }; i <= m_n; ++i) {
            a *= i;
        }
        for (int j{ 1 }; j <= m_k; ++j) {
            b *= j;
        }
        m_value = a / b;
    }
}

PrimeDictionary BinomialCoefficient::calculateLegendre () const
{
    Factorial facUpper{ m_n };
    PrimeDictionary dictUpper{ facUpper.factorialLegendre() };

	Factorial facLower{ m_k };
	PrimeDictionary dictLower{ facLower.factorialLegendre() };

	dictUpper.reduce(dictLower);

	Factorial facUpperMinusLower{ m_n - m_k };
	PrimeDictionary dictUpperMinusLower{ facUpperMinusLower.factorialLegendre() };

	dictUpper.reduce(dictUpperMinusLower);

	return dictUpper;
}

// output
std::ostream& operator<< (std::ostream& os, const BinomialCoefficient& coeff)
{
    os 
        << "("
        << coeff.getUpper()
        << ", "
        << coeff.getLower()
        << ")";

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
