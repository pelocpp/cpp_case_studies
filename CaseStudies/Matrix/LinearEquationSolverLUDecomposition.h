// =====================================================================================
// LinearEquationSolverLUDecomposition.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

template <typename T>
    requires FloatNumber<T>
class LinearEquationSolverLUDecomposition
{
public:
    LinearEquationSolverLUDecomposition();
    LinearEquationSolverLUDecomposition(std::size_t dimension);

private:
    std::size_t m_dimension;          // number of rows / columns
    Matrix<T>   m_matrix;             // equation (left-hand side)
    Vector<T>   m_rhs;                // right-hand side
    Vector<T>   m_solution;           // solution

public:
    // getter/setter
    void setEquation                  (std::initializer_list<std::initializer_list<T>> values);
    void setEquation                  (const Matrix<T> coefficients);

    void setRightHandSide             (std::initializer_list<T> rhs);
    void setRightHandSide             (const Vector<T>& rhs);

    const Matrix<T>& getEquation      () const;
    const Vector<T>& getRightHandSide () const;

    std::size_t dimension             () const;
    const Vector<T>& solution         () const;

    // public interface
    void solve_simple                 ();
    void solve_pivot                  ();

private:
    Vector<T> forwardSubstitution     (const Matrix<T> lower, const Vector<T>& v) const;
    Vector<T> backwardSubstitution    (const Matrix<T> upper, const Vector<T>& v) const;
};

// =====================================================================================

namespace std
{
    // formatter for class LinearEquationSolverLUDecomposition
    template<typename T>
    struct std::formatter<LinearEquationSolverLUDecomposition<T>> : std::formatter<std::string_view>
    {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const LinearEquationSolverLUDecomposition<T>& solver, std::format_context& ctx) const {

            const Matrix<T>& equation{ solver.getEquation() };
            const Vector<T>& rhs{ solver.getRightHandSide() };

            std::size_t rows{ equation.rows() };
            std::size_t cols{ equation.cols() };

            std::string tmp{};
            for (std::size_t row{}; row != rows; ++row) {
                for (std::size_t col{}; col != cols; ++col) {

                    auto elem = equation(row, col);
                    std::format_to(std::back_inserter(tmp), "{:6.4g}", elem);
                }
                std::format_to(std::back_inserter(tmp), " | {:10.4g}\n", rhs[row]);
            }

            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
