// =====================================================================================
// LinearEquationSolverGauss.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

template <typename T>
    requires FloatNumber<T>
class LinearEquationSolverGauss
{
public:
    LinearEquationSolverGauss();

private:
    std::size_t  m_dim;         // number of rows / columns
    Matrix<T>    m_matrix;      // equation
    Vector<T>    m_solution;    // solution

public:
    // getter/setter
    std::size_t dimension() const;

    void setEquation(
        std::size_t dim, 
        std::initializer_list<std::initializer_list<T>> values
    );

    const Vector<T>& solution() const;
    
    // public interface
    bool solve_01_simple();
    bool solve_02_pivot();
    bool solve_03_permutation_vector();

    bool eliminateForward();
    bool eliminateForwardPivot();
    bool eliminateForwardPivotPermutation();

    void substituteBack();

    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
