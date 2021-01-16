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
    PartitionSet() = delete;
    PartitionSet(int);

    // properties
    int number() const { return m_number; }
    size_t size() const { return m_partitions.size(); };

    // public interface
    bool insert(const Partition&);

    template <typename ... Args>
    bool emplace(Args&& ... args) {

        // error handling
        std::initializer_list<int> list =
            std::initializer_list<int>{ std::forward<int>(args)... };

        int number = std::accumulate(list.begin(), list.end(), 0);
        if (number != m_number) {
            throw std::invalid_argument("Number of partition doesn't match set!");
        }

        // std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result
        //    = m_partitions.emplace(list);

        auto result = m_partitions.emplace(Partition{ args ... });

        return std::get<1>(result);
    }

    // iterator support
    // std::set<Partition, std::greater<Partition>>::const_iterator begin() { return m_partitions.cbegin(); }
    // std::set<Partition, std::greater<Partition>>::const_iterator end() { return m_partitions.cend(); }
    auto begin() { return m_partitions.cbegin(); }
    auto end() { return m_partitions.cend(); }

    // output
    friend std::ostream& operator<< (std::ostream&, const PartitionSet&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
