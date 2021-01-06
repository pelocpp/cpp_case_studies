// =====================================================================================
// PartitionSet.h
// =====================================================================================

#pragma once

class PartitionSet {

private:
    std::set<Partition, std::greater<Partition>> m_partitions;
    int m_number{ };

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

    void emplace();

    template <typename ... Args>
    void emplace2(Args&& ... args) {

        std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result 
            = m_partitions.emplace( std::initializer_list<int> { std::forward<int> (args) ... });

        std::cout << std::boolalpha <<  "Result: " << std::get<1>(result) << std::endl;
    }

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
