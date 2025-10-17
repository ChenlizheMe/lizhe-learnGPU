# CUDA's Enviroment and Programming Model
## The Enviroment
要成功编译运行我们的第一个CUDA程序，你需要安装[CUDA Toolkit](https://developer.nvidia.com/cuda-downloads)。这是Nvidia提供的基本开发工具，包含了一个.cu脚本的编译器（nvcc）、常用的CUDA计算库和一些好用的性能分析小玩意<sup>[1]</sup>。你需要先在本地安装它，并将`./CUDAToolkit/bin`和`./CUDAToolkit/libnvvp`加入到环境变量的Path变量中。

如果你熟悉CMake，那么你应该已经注意到项目根目录和每个Lecture目录下都有CMakeLists.txt文件。我们的项目使用CMake来管理编译流程，它会自动找到你安装的CUDA Toolkit，配置编译选项，并生成相应的构建文件。如果你不熟悉CMake也没关系，只需要在项目根目录下运行`run.bat`（Windows）或者手动执行`mkdir build && cd build && cmake .. && cmake --build . --config Release`即可完成编译。CMake会帮你处理好CUDA Driver API的链接、头文件包含路径以及PTX文件的生成等复杂的编译配置。

在`./build/bin/lecture0/Release`中，我们可以发现，除了编译出的可执行文件`lecture0_hello_cuda.exe`，还有一个文件`simple_add.ptx`。它是由`lecture0`源码中的`simple_add.cu`编译而成的CUDA内核模块，可以通过某种方式被加载进GPU内。CUDA内核可以被编译成多种中间格式和二进制格式，其中最常见的是.ptx, .cubin和.fatbin<sup>[2]</sup>。我们暂不深究这些格式的复杂性质，而只需要了解到一些基本常识：
- PTX是一种中间码，在进入GPU后会被二次翻译成机器码。这赋予了PTX良好的可移植性，而且便于调试。但相应的，由于需要二次翻译，在首次加载这些PTX算子的时候会具有较大的开销。

- CUBIN则是一种针对特定GPU架构编译的二进制机器码，它直接包含GPU可执行的指令，无需运行时编译，因此加载速度更快。但缺点是它只能在目标架构及其后续兼容架构上运行。换句话说，在GTX960显卡上编译的.cubin文件，很有可能在RTX5090上完全启动不了。因此，在大多数CUDA应用中，大家更常用的格式仍然是PTX。

- FATBIN是一个容器格式，可以同时包含多个架构的PTX和CUBIN代码。在运行时，驱动会选择最合适的版本加载。这是一种"鱼和熊掌兼得"的方案——既保证了兼容性，又在支持的架构上获得了最佳性能。

接下来让我们看看这一章的源代码，然后完成我们的第一个CUDA程序。

## The Programming Model
通过Driver API组织的CUDA程序的完整生命周期包括：
1. 驱动初始化。首先我们需要加载CUDA的驱动程序，初始化驱动内部的数据结构，然后准备与GPU通信的环境。
2. 获取设备句柄。在这里，我们会获取到系统中GPU设备的指针句柄。由于我们的设备中可能有多张GPU，我们需要在这里指定一张特定的GPU，并在后续计算时使用它。这一步也是实现多GPU并行程序的基础。
3. 创建并指定上下文（cuContext）。一个CUDA上下文记录了GPU的内存管理状态、模块和函数加载信息，以及一些执行配置。一个上下文是绑定在一个设备上的，所有GPU的操作都必须绑定在一个特定的上下文上而非设备本身身上。
4. 加载模块和函数。要导入一个编写并编译好的CUDA算子，就需要先将这个算子（cubin, ptx）以模块的方式加载进显存，随后通过字符串访问特定的算子内函数<sup>[3]</sup>。
5. 内存分配。随后，我们需要在显存上分配空间。这些显存空间可以理解为图形API中最原始的buffer。可以支持从CPU端进行的数据读写。
6. 数据传输。在申请完显存空间，我们就可以通过一些特定接口，将数据从CPU传输到GPU了。在计算结束后，我们也可以将数据从GPU传输到CPU，以获取计算结果。
7. 启动内核。在GPU获取到数据后，就可以启动CUDA内核进行计算了。在计算时，需要传递输入数据和输出数据的显存指针。CUDA会从输入指针中读取到数据，然后将结果暂存在输出指针中。

这就是一般CUDA程序的生命周期，不过我们接下来不会按照生命周期本身的顺序来讨论它，而是用一个更容易让人接受的方式。相关的代码在这个lecture的src文件夹中。

### 数据组织

--- 
[1] 这些小玩意非常有用，在很多时候都能为你的程序调优提供直觉。不过在这一个Lecture，我们主要还是使用我在`./common/include/cuda_utils.h`中提供的`CHECK_CUDA`宏来做基本的debug，因为它更方便，且现在的程序复杂度还不高。

[2] 其他GPU计算框架也有类似的中间表示格式，即使Nvidia自己的不同库可能也会使用不同的中间格式。例如，NVIDIA OptiX使用`.optixir`作为中间表示格式；AMD的ROCm使用LLVM IR；Vulkan计算着色器使用SPIR-V。

[3] 这也是为什么我们在lecture0/simple_add.cu的函数名前加上了`global`修饰符——否则其函数名可能会在编译过程中自动更改。不过另一方面，我们也可以通过是否存在`global`修饰符，判断一个函数是public的还是private的。