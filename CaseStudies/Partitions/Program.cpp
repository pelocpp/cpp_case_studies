// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>

// -----------------------

// TODO: 
// Der kleiner Operator muss zu ende implementiert werden ... strict weak ordereing
// so dass die Beispiele richtig funktionieren .... 

// TODO: 
// Muss ich bei emplace wirklich mit std::forward arbeiten ???

// TODO: 
// Hmm, das emplace hätte man auch ohne variadic template machen können, also nur mit Init List ???
// Okay, dann braucht man beim Aufruf geschweifte Klammern ...

// -----------------------

void Test01_Partition();
void Test02_PartitionSet_01();
void Test02_PartitionSet_02();
void Test02_PartitionSet_03();
void Test02_PartitionSet_04();
void Test02_PartitionSet_05();
void Test02_PartitionSet_06();
void Test02_PartitionSet_07();
void Test03_PartitionCalculator_01();
void Test03_PartitionCalculator_02();
void Test03_PartitionCalculator_03();

int main()
{
    //Test01_Partition();
    //Test02_PartitionSet_01();
    //Test02_PartitionSet_02();
    //Test02_PartitionSet_03();
    Test02_PartitionSet_04();
    //Test02_PartitionSet_05();
    //Test02_PartitionSet_06();
    //Test02_PartitionSet_07();
    //Test03_PartitionCalculator_01();
    //Test03_PartitionCalculator_02();
    //Test03_PartitionCalculator_03();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
