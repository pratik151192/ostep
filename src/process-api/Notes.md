# Process API

What interface should an OS provide to enable process creation and control?

- Most interesting way is through a pair of syscalls: `fork()` and `exec()`
    - `wait()` can be used to wait for the created process to complete

**PID:** A process is identified through a unique ID which is its PID

`int return_code = fork()`

- <0: fork failed
- == 0: A new child process is spawned
- >0: Parent’s path

`fork()` creates an *almost* exact copy of the parent process. The OS thinks that there are two copies of the program running, and **both** are about to return from the syscall. It’s as if the child process called `fork` itself. However, the child does get its own address space, registers etc.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // only main thread will see this
    printf("Before fork running: %d \n", (int) getpid());

    // this is where the child process also enters
    // and gets a rc of 0. Parent gets a rc of child PID
    int fork_return_code = fork();

    printf("After fork running: %d \n", (int) getpid());

    if (fork_return_code == 0) {
        printf("Hello from the child process! ID: %d \n", (int) getpid());
    } else {
        printf("Parent, before waiting! ID: %d child PID: %d\n", (int) getpid(), fork_return_code);
        int wait_return_code = wait(NULL);
        printf("Parent, after waiting! ID: %d WRC: %d", (int) getpid(), wait_return_code);
    }
}
// gcc file.c && ./a.out
```

`wait()` forces the parent process to wait until the child exits/completes. Wait return code is also child’s PID. Without `wait()`, the **scheduler** (MOTL) can decide whichever process to run next.

`exec()` is the final most useful system call that can be used to run a program different from the one which calls it.  Linux has many variants (RTFM). This is a very useful syscall because it allows us to fork a process, *do some things,* and *then* `exec` a new program. Before the `exec`, the code can alternate the running environment enabling rich features. Shell, for example, works in similar ways. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
        printf("this shouldn't print out");
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	       rc, wc, (int) getpid());
    }
    return 0;
}
```

In above we are preparing the commands only after fork but before exec. A more interesting case is

`wc hello.c > wc.output`

In the above case, after the `fork` call, **standard output** FD is closed by the child process and opens the output file. Therefore the output is sent to file rather than the screen. Note FDs are kept open across `exec` invocations. Just add the below two lines in the beginning of the child process code (if revising and don’t know where to put, re-read :))

```c
	close(STDOUT_FILENO); 
	open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
```

Unix **pipes,** which is a queue, is implemented similarly. 

### Signals

`kill()` system call sends a **signal** to a process. Can contain directives such as pause, die, etc. 

Certain keystroke options can be used on linux for convenience. Common ones for `kill` are `9` (SIGKILL) and `2` (SIGINT(errupt)). `SIGSTP` can be used to pause and resume later. Processes can receive and process these signals as well which makes it a rich infrastructure for sending external events.  Processes use the `signal()` **syscall** to “catch” such signals and react. Only allowed **users** can send such signals after entering credentials.