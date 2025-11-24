// =====================================================================================
// MatrixDeterminant.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Matrix.h"

#include <cstddef>
#include <stdexcept>

// =====================================================================================
// Laplace Expansion Theorem

// See here
// https://www.bigdev.de/2013/04/tutorial-determinant-in-java.html

static auto constexpr powerOfMinusOne = [](std::size_t exp) {

    auto result = -1;
    for (size_t i{ 1 }; i != exp; ++i) {
        result *= -1;
    }
    return result;
};

///**
//  * Computing the minor of the matrix m without the i-th row and the j-th
//  * column
//  *
//  * @param m input matrix
//  * @param i removing the i-th row of m
//  * @param j removing the j-th column of m
//  * @return minor of m
//  */
//private static double[][] minor(final double[][] m, final int i, final int j) {

template <typename T>
Matrix<T> minor(Matrix<T> m, std::size_t row, std::size_t col) requires FloatNumber<T>
{
    Matrix<T> result{ m.rows() - 1, m.cols() - 1 };

    std::size_t ri{};

    for (std::size_t r{}; r != m.rows(); ++r) {

        if (r == row) {
            continue;
        }

        std::size_t ci{};

        for (std::size_t c{}; c != m.cols(); ++c) {

            if (c == col) {
                continue;
            }

            T value = m(r, c);
            result(ri, ci) = value;

            ++ci;
        }
        ++ri;
    }

    return result;
}

template <typename T>
T determinant(Matrix<T> m) requires FloatNumber<T>
{
    if (m.cols() != m.rows()) {
        throw std::invalid_argument("Different number of rows and columns!");
    }

    std::size_t n{ m.rows() };
    if (n == 1) {
        return m.at(0,0);
    }
    else {
        T det{};
        for (std::size_t j{}; j != n; ++j) {

            det += powerOfMinusOne(j) * m(0, j) * determinant(minor(m, 0, j));
        }
        return det;
    }

    return T{};
}

// =====================================================================================

extern template Matrix<float>       minor<float>       (Matrix<float>, std::size_t row, std::size_t col);
extern template Matrix<double>      minor<double>      (Matrix<double>, std::size_t row, std::size_t col);
extern template Matrix<long double> minor<long double> (Matrix<long double>, std::size_t row, std::size_t col);

extern template float       determinant<float>         (Matrix<float>);
extern template double      determinant<double>        (Matrix<double>);
extern template long double determinant<long double>   (Matrix<long double>);

// =====================================================================================
// End-of-File
// =====================================================================================
