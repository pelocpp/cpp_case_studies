// COW_String_03

#include <algorithm>
#include <atomic>
#include <cstring>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

namespace CowString03
{
    class CowStringEx 
    {
    private:
        struct StringData
        {
            std::atomic<std::size_t> m_refCount;
            std::size_t              m_size;
            std::size_t              m_capacity;
            //  char data[];

            static StringData* create(std::size_t cap, const char* src = nullptr, std::size_t len = 0)  // TODO: Diese Default Params sind shit
            {
                std::size_t ss{ sizeof(StringData) };

                void* mem{ ::operator new(sizeof(StringData) + cap + 1) };
                StringData* sd{ new (mem) StringData{ 1, len, cap } };

                char* cp{ reinterpret_cast<char*> (mem) + sizeof(StringData) };

                if (src && len > 0) {
                    std::memcpy(/*sd->data*/  cp, src, len);
                }

                // sd->data[len] = '\0';
                cp[len] = '\0';

                return sd;

                //std::size_t len{ std::strlen(src) };
                //void* mem{ ::operator new(sizeof(StringData) + len + 1) };
                //StringData* sd{ new (mem) StringData{ 1, len } };
                //char* cp{ reinterpret_cast<char*> (mem) + sizeof(StringData) };
                //std::memcpy(cp, src, len + 1);
                //return sd;
            }
        };

        StringData* m_ptr;

        // Idee: Kann man diese Adresse nicht als Membervariable aufheben ??
        // Wann wird diese wie initiliersiert :  cp = this + sizeof(StringData);
     //   char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };


        // Ensure writable buffer (copy-on-write)
        void detach() {
            if (m_ptr->m_refCount.load() > 1) {
                //    StringData* old = m_ptr;
                //    m_ptr = StringData::create(old->m_capacity, old->data, old->m_size);
                //    old->m_refCount--;

                StringData* old = m_ptr;
                char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
                m_ptr = StringData::create(old->m_capacity, cp, old->m_size);
                old->m_refCount--;
            }
        }

        void ensure_capacity(std::size_t new_cap) {
            if (new_cap <= m_ptr->m_capacity) {
                return;
            }

            detach(); // ensure unique before realloc

            StringData* old = m_ptr;
            std::size_t newCapacity = std::max(new_cap, old->m_capacity * 2);

            //m_ptr = StringData::create(newCapacity, old->data, old->m_size);
            //old->m_refCount--;

            char* cp{ reinterpret_cast<char*> (old) + sizeof(StringData) };
            m_ptr = StringData::create(newCapacity, cp, old->m_size);
            old->m_refCount--;

            if (old->m_refCount == 0) {
                ::operator delete(old);
            }
        }

    public:
        // Constructors
        CowStringEx() : m_ptr(StringData::create(15)) {}

        CowStringEx(const char* s) {
            std::size_t len{ std::strlen(s) };
            m_ptr = StringData::create(len, s, len);
        }

        CowStringEx(const CowStringEx& other) : m_ptr(other.m_ptr) {
            m_ptr->m_refCount++;
        }

        CowStringEx(CowStringEx&& other) noexcept : m_ptr(other.m_ptr) {
            other.m_ptr = StringData::create(15);
        }

        // Assignment
        CowStringEx& operator=(const CowStringEx& other) {
            if (this != &other) {
                if (--m_ptr->m_refCount == 0)
                    ::operator delete(m_ptr);
                m_ptr = other.m_ptr;
                m_ptr->m_refCount++;
            }
            return *this;
        }

        CowStringEx& operator=(CowStringEx&& other) noexcept {
            if (this != &other) {
                if (--m_ptr->m_refCount == 0)
                    ::operator delete(m_ptr);
                m_ptr = other.m_ptr;
                other.m_ptr = StringData::create(15);
            }
            return *this;
        }

        // Destructor
        ~CowStringEx() {
            if (--m_ptr->m_refCount == 0)
                ::operator delete(m_ptr);
        }

        // Size & capacity
        std::size_t size() const { return m_ptr->m_size; }
        std::size_t length() const { return m_ptr->m_size; }
        std::size_t capacity() const { return m_ptr->m_capacity; }
        bool empty() const { return m_ptr->m_size == 0; }

        void reserve(std::size_t new_cap) {
            if (new_cap > m_ptr->m_capacity) {
                detach();
                ensure_capacity(new_cap);
            }
        }

        void resize(std::size_t new_size, char fill = ' ')  // no default params ....
        {
            detach();

            ensure_capacity(new_size);

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };

            if (new_size > m_ptr->m_size) {

                std::memset(cp + m_ptr->m_size, fill, new_size - m_ptr->m_size);
            }

            m_ptr->m_size = new_size;
            cp[new_size] = '\0';

            //if (new_size > m_ptr->m_size) {
            //    std::memset(m_ptr->data + m_ptr->m_size, fill, new_size - m_ptr->m_size);
            //}
            //    
            //m_ptr->m_size = new_size;
            //m_ptr->data[new_size] = '\0';
        }

        // C-string access
        //const char* c_str() const { return m_ptr->data; }
        //const char* data() const { return m_ptr->data; }

        const char* c_str() const {
            return reinterpret_cast<char*> (m_ptr) + sizeof(StringData);
        }

        const char* data() const {
            return reinterpret_cast<char*> (m_ptr) + sizeof(StringData);
        }

        // type-conversion operator
        operator std::string_view()
        {
            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return { cp , m_ptr->m_size };
        }

        // Element access
        char operator[](std::size_t i) const {
            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[i];
            // return m_ptr->data[i];
        }

        char& operator[](std::size_t i) {
            detach();
            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[i];
            //  return m_ptr->data[i];
        }

        char at(std::size_t i) const {
            if (i >= m_ptr->m_size) {
                throw std::out_of_range("cow_string::at");
            }

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[i];
            //   return m_ptr->data[i];
        }

        char& at(std::size_t i) {
            if (i >= m_ptr->m_size) {
                throw std::out_of_range("cow_string::at");
            }

            detach();

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            return cp[i];
            //  return m_ptr->data[i];
        }

        // Append
        CowStringEx& append(const char* s)
        {
            std::size_t len = std::strlen(s);
            detach();
            ensure_capacity(m_ptr->m_size + len);

            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            std::memcpy(cp + m_ptr->m_size, s, len + 1);
            m_ptr->m_size += len;
            return *this;

            //std::memcpy(m_ptr->data + m_ptr->m_size, s, len + 1);
            //m_ptr->m_size += len;
            //return *this;
        }

        CowStringEx& append(const CowStringEx& other) {
            return append(other.c_str());
        }

        CowStringEx& operator+=(const CowStringEx& other) {
            return append(other);
        }

        CowStringEx& operator+=(const char* s) {
            return append(s);
        }

        //CowStringEx& operator+=(char c) {
        //    detach();
        //    ensure_capacity(m_ptr->m_size + 1);
        //    m_ptr->data[m_ptr->m_size++] = c;
        //    m_ptr->data[m_ptr->m_size] = '\0';
        //    return *this;
        //}

        // Concatenation
        //friend CowStringEx operator+(const CowStringEx& a, const CowStringEx& b) {
        //    CowStringEx r;
        //    r.ensure_capacity(a.size() + b.size());
        //    r.m_ptr->m_size = a.size() + b.size();
        //    std::memcpy(r.m_ptr->data, a.m_ptr->data, a.size());
        //    std::memcpy(r.m_ptr->data + a.size(), b.m_ptr->data, b.size() + 1);
        //    return r;
        //}

        CowStringEx& operator+=(char c) {
            detach();
            ensure_capacity(m_ptr->m_size + 1);
            char* cp{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
            cp[m_ptr->m_size++] = c;
            cp[m_ptr->m_size] = '\0';
            return *this;
        }

        //// Concatenation
        //friend CowStringEx operator+(const CowStringEx& a, const CowStringEx& b) {
        //    CowStringEx r;
        //    r.ensure_capacity(a.size() + b.size());
        //    r.m_ptr->m_size = a.size() + b.size();

        //    char* cpa{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };
        //    char* cpb{ reinterpret_cast<char*> (m_ptr) + sizeof(StringData) };

        //    std::memcpy(r.m_ptr->data, a.m_ptr->data, a.size());
        //    std::memcpy(r.m_ptr->data + a.size(), b.m_ptr->data, b.size() + 1);
        //    return r;
        //}


        // Comparisons
        friend bool operator==(const CowStringEx& a, const CowStringEx& b) {
            if (a.m_ptr == b.m_ptr) return true;
            if (a.size() != b.size()) return false;
            return std::memcmp(a.c_str(), b.c_str(), a.size()) == 0;
        }

        friend bool operator!=(const CowStringEx& a, const CowStringEx& b) {
            return !(a == b);
        }

        friend bool operator<(const CowStringEx& a, const CowStringEx& b) {
            return std::strcmp(a.c_str(), b.c_str()) < 0;
        }

        //// Iterators
        //const char* begin() const { return m_ptr->data; }
        //const char* end() const { return m_ptr->data + m_ptr->m_size; }
        //char* begin() { detach(); return m_ptr->data; }
        //char* end() { detach(); return m_ptr->data + m_ptr->m_size; }

        // Stream output
        friend std::ostream& operator<<(std::ostream& os, const CowStringEx& s) {
            return os << s.c_str();
        }
    };
}

static void test_cow_string_01()
{
    using namespace CowString03;

    CowStringEx a;
}

static void test_cow_string_02()
{
    using namespace CowString03;

    CowStringEx a{ "1234567890" };
    std::println("String: {}", a.c_str());
    std::println("Length: {}", a.size());
}

static void test_cow_string_03()
{
    using namespace CowString03;

    CowStringEx a{ "1234567890" };
    CowStringEx b{ a };
}

static void test_cow_string_04()
{
    using namespace CowString03;

    CowStringEx a{ "1234567890" };
    CowStringEx b{ a };
    CowStringEx c{ a };

    c[0] = '!';
}

static void test_cow_string_05()
{
    using namespace CowString03;

    CowStringEx a{ "1234567890" };
    CowStringEx b{ a };
    CowStringEx c{ a };

    CowStringEx x{ "ABC" };
    CowStringEx y{ x };

    a = x;
}

static void test_cow_string_06()
{
    using namespace CowString03;

    CowStringEx a{ "Hello World" };
    CowStringEx b{ a };  // shares buffer
    CowStringEx c{ b };  // shares buffer

    std::println("Before modification:");
    std::println("a: {}", a.c_str());
    std::println("b: {}", b.c_str());
    std::println("c: {}", c.c_str());

    b[0] = 'h'; // triggers copy-on-write only for 'b'
    b[6] = 'w'; // triggers copy-on-write only for 'b'

    std::println("After modification:");
    std::println("a: {}", a.c_str());  // unchanged
    std::println("b: {}", b.c_str());  // modified
    std::println("c: {}", c.c_str());  // unchanged
}

static void test_cow_string_07()
{
    using namespace CowString03;

    CowStringEx s{ "1234567890" };
    const char* p{ s.c_str() };

    {
        // in this block the contents of `s` is not modified
        CowStringEx other{ s };
        char first_char{ s[0] };
    }

    std::println("After block:");
    std::println("p: {}", p);      // p is no more valid!
}

static void test_cow_string_08()
{
    using namespace CowString03;

    CowStringEx s{ "1234567890" };
    const char* p{ s.c_str() };

    //{
        // in this block the contents of `s` is not modified
    CowStringEx other{ s };
    char first_char{ s[0] };
    //}

    std::println("After block:");
    std::println("p: {}", p);      // p is no more valid!
}

static void test_cow_string_09()
{
    using namespace CowString03;

    CowStringEx s{ "1234567890" };

    std::string_view sv{ s };
    std::println("sv:  {}", sv);

    s[9] = '!';

    std::string_view sv1 = s;
    std::println("sv:  {}", sv);
    std::println("sv1: {}", sv1);
}


static void test_cow_string_10()
{
    using namespace CowString03;

    CowStringEx s{ };
    
    s.append("A");
    s.append("B");
    s.append("C");

    std::string_view sv{ s };
    std::println("sv1:  {}", sv);
}


static void test_cow_string_11()
{
    using namespace CowString03;

    CowStringEx s1{ "1234567890" };
    CowStringEx s2{ s1 };

    s1.append("A");

    std::string_view sv1{ s1 };
    std::println("sv1:  {}", sv1);

    std::string_view sv2{ s2 };
    std::println("sv2:  {}", sv2);

}



void test_cow_string_improved()
{
    //test_cow_string_01();
    //test_cow_string_02();
    //test_cow_string_03();
    //test_cow_string_04();
    //test_cow_string_05();
    //test_cow_string_06();
    //test_cow_string_07();
    //test_cow_string_08();
    //test_cow_string_09();

    test_cow_string_10();
    //test_cow_string_11();
}

