// =====================================================================================
// PermutationCalculatorEx.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

#include "PermutationEx.h"
#include "PermutationArrayEx.h"
#include "PermutationCalculatorEx.h"

// c'tor
PermutationCalculator::PermutationCalculator() : m_p{} {}

// getter/setter
void PermutationCalculator::setPermutation(const Permutation& p)
{
    m_p = p;
}

Permutation PermutationCalculator::getPermutation()
{
    return m_p;
}

// public interface
void PermutationCalculator::calculate()
{
    m_array = calculate(m_p);
}

PermutationArray PermutationCalculator::calculate(const Permutation& p)
{
    if (p.grade() == 1)
    {
        PermutationArray a(1);
        a.insert(p);
        return a;
    }
    else
    {
        int d1 = faculty(p.grade());
        PermutationArray result(faculty(p.grade()));

        int d2 = p.grade();
        for (int i = 0; i < p.grade(); i++)
        {
            // create permutation without i.-th element of current permutation
            Permutation q = p.removeAt(i);

            // calculate permutions of n-1 elements recursively
            PermutationArray tmp = calculate(q);

            // join result with removed character
            tmp.insertAll(p[i]);

            // append calculated permutations
            for (int m = 0; m < tmp.count(); m++)
                result.insert(tmp[m]);
        }

        return result;
    }
}

int PermutationCalculator::faculty(int n) const
{
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;

    return result;
}

// enumerator interface
//void PermutationCalculator::Reset()
//{
//    m_index = -1;
//}
//
//bool PermutationCalculator::MoveNext()
//{
//    m_index++;
//    if (m_index < m_array.Size())
//    {
//        return true;
//    }
//    else
//    {
//        Reset();
//        return false;
//    }
//}
//
//Permutation PermutationCalculator::Current()
//{
//    return m_array[m_index];
//}

// =====================================================================================
// End-of-File
// =====================================================================================
