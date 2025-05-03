// From Ch22.3 learncpp.com
// Deep copy

#include "resource.h"

template <typename T>
class Auto_ptr_v4
{
    T* m_ptr {};
public:
    Auto_ptr_v4(T* ptr=nullptr)
        : m_ptr(ptr)
    {}

    ~Auto_ptr_v4()
    {
        delete m_ptr;
    }

    // Copy constructor from v3
    Auto_ptr_v4(const Auto_ptr_v4& a)
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Move constructor, tranfser ownership from a.m_ptr to m_ptr
    Auto_ptr_v4(Auto_ptr_v4&& a) noexcept
        : m_ptr { a.m_ptr }
    {
        a.m_ptr = nullptr;
    }

    // Copy assignment operator from v3
    Auto_ptr_v4& operator=(const Auto_ptr_v4& a)
    {
        std::cout << "Copy assignment caled!\n";

        if (&a == this)
            return *this;
        
        delete m_ptr;
        
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }

    // Move assignment operator, transfer ownership from a.m_ptr to m_ptr
    Auto_ptr_v4& operator=(Auto_ptr_v4&& a) noexcept
    {
        std::cout << "Move assignment called!\n";

        if (&a == this)
            return *this;
        
        delete m_ptr;
        
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

template <typename T>
Auto_ptr_v4<T> generateResource()
{
    return Auto_ptr_v4<T> {new T};
}

int main()
{
    Auto_ptr_v4<Resource> original_ptr;
    original_ptr = generateResource<Resource>(); // Move assignment
    return 0;
}