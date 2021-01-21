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
    static PartitionSet calculate(size_t n);
    static size_t numberPartitions(size_t number);
    static size_t numberPartitions(size_t number, size_t maxSummand);
};

// =====================================================================================
// End-of-File
// =====================================================================================
