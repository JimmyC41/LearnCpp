#include <iostream>

void selectionSort(int* array, int size, bool(*comparisonFcn)(int, int))
{
    if (!array || !comparisonFcn) return;

    for (int startIdx{0}; startIdx < (size - 1); ++startIdx)
    {
        int bestIdx{startIdx};

        for (int curIdx{startIdx + 1}; curIdx < size; ++curIdx)
        {
            if (comparisonFcn(array[bestIdx], array[curIdx]))
                bestIdx = curIdx;
        }
        std::swap(array[startIdx], array[bestIdx]);
    }
}

void printArray(int* array, int size)
{
    if (!array) return;
    
    for (size_t idx{0}; idx < size; ++idx)
    {
        std::cout << array[idx];

        if (idx < size - 1) std::cout << ' ';
        else std::cout << '\n';
    }
}

template <typename T>
bool ascending(T x, T y)
{
    return x > y;
}

template <typename T>
bool descending(T x, T y)
{
    return x < y;
}

int main()
{
    int array[9]{3, 7, 9, 5, 6, 1, 8, 2, 4};

    selectionSort(array, 9, ascending);
    printArray(array, 9);

    selectionSort(array, 9, descending);
    printArray(array, 9);

    return 0;
}