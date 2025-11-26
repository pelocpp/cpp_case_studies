// =====================================================================================
// Vector.h
// =====================================================================================

#pragma once

#include "FloatNumber.h"

#include <algorithm>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <memory>
#include <string_view>
#include <vector>

template <typename T>
    requires FloatNumber<T>
class Vector
{
protected:
    std::vector<T>        m_values;

public:
    // c'tors
    Vector() = default;
    explicit Vector       (std::size_t dimension);
    explicit Vector       (std::initializer_list<T> values);

    // getter   
    std::size_t dimension () const;
    T length              () const;

    // accessing vector elements
    T& operator[]         (std::size_t index);
    const T& operator[]   (std::size_t index) const;
    T& at                 (std::size_t index);
    const T& at           (std::size_t index) const;

    // operators
    Vector  operator+     (const Vector& other) const;
    Vector  operator-     (const Vector& other) const;
    Vector& operator+=    (const Vector& other);
    Vector& operator-=    (const Vector& other);

    Vector  operator*     (T scalar) const;
    T operator*           (const Vector& other) const;

    bool operator==       (const Vector& other) const;
    bool operator!=       (const Vector& other) const;
    
    // public interface
    void   fill           (T value);
    Vector normalize      () const;
    Vector add            (const Vector& other) const;
    Vector sub            (const Vector& other) const;
    Vector mul            (T scalar) const;
};

// =====================================================================================

namespace std
{
    // formatter for class Vector<T>
    template<typename T>
    struct std::formatter<Vector<T>> : std::formatter<std::string_view>
    {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const Vector<T>& vec, std::format_context& ctx) const {

            std::string tmp{};
            std::format_to(std::back_inserter(tmp), "{{");

            for (std::size_t k{}; k != vec.dimension(); ++k) {
                auto elem{ vec[k] };
                std::format_to(std::back_inserter(tmp), "{:6.4g}", elem);
                if (k != vec.dimension() - 1) {
                    std::format_to(std::back_inserter(tmp), ", ");
                }
            }

            std::format_to(std::back_inserter(tmp), "}}");
            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
