cmake_minimum_required(VERSION 3.8)
project(c17testing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -fsanitize=address -fno-omit-frame-pointer")
add_subdirectory(tests)
add_subdirectory(googletest)
