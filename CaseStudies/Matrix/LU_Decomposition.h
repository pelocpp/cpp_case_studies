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
    LU_Decomposition(const Matrix<T> original);  // DIESEN KONSTRUKTOR ENTFERNEN ... der setter ist besser wegen der Überprüfung auf quadratisch !!! 
  
    LU_Decomposition() = default;

    bool decompose();

    void set(const Matrix<T> matrix);

    const Matrix<T>& getMatrix();
    const Matrix<T>& getLowerMatrix();
    const Matrix<T>& getUpperMatrix();

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
