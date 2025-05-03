#include <iostream>

class A
{
private:
    int m {};
public:
    void setM(int newM) { m = newM; }
    friend class B;
};

class B
{
public:
    void printMember(const A& a) { std::cout << a.m << '\n'; }
};

int main()
{
    A obj_A {};
    B obj_B {};

    obj_B.printMember(obj_A);
    obj_A.setM(10);
    obj_B.printMember(obj_A);
}