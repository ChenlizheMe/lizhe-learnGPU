# Lecture 8: Putting It All Together - A Wave Optics Renderer
# Can be built independently or as part of the main project

cmake_minimum_required(VERSION 3.18)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(Lecture8_WaveOpticsRenderer LANGUAGES CXX)
    
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    enable_language(CUDA)
    set(CMAKE_CUDA_STANDARD 17)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    set(CMAKE_CUDA_ARCHITECTURES 75)
    
    find_package(CUDAToolkit 12.4 REQUIRED)
    
    set(COMMON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
    if(EXISTS ${COMMON_INCLUDE_DIR})
        include_directories(${COMMON_INCLUDE_DIR})
    endif()
endif()

file(GLOB LECTURE8_SOURCES "src/*.cpp" "src/*.cu")
file(GLOB LECTURE8_HEADERS "src/*.h" "src/*.hpp" "src/*.cuh")

if(LECTURE8_SOURCES)
    foreach(source_file ${LECTURE8_SOURCES})
        get_filename_component(executable_name ${source_file} NAME_WE)
        add_executable(lecture8_${executable_name} ${source_file} ${LECTURE8_HEADERS})
        
        target_include_directories(lecture8_${executable_name} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CUDAToolkit_INCLUDE_DIRS}
        )
        
        target_link_libraries(lecture8_${executable_name} PRIVATE
            CUDA::cuda_driver
        )
        
        if(TARGET common)
            target_link_libraries(lecture8_${executable_name} PRIVATE common)
        endif()
        
        set_target_properties(lecture8_${executable_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lecture8
            CUDA_SEPARABLE_COMPILATION ON
        )
    endforeach()
endif()
