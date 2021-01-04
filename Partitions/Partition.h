// =====================================================================================
// Partition.h
// =====================================================================================

class Partition
{
private:
    std::vector<int> m_numbers{ 0 };
    int m_number{ 0 };

public:
    // c'tor(s)
    Partition() = default;
    Partition(const std::initializer_list<int>&);

    // properties
    int number() const { return m_number; }
    int size() const { return static_cast<int> (m_numbers.size()); };

    // overrides
    std::string toString();

    // operators

    // TODO PeLo  : Hier müssen exception hin .... und damit müssen die Methoden in das cpp file ...

    int& operator[] (int i) { return m_numbers[i]; }
    const int& operator[] (int i ) const { return m_numbers[i]; };

    //friend or not ??????
    friend bool operator==(const Partition&, const Partition&);
    friend bool operator!=(const Partition&, const Partition&);

    bool operator<=(const Partition&) const;
    bool operator>=(const Partition&) const;
    bool operator<(const Partition&) const;
    bool operator>(const Partition&) const;

    // output
    friend std::ostream& operator<< (std::ostream&, const Partition&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
