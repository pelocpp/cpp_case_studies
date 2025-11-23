// =====================================================================================
// InvertableMatrix.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

#include <cstddef>

template <typename T>
    requires FloatNumber<T>
class InvertableMatrix
{
public:
    // c'tor(s)
    InvertableMatrix() = default;

private:
    Matrix<T> m_matrix;  // original matrix
    Matrix<T> m_lower;   // lower triangular matrix
    Matrix<T> m_upper;   // upper triangular matrix

public:
    // getter/setter
    void set(const Matrix<T> matrix);

    // public interface
    bool invert();

    // private ... das muss man spaeter umstellen
    
    // Vorwärtssubstitution: L * y = b

    Vector<T> forwardSubstitution();

    Vector<T> backwardSubstitution();
};

// =====================================================================================
// End-of-File
// =====================================================================================
