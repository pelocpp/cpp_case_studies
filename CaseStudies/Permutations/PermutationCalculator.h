// =====================================================================================
// PermutationCalculator.h
// =====================================================================================

#pragma once

#include <algorithm>

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
            PermutationContainer<T> a{};
            a.insert(p);
            return a;
        }
        else
        {
            PermutationContainer<T> result{};

            for (size_t i{}; i != p.grade(); ++i)
            {
                // create permutation without i.-th element of current permutation
                Permutation<T> q{ p.removeAt(i) };

                // calculate permutions of n-1 elements recursively
                PermutationContainer<T> perms{ PermutationCalculator::calculate(q) };

                // join result with removed character
                perms.insertAll(p[i]);

                // append calculated permutations
                for (const auto& perm : perms) {
                    result.insert(perm);
                }
            }

            return result;
        }
    }

    static PermutationContainer<T> calculateEx(const Permutation<T>& p) {

        PermutationContainer<T> result{};

        // retrieve std::vector with values from permutation
        std::vector<T> values = p.getValues();

        // values need to be sorted
        std::sort(
            std::begin(values),
            std::end(values)
        );

        // keep calculating next permutation while there is a next permutation
        do {
            Permutation<T> tmp{};

            std::for_each(
                std::rbegin(values),
                std::rend(values),
                [&](const auto& elem) { 
                    tmp.insertAtFront(elem);
            });

            result.insert(tmp);

        } while (std::next_permutation(std::begin(values), std::end(values)));

        return result;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
