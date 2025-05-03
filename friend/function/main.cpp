#include <iostream>

class A;

class C
{
public:
    void printMember(const A& a);
};

class A
{
private:
    int m {};
public:
    void setM(int newM) { m = newM; }
    friend void C::printMember(const A& a);
};

void C::printMember(const A& a)
{
    std::cout << a.m << '\n';
}

int main()
{
    A obj_A {};
    C obj_C {};

    obj_C.printMember(obj_A);
    obj_A.setM(10);
    obj_C.printMember(obj_A);
    
    return 0;
}