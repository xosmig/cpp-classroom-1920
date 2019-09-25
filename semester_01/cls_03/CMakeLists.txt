cmake_minimum_required (VERSION 3.8)

project(classwork-03)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

# Uncomment to work on task 1
add_executable(task-1-test src/task_1/test.cpp)

# Uncomment to work on task 2
#add_executable(task-2-test src/task_2/test.cpp src/task_2/ladder_combinations.cpp)

# Uncomment to work on task 3
#add_executable(task-3-test src/task_3/test.cpp src/task_3/concat.cpp)

# Uncomment to work on task 4
#add_executable(task-4-test src/task_4/test.cpp src/task_4/matrices.cpp)
