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
    bool               m_calculationFinished;

public:
    PixelContainerStack()  : m_calculationFinished{ false } {}

    void add(Pixel pixel) {

        std::lock_guard<std::mutex> guard{ m_mutex };
        m_container.push(pixel);
    }

    Pixel remove() {

        if (!m_calculationFinished) {

            if (m_container.size() == 0) {
                throw std::out_of_range("No pixel available!");
            }

            Pixel top = m_container.top();
            m_container.pop();
            return top;
        }
        else {

            if (m_container.size() != 0) {

                Pixel top = m_container.top();
                m_container.pop();
                return top;
            }
            else /* if (m_container.size() == 0) */ {

                Pixel last{ SIZE_MAX, SIZE_MAX, 0 };
                return last;
            }

            // TODO: Wenn das mehrere Male bei size == 0 aufgerufen wird ... dann sollte eine exc. geworfen werden
        }

    }

    void clear() {

        std::lock_guard<std::mutex> guard{ m_mutex };
        std::stack<Pixel> empty;
        std::swap(m_container, empty);
    }
    
    size_t size() {

        //if (!m_calculationFinished) {
        //    return m_container.size();
        //}
        //else {
        //    return 1 + m_container.size();
        //}
    
        return m_container.size();
    }

    void endOfCalculationReached() {

        std::lock_guard<std::mutex> guard{ m_mutex };
        m_calculationFinished = true;
    }

    void swap(PixelContainerStack& other) noexcept {
        using std::swap;
        std::swap(other.m_container, m_container);
        std::swap(other.m_calculationFinished, m_calculationFinished);
    }
    
    std::mutex& mutex() {
        return m_mutex;
    }
};

// =====================================================================================

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

        if (m_container.size() == 0) {
            throw std::out_of_range("No pixel available!");
        }

        Pixel front = m_container.front();
        m_container.pop_front();
        return front;
    }

    void clear() {
        std::lock_guard<std::mutex> guard{ m_mutex };
        m_container.clear();
    }

    size_t size() {
        return m_container.size();
    }

    void endOfCalculationReached() {

        // last calculation thread inserts "end-of-pixels-queue" marker
        Pixel pixel{ SIZE_MAX, SIZE_MAX, 0 };
        add(pixel);
    }

    void swap(PixelContainerDeque& other) noexcept {
        using std::swap;
        std::swap(other.m_container, m_container);
    }

    std::mutex& mutex() {
        return m_mutex;
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
