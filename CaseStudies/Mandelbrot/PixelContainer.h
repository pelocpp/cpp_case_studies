// =====================================================================================
// PixelContainer.h
// =====================================================================================

#include "Pixel.h"

#include <stack>
#include <mutex>

class PixelContainerStack
{
private:
    mutable std::mutex m_mutex;
    std::stack<Pixel>  m_container;

public:
    PixelContainerStack () {}

    void add(Pixel pixel) {

        std::lock_guard<std::mutex> guard{ m_mutex };
        m_container.push(pixel);
    }

    Pixel remove() {

        Pixel top = m_container.top();
        m_container.pop();
        return top;
    }

    void clear() {

        std::lock_guard<std::mutex> guard{ m_mutex };
        std::stack<Pixel> empty;
        std::swap(m_container, empty);
    }
    
    size_t size() {

        return m_container.size();
    }

    void swap(PixelContainerStack& other) noexcept {
        using std::swap;
        std::swap(other.m_container, m_container);
    }
    
    std::mutex& mutex() {
        return m_mutex;
    }
};

class PixelContainerDeque
{
private:
    mutable std::mutex m_mutex;
    std::deque<Pixel>  m_container;

public:
    void add(Pixel pixel) {

        std::lock_guard<std::mutex> guard{ m_mutex };
        m_container.push_back(pixel);
    }

    Pixel remove() {

        Pixel front = m_container.front();
        m_container.pop_front();
        return front;
    }

    void clear() {
        m_container.clear();
    }

    size_t size() {

        return m_container.size();
    }

    void swap(PixelContainerDeque& other) noexcept {
        using std::swap;
        std::swap(other.m_container, m_container);
    }

    std::mutex& mutex() {
        return m_mutex;
    }
};

//void swap(PixelContainerDeque& lhs, PixelContainerDeque& rhs) noexcept {
//
//    lhs.swap(rhs);
//}

// =====================================================================================
// End-of-File
// =====================================================================================
