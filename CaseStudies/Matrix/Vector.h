// =====================================================================================
// Vector.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"

#include <cstddef>
#include <initializer_list>
#include <memory>

template <typename T>
    requires FloatNumber<T>
class Vector
{
protected:
    std::size_t m_length;
    std::shared_ptr<T[]> m_values;

public:
    // c'tors
    Vector();
    Vector(std::size_t length);
    Vector(std::size_t length, std::initializer_list<T> values);
   
    // getter   
    std::size_t length() const { return m_length; }

    // public interface
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;


    Vector normalize();

    Vector add(const Vector& other) const;
    Vector sub(const Vector& other) const;
    Vector mul(T scalar) const;



    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
