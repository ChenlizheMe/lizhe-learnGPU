# The Philosophy of Talking to the GPU
## 关于
在一家具身智能公司实习的时候，我的Mentor交给我了一项任务，即通过CUDA实现公司自研仿真引擎的高性能计算模块，那是我第一次真正意义上地接触到GPU编程（之前更多是通过Shader或Taichi）。那时候我发现并行计算领域和传统基于CPU编程思路之间存在巨大的差异，这也给我的学习带来了很大的困难。基于此，我做了这份教程，一方面帮助我自己更好地梳理有关GPU的那些事，另一方面也帮助同样正在入门这个领域的GPU Coder们。

结合我自己的兴趣爱好，这个教程会在最后实现一个基于波动光学的光线追踪渲染器（相比Ray-Tracing方法，可以把光以光波的形式进行表达和传输），这会要求你对图形学有基本的直觉。希望这份教程可以帮到你。

我会使用C++17的一些特征来组织项目的一些生命周期。如果你采用C++14或11也是可以的，只是有一些特性需要你通过更传统的方式来实现。

注意，这个教程在CUDA API的选择上，主要采用Driver API而非Runtime API，因为他更底层，且理解了Driver API后一定能在不付出更多努力的情况下完全掌握Runtime API。

> 这份笔记主要是在我研究生生涯中无聊的英语课与论文写作课之类的课程上完成的，因此难免存在一些疏漏，Haha。同时，作为初学者之一，我也难免会遗漏或是搞错一些点，不过我会尽力确保减少它们的数量。如果有任何问题，欢迎提issue！
## GPU与并行计算
人们制造GPU的唯一目的，就是为了同时进行一系列重复的计算<sup>[1]</sup>。例如，将一张图片的颜色反转（需要对每个像素进行单独的计算），或者做矩阵运算。基于这个目的，英伟达和AMD等等GPU制造商往往会把更多的晶体管用于计算，而非缓存。引用《CUDA C++ Programming Guide》的一张图：

![Difference between CPU and GPU](https://docs.nvidia.com/cuda/cuda-c-programming-guide/_images/gpu-devotes-more-transistors-to-data-processing.png)

在CPU上，每个内核都有自己的缓存和控制块；而在GPU上，大量的内核会共享同一份控制器和缓存，它们的线程往往也以线程束<sup>[2]</sup>的方式被统一管理起来。这种情况在Volta架构被发明出来后发生了一些变化，我们之后会聊到<sup>[3]</sup>。

这种特性引出了在GPU上编程的基本原则：只把高度并行的计算放到GPU上，而高度串行的计算则应放在CPU上。举个简单的例子，将PNG格式图像转为JPG格式的任务，从

---

[1] NVIDIA. [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html).

[2] 在Nvidia GPU中，线程束一般被称为warp；而在AMD GPU中它们则叫做wave。

[3] 在Nvidia的工程师们捣鼓出Volta架构后这一切都不一样了，我们之后会聊到。
