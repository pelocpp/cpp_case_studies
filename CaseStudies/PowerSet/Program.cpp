// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>

// =====================================================================================

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
