// =====================================================================================
// Partition.h
// =====================================================================================

#pragma once

#include <iostream>
using namespace std;

#include "PartialSet.h"
#include "PowerSet.h"

// TODO:
// 
// + Operator, um zwei PartialSets zu vereinigen !!!!!1

// Anstelle von Zahlen lassen sich Potenzmenge auch
//  von Zeichen bilden !!!
// 'A'  'B'  'C'    ????????? 

// function prototypes
void Test01();
void Test02();
void Test03();

void Test04a();
void Test04b();

void Test05();

void Test06a();
void Test06b();
void Test06c();

void Test07();
void Test08();
void Test09();
void Test10();
void Test11();


void Test01a();
void Test01b();
void Test01c();
void Test01d();
void Test01e();
void Test01f();

void main()
{
    Test01a();
}

void Test01()
{
    Test01a();
    Test01b();
    Test01c();
    Test01d();
    Test01e();
    Test01f();
}


// testing power set
void Test01a()
{
    PowerSet powerSet;
    cout << powerSet << endl;
}

void Test01b()
{
    PowerSet powerSet (0);
    cout << powerSet << endl;
}

void Test01c()
{
    PowerSet powerSet (1);
    cout << powerSet << endl;
}

void Test01d()
{
    PowerSet powerSet (2);
    cout << powerSet << endl;
}

void Test01e()
{
    PowerSet powerSet (3);
    cout << powerSet << endl;
}

void Test01f()
{
    PowerSet powerSet (4);
    cout << powerSet << endl;
}

void Test02()
{
    PowerSet powerSet (2);
    cout << powerSet << endl;
}

void Test03()
{
    PowerSet powerSet;
    cout << powerSet << endl;
    PartialSet partialSet;
    cout << partialSet << endl;
}

// testing partial set
void Test04a()
{
    PartialSet set1;
    cout << set1 << endl;

    int numbers2[]  = { 1, 2, 3 };
    PartialSet set2 (numbers2, 3);
    cout << set2 << endl;

    int numbers3[] = { 1, 2 };
    PartialSet set3 (numbers3, 2);
    cout << set3 << endl;

    cout << "IsLessThan:    " << set2.IsLessThan(set3) << endl;
    cout << "IsEqual:       " << set2.IsEqual(set3) << endl;
    cout << "IsGreaterThan: " << set2.IsGreaterThan(set3) << endl;
}

void Test04b()
{
    PartialSet set1;
    cout << set1 << endl;

    int numbers2[]  = { 1, 2, 3 };
    PartialSet set2 (numbers2, 3);
    cout << set2 << endl;

    int numbers3[] = { 1, 2 };
    PartialSet set3 (numbers3, 2);
    cout << set3 << endl;

    cout << "IsLessThan:    " << (set2 <= set3) << endl;
    cout << "IsEqual:       " << (set2 == set3) << endl;
    cout << "IsGreaterThan: " << (set2 >= set3) << endl;
}

void Test05()
{
    PowerSet powerSet;
    cout << powerSet << endl << endl;
}

void Test06a()
{
    PowerSet powerSet (4);
    cout << powerSet << endl << endl;

    powerSet.Sort();
    cout << powerSet << endl;
}

void Test06b()
{
    // testing enumeration
    PowerSet powerSet (3);
    powerSet.Sort();
    cout << powerSet << endl;

    powerSet.Reset();
    while (powerSet.MoveNext())
    {
        PartialSet set = powerSet.Current();
        cout << "Next Set: " << set << endl;
    }
}

void Test06c()
{
    PowerSet powerSet (3);
    powerSet.Sort();

    powerSet.Reset();
    powerSet.MoveNext();
    powerSet.MoveNext();
    cout << "Current: " << powerSet.Current() << endl;
    cout << "Current: " << powerSet.Current() << endl;
    powerSet.MoveNext();
    cout << "Current: " << powerSet.Current() << endl;
    powerSet.Reset();
    powerSet.MoveNext();
    cout << "Current: " << powerSet.Current() << endl;
}

void Test07()
{
    // testing copy c'tor of power set
    PowerSet ps1 (2);
    PowerSet ps2 = ps1;
}

void Test07b()
{
    // testing assignment operator of power set
    PowerSet ps1 (2);
    PowerSet ps2;
    ps2 = ps1;
}

void Test08a()
{
    PowerSet ps (4);
    ps.Sort();
    cout << ps << endl;

    int count = ps.PartialSetsBySize (3);
    cout << "Size 2: " << count << endl;
}

void Test08b()
{
    PowerSet ps(3);
    int count = ps.PartialSetsBySize (2);
    cout << "Partial sets of size 2: " << count << endl;

    PartialSet* buf = new PartialSet[count];
    ps.PartialSetsBySize(2, buf, count);

    for (int i = 0; i < count; i ++)
        cout << i << ": " << buf[i] << endl;

    delete[] buf;
}

void Test09()
{
    PowerSet ps1(4);
    cout << ps1 << endl;

    PowerSet ps2;
    ps2 = ps1;
    cout << ps2 << endl;
}

void Test10()
{
    PowerSet powerSet (3);
    powerSet.Sort();

    for (int i = 0; i < powerSet.GetCardinality(); i ++)
    {
        PartialSet set = powerSet[i];
        cout << "Next Set: " << set << endl;
    }
}

void Test11()
{
    PowerSet powerSet (6);
    cout << powerSet << endl;
	powerSet.Sort();
    cout << powerSet << endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
