// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <cmath> 
#include <numeric>
#include <print>
#include <stdexcept>
#include <utility> 
#include <vector> 

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
bool LinearEquationSolver<T>::solve_01_simple()
{
    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        if (m_matrix.at(k, k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // and move the calculated values by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;
            m_matrix.at(k, i - 1) = 0.0;
        }
    }

    return true;
}

template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolver<T>::solve_02_pivot()
{
    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        // search pivot element (largest coefficient in rows k,..., m_dim-1)
        std::size_t pivot{ k };
        for (std::size_t row{ k + 1  }; row != m_dim; ++row) {
        
            T elem = m_matrix.at(row, k);
            std::println("row {}: {}", row, elem);

            if (std::fabs(elem) > std::fabs(m_matrix.at(pivot,k))) {
                pivot = row;
            };
        }

        std::println("pivot: {}", pivot);
        m_matrix.swapRows(k, pivot);

        if (m_matrix.at(k, k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);
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

    return true;
}

template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolver<T>::solve_03_permutation_vector()
{
    // create a permatations vector being intialized with 0, 1, 2, ...
    std::vector<std::size_t> perms(m_matrix.rows());
    std::iota(perms.begin(), perms.end(), 0);

    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        // search pivot element (largest coefficient in rows k,..., m_dim-1)
        std::size_t pivot{ k };
        for (std::size_t row{ k + 1 }; row != m_dim; ++row) {

            T elem = m_matrix.at(row, k);
            std::println("row {}: {}", row, elem);

            if (std::fabs(elem) > std::fabs(m_matrix.at(pivot, k))) {
                pivot = row;
            };
        }

        std::println("pivot {}", pivot);

        // just swap indices, not rows
        std::swap(perms[k], perms[pivot]);

        if (m_matrix.at(perms[k], k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(perms[rowBelow], k) / m_matrix.at(perms[k], k) };
            std::println("factor: {}", factor);

            //for (std::size_t j{ k }; j != m_matrix.cols(); ++j) {
            //    m_matrix.at(perms[rowBelow], j) -= factor * m_matrix.at(perms[k], j);
            //}

            // versus

            m_matrix.subtractRow(factor, perms[k], perms[rowBelow]);

            // Beachte: Beide Version sind jetzt indentisch -- natürlich ist das mit 'subtractRow' eleganter ....
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>{ m_dim };
    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(perms[i - 1], m_dim) / m_matrix.at(perms[i - 1], j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // and move the calculated values by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            // original
            m_matrix.at(perms[k], m_dim) -= m_matrix.at(perms[k], i - 1) * result;
            m_matrix.at(perms[k], i - 1) = 0.0;
        }
    }

    return true;
}

// =====================================================================================

// explicit template instantiations
template class LinearEquationSolver<float>;
template class LinearEquationSolver<double>;
template class LinearEquationSolver<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
