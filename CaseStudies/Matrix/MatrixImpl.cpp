// =====================================================================================
// MatrixImpl.cpp
// =====================================================================================

#include "Matrix.h"

#include <print>
#include <span>
#include <stdexcept>    

// c'tor(s)
template <typename T>
    requires FloatNumber<T>
Matrix<T>::Matrix() : m_rows{}, m_cols{}, m_values{} {}

template <typename T>
    requires FloatNumber<T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols)
    : m_rows{ rows }, m_cols{ cols }
{
    // m_values = std::make_shared<T[]>(m_rows * m_cols);
    m_values.resize(m_rows * m_cols);
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
        m_values.begin()
    );
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::elements(std::initializer_list<std::initializer_list<T>> values)
{
    if (m_rows != values.size()) {
        throw std::invalid_argument("Wrong number of rows!");
    }

    auto last{ m_values.begin() };

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

// getter/setter
template <typename T>
    requires FloatNumber<T>
std::size_t Matrix<T>::rows() const noexcept
{
    return m_rows; 
}

template <typename T>
    requires FloatNumber<T>
std::size_t Matrix<T>::cols() const noexcept
{
    return m_cols; 
}

// accessing matrix elements
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
    return m_values[row * m_cols + col];
}

template <typename T>
    requires FloatNumber<T>
T& Matrix<T>::operator()(std::size_t row, std::size_t col)
{
   return m_values[row * m_cols + col]; // no index check
}

template <typename T>
    requires FloatNumber<T>
const T& Matrix<T>::operator()(std::size_t row, std::size_t col) const
{
   return m_values[row * m_cols + col]; // no index check
}

// public interface
template <typename T>
    requires FloatNumber<T>
void Matrix<T>::fill(T value)
{
    std::fill(m_values.begin(), m_values.end(), value);
}

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::unit()
{
    std::fill(m_values.begin(), m_values.end(), T{});

    for (std::size_t k{}; k != rows(); ++k) {
        (*this)(k, k) = T{ 1.0 };
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
Vector<T> Matrix<T>::mul(const Vector<T>& vec) const
{
    if (m_cols != vec.dimension()) {
        throw std::invalid_argument("Invalid vector dimensions!");
    }

    Vector<T> result(m_rows);

    for (std::size_t row{}; row != m_rows; ++row) {

        T value{};
        for (std::size_t col{}; col != m_cols; ++col) {
            value += at(row, col) * vec[col];
        }
        result[row] = value;
    }

    return result;
}

// operators
template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::operator+ (const Matrix& other) const
{
    return add(other);
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::operator- (const Matrix& other) const
{
    return sub(other);
}

template <typename T>
    requires FloatNumber<T>
Matrix<T> Matrix<T>::operator* (const Matrix& other) const
{
    return mul(other);
}

template <typename T>
    requires FloatNumber<T>
Vector<T> Matrix<T>::operator* (const Vector<T>& other) const
{
    return mul(other);
}

template <typename T>
    requires FloatNumber<T>
Matrix<T>& Matrix<T>::operator+= (const Matrix& other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
    requires FloatNumber<T>
Matrix<T>& Matrix<T>::operator-= (const Matrix& other)
{
    *this = *this - other;
    return *this;
}


template <typename T>
    requires FloatNumber<T>
Matrix<T>& Matrix<T>::operator*= (const Matrix& other)
{
    *this = *this * other;
    return *this;
}

// comparison operators
template <typename T>
    requires FloatNumber<T>
bool Matrix<T>::operator== (const Matrix& other) const
{
    return m_values == other.m_values;
}

template <typename T>
    requires FloatNumber<T>
bool Matrix<T>::operator!= (const Matrix& other) const
{
    return !(*this == other);
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

// iteration support
template <typename T>
    requires FloatNumber<T>
Matrix<T>::iterator Matrix<T>::begin() noexcept { return m_values.begin(); }

template <typename T>
    requires FloatNumber<T>
Matrix<T>::iterator Matrix<T>::end() noexcept { return m_values.end(); }

template <typename T>
    requires FloatNumber<T>
Matrix<T>::const_iterator Matrix<T>::begin() const noexcept { return m_values.begin(); }

template <typename T>
    requires FloatNumber<T>
Matrix<T>::const_iterator Matrix<T>::end() const noexcept { return m_values.end(); }

template <typename T>
    requires FloatNumber<T>
void Matrix<T>::subtractRow(T factor, std::size_t source, std::size_t target)
{
    // Original
    //for (std::size_t j{ source }; j != m_cols; ++j) {
    //    at(target, j) -= factor * at(source,j);
    //}

    // Neuer Versuch
    for (std::size_t j{ 0 }; j != m_cols; ++j) {
        at(target, j) -= factor * at(source, j);
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

