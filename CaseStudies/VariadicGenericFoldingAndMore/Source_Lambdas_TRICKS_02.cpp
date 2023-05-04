#include <iostream>
#include <concepts>
#include <string>
#include <type_traits>
#include <format>

#include <algorithm>

#include<array>
#include<iostream>
#include<type_traits>
#include<vector>
#include<tuple>

// ==============================================

// https://www.cppstories.com/2020/08/c-lambda-week-some-tricks.html/

// https://www.cppstories.com/2020/07/lambdas5ex.html/

// https://iamsorush.com/posts/cpp-variadic-template/

// https://iamsorush.com/posts/cpp-meta-function/#introduction




// ==============================================

namespace GenericExample05 {

    // Pack in initializer_list


    template <typename T>
    struct is_std_array : public std::false_type {};

    template <typename V, size_t n>
    struct is_std_array<std::array<V, n>>
        : public std::true_type {};


    template<typename ... Ts>
    auto GetInfo(const Ts& ... args) {
        std::vector<std::string> types{};
        std::vector<int> sizes{};
        
        ([&]()
            {
                if constexpr (std::is_same_v<int, Ts>) {
                    types.push_back("int");
                    sizes.push_back(1);
                }
                else if constexpr (is_std_array<Ts>::value) {
                    types.push_back("std::array");
                    sizes.push_back(args.size());
                }
            }
            ()
                , ...);
        return std::make_tuple(types, sizes);
    }

    void test_lambdas_tricks()
    {
        std::array<int, 5> arr;
        auto [types, sizes] = GetInfo(10, arr);

        for (size_t i = 0; i < types.size(); i++)
            std::cout << "type:" << types[i]
            << " size:" << sizes[i] << "\n";
    }
}

// ==============================================


namespace GenericExample06 {

    // Combine predicates with logical conjunction

    template <typename F, typename A, typename B>
    auto combine(F binary_func, A a, B b)
    {
        return [=](auto param) {
            return binary_func(a(param), b(param));
        };
    }

    void test_lambdas_tricks()
    {
        auto begins_with = [](const std::string& s) {
            return s.find("a") == 0;
        };

        auto ends_with = [](const std::string& s) {
            return s.rfind("b") == s.length() - 1;
        };

        auto bool_and = [](const auto& l, const auto& r) {
            return l && r;
        };

        std::copy_if(
            std::istream_iterator<std::string>{std::cin}, {},
            std::ostream_iterator<std::string>{std::cout, " "},
            combine(bool_and, begins_with,ends_with)
        );

        std::cout << '\n';
    }
}

// ==============================================


namespace GenericExample07 {

    // Combine predicates with logical conjunction

    //template <typename F, typename A, typename B>
    //auto combine(F binary_func, A a, B b)
    //{
    //    return [=](auto param) {
    //        return binary_func(a(param), b(param));
    //    };
    //}

    auto combine(auto binary_func, auto a, auto b)
    {
        return [=](auto param) {
            return binary_func(a(param), b(param));
        };
    }

    void test_lambdas_tricks()
    {
        auto begins_with = [](const std::string& s) {
            return s.find("a") == 0;
        };

        auto ends_with = [](const std::string& s) {
            return s.rfind("b") == s.length() - 1;
        };

        auto bool_and = [](const auto& l, const auto& r) {
            return l && r;
        };

        std::copy_if(
            std::istream_iterator<std::string>{std::cin}, {},
            std::ostream_iterator<std::string>{std::cout, " "},
            combine(bool_and, begins_with, ends_with)
        );

        std::cout << '\n';
    }
}

// ==============================================


namespace GenericExample08 {

    // Combine predicates with logical conjunction

    auto combine(const auto& binary_func, auto a, auto b)
    {
        return [=] (auto param) {
            return binary_func(a(param), b(param));
        };
    };

    void test_lambdas_tricks()
    {
        auto begins_with = [] (const std::string& s) {
            return s.find("a") == 0;
        };

        auto ends_with = [] (const std::string& s) {
            return s.rfind("b") == s.length() - 1;
        };

        auto bool_and = [] (const auto& l, const auto& r) {
            return l && r;
        };

        // WEITER: Hier auch ein bool ODER ...

        std::vector <std::string> in{ "aabb", "bbaa", "foo", "bar", "abazb" };

        std::vector <std::string> out;

        std::copy_if(
            in.begin(),
            in.end(),
            std::back_inserter(out),
            combine(bool_and, begins_with, ends_with)
        );

        for (const auto& s : out) {
            std::cout << s << " ";
        }

        std::cout << '\n';
    }
}



// WEITER
// https://iamsorush.com/posts/cpp-variadic-template/

// ==============================================

void test_lambdas_tricks()
{
    //GenericExample01::test_lambdas_tricks();
    //GenericExample02::test_lambdas_tricks();
    //GenericExample03::test_lambdas_tricks();
    //GenericExample04::test_lambdas_tricks();
    // GenericExample05::test_lambdas_tricks();
    // GenericExample06::test_lambdas_tricks();
    //GenericExample07::test_lambdas_tricks();
    //GenericExample08::test_lambdas_tricks();
}

// ==============================================
