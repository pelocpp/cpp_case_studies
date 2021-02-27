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
    removeLeadingZeros();
}

Polynom::Polynom(std::initializer_list<double> list) : m_coefficients{ list } 
{
    removeLeadingZeros();
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
    //Polynom tmp{ p };

    //std::for_each(std::begin (tmp.m_coefficients), std::end(tmp.m_coefficients), [](double& coeff) {
    //    coeff *= -1.0;
    //});
    //
    //return tmp;

    // ############# templates: hier muss kräftig <T> hin ......

    std::vector<double> tmp{ p.m_coefficients };

    std::for_each(std::begin(tmp), std::end(tmp), [](auto& coeff) {  // auto oder T
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
    for (size_t i = count - 1; i != (size_t)-1; i--)
    {
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
    Polynom tmp{ -p2 };
    tmp = p1 + tmp;
    return tmp;   // #################################### kürzer schreiben
}

Polynom operator* (const Polynom& p1, const Polynom& p2)
{
    // create array of coefficients
    size_t count = p1.m_coefficients.size() + p2.m_coefficients.size() - 1;
    // double* coefficients = new double[count];

    // create vector of a specific size for new coefficients
    std::vector<double> coefficients (count);

    // clear coefficients array
    //for (int i = 0; i < count; i++)
    //    coefficients[i] = 0.0;

    // compute coefficients of polynom product
    for (size_t i = p1.m_coefficients.size() - 1; i != (size_t)-1; i--)
    {
        for (size_t j = p2.m_coefficients.size() - 1; j != (size_t)-1; j--)
        {
            coefficients[i + j] += p1.m_coefficients[i] * p2.m_coefficients[j];
        }
    }

    // create result polynom
    // Polynom result(coefficients, count);

    Polynom result{ coefficients };

    // delete temporary array of coefficients
    // delete[] coefficients;

    return result;
}


Polynom operator/ (const Polynom& p1, const Polynom& p2)
{
    // degree of numerator polynom is less than degree of denominator polynom
    if (p1.m_coefficients.size() < p2.m_coefficients.size())
        return Polynom{};  // ################################################## Stimmt der Def c'tor hier

    // need copies of arguments
    Polynom tmp1 = p1;
    Polynom tmp2 = p2;

    // create coefficients array of result polynom
    size_t count = p1.m_coefficients.size() - p2.m_coefficients.size() + 1;
    // double* rescoeff = new double[count];
    std::vector<double> rescoeff(count);

    // clear coefficients array
    //for (int i = 0; i < count; i++)
    //    rescoeff[i] = 0.0;

    // apply algorithm of polynom division
    for (size_t i = count - 1; i != (size_t)-1; i--)
    {
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

    return Polynom(rescoeff);
}





















//
//Polynom operator/ (const Polynom& p1, const Polynom& p2)
//{
//    if (p1.m_count < p2.m_count)  // degree of numerator polynom is less than
//        return Polynom();         // degree of denominator polynom
//
//    // need copies of arguments
//    Polynom tmp1 = p1;
//    Polynom tmp2 = p2;
//
//    // create coefficients array of result polynom
//    int count = p1.m_count - p2.m_count + 1;
//    double* rescoeff = new double[count];
//
//    // clear coefficients array
//    for (int i = 0; i < count; i++)
//        rescoeff[i] = 0.0;
//
//    // apply algorithm of polynom division
//    for (int i = count - 1; i >= 0; i--)
//    {
//        // premature end of division reached (comparing degrees)
//        if (tmp1.m_count < p2.m_count)
//            break;
//
//        // calculate next coefficient of result polynom
//        double coeff =
//            tmp1.m_coefficients[tmp1.m_count - 1] /
//            tmp2.m_coefficients[tmp2.m_count - 1];
//
//        // multiply denominator polynom with coefficient
//        tmp2 = tmp2 * coeff;
//
//        // calculate difference of ranks
//        int diffRank = tmp1.m_count - p2.m_count;
//
//        // multiply denominator polynom with one ore more 'x'
//        tmp2.MultiplyX(diffRank);
//
//        // subtract denominator polynom from numerator polynom
//        tmp1 = tmp1 - tmp2;
//
//        // poke calculated coefficient into result polynom
//        rescoeff[diffRank] = coeff;
//
//        // restore denominator polynom
//        tmp2 = p2;
//    }
//
//    return Polynom(rescoeff, count);
//}
//
Polynom operator% (const Polynom& p1, const Polynom& p2)
{
    return p1 - (p1 / p2) * p2;
}
//
//// binary mathematical assignment operators +=, -=, *=, /= and %=
//Polynom& operator+= (Polynom& p1, const Polynom& p2)
//{
//    p1 = p1 + p2;
//    return p1;
//}
//
//Polynom& operator-= (Polynom& p1, const Polynom& p2)
//{
//    p1 = p1 - p2;
//    return p1;
//}
//
//Polynom& operator*= (Polynom& p1, const Polynom& p2)
//{
//    p1 = p1 * p2;
//    return p1;
//}
//
//Polynom& operator/= (Polynom& p1, const Polynom& p2)
//{
//    p1 = p1 / p2;
//    return p1;
//}
//
//Polynom& operator%= (Polynom& p1, const Polynom& p2)
//{
//    p1 = p1 % p2;
//    return p1;
//}
//
//
//
//
//// horner scheme
//double Polynom::computeHorner(double x)
//{
//    double y = m_coefficients[m_count - 1];
//    for (int i = m_count - 2; i >= 0; i--)
//        y = m_coefficients[i] + y * x;
//    return y;
//}
//
//// apply horner scheme, using array subscripting operator
//double Polynom::operator[](double x)
//{
//    return computeHorner(x);
//}
//
//// apply horner scheme, using function call operator
//double Polynom::operator() (double x)
//{
//    return computeHorner(x);
//}













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

    for (size_t i = p1.m_coefficients.size() - 1; i != (size_t)-1; i--)
    {
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

// assignment operator
Polynom& Polynom::operator= (const Polynom& p)
{
    if (this == &p)
        return *this;

    // use 'operator=' implementation of class 'vector<double>'
    m_coefficients = p.m_coefficients;

    return *this;
}

// private helper operators
Polynom operator* (double d, const Polynom& p)
{
    Polynom q = p;
    for (size_t i = 0; i < p.m_coefficients.size(); i++)
        q.m_coefficients[i] *= d;
    return q;
}

Polynom operator* (const Polynom& p, double d)
{
    return d * p;
}

// private helper methods
void Polynom::multiplyX()
{
    // create new array of coefficients
    //double* tmp = new double[m_count + 1];

    // compute new coefficients
    //tmp[0] = 0.0;
    //for (int i = 1; i <= m_count; i++)
    //    tmp[i] = m_coefficients[i - 1];

    // switch coefficients buffer
    //delete[] m_coefficients;
    //m_coefficients = tmp;
    //m_count++;

    // create new array of coefficients
    std::vector<double> tmp(m_coefficients.size() + 1);
    // compute new coefficients - same as one shift to the right
    std::move(m_coefficients.begin(), m_coefficients.end(), tmp.begin() + 1);
    // switch coefficients buffer
    m_coefficients = tmp;
}

void Polynom::multiplyX(size_t k)
{
    for (size_t i = 0; i != k; i++) {
        multiplyX();
    }
}

void Polynom::removeLeadingZeros() {
    // remove leading zeros, if any ...
    size_t top = m_coefficients.size() - 1;
    while (top != 0 && m_coefficients[top] == 0.0)   // TODO: Hier muss dann T {} stehen !!!!
    {
        m_coefficients.pop_back();
        top--;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
