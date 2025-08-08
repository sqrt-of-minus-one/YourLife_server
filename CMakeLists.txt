cmake_minimum_required(VERSION 3.5)
project(yourlife_server)

set(CMAKE_CXX_STANDARD 20)

find_package(LuaCpp REQUIRED)
include_directories(yourlife_server ${LUACPP_INCLUDE_DIR})
include_directories(yourlife_server Source)

set(SOURCE_TIME Source/Time/Date.cpp Source/Time/Time.cpp Source/Time/DateTime.cpp Source/Time/TimeInterval.cpp)
set(SOURCE_UTIL Source/Util/Util.cpp)

set(SOURCE_EXE ${SOURCE_TIME} ${SOURCE_UTIL} Source/main.cpp)

add_executable(yourlife_server ${SOURCE_EXE})

target_link_libraries(yourlife_server ${LUACPP_LIBRARIES})
