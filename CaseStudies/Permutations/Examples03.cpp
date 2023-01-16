// =====================================================================================
// Examples03.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>

#include "_Permutation.h"
#include "_PermutationContainer.h"
#include "_PermutationCalculatorExEx.h"

//#include "PermutationArrayEx.h"
//#include "PermutationCalculatorEx.h"

void Test01_Permutation_ExEx_01();
void Test02_PermutationContainer_ExEx();


//void Test02_PermutationArray_Ex();
//void Test03_PermutationCalculator_Ex_01();
//void Test03_PermutationCalculator_Ex_02();
//void Test04_PermutationEnumeration_Ex();

void Test01_Permutation_ExEx_01()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationExEx<char> p{ 'A', 'B', 'C' };
    std::cout << p << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront('Z');
    std::cout << p << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (size_t i{}; i != p.grade(); ++i)
    {
        char ch = p[i];
        std::cout << i << ": " << ch << std::endl;
    }

    std::cout << "Testing removeAt: " << std::endl;
    while (true) {
        p = p.removeAt(0);
        std::cout << p << std::endl;
        if (p.grade() == 0) {
            break;
        }
    }
}

void Test01_Permutation_ExEx_02()
{
    std::cout << "Testing c'tor: " << std::endl;
    PermutationExEx<char> p{ 'A', 'B', 'C' };
    std::cout << p << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p.insertAtFront('Z');
    std::cout << p << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (size_t i{}; i != p.grade(); ++i)
    {
        char ch = p[i];
        std::cout << i << ": " << ch << std::endl;
    }

    std::cout << "Testing removeAt: " << std::endl;
    while (true) {
        p = p.removeAt(0);
        std::cout << p << std::endl;
        if (p.grade() == 0) {
            break;
        }
    }
}

void Test02_PermutationContainer_ExEx()
{
    PermutationExEx<int> p({ 1, 2, 3, 4 });
    std::cout << p << std::endl;
    PermutationExEx<int> q({ 4, 3, 2, 1 });
    std::cout << q << std::endl << std::endl;

    PermutationContainer<int> container(2);
    container.insert(p);
    container.insert(q);
    std::cout << container << std::endl;
}

void Test02_PermutationContainer_ExExEx()
{
    using namespace std::complex_literals;
    //PermutationExEx<std::complex<double>> p({ 1. + 2i, 3. + 4i, 5. + 6i });
    //PermutationCalculatorExEx<std::complex<double>> calc;
    //PermutationContainer<std::complex<double>> result = calc.calculate(p);
    //std::cout << result << std::endl;

}

void Test03_PermutationCalculator_ExEx_01()
{
    //PermutationExEx<char> p{ 'A', 'B', 'C' };
    //PermutationCalculatorExEx<char> calc;
    //PermutationContainer<char> result = calc.calculate(p);
    //std::cout << result << std::endl;
}

void Test03_PermutationCalculator_ExEx_02()
{
    //PermutationExEx<int> p({ 1, 2, 3, 4 });
    //PermutationCalculatorExEx<int> calc;
    //PermutationContainer<int> result = calc.calculate(p);
    //std::cout << result << std::endl;
}

void Test04_PermutationEnumeration_ExEx()
{
    PermutationExEx<int> p({ 1, 2, 3, 4 });
    for (auto n : p) {
        std::cout << "Next Element: " << n << std::endl;
    }
}

void Test03_PermutationCalculator_ExEx_03()
{
    PermutationExEx<int> p({ 1, 2, 3, 4 });
    PermutationCalculatorExEx<int> calc;
    PermutationContainer<int> result = calc.calculate(p);

    for (const auto& perm : result) {
        std::cout << "Next Permutation: " << perm << std::endl;
    }
}




//void Test04_PermutationEnumeration_Ex()
//{
//    //Permutation p("ABCD");
//    //PermutationCalculator calc;
//    //calc.SetPermutation(p);
//    //calc.Calculate();
//
//    //calc.Reset();
//    //while (calc.MoveNext())
//    //{
//    //    Permutation q = calc.Current();
//    //    std::cout << "Next Permutation: " << q << std::endl;
//    //}
//}

// =====================================================================================
// End-of-File
// =====================================================================================
