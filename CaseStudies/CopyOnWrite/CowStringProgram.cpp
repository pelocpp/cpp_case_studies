// =====================================================================================
// CowStringProgram.cpp // Simple implementation of a COW string class
// =====================================================================================

#include "CowString.h"

#include <print>
#include <string_view>

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
        CowString a{ "1234567890", 5 };
        std::println("String: {}", a.c_str());
        std::println("Length: {}", a.size());
    }

    static void test_cow_string_04()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
    }

    static void test_cow_string_05()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        c[0] = '!';
    }

    static void test_cow_string_06()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        CowString x{ "ABC" };
        CowString y{ x };

        a = x;
    }

    static void test_cow_string_07()
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

    static void test_cow_string_08()
    {
        CowString s{ "1234567890" };
        const char* p{ s.c_str() };

        {
            // in this block the contents of `s` is not modified
            CowString other{ s };
            char first_char{ s[0] };
        }

        std::println("After block:");
        std::println("p: {}", p);      // p is no more valid!
    }

    static void test_cow_string_09()
    {
        CowString s{ "1234567890" };
        const char* p{ s.c_str() };

        //{
            // in this block the contents of `s` is not modified
            CowString other{ s };
            char first_char{ s[0] };
        //}

        std::println("After block:");
        std::println("p: {}", p);      // p is no more valid!
    }

    static void test_cow_string_10()
    {
        CowString s{ "1234567890" };

        std::string_view sv{ s };
        std::println("sv: {}", sv);

        s[9] = '!';

        std::string_view sv1 = s;
        std::println("sv: {}", sv);
        std::println("sv1: {}", sv1);
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
    test_cow_string_07();
    test_cow_string_08();   // geht NICHT !!! Beschreiben !!!!!!!!!
    test_cow_string_09();
    test_cow_string_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
