#pragma once

#include <memory>

namespace cls_2 {

template <class T>
class unique_ptr
{
public:
    unique_ptr() noexcept
        : ptr_(nullptr)
    { };

    /*implicit*/ unique_ptr(T* ptr) noexcept
        : ptr_(ptr)
    { }

    unique_ptr(unique_ptr&& other) noexcept
        : ptr_(other.release())
    { }

    void swap(unique_ptr& other) noexcept
    {
        std::swap(ptr_, other.ptr_);
    }

    unique_ptr& operator=(unique_ptr other) noexcept
    {
        swap(other);
        return *this;
    }

    T& operator*() const noexcept
    {
        return *ptr_;
    }

    T* operator->() const noexcept
    {
        return ptr_;
    }

    void reset(T* ptr = nullptr) noexcept(noexcept(delete ptr))
    {
        auto old_ptr = ptr_;
        ptr_ = ptr;
        if (old_ptr != nullptr) {
            delete old_ptr;
        }
    }

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    T* get() const noexcept
    {
        return ptr_;
    }

    T* release() noexcept
    {
        auto res = ptr_;
        ptr_ = nullptr;
        return res;
    }

    ~unique_ptr()
    {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
    }

private:
    T* ptr_;
};

template <class T, class ... Args>
unique_ptr<T> make_unique(Args&& ... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // namespace cls_2
