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
        
        // write to pipe
        printf("hello");
        close(pi_pe[1]);
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
            

            char buf[6];
            // read from pipe
            fgets(buf, sizeof(buf), stdin);
            printf("Child 2 received: %s", buf);
            close(pi_pe[0]);
        } else {

            close(pi_pe[0]);  // Close unused read end in parent
            close(pi_pe[1]);  // Close unused write end in parent
            // parent enters again.. wait for both children to complete
            waitpid(child1_pid, NULL, 0);
            waitpid(child2_pid, NULL, 0);   
        }
    }

    
    return 0;
}