cmake_minimum_required(VERSION 3.18)
project(learnGPU LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable CUDA
enable_language(CUDA)

# Find CUDA
find_package(CUDAToolkit 12.4 REQUIRED)
if(CUDAToolkit_FOUND)
    message(STATUS "CUDA version: ${CUDAToolkit_VERSION}")
    message(STATUS "CUDA include dirs: ${CUDAToolkit_INCLUDE_DIRS}")
    message(STATUS "CUDA libraries: ${CUDAToolkit_LIBRARY_DIR}")
endif()

# Set CUDA architecture (adjust based on your GPU)
# Common values: 60, 61, 70, 75, 80, 86, 89, 90
set(CMAKE_CUDA_ARCHITECTURES 75)

# Set CUDA standard
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Global include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/common/include
    ${CUDAToolkit_INCLUDE_DIRS}
)

# Add common library
add_subdirectory(common)

# Add each lecture subdirectory
add_subdirectory(Lecture0_Philosophy)
add_subdirectory(Lecture1_BareMetalSetup)
add_subdirectory(Lecture2_Memory)
add_subdirectory(Lecture3_Kernel)
add_subdirectory(Lecture4_Abstractions)
add_subdirectory(Lecture5_Streams)
add_subdirectory(Lecture6_Warp)
add_subdirectory(Lecture7_SharedMemory)
add_subdirectory(Lecture8_WaveOpticsRenderer)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
