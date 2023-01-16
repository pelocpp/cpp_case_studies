// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

// TODO: Permutation sollte eine Schablone sein 
// mit elementaren Datentypen .... is_integral_type oder ´so ähnlich ....

// TODO: std  initializer list ... zur Initialisierung einer Permutation ....

// TODO: Lässt sich da  ein emplace_back anwenden !?!?! bei den Kontruktoren der Permutationen bei dem internen Vektor 

// TODO: Umbenennen in count:     int Size() const { return static_cast<int>(m_array.size()); }

// TODO: Auch eine VERSION mit den std::perm von der Standard-Bibliothek implementieren !!!

// TODO: Bei den ITeratoren wird es etwas schwieriger: Wenn man alles auf einmal implementiert,
// dann wird der Memory Bedarf zu groß !!!!!!!

// TODO: noexcept

// TODO: UDL User defined Literal :   123123_perm !!!

// TODO: inline

// TODO: Methoden in klein umbenennen

// TODO: Der Iterator ist nicht default - constructable .... ist das schlimm ???

// TODO: Das Thema mit den Templates und friend ist offen ... für mich ....

// TODO: Range Bases Loop für Permutation // für COntainer




void Test01_Permutation_ExEx_01();
void Test01_Permutation_ExEx_02();
void Test02_PermutationContainer_ExEx();
void Test03_PermutationCalculator_ExEx_01();
void Test03_PermutationCalculator_ExEx_02();

void Test04_PermutationEnumeration_ExEx();
void Test03_PermutationCalculator_ExEx_03();
void Test02_PermutationContainer_ExExEx();

int main()
{
    //Test01_Permutation_ExEx_01();
    //Test01_Permutation_ExEx_02();
    //Test02_PermutationContainer_ExEx();
    //Test03_PermutationCalculator_ExEx_01();
   // Test03_PermutationCalculator_ExEx_02();

    //Test04_PermutationEnumeration_ExEx();
  //  Test03_PermutationCalculator_ExEx_03();
    //Test02_PermutationContainer_ExExEx();
    Test03_PermutationCalculator_ExEx_03();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
