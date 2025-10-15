#ifndef CUDA_UTILS_H
#define CUDA_UTILS_H

#include <cuda.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>

// CUDA Driver API error checking macro
#define CHECK_CUDA(call) \
    do { \
        CUresult err = call; \
        if (err != CUDA_SUCCESS) { \
            const char* errStr; \
            cuGetErrorString(err, &errStr); \
            fprintf(stderr, "CUDA Error at %s:%d: %s\n", __FILE__, __LINE__, errStr); \
            exit(1); \
        } \
    } while(0)

// Get the path of the .exe file
inline std::string getExeDirectoryFile(const char* filename) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    
    std::string exeDir(exePath);
    size_t pos = exeDir.find_last_of("\\/");
    if (pos != std::string::npos) {
        exeDir = exeDir.substr(0, pos + 1);
    }
    
    return exeDir + filename;
}

#endif // CUDA_UTILS_H
