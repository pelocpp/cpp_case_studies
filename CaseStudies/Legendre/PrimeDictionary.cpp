// =====================================================================================
// PrimeDictionary.h
// =====================================================================================

#include "PrimeDictionary.h"

// getter / setter
size_t PrimeDictionary::getCount() const
{
    return m_map.size();
}

size_t PrimeDictionary::getValue(size_t key) const
{
    return m_map.at(key);
}

void PrimeDictionary::setValue(size_t key, size_t value)
{
    m_map[key] = value;
}

// public interface
bool PrimeDictionary::insert (size_t key, size_t value)
{
    m_map[key] = value;
    return true;
}

void PrimeDictionary::reduce (const PrimeDictionary& dict)
{
    for (const std::pair<size_t, size_t>& entry : dict.m_map) {

        size_t key = entry.first;
        size_t expUpper = getValue(key);
        size_t newExp = expUpper - dict.getValue(key);
        setValue(key, newExp);
    }
}

// output
std::ostream& operator<< (std::ostream& os, const PrimeDictionary& dict)
{
    // iterate and print keys and values using structured binding
    for (const auto& [key, value] : dict.m_map) {
        os << '(' << key << ',' << value << ')';
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
