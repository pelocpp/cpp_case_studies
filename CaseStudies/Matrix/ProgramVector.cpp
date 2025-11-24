// =====================================================================================
// ProgramVector.cpp
// =====================================================================================

#include "Vector.h"

#include <print>

static void test_vector_01()
{
    Vector<double> vector1{};
    Vector<double> vector2{ 3, { 1, 2, 3 } };
    Vector<double> vector3{ 3, { 1, 2, 3 } };

    // testing vector initialization
    vector1.print();
    vector2.print();
    vector3.print();

    // testing vector dimension and length
    std::size_t dimension{ vector1.dimension() };
    std::println("Dimension: {}", dimension);
    double length{ vector1.length() };
    std::println("Length: {}", length);
    dimension = vector2.dimension();
    std::println("Dimension: {}", dimension);
    length = vector2.length();
    std::println("Length: {}", length);

    // assignment operators
    vector2[0] = 1.0;
    vector2[1] = 1.0;
    vector2[2] = 1.0;
    vector2.print();

    const double& elem = vector2[0];
    std::println("First element: {}", elem);

    // overload resolution of operator[] is based on the 'this' parameter,
    // that is - on the constness or lack of constness of the object - the operator[] is being called upon
    const Vector<double> vector4{ 3, { 1, 2, 3 } };
    const double& elem2 = vector4[0];
    std::println("First element: {}", elem2);
}

static void test_vector_02()
{
    // testing length and normalization
    Vector<double> vector{ 3, { 2, 2, 1 } };
    vector.print();

    // testing vector normalization
    Vector<double> result{ vector.normalize() };
    std::println("Normalized Vector: ");
    result.print();

    double length{ result.length() };
    std::println("Length of normalized vector: {}", length);
}

static void test_vector_03()
{
    Vector<double> vector1{ 3, { 1, 2, 3 } };
    Vector<double> vector2{ 3, { 4, 5, 6 } };

    vector1.print();
    vector2.print();

    // testing vector addition
    Vector<double> result{ vector1 + vector2 };
    result.print();

    // testing vector subtraction
    result = vector1 - vector2;
    result.print();

    // testing vector scalar multiplication
    result = vector2 * 5;
    result.print();

    // testing vector scalar product
    double scalarProduct{ vector1 * vector2 };
    std::println("Scalar Product: {}", scalarProduct);

    // testing arithmetic assignment operators
    vector1 += vector2;
    vector1.print();

    vector1 -= vector2;
    vector1.print();
}

static void test_vector_04()
{
    Vector<double> vector1{ 3, { 1, 2, 3 } };
    Vector<double> vector2{ 3, { 1, 2, 3 } };

    auto b{ vector1 == vector2};
    std::println("operator==: {}", b);

    vector1[0] = 123;

    b = (vector1 == vector2);
    std::println("operator==: {}", b);

    b = (vector1 != vector2);
    std::println("operator!=: {}", b);
}

static void test_vector_10()
{
    // testing std::prinln for template class Vector<>
    Vector<double> vector1{ 3, { 1.0, 2.0, 3.0 } };
    std::println("Vector<double>: {}", vector1);
}

void test_vector()
{
    //test_vector_01();
    //test_vector_02();
    //test_vector_03();
    //test_vector_04();

    test_vector_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
