cmake_minimum_required(VERSION 3.27)
project(MidProjectMugnaiLorenzo)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenMP REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(MidProjectMugnaiLorenzo main.cpp
        SoA/ParallelSoA.cpp
        SoA/ParallelSoA.h
        SoA/SequentialSoA.cpp
        SoA/SequentialSoA.h
        AoS/ParallelAoS.cpp
        AoS/ParallelAoS.h
        AoS/SequentialAoS.cpp
        AoS/SequentialAoS.h
        AoS/Ngram.cpp
        AoS/Ngram.h
        include/gnuplot.h
        include/Benchmark.cpp
        include/Benchmark.h
)
target_link_libraries(MidProjectMugnaiLorenzo OpenMP::OpenMP_CXX)
