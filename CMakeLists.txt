cmake_minimum_required(VERSION 3.20)
project(jsonpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to enable coverage.
#option(CODE_COVERAGE "Enable coverage reporting" ON)
#if(CODE_COVERAGE)
#    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#        message(STATUS "Code coverage enabled")
#        add_compile_options(--coverage -O0 -fprofile-arcs -ftest-coverage)
#        add_link_options(--coverage)
#    endif()
#endif()

#enable_testing()

add_subdirectory(src)
#add_subdirectory(tests)

