// =====================================================================================
// Vector.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <vector>

template <typename T>
    requires FloatNumber<T>
class Vector
{
protected:
    std::vector<T>        m_values;

public:
    // c'tors
    Vector();
    explicit Vector       (std::size_t dimension);
    explicit Vector       (std::size_t dimension, std::initializer_list<T> values);
   
    // getter   
    std::size_t dimension () const;
    T length              () const;

    // accessing vector elements
    T& at                 (std::size_t index);
    const T& at           (std::size_t index) const;
    T& operator[]         (std::size_t index);
    const T& operator[]   (std::size_t index) const;

    // operators
    Vector  operator+     (const Vector& other) const;
    Vector  operator-     (const Vector& other) const;
    Vector& operator+=    (const Vector& other);
    Vector& operator-=    (const Vector& other);

    Vector  operator*     (T scalar) const;
    T operator*           (const Vector& other) const;

    bool operator==       (const Vector& other) const;
    bool operator!=       (const Vector& other) const;
    
    // public interface
    Vector normalize      () const;
    Vector add            (const Vector& other) const;
    Vector sub            (const Vector& other) const;
    Vector mul            (T scalar) const;
    void   print          () const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
