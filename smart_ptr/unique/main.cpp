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
    T* ptr_{};

public:
    UniquePointer() noexcept : UniquePointer(nullptr) {}
    UniquePointer(T* raw) noexcept : ptr_{raw} {}
    UniquePointer(UniquePointer const&) = delete;

    UniquePointer(UniquePointer&& other) noexcept :
    {
        std::cout << "Move constructor called.\n";
        MoveFrom(other);
    }

    UniquePointer& operator=(UniquePointer const&) = delete;

    UniquePointer& operator=(UniquePointer&& other) noexcept
    {
        std::cout << "Move operator= called.\n";
        if (this != &other)
        {
            Reset();
            MoveFrom(other);
        }
        return *this;
    }

    ~UniquePointer() noexcept
    {
        std::cout << "Destructor called.\n";
        Reset();
    }
    
    T* release() noexcept
    {
        T* old = ptr_;
        ptr_ = nullptr;
        return old;
    }

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T* get() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    void MoveFrom(UniquePointer&& other) noexcept
    {
        ptr_ = std::exchange(other.ptr_, nullptr);
    }

    void Reset(T* newPtr = nullptr) noexcept
    {
        if (ptr_)
            Deleter{}(ptr_);
        ptr_ = newPtr;
    }
};

int main()
{
    int* raw = nullptr;
    {
        UniquePointer<int> p1(new int(1403));
        std::cout << "*p1 =  " << *p1 << '\n';
        raw = p1.release();
    }
    *raw = 2025;

    UniquePointer<int> p2(raw);
    std::cout << "*p2 =  " << *p2 << '\n';

    UniquePointer<int> p3{std::move(p2)};
    std::cout << "*p3 =  " << *p3 << '\n';

    UniquePointer<int> p4{};
    p4 = std::move(p3);
    *p4 = 14032025;

    std::cout << "*p4 = " << *p4 << '\n';

    return 0;
}