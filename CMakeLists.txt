cmake_minimum_required(VERSION 3.13)

project(barren-land
    VERSION
        0.0.0
    LANGUAGES
        CXX
)

#include(GNUInstallDirs)

enable_testing()

add_subdirectory("src")
add_subdirectory("test")