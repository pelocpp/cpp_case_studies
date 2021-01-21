// =====================================================================================
// PartialSet.h
// =====================================================================================

#pragma once

class PartialSet
{
private:
    // member data
    std::set<size_t> m_numbers;

public:
    // c'tors / d'tor
    PartialSet() = default;
    PartialSet(const std::initializer_list<size_t>&);

    // getter
    size_t size() const { return m_numbers.size(); }

    // public interface
    void add(size_t elem) { m_numbers.insert(elem); }

	// public operators
	friend bool operator== (const PartialSet&, const PartialSet&);
	friend bool operator<  (const PartialSet&, const PartialSet&);

    // input/output
    friend std::ostream& operator<< (std::ostream&, const PartialSet&);
};
// =====================================================================================
// End-of-File
// =====================================================================================
