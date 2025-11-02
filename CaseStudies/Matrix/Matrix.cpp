// =====================================================================================
// Matrix.cpp
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

#include <exception>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <print>
#include <span>

class Matrix
{
protected:
    std::size_t m_rows;
    std::size_t m_cols;

    std::shared_ptr<double[]> m_values;

public:
    // c'tors
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::size_t rows, std::size_t cols, std::initializer_list<double> values);
    Matrix(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<double>> values);

    // getter
    std::size_t rows() const { return m_rows; }
    std::size_t cols() const { return m_cols; }

    // public interface
    void print(); 
};

Matrix::Matrix() : m_rows{}, m_cols{}, m_values{} {}

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : m_rows{ rows }, m_cols{ cols } 
{
    m_values = std::make_shared<double[]>(m_rows * m_cols);

    // TODO: Ist der Speicher Null ????
}

Matrix::Matrix(std::size_t rows, std::size_t cols, std::initializer_list<double> values)
    : m_rows{ rows }, m_cols{ cols }
{
    if (m_rows * m_cols != values.size()) {
        throw std::invalid_argument("Wrong number of values!");
    }

    m_values = std::make_shared<double[]>(m_rows * m_cols);

    std::copy(
        values.begin(),
        values.end(),
        m_values.get()
    );
}

Matrix::Matrix(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<double>> values)
    : m_rows{ rows }, m_cols{ cols }
{
    if (m_rows != values.size()) {
        throw std::invalid_argument("Wrong number of rows!");
    }
        
    m_values = std::make_shared<double[]>(m_rows * m_cols);

    double* last{ m_values.get() };

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

void Matrix::print()
{
    // to be Done: Überladen von std::format // print a la C++ 23

    std::span<double> sp{ m_values.get(), m_rows * m_cols};

    for (int col = 0;  auto elem : sp) {

        std::print("{:3}", elem);

        ++col;
        if (col % m_cols == 0) {
            std::println();
        }
    }
}

void test_01() {

    Matrix matrix{ 3, 3 };
    matrix.print();

    Matrix matrix2{ 3, 3,  { 1, 2, 3 ,4 , 5, 6, 7, 8, 9 } };
    matrix2.print();

    Matrix matrix3{ 2, 3,  { 1, 2, 3 ,4 , 5, 6 } };
    matrix3.print();
}

void test_02() {

    Matrix matrix2{ 3, 3,  { { 1, 2, 3 } , { 4, 5, 6 } } };
    matrix2.print();

}

void test_03    () {


    double* d1 =  new double[10];
    double* d2 = new double[10] {};

}

// =====================================================================================
// End-of-File
// =====================================================================================
