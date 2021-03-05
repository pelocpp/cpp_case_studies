// =====================================================================================
// Polynom.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <algorithm>

#include "Polynom.h"

// c'tors
Polynom::Polynom(const std::vector<double>& vector) : m_coefficients{ vector }
{
    removeTrailingZeros();
}

Polynom::Polynom(std::initializer_list<double> list) : m_coefficients{ list } 
{
    removeTrailingZeros();
}

// getter
size_t Polynom::rank() const
{
    return m_coefficients.size() - 1;
}

bool Polynom::zero() const
{
    return m_coefficients.size() == 1 && m_coefficients[0] == 0;
}

// unary mathematical operators + and -
Polynom operator+ (const Polynom& p)
{
    return Polynom{ p };
}

Polynom operator- (const Polynom& p)
{
    std::vector<double> tmp{ p.m_coefficients };

    std::for_each(std::begin(tmp), std::end(tmp), [](double& coeff) {
        coeff *= -1.0;
        }
    );

    return { tmp };
}

// binary mathematical operators +, -, *, / and %
Polynom operator+ (const Polynom& p1, const Polynom& p2)
{
    size_t count = (p1.m_coefficients.size() <= p2.m_coefficients.size())
        ? p2.m_coefficients.size()
        : p1.m_coefficients.size();

    // create array for new coefficients
    std::vector<double> coefficients(count);
    // for (size_t i = count - 1; i != static_cast<size_t>(-1); i--) { static_cast<size_t>(-1)
    for (size_t i = count - 1; i != static_cast<size_t>(-1); i--) {
        double coeff = 0.0;
        if (i < p1.m_coefficients.size())
            coeff += p1.m_coefficients[i];
        if (i < p2.m_coefficients.size())
            coeff += p2.m_coefficients[i];
        coefficients.at(i) = coeff;
    }

    return { coefficients };
}

Polynom operator- (const Polynom& p1, const Polynom& p2)
{
    return p1 + -p2;
}

Polynom operator* (const Polynom& p1, const Polynom& p2)
{
    // create array of coefficients
    size_t count = p1.m_coefficients.size() + p2.m_coefficients.size() - 1;

    // create vector of a specific size for new coefficients
    std::vector<double> coefficients(count, 0);

    // compute coefficients of polynom product
    for (size_t i = p1.m_coefficients.size() - 1; i != static_cast<size_t>(-1); i--) {
        for (size_t j = p2.m_coefficients.size() - 1; j != static_cast<size_t>(-1); j--) {
            coefficients[i + j] += p1.m_coefficients[i] * p2.m_coefficients[j];
        }
    }

    return { coefficients };
}

Polynom operator/ (const Polynom& p1, const Polynom& p2)
{
    // degree of numerator polynom is less than degree of denominator polynom
    if (p1.m_coefficients.size() < p2.m_coefficients.size())
        return {};

    // need copies of arguments
    Polynom tmp1{ p1 };
    Polynom tmp2{ p2 };

    // create coefficients array of result polynom
    size_t count = p1.m_coefficients.size() - p2.m_coefficients.size() + 1;
    std::vector<double> rescoeff(count);

    // apply algorithm of polynom division
    for (size_t i = count - 1; i != static_cast<size_t>(-1); i--) {

        // premature end of division reached (comparing degrees)
        if (tmp1.m_coefficients.size() < p2.m_coefficients.size())
            break;

        // calculate next coefficient of result polynom
        double coeff =
            tmp1.m_coefficients[tmp1.m_coefficients.size() - 1] /
            tmp2.m_coefficients[tmp2.m_coefficients.size() - 1];

        // multiply denominator polynom with coefficient
        tmp2 = tmp2 * coeff;

        // calculate difference of ranks
        size_t diffRank = tmp1.m_coefficients.size() - p2.m_coefficients.size();

        // multiply denominator polynom with one ore more 'x'
        tmp2.multiplyX(diffRank);

        // subtract denominator polynom from numerator polynom
        tmp1 = tmp1 - tmp2;

        // poke calculated coefficient into result polynom
        rescoeff[diffRank] = coeff;

        // restore denominator polynom
        tmp2 = p2;
    }

    return { rescoeff };
}

Polynom operator% (const Polynom& p1, const Polynom& p2)
{
    return p1 - (p1 / p2) * p2;
}

// binary mathematical assignment operators +=, -=, *=, /= and %=
Polynom& operator+= (Polynom& p1, const Polynom& p2)
{
    p1 = p1 + p2;
    return p1;
}

Polynom& operator-= (Polynom& p1, const Polynom& p2)
{
    p1 = p1 - p2;
    return p1;
}

Polynom& operator*= (Polynom& p1, const Polynom& p2)
{
    p1 = p1 * p2;
    return p1;
}

Polynom& operator/= (Polynom& p1, const Polynom& p2)
{
    p1 = p1 / p2;
    return p1;
}

Polynom& operator%= (Polynom& p1, const Polynom& p2)
{
    p1 = p1 % p2;
    return p1;
}

// horner scheme
double Polynom::computeHorner(double x) const
{
    size_t count = m_coefficients.size();
    double y = m_coefficients[count - 1];

    std::for_each(
        std::next(std::rbegin(m_coefficients)),
        std::rend(m_coefficients), 
        [&](double coeff) {
            y = coeff + y * x;
        }
    );

    return y;
}

// apply horner scheme, using functor operator
double Polynom::operator() (double x)
{
    return computeHorner(x);
}

// comparison operators
bool operator== (const Polynom& p1, const Polynom& p2)
{
    if (p1.m_coefficients.size() != p2.m_coefficients.size())
        return false;

    for (size_t i = 0; i != p1.m_coefficients.size(); i++)
        if (p1.m_coefficients[i] != p2.m_coefficients[i])
            return false;

    return true;
}

bool operator!= (const Polynom& p1, const Polynom& p2)
{
    return !(p1 == p2);
}

bool operator<  (const Polynom& p1, const Polynom& p2)
{
    if (p1.m_coefficients.size() < p2.m_coefficients.size())
        return true;

    if (p1.m_coefficients.size() > p2.m_coefficients.size())
        return false;

    for (size_t i = p1.m_coefficients.size() - 1; i != static_cast<size_t>(-1); i--) {
        if (p1.m_coefficients[i] < p2.m_coefficients[i])
            return true;
        if (p1.m_coefficients[i] > p2.m_coefficients[i])
            return false;
    }

    return false;
}

bool operator<= (const Polynom& p1, const Polynom& p2)
{
    return (p1 < p2) || (p1 == p2);
}

bool operator>  (const Polynom& p1, const Polynom& p2)
{
    return !(p1 <= p2);
}

bool operator>= (const Polynom& p1, const Polynom& p2)
{
    return !(p1 < p2);
}

// output
std::ostream& operator<< (std::ostream& os, const Polynom& p)
{
    for (size_t i = p.m_coefficients.size() - 1; /* i >= 0 */ ; i--)
    {
        if (p.m_coefficients[i] == 0.0 && p.m_coefficients.size() > 1)
        {
            if (i == 0)
                break;
            else 
                continue;
        }

        if (i < p.m_coefficients.size() - 1) {
            if (p.m_coefficients[i] > 0.0)
                os << '+';
        }

        if (p.m_coefficients[i] != 1 && p.m_coefficients[i] != -1)
        {
            os << p.m_coefficients[i];
        }
        else if (i > 0)
        {
            if (p.m_coefficients[i] == -1)
                os << '-';
        }
        else
            os << p.m_coefficients[i];

        if (i > 0)
            os << 'x' << '^' << i;

        if (i == 0)
            break;
    }

    return os;
}

// private helper operators
Polynom operator* (double scalar, const Polynom& p)
{
    // scalar multiplication with STL
    Polynom q{ p };
    std::transform (
        std::begin(p.m_coefficients),
        std::end(p.m_coefficients), 
        std::begin(q.m_coefficients),
        [scalar](const auto& elem) {
            return elem * scalar;
        }
    );
    return q;
}

Polynom operator* (const Polynom& p, double scalar)
{
    return scalar * p;
}

void Polynom::multiplyX(size_t k)
{
    // create new array of coefficients
    std::vector<double> tmp(m_coefficients.size() + k);

    // compute new coefficients - same as shifting to the right
    std::move(m_coefficients.begin(), m_coefficients.end(), tmp.begin() + k);

    // switch coefficients buffer
    m_coefficients = tmp;
}

void Polynom::removeTrailingZeros()
{
    // remove trailing zeros, if any ... using STL algorithms
    std::reverse_iterator<std::vector<double>::iterator> r_it = std::find_if(
        std::rbegin(m_coefficients),
        std::rend(m_coefficients),
        [](double value) { return value != 0.0; }
    );

    // vector contains only '0's - rescue last '0'
    if (r_it == std::rend(m_coefficients)) {
        r_it--;
    }

    m_coefficients.erase(r_it.base(), std::end(m_coefficients));
}

// =====================================================================================
// End-of-File
// =====================================================================================
