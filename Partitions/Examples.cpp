// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
//#include <sstream>

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

    Partition p3{ 1, 2, 3 };
    std::cout << p3 << std::endl;
    Partition p4{ 3, 2, 1 };
    std::cout << p4 << std::endl;
    std::cout << std::boolalpha << (p3 == p4) << std::endl;

    // TODO PeLo  DAS SOLLTE MIT for Each gehen
    //Partition p5{ 2, 4, 6 };
    //for (int i = 0; i < p5.size(); i++)
    //    std::cout << p5[i] << ' ';
    //std::cout << std::endl;

    //Partition p6{ 6, 4, 2 };
    //for (int i = 0; i < p6.size(); i++)
    //    std::cout << p6[i] << ' ';
    //std::cout << std::endl;
}

void Test02_PartitionSet_01()
{
    PartitionSet set{ 3 };

    // PeLo: Das muss mit einem EMPLACE gehen .. siehe Examples ....

    set.insert({ 3 });
    set.insert({ 1, 2 });
    set.insert({ 1, 1, 1 });

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test02_PartitionSet_02()
{
    PartitionSet set{ 7 };

    // PeLo: Das muss mit einem EMPLACE gehen .. siehe Examples ....

    set.insert({ 7 });
    set.insert({ 6, 1 });
    set.insert({ 5, 2 });
    set.insert({ 5, 1, 1 });
    set.insert({ 4, 3 });
    set.insert({ 4, 2, 1 });
    set.insert({ 4, 1, 1, 1 });
    set.insert({ 3, 3, 1 });
    set.insert({ 3, 2, 2 });
    set.insert({ 3, 2, 1, 1});
    set.insert({ 3, 1, 1, 1, 1 });
    set.insert({ 2, 2, 2, 1 });
    set.insert({ 2, 2, 1, 1, 1 });
    set.insert({ 2, 1, 1, 1, 1, 1 });
    set.insert({ 1, 1, 1, 1, 1, 1, 1 });

    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

void Test03_PartitionCalculator()
{
    PartitionSet set = PartitionCalculator::calculate(6);
   // set.Sort();
    std::cout << "Partitions of " << set.number() << ": " << std::endl;
    std::cout << set << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
