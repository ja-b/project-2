
add_executable(nbody_serial nbody_cpu_serial.c)
add_executable(nbody_multicore nbody_cpu_multicore.c)

if (CMAKE_CUDA_COMPILER)
    add_executable(nbody_gpu1 nbody_gpu1.cu)
    add_executable(nbody_gpu2 nbody_gpu2.cu)
    add_executable(nbody_gpu3 nbody_gpu3.cu)
    add_executable(nbody_gpu4 nbody_gpu4.cu)
    target_link_libraries(nbody_gpu1 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu2 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu3 PUBLIC helper_cuda)
    target_link_libraries(nbody_gpu4 PUBLIC helper_cuda)
endif()
