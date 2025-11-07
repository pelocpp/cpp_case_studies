// =====================================================================================
// ProgramVector.cpp
// =====================================================================================

#include "Vector.h"

#include <print>

static void test_vector_01()
{
    Vector<double> vector{ 3 };
    Vector<double> vector1{ 3,{ 3, 6,  8 } };
    Vector<double> vector2{ 3, { 3, 6,  8 } };

    // testing vector initialization (zero vector)
    vector.print();
    vector1.print();
    vector2.print();

    // testing vector length
    std::size_t length = vector1.length();
    std::println("Length = {}\n", length);

    // testing vector normalization
    // das ist falsch implementiert ... Siehe Aufgaben C Grundlagen ....
    Vector<double> result{ vector1.normalize()};


   // vectorNormalize(result, vector1, 3);
    std::println("Normalized: ");
    result.print();
   // length = vectorLength(result, 3);
    std::println("Length = {}", result.length());

    //// testing vector addition
    //vectorAdd(result, vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" + ");
    //vectorPrint(vector2, 3);
    //printf(" = ");
    //vectorPrint(result, 3);
    //printf("\n");

    //// testing scalar multiplication
    //vectorScalarMul(result, vector1, 3, 10.0);
    //printf(" 10 ");
    //printf(" * ");
    //vectorPrint(vector1, 3);
    //printf(" = ");
    //vectorPrint(result, 3);
    //printf("\n");

    //// testing scalar product
    //double product = vectorScalarProduct(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" * ");
    //vectorPrint(vector2, 3);
    //printf(" = %lf  [scalar product]\n", product);

    // ===========================================

    //// testing vector comparison
    //int comparison = isEqual(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" == ");
    //vectorPrint(vector2, 3);
    //printf(" : %d\n", comparison);

    //comparison = isUnequal(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" != ");
    //vectorPrint(vector2, 3);
    //printf(" : %d\n", comparison);

    //comparison = isEqual(vector1, vector1, 3);
    //vectorPrint(vector1, 3);
    //printf(" == ");
    //vectorPrint(vector1, 3);
    //printf(" : %d\n", comparison);
}

void test_vector()
{
    test_vector_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
