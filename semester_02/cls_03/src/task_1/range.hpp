#pragma once

#include <iterator>
#include <utility>

namespace cls_03 {

template <class Iter>
class range
{
public:
    using iterator = Iter;
    using reverse_iterator = std::reverse_iterator<Iter>;

public:
    range(Iter from, Iter to)
        : from_(from)
        , to_(to)
    { }

    range(const range& other) = default;

    iterator begin() const &
    {
        return from_;
    }

    iterator begin() &&
    {
        return std::move(from_);
    }

    iterator end() const &
    {
        return to_;
    }

    iterator end() &&
    {
        return std::move(to_);
    }

    range<reverse_iterator> reversed()
    {
        return range<reverse_iterator>(reverse_iterator(to_), reverse_iterator(from_));
    }

private:
    Iter from_;
    Iter to_;
};

template <class Iter>
range<Iter> make_range(Iter from, Iter to)
{
    return range(std::move(from), std::move(to));
}

template <class Iter>
range<Iter> make_range(std::pair<Iter, Iter> pair)
{
    return make_range(std::move(pair.first), std::move(pair.second));
}

} // namespace cls_03
