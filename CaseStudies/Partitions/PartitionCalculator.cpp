// =====================================================================================
// PartitionCalculator.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Partition.h"
#include "PartitionSet.h"
#include "PartitionCalculator.h"

// public interface
PartitionSet PartitionCalculator::calculate(size_t number)
{
    PartitionSet result{ number };

    if (number == 1) {
        Partition p{ 1 };
        result.insert(p);
    }
    else {
        PartitionSet setMinusOne = calculate(number - 1);

        for (const auto& p : setMinusOne) {

            std::vector<size_t> numbers = p.numbers();
            for (size_t j = 0; j != numbers.size(); j++) {
                numbers[j]++;
                Partition q{ numbers };
                result.insert(q);
                numbers[j]--;
            }
        }

        // create missing partition (just consisting of '1's)
        std::vector<size_t> ones(number, 1);
        Partition pOnes{ ones };
        result.insert(pOnes);
    }

    return result;
}

size_t PartitionCalculator::numberPartitions(size_t number)
{
    if (number < 1)
        return 0;

    size_t total = 0;
    for (int maxSummand = 1; maxSummand <= number; maxSummand++)
        total += numberPartitions(number, maxSummand);

    return total;
}

size_t PartitionCalculator::numberPartitions(size_t number, size_t maxSummand)
{
    if (maxSummand > number) {
        return 0;
    }
    else if (maxSummand == 0) {
        return 0;
    }
    else if (maxSummand == 1) {
        return 1;
    }
    else {
        return
            numberPartitions(number - 1, maxSummand - 1) +
            numberPartitions(number - maxSummand, maxSummand);
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
