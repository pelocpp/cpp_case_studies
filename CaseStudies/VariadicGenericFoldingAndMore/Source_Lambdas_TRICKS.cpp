// =====================================================================================
// VariadicGenericFoldingAndMore.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <type_traits>
#include <cmath>
#include <functional>

// ==============================================

namespace VariadicGenericFolding_01 {

    auto f1(auto ... args) {
        // some code to use args  
    }

    auto f2(auto ... args) {
        std::cout << sizeof...(args) << std::endl;
    }

    void test_variadic_generic_folding_01()
    {
        f1(1, 2, 3);
        f1('1', 123, 987.654, std::string{"xyz"}, 10.0F);

        f2(1, 2, 3);
        f2('1', 123, 987.654, std::string{ "xyz" }, 10.0F);
    }

    auto l1 = [](auto ... args) {
    };

    auto l2 = [](auto ... args) {
        std::cout << sizeof...(args) << std::endl;
    };

    template<typename ... TArgs>
    auto tf1(TArgs ... args) {
        // some code to use args 
        // some code to use Ts   
    };

    template<typename ... TArgs>
    auto tf2(TArgs ... args) {
        std::cout << sizeof...(TArgs) << std::endl;
        std::cout << sizeof...(args) << std::endl;
    };

    void test_variadic_generic_folding_02()
    {
        l1(1, 2, 3);
        l1('1', 123, 987.654, std::string{ "xyz" }, 10.0F);

        l2(1, 2, 3);
        l2('1', 123, 987.654, std::string{ "xyz" }, 10.0F);

        tf1(1, 2, 3);
        tf1('1', 123, 987.654, std::string{ "xyz" }, 10.0F);

        tf2(1, 2, 3);
        tf2('1', 123, 987.654, std::string{ "xyz" }, 10.0F);
    }
}

// ==============================================

namespace VariadicGenericFolding_02 {

    auto sum(auto ... args) {
        return (... + args);     // (((arg1+ arg2) + arg3) + ...)
    }

    void test_variadic_generic_folding_01()
    {
        auto result{ sum(1, 2, 3, 4, 5) };
        std::cout << "Summe: " << result << std::endl;
    }

    void test_variadic_generic_folding_02()
    {
        auto result{ sum(100, 200l, 300ll, 400.0F, 500.0) };
        std::cout << "Summe: " << result << std::endl;
    }

    void test_variadic_generic_folding_03()
    {
        auto concat{ sum(std::string{"ABC"}, std::string{ "DEF" }, std::string{ "GHI" }) };
        std::cout << "Concatenation: " << concat << std::endl;
    }

    auto norm(auto ... args) {
        return std::sqrt(((args * args) + ...));  // sqrt( arg1*arg1 + arg2*arg2 + ...)
    }

    void test_variadic_generic_folding_04()
    {
        auto n{ norm(1.0, 2.0, 3.0, 4.0) };
        std::cout << "Norm: " << n << std::endl;
    }

    auto root (const auto& x) {
        return std::sqrt(x);
    }

    auto sumOfRoots(auto ... args) {
        return (root(args) + ...);
    }

    void test_variadic_generic_folding_05()
    {
        auto sum{ sumOfRoots(4.0F, 9.0F) };
        std::cout << "SumOfRoots: " << sum << std::endl;
    }
}

// ==============================================


namespace VariadicGenericFolding_03 {


    auto sum(auto ... args) {
        return (args + ...);
    }

    auto average(auto ... args) {
        auto result{ sum(args...) };
        return result / sizeof... (args);
    }

    void test_variadic_generic_folding_01()
    {
        auto avg{ average(3.0F, 5.0F, 7.0) };
        std::cout << "Average: " << avg << std::endl;
    }
}

// ==============================================

// looping about a parameter pack

namespace VariadicGenericFolding_04 {

    auto doSomethingWithParameterPack1(auto ... args) {

        int i{};

        auto printElem = [&](auto arg)
        {
            ++i;
            std::cout << "Element " << i << ": " << arg << std::endl;
        };

        ( printElem(args) , ... );
    }


    auto doSomethingWithParameterPack2(auto ... args) {

        auto printElem = [&, i = 0]  (auto arg) mutable
        {
            ++i;
            std::cout << "Element " << i << ": " << arg << std::endl;
        };

        ( printElem(args) , ... );
    }

    auto doSomethingWithParameterPack3(auto ... args) {

        auto printElemToConsole = [] (auto index, auto arg) 
        {
            std::cout << "Element " << index << ": " << arg << std::endl;
        };

        int i{};

        ( [&] { ++i; printElemToConsole(i, args); } () , ... );
    }

    auto doSomethingWithParameterPack4(auto ... args) {

        int i{};

        ([&] { ++i; std::cout << "Element " << i << ": " << args << std::endl; } (), ... );
    }

    void test_variadic_generic_folding_01()
    {
        doSomethingWithParameterPack1(123, 234.234, '?', std::string{ "XYZ" });
        doSomethingWithParameterPack2(12345, 234.234, '?', std::string{ "XYZ" });
        doSomethingWithParameterPack3(123, 234.234, '?', std::string{ "XYZ" });
        doSomethingWithParameterPack4(12345, 234.234, '?', std::string{ "XYZ" });
    }
}

// ==============================================


namespace VariadicGenericFolding_05 {

    // end of recursion: one parameter left
    auto sum(auto elem) {
        return elem;
    }

    // recursive case: 2 or more parameters
    auto sum(auto first, auto ... args) {
        return first + sum (args ...);
    }

    // ---------------------
    // using template syntax

    // end of recursion: one parameter left
    template <typename T>
    auto sum2(T elem) {
        return elem;
    }

    // recursive case: 2 or more parameters
    template <typename T, typename ... TArgs>
    auto sum2(T first, TArgs ... args) {
        return first + sum2(args ...);
    }

    // ---------------------
    // using lambda syntax

    // NOTE: "Overloading" is not possible
    // https://stackoverflow.com/questions/58700542/overload-a-lambda-function
    //The // lambdas are anonymous functors(i.e.unnamed function objects), and not simple functions.
    //Therefore, overloading those objects not possible.

    // end of recursion: one parameter left
    //auto sum3 = [](auto elem) {
    //    return elem;
    //};

    // recursive case: 2 or more parameters
    //auto sum3 = [](auto first, auto ... args) {
    //    return first + sum3(args ...);
    //};


    // But:
    auto sum3 = [](auto first, auto ... args) {

        if constexpr (sizeof... (args) == 0) {
            return first;
        }
        else {
            return first + sum3(args ...);
        }
    };


    void test_variadic_generic_folding_01()
    {
        auto result{ sum(1, 2, 3, 4, 5) };
        std::cout << "Summe: " << result << std::endl;

        result = sum2(6, 7, 8, 9, 10);
        std::cout << "Summe: " << result << std::endl;

        auto result2 = sum3(3.3, 4.4, 5.5);
        std::cout << "Summe: " << result2 << std::endl;
    }
}

// ==============================================

namespace VariadicGenericFolding_10 {

    auto genericIncrementer = [] (auto x) {
        return [=] (auto y) {
            return x + y;
        };
    };

    void test_variadic_generic_folding_01()
    {
        auto incrementByTen{ genericIncrementer(10) };

        auto result{ incrementByTen(10) };
        std::cout << "Result: " << result << std::endl;

        auto incrementByFive{ genericIncrementer(5) };
        result = incrementByFive(10);
        std::cout << "Result: " << result << std::endl;
    }

    void test_variadic_generic_folding_02()
    {
        auto result{ genericIncrementer(10)(5) };
        std::cout << "Result: " << result << std::endl;
    }

    void test_variadic_generic_folding_03()
    {
        std::function<int(int)> incrementByTen{ genericIncrementer(10) };

        auto result{ incrementByTen(5) };
        std::cout << "Result: " << result << std::endl;

        std::function<int(int)> incrementByFive{ genericIncrementer(5) };
        result = incrementByFive(10);
        std::cout << "Result: " << result << std::endl;
    }
}

namespace VariadicGenericFolding_11 {

    auto square = [] (auto x) {
        return x * x;
    };

    auto power = [](auto x, size_t n) {
        auto result{ x };

        for (size_t i{ 1 }; i < n; ++i) {
            result *= x;
        } 

        return result;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = power(2, 5);
        std::cout << "power(2, 5): " << twoPowerFive << std::endl;
    }
}

namespace VariadicGenericFolding_12 {

    auto timesTwo = [](auto x) {
        return 2 * x;
    };

    auto powerByTwo = [](auto x, size_t n) {
        auto result{ x };

        for (size_t i{ 1 }; i < n; ++i) {
            result = timesTwo(result);
        }

        return result;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = powerByTwo(2, 5);
        std::cout << "twoPowerFive: " << twoPowerFive << std::endl;
    }
}

namespace VariadicGenericFolding_13 {

    auto timesTwo = [](auto x) {
        return 2 * x;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = timesTwo(timesTwo(timesTwo(timesTwo(2))));  // 2*2*2*2*2
        std::cout << "twoPowerFive: " << twoPowerFive << std::endl;
    }
}


namespace VariadicGenericFolding_14 {

    //template <typename T, typename ...Ts>
    //auto combine(T t, Ts ...ts)
    //{
    //    if constexpr (sizeof...(ts) > 0)
    //    {
    //        return [&](auto ...parameters) {
    //            // return t(concat(ts...)(parameters...));

    //            auto result = t(concat(ts...) (parameters...));

    //            return result;
    //        };
    //    }
    //    else
    //    {
    //        return t;
    //    }
    //}

    auto combine(auto func, auto ... funcs)
    {
        if constexpr (sizeof...(funcs) > 0)
        {
            return [&] (auto ... parameters) {
                return func(combine(funcs ...) (parameters ...));

                //auto result = t(concat(ts...) (parameters...));
                //return result;
            };
        }
        else
        {
            return func;
        }
    }

    auto timesTwo = [](auto x) {
        return 2 * x;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = combine(timesTwo, timesTwo, timesTwo, timesTwo)(2);  // 2*2*2*2*2
        std::cout << "twoPowerFive: " << twoPowerFive << std::endl;
    }
}

namespace VariadicGenericFolding_15 {

    auto combine(auto func)
    {
        return func;
    }

    auto combine(auto func, auto ... funcs)
    {
        return [&] (auto ... parameters) {
            return func(combine(funcs ...) (parameters ...));
        };
    }

    auto timesTwo = [](auto x) {
        return 2 * x;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = combine(timesTwo, timesTwo, timesTwo)(2);  // 2*2*2*2
        std::cout << "twoPowerFive: " << twoPowerFive << std::endl;
    }
}

namespace VariadicGenericFolding_16 {

    auto combine(auto func) {
        return func;
    }

    auto combine(auto func1, auto func2)
    {
        return [&](auto ... parameters) {
            auto result = func1(func2(parameters...));
            return result;
        };
    }

    auto combine(auto func1, auto func2, auto func3)
    {
        return [&](auto ... parameters) {
            auto result = func1(func2(func3(parameters ...)));
            return result;
        };
    }

    auto timesTwo = [](auto x) {
        return 2 * x;
    };

    void test_variadic_generic_folding_01()
    {
        auto twoPowerFive = combine(timesTwo, timesTwo, timesTwo)(2);  // 2*2*2*2
        std::cout << "twoPowerFive: " << twoPowerFive << std::endl;
    }
}


// ==============================================




// ==============================================

void test_variadic_generic_folding()
{
    // VariadicGenericFolding_01::test_variadic_generic_folding_01();
    // VariadicGenericFolding_01::test_variadic_generic_folding_02();

    // VariadicGenericFolding_02::test_variadic_generic_folding_01();
    //VariadicGenericFolding_02::test_variadic_generic_folding_02();
    //VariadicGenericFolding_02::test_variadic_generic_folding_03();

    // VariadicGenericFolding_02::test_variadic_generic_folding_04();
    // VariadicGenericFolding_02::test_variadic_generic_folding_05();

    // VariadicGenericFolding_03::test_variadic_generic_folding_01();

    // VariadicGenericFolding_04::test_variadic_generic_folding_01();

    // VariadicGenericFolding_05::test_variadic_generic_folding_01();

    //VariadicGenericFolding_10::test_variadic_generic_folding_01();
    //VariadicGenericFolding_10::test_variadic_generic_folding_02();
    // VariadicGenericFolding_10::test_variadic_generic_folding_03();

    //VariadicGenericFolding_11::test_variadic_generic_folding_01();
    //VariadicGenericFolding_12::test_variadic_generic_folding_01();

    //VariadicGenericFolding_13::test_variadic_generic_folding_01();
    VariadicGenericFolding_14::test_variadic_generic_folding_01();
    VariadicGenericFolding_15::test_variadic_generic_folding_01();
    VariadicGenericFolding_16::test_variadic_generic_folding_01();
}



// =====================================================================================
// End-of-File
// =====================================================================================
