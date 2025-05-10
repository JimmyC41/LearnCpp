#include <iostream>

template <typename T>
struct CustomDeleter
{
    void operator()(T* ptr) const
    {
        std::cout << "Deleting resource!\n";
        delete ptr;
    }
};

template <typename T, typename Deleter = CustomDeleter<T>>
class UniquePointer
{
private:
    T* _ptr{};

public:
    UniquePointer() noexcept
        : _ptr{nullptr}
    {}

    // explicit: Prevent implicit ownership transfer of the raw pointer
    explicit UniquePointer(T* raw) noexcept
        : _ptr{raw}
    {}

    // Disable copy constructor and assignment
    UniquePointer(UniquePointer const&) = delete;
    UniquePointer& operator=(UniquePointer const&) = delete;

    UniquePointer(UniquePointer&& other) noexcept
        : _ptr{std::exchange(other._ptr, nullptr)}
    {}

    UniquePointer& operator=(UniquePointer&& other) noexcept
    {
        std::cout << "Move operator= called.\n";

        if (this != &other)
        {
            reset();
            _ptr = std::exchange(other._ptr, nullptr);
        }

        return *this;
    }

    ~UniquePointer() noexcept
    {
        std::cout << "Destructor called.\n";

        if (_ptr) Deleter{}(_ptr);
    }
    
    T* release() noexcept
    {
        T* old = _ptr;
        _ptr = nullptr;
        return old;
    }

    void reset(T* newPtr = nullptr) noexcept
    {
        if (_ptr) Deleter{}(_ptr);
        _ptr = newPtr;
    }

    T& operator*() const noexcept { return *_ptr; }
    T* operator->() const noexcept { return _ptr; }
    T* get() const noexcept { return _ptr; }
    explicit operator bool() const noexcept { return _ptr != nullptr; }
};

int main()
{
    {
        UniquePointer<int> p1(new int(1403));
        std::cout << "*p1 =  " << *p1 << '\n';

        *p1 = 2025;

        UniquePointer<int> p2 = std::move(p1);
        std::cout << "*p2 =  " << *p1 << '\n';
    }

    return 0;
}