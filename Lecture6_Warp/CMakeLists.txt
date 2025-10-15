# Lecture 6: The Warp - Unveiling the True Execution Unit
# Can be built independently or as part of the main project

cmake_minimum_required(VERSION 3.18)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(Lecture6_Warp LANGUAGES CXX)
    
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    enable_language(CUDA)
    set(CMAKE_CUDA_STANDARD 17)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    set(CMAKE_CUDA_ARCHITECTURES 75)
    
    find_package(CUDAToolkit 12.1 REQUIRED)
    
    set(COMMON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
    if(EXISTS ${COMMON_INCLUDE_DIR})
        include_directories(${COMMON_INCLUDE_DIR})
    endif()
endif()

file(GLOB LECTURE6_SOURCES "src/*.cpp" "src/*.cu")
file(GLOB LECTURE6_HEADERS "src/*.h" "src/*.hpp" "src/*.cuh")

if(LECTURE6_SOURCES)
    foreach(source_file ${LECTURE6_SOURCES})
        get_filename_component(executable_name ${source_file} NAME_WE)
        add_executable(lecture6_${executable_name} ${source_file} ${LECTURE6_HEADERS})
        
        target_include_directories(lecture6_${executable_name} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CUDAToolkit_INCLUDE_DIRS}
        )
        
        target_link_libraries(lecture6_${executable_name} PRIVATE
            CUDA::cuda_driver
        )
        
        if(TARGET common)
            target_link_libraries(lecture6_${executable_name} PRIVATE common)
        endif()
        
        set_target_properties(lecture6_${executable_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lecture6
            CUDA_SEPARABLE_COMPILATION ON
        )
    endforeach()
endif()
