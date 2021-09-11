cmake_minimum_required(VERSION 3.17)
project(creator)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(creator creator.cpp)
target_link_libraries(creator ${SDL2_LIBRARIES})
