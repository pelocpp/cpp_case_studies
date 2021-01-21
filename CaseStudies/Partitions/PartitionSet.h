// =====================================================================================
// PartitionSet.h
// =====================================================================================

#pragma once

class PartitionSet {

private:
    std::set<Partition, std::greater<Partition>> m_partitions;
    size_t m_number{ };

public:
    // c'tors/d'tor
    PartitionSet() = delete;
    PartitionSet(size_t);

    // properties
    size_t number() const { return m_number; }
    size_t size() const { return m_partitions.size(); };

    // public interface
    bool insert(const Partition&);

    template <typename ... Args>
    bool emplace(Args&& ... args) {

        // error handling
        std::initializer_list<size_t> list =
            std::initializer_list<size_t>{ static_cast<size_t>(args)... };

        size_t number = std::accumulate(list.begin(), list.end(), static_cast<size_t>(0));
        if (number != m_number) {
            throw std::invalid_argument("Number of partition doesn't match set!");
        }

         //std::pair<std::set<Partition, std::greater<Partition>>::iterator, bool> result
         //   = m_partitions.emplace(list);

        auto result = m_partitions.emplace(Partition{ static_cast<size_t>(args) ... });

        return std::get<1>(result);
    }

    // iterator support
     //std::set<Partition, std::greater<Partition>>::const_iterator begin() { return m_partitions.cbegin(); }
     //std::set<Partition, std::greater<Partition>>::const_iterator end() { return m_partitions.cend(); }
    auto begin() { return m_partitions.cbegin(); }
    auto end() { return m_partitions.cend(); }

    // output
    friend std::ostream& operator<< (std::ostream&, const PartitionSet&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
