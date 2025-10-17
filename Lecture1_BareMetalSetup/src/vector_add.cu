#include <cuda.h>

extern "C" __global__ void add(float *a, float *b, float *c) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    c[idx] = a[idx] + b[idx];
}