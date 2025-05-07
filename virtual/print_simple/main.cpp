/* How to override operator<< for a derived class */

#include <iostream>

class Base
{
public:
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        return b.print(out);
    }

    virtual std::ostream& print(std::ostream& out) const
    {
        std::cout<< "Base";
        return out;
    }
};

class Derived : public Base
{
public:
    std::ostream& print(std::ostream& out) const override
    {
        std::cout << "Derived";
        return out;
    }
};

int main()
{
    Base b{};
    Derived d{};

    std::cout << b << '\n';
    std::cout << d << '\n';
    
    return 0;
}