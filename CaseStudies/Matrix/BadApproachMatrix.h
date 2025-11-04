// =====================================================================================
// BadApproachMatrix.h
// =====================================================================================

#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <print>

template <typename T, std::size_t Rows, std::size_t Cols>
class BadApproachMatrix
{
protected:
    std::array<std::array<T, Cols>, Rows> m_values{};

public:
    // c'tors
    BadApproachMatrix() = default;

    BadApproachMatrix(std::initializer_list<double> values)
    {
        std::copy(
            values.begin(),
            values.end(),
            &m_values[0][0]
        );
    }
    
    BadApproachMatrix(std::initializer_list<std::initializer_list<double>> list)
    {
        if (Rows != list.size()) {
            throw std::invalid_argument("Wrong number of rows!");
        }

        for (std::size_t rowIndex{}; auto values : list) {

            if (values.size() != Cols) {
                throw std::invalid_argument("Wrong number of columns!");
            }

            auto& row = m_values[rowIndex];

            std::copy(
                values.begin(),
                values.end(),
                row.begin()
            );

            ++rowIndex;
        }
    }

    // public interface
    void print() const
    {
        for (const auto& row : m_values) {

            for (const auto& elem : row) {
                std::print("{:3}", elem);
            }
            std::println();
        }
        std::println();
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
