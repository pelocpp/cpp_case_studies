// =====================================================================================
// PrimeDictionary.h
// =====================================================================================

#include "PrimeDictionary.h"

// TODO: Entscheiden --- fehlt da ein Clear ????

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
    //// increment top of dictionary
    //m_top ++;
    //if (m_top >= m_count)
    //    return false;

    //// insert key and value
    //m_keys[m_top] = key;
    //m_values[m_top] = value;

    m_map[key] = value;
    return true;
}

void PrimeDictionary::reduce (const PrimeDictionary& dict)
{
    for (size_t i{}; i != dict.m_map.size(); ++i)
    {
        size_t key = dict.m_map.at(i);

        size_t expUpper = getValue (key);

        size_t newExp = expUpper - dict.getValue (key);

        // store result in upper map
        setValue (key, newExp);
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
