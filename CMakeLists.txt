cmake_minimum_required(VERSION 3.16) # 4.0 doesn't exist, use a realistic min
project(QuadCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define include and source dirs
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/QuadCalculator/includes)
set(SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/QuadCalculator/src)

# Executable sources (.cpp files only!)
set(SOURCES
        ${INCLUDE_DIR}/PPrintter.cpp
        ${SRC_DIR}/QuadCalculator.cpp
)

add_executable(QuadCalc ${SOURCES})

# Add includes for headers
target_include_directories(QuadCalc
        PRIVATE
        ${INCLUDE_DIR}
)

# Compiler warnings
if (MSVC)
    target_compile_options(QuadCalc PRIVATE /W4 /permissive-)
else()
    target_compile_options(QuadCalc PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: make IDEs show headers in project view
target_sources(QuadCalc PRIVATE
        ${INCLUDE_DIR}/ColorMod.h
        ${INCLUDE_DIR}/Complex.h
        ${INCLUDE_DIR}/PPrintter.h
)
