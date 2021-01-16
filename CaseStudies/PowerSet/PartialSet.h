// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

class PartialSet
{
private:
    // member data
    int* m_numbers;
    int  m_size;

public:
    // c'tors / d'tor
    PartialSet();
    PartialSet(const PartialSet&);
    PartialSet(int numbers[], int size);
    ~PartialSet();

    // getter/setter
    int GetSize() { return m_size; }

    // operators
    PartialSet& operator= (const PartialSet&);

    // public interface
    bool IsEqual (const PartialSet&) const;
    bool IsLessThan (const PartialSet&) const;
    bool IsGreaterThan (const PartialSet&) const;

	// public operators
	friend bool operator== (const PartialSet&, const PartialSet&);
	friend bool operator!= (const PartialSet&, const PartialSet&);
	friend bool operator<= (const PartialSet&, const PartialSet&);
	friend bool operator>= (const PartialSet&, const PartialSet&);

    // input/output
    friend ostream& operator<< (ostream&, const PartialSet&);
};
// =====================================================================================
// End-of-File
// =====================================================================================
