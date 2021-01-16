// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "PartialSet.h"
#include "PowerSet.h"

//#include "PartitionSet.h"
//#include "PartitionCalculator.h"
//

//
//void Test01_PowerSet()
//{
//    for (int i = 0; i < 12; ++i) {
//        std::cout << PowerSet::PowerByTwo(i) << std::endl;
//        std::cout << PowerSet::PowerByTwo_Neu(i) << std::endl;
//        std::cout << std::endl;
//    }
//}

void Test01_PartialSet()
{
    PartialSet set1;
    std::cout << set1 << std::endl;

    PartialSet set2({ 1, 2, 3 });
    std::cout << set2 << std::endl;

    PartialSet set3({ 1, 2 });
    std::cout << set3 << std::endl;

    std::cout << "IsLessThan: " << (set2 == set3) << std::endl;
    std::cout << "IsEqual: " << (set2 == set3) << std::endl;
    std::cout << "IsGreaterThan: " << (set2 >= set3) << std::endl;
}

void Test02_PowerSet_01()
{
    PowerSet set{ };
    std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
    std::cout << set << std::endl << std::endl;
}

void Test02_PowerSet_02()
{
    for (int n = 0; n <= 5; ++n) {
        PowerSet set{ n };
        std::cout << "Size: " << set.size() << ", Cardinality: " << set.cardinality() << std::endl;
        std::cout << set << std::endl << std::endl;
    }
}



// =====================================================================================
// End-of-File
// =====================================================================================
