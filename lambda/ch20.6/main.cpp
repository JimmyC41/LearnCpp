#include <functional>
#include <iostream>

// Avoid copying functor, allow rvalues
// Abbreviated function template syntax (C++ 20)
void repeat_auto(int reps, const auto& fn)
{
    std::cout << "Calling repeat_auto!\n";
    for (int i{0}; i < reps; ++i)
        fn(i);
}

template <typename T>
void repeat_auto_templated(int reps, const T& fn)
{
    std::cout << "Calling repeat_auto_templated!\n";
    for (int i{0}; i < reps; ++i)
        fn(i);
}

int main()
{
    auto print_lambda = [](int i) -> void
    {
        std::cout << i << '\n';
    };

    repeat_auto(5, print_lambda);
    repeat_auto_templated(5, [](int i) { std::cout << i * 2 << '\n'; });
    return 0;
}