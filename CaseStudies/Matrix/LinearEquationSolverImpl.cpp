// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <print>
#include <stdexcept> 

// =====================================================================================

LinearEquationSolver::LinearEquationSolver() : m_dim{} {}

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

    m_matrix = Matrix<double>{ dim, dim + 1, values };
}

void LinearEquationSolver::print() const
{
    for (size_t row{}; row != m_dim; ++row) {
        size_t col{};
        for (; col != m_dim; ++col) {
            std::print("{:5g}", m_matrix.at(row,col));
        }
        std::println(" | {:5g}", m_matrix.at(row, col+1));
    }
    std::println();
}

//https://www.youtube.com/watch?v=vaahX3Wdxu8
//
//https://www.youtube.com/watch?v=9Ule9qQaBB0



bool LinearEquationSolver::solve()
{
    // wenn 1-dimensional ... Sonderbehanldung

    // mehr als eine Zeile ....


    // forward elimination to create a upper right triangle matrix
    for (std::size_t dim{}; dim != m_dim - 1; ++dim) {

        for (std::size_t rowBelow{ dim }; rowBelow != m_dim - 1; ++rowBelow) {

            // eliminate row
            double coeff1 = m_matrix.at(dim, dim);
            double coeff2 = m_matrix.at(rowBelow + 1, dim);

            double newCoeff = coeff1 / coeff2;

            // multiply row below current row with this coeccicient
            m_matrix.mulRow(rowBelow + 1, newCoeff);

            // ... and update right-hand side
        //    m_rhs[rowBelow + 1] *= newCoeff;

            print();

            // subtract modified row from first row, result replaces current row ...
            m_matrix.subtractRowFromRow(rowBelow + 1, dim);

            // ... and update right-hand side
        //    m_rhs[rowBelow + 1] = m_rhs[rowBelow + 1] - m_rhs[dim];
            print();

            std::println("--------------------");
        }
    }


    //// i ist IMMER groesser Null ?!?!?!?!

    //for (std::size_t i{ m_dim - 1 }, j{ m_dim - 1 }; i >= 0; --i, --j)
    //{
    //    double result = m_rhs[i] / m_matrix.at(i, j);
    //    m_solution[i] = result;

    //    // die gefunden Lösung einsetzen in allen Zeilen , die darüber liegen (o .. i) 
    //    // und durch Subtraktion auf die rechte Seite bringen
    //    for (int k = 0; k <= i; ++k)
    //    {
    //        m_rhs[k] -= m_matrix.at(k,i) * result;

    //        m_matrix.at(k, i) = 0.0;
    //    }
    //}

    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        // double result = m_rhs[i-1] / m_matrix.at(i - 1, j - 1);
        
        double result = m_matrix.at(i - 1, i) / m_matrix.at(i - 1, j - 1);

        m_solution[i - 1] = result;

        // die gefunden Lösung einsetzen in allen Zeilen , die darüber liegen (o .. i) 
        // und durch Subtraktion auf die rechte Seite bringen
        for (std::size_t k = 0; k != i; ++k)
        {
          //  m_rhs[k] -= m_matrix.at(k, i-1) * result;
            m_matrix.at(k, i) -= m_matrix.at(k, i - 1) * result;

            m_matrix.at(k, i-1) = 0.0;
        }
    }

    // now apply back substitution to solve the linear equation system

    return true;   // hmm, das ist noch zu klären ....
}


// =====================================================================================
// End-of-File
// =====================================================================================
