// =====================================================================================
// ProgramVector.cpp
// =====================================================================================

#include "Vector.h"

#include <print>

static void test_vector_01()
{
    Vector<double> vector1{};
    Vector<double> vector2{ 1.0, 2.0, 3.0 };
    Vector<double> vector3{ 1.0, 2.0, 3.0 };

    // testing vector initialization
    std::println("{}", vector1);
    std::println("{}", vector2);
    std::println("{}", vector3);

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
    std::println("{}", vector2);

    const double& elem = vector2[0];
    std::println("First element: {}", elem);

    // overload resolution of operator[] is based on the 'this' parameter,
    // that is - on the constness or lack of constness of the object - the operator[] is being called upon
    const Vector<double> vector4{ 1.0, 2.0, 3.0 };
    const double& elem2 = vector4[0];
    std::println("First element: {}", elem2);
}

static void test_vector_02()
{
    // testing length and normalization
    Vector<double> vector{ 2.0, 2.0, 1.0 };
    std::println("{}", vector);

    // testing vector normalization
    Vector<double> result{ vector.normalize() };
    std::println("Normalized Vector: ");
    std::println("{}", result);

    double length{ result.length() };
    std::println("Length of normalized vector: {}", length);
}

static void test_vector_03()
{
    Vector<double> vector1{ 1.0, 2.0, 3.0 };
    Vector<double> vector2{ 4.0, 5.0, 6.0 };

    std::println("{}", vector1);
    std::println("{}", vector2);

    // testing vector addition
    Vector<double> result{ vector1 + vector2 };
    std::println("{}", result);

    // testing vector subtraction
    result = vector1 - vector2;
    std::println("{}", result);

    // testing vector scalar multiplication
    result = vector2 * 5;
    std::println("{}", result);

    // testing vector scalar product
    double scalarProduct{ vector1 * vector2 };
    std::println("Scalar Product: {}", scalarProduct);

    // testing arithmetic assignment operators
    vector1 += vector2;
    std::println("{}", vector1);

    vector1 -= vector2;
    std::println("{}", vector1);
}

static void test_vector_04()
{
    Vector<double> vector1{ 1.0, 2.0, 3.0 };
    Vector<double> vector2{ 1.0, 2.0, 3.0 };

    auto b{ vector1 == vector2};
    std::println("operator==: {}", b);

    vector1[0] = 123.0;

    b = (vector1 == vector2);
    std::println("operator==: {}", b);

    b = (vector1 != vector2);
    std::println("operator!=: {}", b);
}

static void test_vector_10()
{
    // testing std::println for template class Vector<>
    Vector<double> vector{ 1.0, 2.0, 3.0 };
    std::println("Vector<double>: {}", vector);
}

void test_vector()
{
    test_vector_01();
    test_vector_02();
    test_vector_03();
    test_vector_04();

    test_vector_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
