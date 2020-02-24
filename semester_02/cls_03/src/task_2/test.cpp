#include "schedule.hpp"

#include <cassert>
#include <vector>
#include <string>

void test_no_rooms() {
    cls_03::DaySchedule schedule;

    cls_03::Event ev("discuss", 42, 43200, 3600);

    try {
        schedule.try_add_event(ev);
        assert(false);
    } catch (std::exception const&) {

    }
}

void test_correct_planning() {
    cls_03::DaySchedule schedule({42});

    cls_03::Event ev("discuss", 42, 43200, 3600);
    assert(schedule.try_add_event(ev));

    cls_03::Event ev2("discuss2", 42, 32400, 3600);
    assert(schedule.try_add_event(ev2));
}


void test_no_free_rooms() {
    cls_03::DaySchedule schedule({42});

    cls_03::Event ev("discuss", 42, 43200, 3600);
    assert(schedule.try_add_event(ev));

    cls_03::Event ev2("discuss2", 42, 43000, 3600);
    assert(!schedule.try_add_event(ev2));
}


void test_different_rooms() {
    cls_03::DaySchedule schedule({42, 24});

    cls_03::Event ev("discuss", 42, 43200, 3600);
    assert(schedule.try_add_event(ev));

    cls_03::Event ev2("discuss2", 24, 43000, 3600);
    assert(schedule.try_add_event(ev2));
}


void test_get_planned_events() {
    cls_03::DaySchedule schedule({42, 12, 24});

    cls_03::Event ev("discuss", 42, 43200, 3600);
    schedule.try_add_event(ev);

    cls_03::Event ev2("discuss2", 24, 41400, 7200);
    schedule.try_add_event(ev2);

    cls_03::Event ev3("discuss3", 24, 32400, 3600);
    schedule.try_add_event(ev3);

    cls_03::Event ev4("discuss4", 12, 45000, 3600);
    schedule.try_add_event(ev4);

    auto plannedEventsRange = schedule.get_events_at_moment(45000);
    std::vector<cls_03::Event> expectedPlannedEvents { ev4, ev2, ev };

    assert(std::equal(expectedPlannedEvents.cbegin(), expectedPlannedEvents.cend(),
                      plannedEventsRange.first, plannedEventsRange.second));
}

#ifdef SEM_02_CLS_02_TASK_2_PRIVATE_TEST
#include "sem_02_cls_02_task_2_private_test.cpp"
#endif

int main() {
    test_no_rooms();
    test_correct_planning();
    test_no_free_rooms();
    test_different_rooms();
    test_get_planned_events();
#ifdef SEM_02_CLS_02_TASK_2_PRIVATE_TEST
    test_private();
#endif
    return 0;
}