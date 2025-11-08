// =====================================================================================
// ProgramVector.cpp
// =====================================================================================

#include "Vector.h"

#include <print>

static void test_vector_01()
{
    Vector<double> vector1{ 3 };
    Vector<double> vector2{ 3, { 3, 6, 9 } };
    Vector<double> vector3{ 3, { 3, 6, 9 } };

    // testing vector initialization (zero vector)
    vector1.print();
    vector2.print();
    vector3.print();

    // testing vector dimension and length
    std::size_t dimension{ vector1.dimension() };
    std::println("Dimension: {}", dimension);
    double length{ vector1.length() };
    std::println("Length: {}", length);

    // testing vector normalization
    Vector<double> result{ vector1.normalize()};
    std::println("Normalization: ");
    result.print();
 
    // testing vector addition
    result = vector2 + vector3;
    result.print();

   
    //// testing vector addition
    //vectorAdd(result, vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" + ");
    //vectorPrint(vector2, 3);
    //printf(" = ");
    //vectorPrint(result, 3);
    //printf("");

    //// testing scalar multiplication
    //vectorScalarMul(result, vector1, 3, 10.0);
    //printf(" 10 ");
    //printf(" * ");
    //vectorPrint(vector1, 3);
    //printf(" = ");
    //vectorPrint(result, 3);
    //printf("");

    //// testing scalar product
    //double product = vectorScalarProduct(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" * ");
    //vectorPrint(vector2, 3);
    //printf(" = %lf  [scalar product]", product);

    // ===========================================

    //// testing vector comparison
    //int comparison = isEqual(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" == ");
    //vectorPrint(vector2, 3);
    //printf(" : %d", comparison);

    //comparison = isUnequal(vector1, vector2, 3);
    //vectorPrint(vector1, 3);
    //printf(" != ");
    //vectorPrint(vector2, 3);
    //printf(" : %d", comparison);

    //comparison = isEqual(vector1, vector1, 3);
    //vectorPrint(vector1, 3);
    //printf(" == ");
    //vectorPrint(vector1, 3);
    //printf(" : %d", comparison);
}

void test_vector()
{
    test_vector_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
