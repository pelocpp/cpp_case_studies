// =====================================================================================
// PermutationIterator.h
// =====================================================================================

//class PermutationIterator
//{
//private:
//    int m_i;
//    const Permutation* m_p;
//
//public:
//    // explicit PermutationIterator(int position = 0);
//
//    PermutationIterator() = default;
//
//    // copy c'tor
//    //PermutationIterator(const PermutationIterator*);
//
//    PermutationIterator(const Permutation* p, int position);
//
//    // void setPermutation(const Permutation&);
//
//    char operator*() const;
//
//    // need postfix increment and decrement operators
//    PermutationIterator operator++(int);
//    PermutationIterator operator--(int);
//
//    // provide also prefix increment and decrement operators
//    // as helpers for their postfix pendants
//    PermutationIterator& operator++();
//    PermutationIterator& operator--();
//
//    bool operator!=(const PermutationIterator& other) const;
//    bool operator==(const PermutationIterator& other) const;
//
//    // subscript operator
//    const char& operator[] (int i);
//
//    // =========
//
//    friend int operator- (const PermutationIterator& lhs, const PermutationIterator& rhs)
//    {
//        return lhs.m_i - rhs.m_i;
//    }
//
//    friend PermutationIterator operator-(PermutationIterator const& lhs, int rhs)
//    {
//        return PermutationIterator(lhs, lhs.m_i - rhs);
//    }
//
//    friend PermutationIterator operator+(PermutationIterator const& lhs, int rhs)
//    {
//        return PermutationIterator(lhs, lhs.m_i + rhs);
//    }
//
//    friend PermutationIterator operator+(int lhs, PermutationIterator const& rhs)
//    {
//        return PermutationIterator(lhs + rhs.m_i);
//    }
//
//    friend PermutationIterator& operator+= (PermutationIterator& lhs, const PermutationIterator& rhs)
//    {
//        lhs.m_i += rhs.m_i;
//        return lhs;
//    }
//
//    friend PermutationIterator& operator-= (PermutationIterator& lhs, const PermutationIterator& rhs)
//    {
//        lhs.m_i -= rhs.m_i;
//        return lhs;
//    }
//
//    // ==========
//
//    char operator-(const PermutationIterator& other);
//};

// =====================================================================================
// End-of-File
// =====================================================================================


class PermutationIterator
{
private:
    int m_i;
    const Permutation& m_p;

public:
    // explicit PermutationIterator(int position = 0);

    PermutationIterator() = default;

    // copy c'tor
    //PermutationIterator(const PermutationIterator*);

    PermutationIterator(const Permutation& p, int position);


    PermutationIterator(const PermutationIterator& it, int position) : m_p (it.m_p), m_i(it.m_i){}

    // void setPermutation(const Permutation&);

    char operator*() const;

    // need postfix increment and decrement operators
    PermutationIterator operator++(int);
    PermutationIterator operator--(int);

    // provide also prefix increment and decrement operators
    // as helpers for their postfix pendants
    PermutationIterator& operator++();
    PermutationIterator& operator--();

    bool operator!=(const PermutationIterator& other) const;
    bool operator==(const PermutationIterator& other) const;

    // subscript operator
    const char& operator[] (long i) const;
   // char& operator[] (long i);




    // =========

    friend int operator- (const PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        return lhs.m_i - rhs.m_i;
    }

    friend PermutationIterator operator-(const PermutationIterator & lhs, int rhs)
    {
       return PermutationIterator(lhs, lhs.m_i - rhs);
    }

    friend PermutationIterator operator+(PermutationIterator const& lhs, int rhs)
    {
        return PermutationIterator(lhs, lhs.m_i + rhs);
    }

    friend PermutationIterator operator+(int lhs, PermutationIterator const& rhs)
    {
        return PermutationIterator(rhs, lhs + rhs.m_i);
    }

    friend PermutationIterator& operator+= (PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        lhs.m_i += rhs.m_i;
        return lhs;
    }

    friend PermutationIterator& operator-= (PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        lhs.m_i -= rhs.m_i;
        return lhs;
    }


    friend bool operator<= (const PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        return true;
    }

    friend bool operator>= (const PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        return true;
    }

    friend bool operator< (const PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        return true;
    }

    friend bool operator> (const PermutationIterator& lhs, const PermutationIterator& rhs)
    {
        return true;
    }


    // ==========

   // char operator-(const PermutationIterator& other);
};