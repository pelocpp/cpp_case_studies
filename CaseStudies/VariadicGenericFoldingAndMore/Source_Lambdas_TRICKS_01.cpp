#include <iostream>
#include <concepts>
#include <string>
#include <type_traits>
#include <format>

// ==============================================

// https://www.cppstories.com/2020/08/c-lambda-week-some-tricks.html/

// https://iamsorush.com/posts/cpp-variadic-template/

// https://iamsorush.com/posts/cpp-meta-function/#introduction


// https://iamsorush.com/posts/concepts-cpp/

// ==============================================

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts) 
{
    if constexpr (sizeof...(ts) > 0)
    {
        return [&](auto ...parameters) {
            // return t(concat(ts...)(parameters...));

            auto result = t( concat(ts...) (parameters...) );

            return result;
        };
    }
    else
    {
        return t;
    }
}

// ==============================================

template <typename T>
auto concatEx(T t)
{
   return t;
}

template <typename T, typename ...Ts>
auto concatEx(T t, Ts ...ts)
{
    return [=](auto ...parameters) {
        // return t(concat(ts...)(parameters...));

        auto result = t( concatEx(ts...) (parameters...) );

        return result;
    };
}



// ==============================================

template <typename T>
auto concatExEx(T t)
{
    return t;
}

template <typename T1, typename T2>
auto concatExEx(T1 t, T2 t2)
{
    return [&](auto ... parameters) {

        auto result = t(t2(parameters...));
        return result;
    };
}

template <typename T1, typename T2, typename T3>
auto concatExEx(T1 t, T2 t2, T3 t3)
{
    return [&](auto ... parameters) {

        auto result = t(t2(t3(parameters ...)));
        return result;
    };
}

// ==============================================


auto concatExExEx(auto t)
{
    return t;
}


auto concatExExEx(auto t, auto t2)
{
    return [&](auto ... parameters) {

        auto result = t(t2(parameters...));
        return result;
    };
}

auto concatExExEx(auto t, auto t2, auto t3)
{
    return [&] (auto ... parameters) {

        auto result = t(t2(t3(parameters ...)));
        return result;
    };
}

// ==============================================

void test_recursive_lambdas_01()
{
    auto twice = [](auto i) { 
        return i * 2;
    };

    auto thrice = [](auto i) { 
        return i * 3; 
    };

    auto add = [](auto i, auto j) { 
        return i + j;
    };

   //  auto combined = concat(thrice, twice, std::plus<int>{});

    auto combined = concat(thrice, twice, add);

    std::cout << std::format("{}\n", combined(2, 3));
}

void test_recursive_lambdas_02()
{
    auto twice = [](auto i) {
        return i * 2;
    };

    auto thrice = [](auto i) {
        return i * 3;
    };

    auto add = [](auto i, auto j) {
        return i + j;
    };

    auto result = thrice(twice(add(2, 3)));

    std::cout << std::format("{}\n", result);
}

void test_recursive_lambdas_03()
{
    auto twice = [](auto i) {
        return i * 2;
    };

    auto add = [](auto i, auto j) {
        return i + j;
    };

    auto combined = concat(twice, add);

    std::cout << std::format("{}\n", combined(2, 3));
}

void test_recursive_lambdas_04()
{
    auto twice = [](auto i) {
        return i * 2;
    };

    auto thrice = [](auto i) {
        return i * 3;
    };

    auto add = [](auto i, auto j) {
        return i + j;
    };

    //  auto combined = concat(thrice, twice, std::plus<int>{});

    auto combined = concatEx(thrice, twice, add);

    std::cout << std::format("{}\n", combined(2, 3));
}


void test_recursive_lambdas_05()
{
    auto twice = [](auto i) {
        return i * 2;
    };

    auto thrice = [](auto i) {
        return i * 3;
    };

    auto add = [](auto i, auto j) {
        return i + j;
    };

    auto combined = concatExEx(thrice, twice, add);

    auto result = combined(20, 30);

    std::cout << std::format("{}\n", result);
}

void test_recursive_lambdas_06()
{
    auto twice = [](auto i) {
        return i * 2;
    };

    auto thrice = [](auto i) {
        return i * 3;
    };

    auto add = [](auto i, auto j) {
        return i + j;
    };

    auto combined = concatExExEx(thrice, twice, add);

    auto result = combined(20, 30);

    std::cout << std::format("{}\n", result);
}


void test_recursive_lambdas()
{
    //test_recursive_lambdas_01();
    //test_recursive_lambdas_02();
    //test_recursive_lambdas_03();
    //test_recursive_lambdas_04();
    test_recursive_lambdas_05();
}

