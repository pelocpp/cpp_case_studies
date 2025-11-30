// =====================================================================================
// MatrixDeterminantImpl.cpp
// =====================================================================================

#include "MatrixDeterminant.h"

#include <print>

// ist hier beschrieben
// https://www.youtube.com/watch?v=pyiKhRmvMF4

// =====================================================================================

static auto constexpr powerOfMinusOne = [] (std::size_t exp) -> int {

    if (exp == 0) {
        return 1;
    }
    else {
        auto result{ -1 };
        for (size_t i{ 1 }; i != exp; ++i) {
            result *= -1;
        }
        return result;
    }
};

// =====================================================================================
// c'tor(s)

template <typename T>
    requires FloatNumber<T>
MatrixDeterminant<T>::MatrixDeterminant(const Matrix<T> matrix)
    : m_matrix{ matrix }
{}

// =====================================================================================
// getter/setter

template <typename T>
    requires FloatNumber<T>
void MatrixDeterminant<T>::setMatrix(const Matrix<T> matrix)
{
    m_matrix = matrix;
}

// =====================================================================================
// public interface

template <typename T>
    requires FloatNumber<T>
T MatrixDeterminant<T>::determinant() const
{
    if (m_matrix.cols() != m_matrix.rows()) {
        throw std::invalid_argument("Different number of rows and columns!");
    }
    
    std::size_t n{ m_matrix.rows() };
    if (n == 1) {
        return m_matrix.at(0,0);
    }
    else {
        T det{};
        for (std::size_t j{}; j != n; ++j) {

            MatrixDeterminant<T> md{ MatrixDeterminant<T>::minor(m_matrix, 0, j) };
            det += powerOfMinusOne(j) * m_matrix(0, j) * md.determinant();
        }
        return det;
    }
    
    return T{};
}

/**
  * Computing the determinant of a 3*3 matrix according to the rule of Sarrus
  * 
  * @return       determinant of matrix
  */
template <typename T>
    requires FloatNumber<T>
T MatrixDeterminant<T>::determinant_sarrus() const
{
    if (m_matrix.rows() != 3 || m_matrix.cols() != 3) {
        throw std::invalid_argument("Expected 3*3 matrix!");
    }

    T d{
        m_matrix.at(0,0) * m_matrix.at(1, 1) * m_matrix.at(2, 2) +
        m_matrix.at(0,1) * m_matrix.at(1, 2) * m_matrix.at(2, 0) +
        m_matrix.at(0,2) * m_matrix.at(1, 0) * m_matrix.at(2, 1) -
        m_matrix.at(0,2) * m_matrix.at(1, 1) * m_matrix.at(2, 0) -
        m_matrix.at(0,0) * m_matrix.at(1, 2) * m_matrix.at(2, 1) -
        m_matrix.at(0,1) * m_matrix.at(1, 0) * m_matrix.at(2, 2)
    };

    return d;
}

/**
  * Computing the minor of the matrix m without the i-th row and the j-th column
  *
  * @param matrix input matrix
  * @param i      removing the i-th row of m
  * @param j      removing the j-th column of m
  * @return       minor of matrix
  */
template <typename T>
    requires FloatNumber<T>
Matrix<T> MatrixDeterminant<T>::minor(const Matrix<T>& matrix, std::size_t row, std::size_t col)
{
    Matrix<T> result{ matrix.rows() - 1, matrix.cols() - 1 };

    std::size_t ri{};

    for (std::size_t r{}; r != matrix.rows(); ++r) {

        if (r == row) {
            continue;
        }

        std::size_t ci{};

        for (std::size_t c{}; c != matrix.cols(); ++c) {

            if (c == col) {
                continue;
            }

            T value = matrix(r, c);
            result(ri, ci) = value;

            ++ci;
        }
        ++ri;
    }

    return result;
}

// =====================================================================================

// explicit template instantiations
template class MatrixDeterminant<float>;
template class MatrixDeterminant<double>;
template class MatrixDeterminant<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================
