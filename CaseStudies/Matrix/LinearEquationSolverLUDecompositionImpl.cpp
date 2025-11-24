// =====================================================================================
// LinearEquationSolverLUDecompositionImpl.cpp
// =====================================================================================

#include "LU_Decomposition.h"
#include "LinearEquationSolverLUDecomposition.h"

//#include <cmath> 
//#include <numeric>
#include <print>
#include <stdexcept>
//#include <utility> 
//#include <vector> 

// =====================================================================================
// c'tors

template <typename T>
    requires FloatNumber<T>
LinearEquationSolverLUDecomposition<T>::LinearEquationSolverLUDecomposition() : m_dimension{} {}

template <typename T>
    requires FloatNumber<T>
LinearEquationSolverLUDecomposition<T>::LinearEquationSolverLUDecomposition(std::size_t dimension) 
    : m_dimension{ dimension } 
{}

// =====================================================================================
// getter/setter

template <typename T>
    requires FloatNumber<T>
std::size_t LinearEquationSolverLUDecomposition<T>::dimension() const
{
    return m_dimension;
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverLUDecomposition<T>::setEquation(
    std::initializer_list<std::initializer_list<T>> values
)
{
    m_matrix = Matrix<T>{ m_dimension, m_dimension };
    m_matrix.elements(values);
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverLUDecomposition<T>::setRightHandSide(std::initializer_list<T> rhs)
{
    if (rhs.size() != dimension()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    Vector<T> tmp{ rhs };

    m_rhs = tmp;
}

//template <typename T>
//    requires FloatNumber<T>
//void LinearEquationSolverLUDecomposition<T>::setRightHandSide(const Vector<T>& rhs)
//{
//    if (rhs.dimension() != dimension()) {
//        throw std::invalid_argument("Wrong number of values!");
//    }
//
//    m_rhs = rhs;
//}

template <typename T>
    requires FloatNumber<T>
const Vector<T>& LinearEquationSolverLUDecomposition<T>::solution() const
{
    return m_solution;
}

// =====================================================================================
// public interface

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverLUDecomposition<T>::solve()
{
    // need at first a LU decomposition of the matrix to invert
    LU_Decomposition<T> lu{ m_matrix };
    lu.decompose();

    const Matrix<T>& lower = lu.getLowerMatrix();
    const Matrix<T>& upper = lu.getUpperMatrix();

    Vector<T> result{ m_dimension };

    Vector<T> y = forwardSubstitution(lower, m_rhs);   // L * y = b
    Vector<T> x = backwardSubstitution(upper, y);      // U * x = y

    // Hmmm, jetzt müsste die Lösung in x stehen !!!

}

template <typename T>
    requires FloatNumber<T>
Vector<T> LinearEquationSolverLUDecomposition<T>::forwardSubstitution(const Matrix<T> lower, const Vector<T>& b) const
{
    Vector<T> y{ b.dimension() };

    for (std::size_t i{}; i != b.dimension(); ++i) {

        T sum{ b[i] };
        for (std::size_t j{}; j != i; ++j) {
            sum -= lower(i, j) * y[j];
        }
        y[i] = sum / lower(i, i);
    }

    return y;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> LinearEquationSolverLUDecomposition<T>::backwardSubstitution(const Matrix<T> upper, const Vector<T>& y) const
{
    std::size_t dimension{ y.dimension() };

    Vector<T> x{ dimension };

    // Note: reverse iteration with an unsigned loop variable
    for (std::size_t i = dimension; i-- > 0; ) {

        T sum{ y[i] };
        for (std::size_t j = i + 1; j != dimension; ++j) {
            sum -= upper(i, j) * x[j];
        }
        x[i] = sum / upper(i, i);
    }

    return x;
}

template <typename T>
    requires FloatNumber<T>
void LinearEquationSolverLUDecomposition<T>::print() const
{
    for (size_t row{}; row != m_dimension; ++row) {
        size_t col{};
        for (; col != m_dimension; ++col) {
            std::print("{:10.4g}", m_matrix.at(row, col));
        }
        std::println(" | {:10.4g}", m_matrix.at(row, col));
    }
    std::println();
}

// =====================================================================================

// explicit template instantiations
template class LinearEquationSolverLUDecomposition<float>;
template class LinearEquationSolverLUDecomposition<double>;
template class LinearEquationSolverLUDecomposition<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
