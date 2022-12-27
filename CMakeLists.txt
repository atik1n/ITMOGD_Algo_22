cmake_minimum_required(VERSION 3.19)
project(AlgoLabs)
set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 src/sumer-game.cpp src/sumer-game.hpp)

include_directories(src)
add_subdirectory(src)

add_subdirectory(google_tests)