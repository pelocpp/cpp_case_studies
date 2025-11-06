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

#include <print>
#include <span>
#include <stdexcept>    

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector() : m_length{}, m_values{} {}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t length)
    : m_length{ length }
{
    m_values = std::make_shared<T[]>(length);
}

template <typename T>
    requires FloatNumber<T>
Vector<T>::Vector(std::size_t length, std::initializer_list<T> values)
    : m_length{ length }
{
    if (m_length != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    m_values = std::make_shared<T[]>(length);

    std::copy(
        values.begin(),
        values.end(),
        m_values.get()
    );
}

template <typename T>
    requires FloatNumber<T>
void Vector<T>::print() const
{
    if (m_values == nullptr) {
        return;
    }

    std::span<T> sp{ m_values.get(), m_length };

    std::print("{{ ");
    for (int k{};  auto elem : sp) {
        std::print("{:3}", elem);
        if (k != m_length - 1) {
            std::print(", ", elem);
            ++k;
        }
    }
    std::println(" }}");
}

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
    if (index >= m_length) {
        throw std::invalid_argument("Invalid index!!");
    }

    return m_values[index];
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::normalize()
{
    std::size_t len{ length() };

    T norm{ static_cast<T>(1.0) / static_cast<T>(len) };

    //  normalize vector
    Vector<T> result{};
    for (std::size_t i{}; i != len; ++i) {
        result.at(i) = m_values[i] * norm;
    }

    return result;
}


template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::add(const Vector& other) const
{
    Vector<T> result{ m_length };

    for (std::size_t i{}; i != m_length; ++i) {

        result.m_values[i] = m_values[i] + other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::sub(const Vector& other) const
{
    Vector<T> result{ m_length };

    for (std::size_t i{}; i != m_length; ++i) {

        result.m_values[i] = m_values[i] - other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Vector<T>::mul(T scalar) const
{
    Vector<T> result{ *this };

    for (std::size_t i{}; i != m_length; ++i) {

        result.m_values[i] *= scalar;
    }

    return result;
}

// =====================================================================================

// explicit template instantiations
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
