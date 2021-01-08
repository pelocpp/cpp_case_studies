// =====================================================================================
// PartitionCalculator.h
// =====================================================================================

#pragma once

class PartitionCalculator
{
public:
    // c'tor
    PartitionCalculator() = delete;

    // public interface
    static PartitionSet calculate(int n);
    static int numberPartitions(int number);
    static int numberPartitions(int number, int maxSummand);
};

// =====================================================================================
// End-of-File
// =====================================================================================
