// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

class Partition
{
private:
    std::multiset<int, std::greater<int>> m_numbers;
    int m_number{ };

public:
    // c'tor(s)
    Partition() = default;
    Partition(const std::initializer_list<int>&);
    Partition(const std::vector<int>&);

    // getter
    int number() const { return m_number; }
    size_t size() const { return m_numbers.size(); }
    std::vector<int> numbers() const;

    // operators
    friend bool operator==(const Partition&, const Partition&);
    friend bool operator<(const Partition&, const Partition&);
    friend bool operator>(const Partition&, const Partition&);

    // iterator support
    //std::multiset<int, std::greater<int>>::const_iterator begin() {
    //    return m_numbers.cbegin(); 
    //}
    //std::multiset<int, std::greater<int>>::const_iterator end() {
    //    return m_numbers.cend(); 
    //}
    auto begin() { return m_numbers.cbegin(); }
    auto end() { return m_numbers.cend(); }

    // output
    friend std::ostream& operator<< (std::ostream&, const Partition&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
