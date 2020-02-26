#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

namespace cls_03 {

class Event
{
public:
    Event(std::string name, int room, int startTime, int length)
        : name_(std::move(name))
        , room_(room)
        , start_time_(startTime)
        , length_(length)
    { }

    const std::string& name() const noexcept
    {
        return name_;
    }

    int room() const noexcept
    {
        return room_;
    }

    int start_time() const noexcept
    {
        return start_time_;
    }

    int end_time() const noexcept
    {
        return start_time_ + length_; // - 1;
    }

    bool operator==(const Event& other) const noexcept
    {
        return name_ == other.name_ && room_ == other.room_ && start_time_ == other.start_time_ &&
            length_ == other.length_;
    }

private:
    std::string name_;
    int room_;
    int start_time_;
    int length_;
};


class DaySchedule
{
public:
    class iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = Event;
        using difference_type = int;
        using pointer = Event*;
        using reference = Event&;

        iterator(const iterator& other) = default;

        const iterator& operator++()  // pre-increment
        {
            assert(room_it_ != room_end_);
            room_it_++;
            event_ = std::nullopt;
            find_next();
            return *this;
        }

        iterator operator++(int)  // post-increment
        {
            auto ret = *this;
            ++*this;
            return ret;
        }

        bool operator==(const iterator& other) const
        {
            return room_it_ == other.room_it_ && moment_ == other.moment_;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        const value_type& operator*() const
        {
            return **event_;
        }

    private:
        friend class DaySchedule;
        using room_iterator = std::map<int, std::map<int, Event>>::const_iterator;

        iterator(room_iterator room_it, room_iterator room_end, int moment)
            : room_it_(room_it)
            , room_end_(room_end)
            , moment_(moment)
        {
            find_next();
        }

        std::optional<const Event*> event_;
        room_iterator room_it_;
        room_iterator room_end_;
        int moment_;

        void find_next()
        {
            while (room_it_ != room_end_ && !event_.has_value()) {
                const auto& event_by_end = room_it_->second;
                auto candidate_it = event_by_end.lower_bound(moment_);

                if (candidate_it != event_by_end.end() && candidate_it->second.start_time() <= moment_) {
                    event_ = &candidate_it->second;
                }
            }
        }
    };

public:
    explicit DaySchedule(std::set<int> rooms = {})
        : rooms_(std::move(rooms))
    { }

    bool try_add_event(const Event& ev)
    {
        auto& event_by_end = event_by_end_by_room_[ev.room()];

        if (!rooms_.count(ev.room())) {
            throw std::invalid_argument("Invalid room " + std::to_string(ev.room()));
        }
        auto possible_conflict_it = event_by_end.lower_bound(ev.start_time());

        if (possible_conflict_it != event_by_end.end() && possible_conflict_it->second.start_time() < ev.end_time()) {
            return false;
        }

        event_by_end.insert({ev.end_time(), ev});
        return true;
    }

    std::pair<iterator, iterator> get_events_at_moment(int moment)
    {
        return {
            iterator(cbegin(event_by_end_by_room_), cend(event_by_end_by_room_), moment),
            iterator(cend(event_by_end_by_room_), cend(event_by_end_by_room_), moment)
        };
    }

private:
    std::set<int> rooms_;
    std::map<int, std::map<int, Event>> event_by_end_by_room_;

};

} // namespace cls_03

