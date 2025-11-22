// =====================================================================================
// LU_Decomposition.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

//#include <cstddef>
//#include <initializer_list>
//#include <memory>
//#include <vector>

template <typename T>
    requires FloatNumber<T>
class LU_Decomposition
{
public:
    // c'tors
    LU_Decomposition(const Matrix<T> original);
  
    bool decompose();

    void printMatrix() const;
    void printLowerTriangularMatrix() const;
    void printUpperTriangularMatrix() const;

private:
    Matrix<T> m_matrix;  // original matrix
    Matrix<T> m_lower;   // lower triangular matrix
    Matrix<T> m_upper;   // upper triangular matrix
};

// =====================================================================================
// End-of-File
// =====================================================================================
