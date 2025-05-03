// From Ch22.3 learncpp.com
// Deep copy
// Works, but copying rvalues is inefficient

#include "resource.h"

template <typename T>
class Auto_ptr_v3
{
    T* m_ptr {};
public:
    Auto_ptr_v3(T* ptr=nullptr)
        : m_ptr(ptr)
    {}

    ~Auto_ptr_v3()
    {
        delete m_ptr;
    }

    // Copy constructor, do a deep copy of a.m_ptr to m_ptr
    Auto_ptr_v3(const Auto_ptr_v3& a)
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        
        // m_ptr still points to original resource
        // a.m_ptr points to a newly-allocated copy of the resource
    }

    // Assignment operator, do a deep copy of a.m_ptr to m_ptr
    Auto_ptr_v3& operator=(const Auto_ptr_v3& a)
    {
        if (&a == this)
            return *this;
        
        delete m_ptr;
        
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

template <typename T>
Auto_ptr_v3<T> generateResource()
{
    return Auto_ptr_v3<T> {new T};
}

int main()
{
    Auto_ptr_v3<Resource> original_ptr;
    original_ptr = generateResource<Resource>();
    return 0;
}