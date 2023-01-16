// =====================================================================================
// Program.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>


// TODO: Auch eine VERSION mit den std::perm von der Standard-Bibliothek implementieren !!!

// TODO: UDL User defined Literal :   123123_perm !!!

// TODO: inline

// TODO: Das Thema mit den Templates und friend ist offen ... für mich ....


// Das mit den mehreren gleichen Werten testen ???????
//    try {
//        // permutation constructor throws an invalid_argument if
//        // initialized with a string containing multiple characters
//        Permutation p{ "ABA" };
//        std::cout <<p << std::endl;
//    }
//    catch (const std::invalid_argument& ia) {
//        std::cout << "Invalid argument: " << ia.what() << std::endl;
//    }


void Test_Permutation_01();
void Test_Permutation_02();
void Test_Permutation_03();
void Test_Permutation_04();

void Test_PermutationContainer_01();
void Test_PermutationContainer_02();

void Test_PermutationCalculator_01();
void Test_PermutationCalculator_02();
void Test_PermutationCalculator_03();
void Test_PermutationCalculator_04();

void Test_UDL_01();

int main()
{
    //Test_Permutation_01();
    //Test_Permutation_02();
    //Test_Permutation_03();
    //Test_Permutation_04();

    //Test_PermutationContainer_01();
    //Test_PermutationContainer_02();
    //
    //Test_PermutationCalculator_01();
    //Test_PermutationCalculator_02();
    //Test_PermutationCalculator_03();
    //Test_PermutationCalculator_04();

    Test_UDL_01();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
