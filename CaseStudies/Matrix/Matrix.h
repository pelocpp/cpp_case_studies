// =====================================================================================
// Matrix.h
// =====================================================================================

#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>

template <typename T>
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
    //Matrix(std::size_t rows, std::size_t cols, std::initializer_list<T> values);
    //Matrix(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<T>> values);

    //// getter   
    //std::size_t rows() const { return m_rows; }
    //std::size_t cols() const { return m_cols; }

    //// public interface
    void print() const;
    //T& at(std::size_t row, std::size_t col);  // TODO: die 2. Version für const !!!
    //const T& at(std::size_t row, std::size_t col) const;

    //Matrix<T> transpose() const;
    //Matrix<T> add(const Matrix& other) const;        // ??? Muss das heißen   
    //Matrix<T> sub(const Matrix& other) const;
    //Matrix<T> mul(const Matrix& other) const;
};

// =====================================================================================
// End-of-File
// =====================================================================================

