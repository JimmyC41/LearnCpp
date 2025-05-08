#include <iostream>
#include <format>
#include <algorithm>

int main()
{
    size_t sz {};
    std::cout << "How many names do you want to enter? ";
    std::cin >> sz;

    auto* container { new std::string[sz]{} };

    for (size_t i = 0; i < sz; ++i)
    {
        std::string new_name;
        std::cout << std::format("Enter name #{}: ", i + 1);
        std::cin >> new_name;
        container[i] = new_name;
    }

    std::sort(container, container + sz);
    std::cout << "Here is your sorted list: ";
    for (size_t i = 0; i < sz; ++i)
    {
        std::cout << container[i];
        if (i < sz - 1) std::cout << ", ";
        else std::cout << '\n';
    }

    delete[] container;
    return 0;
}