// =====================================================================================
// CowString.h // Simple implementation of a COW string class
// =====================================================================================

#pragma once

#include <atomic>       // std::atomic
#include <cstddef>      // std::size_t
#include <string_view>  // std::string_view

namespace CowStringSimple
{
    class CowString
    {
    private:
        struct Controlblock
        {
            std::atomic<std::size_t> m_refCount;
            std::size_t              m_length;

            static Controlblock*     create      (const char* src);
            static Controlblock*     createEmpty ();
        };

        Controlblock* m_ptr;
        char*         m_str;

        // ensure we have a private (unshared) copy before writing
        void detach  ();

    public:
        // c'tor(s), d'tor
        CowString    ();
        CowString    (const char* s);
        CowString    (const CowString& other);
        ~CowString   ();

        // FEHLT: C'tor aus einem std::string_view heraus ...

        // move semantics
        CowString(CowString&& other) noexcept;
        CowString& operator= (CowString&& other) noexcept;

        // assignment operator
        CowString& operator= (const CowString& other);

        // getter
        std::size_t size() const;
        const char* c_str() const;

        // type-conversion operator
        operator std::string_view();

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

// =====================================================================================
// End-of-File
// =====================================================================================
