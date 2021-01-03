// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

// TODO: Permutation sollte eine Schablone sein 
// mit elementaren Datentypen .... is_integral_type oder �so �hnlich ....

// TODO: std  initializer list ... zur Initialisierung einer Permutation ....

// TODO: L�sst sich da  ein emplace_back anwenden !?!?! bei den Kontruktoren der Permutationen bei dem internen Vektor 

// TODO: Umbenennen in count:     int Size() const { return static_cast<int>(m_array.size()); }

// TODO: Auch eine VERSION mit den std::perm von der Standard-Bibliothek implementieren !!!

// TODO: Bei den ITeratoren wird es etwas schwieriger: Wenn man alles auf einmal implementiert,
// dann wird der Memory Bedarf zu gro� !!!!!!!

// TODO: noexcept

// TODO: inline

// TODO: Methoden in klein umbenennen

// TODO: Der Iterator ist nicht default - constructable .... ist das schlimm ???

void Test01_Permutation_Errors();
void Test01_Permutation();
void Test01_Permutation_Iteration();
void Test02_PermutationArray();
void Test02_PermutationArray_02();
void Test03_PermutationCalculator();
void Test03_PermutationCalculator_02();
void Test04_PermutationEnumeration();

void Test01_Permutation_Ex_01();
void Test01_Permutation_Ex_02();
void Test02_PermutationArray_Ex();
void Test03_PermutationCalculator_Ex_01();
void Test03_PermutationCalculator_Ex_02();
void Test03_PermutationCalculator_Ex_03();
void Test04_PermutationEnumeration_Ex();

int main()
{
    // Test01_Permutation_Errors();
    //Test01_Permutation();
    Test01_Permutation_Iteration();
    //Test02_PermutationArray();
    //Test02_PermutationArray_02();
    //Test03_PermutationCalculator();
    //Test03_PermutationCalculator_02();
    //Test04_PermutationEnumeration();

    //Test01_Permutation_Ex_01();
    //Test01_Permutation_Ex_02();
    //Test02_PermutationArray_Ex();
    //Test03_PermutationCalculator_Ex_01();
    //Test03_PermutationCalculator_Ex_02();
    //Test03_PermutationCalculator_Ex_03();

    //Test04_PermutationEnumeration_Ex();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
