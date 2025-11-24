// =====================================================================================
// MatrixInverterImpl.cpp
// =====================================================================================

#include "Vector.h"
#include "LU_Decomposition.h"
#include "MatrixInverter.h"

#include <cstddef>
#include <stdexcept>

// getter/setter
template <typename T>
    requires FloatNumber<T>
void MatrixInverter<T>::set(const Matrix<T> matrix)
{
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("The matrix must be square!");
    }

    m_matrix = matrix;
}

// public interface
template <typename T>
    requires FloatNumber<T>
void MatrixInverter<T>::invert()
{
    // need at first a LU decomposition of the matrix to invert
    LU_Decomposition<T> lu{ m_matrix };
    lu.decompose();

    const Matrix<T>& lower = lu.getLowerMatrix();
    const Matrix<T>& upper = lu.getUpperMatrix();

    std::size_t n = m_matrix.rows();  // count of rows (or cols)
    Matrix<T> result{ n , n };   

    // now invert input matrix with forward and backward substitution
    for (std::size_t i{}; i != n; ++i) {

        // unit vector with a 1 at the i-th position
        Vector<T> e{n};
        e[i] = T{ 1.0 };

        Vector<T> y = forwardSubstitution(lower, e);   // L * y = e        
        Vector<T> x = backwardSubstitution(upper, y);  // U * x = y

        // storing x at the i-th position in the inverse matrix 
        for (std::size_t row{}; row != n; ++row) {
            result(row,i) = x[row];
        }
    }

    result.print();
}

template <typename T>
    requires FloatNumber<T>
Vector<T> MatrixInverter<T>::forwardSubstitution(const Matrix<T> lower, const Vector<T>& b) const
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
Vector<T> MatrixInverter<T>::backwardSubstitution(const Matrix<T> upper, const Vector<T>& y) const
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

// =====================================================================================

// explicit template instantiations
template class MatrixInverter<float>;
template class MatrixInverter<double>;
template class MatrixInverter<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
