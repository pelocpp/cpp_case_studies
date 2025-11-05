// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <print>
#include <stdexcept> 

// =====================================================================================

LinearEquationSolver::LinearEquationSolver() : m_dim{}, m_rhs{}, m_solution{} {}

//void LinearEquationSolver::setDimension(std::size_t dim)
//{
//    m_dim = dim;
//}

std::size_t LinearEquationSolver::getDimension() const
{
    return m_dim;
}

void LinearEquationSolver::setEquation(std::size_t dim, std::initializer_list<std::initializer_list<double>> values)
{
    m_dim = dim;

    m_matrix = Matrix<double>{ dim, dim, values };
}

void LinearEquationSolver::setRightHandSide(std::initializer_list<double> values)
{
    if (m_dim != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    // m_rhs
    for (int i{}; auto elem : values) {
        m_rhs[i] = elem;
        ++i;
    }
}

void LinearEquationSolver::print() const
{
    for (size_t row{}; row != m_dim; ++row) {
        for (size_t col{}; col != m_dim; ++col) {
            std::print("{:3}", m_matrix.at(row,col));
        }
        std::println(" | {:3}", m_rhs[row]);
    }
    std::println();
}

bool LinearEquationSolver::solve()
{
    // wenn 1-dimensional ...

     for (std::size_t row{}; row != m_dim - 1; ++row) {
   // for (std::size_t row{}; row != 1; ++row) {

        // eliminate row
        double coeff1 = m_matrix.at(row, row);
        double coeff2 = m_matrix.at(row+1, row);

        double newCoeff = coeff1 / coeff2;

        // multiply row below current row with this coeccicient
        m_matrix.mulRow(row + 1, newCoeff);
        print();

        // subtract modified row from first row, result replaces current row ...
        m_matrix.subtractRow(row, row+1);

        // ... and update right-hand side
        m_rhs[row+1] -= m_rhs[row];

        print();
    }

    return false;
}


// =====================================================================================
// End-of-File
// =====================================================================================
