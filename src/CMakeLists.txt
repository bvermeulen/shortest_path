cmake_minimum_required(VERSION 3.12)

project(shortest_path)
enable_language(C CXX)

set(sources
    csv.cpp
    plotpaths.cpp
    point.cpp
    shortest_path_tsp.cpp
)

find_package(Python3 COMPONENTS Interpreter Development)

include_directories(
    includes
    ../include
    d:/cpp/matplotlibcpp17/include
    d:/cpp/pybind11/include
)

add_executable(shortest_path ${sources} ${includes})
target_include_directories(shortest_path PUBLIC ${Python3_INCLUDE_DIRS})

target_link_libraries(shortest_path ${Python3_LIBRARIES})

set_target_properties(shortest_path PROPERTIES LDFLAGS "-Wall")
set_target_properties(shortest_path PROPERTIES COMPILE_FLAGS "-Wall -g")
