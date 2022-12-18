cmake_minimum_required (VERSION 3.20)
project("Benchmarks")

set (CMAKE_CXX_STANDARD 20)

add_subdirectory("generators")
add_subdirectory("headers")

add_compile_options(/permissive /openmp:llvm  /Qpar- /GL /W3 /Gy /Zc:wchar /Zi /Gm- /O2 /Ob2 /sdl /arch:AVX2 /nologo)
add_executable(NaturalNumbers NaturalNumbers.cpp)
add_executable(IntegerNumbers IntegerNumbers.cpp)
add_executable(LinearAlgebra LinearAlgebra.cpp)
