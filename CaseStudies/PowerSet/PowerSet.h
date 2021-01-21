// =====================================================================================
// PowerSet.h
// =====================================================================================

#pragma once

class PowerSet
{
private:
    // member data
    size_t m_size;                // number of elements in base set
    size_t m_cardinality;         // number of subsets
    std::set<PartialSet> m_sets;  // subsets

public:
    // c'tors / d'tor
    PowerSet();
    PowerSet(size_t size);

    // getter/setter
    size_t cardinality() const { return m_cardinality; }
    size_t size() const { return m_size; }

    // public interface
    // int  partialSetsBySize(int cardinality);
    PowerSet partialSetsBySize(size_t size);

    // iterator support
    std::set<PartialSet>::const_iterator begin();
    std::set<PartialSet>::const_iterator end();

    // input/output
    friend std::ostream& operator<< (std::ostream&, const PowerSet&);

private:
    void computePartialSets();
    static size_t powerByTwo(size_t num);
};

// =====================================================================================
// End-of-File
// =====================================================================================
