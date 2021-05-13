// =====================================================================================
// Literals.cpp
// =====================================================================================

#include <iostream>
#include <cassert>
#include <iomanip>
#include <string>
#include <array>
#include <limits>

#include "Literals.h"

namespace Literals_00
{
    constexpr size_t getValue()
    {
        return 123;
    }

    constexpr int factorial(int i)
    {
        return (i > 1) ? i * factorial(i - 1) : 1;
    }

    constexpr int safe_factorial(int i)
    {
        return (i < 0) ?             // error condition
            throw std::exception() : // error reporting
            factorial(i);            // real computation
    }

    void test_0a()
    {
        constexpr int value = safe_factorial(5);
    }

    void test_0b()
    {
        constexpr size_t n = getValue();
        std::cout << n << std::endl;
    }
}


namespace Literals_01
{
    /*
    * literal operator for binary literals - runtime version
    */

    template <typename T>
    constexpr size_t numberOfBits()
    {
        return std::numeric_limits<T>::digits;
    }

    // literal operator - "raw" version
    uint32_t operator"" _b(const char* str, size_t)
    {
        if (strlen(str) > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }

        uint32_t literal{};
        for (size_t i{}; str[i] != '\0'; ++i) {

            char digit{ str[i] };
            if (digit != '0' and digit != '1') {
                throw std::runtime_error("wrong digit in binary literal!");
            }
            literal = 2 * literal + (digit - '0');
        }
        return literal;
    }

    // literal operator - "cooked" version
    uint32_t operator"" _b(unsigned long long int value)
    {
        uint32_t literal{};
        size_t count{};
        while (value != 0) {
            int digit{ value % 10 };
            if (digit != 0 and digit != 1) {
                throw std::runtime_error("wrong digit in binary literal!");
            }
            literal = 2 * literal + digit;
            value /= 10;
            ++count;
        }

        if (count > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }

        return literal;
    }

    void test_01a() try // note: function-try-block feature
    {
        size_t i{ 101_b };
        std::cout << i << std::endl;

        size_t j{ 1111111_b };
        std::cout << j << std::endl;

        size_t k{ "1010101"_b };
        std::cout << k << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    void test_01b()
    {
        size_t i{ 121_b };
        std::cout << i << std::endl;

        size_t k{ "1234567"_b };
        std::cout << k << std::endl;
    }

    void test_01c()
    {
        //constexpr size_t i = 11011_b;             // Error - doesn't compile
        //static_assert(101_b == 5, "!");           // Error - doesn't compile
        //int classic_array[11011_b];               // Error - doesn't compile
        //std::array<int, 11011_b> modern_array{};  // Error - doesn't compile
    }
}

namespace Literals_02
{
    /*
    * literal operator for binary literals - compile time version
    */

    template <typename T>
    constexpr size_t numberOfBits()
    {
        return std::numeric_limits<T>::digits;
    }

    constexpr size_t length(const char* str)
    {
        int len{};
        while (*str++ != '\0') {
            ++len;
        }
        return len;
    }

    // literal operator - "raw" version
    constexpr uint32_t operator"" _b(const char* str, size_t)
    {
        if (length(str) > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }

        uint32_t literal{};
        for (size_t i{}; str[i] != '\0'; ++i) {

            char digit{ str[i] };
            if (digit != '0' and digit != '1') {
                throw std::runtime_error("wrong digit in binary literal!");
            }
            literal = 2 * literal + (digit - '0');
        }
        return literal;
    }

    // literal operator - "cooked" version
    constexpr uint32_t operator"" _b(unsigned long long int value)
    {
        uint32_t literal{};
        size_t count{};
        while (value != 0) {
            int digit{ value % 10 };
            if (digit != 0 and digit != 1) {
                throw std::runtime_error("wrong digit in binary literal!");
            }
            literal = 2 * literal + digit;
            value /= 10;
            ++count;
        }

        if (count > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }

        return literal;
    }

    void test_02a() try // note: function-try-block feature
    {
        constexpr size_t i{ 101_b };
        std::cout << i << std::endl;

        constexpr size_t j{ 1111111_b };
        std::cout << j << std::endl;

        constexpr size_t k{ "1010101"_b };
        std::cout << k << std::endl;

        constexpr size_t n{ 11'111'11_b };
        std::cout << n << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    void test_02b()
    {
        //constexpr size_t i{ 121_b };
        //constexpr size_t j{ "1234567"_b };
    }

    void test_02c()
    {
        constexpr size_t i = 11011_b;             // compiles
        static_assert(101_b == 5, "!");           // compiles
        int classic_array[11011_b] = {};          // compiles
        std::array<int, 11011_b> modern_array{};  // compiles
    }
}

namespace Literals_03
{
    /*
    * literal operator for binary literals - compile time version with variadic templates
    */

    template <typename T>
    constexpr size_t numberOfBits()
    {
        return std::numeric_limits<T>::digits;
    }

    constexpr bool isBinary(char ch)
    {
        return ch == '0' or ch == '1';
    }

    // end of recursion
    template <size_t VALUE>                             
    constexpr size_t evalBinaryLiteral()
    {
        return VALUE;
    }

    // recursive function template definition
    template <size_t VALUE, char DIGIT, char... REST>
    constexpr size_t evalBinaryLiteral()
    {
        if (! isBinary(DIGIT)) {
            throw std::runtime_error("wrong digit in binary literal!");
        }
        return evalBinaryLiteral<(2 * VALUE + DIGIT - '0'), REST...>();
    }

    template <char... STR>
    constexpr size_t operator"" _b()
    {
        if (sizeof...(STR) > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }
        return evalBinaryLiteral<0, STR...>();
    }

    void test_03a()
    {
        constexpr size_t n = evalBinaryLiteral<0, '1', '1', '0', '1', '1'>();
        std::cout << n << std::endl;
    }

    void test_03b() try // note: function-try-block feature
    {
        constexpr size_t i{ 101_b };
        std::cout << i << std::endl;

        constexpr size_t j{ 1111111_b };
        std::cout << j << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    void test_03c()
    {
        //constexpr size_t i{ 121_b };
        //constexpr size_t j{ "1234567"_b };
    }

    void test_03d()
    {
        static_assert(10001000100010001000100010001000_b == 0x88888888, "!!");
        constexpr size_t n{ 10001000100010001000100010001000_b };
        std::cout << n << std::endl;
    }
}

namespace Literals_04
{
    /*
    * literal operator for RGB literals - compile time version
    */

    class Color {
        friend std::ostream& operator<< (std::ostream&, const Color&);

    private:
        uint8_t m_r;
        uint8_t m_g;
        uint8_t m_b;

    public:
        constexpr Color() : m_r{}, m_g{}, m_b{} {}

        constexpr Color(uint8_t r, uint8_t g, uint8_t b)
            : m_r{ r }, m_g{ g }, m_b{ b } {}
    };

    std::ostream& operator<< (std::ostream& os, const Color& col) {

        os << std::uppercase
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_b;

        return os;
    }

    // literal operator ("cooked" version)
    constexpr Color operator"" _rgb(unsigned long long int value) {

        if (value > 0xFFFFFF) {
            throw std::runtime_error("literal too large");
        }

        uint8_t r{ (uint8_t)((value & 0xFF0000) >> 16) };
        uint8_t g{ (uint8_t)((value & 0x00FF00) >>  8) };
        uint8_t b{ (uint8_t)((value & 0x0000FF) >>  0) };

        return Color{ r, g, b };
    }

    constexpr size_t length(const char* str)
    {
        int len{};
        while (*str++ != '\0') {
            ++len;
        }
        return len;
    }

    constexpr uint8_t hex2int(char ch)
    {
        // transform hex character to 4-bit equivalent number
        uint8_t byte = ch;
        if (byte >= '0' and byte <= '9') {
            // byte = byte - '0';
            byte -= '0';
        }
        else if (byte >= 'a' and byte <= 'f') {
            // byte = byte - 'a' + 10;
            byte -= ('a' - 10);
        }
        else if (byte >= 'A' and byte <= 'F') {
            //byte = byte - 'A' + 10;
            byte -= ('A' - 10);
        }
        return byte;
    }

    constexpr size_t hexstoi(const char* str)
    {
        int value{};
        while (*str != '\0') {
            // get current character, then increment
            uint8_t byte = hex2int(*str);
            ++str;

            // shift 4 to make space for new digit, and add the 4 bits of the new digit 
            value = (value << 4) | (byte & 0xF);
        }
        return value;
    }

    // literal operator ("raw" version)
    constexpr Color operator"" _rgb(const char* literal, size_t) {

        // tiny implementation - just parsing hexadecimal format
        size_t len{ length(literal) };
        if (len == 2 /* 0x */ + 6 /* FF FF FF */) {

            char ar[3] = {};
            char ag[3] = {};
            char ab[3] = {};

            ar[0] = literal[2];
            ar[1] = literal[3];
            ag[0] = literal[4];
            ag[1] = literal[5];
            ab[0] = literal[6];
            ab[1] = literal[7];

            uint8_t r = static_cast<uint8_t>(hexstoi(ar));
            uint8_t g = static_cast<uint8_t>(hexstoi(ag));
            uint8_t b = static_cast<uint8_t>(hexstoi(ab));

            return { r, g, b };
        }

        return {};
    }

    void test_04a()
    {
        constexpr Color red = 0xFF0000_rgb;
        std::cout << red << std::endl;
        constexpr Color magenta = 0xFF00FF_rgb;
        std::cout << magenta << std::endl;
        constexpr Color yellow = 0xFFFF00_rgb;
        std::cout << yellow << std::endl;
        constexpr Color unknown = 12345_rgb;
        std::cout << unknown << std::endl;
        constexpr Color white = 16777215_rgb;
        std::cout << white << std::endl;
        constexpr Color anotherWhite = "0xFFFFFF"_rgb;
        std::cout << anotherWhite << std::endl;
        constexpr Color black = "0x000000"_rgb;
        std::cout << black << std::endl;
    }
}

namespace Literals_05
{
    /*
    * literal operator for binary literals - compile time version
    */

    template <typename T>
    constexpr size_t numberOfBits()
    {
        return std::numeric_limits<T>::digits;
    }

    constexpr bool isValid(char ch)
    {
        return ch == '0' or ch == '1' or ch == '\'';
    }

    constexpr size_t length(const char* str)
    {
        int len{};
        while (*str++ != '\0') {
            if (*str == '\'') 
                continue;
            ++len;
        }
        return len;
    }

    // literal operator - "raw" version
    constexpr uint32_t operator"" _b(const char* str, size_t)
    {
        if (length(str) > numberOfBits<uint32_t>()) {
            throw std::runtime_error("binary literal too long");
        }

        uint32_t literal{};
        for (size_t i{}; str[i] != '\0'; ++i) {

            char digit{ str[i] };
            if (! isValid(digit)) {
                throw std::runtime_error("wrong digit in binary literal!");
            }

            if (digit != '\'') {
                literal = 2 * literal + (digit - '0');
            }
        }
        return literal;
    }

    void test_05a() try // note: function-try-block feature
    {
        constexpr size_t j{ "11'111'11"_b };
        std::cout << j << std::endl;   // 127

        constexpr size_t k{ "1000'1000'1000'1000'1000'1000'1000'1000"_b };
        std::cout << k << std::endl;   // 2'290'649'224
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
