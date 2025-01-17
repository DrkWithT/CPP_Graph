cmake_minimum_required(VERSION 3.28)

project(CPPGraph VERSION 0.0.1 LANGUAGES CXX)

set(CPPG_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (DEBUG_BUILD)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -Og)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O3)
endif ()

enable_testing()
add_subdirectory(tests)
