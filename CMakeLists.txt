cmake_minimum_required(VERSION 2.8.11)

project(CascLibPlus)

set(WITH_STATIC 1)

add_subdirectory(lib/CascLib)

if(${CMAKE_CXX_COMPILER_ID} MATCHES MSVC)
    # /W4       Warning level 4
    # /WX       Warnings as errors
    # /MP       Multi-process compilation
    # /sdl      Additional security checks
    add_compile_options(/W4 /WX /MP /sdl)

elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    # -Wall         Enable (almost) all warnings
    # -Wextra       Enable additional warnings
    # -Werror       Warnings as errors
    # -std=c++11    Use C++11 language features
    add_compile_options(-Wall -Wextra -Werror -std=c++11)

elseif(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    # -Wall         Enable (almost) all warnings
    # -Wextra       Enable additional warnings
    # -Werror       Warnings as errors
    # -std=c++11    Use C++11 language features
    add_compile_options(-Wall -Wextra -Werror -std=c++11)

endif()

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
    PUBLIC
        include
        lib/CascLib/src
)
