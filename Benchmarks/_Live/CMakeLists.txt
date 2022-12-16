cmake_minimum_required (VERSION 3.1)
project("Benchmarks")

add_subdirectory("generators")
add_subdirectory("headers")

add_executable(NumberSystems NumberSystems.cpp)