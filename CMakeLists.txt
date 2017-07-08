cmake_minimum_required(VERSION 2.8.12)

project(CascLibPlus)

set(WITH_STATIC 1)

add_compile_options("/W4")

add_subdirectory(lib/CascLib)

add_library(CascLibPlus
    src/CascFile.cpp
    src/CascIterator.cpp
    src/CascStorage.cpp

    include/CascFile.hpp
    include/CascIterator.hpp
    include/CascLib.hpp
    include/CascStorage.hpp
)

target_link_libraries(CascLibPlus
    PRIVATE
        casc_static
)

target_include_directories(CascLibPlus
    PRIVATE
        lib/CascLib/src
    PUBLIC
        include
)
