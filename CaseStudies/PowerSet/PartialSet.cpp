// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

#include <iostream>
using namespace std;

#include "PartialSet.h"
#include "PowerSet.h"

// c'tors / d'tor
PartialSet::PartialSet()
{
    m_size = 0;
    m_numbers = (int*) 0;
}

PartialSet::PartialSet(const PartialSet& set)
{
    m_size = set.m_size;
    m_numbers = new int[set.m_size];

    for (int i = 0; i < m_size; i ++)
        m_numbers[i] = set.m_numbers[i];
}
   
PartialSet::PartialSet(int numbers[], int size)
{
    m_size = size;
    m_numbers = new int[m_size];

    for (int i = 0; i < size; i ++)
        m_numbers[i] = numbers[i];
}

PartialSet::~PartialSet()
{
    delete[] m_numbers;
}

// assignment operator
PartialSet& PartialSet::operator= (const PartialSet& set)
{
    if (this == &set)
        return *this;

    m_size = set.m_size;

    delete[] m_numbers;
    m_numbers = new int[set.m_size];

    for (int i = 0; i < m_size; i ++)
        m_numbers[i] = set.m_numbers[i];

    return *this;
}

// public interface
bool PartialSet::IsEqual (const PartialSet& set) const
{
    if (m_size != set.m_size)
        return false;

    for (int i = 0; i < m_size; i++)
    {
        if (m_numbers[i] != set.m_numbers[i])
            return false;
    }

    return true;
}

bool PartialSet::IsLessThan (const PartialSet& set) const
{
    if (m_size < set.m_size)
    {
        return true;
    }
    else if (m_size > set.m_size)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_numbers[i] < set.m_numbers[i])
                return true;
            else if (m_numbers[i] > set.m_numbers[i])
                return false;
            else
                continue;
        }
    }

    return true;
}

bool PartialSet::IsGreaterThan (const PartialSet& set) const
{
	if (this -> IsEqual (set))
		return true;

	return ! this -> IsLessThan (set);
}

// public operators
bool operator== (const PartialSet& set1, const PartialSet& set2)
{
	return set1.IsEqual (set2);
}

bool operator!= (const PartialSet& set1, const PartialSet& set2)
{
	return ! (set1 == set2);
}

bool operator<= (const PartialSet& set1, const PartialSet& set2)
{
	return set1.IsLessThan (set2);
}

bool operator>= (const PartialSet& set1, const PartialSet& set2)
{
	return set1.IsGreaterThan (set2);
}

// input/output
ostream& operator<< (ostream& os, const PartialSet& set)
{
    os << "{ ";
    for (int i = 0; i < set.m_size; i++)
    {
        os << set.m_numbers[i];
        if (i < set.m_size - 1)
            os << ", ";
    }

    os << " }";
    return os;
}
// =====================================================================================
// End-of-File
// =====================================================================================
