// =====================================================================================
// VectorImpl.cpp
// =====================================================================================

#include "Vector.h"

#include <algorithm>
#include <cmath>
//#include <format> 
#include <print>
#include <stdexcept>
//#include <string_view>

// =====================================================================================
// c'tors

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector() : m_values{} {}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t dimension)
{
    m_values.resize(dimension);
}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t dimension, std::initializer_list<T> values)
{
    if (dimension != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    m_values.resize(dimension);

    std::copy(
        values.begin(),
        values.end(),
        m_values.begin()
    );
}

// =====================================================================================
// getter

template <typename T>
    requires FloatNumber<T>
std::size_t Vector<T>::dimension() const 
{
    return m_values.size();
}

template <typename T>
    requires FloatNumber<T>
T Vector<T>::length() const
{
    T result{};

    for (std::size_t i{}; i != dimension(); ++i) {
        result += m_values[i] * m_values[i];
    }

    result = std::sqrt(result);

    return result;
}

// =====================================================================================
// operators

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::operator+ (const Vector& other) const
{
    return add(other);
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::operator- (const Vector& other) const
{
    return sub(other);
}

template <typename T>
    requires FloatNumber<T>
Vector<T>& Vector<T>::operator+= (const Vector& other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
    requires FloatNumber<T>
Vector<T>& Vector<T>::operator-= (const Vector& other)
{
    *this = *this - other;
    return *this;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::operator* (T scalar) const
{
    return mul(scalar);
}

template <typename T>
    requires FloatNumber<T>
T Vector<T>::operator* (const Vector& other) const
{
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Wrong dimension!");
    }

    T result{};

    for (std::size_t i{}; i != dimension(); ++i) {
        result += (m_values[i] * other.m_values[i]);
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
bool Vector<T>::operator== (const Vector& other) const
{
    return m_values == other.m_values;
}

template <typename T>
    requires FloatNumber<T>
bool Vector<T>::operator!= (const Vector& other) const
{
    return ! (*this == other);
}

// =====================================================================================
// public interface

template <typename T>
    requires FloatNumber<T>
T& Vector<T>::at(std::size_t index)
{
    return const_cast<T&>(static_cast<const Vector&>(*this).at(index));
}

template <typename T>
    requires FloatNumber<T>
const T& Vector<T>::at(std::size_t index) const
{
    if (index >= dimension()) {
        throw std::invalid_argument("Invalid index!!");
    }

    return m_values[index];
}

template <typename T>
    requires FloatNumber<T>
T& Vector<T>::operator[](std::size_t index)
{
    return m_values[index]; // no index check
}

template <typename T>
    requires FloatNumber<T>
const T& Vector<T>::operator[](std::size_t index) const
{
    return m_values[index]; // no index check
}

template <typename T>
    requires FloatNumber<T>
void Vector<T>::fill(T value)
{
    std::fill(m_values.begin(), m_values.end(), value);
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::normalize() const
{
    Vector<T> result{ dimension() };
    T norm{ static_cast<T>(1.0) / length() };

    //  normalize vector
    for (std::size_t i{}; i != dimension(); ++i) {
        result.at(i) = m_values[i] * norm;
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::add(const Vector& other) const
{
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Wrong dimension!");
    }

    Vector<T> result{ dimension() };

    for (std::size_t i{}; i != dimension(); ++i) {
        result.m_values[i] = m_values[i] + other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::sub(const Vector& other) const
{
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Wrong dimension!");
    }

    Vector<T> result{ dimension() };

    for (std::size_t i{}; i != dimension(); ++i) {
        result.m_values[i] = m_values[i] - other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::mul(T scalar) const
{
    Vector<T> result{ *this };

    for (std::size_t i{}; i != dimension(); ++i) {
        result.m_values[i] *= scalar;
    }

    return result;
}

//template <typename T>
//    requires FloatNumber<T>
//void Vector<T>::print() const
//{
//    std::print("{{");
//    for (int k{}; auto elem : m_values) {
//        std::print("{:6.4g}", elem);
//        if (k != dimension() - 1) {
//            std::print(", ");
//            ++k;
//        }
//    }
//    std::println(" }}");
//}

// =====================================================================================

// explicit template instantiations
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
