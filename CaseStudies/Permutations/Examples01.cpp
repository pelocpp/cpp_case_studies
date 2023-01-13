// =====================================================================================
// Examples01.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationCalculator.h"
#include "PermutationIterator.h"
#include <algorithm>

void Test01_Permutation_Errors();
void Test01_Permutation();
void Test02_PermutationArray();
void Test03_PermutationCalculator();
void Test04_PermutationEnumeration();

void Test01_Permutation_Errors()
{
    try {
        // permutation constructor throws an invalid_argument if
        // initialized with a string containing multiple characters
        Permutation p{ "ABA" };
        std::cout <<p << std::endl;
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "Invalid argument: " << ia.what() << std::endl;
    }

    try {
        // permutation constructor throws an invalid_argument if
        // initialized with a list containing multiple characters
        Permutation p{ '1', '2', '3', '4', '5' };
        std::cout << p << std::endl;
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "Invalid argument: " << ia.what() << std::endl;
    }

    try {
        // permutation constructor throws an invalid_argument if
        // initialized with a list containing multiple characters
        std::vector<char> chars = { 'X', 'Y', 'Z' };
        Permutation p{ chars };
        std::cout << p << std::endl;
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "Invalid argument: " << ia.what() << std::endl;
    }
}

void Test01_Permutation()
{
    std::cout << "Testing c'tor: " << std::endl;
    Permutation p1{ "ABC" };
    std::cout << p1 << std::endl;

    std::cout << "Testing insertAtFront: " << std::endl;
    p1.insertAtFront('Z');
    std::cout << p1 << std::endl;

    Permutation p2{ '1', '2', '3', '4', '5' };
    std::cout << p2 << " [Number of Elements: " << p2.grade() << ']' << std::endl;

    std::cout << "Testing []-Operator: " << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        char c = p2[i];
        std::cout << i << ": " << c << std::endl;
    }

    Permutation p3 = p2;
    std::cout << "Testing removeAt: " << p3 << std::endl;
    for (int i = 0; i < p2.grade(); i++)
    {
        p3 = p3.removeAt(0);
        std::cout << i << ": " << p3 << std::endl;
    }
}

void Test01_Permutation_Iteration()
{

    //std::vector<char> vec;

    //using x = std::array<char, 5>::difference_type;

    //x aha = 0;


    // testing range based loop
    Permutation p{ "ABCDE" };
    for (char ch : p) {
        std::cout << ch << std::endl;
    }

    // testing STL compliance ot iterator implementation
    Permutation q{ '5', '4', '3', '2', '1' };
    std::cout << q << std::endl;

// https://stackoverflow.com/questions/55940777/custom-iterator-for-use-in-stdsort

//https://www.walletfox.com/course/sortvectorofcustomobjects.php
//
//https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp   // seeeeeeeehr gut
//
//https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/


    // DAs ist nicht übersetzungsfähig

    //std::sort(std::begin(q), std::end(q), [](auto a, auto b) -> bool { return true; });
    //std::cout << std::endl;

    // =======================================

    // https://www.geeksforgeeks.org/stdminmax-stdminmax_element-c-stl/

   //  // declaring pair pointer to catch the return value 
   // std::pair<PermutationIterator, PermutationIterator> mnmx;

   //// std::pair<int, int> bounds = std::minmax(std::rand() % v.size(), std::rand() % v.size());

   // mnmx =  std::minmax_element(std::begin(q), std::end(q));

   // // printing position of minimum and maximum values. 
   // std::cout << "The minimum value position obtained is : ";
   // std::cout << mnmx.first - q.begin() << std::endl;

   // std::cout << "The maximum value position obtained is : ";
   // std::cout << mnmx.second - q.begin() << std::endl;



    std::cout << q << std::endl;
}

void Test02_PermutationArray()
{
    Permutation p{ "ABC" };
    Permutation q{ "CBA" };
    PermutationArray array(2);
    array.insert(p);
    array.insert(q);
    std::cout << array << std::endl;
}

void Test02_PermutationArray_02()
{
    PermutationArray array(4);
    array.emplace({ "ABC" });
    array.emplace({ "CBA" });
    std::cout << array << std::endl;
    array.emplace({ 'B', 'C', 'A' });
    array.emplace({ 'B', 'A', 'C' });
    std::cout << array << std::endl;
}

void Test03_PermutationCalculator()
{
    Permutation p("ABC");
    PermutationCalculator calc;
    PermutationArray result = calc.calculate(p);
    std::cout << result << std::endl;
}

void Test03_PermutationCalculator_02()
{
    Permutation p("XYZ");
    PermutationCalculator calc;
    PermutationArray result = calc.calculateEx(p);
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

// =====================================================================================
// End-of-File
// =====================================================================================
