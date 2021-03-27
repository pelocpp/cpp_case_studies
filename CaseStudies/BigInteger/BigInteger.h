// =====================================================================================
// BigInteger.h
// =====================================================================================

#pragma once

using digit_t = uint8_t;

class BigInteger
{
private:
    std::vector<digit_t> m_digits;
    bool m_sign;

public:
    // c'tors / d'tor
    BigInteger();
    explicit BigInteger(std::string_view);

    // type conversion c'tors
    explicit BigInteger(int);
    explicit BigInteger(long);
    explicit BigInteger(long long);

public:
    // getter
    size_t size() const;
    bool zero() const;
    bool sign() const;

    // comparison operators
    friend bool operator== (const BigInteger&, const BigInteger&);
    friend bool operator!= (const BigInteger&, const BigInteger&);
    friend bool operator<  (const BigInteger&, const BigInteger&);
    friend bool operator<= (const BigInteger&, const BigInteger&);
    friend bool operator>  (const BigInteger&, const BigInteger&);
    friend bool operator>= (const BigInteger&, const BigInteger&);

    // unary arithmetic operators
    friend BigInteger operator+ (const BigInteger&);
    friend BigInteger operator- (const BigInteger&);

    // binary arithmetic operators
    friend BigInteger operator+ (const BigInteger&, const BigInteger&);
    friend BigInteger operator- (const BigInteger&, const BigInteger&);
    friend BigInteger operator* (const BigInteger&, const BigInteger&);
    friend BigInteger operator/ (const BigInteger&, const BigInteger&);
    friend BigInteger operator% (const BigInteger&, const BigInteger&);

    // arithmetic-assignment operators
    friend BigInteger& operator+= (BigInteger&, const BigInteger&);
    friend BigInteger& operator-= (BigInteger&, const BigInteger&);
    friend BigInteger& operator*= (BigInteger&, const BigInteger&);
    friend BigInteger& operator/= (BigInteger&, const BigInteger&);
    friend BigInteger& operator%= (BigInteger&, const BigInteger&);

    // increment/decrement operators (prefix/postfix version)
    friend BigInteger& operator++ (BigInteger&);       // prefix increment
    friend BigInteger  operator++ (BigInteger&, int);  // postfix increment
    friend BigInteger& operator-- (BigInteger&);       // prefix decrement
    friend BigInteger  operator-- (BigInteger&, int);  // postfix decrement

    // functor (supporting formatted output)
    std::string operator()(int);  // n Blöcke in einer Zeile ....

    // public helper methods
    BigInteger abs() const;
    BigInteger pow(int);

    // test method
    //friend BigInteger faculty(BigInteger);
   // public BigInteger Power(int exponent)

private:
    // private helper operator
    digit_t& operator[] (size_t);  // subscript operator
    const digit_t& operator[] (size_t) const; // const subscript operator

    // private helper methods
    void removeLeadingZeros();
    // void Zero();
    int compareTo(const BigInteger&) const;
    void toBigInteger(long long);

    // output
    friend std::ostream& operator<< (std::ostream&, const BigInteger&);
};

// =====================================================================================
// End-of-File
// =====================================================================================
