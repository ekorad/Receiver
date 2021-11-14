cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Receiver VERSION 1.0)

# add the Logging library
add_subdirectory(libs/Logging)

include_directories(include)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES src/*.cpp)

# add the executable
add_executable(Receiver ${SOURCES})

configure_file(ReceiverConfig.h.in ReceiverConfig.h)

# add binary tree to search path for ReceiverConfig.h
# add the Logging tree to search path for the headers
target_include_directories(Receiver PUBLIC
    "${PROJECT_BINARY_DIR}")

target_link_libraries(Receiver PUBLIC Logging)

install(TARGETS Receiver DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ReceiverConfig.h"
    DESTINATION include)