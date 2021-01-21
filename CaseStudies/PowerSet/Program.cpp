// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>

// =====================================================================================

// TODO: PeLo
// 
// + Operator, um zwei PartialSets zu vereinigen !!!!!1

//  PeLo Anstelle von Zahlen lassen sich Potenzmenge auch
//  von Zeichen bilden !!!
// 'A'  'B'  'C'    ????????? 

// TODO: PeLo  Ausprobieren: Die set ist sorted ... aber ist es kleiner oder kleiner-gleich, der das dann
// Also welche Operatoren sind dafür notwendig !!!

// TODO: Vielleicht eine PartialPowerSet implementieren ... für die PartialSetsBySize

void test_PartialSet_01();
void test_PartialSet_02();
void test_PartialSet_03();

void test_PowerSet_01();
void test_PowerSet_02();
void test_PowerSet_03();
void test_PowerSet_04();
void test_PowerSet_05();

void test_Iterator_01();
void test_PartialSetsBySize_01();

int main()
{
    test_PartialSet_01();
    test_PartialSet_02();
    test_PartialSet_03();

    test_PowerSet_01();
    test_PowerSet_02();
    test_PowerSet_03();
    test_PowerSet_04();
    test_PowerSet_05();

    test_Iterator_01();

    test_PartialSetsBySize_01();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
