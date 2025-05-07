/* How to override operator<< for a derived class; includes chaining */

#include <iostream>

struct Employee
{
    std::string name{};
    int id{};

    friend std::ostream& operator<<(std::ostream& out, const Employee& e)
    {
        out << "Employee(" << e.name << ", " << e.id;
        return out;
    }
};

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
    Employee m_e{};
public:
    Derived(const Employee& e)
        : m_e{e}
    {}

    std::ostream& print(std::ostream& out) const override
    {
        std::cout << "Derived" << '\n' << m_e << '\n';
        return out;
    }
};

int main()
{
    Base b{};
    Derived d{ Employee{"Jim Halpert", 2004} };

    std::cout << b << '\n';
    std::cout << d << '\n';
    
    return 0;
}