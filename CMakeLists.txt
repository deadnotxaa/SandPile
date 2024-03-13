cmake_minimum_required(VERSION 3.12)

project(
        sand_pile_bmp
        VERSION 1.0
        DESCRIPTION "Abelian Sand Pile"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(bin)

