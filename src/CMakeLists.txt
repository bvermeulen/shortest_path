cmake_minimum_required(VERSION 3.12)

project(shortest_path_array)
enable_language(C CXX)

set(sources
    args_handle.cpp
    csv.cpp
    plotpaths.cpp
    point.cpp
    shortest_path_tsp.cpp
)

find_package(Python3 COMPONENTS Interpreter Development)

include_directories(
    includes
    ../include
    c:/data/cpp/matplotlibcpp17/include
    c:/data/cpp/pybind11/include
)

add_executable(shortest_path_array ${sources} ${includes})
target_include_directories(shortest_path_array PUBLIC ${Python3_INCLUDE_DIRS})

target_link_libraries(shortest_path_array ${Python3_LIBRARIES})

set_target_properties(shortest_path_array PROPERTIES LDFLAGS "-Wall")
set_target_properties(shortest_path_array PROPERTIES COMPILE_FLAGS "-Wall -g -fvisibility=hidden")
