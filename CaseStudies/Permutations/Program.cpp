#include <iostream>
using namespace std;

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void main()
{
    Test01_Permutation();
    Test02_PermutationArray();
    Test03_PermutationCalculator();
    Test04_PermutationEnumeration();

    getchar();
}

void Test01_Permutation()
{
    cout << "Testing c'tor: " << endl;
    Permutation p1("ABC", 3);
    cout << p1 << endl;

    cout << "Testing Insert: " << endl;
    p1.Insert('Z');
    cout << p1 << endl;

    Permutation p2("12345", 5);
    cout << p2 << " [Number of Elements: " << p2.Grade() << ']' << endl;

    cout << "Testing []-Operator: " << endl;
    for (int i = 0; i < p2.Grade(); i++)
    {
        char c = p2[i];
        cout << i << ": " << c << endl;
    }

    Permutation p3 = p2;
    cout << "Testing Remove: " << p3 << endl;
    for (int i = 0; i < p2.Grade(); i++)
    {
        p3 = p3.Remove(0);
        cout << i << ": " << p3 << endl;
    }
}

void Test02_PermutationArray()
{
    Permutation p("ABC", 3);
    cout << p << endl;
    Permutation q("CBA", 3);
    cout << q << endl << endl;

    PermutationArray array(5);
    array.Insert(p);
    array.Insert(q);
    cout << array << endl;
}

void Test03_PermutationCalculator()
{
    Permutation p("XYZ", 3);
    PermutationCalculator calc;
    PermutationArray result = calc.Calculate(p);
    cout << result << endl;
}

void Test04_PermutationEnumeration()
{
    Permutation p("ABCD", 4);
    PermutationCalculator calc;
    calc.SetPermutation(p);
    calc.Calculate();

    calc.Reset();
    while (calc.MoveNext())
    {
        Permutation q = calc.Current();
        cout << "Next Permutation: " << q << endl;
    }
}