// =====================================================================================
// PalindromCalculator.h
// =====================================================================================

#pragma once

class PalindromCalculator
{
public:
    PalindromCalculator() = delete;

    static std::tuple<std::optional<Number>, Number, size_t>
        calcPalindrom(const Number&, size_t);

    static std::tuple<size_t, size_t, size_t> forthEulerProblem();
};

// =====================================================================================
// End-of-File
// =====================================================================================
