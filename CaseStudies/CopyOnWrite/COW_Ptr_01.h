
// Wikipedia

#ifndef COWPTR_HPP
#define COWPTR_HPP

#include <memory>

template <class T>
class CowPtr
{
public:
    typedef std::shared_ptr<T> RefPtr;

private:
    RefPtr m_sp;

    void detach()
    {
        T* tmp = m_sp.get();
        if (!(tmp == nullptr || m_sp.unique())) {
            m_sp = RefPtr(new T(*tmp));
        }
    }

public:
    CowPtr(T* t)
        : m_sp(t)
    {
    }
    CowPtr(const RefPtr& refptr)
        : m_sp(refptr)
    {
    }
    const T& operator*() const
    {
        return *m_sp;
    }
    T& operator*()
    {
        detach();
        return *m_sp;
    }
    const T* operator->() const
    {
        return m_sp.operator->();
    }
    T* operator->()
    {
        detach();
        return m_sp.operator->();
    }
};

#endif