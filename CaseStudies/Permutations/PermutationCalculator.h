// =====================================================================================
// PermutationCalculator.h
// =====================================================================================

#pragma once

#include "Permutation.h"
#include "PermutationContainer.h"

//template <typename T>
//class PermutationCalculator
//{
//private:
//    Permutation<T> m_perm;
//    PermutationContainer<T> m_perms;
//
//public:
//    // c'tor
//    PermutationCalculator() : m_perm{}, m_perms{} {}
//
//    // getter/setter
//    void setPermutation(const Permutation<T>& p) {
//        m_perm = p;
//    }
//
//    Permutation<T> getPermutation() {
//        return m_perm;
//    }
//
//    // public interface
//    void calculate() {
//        m_perms = calculate(m_perm);
//    }
//
//    PermutationContainer<T> calculate(const Permutation<T>& p) {
//        if (p.grade() == 1)
//        {
//            PermutationContainer<T> a{ 1 };
//            a.insert(p);
//            return a;
//        }
//        else
//        {
//            PermutationContainer<T> result{ faculty(p.grade()) };
//
//            for (size_t i{}; i != p.grade(); ++i)
//            {
//                // create permutation without i.-th element of current permutation
//                Permutation<T> q{ p.removeAt(i) };
//
//                // calculate permutions of n-1 elements recursively
//                PermutationContainer<T> tmp{ calculate(q) };
//
//                // join result with removed character
//                tmp.insertAll(p[i]);
//
//                // append calculated permutations
//                for (size_t m{}; m != tmp.count(); ++m) {
//                   result.insert(tmp[m]);
//                }
//
//            }
//
//            return result;
//        }
//    }
//
//    //PermutationContainer<T> calculateEx(const Permutation<T>& p) {
//
//    //    PermutationContainer<T> result(faculty(p.grade()));
//
//    //    // retrieve std::vector with values from permutation
//    //    std::vector<T> values = p.getValues();
//
//    //    // need to sort the values
//    //    std::sort(std::begin(values), std::end(values));
//
//    //    // keep calculating next permutation while there is a next permutation
//    //    do {
//    //        result.insert(values);
//    //    } while (std::next_permutation(std::begin(values), std::end(values)));
//
//    //    return result;
//    //}
//
//    // enumerator interface
//    //void Reset();
//    //bool MoveNext();
//    //Permutation Current();
//
//private:
//    size_t faculty(size_t n) const {
//        size_t result{ 1 };
//        for (size_t i{ 2 }; i <= n; ++i)
//            result *= i;
//        return result;
//    }
//};

// =====================================================================================
// End-of-File
// =====================================================================================


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