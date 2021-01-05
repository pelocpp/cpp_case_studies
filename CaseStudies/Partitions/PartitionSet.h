// =====================================================================================
// PartitionSet.h
// =====================================================================================

#pragma once

class PartitionSet {

private:
    std::set<Partition, std::greater<Partition>> m_partitions;
    int m_number;

public:
    // c'tors/d'tor
    PartitionSet() = default;
    PartitionSet(int);

    // properties
    int number() const { return m_number; }
    int size() const { return static_cast<int> (m_partitions.size()); };

    // operators
   // Partition operator[] (int i) const;

    // public interface
    void insert(const Partition&);
   // bool contains(const Partition&);
    //void sortDescending();
    //void sortAscending();

    // iterator support
    std::set<Partition, std::greater<Partition>>::iterator begin() { return m_partitions.begin(); }
    std::set<Partition, std::greater<Partition>>::iterator end() { return m_partitions.end(); }

    // output
    friend std::ostream& operator<< (std::ostream&, const PartitionSet&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
