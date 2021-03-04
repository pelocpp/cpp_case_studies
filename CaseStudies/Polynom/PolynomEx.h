// =====================================================================================
// PolynomEx.h
// =====================================================================================

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class PolynomEx
{
private:
    std::vector<T> m_coefficients{ 0 };  // zero polynom

public:
    // c'tors
    PolynomEx() = default;

    PolynomEx(std::initializer_list<T> list) : m_coefficients{ list } {
        removeTrailingZeros();
    }

private:
    // internal helper c'tor
    PolynomEx(const std::vector<T>& vector) : m_coefficients{ vector } {
        removeTrailingZeros();
    }

public:
    // getter
    size_t rank() const { return m_coefficients.size() - 1; }
    bool zero() const { return m_coefficients.size() == 1 && m_coefficients[0] == 0; }
    T getCoefficient(size_t index) const { return m_coefficients[index]; }

    // unary mathematical operators
    friend PolynomEx operator+ (const PolynomEx& p) { return PolynomEx{ p }; }

    friend PolynomEx operator- (const PolynomEx& p) {
        std::vector<T> tmp{ p.m_coefficients };
        std::for_each(std::begin(tmp), std::end(tmp), [](T& coeff) {
            coeff *= T{ -1.0 };
            }
        );
        return { tmp };
    }

    // binary mathematical operators
    friend PolynomEx operator+ (const PolynomEx& p1, const PolynomEx& p2) {
        size_t count = (p1.m_coefficients.size() <= p2.m_coefficients.size())
            ? p2.m_coefficients.size()
            : p1.m_coefficients.size();

        // create array for new coefficients
        std::vector<T> coefficients(count);
        for (size_t i = count - 1; i != (size_t)-1; i--) {

            T coeff{ };
            if (i < p1.m_coefficients.size())
                coeff += p1.m_coefficients[i];
            if (i < p2.m_coefficients.size())
                coeff += p2.m_coefficients[i];
            coefficients.at(i) = coeff;
        }

        return { coefficients };
    }

    friend PolynomEx operator- (const PolynomEx& p1, const PolynomEx& p2) {
        return p1 + -p2;
    }
    
    friend PolynomEx<T> operator* (const PolynomEx& p1, const PolynomEx& p2) {
        // create array of coefficients
        size_t count = p1.m_coefficients.size() + p2.m_coefficients.size() - 1;

        // create vector of a specific size for new coefficients
        std::vector<T> coefficients(count);

        // compute coefficients of polynom product
        for (size_t i = p1.m_coefficients.size() - 1; i != (size_t)-1; i--) {
            for (size_t j = p2.m_coefficients.size() - 1; j != (size_t)-1; j--) {
                coefficients[i + j] += p1.m_coefficients[i] * p2.m_coefficients[j];
            }
        }

        return { coefficients };
    }
    
    friend PolynomEx operator/ (const PolynomEx& p1, const PolynomEx& p2) {
        // degree of numerator polynom is less than degree of denominator polynom
        if (p1.m_coefficients.size() < p2.m_coefficients.size())
            return {};

        // need copies of arguments
        PolynomEx tmp1{ p1 };
        PolynomEx tmp2{ p2 };

        // create coefficients array of result polynom
        size_t count = p1.m_coefficients.size() - p2.m_coefficients.size() + 1;
        std::vector<T> rescoeff(count);

        // apply algorithm of polynom division
        for (size_t i = count - 1; i != (size_t)-1; i--) {

            // premature end of division reached (comparing degrees)
            if (tmp1.m_coefficients.size() < p2.m_coefficients.size())
                break;

            // calculate next coefficient of result polynom
            T coeff =
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
    
    friend PolynomEx operator% (const PolynomEx& p1, const PolynomEx& p2) {
        return p1 - (p1 / p2) * p2;
    }

    // binary mathematical assignment operators
    friend PolynomEx& operator+= (PolynomEx& p1, const PolynomEx& p2){
        p1 = p1 + p2;
        return p1;
    }

    friend PolynomEx& operator-= (PolynomEx& p1, const PolynomEx& p2){
        p1 = p1 - p2;
        return p1;
    }

    friend PolynomEx& operator*= (PolynomEx& p1, const PolynomEx& p2){
        p1 = p1 * p2;
        return p1;
    }

    friend PolynomEx& operator/= (PolynomEx& p1, const PolynomEx& p2){
        p1 = p1 / p2;
        return p1;
    }

    friend PolynomEx& operator%= (PolynomEx& p1, const PolynomEx& p2){
        p1 = p1 % p2;
        return p1;
    }

    // apply horner scheme, using functor operator
    T operator() (T x)
    {
        return computeHorner(x);
    }

    // comparison operators
    friend bool operator== (const PolynomEx& p1, const PolynomEx& p2) {
        if (p1.m_coefficients.size() != p2.m_coefficients.size())
            return false;

        for (size_t i = 0; i != p1.m_coefficients.size(); i++)
            if (p1.m_coefficients[i] != p2.m_coefficients[i])
                return false;

        return true;
    }
    
    friend bool operator!= (const PolynomEx& p1, const PolynomEx& p2) {
        return !(p1 == p2);
    }
    
    friend bool operator<  (const PolynomEx& p1, const PolynomEx& p2) {
        if (p1.m_coefficients.size() < p2.m_coefficients.size())
            return true;

        if (p1.m_coefficients.size() > p2.m_coefficients.size())
            return false;

        for (size_t i = p1.m_coefficients.size() - 1; i != (size_t)-1; i--) {
            if (p1.m_coefficients[i] < p2.m_coefficients[i])
                return true;
            if (p1.m_coefficients[i] > p2.m_coefficients[i])
                return false;
        }

        return false;
    }
    
    friend bool operator<= (const PolynomEx& p1, const PolynomEx& p2) {
        return (p1 < p2) || (p1 == p2);
    }
    
    friend bool operator> (const PolynomEx& p1, const PolynomEx& p2) {

        return !(p1 <= p2);
    }
    
    friend bool operator>= (const PolynomEx& p1, const PolynomEx& p2) {

        return !(p1 < p2);
    }

private:
    // private helper operators
    friend PolynomEx operator* (const PolynomEx& p, T scalar) {
        // scalar multiplication with STL
        PolynomEx q{ p };
        std::transform(
            std::begin(p.m_coefficients),
            std::end(p.m_coefficients),
            std::begin(q.m_coefficients),
            [scalar](const auto& elem) {
                return elem * scalar;
            }
        );
        return q;
    }

    friend PolynomEx operator* (T scalar, const PolynomEx& p) {
        return p * scalar;
    }

    // horner scheme
    T computeHorner(T x) const
    {
        size_t count = m_coefficients.size();
        T y = m_coefficients[count - 1];

        std::for_each(
            std::next(std::rbegin(m_coefficients)),
            std::rend(m_coefficients),
            [&](T coeff) {
                y = coeff + y * x;
            }
        );

        return y;
    }

    // private helper methods
    void multiplyX(size_t k) {

        // create new array of coefficients
        std::vector<T> tmp(m_coefficients.size() + k);

        // compute new coefficients - same as shifting to the right
        std::move(m_coefficients.begin(), m_coefficients.end(), tmp.begin() + k);
        
        // switch coefficients buffer
        m_coefficients = tmp;
    }
    
    void removeTrailingZeros() {

        // remove trailing zeros, if any ... using STL algorithms
        std::reverse_iterator<std::vector<T>::iterator> r_it = std::find_if(
            std::rbegin(m_coefficients),
            std::rend(m_coefficients),
            [](T value) { return value != T{}; }
        );

        // vector contains only '0's - rescue last '0'
        if (r_it == std::rend(m_coefficients)) {
            r_it--;
        }

        m_coefficients.erase(r_it.base(), std::end(m_coefficients));
    }
};

// output
template <typename T>
inline std::ostream& operator<< (std::ostream& os, const PolynomEx<T>& p) {
    for (size_t i = p.rank(); /* i >= 0 */; i--)
    {
        if (p.getCoefficient(i) == 0.0 && p.rank() + 1 > 1)
        {
            if (i == 0)
                break;
            else
                continue;
        }

        if (i < p.rank() /* + 1 - 1 */) {
            if (p.getCoefficient(i) > 0.0)
                os << '+';
        }

        if (p.getCoefficient(i) != 1 && p.getCoefficient(i) != -1)
        {
            os << p.getCoefficient(i);
        }
        else if (i > 0)
        {
            if (p.getCoefficient(i) == -1)
                os << '-';
        }
        else
            os << p.getCoefficient(i);

        if (i > 0)
            os << 'x' << '^' << i;

        if (i == 0)
            break;
    }

    return os;
}

// =====================================================================================
// End-of-File
// =====================================================================================
