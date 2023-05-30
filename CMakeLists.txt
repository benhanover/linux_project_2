cmake_minimum_required(VERSION 3.13)
project(project2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)              # Enable c++20 standard

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-w)  # Suppress all warnings

# Find libzip package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBZIP REQUIRED IMPORTED_TARGET libzip)

# Set your source files
set(MAIN RunMe.cpp)
file(GLOB UTILITIES CONFIGURE_DEPENDS "./utilities/*.cpp")
file(GLOB MISSIONS CONFIGURE_DEPENDS "./missions/*.cpp")

# Create the executable and link against libzip
add_executable(runMe ${MAIN} ${UTILITIES} ${MISSIONS})
target_link_libraries(runMe PRIVATE PkgConfig::LIBZIP)
















# target_include_directories(runMe PUBLIC  
#                            "${MAKE_CURRENT_SOURCE_DIR}/include/"
#                            "${CMAKE_CURRENT_SOURCE_DIR}/utilities/include/"
#                            "/usr/local/include/"
#                            )


#find_library(ZIPLIB zip)

#add custom lib
#add_subdirectory(my_lib)

# Add main.cpp file of project root directory as source file
#add all src files 
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
# Add executable target with source files listed in SOURCE_FILES variable
#target_link_libraries(runMe PUBLIC my_lib)
#target_link_libraries(runMe PUBLIC ${ZIPLIB})
#target_link_libraries(runMe PUBLIC "/usr/local/lib/libzip.so")
