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
    void print() const;
    double& at(std::size_t row, std::size_t col);  // TODO: die 2. Version für const !!!
    const double& at(std::size_t row, std::size_t col) const;
    Matrix transpose() const;

    Matrix add(const Matrix& other) const;
    Matrix sub(const Matrix& other) const;
    Matrix mul(const Matrix& other) const;
};

Matrix::Matrix() : m_rows{}, m_cols{}, m_values{} {}

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : m_rows{ rows }, m_cols{ cols } 
{
    m_values = std::make_shared<double[]>(m_rows * m_cols);

    // TODO: Ist der Speicher Null ???? Ja !!! Value-Initialize
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

void Matrix::print() const
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

double& Matrix::at(std::size_t row, std::size_t col)
{
    //if (row >= m_rows) {
    //    throw std::invalid_argument("Invalid row index!!");
    //}

    //if (col >= m_cols) {
    //    throw std::invalid_argument("Invalid col index!!");
    //}

    //return m_values.get()[m_cols * row + col];


    // https://stackoverflow.com/questions/2673508/correct-usages-of-const-cast



    // or Scott Meyers
    return const_cast<double&>(static_cast<const Matrix&>(*this).at(row, col));
}

const double& Matrix::at(std::size_t row, std::size_t col) const
{
    if (row >= m_rows) {
        throw std::invalid_argument("Invalid row index!!");
    }

    if (col >= m_cols) {
        throw std::invalid_argument("Invalid col index!!");
    }

    return m_values.get()[m_cols * row + col];
}


Matrix Matrix::transpose() const
{
    Matrix result{ m_cols, m_rows };

    for (int row{}; row != m_rows; ++row) {

        for (int col{}; col != m_cols; ++col) {

            auto value{ m_values[row * m_cols + col] };
            result.at(col, row) = value;
        }
    }

    return result;
}

Matrix Matrix::add(const Matrix& other) const
{
    Matrix result{ m_rows, m_cols };

    std::span<double> left{ m_values.get(), m_rows * m_cols };
    std::span<double> right{ other.m_values.get(), m_rows * m_cols };
    std::span<double> target{ result.m_values.get(), m_rows * m_cols };

    for (std::size_t i{}; i != m_rows * m_cols; ++i) {

        target[i] = left[i] + right[i];
    }

    return result;
}


Matrix Matrix::sub(const Matrix& other) const
{
    Matrix result{ m_rows, m_cols };

    std::span<double> left{ m_values.get(), m_rows * m_cols };
    std::span<double> right{ other.m_values.get(), m_rows * m_cols };
    std::span<double> target{ result.m_values.get(), m_rows * m_cols };

    for (std::size_t i{}; i != m_rows * m_cols; ++i) {

        target[i] = left[i] - right[i];
    }

    return result;
}

Matrix Matrix::mul(const Matrix& other) const
{
    if (m_cols != other.m_rows) {
        throw std::invalid_argument("Invalid matrix dimensions!");
    }

    Matrix result{ m_rows, other.m_cols };

    for (std::size_t row{}; row != m_rows; ++row) {

        for (std::size_t col{}; col != other.m_cols; ++col) {

            double value{};

            for (std::size_t k{}; k != m_cols; ++k) {
            
            
            
            }

        }
    }



    //std::span<double> left{ m_values.get(), m_rows * m_cols };
    //std::span<double> right{ other.m_values.get(), m_rows * m_cols };
    //std::span<double> target{ result.m_values.get(), m_rows * m_cols };

    //for (std::size_t i{}; i != m_rows * m_cols; ++i) {

    //    target[i] = left[i] - right[i];
    //}

    return result;
}

// ====================

void test_01() {

    Matrix matrix{ 3, 3 };
    matrix.print();

    Matrix matrix2{ 3, 3, { 1, 2, 3 ,4 , 5, 6, 7, 8, 9 } };
    matrix2.print();

    Matrix matrix3{ 2, 3, { 1, 2, 3 ,4 , 5, 6 } };
    matrix3.print();
}

void test_02() {

    Matrix matrix2{ 3, 3, { { 1, 2, 3 } , { 4, 5, 6 } } };
    matrix2.print();
}

void test_03 () {

    Matrix matrix{ 2, 3, { { 1, 2, 3 } , { 4, 5, 6 } } };
    matrix.print();

    auto value = matrix.at(0, 2);
    std::println("Value: {}", value);

    matrix.at(0, 2) = 33;
    std::println("Value: {}", matrix.at(0, 2));

    matrix.print();

    const Matrix constMatrix{ 2, 3, { { 1, 2, 3 } , { 4, 5, 6 } } };

    value = constMatrix.at(0, 2);
    std::println("Value: {}", value);

    constMatrix.print();
}

void test_04() {

    Matrix matrix{ 2, 3, { { 1, 2, 3 } , { 4, 5, 6 } } };
    Matrix copy{ matrix };

    matrix.print();
    copy.print();
}

void test_05() {

    Matrix matrix{ 2, 3, { { 1, 2, 3 } , { 4, 5, 6 } } };
    matrix.print();

    Matrix t = matrix.transpose();
    t.print();
}

void test_06() {

    Matrix matrix1{ 3, 3, { { 1, 2, 3 } ,{ 4 , 5, 6 }, { 7, 8, 9 } } };
    matrix1.print();

    Matrix matrix2{ 3, 3, { { 9, 8, 7 } ,{ 6, 5, 4 }, { 3, 2, 1 } } };
    matrix2.print();

    Matrix sum = matrix1.add(matrix2);
    sum.print();
}

void test_07() {

    Matrix matrix1{ 3, 3, { { 1, 2, 3 } ,{ 4 , 5, 6 }, { 7, 8, 9 } } };
    matrix1.print();

    Matrix matrix2{ 3, 3, { { 9, 8, 7 } ,{ 6, 5, 4 }, { 3, 2, 1 } } };
    matrix2.print();

    Matrix sum = matrix1.sub(matrix2);
    sum.print();
}

// =====================================================================================
// End-of-File
// =====================================================================================
