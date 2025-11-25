// =====================================================================================
// Matrix.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"
#include "Vector.h"

#include <cstddef>
#include <initializer_list>
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
    // follow some of the conventions of a C++ container
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

public:
    // c'tors
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);

    // getter/setter   
    std::size_t rows    () const noexcept;
    std::size_t cols    () const noexcept;

    // TO BE DONE: Hier die Elemente vorne mit hin
    //void elements(std::size_t rows, std::size_t cols, std::initializer_list<T> values);
    //void elements(std::size_t rows, std::size_t cols, std::initializer_list<std::initializer_list<T>> values);

    //TO BE DONE : Hier die Elemente vorne mit hin
    // Matrix mal Vector = Vector
    // Zum Beispiel zur Überprüfung von Lineren Gleichungssystemen: = Produkt von Matrix und Vektor

    void elements       (std::initializer_list<T> values);
    void elements       (std::initializer_list<std::initializer_list<T>> values);

    // accessing matrix elements
    T& operator()       (std::size_t row, std::size_t col);
    const T& operator() (std::size_t row, std::size_t col) const;
    T& at               (std::size_t row, std::size_t col);
    const T& at         (std::size_t row, std::size_t col) const;

    // public interface
    void      fill      (T value);
    Matrix    transpose () const;
    Matrix    add       (const Matrix& other) const;
    Matrix    sub       (const Matrix& other) const;
    Matrix    mul       (const Matrix& other) const;
    Vector<T> mul       (const Vector<T>& other) const;
    void      print     () const;

    // Fehlt: Methode fill ... mit einem konstanten Wert vorbelegen ....

    // operators
    Matrix operator+    (const Matrix& other) const;
    Matrix operator-    (const Matrix& other) const;
    Matrix operator*    (const Matrix& other) const;
    Vector<T> operator* (const Vector<T>& other) const;

    Matrix& operator+=  (const Matrix& other);
    Matrix& operator-=  (const Matrix& other);
    Matrix& operator*=  (const Matrix& other);

    // iterator support
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

private:
   // void mulRow         (std::size_t row, T value);   // Hmmm, wozu habe ich diese Methode ....

public:
    // helper methods for forward elimination
    void swapRows(std::size_t row1, std::size_t row2);
    void subtractRow(T factor, std::size_t source, std::size_t target);
};

// =====================================================================================

namespace std
{
    // formatter for class Color
    template<typename T>
    struct std::formatter<Matrix<T>> : std::formatter<std::string_view>
    {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const Matrix<T>& m, std::format_context& ctx) const {

            std::string tmp{};
            std::format_to(std::back_inserter(tmp), "{{\n");

            for (std::size_t row{}; row != m.rows(); ++row) {
                for (std::size_t col{}; col != m.cols(); ++col) {

                    auto elem = m(row, col);
                    std::format_to(std::back_inserter(tmp), "{:6.4g}", elem);
                }
                std::format_to(std::back_inserter(tmp), "\n");
            }

            std::format_to(std::back_inserter(tmp), "}}");
            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
