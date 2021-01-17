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

void Test01_PartialSet();
void Test02_PowerSet_01();
void Test02_PowerSet_02();

void Test03_PowerSet_01();

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
    //test_PartialSet_01();
    //test_PartialSet_02();
    //test_PartialSet_03();

    //test_PowerSet_01();
    //test_PowerSet_02();
    //test_PowerSet_03();
    //test_PowerSet_04();
    //test_PowerSet_05();

    //test_Iterator_01();

    test_PartialSetsBySize_01();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
//
//// function prototypes


//
//void Test03()
//{
//    PowerSet powerSet;
//    cout << powerSet << endl;
//    PartialSet partialSet;
//    cout << partialSet << endl;
//}
//
//// testing partial set
//void Test04a()
//{
//    PartialSet set1;
//    cout << set1 << endl;
//
//    int numbers2[] = { 1, 2, 3 };
//    PartialSet set2(numbers2, 3);
//    cout << set2 << endl;
//
//    int numbers3[] = { 1, 2 };
//    PartialSet set3(numbers3, 2);
//    cout << set3 << endl;
//
//    cout << "IsLessThan:    " << set2.IsLessThan(set3) << endl;
//    cout << "IsEqual:       " << set2.IsEqual(set3) << endl;
//    cout << "IsGreaterThan: " << set2.IsGreaterThan(set3) << endl;
//}
//

//
//void Test06a()
//{
//    PowerSet powerSet(4);
//    cout << powerSet << endl << endl;
//
//    powerSet.Sort();
//    cout << powerSet << endl;
//}
//
//void Test06b()
//{
//    // testing enumeration
//    PowerSet powerSet(3);
//    powerSet.Sort();
//    cout << powerSet << endl;
//
//    powerSet.Reset();
//    while (powerSet.MoveNext())
//    {
//        PartialSet set = powerSet.Current();
//        cout << "Next Set: " << set << endl;
//    }
//}
//
//void Test06c()
//{
//    PowerSet powerSet(3);
//    powerSet.Sort();
//
//    powerSet.Reset();
//    powerSet.MoveNext();
//    powerSet.MoveNext();
//    cout << "Current: " << powerSet.Current() << endl;
//    cout << "Current: " << powerSet.Current() << endl;
//    powerSet.MoveNext();
//    cout << "Current: " << powerSet.Current() << endl;
//    powerSet.Reset();
//    powerSet.MoveNext();
//    cout << "Current: " << powerSet.Current() << endl;
//}
//

//void Test08a()
//{
//    PowerSet ps(4);
//    ps.Sort();
//    cout << ps << endl;
//
//    int count = ps.PartialSetsBySize(3);
//    cout << "Size 2: " << count << endl;
//}
//
//void Test08b()
//{
//    PowerSet ps(3);
//    int count = ps.PartialSetsBySize(2);
//    cout << "Partial sets of size 2: " << count << endl;
//
//    PartialSet* buf = new PartialSet[count];
//    ps.PartialSetsBySize(2, buf, count);
//
//    for (int i = 0; i < count; i++)
//        cout << i << ": " << buf[i] << endl;
//
//    delete[] buf;
//}
//
//void Test09()
//{
//    PowerSet ps1(4);
//    cout << ps1 << endl;
//
//    PowerSet ps2;
//    ps2 = ps1;
//    cout << ps2 << endl;
//}
//
//void Test10()
//{
//    PowerSet powerSet(3);
//    powerSet.Sort();
//
//    for (int i = 0; i < powerSet.GetCardinality(); i++)
//    {
//        PartialSet set = powerSet[i];
//        cout << "Next Set: " << set << endl;
//    }
//}
//
//void Test11()
//{
//    PowerSet powerSet(6);
//    cout << powerSet << endl;
//    powerSet.Sort();
//    cout << powerSet << endl;
//}
