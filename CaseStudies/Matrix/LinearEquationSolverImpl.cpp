// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <cmath> 
#include <print>
#include <stdexcept> 

// =====================================================================================

template <typename T>
    requires FloatNumber<T>
LinearEquationSolver<T>::LinearEquationSolver() : m_dim{} {}

template <typename T>
    requires FloatNumber<T>
std::size_t LinearEquationSolver<T>::dimension() const
{
    return m_dim;
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolver<T>::equation(std::size_t dim, std::initializer_list<std::initializer_list<T>> values)
{
    m_dim = dim;
    m_matrix = Matrix<T>{ m_dim, m_dim + 1 };
    m_matrix.elements(values);
}

template <typename T>
    requires FloatNumber<T>
const Vector<T>& LinearEquationSolver<T>::solution() const
{
    return m_solution; 
}

template <typename T>
    requires FloatNumber<T>
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
    requires FloatNumber<T>
void LinearEquationSolver<T>::solve_01_simple()
{
    // forward elimination to create a upper right triangle matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        if (m_matrix.at(k, k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            continue;  
        }

        // Remove all rows below
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };

            m_matrix.subtractRow(factor, k, rowBelow);

            //// multiply row below current row with this coeccicient
            //m_matrix.mulRow(rowBelow + 1, newCoeff);

            std::println(">>>>>>>>>>>>");
            print();
            std::println("<<<<<<<<<<<<");

            //// subtract modified row from first row, result replaces current row ...
            //m_matrix.subtractRowFromRow(rowBelow + 1, k);

            //std::println(">>>>>>>>>>>>");
            //print();
            //std::println("<<<<<<<<<<<<");
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // and move the calculated values ??by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            // original
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;
            m_matrix.at(k, i - 1) = 0.0;
        }
    }
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolver<T>::solve_02_pivot()
{
    // forward elimination to create a upper right triangle matrix
    for (std::size_t dim{}; dim != m_dim - 1; ++dim) {

        // search pivot element
        std::size_t maxRow{ dim };
        for (std::size_t row{ dim  }; row != m_dim; ++row) {
        
            T elem = m_matrix.at(row, dim);
            std::println("row {}: {}", row, elem);

            if (std::fabs(elem) > std::fabs(m_matrix.at(maxRow,dim))) {
                maxRow = row;
            };
        }

        std::println("maxRow {}", maxRow);
        m_matrix.swapRows(dim, maxRow);

        // Wieso steht hier nicht std::size_t rowBelow{ dim + 1 } ???????????????????
        for (std::size_t rowBelow{ dim }; rowBelow != m_dim - 1; ++rowBelow) {

            // eliminate rows
            T coeff1 = m_matrix.at(dim, dim);
            T coeff2 = m_matrix.at(rowBelow + 1, dim);

            // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            if (coeff2 == 0.0) {
                continue;
            }

            T newCoeff{ coeff1 / coeff2 };

            // multiply row below current row with this coeccicient
            m_matrix.mulRow(rowBelow + 1, newCoeff);

            // subtract modified row from first row, result replaces current row ...
            m_matrix.subtractRowFromRow(rowBelow + 1, dim);

            std::println("############");
            print();
            std::println("############");
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // and move the calculated values ??by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            // original
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;
            m_matrix.at(k, i - 1) = 0.0;
        }
    }
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolver<T>::solve_03_permutation_vector()
{
    size_t perms[3] = { 0, 1, 2};

    // forward elimination to create a upper right triangle matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        std::println(">>>>>>>>>>>>");
        print();
        std::println("<<<<<<<<<<<<");

        // search pivot element
        std::size_t pivot{ k };
        T maxValue = m_matrix.at(perms[k], k);

        for (std::size_t i{ k + 1 }; i != m_dim; ++i) {

            // if (fabs(A[P[i]][k]) > maxVal) 
            if (std::fabs(m_matrix.at(perms[i], k)) > maxValue) {
                pivot = i;
            };
        }

        std::println("pivot {}", pivot);

        // just swap indices, not rows
        // TODO: Das muss mit std::spap gehen ....
        size_t tmp = perms[k];
        perms[k] = perms[pivot];
        perms[pivot] = tmp;

        // elimination
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim - 1; ++rowBelow) {

            // eliminate rows
            T coeff1 = m_matrix.at(perms[k], k);
            T coeff2 = m_matrix.at(perms[rowBelow] + 1, k);

            // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            if (coeff2 == 0.0) {
                continue;
            }

            T newCoeff{ coeff1 / coeff2 };

            // multiply row below current row with this coeccicient
            m_matrix.mulRow(perms[rowBelow] + 1, newCoeff);

            // subtract modified row from first row, result replaces current row ...
            m_matrix.subtractRowFromRow(perms[rowBelow] + 1, k);

            std::println("############");
            print();
            std::println("############");
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(perms[i - 1], m_dim) / m_matrix.at(perms[i - 1], j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // and move the calculated values ??by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            // original
            m_matrix.at(perms[k], m_dim) -= m_matrix.at(perms[k], i - 1) * result;
            m_matrix.at(perms[k], i - 1) = 0.0;
        }
    }
}

// =====================================================================================

// explicit template instantiations
template class LinearEquationSolver<float>;
template class LinearEquationSolver<double>;
template class LinearEquationSolver<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
