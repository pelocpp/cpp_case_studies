// =====================================================================================
// Polynom.h
// =====================================================================================

#pragma once

class Polynom
{
private:
    std::vector<double> m_coefficients{ 0 };  // zero polynom

public:
    // c'tors / d'tor
    Polynom() = default;
    Polynom(std::initializer_list<double>);

private:
    // internal helper c'tor
    Polynom(const std::vector<double>&);

public:
    // getter
    size_t rank() const;
    bool zero() const;

    // assignment operator
    Polynom& operator= (const Polynom&);  // ?????????????????????????????????????

    // unary mathematical operators
    friend Polynom operator+ (const Polynom&);
    friend Polynom operator- (const Polynom&);

    // binary mathematical operators
    friend Polynom operator+ (const Polynom&, const Polynom&);
    friend Polynom operator- (const Polynom&, const Polynom&);
    friend Polynom operator* (const Polynom&, const Polynom&);
    friend Polynom operator/ (const Polynom&, const Polynom&);
    friend Polynom operator% (const Polynom&, const Polynom&);

    // binary mathematical assignment operators
    friend Polynom& operator+= (Polynom&, const Polynom&);
    friend Polynom& operator-= (Polynom&, const Polynom&);
    friend Polynom& operator*= (Polynom&, const Polynom&);
    friend Polynom& operator/= (Polynom&, const Polynom&);
    friend Polynom& operator%= (Polynom&, const Polynom&);

    // comparison operators
    friend bool operator== (const Polynom&, const Polynom&);
    friend bool operator!= (const Polynom&, const Polynom&);
    friend bool operator<  (const Polynom&, const Polynom&);
    friend bool operator<= (const Polynom&, const Polynom&);
    friend bool operator>  (const Polynom&, const Polynom&);
    friend bool operator>= (const Polynom&, const Polynom&);

    // index operator
    double operator[] (double x);

    // function call operator
    double operator() (double x);

    // output
    friend std::ostream& operator<< (std::ostream& os, const Polynom& p);

private:
    // private helper operators
    friend Polynom operator* (const Polynom& p, double d);
    friend Polynom operator* (double d, const Polynom& p);

    // horner scheme
    double computeHorner(double x);

    // private helper methods
    void multiplyX();
    void multiplyX(size_t k);
    void removeLeadingZeros();
};

// =====================================================================================
// End-of-File
// =====================================================================================
