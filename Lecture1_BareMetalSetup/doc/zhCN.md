# CUDA's Enviroment and Programming Model
## The Enviroment
要成功编译运行我们的第一个CUDA程序，你需要安装[CUDA Toolkit](https://developer.nvidia.com/cuda-12-4-0-download-archive)。这是Nvidia提供的基本开发工具，包含了一个.cu脚本的编译器、常用的CUDA计算库和一些好用的性能分析小玩意<sup>[1]</sup>。你需要先在本地安装它，并将`./CUDAToolkit/bin`和`./CUDAToolkit/libnvvp`加入到环境变量的Path变量中。

## The Programming Model

--- 
[1] : 这些小玩意非常有用，在很多时候都能为你的程序调优提供直觉。不过在这一个Lecture，我们主要还是使用我在./common/include/cuda_utils.h中提供的CHECK_CUDA来做基本的debug，因为它更方便，且现在的程序复杂度还不高。