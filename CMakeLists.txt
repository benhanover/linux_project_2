cmake_minimum_required(VERSION 3.13)  # CMake version check
project(runMe VERSION 1.0)               # Create project "hello"
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)              # Enable c++20 standard

#find_library(ZIPLIB zip)

#add custom lib
#add_subdirectory(my_lib)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES RunMe.cpp)

#add all src files 
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB SRC_FILES CONFIGURE_DEPENDS "./*.cpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "./missions/*.cpp")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(runMe ${SOURCE_FILES} ${SRC_FILES})

#target_link_libraries(runMe PUBLIC my_lib)
#target_link_libraries(runMe PUBLIC ${ZIPLIB})
#target_link_libraries(runMe PUBLIC "/usr/local/lib/libzip.so")


# target_include_directories(runMe PUBLIC  
#                            "${CMAKE_CURRENT_SOURCE_DIR}/include/"
#                            "${CMAKE_CURRENT_SOURCE_DIR}/My_lib/include/"
#                            "/usr/local/include/"
#                            )

