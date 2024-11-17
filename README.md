# KernelFlow: Process and Memory Management Simulator

## Description
KernelFlow is a process forking and memory management simulator developed in C on Unix, designed to illustrate key concepts of operating systems. The project utilizes semaphores for concurrency control, focusing on efficient memory partitioning and CPU scheduling algorithms.

## Features
- **Process Management**: Simulates the creation and management of processes using fork.
- **Memory Management**: Implements fixed partitioning of memory, tracking allocation and deallocation.
- **Concurrency**: Uses semaphores to prevent race conditions and ensure safe access to shared resources.
- **Scheduling Algorithms**: Supports various CPU scheduling algorithms to enhance throughput and resource utilization.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/machine-moon/KernelFlow.git
   ```
2. Navigate to the project directory:
   ```bash
   cd KernelFlow
   ```
3. Compile the code:
   ```bash
   make
   ```
## Usage
Run the simulator with:
   ```bash
   ./kernelflow input_data.txt
   ```

## Author
Tarek Ibrahim
