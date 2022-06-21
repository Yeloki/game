project(engine)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SRC src/engine/map.hpp)
set(SRC ${SRC})

add_executable(engine src/main.cpp ${SRC})

target_link_libraries(engine sfml-graphics sfml-audio)