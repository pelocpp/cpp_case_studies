// =====================================================================================
// CowStringImpl.cpp // Simple implementation of a COW string class
// =====================================================================================

#include "CowString.h"

#include <print>

#include <cstring>     // std::strlen
#include <stdexcept>   // std::out_of_range

namespace COWString
{
    // =================================================================================
    // Controlblock

    CowString::Controlblock* CowString::Controlblock::create(const char* src, std::size_t len)
    {
        void* mem{ ::operator new(sizeof(Controlblock) + len + 1) };
        Controlblock* sd{ new (mem) Controlblock{ 1 } };
        char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
        std::memcpy(cp, src, len);
        cp[len] = '\0';
        return sd;
    }

    CowString::Controlblock* CowString::Controlblock::createEmpty()
    {
        void* mem{ ::operator new(sizeof(Controlblock) + 1) };
        Controlblock* sd{ new (mem) Controlblock{ 1 } };
        char* cp{ reinterpret_cast<char*> (mem) + sizeof(Controlblock) };
        cp[0] = '\0';
        return sd;
    }

    // =================================================================================
    // c'tor(s) / d'tor

    CowString::CowString()
    {
        m_ptr = Controlblock::createEmpty();
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
        m_len = 0;
    }

    CowString::CowString(const char* s)
    {
        m_len = std::strlen(s);
        m_ptr = Controlblock::create(s, m_len);
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
    }

    CowString::CowString(const char* s, std::size_t length)
    {
        m_ptr = Controlblock::create(s, length);
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
        m_len = length;
    }

    CowString::CowString(std::string_view sv)
    {
        m_ptr = Controlblock::create(sv.data(), sv.size());
        m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
        m_len = sv.size();
    }

    CowString::~CowString()
    {
        if (m_ptr != nullptr) {

            m_ptr->m_refCount--;
            if (m_ptr->m_refCount == 0) {
                ::operator delete(m_ptr);
            }
        }
    }

    // =================================================================================
    // copy semantics

    CowString::CowString(const CowString& other)
        : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
    {
        m_ptr->m_refCount++;
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
            m_len = other.m_len;

            m_ptr->m_refCount++;
        }

        return *this;
    }

    // =================================================================================
    // move semantics

    CowString::CowString(CowString&& other) noexcept 
        : m_ptr{ other.m_ptr }, m_str{ other.m_str }, m_len{ other.m_len }
    {
        other.m_ptr = Controlblock::createEmpty();
        other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
        other.m_len = 0;
    }

    CowString& CowString::operator=(CowString&& other) noexcept {

        if (this != &other) {

            m_ptr->m_refCount--;
            if (m_ptr->m_refCount == 0) {
                ::operator delete(m_ptr);
            }

            m_ptr = other.m_ptr;
            m_str = other.m_str;
            m_len = other.m_len;

            other.m_ptr = Controlblock::createEmpty();
            other.m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
            other.m_len = 0;
        }
    
        return *this;
    }

    // =================================================================================
    // getter

    std::size_t CowString::size() const { return m_len; }

    const char* CowString::c_str() const { return m_str; }

    bool CowString::empty() const { return m_len == 0; }

    // =================================================================================
    // read-only access / write access (triggers COW)

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
        if (idx >= m_len)
            throw std::out_of_range("index out of range!");

        return m_str[idx];
    }

    // possible write access - triggers COW
    char& CowString::at(std::size_t idx) {
        if (idx >= m_len)
            throw std::out_of_range("index out of range!");

        detach();
        return m_str[idx];
    }

    // =================================================================================
    // comparison operators

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

    // =================================================================================
    // type-conversion operator

    CowString::operator std::string_view() const
    {
        return { m_str , m_len };
    }

    // =================================================================================
    // ensure we have a private (unshared) copy before writing
    // (switching from state 'shared' into state 'owning')

    void CowString::detach()
    {
        if (m_ptr->m_refCount.load() > 1) {

            Controlblock* old{ m_ptr };
            
            std::size_t len{ std::strlen(m_str) };
            m_ptr = Controlblock::create(m_str, m_len);
            m_str = reinterpret_cast<char*> (m_ptr) + sizeof(Controlblock);
            m_len = len;

            old->m_refCount--;
        }
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
