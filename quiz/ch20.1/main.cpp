// Basic calculator w/ std::function (function pointer)

#include <functional>
#include <iostream>
#include <assert.h>
#include <format>

using ArithmeticFunction = std::function<int(int, int)>;

int add(int x, int y) { return x + y; }

int subtract(int x, int y) { return x - y; }

int multiply(int x , int y) { return x * y; }

int divide(int x, int y)
{
    assert(y != 0);
    return x / y;
}

ArithmeticFunction getArithmeticFunction(char op)
{
    if (op == '+') return add;
    if (op == '-') return subtract;
    if (op == '*') return multiply;
    if (op == '/') return divide;
    return add;
}

int getInteger()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    return x;
}

char getOperation()
{
    char op{};
    do
    {
        std::cout << "Enter an operation (+, -, *, /): ";
        std::cin >> op;
    } while (op != '+' && op != '-' && op != '*' && op != '/');
    return op;
}

void getInput(int& a, int& b, char& op)
{
    a = getInteger();
    b = getInteger();
    op = getOperation();
}

int main()
{
    std::cout << "Welcome to the calculator!\n";

    int a{};
    int b{};
    char op{};
    getInput(a, b, op);

    int res = getArithmeticFunction(op)(a, b);
    std::cout << std::format("{} {} {} = {}\n", a, op, b, res);

    return 0;
}