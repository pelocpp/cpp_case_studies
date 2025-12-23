// =====================================================================================
// CowStringImpl.cpp // Simple implementation of a COW string class
// =====================================================================================

#include "CowString.h"

#include <cstring>     // std::strlen
#include <print>       // std::print
#include <stdexcept>   // std::out_of_range

namespace CowStringSimple
{
    // Controlblock
    CowString::Controlblock* CowString::Controlblock::create(const char* src)
    {
        std::size_t len{ std::strlen(src) };
        void* mem{ ::operator new(sizeof(Controlblock) + len + 1) };
        Controlblock* sd{ new (mem) Controlblock{ 1, len } };
        char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
        std::memcpy(cp, src, len + 1);
        return sd;
    }

    CowString::Controlblock* CowString::Controlblock::create(const char* src, std::size_t len)
    {
        void* mem{ ::operator new(sizeof(Controlblock) + len + 1) };
        Controlblock* sd{ new (mem) Controlblock{ 1, len } };
        char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
        std::memcpy(cp, src, len);
        cp[len] = '\0';
        return sd;
    }

    CowString::Controlblock* CowString::Controlblock::createEmpty()
    {
        void* mem{ ::operator new(sizeof(Controlblock) + 1) };
        Controlblock* sd{ new (mem) Controlblock{ 1, 0 } };
        char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
        cp[0] = '\0';
        return sd;
    }

    // c'tor(s) / d'tor
    CowString::CowString()
    {
        m_ptr = Controlblock::createEmpty();
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
    }

    CowString::CowString(const char* s)
    {
        m_ptr = Controlblock::create(s);
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
    }

    // Neu, noch nicht getestet
    CowString::CowString(const char* s, std::size_t length)
    {
        m_ptr = Controlblock::create(s, length);
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
    }


    // not tested
    // Geht das besser... die Länge habe ich schon
    // ein Überladung von create .... mit Länge ...
    CowString::CowString(std::string_view sv)
    {
        m_ptr = Controlblock::create(sv.data());
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
    }

    CowString::CowString(const CowString& other)
    {
        m_ptr = other.m_ptr;
        m_str = other.m_str;
        m_ptr->m_refCount++;
    }

    CowString::~CowString()
    {
        m_ptr->m_refCount--;
        if (m_ptr->m_refCount == 0) {
            ::operator delete(m_ptr);
        }
    }

    // move semantics
    CowString::CowString(CowString&& other) noexcept 
        : m_ptr{ other.m_ptr }, m_str{ other.m_str } 
    {
        other.m_ptr = nullptr;
        other.m_str = nullptr;    
    }

    CowString& CowString::operator=(CowString&& other) noexcept {

        if (this != &other) {

            m_ptr->m_refCount--;
            if (m_ptr->m_refCount == 0) {
                ::operator delete(m_ptr);
            }

            m_ptr = other.m_ptr;
            m_str = other.m_str;
            other.m_ptr = nullptr;
            other.m_str = nullptr;
        }
    
        return *this;
    }

    // getter
    std::size_t CowString::size() const { return m_ptr->m_length; }

    const char* CowString::c_str() const { return m_str; }

    // read-only access
    char CowString::operator[](std::size_t idx) const {
        return m_str[idx];
    }

    // possible write access - triggers COW
    char& CowString::operator[](std::size_t idx) {
        detach();
        return m_str[idx];
    }

    // read-only access
    char CowString::at(std::size_t idx) const {
        if (idx >= m_ptr->m_length)
            throw std::out_of_range("index out of range!");

        return m_str[idx];
    }

    // possible write access - triggers COW
    char& CowString::at(std::size_t idx) {
        if (idx >= m_ptr->m_length)
            throw std::out_of_range("index out of range!");

        detach();
        return m_str[idx];
    }

    // assignment operator
    CowString& CowString::operator=(const CowString& other)
    {
        if (this != &other) {

            m_ptr->m_refCount--;
            if (m_ptr->m_refCount == 0) {
                ::operator delete(m_ptr);
            }

            m_ptr = other.m_ptr;
            m_str = other.m_str;
            m_ptr->m_refCount++;
        }

        return *this;
    }

    // comparison operators - global methods
    bool operator==(const CowString& a, const CowString& b) {

        if (a.m_ptr == b.m_ptr) {
            return true;
        }

        if (a.size() != b.size()) {
            return false;
        }

        return std::memcmp(a.c_str(), b.c_str(), a.size()) == 0;
    }

    bool operator!=(const CowString& a, const CowString& b) {
        return !(a == b);
    }

    bool operator<(const CowString& a, const CowString& b) {
        return std::strcmp(a.c_str(), b.c_str()) < 0;
    }

    // type-conversion operator
    CowString::operator std::string_view() const
    {
        return { m_str , m_ptr->m_length };
    }

    // ensure we have a private (unshared) copy before writing
    void CowString::detach()
    {
        if (m_ptr->m_refCount.load() > 1) {

            Controlblock* old{ m_ptr };
            m_ptr = Controlblock::create(m_str);
            m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
            old->m_refCount--;
        }
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
