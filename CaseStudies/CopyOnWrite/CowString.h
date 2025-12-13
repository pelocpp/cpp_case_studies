// =====================================================================================
// CowString.h // Simple implementation of a COW string class
// =====================================================================================

#pragma once

#include <atomic>      // std::atomic
#include <cstddef>     // std::std::size_t, offsetof

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
        void detach();

    public:
        // c'tor(s), d'tor
        CowString();
        CowString(const char* s);
        CowString(const CowString& other);
        ~CowString();

        // assignment operator
        CowString& operator=(const CowString& other);

        // getter
        std::size_t size() const;
        const char* c_str() const;

        // read- and write-access
        char operator[](std::size_t idx) const;
        char& operator[](std::size_t idx);
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
