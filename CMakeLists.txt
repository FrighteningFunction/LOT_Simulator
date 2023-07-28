cmake_minimum_required(VERSION 3.23)
project(LOT)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to Google Test directory
set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest)

# Add Google Test's CMakeLists.txt
add_subdirectory(${GTEST_DIR})

# Add your application's executable
add_executable(LOT
        Errors.cpp
        Errors.h
        LOT.cpp
        LOT.h
        Control.cpp
        Control.h
        LOT_Simulator.cpp)

# Add your test executable
add_executable(runTests
        tests.cpp
        Errors.cpp
        Errors.h
        LOT.cpp
        LOT.h
        Control.cpp
        Control.h
        )

# Link your test executable with Google Test libraries
target_link_libraries(runTests gtest gtest_main)