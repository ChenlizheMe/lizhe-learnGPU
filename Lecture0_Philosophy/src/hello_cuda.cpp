#include <cuda.h>
#include <cstdio>
#include "cuda_utils.h"

int main() {
    CHECK_CUDA(cuInit(0));
    
    CUdevice device;
    CHECK_CUDA(cuDeviceGet(&device, 0));
    
    CUcontext context;
    CHECK_CUDA(cuCtxCreate(&context, 0, device));
    
    // 编译CUDA模块
    CUmodule module;
    CHECK_CUDA(cuModuleLoad(&module, getExeDirectoryFile("simple_add.ptx").c_str()));
    
    CUfunction add;
    CHECK_CUDA(cuModuleGetFunction(&add, module, "add"));
    
    int a=3, b=4, c;
    CUdeviceptr d_a, d_b, d_c;
    
    CHECK_CUDA(cuMemAlloc(&d_a, sizeof(int)));
    CHECK_CUDA(cuMemAlloc(&d_b, sizeof(int)));
    CHECK_CUDA(cuMemAlloc(&d_c, sizeof(int)));
    
    CHECK_CUDA(cuMemcpyHtoD(d_a, &a, sizeof(int)));
    CHECK_CUDA(cuMemcpyHtoD(d_b, &b, sizeof(int)));
    
    void *args[] = {&d_a, &d_b, &d_c};
    CHECK_CUDA(cuLaunchKernel(add, 1,1,1, 1,1,1, 0,0, args, 0));
    
    CHECK_CUDA(cuMemcpyDtoH(&c, d_c, sizeof(int)));
    printf("%d + %d = %d\n", a, b, c);
    
    CHECK_CUDA(cuMemFree(d_a)); 
    CHECK_CUDA(cuMemFree(d_b)); 
    CHECK_CUDA(cuMemFree(d_c));
    CHECK_CUDA(cuCtxDestroy(context));
    return 0;
}