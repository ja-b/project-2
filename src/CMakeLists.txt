

add_executable(nbody_serial nbody_cpu_serial.c timer.c)
add_executable(nbody_multicore nbody_cpu_multicore.c timer.c)

target_include_directories(nbody_serial PUBLIC ${PAPI_INCLUDE_DIRS})
target_include_directories(nbody_multicore PUBLIC ${PAPI_INCLUDE_DIRS})
target_link_libraries(nbody_multicore PUBLIC OpenMP::OpenMP_C)
target_link_libraries(nbody_serial PUBLIC ${PAPI_LIBRARIES})
target_link_libraries(nbody_serial PUBLIC m)
target_link_libraries(nbody_multicore PUBLIC ${PAPI_LIBRARIES})
target_link_libraries(nbody_multicore PUBLIC m)

if (CMAKE_CUDA_COMPILER)
    add_executable(nbody_gpu1 nbody_gpu1.cu timer.c)
    add_executable(nbody_gpu2 nbody_gpu2.cu timer.c)
    add_executable(nbody_gpu3 nbody_gpu3.cu timer.c)
    add_executable(nbody_gpu4 nbody_gpu4.cu timer.c)
    target_link_libraries(nbody_gpu1 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu2 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu3 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu4 PUBLIC helper_cuda)

    target_link_libraries(nbody_gpu1 PUBLIC OpenMP::OpenMP_C)
endif()
