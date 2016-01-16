cmake_minimum_required(VERSION 2.8)

project(wallaby-estop)

add_executable(wallaby-estop main.cpp)

install(TARGETS wallaby-estop DESTINATION bin)

