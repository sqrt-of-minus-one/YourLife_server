cmake_minimum_required(VERSION 3.5)
project(yourlife_server)

set(CMAKE_CXX_STANDARD 20)

find_package(LuaCpp REQUIRED)
include_directories(yourlife_server ${LUACPP_INCLUDE_DIR})

set(SOURCE_EXE Source/main.cpp)

add_executable(yourlife_server ${SOURCE_EXE})

target_link_libraries(yourlife_server ${LUACPP_LIBRARIES})
