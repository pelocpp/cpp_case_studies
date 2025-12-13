// =====================================================================================
// CowStringProgram.cpp // Simple implementation of a COW string class
// =====================================================================================

#include "CowString.h"

#include <print>

namespace CowStringSimple
{
    static void test_cow_string_01()
    {
        CowString a;
    }

    static void test_cow_string_02()
    {
        CowString a{ "1234567890" };
        std::println("String: {}", a.c_str());
        std::println("Length: {}", a.size());
    }

    static void test_cow_string_03()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
    }

    static void test_cow_string_04()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        c[0] = '!';
    }

    static void test_cow_string_05()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        CowString x{ "ABC" };
        CowString y{ x };

        a = x;
    }

    static void test_cow_string_06()
    {
        CowString a{ "Hello World" };
        CowString b{ a };  // shares buffer
        CowString c{ b };  // shares buffer

        std::println("Before modification:");
        std::println("a: {}", a.c_str());
        std::println("b: {}", b.c_str());
        std::println("c: {}", c.c_str());

        b[0] = 'h'; // triggers copy-on-write only for 'b'
        b[6] = 'w'; // triggers copy-on-write only for 'b'

        std::println("After modification:");
        std::println("a: {}", a.c_str());  // unchanged
        std::println("b: {}", b.c_str());  // modified
        std::println("c: {}", c.c_str());  // unchanged
    }
}

void test_cow_string_simple()
{
    using namespace CowStringSimple;

    std::println("Testing CowString:");

    test_cow_string_01();
    test_cow_string_02();
    test_cow_string_03();
    test_cow_string_04();
    test_cow_string_05();
    test_cow_string_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
