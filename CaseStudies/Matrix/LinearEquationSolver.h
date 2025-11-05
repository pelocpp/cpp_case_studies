// =====================================================================================
// LinearEquationSolver.h
// =====================================================================================

#pragma once

#include "Matrix.h"

#include <cstddef>
#include <initializer_list>
//#include <memory>

class LinearEquationSolver
{
public:
    LinearEquationSolver();

private:
    Matrix<double> m_matrix;       // equation
    double         m_rhs[3];       // right-hand side
    std::size_t    m_dim;          // number of rows = number of columns
    double         m_solution[3];  // solution

public:
  //  void setDimension(std::size_t dim);
    std::size_t getDimension() const;

    void setEquation(std::size_t dim, std::initializer_list<std::initializer_list<double>> values);
    void setRightHandSide(std::initializer_list<double> values);

    bool solve();

    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
