// =====================================================================================
// Permutation.h
// =====================================================================================

#pragma once

class Permutation
{
    friend class PermutationIterator;

public:
    //typedef T value_type;
    //typedef value_type* iterator;
    //typedef value_type const* const_iterator;

    //using value_type = char;
    //using iterator = value_type*;
    //using const_iterator = value_type const*;

    using iterator_category = std::random_access_iterator_tag;

    using value_type = char;
   // using iterator = value_type*;
    using difference_type = std::ptrdiff_t;
    using pointer = char*;
    using reference = char&;



private:
    std::vector<char> m_values;

public:
    // c'tors
    Permutation() = default;
    Permutation(const std::initializer_list<char>&);
    Permutation(const std::string_view);
    Permutation(const std::vector<char>&);
    ~Permutation() { std::cout << "d'tor Permutation" << std::endl; };

public:
    // getter
    int grade() const { return static_cast<int>(m_values.size()); }
    std::vector<char> getValues() const { return m_values; }

    // public interface
    void insertAtFront(char c);
    Permutation removeAt(int i) const;

    // operator(s)
    char operator[] (int i) const;

    // iterator support
    class PermutationIterator begin() const;
    class PermutationIterator end() const;

    // output
    friend std::ostream& operator<< (std::ostream&, const Permutation&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
