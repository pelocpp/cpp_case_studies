// =====================================================================================
// Program.cpp
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================


// TODO

// Matrix: Siehe Breyman mit den vielen Template Instanzzierungen ....

// Matrix als Klassentemplate !!!

// Concepts // requires: nur für float, double, long double

// Rule of Zero aufzeigen // demonstrieren

// Modern C++:
// Diese beiden Zeilen aufnehmen:

//double* d1 = new double[10];  // then no initialization is performed — it’s as if you called new double[n] without parentheses, so: The array contains indeterminate(garbage) values.
//double* d2 = new double[10] {};  // then the array is value - initialized, meaning: All elements are initialized to 0.0.

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#include <exception>
#include <print>

void test_01();
void test_02();
void test_03();
void test_04();
void test_05();
void test_06();
void test_07();
void test_08();

void test_000();

int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        test_000();
    }
    catch (std::invalid_argument const& ex)
    {
        std::println("{}", ex.what());
    }
    catch (std::exception const& ex)
    {
        std::println("{}", ex.what());
    }


    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
