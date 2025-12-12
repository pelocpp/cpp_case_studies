// COW_String_01

#include <atomic>      // std::atomic
#include <cstddef>     // std::std::size_t, offsetof
#include <cstring>
#include <iostream>

//#include <string>


namespace CowString01
{

    // TODO: 
    // CHecken, ob die ganzen Destruktoren aufgerufen werden ?!?!?!

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
        }

        CowString(const CowString& other)
        {
            m_ptr = other.m_ptr;
            m_ptr->m_refCount++;
        }

        CowString& operator=(const CowString& other)
        {
            if (this != &other) {

                m_ptr->m_refCount--;
                if (m_ptr->m_refCount == 0) {
                    ::operator delete(m_ptr);
                }

                //if (--m_ptr->m_refCount == 0) {
                //    ::operator delete(m_ptr);
                //}

                m_ptr = other.m_ptr;
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
            return reinterpret_cast<char*> (m_ptr) + sizeof(StringData);
        }

        // read-only access
        char operator[](std::size_t idx) const {

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[idx];
        }

        // write access - triggers COW
        char& operator[](std::size_t idx) {

            detach();

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[idx];
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
        std::cout << "TEST 01" << std::endl;

        CowString a("Hello");
        CowString b = a;      // shares buffer
        CowString c = b;      // shares buffer

        std::cout << "Before modification:\n";
        std::cout << "a: " << a.c_str() << "\n";
        std::cout << "b: " << b.c_str() << "\n";
        std::cout << "c: " << c.c_str() << "\n";

        b[0] = 'J'; // triggers copy-on-write only for 'b'

        std::cout << "\nAfter modifying b:\n";
        std::cout << "a: " << a.c_str() << "\n"; // unchanged
        std::cout << "b: " << b.c_str() << "\n"; // modified
        std::cout << "c: " << c.c_str() << "\n"; // unchanged
    }
    //
    //
    //void test_cow_string_AA()
    //{
    //    std::string s = s;
    //    auto length = s.length();
    //}

}

void test_cow_string_01()
{
    using namespace CowString01;


    std::cout << "TEST 01" << std::endl;

    //test_cow_string_01_A();
    //test_cow_string_01_B();
    //test_cow_string_01_C();
    test_cow_string_01_D();
   // test_cow_string_01_E();
}
