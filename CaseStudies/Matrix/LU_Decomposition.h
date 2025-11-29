// =====================================================================================
// LU_Decomposition.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

template <typename T>
    requires FloatNumber<T>
class LU_Decomposition
{
public:
    // c'tors
    LU_Decomposition                () = delete;
    LU_Decomposition                (const Matrix<T> matrix);

    // getter / setter
    void set                        (const Matrix<T> matrix);

    const Matrix<T>& getMatrix      () const;
    const Matrix<T>& getLowerMatrix () const;
    const Matrix<T>& getUpperMatrix () const;

    // public interface
    bool decompose_simple();
    bool decompose_pivot();

    void printMatrix                () const;
    void printLowerTriangularMatrix () const;
    void printUpperTriangularMatrix () const;

private:
    Matrix<T> m_matrix;             // matrix to decompose
    Matrix<T> m_lower;              // lower triangular matrix
    Matrix<T> m_upper;              // upper triangular matrix
    Matrix<T> m_perm;               // permutation matrix
};

// =====================================================================================
// End-of-File
// =====================================================================================
