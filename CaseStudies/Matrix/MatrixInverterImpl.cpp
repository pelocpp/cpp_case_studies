// =====================================================================================
// MatrixInverterImpl.cpp
// =====================================================================================

#include "Vector.h"
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
bool MatrixInverter<T>::invert()
{
    // ========================================
    Matrix<T> lower{ 3, 3 };
    lower.elements({ { 1.0, 0.0, 0.0 } , { 2.0, 1.0, 0.0 } , { -1.0, -1.0, 1.0 } });
    m_lower = lower;

    Matrix<T> upper{ 3, 3 };
    upper.elements({ { 2.0, 1.0, 1.0 } , { 0.0, -8.0, -2.0 } , { 0.0, 0.0, 1.0 } });
    m_upper = upper;
    // ========================================


    std::size_t n = m_matrix.rows();  // count of rows (or cols)

    Matrix<T> result{ n , n };
   
    for (std::size_t i{}; i != n; ++i) {

        // unit vector with a 1 at the i-th position
        Vector<T> e{n};
        e[i] = T{ 1.0 };

        // L * y = e
        Vector<T> y = forwardSubstitution(e);

        // U * x = y
        Vector<T> x = backwardSubstitution(y);

        // storing x at the i-th position in the inverse matrix 
        for (std::size_t row{}; row != n; ++row) {
            result(row,i) = x[row];
        }
    }

    result.print();

    return true;
}


template <typename T>
    requires FloatNumber<T>
Vector<T> MatrixInverter<T>::forwardSubstitution(const Vector<T>& b)
{
    // -------------------------------
    // forward substitution: L * y = b

    Vector<T> y{ b.dimension() };

    for (std::size_t i{}; i != b.dimension(); ++i) {

        T sum{ b[i] };
        for (std::size_t j{}; j != i; ++j) {
            sum -= m_lower(i, j) * y[j];
        }
        y[i] = sum / m_lower(i, i);
    }

    return y;
}

template <typename T>
    requires FloatNumber<T>
Vector<T> MatrixInverter<T>::backwardSubstitution(const Vector<T>& y)
{
    // --------------------------------
    // backward substitution: U * x = y

    std::size_t dimension{ y.dimension() };

    Vector<T> x{ dimension };

    // Note: reverse iteration with an unsigned loop variable
    for (std::size_t i = dimension; i-- > 0; ) {

        T sum{ y[i] };
        for (std::size_t j = i + 1; j != dimension; ++j) {
            sum -= m_upper(i, j) * x[j];
        }
        x[i] = sum / m_upper(i, i);
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
