// =====================================================================================
// Program.cpp
// =====================================================================================

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

void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void Test01_Permutation_Ex_01();
void Test01_Permutation_Ex_02();
void Test02_PermutationArray_Ex();
void Test03_PermutationCalculator_Ex();
void Test04_PermutationEnumeration_Ex();

int main()
{
    //Test01_Permutation();
    //Test02_PermutationArray();
    //Test03_PermutationCalculator();
    //Test04_PermutationEnumeration();

    Test01_Permutation_Ex_01();
    Test01_Permutation_Ex_02();
    //Test02_PermutationArray_Ex();
    //Test03_PermutationCalculator_Ex();
    //Test04_PermutationEnumeration_Ex();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
