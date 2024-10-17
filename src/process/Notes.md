# Processes

**Process:** A running program. Otherwise, a program is just lying on disk. OS makes it a process

We often want to run more than one program. So the CRUX of the problem is can we (or the OS) provide the illusion of unlimited CPUs when only a few are available.

**Virtualization:** A way of OS to provide this illusion by switching b/w programs, based off of a concept called **time sharing.**

- Time sharing and space sharing are useful to virtualize the OS.

How to virtualize?

- Low level machinery: **mechanisms**, low-level methods/protocols that implement a functionality, such as a context switch. Mechanisms answers “how is it done?”
- High level intelligence: **policies,** algorithms for making decisions on the OS. e.g., which program to run given a list (and based on what factors?). Policies answer “which one?”

What constitutes a process?

To answer this, answer what is the **machine state** for a process, important for it’s execution?

- Memory: Where the program itself lives, and what the process can read and write to (it’s address space).
- Registers: Many instructions access registers directly.
    - Program Counter *(PC)*: which instruction will execute next? also called instruction pointer or IP.
    - Stack and Frame pointers: used to manage stack (for functions), variables, return addresses etc.
- I/O Information: Which persistent files/devices does the process access?

### Process API Requirements

Should provide APIs to create, destroy, wait, pause, resume, list status

Process Creation

![Screenshot 2024-09-16 at 10.32.05 PM.png](1%20Processes%20634a68373e1c436bb9d0908ad656e819/Screenshot_2024-09-16_at_10.32.05_PM.png)

- OS loads the program stored on disk or other flash memory
- OS allocates the address space for the run-time stack (to keep vars, return address etc).
    - Initializes the stack with args and specifically fill in the args to `main()`
- Then allocates memory for the program heap. Starts small but can expand and is dynamic
- Other initialization tasks like setting up I/O (open FDs) for stdout, stderr and stdin.
- Trigger the entry point of the program, and jumps to the `main()` routine (MOTL)
    - CPU control is transferred to the program which starts running.

Process States 

- **Ready:** In **descheduled** state, ready to be scheduled by the OS
- **Running:** Scheduled by the OS and executing
- **Blocked:** Most of the times blocked on things like I/O. Transitions to Ready before Running.

Scheduler does all of this and decides when and which process to resume or schedule and how.

### Data Structures

OS maintains data structures of itself like any other program.

- **Process List:** To track all the processes along with the mapping to their states.
- Each individual process is a C like structure called the **process control block** or **process descriptor.**
    - **Register context:** Contains register contents of stopped processes that must be restored to resume the process at a later time. Technique called context switch (MOTL)
    - Can contain other states like Initial, Exited and Zombie