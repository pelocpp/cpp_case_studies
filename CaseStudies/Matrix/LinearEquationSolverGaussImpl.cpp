// =====================================================================================
// LinearEquationSolverGaussImpl.cpp
// =====================================================================================

#include "LinearEquationSolverGauss.h"

#include <cmath> 
#include <numeric>
#include <print>
#include <stdexcept>
#include <utility> 
#include <vector> 

// =====================================================================================
// c'tors

template <typename T>
    requires FloatNumber<T>
LinearEquationSolverGauss<T>::LinearEquationSolverGauss() : m_dim{} {}

// =====================================================================================
// getter/setter

template <typename T>
    requires FloatNumber<T>
std::size_t LinearEquationSolverGauss<T>::dimension() const
{
    return m_dim;
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverGauss<T>::setEquation(
    std::size_t dim,
    std::initializer_list<std::initializer_list<T>> values
)
{
    m_dim = dim;
    m_matrix = Matrix<T>{ m_dim, m_dim + 1 };
    m_matrix.elements(values);
}

template <typename T>
    requires FloatNumber<T>
const Vector<T>& LinearEquationSolverGauss<T>::solution() const
{
    return m_solution; 
}

// =====================================================================================
// public interface

template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolverGauss<T>::eliminateForward()
{
    std::println("Forward Elimination:");

    // forward elimination, create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        std::println("Eliminating column {}:", k);

        if (m_matrix.at(k, k) == 0.0) {
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);

            std::println("Transformed row {}:", rowBelow);
            print();
        }
    }

    std::println("Forward Elimination Done.");

    return true;
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverGauss<T>::substituteBack()
{
    // apply back substitution to solve the linear equation system
    m_solution = Vector<T>(m_dim);

    for (std::size_t i{ m_dim }, j{ m_dim }; i != 0; --i, --j)
    {
        T result = m_matrix.at(i - 1, m_dim) / m_matrix.at(i - 1, j - 1);
        m_solution[i - 1] = result;

        // substitute the value into all the equation lines above,
        // move the calculated values by subtraction to the right side
        for (std::size_t k{}; k != i - 1; ++k)
        {
            m_matrix.at(k, m_dim) -= m_matrix.at(k, i - 1) * result;
            m_matrix.at(k, i - 1) = 0.0;
        }
    }
}
























template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolverGauss<T>::eliminateForwardPivot()
{
    return false;
}

template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolverGauss<T>::eliminateForwardPivotPermutation()
{
    return false;
}

template <typename T>
    requires FloatNumber<T>
bool LinearEquationSolverGauss<T>::solve_01_simple()
{
    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        if (m_matrix.at(k, k) == 0.0) {
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>(m_dim);
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
bool LinearEquationSolverGauss<T>::solve_02_pivot()
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

        if (m_matrix.at(k, k) == 0.0) {
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);
        }
    }

    // now apply back substitution to solve the linear equation system
    m_solution = Vector<T>(m_dim);
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
bool LinearEquationSolverGauss<T>::solve_03_permutation_vector()
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

        if (m_matrix.at(perms[k], k) == 0.0) {
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
    m_solution = Vector<T>(m_dim);
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

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverGauss<T>::print() const
{
    for (size_t row{}; row != m_dim; ++row) {
        size_t col{};
        for (; col != m_dim; ++col) {
            std::print("{:10.4g}", m_matrix.at(row, col));
        }
        std::println(" | {:10.4g}", m_matrix.at(row, col));
    }
    std::println();
}

// =====================================================================================

// explicit template instantiations
template class LinearEquationSolverGauss<float>;
template class LinearEquationSolverGauss<double>;
template class LinearEquationSolverGauss<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
