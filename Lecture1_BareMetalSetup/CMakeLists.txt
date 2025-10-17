# Lecture 1: The Bare Metal Setup - CMake and First Context
# Can be built independently or as part of the main project

cmake_minimum_required(VERSION 3.18)

# If built independently
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(Lecture1_BareMetalSetup LANGUAGES CXX)
    
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

# Collect source files
file(GLOB LECTURE1_CPP_SOURCES "src/*.cpp")
file(GLOB LECTURE1_CU_SOURCES "src/*.cu")
file(GLOB LECTURE1_HEADERS "src/*.h" "src/*.hpp" "src/*.cuh")

# Build executables from .cpp files
if(LECTURE1_CPP_SOURCES)
    foreach(source_file ${LECTURE1_CPP_SOURCES})
        get_filename_component(executable_name ${source_file} NAME_WE)
        add_executable(lecture1_${executable_name} ${source_file} ${LECTURE1_HEADERS})
        
        target_include_directories(lecture1_${executable_name} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/common/include
            ${CUDAToolkit_INCLUDE_DIRS}
        )
        
        target_link_libraries(lecture1_${executable_name} PRIVATE
            CUDA::cuda_driver
        )
        
        # Link common library if building as part of main project
        if(TARGET common)
            target_link_libraries(lecture1_${executable_name} PRIVATE common)
        endif()
        
        set_target_properties(lecture1_${executable_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lecture1
        )
    endforeach()
endif()

# Compile .cu files to PTX for loading at runtime
if(LECTURE1_CU_SOURCES)
    foreach(cu_file ${LECTURE1_CU_SOURCES})
        get_filename_component(cu_name ${cu_file} NAME_WE)
        set(ptx_file ${CMAKE_BINARY_DIR}/bin/lecture1/Release/${cu_name}.ptx)
        
        add_custom_command(
            OUTPUT ${ptx_file}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/lecture1/Release
            COMMAND ${CUDAToolkit_NVCC_EXECUTABLE}
                --ptx
                -arch=sm_75
                -o ${ptx_file}
                ${cu_file}
            DEPENDS ${cu_file}
            COMMENT "Compiling ${cu_name}.cu to PTX"
        )
        
        add_custom_target(lecture1_${cu_name}_ptx ALL DEPENDS ${ptx_file})
    endforeach()
endif()
