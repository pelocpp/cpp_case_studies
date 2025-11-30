// =====================================================================================
// MatrixDeterminant.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

#include <cstddef>
#include <stdexcept>

// =====================================================================================

template <typename T>
    requires FloatNumber<T>
class MatrixDeterminant
{
private:
    Matrix<T> m_matrix;           // matrix to compute determinant

public:
    // c'tor(s)
    MatrixDeterminant             () = delete;
    MatrixDeterminant             (const Matrix<T> matrix);

    // getter/setter
    void setMatrix                (const Matrix<T> matrix);

    // public interface
    T determinant                 () const;
    T determinant_sarrus          () const;

public:
    // helper function
    static Matrix<T> minor        (const Matrix<T>& matrix, std::size_t row, std::size_t col);
};

// =====================================================================================
// End-of-File
// =====================================================================================
