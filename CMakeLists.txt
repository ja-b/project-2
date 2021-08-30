cmake_minimum_required(VERSION 3.11)
project(advanced_ca_projec2 C CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(PAPI)
find_package(OpenMP)

set(CMAKE_C_FLAGS_DEBUG "-std=c99 -D_BSD_SOURCE -O0 -DOMP -DPAPI")
set(CMAKE_C_FLAGS_RELEASE "-std=c99 -D_BSD_SOURCE -O2 -DOMP -DPAPI")

include(CheckLanguage)
check_language(CUDA)
if (CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
endif ()

# CUDA Helpers
if (CMAKE_CUDA_COMPILER)
    add_library(helper_cuda INTERFACE)
    target_include_directories(helper_cuda INTERFACE helper_cuda/)
endif ()

# Adds forced vectorization (and report) for ICC
if (CMAKE_C_COMPILER_ID STREQUAL Intel)
    add_compile_options(-xAVX -qopt-report-stdout)
endif ()

add_subdirectory(gpu_examples)
add_subdirectory(src)
