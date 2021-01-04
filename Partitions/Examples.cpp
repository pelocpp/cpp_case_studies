// =====================================================================================
// Examples.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
//#include <sstream>

#include "Partition.h"
// #include "PermutationIterator.h"

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
    Partition p5{ 2, 4, 6 };
    for (int i = 0; i < p5.size(); i++)
        std::cout << p5[i] << ' ';
    std::cout << std::endl;

    Partition p6{ 6, 4, 2 };
    for (int i = 0; i < p6.size(); i++)
        std::cout << p6[i] << ' ';
    std::cout << std::endl;
}

void Test_Partition()
{
    Test01_Partition();
    //Test02_Partition();
    //Test03_Partition();
    //Test04_Partition();
    //Test05_Partition();
    //Test06_Partition();
    //Test07_Partition();
    //Test08_Partition();
}

int main()
{
    Test_Partition();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
