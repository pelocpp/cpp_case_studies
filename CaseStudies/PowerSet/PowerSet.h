// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

class PowerSet
{
private:
    // member data
    int m_elements;      // number of elements in base set
    int m_cardinality;   // number of subsets
    int m_index;         // enumeration index

    PartialSet** m_sets; // array of power sets

public:
    // c'tors / d'tor
    PowerSet ();
    PowerSet (const PowerSet&);
    PowerSet (int elements);
    ~PowerSet ();

    // getter/setter
    int GetCardinality() { return m_cardinality; }
    int GetSize() { return m_elements; }

    // public interface
    void Sort();

    int  PartialSetsBySize(int cardinality);
    void PartialSetsBySize(int cardinality, PartialSet buf[], int len);

    // operators
    PowerSet& operator= (const PowerSet&);
    PartialSet operator[] (int index);

    // enumerator interface
    void Reset();
    bool MoveNext();
    PartialSet Current();

    // input/output
    friend ostream& operator<< (ostream&, const PowerSet&);

private:
    // private helper methods
    static int PowerByTwo(int num);
};

// =====================================================================================
// End-of-File
// =====================================================================================
