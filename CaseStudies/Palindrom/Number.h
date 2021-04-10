// =====================================================================================
// Number.h
// =====================================================================================

#pragma once

using digit_t = uint8_t;

class Number
{
private:
    std::vector<digit_t> m_digits;
    bool m_sign;

public:
    // c'tors / d'tor
    Number();
    explicit Number(std::string_view);

public:
    // getter
    size_t size() const;

    // comparison operators
    //friend bool operator== (const Number&, const Number&);
    //friend bool operator!= (const Number&, const Number&);
    //friend bool operator<  (const Number&, const Number&);
    //friend bool operator<= (const Number&, const Number&);
    //friend bool operator>  (const Number&, const Number&);
    //friend bool operator>= (const Number&, const Number&);

    // binary arithmetic operators
    friend Number operator+ (const Number&, const Number&);

    // functor (supporting formatted output)
    std::string operator()(int);

private:
    // private helper operator
    digit_t& operator[] (size_t);  // subscript operator
    const digit_t& operator[] (size_t) const; // const subscript operator

    // private helper methods
    //void removeLeadingZeros();
    //int compareTo(const Number&) const;
    //void toNumber(long long);

    // output
    friend std::ostream& operator<< (std::ostream&, const Number&);
};

// Number operator"" _big(const char*);

// =====================================================================================
// End-of-File
// =====================================================================================
