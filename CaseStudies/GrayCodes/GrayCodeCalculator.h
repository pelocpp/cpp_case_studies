// =====================================================================================
// GrayCodeCalculator.h
// =====================================================================================

#pragma once

class GrayCodeCalculator
{
public:
    // c'tors
    GrayCodeCalculator() = delete;

    // public interface
    static std::list<std::list<bool>> calculate(size_t);
    static void print(std::list<std::list<bool>>);

private:
    static std::list<std::list<bool>> calculateRankOne();
};

// =====================================================================================
// End-of-File
// =====================================================================================
