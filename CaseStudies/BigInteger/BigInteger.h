// =====================================================================================
// BigInteger.h
// =====================================================================================

#pragma once

class BigInteger
{
private:
    //int* m_digits;
    //int  m_length;
    //bool m_sign;

    std::vector<int> m_digits;
    int  m_length;
    bool m_sign;

public:
    // c'tors / d'tor
    BigInteger();
    BigInteger(std::string_view);
    BigInteger(const BigInteger&);

    // type conversion c'tors
    BigInteger(int n);
    BigInteger(long n);

private:
    // internal helper c'tor
    BigInteger(bool sign, int digits[], int length);

public:
    // getter
    bool Sign() const;
    int Cardinality() const;
    bool IsNull() const;

    // assignment operator
    BigInteger& operator= (const BigInteger&);

    // comparison operators
    friend bool operator== (const BigInteger& a, const BigInteger& b);
    friend bool operator!= (const BigInteger& a, const BigInteger& b);
    friend bool operator<  (const BigInteger& a, const BigInteger& b);
    friend bool operator<= (const BigInteger& a, const BigInteger& b);
    friend bool operator>  (const BigInteger& a, const BigInteger& b);
    friend bool operator>= (const BigInteger& a, const BigInteger& b);

    // unary arithmetic operators
    friend BigInteger operator+ (const BigInteger& a);
    friend BigInteger operator- (const BigInteger& a);

    // binary arithmetic operators
    friend BigInteger operator+ (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator- (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator* (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator/ (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator% (const BigInteger& a, const BigInteger& b);

    // arithmetic-assignment operators
    friend const BigInteger& operator+= (BigInteger& a, const BigInteger& b);
    friend const BigInteger& operator-= (BigInteger& a, const BigInteger& b);
    friend const BigInteger& operator*= (BigInteger& a, const BigInteger& b);
    friend const BigInteger& operator/= (BigInteger& a, const BigInteger& b);
    friend const BigInteger& operator%= (BigInteger& a, const BigInteger& b);

    // increment/decrement operators (prefix/postfix version)
    friend BigInteger& operator++ (BigInteger& a);           // prefix increment
    friend const BigInteger operator++ (BigInteger& a, int); // postfix increment
    friend BigInteger& operator-- (BigInteger& a);           // prefix decrement
    friend const BigInteger operator-- (BigInteger& a, int); // postfix decrement

    // public helper methods
    BigInteger Abs() const;

    // test method
    friend BigInteger Faculty(BigInteger n);

private:
    // private helper operator
    int& operator[] (int) const; // subscript operator

    // private helper methods
    void RemoveLeadingZeros();
    void Zero();
    int CompareTo(const BigInteger& a) const;
    void ToBigInteger(long);

    // output
    friend std::ostream& operator<< (std::ostream& os, const BigInteger& n);
};

// =====================================================================================
// End-of-File
// =====================================================================================
