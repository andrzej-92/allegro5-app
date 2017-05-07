cmake_minimum_required(VERSION 3.6)
project(allegro_hello_world)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(allegro_hello_world ${SOURCE_FILES})

file(GLOB LIBRARIES "/usr/local/lib/liballegro*.so")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(allegro_hello_world  ${LIBRARIES})