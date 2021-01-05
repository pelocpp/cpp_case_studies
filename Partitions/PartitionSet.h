// =====================================================================================
// PartitionSet.h
// =====================================================================================

#pragma once

class PartitionSet {

private:
   // std::vector<Partition> m_partitions{ };

    std::set<Partition, std::greater<Partition>> m_partitions{ };

    int m_number{ 0 };

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
    bool contains(const Partition&);
    //void sortDescending();
    //void sortAscending();

    // output
    friend std::ostream& operator<< (std::ostream&, const PartitionSet&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
