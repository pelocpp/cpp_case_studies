// =====================================================================================
// LinearEquationSolver.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

template <typename T>
    requires FloatNumber<T>
class LinearEquationSolver
{
public:
    LinearEquationSolver();

private:
    std::size_t  m_dim;          // number of rows / columns
    Matrix<T>    m_matrix;       // equation
    Vector<T>    m_solution;     // solution

public:
    // getter/setter
    std::size_t dimension() const;

    void equation(
        std::size_t dim, 
        std::initializer_list<std::initializer_list<T>> values
    );

    const Vector<T>& solution() const;
    
    // public interface
    void solve_01_simple();
    void solve_02_pivot();
    void solve_02_pivot_original();
    void solve_03_permutation_vector();

    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
