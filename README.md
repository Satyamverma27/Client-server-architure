# Client-Server Architecture using IPC Techniques

## Description
This project demonstrates a client-server architecture implemented using various Inter-Process Communication (IPC) techniques such as pipes, shared memory, and message queues. The server processes mathematical expressions sent by the client and returns the results.

## Installation
Follow these steps to set up the project on your local machine.

### Prerequisites
- GCC compiler
- Python3 (for evaluating expressions)
- Linux environment (preferably)
### Execution Time Measurement Guide for Client-Server Architecture (C++ on Linux)
This guide covers quick and precise methods to measure the execution time of any client-server architecture in C++ on Linux.

⚙️ 1. Compilation
Compile both client and server programs using g++:

g++ server.cpp -o server
g++ client.cpp -o client

⏱️ 2. Using the time Command (Simple & Quick)
Run the Server:
time ./server
Run the Client in Another Terminal:
time ./client

#### 🔍 Output Explanation:

-  real    0m0.456s  → Total elapsed (wall-clock) time
-  user    0m0.123s  → CPU time in user mode
-  sys     0m0.045s  → CPU time in kernel mode

### Clone the Repository
```sh
git clone https://github.com/Satyamverma27/client-server-ipc.git
cd client-server-ipc
```
### 🚀 Conclusion: IPC Methods Performance Analysis
### 📊 **Average Execution Time for IPC Methods (Simulated Results)**

| **IPC Method**               | **Average Execution Time**   |
|------------------------------|------------------------------|
| **Shared Memory (SHM)**       | ~20 µs (microseconds)        |
| **Message Queues**            | ~100 µs                      |
| **Pipes (Anonymous/FIFO)**    | ~150 µs                      |
| **Sockets (TCP/UDP)**         | ~250 µs (TCP), ~180 µs (UDP) |
Note: These values are estimates and may vary based on system architecture, implementation, and data size. For simple operations like 1 + 1, IPC overhead plays a significant role in the execution time.

### ✅ **Which IPC Method to Choose?**

| **Scenario**                        | **Recommended IPC Method**     |
|-------------------------------------|--------------------------------|
| High-speed, large data transfer     | Shared Memory                  |
| Reliable messaging (structured data)| Message Queues                 |
| Simple parent-child communication   | Pipes (Anonymous/FIFO)         |
| Remote process communication        | Sockets (TCP/UDP)              |
| Cross-platform networking           | Sockets                        |
| Low-latency, real-time processing   | Shared Memory with Semaphores  |




