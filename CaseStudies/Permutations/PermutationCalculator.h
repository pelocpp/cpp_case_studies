// =====================================================================================
// PermutationCalculator.h
// =====================================================================================

#pragma once

#include "Permutation.h"
#include "PermutationContainer.h"

template <typename T>
class PermutationCalculator
{
public:
    // public interface
    static PermutationContainer<T> calculate(const Permutation<T>& p) {
        if (p.grade() == 1)
        {
            PermutationContainer<T> a{ 1 };
            a.insert(p);
            return a;
        }
        else
        {
            PermutationContainer<T> result{ faculty(p.grade()) };

            for (size_t i{}; i != p.grade(); ++i)
            {
                // create permutation without i.-th element of current permutation
                Permutation<T> q{ p.removeAt(i) };

                // calculate permutions of n-1 elements recursively
                PermutationContainer<T> tmp{ PermutationCalculator::calculate(q) };

                // join result with removed character
                tmp.insertAll(p[i]);

                // append calculated permutations
                for (size_t m{}; m != tmp.count(); ++m) {
                    result.insert(tmp[m]);
                }

            }

            return result;
        }
    }

private:
    static size_t faculty(size_t n) {
        size_t result{ 1 };
        for (size_t i{ 2 }; i <= n; ++i)
            result *= i;
        return result;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
