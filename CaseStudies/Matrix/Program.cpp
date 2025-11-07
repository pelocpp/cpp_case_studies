// =====================================================================================
// Program.cpp
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

// Youtube

// TODO

// Es fehlen bei den Vektor und Matrix-Klassen die Vergleichsoperatoren == und !=
// Das könnte man möglicherweise modern machen ...............

// Rule of Zero aufzeigen // demonstrieren
// Vorsicht:
// Da ist doch Rule-of-Three / Five zu implementieren,
// weil trotzt SmartPointer  keine echte Kopie entsteht !!!

// Modern C++:
// Diese beiden Zeilen aufnehmen:

//double* d1 = new double[10];  // then no initialization is performed — it’s as if you called new double[n] without parentheses, so: The array contains indeterminate(garbage) values.
//double* d2 = new double[10] {};  // then the array is value - initialized, meaning: All elements are initialized to 0.0.

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#include <exception>
#include <print>

void test_vector_01();
void test_matrix();
void test_bad_matrix();
void test_linear_equation();

int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        test_linear_equation();
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
