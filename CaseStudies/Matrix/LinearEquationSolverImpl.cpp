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

std::size_t LinearEquationSolver::dimension() const
{
    return m_dim;
}

void LinearEquationSolver::setEquation(std::size_t dim, std::initializer_list<std::initializer_list<double>> values)
{
    m_dim = dim;
    m_matrix = Matrix<double>{ dim, dim + 1, values };
}

const Vector<double>& LinearEquationSolver::solution() const 
{
    return m_solution; 
}

void LinearEquationSolver::print() const
{
    for (size_t row{}; row != m_dim; ++row) {
        size_t col{};
        for (; col != m_dim; ++col) {
            std::print("{:4g}", m_matrix.at(row,col));
        }
        std::println(" | {:4g}", m_matrix.at(row, col));
    }
    std::println();
}


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

            // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            if (coeff2 == 0.0) {
                continue;
            }

            double newCoeff = coeff1 / coeff2;

            // multiply row below current row with this coeccicient
            m_matrix.mulRow(rowBelow + 1, newCoeff);

            std::println(">>>>>>>>>>>>");
            print();
            std::println("<<<<<<<<<<<<");

            // subtract modified row from first row, result replaces current row ...
            m_matrix.subtractRowFromRow(rowBelow + 1, dim);

            std::println(">>>>>>>>>>>>");
            print();
            std::println("<<<<<<<<<<<<");
        }
    }

    m_solution = Vector<double>{ m_dim };

    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        std::println(">>>>>>>>>>>>");
        print();
        std::println("<<<<<<<<<<<<");

        double result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // die gefunden Lösung einsetzen in allen Zeilen , die darüber liegen (o .. i) 
        // und durch Subtraktion auf die rechte Seite bringen
        for (std::size_t k = 0; k != i - 1; ++k)
        {
            // original
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;

            //double xxx = m_matrix.at(k, i - 1);
            //xxx = xxx * result;
            //m_matrix.at(k, m_dim) -= xxx;

            m_matrix.at(k, i-1) = 0.0;

            //std::println(">>>>>>>>>>>>");
            //print();
            //std::println("<<<<<<<<<<<<");
        }
    }

    // now apply back substitution to solve the linear equation system

   // m_solution.print();

    return true;   // hmm, das ist noch zu klären ....
}


// =====================================================================================
// End-of-File
// =====================================================================================
