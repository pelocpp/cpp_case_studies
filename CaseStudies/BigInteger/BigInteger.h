// =====================================================================================
// BigInteger.h
// =====================================================================================

#pragma once

class BigInteger
{
private:
    std::vector<int> m_digits;
    int  m_length;
    bool m_sign;

public:
    // c'tors / d'tor
    BigInteger();
    explicit BigInteger(std::string_view);

    // type conversion c'tors
    explicit BigInteger(int n);
    explicit BigInteger(long n);
    explicit BigInteger(long long n);

private:
    // internal helper c'tor
    BigInteger(bool sign, int digits[], int length);  // TODO: Der kommt wohl weg ...........

public:
    // getter
    bool sign() const;
    int cardinality() const;
    bool isNull() const;

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
    friend BigInteger& operator+= (BigInteger& a, const BigInteger& b);
    friend BigInteger& operator-= (BigInteger& a, const BigInteger& b);
    friend BigInteger& operator*= (BigInteger& a, const BigInteger& b);
    friend BigInteger& operator/= (BigInteger& a, const BigInteger& b);
    friend BigInteger& operator%= (BigInteger& a, const BigInteger& b);

    // increment/decrement operators (prefix/postfix version)
    friend BigInteger& operator++ (BigInteger& a);           // prefix increment
    friend const BigInteger operator++ (BigInteger& a, int); // postfix increment
    friend BigInteger& operator-- (BigInteger& a);           // prefix decrement
    friend const BigInteger operator-- (BigInteger& a, int); // postfix decrement

    // public helper methods
    BigInteger abs() const;

    // test method
    friend BigInteger faculty(BigInteger n);

private:
    // private helper operator
    int& operator[] (int);  // subscript operator
    const int& operator[] (int) const; // const subscript operator

    // private helper methods
    void removeLeadingZeros();
    // void Zero();
    int compareTo(const BigInteger& a) const;
    void toBigInteger(long long);

    // output
    friend std::ostream& operator<< (std::ostream& os, const BigInteger& n);
};

// =====================================================================================
// End-of-File
// =====================================================================================
