#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); 
    if (pid < 0) { // failure
        perror("unable to fork program");
        return EXIT_FAILURE;
    } else if (pid == 0) { // child
    } else { // parent
    }
    return 0;
}
