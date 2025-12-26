// =====================================================================================
// CowStringProgram.cpp // Simple implementation of a COW string class
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "CowString.h"

#include <print>
#include <string_view>
#include <vector>

namespace COWString
{
    static void test_cow_string_01()
    {
        CowString a;
        std::println("String: {}", a);
        std::println("Length: {}", a.size());
        std::println("Data:   {}", a.c_str());
        std::println();
    }

    static void test_cow_string_02()
    {
        CowString a{ "1234567890" };
        std::println("String: {}", a);
        std::println("Length: {}", a.size());
        std::println("Data:   {}", a.c_str());
        std::println();
    }

    static void test_cow_string_03()
    {
        const char* s = "1234567890";
        CowString a{ s, std::strlen(s) };

        std::println("String: {}", a);
        std::println("Length: {}", a.size());
        std::println("Data:   {}", a.c_str());
        std::println();
    }

    static void test_cow_string_04()
    {
        std::string_view sv{ "1234567890" };
        std::println("sv: {}", sv);
        
        CowString a{ sv };

        std::println("String: {}", a);
        std::println("Length: {}", a.size());
        std::println("Data:   {}", a.c_str());
        std::println();
    }

    static void test_cow_string_05()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
    }

    static void test_cow_string_06()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        c[0] = '!';
    }

    static void test_cow_string_07()
    {
        CowString a{ "1234567890" };
        CowString b{ a };
        CowString c{ a };

        CowString x{ "ABC" };
        CowString y{ x };

        a = x;
    }

    static void test_cow_string_08()
    {
        CowString a{ "Hello World" };
        CowString b{ a };  // shares buffer
        CowString c{ b };  // shares buffer

        std::println("Before modification:");
        std::println("a: {}", a);
        std::println("b: {}", b);
        std::println("c: {}", c);

        b[0] = 'h'; // triggers copy-on-write only for 'b'
        b[6] = 'w'; // triggers copy-on-write only for 'b'

        std::println("After modification:");
        std::println("a: {}", a);  // unchanged
        std::println("b: {}", b);  // modified
        std::println("c: {}", c);  // unchanged
    }

    static void test_cow_string_09()
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

    static void test_cow_string_10()
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

    static void test_cow_string_11()
    {
        CowString s{ "1234567890" };

        std::string_view sv{ s };
        std::println("sv: {}", sv);

        s[9] = '!';

        std::string_view sv1 = s;
        std::println("sv: {}", sv);
        std::println("sv1: {}", sv1);
    }

    static void test_cow_string_12()
    {
        // testing move semantics
        CowString s1{ "1234567890" };
        std::string_view sv1{ s1 };
        std::println("sv: {}", sv1);

        CowString s2{ std::move(s1) };
        std::string_view sv2{ s2 };
        std::println("sv: {}", sv2);

        CowString s3{};
        s3 = std::move(s2);
        std::string_view sv3{ s3 };
        std::println("sv: {}", sv3);
    }

    static void test_cow_string_13()
    {
        // testing move semantics
        CowString s1{ "1234567890" };
        std::string_view sv1{ s1 };
        std::println("sv: {}", sv1);

        CowString s2{ std::move(s1) };
        std::string_view sv2{ s2 };
        std::println("sv: {}", sv2);

        CowString s3{};
        s3 = std::move(s2);
        std::string_view sv3{ s3 };
        std::println("sv: {}", sv3);
    }

    static void test_cow_string_14()
    {
        std::vector<CowString> vec;

        // testing move semantics
        vec.push_back(CowString{ "ABC" });
        vec.push_back(CowString{ "DEF" });
        vec.push_back(CowString{ "GHI" });

        for (const auto& cs : vec) {
            std::println("{}", cs);
        }
    }
}

void main_cow_string()
{
    using namespace COWString;

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    std::println("Testing CowString:");

    test_cow_string_01();
    test_cow_string_02();
    test_cow_string_03();
    test_cow_string_04();
    test_cow_string_05();
    test_cow_string_06();
    test_cow_string_07();
    test_cow_string_08();
    test_cow_string_09();
   // test_cow_string_10();   // crashes - by design
    // test_cow_string_11();
    test_cow_string_12();
    test_cow_string_13();
    test_cow_string_14();
}

// =====================================================================================
// End-of-File
// =====================================================================================
