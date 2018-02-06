cmake_minimum_required(VERSION 3.8)
project(SMS)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp core/auth/user.cpp core/auth/user.h core/init.cpp core/init.h core/view.cpp core/view.h core/menu.cpp core/menu.h courses/courses.h courses/courses.cpp attendance/attendance.cpp attendance/attendance.h)
add_executable(SMS ${SOURCE_FILES})