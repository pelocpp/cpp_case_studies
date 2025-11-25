// =====================================================================================
// LinearEquationSolverLUDecomposition.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

template <typename T>
    requires FloatNumber<T>
class LinearEquationSolverLUDecomposition
{
public:
    LinearEquationSolverLUDecomposition();
    LinearEquationSolverLUDecomposition(std::size_t dimension);

private:
    std::size_t m_dimension;  // number of rows / columns
    Matrix<T>   m_matrix;     // equation (left-hand side)
    Vector<T>   m_rhs;        // right-hand side
    Vector<T>   m_solution;   // solution

public:
    // getter/setter
    void setEquation          (std::initializer_list<std::initializer_list<T>> values);
    void setEquation          (const Matrix<T> coefficients);

    void setRightHandSide     (std::initializer_list<T> rhs);
    void setRightHandSide     (const Vector<T>& rhs);

    std::size_t dimension     () const;
    const Vector<T>& solution () const;

    // public interface
    void solve();
    void print() const;

private:
    Vector<T> forwardSubstitution(const Matrix<T> lower, const Vector<T>& v) const;
    Vector<T> backwardSubstitution(const Matrix<T> upper, const Vector<T>& v) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
