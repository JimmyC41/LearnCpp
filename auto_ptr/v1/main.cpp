// From Ch22.1 learncpp.com
// Compiler generated memberwise copy constructor and assignment operator

#include "resource.h"

template <typename T>
class Auto_ptr_v1
{
    T* m_ptr {};
public:
    Auto_ptr_v1(T* ptr=nullptr)
        : m_ptr(ptr)
    {}

    ~Auto_ptr_v1()
    {
        delete m_ptr;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

int main()
{
    Auto_ptr_v1<Resource> res1(new Resource());
    Auto_ptr_v1<Resource> res2(res1); // Results in double free of resource
    return 0;
}