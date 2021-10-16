// =====================================================================================
// ExpressionTemplates.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <chrono>

namespace ExpressionTemplatesStrings
{
    constexpr size_t IterationCount{ 50000 };

    // primary template
    template <typename... Strings>
    class StringHelper;

    template <typename String, typename... Strings>
    class StringHelper<String, Strings...> {
    private:
        const String& m_data;  // storing reference of first string
        StringHelper<Strings...> m_tail;  // structure that contains other strings

    public:
        StringHelper(const String& data, StringHelper<Strings...> tail)
            : m_data{ data }, m_tail{ tail }
        {}

        StringHelper(const String& data)
            : m_data{ data }, m_tail{ StringHelper<>() }
        {}

        // calculating size of all strings being concatenated
        size_t size() const
        {
            size_t length{ m_data.size() + m_tail.size() };
            return length;
        }

        // The expression structure stores strings in reverse order:
        // the data member variable contains the string that comes last,
        // so we start at the end of the buffer
        void save(const std::string::iterator& end) const
        {
            const std::string::iterator begin{ end - m_data.size() };
            std::copy(std::begin(m_data), std::end(m_data), begin);
            m_tail.save(begin);
        }

        // type conversion operator:
        // converts the expression definition into a real string
        // (allocate memory and copy strings into it)
        operator std::string() const
        {
            // compute total length of concatenated string
            size_t length{ size() };

            // construct result string of size 'length' with 'length' copies of '\0'
            std::string result(length, '\0');  // <--- preallocate result string

            // passing end of this buffer (end iterator),
            // result string is constructed in reverse order
            save(std::end(result));
            return result;
        }

        // create a new instance of the expression structure
        // with one string added to it
        StringHelper<std::string, String, Strings...>
            operator+(const std::string& next) const
        {
            return StringHelper<std::string, String, Strings...>(
                next,
                *this
                );
        }
    };

    template <>
    class StringHelper<> {
    public:
        StringHelper() = default;

        size_t size() const { return 0; }

        void save(const std::string::iterator&) const {}

        StringHelper<std::string> operator+(const std::string& next) const
        {
            return StringHelper<std::string>(next, *this);
        }
    };

    template<typename ... ARGS>
    std::string concatClassic(ARGS&& ... args)
    {
        std::string result{ (... + std::forward<ARGS>(args)) };
        return result;
    }

    template<typename ... ARGS>
    std::string concat(ARGS&& ... args)
    {
        std::string result{ (StringHelper<>{} + ... + std::forward<ARGS>(args)) };
        return result;
    }
}

// =====================================================================================

namespace ExpressionTemplatesStrings_GCC
{
    constexpr size_t IterationCount{ 50000 };

    // primary template
    template <typename... Strings>
    class StringHelper;

    template <>
    class StringHelper<> {
    public:
        StringHelper() = default;
        size_t size() const { return 0; }
        void save(const std::string::iterator&) const {}
        StringHelper<std::string> operator+(const std::string& next) const;
    };

    template <typename String, typename... Strings>
    class StringHelper<String, Strings...> {
    private:
        const String& m_data;
        StringHelper<Strings...> m_tail;

    public:
        StringHelper(const String& data, StringHelper<Strings...> tail)
            : m_data{ data }, m_tail{ tail }
        {}

        StringHelper(const String& data)
            : m_data{ data }, m_tail{ StringHelper<>() }
        {}

        // calculating size of all strings being concatenated
        size_t size() const
        {
            size_t length{ m_data.size() + m_tail.size() };
            return length;
        }

        void save(const std::string::iterator& end) const
        {
            const std::string::iterator begin{ end - m_data.size() };
            std::copy(std::begin(m_data), std::end(m_data), begin);
            m_tail.save(begin);
        }

        operator std::string() const
        {
            size_t length{ size() };
            std::string result(length, '\0');
            save(std::end(result));
            return result;
        }

        StringHelper<std::string, String, Strings...>
            operator+(const std::string& next) const
        {
            return StringHelper<std::string, String, Strings...>(
                next,
                *this
                );
        }
    };

    StringHelper<std::string> StringHelper<>::operator+(const std::string& next) const
    {
        return StringHelper<std::string>(
            next,
            *this
            );
    }

    template<typename ... ARGS>
    std::string concatClassic(ARGS&& ... args)
    {
        std::string result{ (... + std::forward<ARGS>(args)) };
        return result;
    }

    template<typename ... ARGS>
    std::string concat(ARGS&& ... args)
    {
        std::string result{ (StringHelper<>{} + ... + std::forward<ARGS>(args)) };
        return result;
    }
}

// =====================================================================================

std::string s1{
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"
};
std::string s2{
    "Ut enim ad minim veniam, quis nostrud exercitation "
    "ullamco laboris nisi ut aliquip ex ea commodo consequat"
};
std::string s3{
    "Duis aute irure dolor in reprehenderit in voluptate "
    "velit esse cillum dolore eu fugiat nulla pariatur"
};
std::string s4{
    "Excepteur sint occaecat cupidatat non proident, "
    "sunt in culpa qui officia deserunt mollit anim id est laborum"
};

// =====================================================================================

void Test_01()
{
    using namespace ExpressionTemplatesStrings;
    using namespace std::string_literals;
    std::string result{ StringHelper<>{} + "123"s + "ABC"s + "456"s + "XYZ"s + "789"s };
    std::cout << result << std::endl;
}

void Test_01_GCC()
{
    using namespace ExpressionTemplatesStrings_GCC;
    using namespace std::string_literals;
    std::string result{ StringHelper<>{} + "123"s + "ABC"s + "456"s + "XYZ"s + "789"s };
    std::cout << result << std::endl;
}

void Test_02()
{
    using namespace ExpressionTemplatesStrings;

    std::string s1{ "aaa" };
    std::string s2{ "BBBBBB" };
    std::string s3{ "CCCCCCCCC" };

    // Cannot overload operator+ on std::string,
    // so I have to start the concatenation with a 
    // StringHelper<> object as first operand.
    // All following + operators now act on the overloaded operator+
    // of class StringHelper 
    StringHelper<> begin;
    const std::string fullname{ begin + s1 + s2 + s3 };
    std::cout << fullname << std::endl;
}

void Test_03_Possible_Error()
{
    using namespace ExpressionTemplatesStrings;

    std::string s1{ "AAA" };
    std::string s2{ "BBB" };
    std::string s3{ "CCC" };

    StringHelper<std::string, std::string, std::string> expression{ StringHelper<>{} + s1 + s2 + s3 };

    s2 = "111";
    std::cout << (std::string)expression << std::endl;

    s3 = "222";
    std::string s = expression;
    std::cout << s << std::endl;
}

void Test_04()
{
    using namespace ExpressionTemplatesStrings;

    std::string s1{ "aaa" };
    std::string s2{ "BBBBBB" };
    std::string s3{ "CCCCCCCCC" }; 

    StringHelper<std::string> expr1{ s1 };
    StringHelper<std::string, std::string> expr2{ s2, expr1 };
    StringHelper<std::string, std::string, std::string> expr3{ s3, expr2 };

    std::string fullname{ expr3 };
    std::cout << fullname << std::endl;
}

void Test_05()
{
    using namespace ExpressionTemplatesStrings;
    using namespace std::string_literals;

    const std::string s1{ "111111111" };
    const std::string s2{ "222222" };
    const std::string s3{ "333" };
    std::string result{};

    result = concatClassic(s1, s2, s3);
    std::cout << result << std::endl;

    result = concat(s1, s2, s3);
    std::cout << result << std::endl;

    result = concatClassic("aaaaa"s, "bbbb"s, "ccc"s, "dd"s, "e"s);
    std::cout << result << std::endl;

    result = concat("aaaaa"s, "bbbb"s, "ccc"s, "dd"s, "e"s);
    std::cout << result << std::endl;
}

void Test_06_ClassicBenchmark()
{
    using namespace ExpressionTemplatesStrings;

    const auto start{ std::chrono::high_resolution_clock::now() };
    for (size_t i{}; i != IterationCount; ++i)
    {
        std::string result{ s1 + ". " + s2 + ". " + s3 + ". " + s4 + "." };
        // std::string result{ concatClassic(s1, ". ", s2, ". ", s3, ". ", s4, ".") };
    }
    const auto end{ std::chrono::high_resolution_clock::now() };

    const auto diff{ std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() };

    std::cout << std::fixed << diff << " msecs." << std::endl;
}

void Test_06_ClassicBenchmark_LoopUnrollingBenchmark()
{
    using namespace ExpressionTemplatesStrings;

    const auto start{ std::chrono::high_resolution_clock::now() };
    for (size_t i{}; i != IterationCount; ++i)
    {
        std::string result{ StringHelper<>{} + s1 + ". " + s2 + ". " + s3 + ". " + s4 + "." };
        // std::string result{ concat(s1, ". ", s2, ". ", s3, ". ", s4, ".") };
    }
    const auto end{ std::chrono::high_resolution_clock::now() };

    const auto diff{ std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() };

    std::cout << std::fixed << diff << " msecs." << std::endl;
}

void Test_06_Benchmark()
{
    Test_06_ClassicBenchmark();
    Test_06_ClassicBenchmark_LoopUnrollingBenchmark();
}

// =====================================================================================
// End-of-File
// =====================================================================================
