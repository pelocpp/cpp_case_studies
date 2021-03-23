// =====================================================================================
// BigFaculty.cpp
// =====================================================================================

#include <iostream>
#include <string_view>
#include <vector>

#include "BigInteger.h"
#include "BigFaculty.h"

size_t BigFaculty::faculty(int n)
{
    if (n == 1)
        return 1;
    else
        return n * faculty(n - 1);
}

BigInteger BigFaculty::faculty(BigInteger n)
{
    if (n == BigInteger{ 1 })
        return BigInteger{ 1 };
    else
        return n * faculty(n - BigInteger{ 1 });
}

// =====================================================================================
// End-of-File
// =====================================================================================
