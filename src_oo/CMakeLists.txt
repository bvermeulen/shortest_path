cmake_minimum_required(VERSION 3.12)

project(shortest_path_oo)
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
    ../include_oo
    /home/bvermeulen/Python/cpp/matplotlibcpp17/include
    /home/bvermeulen/Python/cpp/pybind11/include
)

add_executable(shortest_path_oo ${sources} ${includes})
target_include_directories(shortest_path_oo PUBLIC ${Python3_INCLUDE_DIRS})

target_link_libraries(shortest_path_oo ${Python3_LIBRARIES})

set_target_properties(shortest_path_oo PROPERTIES LDFLAGS "-Wall")
set_target_properties(shortest_path_oo PROPERTIES COMPILE_FLAGS "-Wall -g -fvisibility=hidden")
