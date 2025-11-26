// =====================================================================================
// LinearEquationSolverGauss.h
// =====================================================================================

#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <cstddef>
#include <initializer_list>

template <typename T>
    requires FloatNumber<T>
class LinearEquationSolverGauss
{
public:
    LinearEquationSolverGauss();

private:
    std::size_t  m_dim;                  // number of rows / columns
    Matrix<T>    m_matrix;               // equation
    Vector<T>    m_solution;             // solution

public:
    // getter/setter
    std::size_t dimension                () const;

    void setEquation(
        std::size_t dim, 
        std::initializer_list<std::initializer_list<T>> values
    );

    const Matrix<T>& getEquation         () const;
    const Vector<T>& solution            () const;

    // public interface
    bool solve_01_simple                 ();
    bool solve_02_pivot                  ();
    bool solve_03_permutation_vector     ();

    bool eliminateForward                ();
    bool eliminateForwardPivot           ();
    bool eliminateForwardPivotPermutation();

    void substituteBack                  ();
};

// =====================================================================================

namespace std
{
    // formatter for class LinearEquationSolverGauss
    template<typename T>
    struct std::formatter<LinearEquationSolverGauss<T>> : std::formatter<std::string_view>
    {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const LinearEquationSolverGauss<T>& solver, std::format_context& ctx) const {

            const Matrix<T>& equation{ solver.getEquation() };
            std::size_t rows{ equation.rows() };
            std::size_t cols{ equation.cols() };

            std::string tmp{};
            for (std::size_t row{}; row != rows; ++row) {

                std::size_t col{};
                for (; col != cols - 1; ++col) {

                    auto elem = equation(row, col);
                    std::format_to(std::back_inserter(tmp), "{:6.4g}", elem);
                }
                std::format_to(std::back_inserter(tmp), " | {:10.4g}\n", equation(row, col));
            }

            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
