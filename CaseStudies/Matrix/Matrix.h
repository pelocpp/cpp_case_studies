// =====================================================================================
// Matrix.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"

#include <cstddef>
#include <initializer_list>
#include <memory>

template <typename T>
    requires FloatNumber<T>
class Matrix
{
protected:
    std::size_t m_rows;
    std::size_t m_cols;
    std::shared_ptr<T[]> m_values;

public:
    // c'tors
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::size_t rows, std::size_t cols, std::initializer_list<T> values);
    Matrix(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<T>> values);

    // getter   
    std::size_t rows() const { return m_rows; }
    std::size_t cols() const { return m_cols; }


    // accessing matrix elements

    T& at(std::size_t row, std::size_t col);
    const T& at(std::size_t row, std::size_t col) const;

    void mulRow(std::size_t row, T value);

    // source = row to modify, target = row to subtract
    void subtractRowFromRow(std::size_t source, std::size_t target);

    // public interface

    Matrix transpose() const;
    Matrix add(const Matrix& other) const;
    Matrix sub(const Matrix& other) const;
    Matrix mul(const Matrix& other) const;
    void print() const;
};

// =====================================================================================
// End-of-File
// =====================================================================================
