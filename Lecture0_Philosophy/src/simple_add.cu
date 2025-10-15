#include <cuda.h>

extern "C" __global__ void add(int *a, int *b, int *c) {
    c[0] = a[0] + b[0];
}