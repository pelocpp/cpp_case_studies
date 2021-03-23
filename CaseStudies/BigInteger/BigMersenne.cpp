// =====================================================================================
// BigMersenne.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>

#include "BigInteger.h"
#include "BigMersenne.h"

BigInteger BigMersenne::number(int pow)
{
    BigInteger mersenne{ 2 };
    mersenne = mersenne.pow(pow);
    mersenne = mersenne - BigInteger{ 1 };
    return mersenne;
}

// =====================================================================================
// End-of-File
// =====================================================================================
