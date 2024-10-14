#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    pid_t child_pid = fork();
     if (child_pid < 0) {
        write(STDERR_FILENO, "Error forking!", 14);
        exit(1);
    } else if (child_pid == 0) {
        
        char* argv[3];
        argv[0] = "ls";
        argv[1] = "-l";
        argv[2] = NULL;
        char *envp[0];

        // write(0, "execv", 5);
        // execv("ls", argv);
        // write(0, "execvp", 6);
        // execvp("ls", argv);
        // write(0, "execve", 6);
        // execve("ls", argv, envp);
        // write(0, "execl", 5);
        // execl("/bin/ls", "ls", "-l", NULL);
        // write(0, "execlp", 6);
        // execlp("ls", "ls", "-l", NULL);
        write(0, "execle", 6);
        execle("ls", "ls", "-l", NULL, NULL);
    } else {
        wait(NULL);
        printf("goodbye");
    }
}