// =====================================================================================
// LinearEquationSolver.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

class LinearEquationSolver
{
public:
    LinearEquationSolver();

private:
    Matrix<double> m_matrix;       // equation
 //   double         m_rhs[3];       // right-hand side
    std::size_t    m_dim;          // number of rows = number of columns
    Vector<double> m_solution;     // solution

public:
  //  void setDimension(std::size_t dim);
    std::size_t getDimension() const;

    void setEquation(
        std::size_t dim, 
        std::initializer_list<std::initializer_list<double>> values
    );
    
    bool solve();

    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
