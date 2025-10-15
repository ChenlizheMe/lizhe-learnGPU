# Common library for shared utilities
file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp" "src/*.cu")
file(GLOB_RECURSE COMMON_HEADERS "include/*.h" "include/*.hpp" "include/*.cuh")

if(COMMON_SOURCES)
    add_library(common STATIC ${COMMON_SOURCES} ${COMMON_HEADERS})
    
    target_include_directories(common PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CUDAToolkit_INCLUDE_DIRS}
    )
    
    target_link_libraries(common PUBLIC
        CUDA::cuda_driver
    )
    
    set_target_properties(common PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
    )
else()
    # Create an interface library if no source files exist yet
    add_library(common INTERFACE)
    target_include_directories(common INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CUDAToolkit_INCLUDE_DIRS}
    )
    target_link_libraries(common INTERFACE
        CUDA::cuda_driver
    )
endif()
