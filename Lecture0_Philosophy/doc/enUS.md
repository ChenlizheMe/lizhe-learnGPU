# The Philosophy of Talking to the GPU

[中文版 / Chinese Version](zhCN.md)

## About
During my internship at an embodied AI company, my mentor assigned me a task to implement high-performance computing modules for the company's self-developed simulation engine using CUDA. That was my first real encounter with GPU programming (previously I'd only worked with Shaders or Taichi). I discovered a huge gap between parallel computing and traditional CPU-based programming approaches, which made learning quite challenging. Based on this experience, I created this tutorial to help myself better organize GPU-related knowledge and to assist fellow GPU coders who are also entering this field.

Combined with my personal interests, this tutorial will ultimately implement a wave optics-based ray tracing renderer (compared to traditional ray-tracing methods, it can express and propagate light as waves), which requires basic intuition about computer graphics. I hope this tutorial helps you.

The project uses C++17 and CUDA Toolkit 12.1+, managed with CMake. If you're not familiar with CMake, you can simply double-click `run.bat` in the project root directory to automatically configure and compile the entire project. The project is primarily tested on Windows; Linux users can refer to `run.bat` to write corresponding shell scripts and modify CMake files. Additionally, this tutorial mainly uses the Driver API rather than the Runtime API, because it's more low-level, and understanding the Driver API will definitely help you fully master the Runtime API without extra effort.

> This note was mainly completed during boring English and thesis writing classes in my graduate studies, so there may inevitably be some omissions, haha. Also, as a beginner myself, I may miss or misunderstand some points, but I'll try my best to minimize them. If you have any questions, feel free to open an issue!

## GPU and Parallel Computing
The sole purpose of manufacturing GPUs is to perform a series of repetitive calculations simultaneously<sup>[1]</sup>. For example, inverting the colors of an image (requiring individual calculations for each pixel), or performing matrix operations. Based on this purpose, GPU manufacturers like NVIDIA and AMD typically dedicate more transistors to computation rather than caching. Quoting a diagram from the *CUDA C++ Programming Guide*:

![Difference between CPU and GPU](https://docs.nvidia.com/cuda/cuda-c-programming-guide/_images/gpu-devotes-more-transistors-to-data-processing.png)

On CPUs, each core has its own cache and control unit; on GPUs, a large number of cores share the same controller and cache, and their threads are typically managed uniformly in thread bundles<sup>[2]</sup>. This situation changed somewhat after the Volta architecture was invented, which we'll discuss later<sup>[3]</sup>.

This characteristic leads to the basic principle of GPU programming: only put highly parallel computations on the GPU, while highly serial computations should stay on the CPU. For a simple example, converting PNG images to JPG format intuitively seems like a task suitable for GPUs. However, in practice, people prefer to implement this task on CPUs because the algorithm contains many if branches<sup>[4]</sup> and sequential execution conditions, and implementing it on GPUs brings no benefits.

Therefore, another basic fact to understand is: GPU is NOT all you need. A program typically has both parallel and serial parts, so the best approach is to use GPUs and CPUs in combination to maximize overall performance. In subsequent projects, we'll frequently discuss how to alternate between CPU and GPU usage to mask GPU memory latency while satisfying both serial and parallel requirements of the program.

## About CUDA
All GPUs need to be called through interface APIs, and CUDA and AMD's ROCm are such APIs. These APIs generally consist of two parts: first, control code on the CPU, similar to regular scripts written in graphics APIs (OpenGL, DirectX, Vulkan, etc.); second, GPU compute code, which in CUDA applications is typically a series of script files with .cu extensions (including .ptx and .cubin, which are essentially the same thing!), while in graphics APIs these are called shaders.

In Lecture0_Philosophy/src, we have a very simple CUDA program example and a simple A+B operator.<sup>[5]</sup> For readers with a graphics API background, you can easily notice the similarity between this code organization and graphics APIs, because CUDA's early form was constructed by referencing graphics APIs.

Well, that's everything you need to know for now. Get ready, we're about to officially start learning CUDA. In the next chapter, we'll briefly discuss CUDA's environment and programming model.

---

[1] NVIDIA. [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html).

[2] In NVIDIA GPUs, thread bundles are generally called warps; in AMD GPUs they're called waves.

[3] After NVIDIA engineers came up with the Volta architecture, everything changed, which we'll discuss later.

[4] Not all if branches significantly increase GPU overhead; we'll discuss this later.

[5] If your compilation fails, we introduce basic CUDA environment setup in Chapter 2, which you can check out first.
