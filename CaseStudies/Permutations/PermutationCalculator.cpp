#include <iostream>
using namespace std;

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

// c'tor
PermutationCalculator::PermutationCalculator() : m_array(0), m_perm()
{
    m_index = -1;
}

// getter/setter
void PermutationCalculator::SetPermutation(const Permutation& p)
{
    m_perm = p;
}

Permutation PermutationCalculator::GetPermutation()
{
    return m_perm;
}

// public interface
void PermutationCalculator::Calculate()
{
    m_array = Calculate(m_perm);
}

PermutationArray PermutationCalculator::Calculate(const Permutation& p)
{
    if (p.Grade() == 1)
    {
        PermutationArray a(1);
        a.Insert(p);
        return a;
    }
    else
    {
        PermutationArray result(Faculty(p.Grade()));

        for (int i = 0; i < p.Grade(); i++)
        {
            // create permutation without i.-th element of current permutation
            Permutation q = p.Remove(i);

            // calculate permutions of n-1 elements recursively
            PermutationArray tmp = Calculate(q);

            // join result with removed character
            tmp.InsertAll(p[i]);

            // append calculated permutations
            for (int m = 0; m < tmp.Size(); m++)
                result.Insert(tmp[m]);
        }

        return result;
    }
}

// enumerator interface
void PermutationCalculator::Reset()
{
    m_index = -1;
}

bool PermutationCalculator::MoveNext()
{
    m_index++;
    if (m_index < m_array.Size())
    {
        return true;
    }
    else
    {
        Reset();
        return false;
    }
}

Permutation PermutationCalculator::Current()
{
    return m_array[m_index];
}

int PermutationCalculator::Faculty(int n) const
{
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;

    return result;
}