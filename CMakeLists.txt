# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.24)
project(project1)

set(PROJECT_NAME project1)
set(APPLICATION_LIBRARY project1Lib)

set(CMAKE_CXX_STANDARD 17)

# import resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/levels DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



set(SOURCE_FILES main.cpp
        pch.h
        SpartyAPP.cpp
        SpartyAPP.h
)

# Find wxWidgets package
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)