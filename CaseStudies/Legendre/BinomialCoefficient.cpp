#include <iostream>
using namespace std;

#include "PrimeDictionary.h"
#include "Factorial.h"
#include "BinomialCoefficient.h"

// ctors
BinomialCoefficient::BinomialCoefficient ()
{
	m_n = 1;
	m_k = 1;
	m_value = 1;
}

BinomialCoefficient::BinomialCoefficient (long n, long k)
{
	m_n = (n >= 1) ? n : 1;
	m_k = (k >= 1) ? k : 1;
	m_value = -1;
}

// getter / setter
long BinomialCoefficient::GetUpperNumber()
{
	return m_n;
}

long BinomialCoefficient::GetLowerNumber()
{
	return m_k;
}

void BinomialCoefficient::SetUpperNumber(long n)
{
	m_n = (n >= 1) ? n : 1;
}

void BinomialCoefficient::SetLowerNumber(long k)
{
	m_k = (k >= 1) ? k : 1;
}

long BinomialCoefficient::GetValue()
{
	return m_value;
}

// public interface
void BinomialCoefficient::Calculate ()
{
    if (m_k == 0 || m_k == m_n)
    {
        m_value = 1;
    }
    else
    {
        long a = 1, b = 1;
        for (long i = m_n - m_k + 1; i <= m_n; i++)
        {
            a *= i;
        }
        for (int j = 1; j <= m_k; j++)
        {
            b *= j;
        }
        m_value = a / b;
    }
}

PrimeDictionary BinomialCoefficient::CalculateLegendre ()
{
	Factorial fUpper (m_n);
	PrimeDictionary dictUpper = fUpper.factorialLegendre();

	Factorial fLower (m_k);
	PrimeDictionary dictLower = fLower.factorialLegendre();

	dictUpper.reduce (dictLower);

	Factorial fUpperMinusLower (m_n - m_k);
	PrimeDictionary dictUpperMinusLower = fUpperMinusLower.factorialLegendre();

	dictUpper.reduce (dictUpperMinusLower);

	return dictUpper;
}
