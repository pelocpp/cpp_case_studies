// =====================================================================================
// CowString.h // Simple implementation of a COW string class
// =====================================================================================

#pragma once

#include <atomic>       // std::atomic
#include <cstddef>      // std::size_t
#include <string_view>  // std::string_view
#include <format>       // std::std::formatter

namespace COWString
{
    class CowString
    {
    private:
        struct Controlblock
        {
            std::atomic<std::size_t> m_refCount;
            std::size_t              m_length;

            static Controlblock*     create      (const char* src);
            static Controlblock*     create      (const char* src, std::size_t length);
            static Controlblock*     createEmpty (); 
        };

        Controlblock* m_ptr;
        char*         m_str;

        // ensure we have a private (unshared) copy before writing
        void detach  ();

    public:
        // c'tor(s), d'tor
        CowString             ();
        explicit CowString    (const char* s);
        CowString             (const char* s, std::size_t count);
        explicit CowString    (std::string_view sv);
        ~CowString            ();

        // copy semantics
        CowString(const CowString& other);
        CowString& operator= (const CowString& other);

        // move semantics
        CowString(CowString&& other) noexcept;
        CowString& operator= (CowString&& other) noexcept;

        // getter
        std::size_t  size() const;
        const char*  c_str() const;
        bool         empty() const;

        // type-conversion operator
        operator std::string_view() const;

        // comparison operators
        friend bool operator== (const CowString& a, const CowString& b);
        friend bool operator!= (const CowString& a, const CowString& b);
        friend bool operator<  (const CowString& a, const CowString& b);

        // read- and write-access - no exception handling
        char operator[] (std::size_t idx) const;  // read-only access
        char& operator[](std::size_t idx);        // possible write access - triggers COW
    
        char at (std::size_t idx) const;          // read-only access
        char& at(std::size_t idx);                // possible write access - triggers COW
    };
}

namespace std
{
    using namespace COWString;

    // =======================================================================
    // std::hash for class CowString

    template <>
    struct hash<CowString>
    {
        // Note: std::hash<const char*> hashes the pointer value, not the characters it points to
        // Workaround: let's use std::string_view

        std::size_t operator() (const CowString& cs) const {

            std::string_view sv{ cs };
            std::size_t h{ std::hash<std::string_view>{}(sv) };
            return h;
        }
    };

    // =======================================================================
    //  std::formatter for class CowString

    template <>
    struct formatter<CowString>
    {
        // parse the format string for this type
        constexpr auto parse(std::format_parse_context & ctx) {
            return ctx.begin(); // returns position of '}'
        }

        // format by always writing its 'char*' value
        auto format(const CowString& obj, std::format_context & ctx) const {
            return std::format_to(ctx.out(), "{}", obj.c_str());
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
