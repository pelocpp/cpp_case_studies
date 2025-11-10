// =====================================================================================
// VectorImpl.cpp
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "Vector.h"

#include <cmath>
#include <print>
#include <span>
#include <stdexcept>    

// c'tors
template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector() : m_dimension{}, m_values{} {}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t length)
    : m_dimension{ length }
{
    m_values = std::make_shared<T[]>(length);
}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t length, std::initializer_list<T> values)
    : m_dimension{ length }
{
    if (m_dimension != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    m_values = std::make_shared<T[]>(length);

    std::copy(
        values.begin(),
        values.end(),
        m_values.get()
    );
}

// getter
template <typename T>
    requires FloatNumber<T>
std::size_t Vector<T>::dimension() const 
{
    return m_dimension;
}

template <typename T>
    requires FloatNumber<T>
T Vector<T>::length() const
{
    T result{};

    for (std::size_t i{}; i != m_dimension; ++i) {
        result += m_values[i] * m_values[i];
    }

    result = std::sqrt(result);

    return result;
}

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
Vector<T> Vector<T>::operator* (T scalar) const
{
    return mul(scalar);
}

template <typename T>
    requires FloatNumber<T>
bool Vector<T>::operator== (const Vector& other) const
{
    if (m_dimension != other.m_dimension) {
        return false;
    }

    for (size_t k{}; k != m_dimension; ++k) {
        if (m_values[k] != other.m_values[k]) {
            return false;
        }
    }

    return true;
}

template <typename T>
    requires FloatNumber<T>
bool Vector<T>::operator!= (const Vector& other) const
{
    return ! (*this == other);
}

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
    if (index >= m_dimension) {
        throw std::invalid_argument("Invalid index!!");
    }

    return m_values[index];
}

// die beiden mal aufrufen ... werden die an die jeweilige const / non-const version umgeleitet ???
template <typename T>
    requires FloatNumber<T>
T& Vector<T>::operator[](std::size_t index)
{
    return at(index);
}

template <typename T>
    requires FloatNumber<T>
const T& Vector<T>::operator[](std::size_t index) const
{
    return at(index);
}


template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::normalize() const
{
    Vector<T> result{ m_dimension };
    T norm{ static_cast<T>(1.0) / length() };

    //  normalize vector
    for (std::size_t i{}; i != m_dimension; ++i) {
        result.at(i) = m_values[i] * norm;
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::add(const Vector& other) const
{
    Vector<T> result{ m_dimension };

    for (std::size_t i{}; i != m_dimension; ++i) {

        result.m_values[i] = m_values[i] + other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::sub(const Vector& other) const
{
    Vector<T> result{ m_dimension };

    for (std::size_t i{}; i != m_dimension; ++i) {

        result.m_values[i] = m_values[i] - other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::mul(T scalar) const
{
    Vector<T> result{ *this };

    for (std::size_t i{}; i != m_dimension; ++i) {

        result.m_values[i] *= scalar;
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
void Vector<T>::print() const
{
    if (m_values == nullptr) {
        return;
    }

    std::span<T> sp{ m_values.get(), m_dimension };

    std::print("{{");
    for (int k{}; auto elem : sp) {
        std::print("{:6.4g}", elem);
        if (k != m_dimension - 1) {
            std::print(", ", elem);
            ++k;
        }
    }
    std::println(" }}");
}

// =====================================================================================

// explicit template instantiations
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
