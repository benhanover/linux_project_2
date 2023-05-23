cmake_minimum_required(VERSION 3.13)
project(project2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)              # Enable c++20 standard



set(CMAKE_BUILD_TYPE Debug)
set(MAIN RunMe.cpp)
file(GLOB UTILITIES CONFIGURE_DEPENDS "./utilities/.cpp")
file(GLOB MISSIONS CONFIGURE_DEPENDS "./missions/.cpp")


add_executable(runMe ${MAIN} ${UTILITIES} ${MISSIONS})
