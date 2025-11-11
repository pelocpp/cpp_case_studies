// =====================================================================================
// MatrixImpl.cpp
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "Matrix.h"

#include <print>
#include <span>
#include <stdexcept>    

template <typename T>
    requires FloatNumber<T>
Matrix<T>::Matrix() : m_rows{}, m_cols{}, m_values{} {}

template <typename T>
    requires FloatNumber<T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols)
    : m_rows{ rows }, m_cols{ cols }
{
    m_values = std::make_shared<T[]>(m_rows * m_cols);
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::elements(std::initializer_list<T> values)
{
    if (m_rows * m_cols != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    std::copy(
        values.begin(),
        values.end(),
        m_values.get()
    );
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::elements(std::initializer_list<std::initializer_list<T>> values)
{
    if (m_rows != values.size()) {
        throw std::invalid_argument("Wrong number of rows!");
    }

    T* last{ m_values.get() };

    for (auto row : values) {

        if (row.size() != m_cols) {
            throw std::invalid_argument("Wrong number of columns!");
        }

        last = std::copy(
            row.begin(),
            row.end(),
            last
        );
    }
}

template <typename T>
    requires FloatNumber<T>
T& Matrix<T>::at(std::size_t row, std::size_t col)
{
    // https://stackoverflow.com/questions/2673508/correct-usages-of-const-cast

    // or Scott Meyers
    return const_cast<T&>(static_cast<const Matrix&>(*this).at(row, col));
}

template <typename T>
    requires FloatNumber<T>
const T& Matrix<T>::at(std::size_t row, std::size_t col) const
{
    if (row >= m_rows) {
        throw std::invalid_argument("Invalid row index!!");
    }

    if (col >= m_cols) {
        throw std::invalid_argument("Invalid col index!!");
    }

    // return m_values.get()[m_cols * row + col];
    return m_values[m_cols * row + col];
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::mulRow(std::size_t row, T value)
{
    for (int col{}; col != m_cols; ++col) {
        at(row, col) *= value;
    }
}


// source = row to modify, target = row to subtract
// void subtractRowFromRow(std::size_t source, std::size_t target);

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::subtractRowFromRow(std::size_t source, std::size_t target)
{
    for (int col{}; col != m_cols; ++col) {

         at(source, col) = at(source, col) - at(target, col);   // geht
        // oder
        //at(source, col) =  at(target, col) - at(source, col);     // geht
    }
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> result{ m_cols, m_rows };

    for (int row{}; row != m_rows; ++row) {

        for (int col{}; col != m_cols; ++col) {

            auto value{ m_values[row * m_cols + col] };
            result.at(col, row) = value;
        }
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::add(const Matrix& other) const
{
    Matrix<T> result{ m_rows, m_cols };

    for (std::size_t i{}; i != m_rows * m_cols; ++i) {

        result.m_values[i] = m_values[i] + other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::sub(const Matrix& other) const
{
    Matrix<T> result{ m_rows, m_cols };

    for (std::size_t i{}; i != m_rows * m_cols; ++i) {

        result.m_values[i] = m_values[i] - other.m_values[i];
    }

    return result;
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::mul(const Matrix& other) const
{
    if (m_cols != other.m_rows) {
        throw std::invalid_argument("Invalid matrix dimensions!");
    }

    Matrix<T> result{ m_rows, other.m_cols };

    for (std::size_t row{}; row != m_rows; ++row) {

        for (std::size_t col{}; col != other.m_cols; ++col) {

            T value{};

            for (std::size_t k{}; k != m_cols; ++k) {
                value += at(row, k) * other.at(k,col);
            }

            result.at(row, col) = value;
        }
    }

    return result;
}



template <typename T>
    requires FloatNumber<T>
void Matrix<T>::swapRows(std::size_t row1, std::size_t row2)
{
    if (row1 == row2) {
        return; // nothing to do
    }

    for (std::size_t k{}; k != m_cols; ++k) {

        T tmp = at(row1, k);
        at(row1, k) = at(row2, k);
        at(row2, k) = tmp;
    }
}


template <typename T>
    requires FloatNumber<T>
void Matrix<T>::print() const
{
    // to be Done: Überladen von std::format // print a la C++ 23

    if (m_values == nullptr) {
        return;
    }

    std::span<T> sp{ m_values.get(), m_rows * m_cols };

    for (std::size_t col{}; auto elem : sp) {

        std::print("{:6}", elem);

        ++col;
        if (col % m_cols == 0) {
            std::println();
        }
    }
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::subtractRow(T factor, std::size_t source, std::size_t target)
{
    for (std::size_t j{ source }; j != m_cols; ++j) {
        at(target, j) -= factor * at(source,j);
    }
}

// =====================================================================================

// explicit template instantiations
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;

// =====================================================================================
// End-of-File
// =====================================================================================

