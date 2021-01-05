// =====================================================================================
// PartitionCalculator.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

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
            for (int j = 0; j < numbers.size(); j++) {
                numbers[j]++;
                Partition p{ numbers };
                result.insert(p);
                numbers[j]--;
            }
        }

        // create missing partition (just consisting of '1's)
        std::vector<int> ones(number, 1);
        Partition pOnes (ones);
        result.insert(pOnes);
    }

    return result;
}

// =====================================================================================
// End-of-File
// =====================================================================================
