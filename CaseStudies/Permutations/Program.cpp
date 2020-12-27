#include <iostream>
#include <string>
#include <vector>

// TODO: Permutation sollte eine Schablone sein 
// mit elementaren Datentypen .... is_integral_type oder ´so ähnlich ....

// TODO: Permutation: std::deque ist besser 

// TODO: std  initializer list ... zur Initialisierung einer Permutation ....

// TODO: Lässt sich da  ein emplace_back anwenden !?!?! bei den Kontruktoren der Permutationen bei dem internen Vektor 

// TODO: Umbenennen in count:     int Size() const { return static_cast<int>(m_array.size()); }

// TODO: noexcept

// TODO: inline

// TODO: Methoden in klein umbenennen

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"

void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void Test01_Permutation()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation p1("ABC");
    std::cout << p1 << std::endl;

    std::cout << "Testing Insert: " << std::endl;
    p1.Insert('Z');
    std::cout << p1 << std::endl;

    Permutation p2("12345");
    std::cout << p2 << " [Number of Elements: " << p2.Grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p2.Grade(); i++)
    {
        char c = p2[i];
        std::cout << i << ": " << c << std::endl;
    }

    Permutation p3 = p2;
    std::cout << "Testing Remove: " << p3 << std::endl;
    for (int i = 0; i < p2.Grade(); i++)
    {
        p3 = p3.Remove(0);
        std::cout << i << ": " << p3 << std::endl;
    }
}

void Test02_PermutationArray()
{
    Permutation p("ABC");
    std::cout << p << std::endl;
    Permutation q("CBA");
    std::cout << q << std::endl << std::endl;

    PermutationArray array(5);
    array.Insert(p);
    array.Insert(q);
    std::cout << array << std::endl;
}

void Test03_PermutationCalculator()
{
    Permutation p("ABCD");
    PermutationCalculator calc;
    PermutationArray result = calc.Calculate(p);
    std::cout << result << std::endl;
}

void Test04_PermutationEnumeration()
{
    //Permutation p("ABCD");
    //PermutationCalculator calc;
    //calc.SetPermutation(p);
    //calc.Calculate();

    //calc.Reset();
    //while (calc.MoveNext())
    //{
    //    Permutation q = calc.Current();
    //    std::cout << "Next Permutation: " << q << std::endl;
    //}
}


int main()
{
    //Test01_Permutation();
    //Test02_PermutationArray();
    Test03_PermutationCalculator();
   // Test04_PermutationEnumeration();

    return 0;
}