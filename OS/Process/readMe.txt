------------------------------------------------------------------- [

IPC: how processes communicate with each other, how threads work with each other? 
what are the different mechanisms to pass Messages between processes?
Give an example of race condition to acquire a resource between two processes? What type of race conditions/deadlocks could be there?
Mechanisms to resolve race conditions? Explain mutexes semaphores etc in detail?
How to avoid race condition using : Timeout for lock acquisition. AND Avoid circular dependencies.
How program memory is managed around virtual memory space allocation for newly loaded .so or .exec? 
What is the behaviour of a program in terms of resource and memory sharing when it loads/invokes/executes a .so or .exec?
How Memory Management Unit (MMU) maps the virtual addresses to physical addresses?
What are process scheduling algorithms? how system decide which process to give priority over other process?
How is a process different from a thread? how multiple threads managed by a single process? multithreading?
synchronization issues between multiple threads? synchronization issues between processes?
what is paging? when system has very low memory and want to execute multiple processes, who and how memory is managed?
what is context switching? how processor switches the context between 2 processes? how context switching between 2 processes is different from 2 threads?
file management by system? how file io operations work? what are the execution steps when a process requests to open a file and read the content?
why are file io operation so slow? how long will 1 GHz process take to read say 128 bytes or 128 bits of file content?
how long will a 1 GHz processor take to add two 32 bit integers? How processor speed is linked to clock speed? how to calculate processing power of a processor?
when we say 1 GHz processor, what exactly it means?
Producer consumer program?
Explain usage of fork() ? how and from where child and parent process execution starts? how system gives control to parent and child process? how wait command works to wait for the results of child process and stops execution of parent process?
Please write a complete program that can explain child process creation, parent process wait, execution order, resource sharing, synchronization aspects and message passing between parent and child process. I need to understand inter process communication in detail.
What is pipe() function and how it works? what is wait() function and how it works? how wait() in parent keeps execution of parent in waiting till child completes execution?
How mutex is used for synchronization in IPC? give an example.
What is normal (PTHREAD_MUTEX_NORMAL), recursive (PTHREAD_MUTEX_RECURSIVE) and shared mutex(PTHREAD_PROCESS_SHARED)? How shared memory is needed and used for shred mutex?
Difference between process and thread? How to divide a program to be executed with multiple threads and synchronize the output? How to handle resource sharing for such cases? How multi threading works in such scenario? give me elaborative example with all the details in code.
How to use synchronization primitives like mutexes, semaphores, condition variables, or barriers to coordinate threads. Give exapmle code for each.
How OS manages program counter, registers, and stack to run threads? How program counter works? Explain different registers and theit usage in detail? Thread control block, Process control block details?
How maximum memory usage is defined or decided for a process?
How to measure Processor power in flops (floating-point operations per second) or based on clock speed (GHz) and the number of cores. Examples?
How many instrunction will be needed to run below program?
  int main() {
    cout << "in main" << "\n";
    int a= 32000000;
    int b= 55;
    int c = a*b;
    return c;
  }
Can clock Speed fo 4 GHz having 4 cores (AVX-512 Unit: 16 single-precision FLOPS per cycle) system handle entries into a hashmap of size 72G at 25k entries per second?
Write a program to simulate clock Speed fo 4 GHz having 4 cores (AVX-512 Unit: 16 single-precision FLOPS per cycle) system handle entries into a hashmap of size 72G at 25k entries per second. Just a dummy program for performance calculation will work.
How thread parallelism is managed? why the number of threads be in range of available CPUs in the system? How thread distribution is done? How OS manages thread creation and parallelism?
IPC:pipes, sockets and shared memory. How processes communicate with each other, how threads work with each other? Give me the details of IPC mechanisms pipes, message queues, signals, sockets and shared memory. Give me the examples with lot of details.
In TCP Socket Example given above, how can i debug server() code in gdb i mean how to debug child process code in gdb?
------------------------------------------------------------------- ] 

Since processes have separate memory spaces, explicit methods are needed for them to exchange information.

Kernel creates a new process (child).
Child inherits:
  A copy of the parents memory.
  Open file descriptors.
  Environment variables.


On 32-bit systems, the virtual address space is typically limited to 2 to the power 32, or 4 GB, with a
On 64-bit systems, the virtual address space is vastly larger (2 to the power 64), though practical limits are imposed by the hardware and OS.
The processors memory management unit (MMU) dictates how much memory can be addressed and managed.
The total memory used by all processes is capped by available physical memory and swap space.



Measuring processor power can be done in two ways:
1. Measuring Processor Power in FLOPS
  Understand the FLOPS per core per cycle:
    Modern CPUs can perform multiple floating-point operations per cycle due to vector processing units (e.g., AVX or SSE instructions).
    For example, an AVX-512 unit can perform 16 single-precision (32-bit) or 8 double-precision (64-bit) floating-point operations per cycle.
  Multiply by clock speed:
    Multiply the number of FLOPS per core per cycle by the clock speed in Hz.
  Multiply by the number of cores:
    Finally, multiply the result by the number of physical cores to get the total theoretical FLOPS.
  Eg:
    Clock Speed: 3.5 GHz (3.5 billion cycles/second). + cores 4 + AVX-512 Unit: 16 single-precision FLOPS per cycle.
    = 3.5 billion x 4 x 16 = 224 billion instructions per second
2. Measuring Processor Power Based on Clock Speed (GHz)
  Determine the clock speed of the CPU (e.g., 3 GHz).
  Multiply by the number of cores. (4)
  Multiply by the average instructions per cycle (IPC). (say average 2)
  = 24 billion instructions per second

Real-World Example (Using Core i7 Processor)
  Clock Speed: 4.2 GHz + cores 8 + AVX-512 Instructions: 32 FLOPS/cycle/core for single precision.
  = 1075.2 billion instructions per second


The number of instructions required to execute a program depends on the specific machine code generated during compilation, the CPU architecture, and how the compiler optimizes the code.
