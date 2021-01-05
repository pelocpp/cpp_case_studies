// =====================================================================================
// PartitionCalculator.h
// =====================================================================================

#pragma once

class PartitionCalculator
{
private:
    int m_number{ 0 };

public:
    // c'tor
    PartitionCalculator() = default;

    // getter/setter
    //void setPermutation(const Permutation&);
    //Permutation getPermutation();

    // public interface
    static PartitionSet calculate(int n);
};

// =====================================================================================
// End-of-File
// =====================================================================================
