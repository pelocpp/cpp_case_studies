// =====================================================================================
// Program.cpp
// https://github.com/pelocpp/cpp_case_studies    // https://peterloos.de
// =====================================================================================


// Guter Link zur Mathe:
// https://www.matheretter.de/wiki/eigenvektor-eigenwert-geometrische-deutung

// Invertieren einer Matrix:
// https://www.geeksforgeeks.org/dsa/adjoint-inverse-matrix/

// Markdown:
// https://www.geeksforgeeks.org/google-docs/how-to-insert-matrix-in-google-docs/




// Weiterarbeit:
// Habe da eine Matrix auf dem Internet
// ==============> NotizzettelMatrix.txt
// C++ for Financial Mathematics from John Armstrong






// Weiterarbeit:

// Frage:
// I'm implementing a C++ class for matrices. Does it make sense, to implement this class in the manner as a C++ container class?

// https://chatgpt.com/share/69136761-da80-8007-ac79-e3735a306944

// aber warum nicht !?!?!
// Das Kopieren funkioniert jetzt .........................



// TODO

// Es fehlen bei den Vektor und Matrix-Klassen die Vergleichsoperatoren == und !=
// Das könnte man möglicherweise modern machen ...............
    //// testing vector comparison
    //int comparison = isEqual(vector1, vector2, 3);
    //comparison = isUnequal(vector1, vector2, 3);

// Die brauche ich bei der LU Zerlegung, um das Erbenis kontrollieren zu können !!!!




//   if (m_matrix.at(perms[k], k) == 0.0) {   // Hmmm, das ist ein Vergleich mit 0.0 ... das geht besser ...
// Hmmm, das Thema "double Vergleich mit 0.0" ist oder bleibt wohl offen


// Rule of Zero aufzeigen // demonstrieren
// Vorsicht:
// Da ist doch Rule-of-Three / Five zu implementieren,
// weil trotzt SmartPointer  keine echte Kopie entsteht !!!


// Modern C++:
// Diese beiden Zeilen aufnehmen:

//double* d1 = new double[10];  // then no initialization is performed — it’s as if you called new double[n] without parentheses, so: The array contains indeterminate(garbage) values.
//double* d2 = new double[10] {};  // then the array is value - initialized, meaning: All elements are initialized to 0.0.


// ChatGPT Dialog:
// Ich möchte ein lineares Gleichungssystem mit dem Varfahren von Gauss lösen.
// Dabei soll die Betrachtung von Pivot-Elementen mit berücksichtig werden.
// Ich hätte gerne ein Beispiel, dass die Lösung Schritt für Schritt aufzeigt.
// Exemplarisch sind auch Anweisungen in C++ erwünscht.


// To be Done:
// Habe jetzt alle printer in den Includes nach dem Inclusion Modell
// Hmm, müsste man das auch nicht rausziehen ................
// Sollte ich eher am Ende machen, sonst wird es unübersichtlich ....



// Determinantenberechnung
// Habe diese hier vorgefunden
//// =====================================================================================
//// Laplace Expansion Theorem
//
//// See here
//// https://www.bigdev.de/2013/04/tutorial-determinant-in-java.html
//



// =====================================================================================

#include <exception>
#include <print>

void test_vector();
void test_matrix();
void test_bad_matrix();

void test_linear_equation_solver_gauss();
void test_linear_equation_solver_lu_decomposition();

void test_determinant();
void test_lu_decomposition();
void test_invertable_matrix();

int main()
{   
    try
    {
        test_determinant();
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
