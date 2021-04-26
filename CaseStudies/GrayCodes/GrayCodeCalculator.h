// =====================================================================================
// GrayCodeCalculator.h
// =====================================================================================

#pragma once

class GrayCodeCalculator
{
public:
    // c'tors
    // TODO: Dies auch bei den Palindromen nachziehen !!!!!!!!!!!!!!!!!!
    GrayCodeCalculator() = delete;

    // public interface
    static std::vector<std::vector<bool>> calculate(size_t);
    static void print(std::vector<std::vector<bool>>);

private:
 //   std::vector<std::vector<bool>> calculate(size_t length);
    static std::vector<std::vector<bool>> calculateRankOne();


};

// =====================================================================================
// End-of-File
// =====================================================================================
