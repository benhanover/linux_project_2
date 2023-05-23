#cmake_minimum_required(VERSION 3.13)  # CMake version check
#project(runMe VERSION 1.0)               # Create project "hello"
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)              # Enable c++20 standard

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

# Project name
project(runMe VERSION 1.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)              # Enable c++20 standard

# Specify the source files for the shared library
set(SHARED_LIBRARY_SOURCES
    src/utilities/utility.cpp
)

# Specify the header files for the shared library
set(SHARED_LIBRARY_HEADERS
    include/utilities/utility.h
)

# Specify the source files for the program
set(PROGRAM_SOURCES
    src/runMe.cpp
    src/missions/functions.cpp
    src/missions/mission1.cpp
)

# Specify the header files for the program
set(PROGRAM_HEADERS
    include/missions/missions.h
)

# Add the shared library target
add_library(mylibrary SHARED ${SHARED_LIBRARY_SOURCES} ${SHARED_LIBRARY_HEADERS})

# Set the output name of the shared library
set_target_properties(mylibrary PROPERTIES
    OUTPUT_NAME mylibrary
)

# Specify any additional include directories for the shared library
target_include_directories(mylibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add the program executable target
add_executable(runMe ${PROGRAM_SOURCES} ${PROGRAM_HEADERS})

# Specify any additional include directories for the program
target_include_directories(runMe PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link the program executable to the shared library
target_link_libraries(runMe PRIVATE mylibrary)

# Specify any additional libraries to link against
target_link_libraries(runMe
    # List any required libraries here
)

# Specify the installation destination for the program executable
install(TARGETS runMe
    RUNTIME DESTINATION bin
)

# Specify the installation destination for the shared library
install(TARGETS mylibrary
    LIBRARY DESTINATION lib
)












































#find_library(ZIPLIB zip)

#add custom lib
#add_subdirectory(my_lib)

# Add main.cpp file of project root directory as source file
#set(SOURCE_FILES RunMe.cpp)

#add all src files 
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
#file(GLOB SRC_FILES CONFIGURE_DEPENDS "./*.cpp")

# Add executable target with source files listed in SOURCE_FILES variable
#add_executable(runMe ${SOURCE_FILES} ${SRC_FILES})

#target_link_libraries(runMe PUBLIC my_lib)
#target_link_libraries(runMe PUBLIC ${ZIPLIB})
#target_link_libraries(runMe PUBLIC "/usr/local/lib/libzip.so")


#target_include_directories(runMe PUBLIC  
 #                          "${CMAKE_CURRENT_SOURCE_DIR}/include/"
   #                        "${CMAKE_CURRENT_SOURCE_DIR}/My_lib/include/"
   #                        "/usr/local/include/"
    #                       )