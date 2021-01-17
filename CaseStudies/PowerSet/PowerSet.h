// =====================================================================================
// PowerSet.h
// =====================================================================================

#pragma once

class PowerSet
{
private:
    // member data
    int m_size;                   // number of elements in base set
    int m_cardinality;            // number of subsets
    std::set<PartialSet> m_sets;  // subsets

public:
    // c'tors / d'tor
    PowerSet() : m_size{ 0 }, m_cardinality{ 1 }, m_sets{ PartialSet {} } {}
    PowerSet(int size);

    // getter/setter
    int cardinality() { return m_cardinality; }
    int size() { return m_size; }

    // public interface
    //void sort();

    int  partialSetsBySize(int cardinality);
    void partialSetsBySize(int cardinality, PartialSet buf[], int len);

    // operators
    // PartialSet operator[] (int index);

    // enumerator interface
    //void Reset();
    //bool MoveNext();
    //PartialSet Current();

    // input/output
    friend std::ostream& operator<< (std::ostream&, const PowerSet&);

private:
    void computePartialSets();

    static int powerByTwo(int num);
};

// =====================================================================================
// End-of-File
// =====================================================================================
