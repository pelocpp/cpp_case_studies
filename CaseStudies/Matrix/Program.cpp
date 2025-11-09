// =====================================================================================
// Program.cpp
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================

// Youtube

// TODO

// Es fehlen bei den Vektor und Matrix-Klassen die Vergleichsoperatoren == und !=
// Das könnte man möglicherweise modern machen ...............
    //// testing vector comparison
    //int comparison = isEqual(vector1, vector2, 3);
    //comparison = isUnequal(vector1, vector2, 3);



// Rule of Zero aufzeigen // demonstrieren
// Vorsicht:
// Da ist doch Rule-of-Three / Five zu implementieren,
// weil trotzt SmartPointer  keine echte Kopie entsteht !!!


// TODO:
// Hmmm, generelle Frage:
// Aus Vector ... und Matrix (??) könnte man einen STL Container machen ????

// Modern C++:
// Diese beiden Zeilen aufnehmen:

//double* d1 = new double[10];  // then no initialization is performed — it’s as if you called new double[n] without parentheses, so: The array contains indeterminate(garbage) values.
//double* d2 = new double[10] {};  // then the array is value - initialized, meaning: All elements are initialized to 0.0.

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#include <exception>
#include <print>

void test_vector();
void test_matrix();
void test_bad_matrix();
void test_linear_equation();

int main()
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        test_matrix();
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
