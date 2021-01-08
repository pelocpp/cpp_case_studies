// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <numeric>

#include "Partition.h"
#include "PartitionSet.h"
#include "PartitionCalculator.h"

void Test01_Partition()
{
    Partition p1 { 2 };
    std::cout << p1 << std::endl;
    Partition p2{ 1, 1 };
    std::cout << p2 << std::endl;
    std::cout << std::boolalpha << (p1 == p2) << std::endl;
    std::cout << std::boolalpha << (p1 < p2) << std::endl;
    std::cout << std::boolalpha << (p1 > p2) << std::endl;

    Partition p3{ 1, 2, 3 };
    std::cout << p3 << std::endl;
    Partition p4{ 3, 2, 1 };
    std::cout << p4 << std::endl;
    std::cout << std::boolalpha << (p3 == p4) << std::endl;
    std::cout << std::boolalpha << (p3 < p4) << std::endl;
    std::cout << std::boolalpha << (p3 > p4) << std::endl;

    Partition p5{ 1, 2, 3, 4, 5 };
    for (const auto elem : p5) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

void Test02_PartitionSet_01()
{
    PartitionSet set{ 3 };

    set.insert({ 3 });
    set.insert({ 1, 2 });
    set.insert({ 1, 1, 1 });

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test02_PartitionSet_02()
{
    PartitionSet set{ 4 };
    set.emplace(4);
    set.emplace(3, 1);
    set.emplace(2, 2);
    set.emplace(2, 1, 1);
    set.emplace(1, 1, 1, 1);

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test02_PartitionSet_03()
{
    PartitionSet set{ 4 };
    bool b;

    b = set.insert({ 2, 1, 1 });
    std::cout << std::boolalpha << b << std::endl;
    b = set.insert({ 1, 2, 1 });
    std::cout << std::boolalpha << b << std::endl;
    b = set.insert({ 1, 1, 2 });
    std::cout << std::boolalpha << b << std::endl;

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test02_PartitionSet_04()
{
    PartitionSet set{ 4 };
    bool b;

    b = set.emplace(2, 1, 1);
    std::cout << std::boolalpha << b << std::endl;
    b = set.emplace(1, 2, 1);
    std::cout << std::boolalpha << b << std::endl;
    b = set.emplace(1, 1, 2);
    std::cout << std::boolalpha << b << std::endl;

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test02_PartitionSet_05()
{
    PartitionSet set{ 4 };
    try {
        set.insert({ 2, 2, 1 });
    }
    catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Test02_PartitionSet_06()
{
    PartitionSet set{ 4 };
    try {
        set.emplace(2, 2, 1);
    }
    catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    for (const Partition& p : set) {
        std::cout << p << std::endl;
    }
}

void Test02_PartitionSet_07()
{
    PartitionSet set{ 7 };

    set.emplace(7 );
    set.emplace(6, 1 );
    set.emplace(5, 2 );
    set.emplace(5, 1, 1 );
    set.emplace(4, 3 );
    set.emplace(4, 2, 1 );
    set.emplace(4, 1, 1, 1 );
    set.emplace(3, 3, 1 );
    set.emplace(3, 2, 2 );
    set.emplace(3, 2, 1, 1 );
    set.emplace(3, 1, 1, 1, 1 );
    set.emplace(2, 2, 2, 1 );
    set.emplace(2, 2, 1, 1, 1 );
    set.emplace(2, 1, 1, 1, 1, 1 );
    set.emplace(1, 1, 1, 1, 1, 1, 1 );

    for (const Partition& p : set) {
        std::cout << p << std::endl;
    }
}

void Test03_PartitionCalculator_01()
{
    PartitionSet set = PartitionCalculator::calculate(5);
    for (const Partition& p : set) {
        std::cout << p << std::endl;
    }
}

void Test03_PartitionCalculator_02()
{
    PartitionSet set = PartitionCalculator::calculate(6);
    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test03_PartitionCalculator_03()
{
    for (int i = 1; i <= 20; ++i) {
        std::cout 
            << "Number partitions of " << i
            << ": " << PartitionCalculator::numberPartitions(i)
            << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
