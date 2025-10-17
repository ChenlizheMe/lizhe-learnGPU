#include <cuda.h>
#include <cuda_utils.h>

template<typename T>
class CudaVector
{
    public:
        CudaVector(size_t numElements)
        {
            this->numElements = numElements;
            hostData = malloc(numElements * sizeof(T));
            CHECK_CUDA(cuMemAlloc(&deviceData, numElements * sizeof(T)));
        }
        ~CudaVector(){
            free(hostData);
            CHECK_CUDA(cuMemFree(deviceData));
        }

        // [] operator for easy access, we can use vec[i] to access elements
        T& operator[](size_t index)
        {
            return static_cast<T*>(hostData)[index];
        }
        T& operator[](size_t index) const
        {
            return static_cast<T*>(hostData)[index];
        }
        
        /// @brief Copy data from host to device
        void SyncToDevice()
        {
            CHECK_CUDA(cuMemcpyHtoD(deviceData, hostData, numElements * sizeof(T)));
        }

        /// @brief Copy data from device to host
        void SyncToHost()
        {
            CHECK_CUDA(cuMemcpyDtoH(hostData, deviceData, numElements * sizeof(T)));
        }
        
        /// @brief  Get device data pointer
        /// @return Device data pointer
        CUdeviceptr GetDevicePointer() const
        {
            return deviceData;
        }

        /// @brief Get the size of the vector
        /// @return Size of the vector
        size_t Size() const
        {
            return numElements;
        }

    private:
        size_t numElements;
        void* hostData;
        CUdeviceptr deviceData;
};

int main() {
    // Initialize the CUDA driver API
    CHECK_CUDA(cuInit(0));

    CUdevice device;
    // Get the first CUDA device
    CHECK_CUDA(cuDeviceGet(&device, 0));

    CUcontext context;
    CHECK_CUDA(cuCtxCreate(&context, 0, device));

    // Create a CudaVector
    CudaVector<float> vec1(3);
    vec1[0] = 1.0f;
    vec1[1] = 2.0f;
    vec1[2] = 3.0f;

    CudaVector<float> vec2(3);
    vec2[0] = 4.0f;
    vec2[1] = 5.0f;
    vec2[2] = 6.0f;

    CudaVector<float> vec3(3);

    // Sync data to device
    vec1.SyncToDevice();
    vec2.SyncToDevice();

    // Load the CUDA module
    CUmodule module;
    CHECK_CUDA(cuModuleLoad(&module, getExeDirectoryFile("vector_add.ptx").c_str()));

    // Get the kernel function
    CUfunction kernel;
    CHECK_CUDA(cuModuleGetFunction(&kernel, module, "add"));

    // Launch the kernel
    CUdeviceptr d_vec1 = vec1.GetDevicePointer();
    CUdeviceptr d_vec2 = vec2.GetDevicePointer();
    CUdeviceptr d_vec3 = vec3.GetDevicePointer();
    void* args[] = { &d_vec1, &d_vec2, &d_vec3 };
    CHECK_CUDA(cuLaunchKernel(kernel, 1, 1, 1, 3, 1, 1, 0, nullptr, args, nullptr));

    // Sync result back to host
    vec3.SyncToHost();
    for(size_t i = 0; i < vec3.Size(); i++) {
        printf("%.2f + %.2f = %.2f\n", vec1[i], vec2[i], vec3[i]);
    }

    // Note: vec1, vec2, vec3 destructors will be called before cuCtxDestroy
    // This is intentional to ensure proper cleanup order
    return 0;
}