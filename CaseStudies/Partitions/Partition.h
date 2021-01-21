// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

class Partition
{
private:
    std::multiset<size_t, std::greater<size_t>> m_numbers;
    size_t m_number{ };

public:
    // c'tor(s)
    Partition() = default;
    Partition(const std::initializer_list<size_t>&);
    Partition(const std::vector<size_t>&);

    // getter
    size_t number() const { return m_number; }
    size_t size() const { return m_numbers.size(); }
    std::vector<size_t> numbers() const;

    // operators
    friend bool operator==(const Partition&, const Partition&);
    friend bool operator<(const Partition&, const Partition&);
    friend bool operator>(const Partition&, const Partition&);

    // iterator support
    std::multiset<size_t, std::greater<size_t>>::const_iterator begin() {
        return m_numbers.cbegin(); 
    }
    std::multiset<size_t, std::greater<size_t>>::const_iterator end() {
        return m_numbers.cend(); 
    }
    //auto begin() { return m_numbers.cbegin(); }
    //auto end() { return m_numbers.cend(); }

    // output
    friend std::ostream& operator<< (std::ostream&, const Partition&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
