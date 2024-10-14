#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int pi_pe[2];
    
    if (pipe(pi_pe) < 0){
        perror("Pipe error");
    }   

    pid_t child1_pid = fork();
    
    if (child1_pid == -1) {
        perror("Fork error");
        return 1;
    }

    if (child1_pid == 0) {
        // child1 enters

        // no need of the read end here as we are just writing
        close(pi_pe[0]);
        // dup will redirect STDOUT to our pipe
        dup2(pi_pe[1], STDOUT_FILENO); 
        close(pi_pe[1]);
        // write to pipe
        printf("hello");
    } else {
        // parent enters

        // spin new child
        pid_t child2_pid = fork();

        if (child2_pid == -1) {
            perror("Fork error");
            return 1;
        }

        if (child2_pid == 0) {
            close(pi_pe[1]);
            dup2(pi_pe[0], STDIN_FILENO);
            close(pi_pe[0]);

            char buf[6];
            // read from pipe
            fgets(buf, sizeof(buf), stdin);
            printf("Child 2 received: %s", buf);
        } else {

            // parent enters again.. wait for both children to complete
            waitpid(child1_pid, NULL, 0);
            waitpid(child2_pid, NULL, 0);   
        }
    }

    
    return 0;
}