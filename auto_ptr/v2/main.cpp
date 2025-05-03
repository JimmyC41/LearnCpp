// From Ch22.3 learncpp.com
// Shallow copy move semantics

// Issue: When pass by value, resource is moved to parameter and destroyed when
// out of scope. Then, when you go to access the resource, you dereference a
// null pointer!

#include "resource.h"

template <typename T>
class Auto_ptr_v2
{
    T* m_ptr {};
public:
    Auto_ptr_v2(T* ptr=nullptr)
        : m_ptr(ptr)
    {}

    ~Auto_ptr_v2()
    {
        delete m_ptr;
    }

    // Copy constructor, does a shallow copy from a.m_ptr to m_ptr
    Auto_ptr_v2(Auto_ptr_v2& a)
    {
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
    }

    // Assignment operator, does a shallow copy from a.m_ptr to m_ptr
    Auto_ptr_v2& operator=(Auto_ptr_v2& a)
    {
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
void passByValuePrint(const Auto_ptr_v2<T> param)
{
    std::cout << "Address of resource held by value parameter is: " << param.get() << '\n';
}

int main()
{
    // original_ptr holds pointer to the resource
    Auto_ptr_v2<Resource> original_ptr(new Resource());
    std::cout << "Address of resource held by original_ptr is " << original_ptr.get() << '\n';

    // Resource transferred to param and destroyed at the end of scope
    passByValuePrint(original_ptr);

    // The pointer to the resource is now nullptr
    std::cout << "Address of resource held by original_ptr is " << original_ptr.get() << '\n';
    return 0;
}