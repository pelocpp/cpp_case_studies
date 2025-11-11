// =====================================================================================
// LinearEquationSolverImpl.cpp
// =====================================================================================

#include "LinearEquationSolver.h"

#include <cmath> 
#include <print>
#include <stdexcept>
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
    std::println(">>>>>>>>>>>");
    print();
    std::println(">>>>>>>>>>>");

    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        if (m_matrix.at(k, k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
            return false;
        }

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            m_matrix.subtractRow(factor, k, rowBelow);

            std::println("----------");
            print();
            std::println("----------");
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

            // TEST
            T elem1 = m_matrix.at(pivot, k);

            if (std::fabs(elem) > std::fabs(m_matrix.at(pivot,k))) {
                pivot = row;
            };
        }

        std::println("pivot: {}", pivot);
        m_matrix.swapRows(k, pivot);

        std::println(">>>>>>>>>>>");
        print();
        std::println(">>>>>>>>>>>");

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            std::println("factor: {}", factor);
            m_matrix.subtractRow(factor, k, rowBelow);

            std::println("----------");
            print();
            std::println("----------");
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
   // size_t perms[3] = { 0, 1, 2};

    std::vector<std::size_t> perms{ 0, 1, 2 };


    // forward elimination to create an upper triangular matrix
    for (std::size_t k{}; k != m_dim - 1; ++k) {

        std::println(">>>>>>>>>>>>");
        print();
        std::println("<<<<<<<<<<<<");

        // search pivot element (largest coefficient in rows k,..., m_dim-1)
        std::size_t pivot{ k };
        for (std::size_t row{ k + 1 }; row != m_dim; ++row) {

            T elem = m_matrix.at(row, k);
            std::println("row {}: {}", row, elem);

            // TEST
            T elem1 = m_matrix.at(pivot, k);

            if (std::fabs(elem) > std::fabs(m_matrix.at(pivot, k))) {
                pivot = row;
            };
        }

        std::println("pivot {}", pivot);

        // just swap indices, not rows
        // TODO: Das muss mit std::spap gehen ....
        size_t tmp = perms[k];
        perms[k] = perms[pivot];
        perms[pivot] = tmp;

        
        // SO MACHT DAS VERSION 2 !=!=!=!=
        // create a zero value in column 'k' in all rows beneath
       // for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {
        
        // create a zero value in column 'k' in all rows beneath
        //for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim - 1; ++rowBelow) {

        //    // eliminate rows
        //    T coeff1 = m_matrix.at(perms[k], k);
        //    T coeff2 = m_matrix.at(perms[rowBelow], k);

        //    // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
        //    if (coeff2 == 0.0) {
        //        continue;
        //    }

        //    T newCoeff{ coeff1 / coeff2 };
        //    std::println("factor: {}", newCoeff);

        //    // multiply row below current row with this coeccicient
        //    m_matrix.mulRow(perms[rowBelow] + 1, newCoeff);

        //    // subtract modified row from first row, result replaces current row ...
        //    m_matrix.subtractRowFromRow(perms[rowBelow] + 1, k);

        //    std::println("############");
        //    print();
        //    std::println("############");
        //}

        // create a zero value in column 'k' in all rows beneath
        for (std::size_t rowBelow{ k + 1 }; rowBelow != m_dim; ++rowBelow) {

            // T factor{ m_matrix.at(rowBelow, k) / m_matrix.at(k, k) };
            T factor{ m_matrix.at(perms[rowBelow], k) / m_matrix.at(perms[k], k) };
            std::println("factor: {}", factor);
            //m_matrix.subtractRow(factor, perms[k], perms[rowBelow]);

            for (std::size_t j{ k }; j != m_matrix.cols(); ++j) {

                m_matrix.at(perms[rowBelow], j) -= factor * m_matrix.at(perms[k], j);
            }

            std::println("----------");
            print();
            std::println("----------");
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
