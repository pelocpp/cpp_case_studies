// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

class Partition
{
private:
    std::multiset<int, std::greater<int>> m_numbers;
    int m_number{ 0 };

public:
    // c'tor(s)
    Partition() = default;
    Partition(const std::initializer_list<int>&);
    Partition(const std::vector<int>&);

    // getter
    int number() const { return m_number; }
    int size() const { return static_cast<int> (m_numbers.size()); }
    std::vector<int> numbers() const;


    // operators

    // TODO PeLo  : Hier müssen exception hin .... und damit müssen die Methoden in das cpp file ...

    //int& operator[] (int i) { return m_numbers[i]; }
    //const int& operator[] (int i ) const { return m_numbers[i]; }

    friend bool operator==(const Partition&, const Partition&);
    friend bool operator!=(const Partition&, const Partition&);
    friend bool operator<=(const Partition&, const Partition&);
    friend bool operator>=(const Partition&, const Partition&);
    friend bool operator<(const Partition&, const Partition&);
    friend bool operator>(const Partition&, const Partition&);

    // output
    friend std::ostream& operator<< (std::ostream&, const Partition&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
