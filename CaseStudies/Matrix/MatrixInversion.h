// =====================================================================================
// MatrixInversion.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

#include <cstddef>

template <typename T>
    requires FloatNumber<T>
class MatrixInversion
{
private:
    Matrix<T> m_matrix;            // matrix to invert

public:
    // c'tor(s)
    MatrixInversion                () = default;

    // getter/setter
    void      set                  (const Matrix<T> matrix);

    // public interface
    void      invert               ();

private:
    Vector<T> forwardSubstitution  (const Matrix<T> lower, const Vector<T>& v) const;
    Vector<T> backwardSubstitution (const Matrix<T> upper, const Vector<T>& v) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
