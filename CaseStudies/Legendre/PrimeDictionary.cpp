// =====================================================================================
// PrimeDictionary.h
// =====================================================================================

#include "PrimeDictionary.h"

// getter / setter
size_t PrimeDictionary::get(size_t key) const
{
    return m_map.at(key);
}

void PrimeDictionary::set(size_t key, size_t value)
{
    m_map[key] = value;
}

// public interface
void PrimeDictionary::reduce (const PrimeDictionary& dict)
{
    for (const auto& [key, value] : dict.m_map) {

        size_t newCoeff = get(key) - value;
        set(key, newCoeff);
    }
}

// output
std::ostream& operator<< (std::ostream& os, const PrimeDictionary& dict)
{
    // iterate and print keys and values using structured binding
    for (int k = 0; const auto & [key, value] : dict.m_map) {
        os << '(' << key << ',' << value << ')';
        ++k;
        if (k % 16 == 0)
            os << '\n';
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
