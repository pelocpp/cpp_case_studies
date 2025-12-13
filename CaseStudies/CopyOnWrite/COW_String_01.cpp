// =====================================================================================
// COW_String_01.cpp // Simple implementation of a COW string class
// =====================================================================================

#include <atomic>      // std::atomic
#include <cstddef>     // std::std::size_t, offsetof
#include <cstring>     // std::strlen
#include <print>       // std::print

namespace CowString01
{
    class CowString
    {
    private:
        struct StringData
        {
            std::atomic<std::size_t> m_refCount;
            std::size_t              m_length;

            static StringData* create(const char* src)
            {
                std::size_t len{ std::strlen(src) };
                void* mem{ ::operator new(sizeof(StringData) + len + 1) };
                StringData* sd{ new (mem) StringData{ 1, len } };
                char* cp{ reinterpret_cast<char*> (mem) + sizeof(StringData) };
                std::memcpy(cp, src, len + 1);
                return sd;
            }

            static StringData* createEmpty()
            {
                void* mem{ ::operator new(sizeof(StringData) + 1) };
                StringData* sd{ new (mem) StringData{ 1, 0 } };
                char* cp{ reinterpret_cast<char*> (mem) + sizeof(StringData) };
                cp[0] = '\0';
                //std::memcpy(cp, src, len + 1);
                return sd;
            }
        };

        StringData* m_ptr;
        char*       m_str;

        // ensure we have a private (unshared) copy before writing
        void detach()
        {
            if (m_ptr->m_refCount.load() > 1) {

                StringData* old{ m_ptr };
                char* cp{ reinterpret_cast<char*> (old) + sizeof(StringData) };
                m_ptr = StringData::create(cp);
                old->m_refCount--;
            }
        }

    public:
        CowString(const char* s = "")  // TODO; Für "" durchlaufen 
        {
            m_ptr = StringData::create(s);
            m_str = reinterpret_cast<char*> (m_ptr) + sizeof(StringData);
        }

        CowString(const CowString& other)
        {
            m_ptr = other.m_ptr;
            m_str = other.m_str;
            m_ptr->m_refCount++;
        }

        CowString& operator=(const CowString& other)
        {
            if (this != &other) {

                m_ptr->m_refCount--;
                if (m_ptr->m_refCount == 0) {
                    ::operator delete(m_ptr);
                }

                // Ähmmm .. fehlt da ein else ??????????????????????????????

                m_ptr = other.m_ptr;
                m_str = other.m_str;
                m_ptr->m_refCount++;
            }

            return *this;
        }

        ~CowString()
        {
            m_ptr->m_refCount--;
            if (m_ptr->m_refCount == 0) {
                ::operator delete(m_ptr);
            }
        }

        std::size_t size() const { return m_ptr->m_length; }

        const char* c_str() const
        {
            // return reinterpret_cast<char*> (m_ptr) + sizeof(StringData);
            return m_str;
        }

        // read-only access
        char operator[](std::size_t idx) const {



           // char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return m_str[idx];
        }

        // write access - triggers COW
        char& operator[](std::size_t idx) {

            detach();

            //char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            //return cp[idx];

            return m_str[idx];
        }
    };

    static void test_cow_string_01_A()
    {
        CowString a;
    }

    static void test_cow_string_01_B()
    {
        const CowString a("1234567890");
        char cr = a[3];
    }

    static void test_cow_string_01_C()
    {
        CowString a("1234567890");
        CowString b = a;
        CowString c = a;
        c[0] = '!';
    }

    static void test_cow_string_01_D()
    {
        CowString a("1234567890");
        CowString b = a;
        CowString c = a;

        CowString x("ABC");
        CowString y = x;

        a = x;
    }

    static void test_cow_string_01_E()
    {
        CowString a("Hello");
        CowString b = a;      // shares buffer
        CowString c = b;      // shares buffer

        std::println("Before modification:");
        std::println("a: {}", a.c_str());
        std::println("b: {}", b.c_str());
        std::println("c: {}", c.c_str());

        b[0] = 'J'; // triggers copy-on-write only for 'b'

        std::println("After modifying b:");
        std::println("a: {}", a.c_str());  // unchanged
        std::println("b: {}", b.c_str());  // modified
        std::println("c: {}", c.c_str());  // unchanged
    }
}

void test_cow_string_01()
{
    using namespace CowString01;

    std::println("Test 01 Simple COW String");

    test_cow_string_01_A();
    test_cow_string_01_B();
    test_cow_string_01_C();
    test_cow_string_01_D();
    test_cow_string_01_E();
}

// =====================================================================================
// End-of-File
// =====================================================================================


