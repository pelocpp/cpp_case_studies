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

    // assignment operators
    vector1[0] = 1.0;
    vector1[1] = 1.0;
    vector1[2] = 1.0;
    vector1.print();

    const double& elem = vector1[0];
    std::println("First element: {}", elem);

    // overload resolution of operator[] is based on the this parameter,
    // that is - on the constness or lack of constness of the object the operator[] is being called upon
    const Vector<double> vector4{ 3, { 1, 2, 3 } };
    const double& elem2 = vector4[0];
    std::println("First element: {}", elem2);
}


static void test_vector_02()
{
    // testing length and normalization
    Vector<double> vector{ 3, { 2, 2, 1 } };
    vector.print();

    // testing vector dimension and length
    std::size_t dimension{ vector.dimension() };
    std::println("Dimension: {}", dimension);
    double length{ vector.length() };
    std::println("Length: {}", length);


    // testing vector normalization
    Vector<double> result{ vector.normalize() };
    std::println("Normalized Vector: ");
    result.print();


    length = result.length();
    std::println("Length of normalized vector: {}", length);
}

static void test_vector_03()
{
    Vector<double> vector1{ 3 };
    Vector<double> vector2{ 3, { 1, 2, 3 } };
    Vector<double> vector3{ 3, { 4, 5, 6 } };

    // testing vector initialization (zero vector)
    vector1.print();
    vector2.print();
    vector3.print();

    // assignment operators
    vector1[0] = 1.0;
    vector1[1] = 1.0;
    vector1[2] = 1.0;
    vector1.print();

    // testing vector addition
    Vector<double> result = vector2 + vector3;
    result.print();

    // testing vector subtraction
    result = vector2 - vector3;
    result.print();

    // testing vector scalar multiplication
    result = vector2 * 5;  // hmm: 5 * vector2 geht nicht ?!?!??!
    result.print();
}

void test_vector()
{
    test_vector_01();
    test_vector_02();
    test_vector_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
