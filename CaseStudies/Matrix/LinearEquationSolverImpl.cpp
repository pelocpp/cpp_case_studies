// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <print>
#include <stdexcept> 

// =====================================================================================

template <typename T>
LinearEquationSolver<T>::LinearEquationSolver() : m_dim{} {}

//void LinearEquationSolver::setDimension(std::size_t dim)
//{
//    m_dim = dim;
//}

template <typename T>
std::size_t LinearEquationSolver<T>::dimension() const
{
    return m_dim;
}

template <typename T>
void LinearEquationSolver<T>::setEquation(std::size_t dim, std::initializer_list<std::initializer_list<T>> values)
{
    m_dim = dim;
    m_matrix = Matrix<T>{ m_dim, m_dim + 1, values };
}

template <typename T>
const Vector<T>& LinearEquationSolver<T>::solution() const
{
    return m_solution; 
}

template <typename T>
void LinearEquationSolver<T>::print() const
{
    for (size_t row{}; row != m_dim; ++row) {
        size_t col{};
        for (; col != m_dim; ++col) {
            std::print("{:10.2g}", m_matrix.at(row,col));
        }
        std::println(" | {:10.2g}", m_matrix.at(row, col));
    }
    std::println();
}


template <typename T>
bool LinearEquationSolver<T>::solve()
{
    // wenn 1-dimensional ... Sonderbehanldung

    // mehr als eine Zeile ....


    // forward elimination to create a upper right triangle matrix
    for (std::size_t dim{}; dim != m_dim - 1; ++dim) {

        for (std::size_t rowBelow{ dim }; rowBelow != m_dim - 1; ++rowBelow) {

            // eliminate row
            T coeff1 = m_matrix.at(dim, dim);
            T coeff2 = m_matrix.at(rowBelow + 1, dim);

            // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            if (coeff2 == 0.0) {
                continue;
            }

            T newCoeff = coeff1 / coeff2;

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

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        std::println(">>>>>>>>>>>>");
        print();
        std::println("<<<<<<<<<<<<");

        T result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // die gefunden Lösung einsetzen in allen Zeilen , die darüber liegen (o .. i) 
        // und durch Subtraktion auf die rechte Seite bringen
        for (std::size_t k = 0; k != i - 1; ++k)
        {
            // original
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;

            //T xxx = m_matrix.at(k, i - 1);
            //xxx = xxx * result;
            //m_matrix.at(k, m_dim) -= xxx;

            m_matrix.at(k, i-1) = 0.0;

            //std::println(">>>>>>>>>>>>");
            //print();
            //std::println("<<<<<<<<<<<<");
        }
    }

    return true;   // hmm, das ist noch zu klären ....
}

// =====================================================================================

// explicit template instantiations
template class LinearEquationSolver<float>;
template class LinearEquationSolver<double>;
template class LinearEquationSolver<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
