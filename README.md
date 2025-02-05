# Client-Server Architecture using IPC Techniques

## Description
This project demonstrates a client-server architecture implemented using various Inter-Process Communication (IPC) techniques such as pipes, shared memory, and message queues. The server processes mathematical expressions sent by the client and returns the results.

## Installation
Follow these steps to set up the project on your local machine.

### Prerequisites
- GCC compiler
- Python3 (for evaluating expressions)
- Linux environment (preferably)

### Clone the Repository
```sh
git clone https://github.com/Satyamverma27/client-server-ipc.git
cd client-server-ipc


Execution Time Measurement Guide for Client-Server Architecture (C++ on Linux)
This guide covers quick and precise methods to measure the execution time of any client-server architecture in C++ on Linux.

⚙️ 1. Compilation
Compile both client and server programs using g++:

bash
Copy
Edit
g++ server.cpp -o server
g++ client.cpp -o client
⏱️ 2. Method 1: Using the time Command (Simple & Quick)
✅ Steps:
Run the Server:

bash
Copy
Edit
time ./server
Run the Client in Another Terminal:

bash
Copy
Edit
time ./client
🔍 Output Explanation:
sql
Copy
Edit
real    0m0.456s  → Total elapsed (wall-clock) time
user    0m0.123s  → CPU time in user mode
sys     0m0.045s  → CPU time in kernel mode


