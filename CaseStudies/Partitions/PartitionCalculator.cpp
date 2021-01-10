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
PartitionSet PartitionCalculator::calculate(int number)
{
    PartitionSet result{ number };

    if (number == 1) {
        Partition p{ 1 };
        result.insert(p);
    }
    else {
        PartitionSet setMinusOne = calculate(number - 1);

        for (const auto& p : setMinusOne) {

            std::vector<int> numbers = p.numbers();
            for (size_t j = 0; j != numbers.size(); j++) {
                numbers[j]++;
                Partition q{ numbers };
                result.insert(q);
                numbers[j]--;
            }
        }

        // create missing partition (just consisting of '1's)
        std::vector<int> ones(number, 1);
        Partition pOnes{ ones };
        result.insert(pOnes);
    }

    return result;
}

int PartitionCalculator::numberPartitions(int number)
{
    if (number < 1)
        return 0;

    int total = 0;
    for (int maxSummand = 1; maxSummand <= number; maxSummand++)
        total += numberPartitions(number, maxSummand);

    return total;
}

int PartitionCalculator::numberPartitions(int number, int maxSummand)
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
