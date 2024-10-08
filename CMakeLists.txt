# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.24)
project(project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(project1 main.cpp
        Gate.cpp
        Gate.h
        pch.h
        Sensor.cpp
        Sensor.h
        Item.cpp
        Item.h)
# Find wxWidgets package
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)


# Include wxWidgets macros for setting up your project
include(${wxWidgets_USE_FILE})
target_link_libraries(project1 ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
