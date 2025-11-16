// =====================================================================================
// Matrix.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"

#include <cstddef>
#include <initializer_list>
//#include <memory>
#include <vector>

template <typename T>
    requires FloatNumber<T>
class Matrix
{
protected:
    std::size_t    m_rows;
    std::size_t    m_cols;
    std::vector<T> m_values;

public:
    // c'tors
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);

    // getter/setter   
    std::size_t rows    () const;
    std::size_t cols    () const;

    void elements       (std::initializer_list<T> values);
    void elements       (std::initializer_list<std::initializer_list<T>> values);

    // accessing matrix elements
    T& at               (std::size_t row, std::size_t col);
    const T& at         (std::size_t row, std::size_t col) const;

    T& operator()       (size_t row, size_t col);
    const T& operator() (size_t row, size_t col) const;

    // public interface
    Matrix transpose    () const;
    Matrix add          (const Matrix& other) const;
    Matrix sub          (const Matrix& other) const;
    Matrix mul          (const Matrix& other) const;
    void   print        () const;

    // Fehlt: Methode fill ... mit einem konstanten Wert vorbelegen ....

    // operators
    Matrix operator+    (const Matrix& other) const;
    Matrix operator-    (const Matrix& other) const;
    Matrix operator*    (const Matrix& other) const;

    Matrix& operator+=  (const Matrix& other);
    Matrix& operator-=  (const Matrix& other);
    Matrix& operator*=  (const Matrix& other);

private:
   // void mulRow         (std::size_t row, T value);   // Hmmm, wozu habe ich diese Methode ....

public:
    // helper methods for forward elimination
    void swapRows(std::size_t row1, std::size_t row2);
    void subtractRow(T factor, std::size_t source, std::size_t target);
};

// =====================================================================================
// End-of-File
// =====================================================================================
