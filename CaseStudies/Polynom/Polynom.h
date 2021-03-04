// =====================================================================================
// Polynom.h
// =====================================================================================

#pragma once

class Polynom
{
private:
    std::vector<double> m_coefficients{ 0 };  // zero polynom

public:
    // c'tors
    Polynom() = default;
    Polynom(std::initializer_list<double>);

private:
    // internal helper c'tor
    Polynom(const std::vector<double>&);

public:
    // getter
    size_t rank() const;
    bool zero() const;

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

    // functor operator
    double operator() (double);

    // output
    friend std::ostream& operator<< (std::ostream&, const Polynom&);

private:
    // private helper operators
    friend Polynom operator* (const Polynom&, double);
    friend Polynom operator* (double, const Polynom&);

    // horner scheme
    double computeHorner(double) const;

    // private helper methods
    void multiplyX(size_t);
    void removeTrailingZeros();
};

// =====================================================================================
// End-of-File
// =====================================================================================
