// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "PartialSet.h"
#include "PowerSet.h"

void test_PartialSet_01()
{
    PartialSet set1{ };
    std::cout << set1 << std::endl;

    PartialSet set2{ 1, 2, 3 };
    std::cout << set2 << std::endl;

    PartialSet set3{ 3, 2, 1 };
    std::cout << set3 << std::endl;
}

void test_PartialSet_02()
{
    PartialSet set{ };
    set.add(3);
    set.add(2);
    set.add(1);
    std::cout << set << std::endl;
}

void test_PartialSet_03()
{
    PartialSet set1{ };
    std::cout << set1 << std::endl;

    PartialSet set2{ 1 };
    std::cout << set2 << std::endl;

    PartialSet set3{ 1, 2 };
    std::cout << set3 << std::endl;

    PartialSet set4{ 1, 2, 3 };
    std::cout << set4 << std::endl;

    std::cout << std::boolalpha << (set1 == set1) << std::endl;
    std::cout << std::boolalpha << (set1 == set2) << std::endl;
    std::cout << std::boolalpha << (set1 < set2) << std::endl;
    std::cout << std::boolalpha << (set2 < set1) << std::endl;

    std::cout << std::boolalpha << (set3 == set3) << std::endl;
    std::cout << std::boolalpha << (set3 == set4) << std::endl;
    std::cout << std::boolalpha << (set3 < set4) << std::endl;
    std::cout << std::boolalpha << (set4 < set3) << std::endl;
}

void test_PowerSet_01()
{
    PowerSet set{ };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl;
}

void test_PowerSet_02()
{
    PowerSet set{ 1 };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl;
}

void test_PowerSet_03()
{
    PowerSet set{ 2 };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl;
}

void test_PowerSet_04()
{
    PowerSet set{ 3 };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl;
}

void test_PowerSet_05()
{
    PowerSet set{ 4 };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl;
}

void test_Iterator_01()
{
    // testing enumeration
    PowerSet powerSet{ 3 };
    for (const PartialSet& set : powerSet) {
        std::cout << "Next Set: " << set << std::endl;
    }
}

void test_PartialSetsBySize_01()
{
    PowerSet powerSet{ 5 };
    std::cout << "PowerSet:" << std::endl;
    for (const PartialSet& set : powerSet) {
        std::cout << set << std::endl;
    }

    size_t size = 3;
    PowerSet someSets = powerSet.partialSetsBySize(size);
    std::cout << "Partial set of size " << size << ':' << std::endl;
    for (const PartialSet& set : someSets) {
        std::cout << set << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
