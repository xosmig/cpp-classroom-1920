#pragma once

#include <cassert>
#include <utility>
#include <memory>

namespace control_01 {

template <class T>
class vector
{
 public:
  using iterator = T*;
  using const_iterator = const T*;

 public:
  vector() = default;

  template <class InputIter>
  vector(InputIter first, InputIter last)
    : this()
  {
    for (auto it = first; it != last; it++) {
      push_back(*it);
    }
  }

  vector(const vector& other)
      : this(std::begin(other), std::end(other))
  { }

  vector(vector&& other) noexcept
      : data_(other.data_)
      , size_(other.size_)
      , cap_(other.cap_)
  {
    other.data_.release();
    other.size_ = 0;
    other.cap_ = 0;
  }

  vector& operator=(T other)
  {
    swap(other);
    return *this;
  }

  void swap(T& other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
  }

  const_iterator begin() const noexcept
  {
    return data_.get();
  }

  const_iterator end() const noexcept
  {
    return data_.get() + size_;
  }

  iterator begin() noexcept
  {
    return data_.get();
  }

  iterator end() noexcept
  {
    return data_.get() + size_;
  }

  void push_back(const T& elem)
  {
    emplace_back(elem);
  }

  void push_back(T&& elem)
  {
    emplace_back(std::move(elem));
  }

  template <class ... Args>
  void emplace_back(Args&& ... args)
  {
    reserve(size_ + 1);
    new (data_.get() + size_) T(std::forward<Args>(args)...);
  }

  void pop_back()
  {
    assert(size_ > 0);
    data_.get()[size_ - 1].~T();
    size_--;
  }

  const T& front() const noexcept
  {
    return const_cast<vector&>(*this).front();
  }

  T& front() noexcept
  {
    assert(size_ > 0);
    return data_.get()[0];
  }

  const T& back() const noexcept
  {
    return const_cast<vector&>(*this).back();
  }

  T& back() noexcept
  {
    assert(size_ > 0);
    return data_.get()[size - 1];
  }

  T& operator[](size_t idx) noexcept
  {
    assert(idx >= 0 && idx < size_);
    return data_.get()[idx];
  }

  const T& operator[](size_t idx) const noexcept
  {
    return const_cast<vector&>(*this)[idx];
  }

  T& at(size_t idx)
  {
    if (idx < 0 || idx >= size_) {
      throw std::invalid_argument("Invalid index " + idx);
    }
    return (*this)[idx];
  }

  const T& at(size_t idx) const
  {
    return const_cast<vector&>(*this).at(idx);
  }

  void reserve(size_t hint)
  {
    size_t new_cap = std::max(hint, cap_ * 2);
    std::unique_ptr<T[]> new_data = Allocator().allocate(new_cap);
    if constexpr (noexcept(new (0) T(std::move(std::declval<T>())))) {
      for (size_t i = 0; i < size_; i++) {
        new (new_data.get() + i) T(std::move(data_.get()[i]));
      }
    } else {
      size_t cur = 0;
      try {
        for (cur = 0; cur < size_; cur++) {
          new (new_data.get() + cur) T(data_.get()[cur]);
        }
      } catch (...) {
        while (cur > 0) {
          cur--;
          new_data.get()[cur].~T();
        }
        throw;
      }
    }
    std::swap(data_, new_data);
  }

  size_t size() const noexcept
  {
    return size_;
  }

  size_t capacity() const noexcept
  {
    return cap_;
  }

  bool empty() const noexcept
  {
    return size_ == 0;
  }

 private:
  using Allocator = std::allocator<T>;

  std::unique_ptr<T[]> data_;
  size_t size_;
  size_t cap_;
};

} // namespace control_01
