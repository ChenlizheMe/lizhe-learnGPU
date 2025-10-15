# The Philosophy of Talking to the GPU

[English Version / 英文版](enUS.md)

## 关于
在一家具身智能公司实习的时候，我的Mentor交给我了一项任务，即通过CUDA实现公司自研仿真引擎的高性能计算模块，那是我第一次真正意义上地接触到GPU编程（之前更多是通过Shader或Taichi）。那时候我发现并行计算领域和传统基于CPU编程思路之间存在巨大的差异，这也给我的学习带来了很大的困难。基于此，我做了这份教程，一方面帮助我自己更好地梳理有关GPU的那些事，另一方面也帮助同样正在入门这个领域的GPU Coder们。

结合我自己的兴趣爱好，这个教程会在最后实现一个基于波动光学的光线追踪渲染器（相比Ray-Tracing方法，可以把光以光波的形式进行表达和传输），这会要求你对图形学有基本的直觉。希望这份教程可以帮到你。

项目采用C++17和CUDA Toolkit 12.1+，使用CMake管理。如果你不熟悉CMake，可以直接双击项目根目录的`run.bat`自动配置并编译整个项目。项目主要在Windows上测试，Linux用户可参考`run.bat`编写对应shell脚本，并修改CMake文件。同时，这个教程主要采用Driver API而非Runtime API，因为它更底层，且理解了Driver API后一定能在不付出更多努力的情况下完全掌握Runtime API。

> 这份笔记主要是在我研究生生涯中无聊的英语课与论文写作课之类的课程上完成的，因此难免存在一些疏漏，Haha。同时，作为初学者之一，我也难免会遗漏或是搞错一些点，不过我会尽力确保减少它们的数量。如果有任何问题，欢迎提issue！

## GPU与并行计算
人们制造GPU的唯一目的，就是为了同时进行一系列重复的计算<sup>[1]</sup>。例如，将一张图片的颜色反转（需要对每个像素进行单独的计算），或者做矩阵运算。基于这个目的，英伟达和AMD等等GPU制造商往往会把更多的晶体管用于计算，而非缓存。引用《CUDA C++ Programming Guide》的一张图：

![Difference between CPU and GPU](https://docs.nvidia.com/cuda/cuda-c-programming-guide/_images/gpu-devotes-more-transistors-to-data-processing.png)

在CPU上，每个内核都有自己的缓存和控制块；而在GPU上，大量的内核会共享同一份控制器和缓存，它们的线程往往也以线程束<sup>[2]</sup>的方式被统一管理起来。这种情况在Volta架构被发明出来后发生了一些变化，我们之后会聊到<sup>[3]</sup>。

这种特性引出了在GPU上编程的基本原则：只把高度并行的计算放到GPU上，而高度串行的计算则应放在CPU上。举个简单的例子，将PNG格式图像转为JPG格式的任务，从直觉上来看，应该是一个适应于GPU的任务。但是在实际上，人们更倾向于用CPU来实现这个任务，因为这个算法里包含大量的if分支<sup>[4]</sup>和顺序执行条件，在GPU上实现该算法不能带来任何收益。

因此，另一个需要了解到的基本事实是，GPU is NOT all you need. 一个程序通常既有并行部分又有串行部分，因此最佳的方式是混合使用GPU和CPU来最大化总体性能。我们在之后的各种项目中，将会非常频繁地聊到，怎么样交替使用CPU与GPU，以此掩盖GPU的内存延迟，并同时满足程序的串行和并行需求。

## 有关CUDA
所有的GPU都需要通过一些接口API来调用，CUDA和AMD的ROCm就是这样的API。这些API一般通过两方面组成，一是CPU上的控制代码，这类似于在图形API（OpenGL、DirectX和Vulkan等）中写的一般脚本；另一方面则是GPU计算代码，在CUDA应用程序里一般是一系列以.cu为后缀的脚本文件（包括.ptx和.cubin，它们实际上是一回事！），在图形API里这些东西则被称为shader。

在Lecture0_Philosophy/src，我们有一个最简单的CUDA程序示例，和一个简单的A+B算子。<sup>[5]</sup>对于有图形API基础的读者来说，可以很轻易地发现这种代码的组织形式与图形API的相似性，因为CUDA的早期形式就是参考图形API构造出来的。

好了，这就是你目前需要了解的一切。接下来做好准备，我们要正式开始学习CUDA了。在下一章，我们会先简单讨论一下CUDA的环境和编程模型。

---

[1] NVIDIA. [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html).

[2] 在Nvidia GPU中，线程束一般被称为warp；而在AMD GPU中它们则叫做wave。

[3] 在Nvidia的工程师们捣鼓出Volta架构后这一切都不一样了，我们之后会聊到。

[4] 不是所有的if分支都会大幅度增加GPU的开销，我们之后会讨论这个。

[5] 如果你编译失败了，我们在第二章介绍了基本的CUDA环境搭建，你可以先看看它。

