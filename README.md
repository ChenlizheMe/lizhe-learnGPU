# GPU Architecture Learning Project - CUDA Wave Optics Renderer

[中文](#中文) | [English](#english)

---

## English

### 📌 Project Overview

This is a personal learning project focused on GPU architecture and parallel computing, with an emphasis on CUDA programming using the **CUDA Driver API**. The primary goal is to progressively implement a **wave optics renderer** based on CUDA, exploring the principles of physically-based wave optics simulation and GPU acceleration techniques.

By using the low-level Driver API instead of the Runtime API, this project aims to gain deeper insights into GPU resource management, context handling, and fine-grained control over CUDA operations.

### 🎯 Learning Objectives

- Master CUDA Driver API programming and low-level GPU control
- Understand GPU architecture and parallel computing principles
- Learn explicit context management and resource allocation
- Implement wave optics algorithms (diffraction, interference, holography, etc.)
- Optimize GPU performance and memory management
- Build a practical rendering system from scratch

### 📚 Technologies

- **Language**: C++, CUDA (Driver API)
- **API Level**: CUDA Driver API (low-level) for fine-grained control
- **Libraries**: cuFFT, cuBLAS, OpenGL/Vulkan (for visualization)
- **Tools**: NVIDIA Nsight, CUDA Toolkit
- **Platform**: NVIDIA GPU (Compute Capability 6.0+)

### 🔧 Requirements

- NVIDIA GPU with CUDA support
- **CUDA Toolkit 12.4 or higher**
- CMake 3.18 or higher
- C++17 compatible compiler
- Windows

### 🏛️ Project Structure

This project is organized into a series of progressive "Lectures," each focusing on a core concept of CUDA programming with the Driver API. The structure is designed to build knowledge incrementally, culminating in a complete wave optics renderer.

-   `Lecture0_Philosophy/` - Philosophy of talking to the GPU.
-   `Lecture1_BareMetalSetup/` - CUDA's environment and programming model.
-   `Lecture2_Memory/` - GPU memory management.
-   `Lecture3_Kernel/` - From PTX to execution.
-   `Lecture4_Abstractions/` - Building our own `<<<...>>>`.
-   `Lecture5_Streams/` - Asynchrony and concurrency.
-   `Lecture6_Warp/` - The true execution unit.
-   `Lecture7_SharedMemory/` - The programmable cache.
-   `Lecture8_WaveOpticsRenderer/` - The final project.
-   `common/` - Shared utilities (error checking, helpers).

Each `LectureX` directory contains:
-   `src/`: Source code demonstrating the concepts of that lecture.
-   `doc/`: Detailed documentation and notes for the lecture.

### 📖 Resources

- [NVIDIA CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [GPU Gems Series](https://developer.nvidia.com/gpugems)
- Wave Optics: Goodman's "Introduction to Fourier Optics"

### 📝 Notes

This is an ongoing learning project. Code and documentation will be updated continuously. Contributions, suggestions, and discussions are welcome!

### 📄 License

This project is for educational purposes. Please refer to LICENSE file for details.

---

## 中文

### 📌 项目简介

这是一个专注于GPU体系架构和并行计算的个人学习项目，主要研究方向是使用**CUDA Driver API**进行底层编程。项目的核心目标是逐步实现一个基于CUDA的**波动光学渲染器**，探索物理真实的波动光学模拟原理和GPU加速技术。

通过使用底层的Driver API而非Runtime API，本项目旨在深入理解GPU资源管理、上下文处理以及对CUDA操作的细粒度控制。

### 🎯 学习目标

- 掌握CUDA Driver API编程和底层GPU控制
- 深入理解GPU架构和并行计算原理
- 学习显式的上下文管理和资源分配
- 实现波动光学算法（衍射、干涉、全息等）
- 优化GPU性能和内存管理
- 从零构建实用的渲染系统

### 📚 技术栈

- **编程语言**: C++, CUDA（Driver API）
- **API层级**: CUDA Driver API（底层）实现细粒度控制
- **依赖库**: cuFFT, cuBLAS, OpenGL/Vulkan（用于可视化）
- **开发工具**: NVIDIA Nsight, CUDA Toolkit
- **运行平台**: NVIDIA GPU（计算能力6.0+）

### 🔧 环境要求

- 支持CUDA的NVIDIA显卡
- CUDA Toolkit 12.4或更高版本
- CMake 3.18或更高版本
- 支持C++17的编译器
- Windows操作系统

### 🚀 快速开始

**Windows用户：**
直接运行项目根目录下的 `run.bat` 文件，即可自动配置CMake并编译整个项目。

可执行文件将位于 `build/bin/lectureX/Release/` 目录下。

### 🏛️ 项目架构

本项目被组织成一系列循序渐进的“讲座”（Lectures），每一讲都专注于使用Driver API进行CUDA编程的一个核心概念。这种结构旨在逐步累积知识，最终构建一个完整的波动光学渲染器。

-   `Lecture0_Philosophy/` - 与GPU对话的哲学。
-   `Lecture1_BareMetalSetup/` - CUDA的编程环境与第一个上下文。
-   `Lecture2_Memory/` - GPU的内存荒野。
-   `Lecture3_Kernel/` - 从PTX到执行。
-   `Lecture4_Abstractions/` - 构建我们自己的 `<<<...>>>`。
-   `Lecture5_Streams/` - 驾驭并发与异步。
-   `Lecture6_Warp/` - 揭示真正的执行单元。
-   `Lecture7_SharedMemory/` - 可编程缓存。
-   `Lecture8_WaveOpticsRenderer/` - 集大成者——波动光学渲染器。
-   `common/` - 共享工具（错误检查、辅助函数）。

每个 `LectureX` 目录包含：
-   `src/`: 用于演示该讲座概念的源代码。
-   `doc/`: 该讲座的详细文档和笔记。

### 📖 参考资料

- [NVIDIA CUDA编程指南](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [GPU Gems系列](https://developer.nvidia.com/gpugems)
- 波动光学：Goodman《傅里叶光学导论》

### 📝 说明

这是一个持续学习中的项目，代码和文档会不断更新完善。欢迎交流讨论和提出建议！

### 📄 许可证

本项目仅用于教育学习目的，具体许可信息请参见LICENSE文件。

---

### 👤 Author

Personal learning project by [Your Name]

### ⭐ Star History

If you find this project helpful for your learning, please consider giving it a star!
